#version 330

in vec3 CameraPos;

in vec3 CameraDir;
out vec4 FragColor;

//layout(location=0) out vec4 accum;
//in vec2 posi;

uniform vec3 volumeScale;
uniform mat4 invModelView;


//Transfer Function stuff
uniform float Brightness;
uniform float Density;
uniform float offset;
uniform float SamplingRate;
uniform float transparency;
uniform float StepSize;
uniform float transferScale;
uniform float transferOffset;
uniform float preIntCheck;

uniform float BoundingBox;
uniform float checkAmbient;


//Slicing stuff
uniform float SliceXleft;
uniform float SliceXright;

uniform float SliceYleft;
uniform float SliceYright;

uniform float SliceZleft;
uniform float SliceZright;

//Lighting Stuff the parameters are called from the main program
uniform float Shininess;
uniform float DiffuseContribution;
uniform float SpecularContribution;
uniform float AmbienceCoefficient;
vec3 lightPos = CameraPos;

// Sample texture volumne from CPU
uniform sampler3D volumeTex;
uniform sampler2D transferFuncTex;
uniform sampler2D PreIntTex;
uniform sampler3D AmbbientTex;

bool intersectBox(vec3 ori, vec3 dir, vec3 boxMin, vec3 boxMax, out float t0, out float t1)
{
        vec3 invDir = 1.0 / dir;
        vec3 tBot = invDir * (boxMin.xyz - ori);
        vec3 tTop = invDir * (boxMax.xyz - ori);

        vec3 tMin = min(tTop, tBot);
        vec3 tMax = max(tTop, tBot);

        vec2 temp = max(tMin.xx, tMin.yz);
        float tMinMax = max(temp.x, temp.y);
        temp = min(tMax.xx, tMax.yz);
        float tMaxMin = min(temp.x, temp.y);

        bool hit;
        if((tMinMax > tMaxMin))
                hit = false;
        else
                hit = true;

        t0 = tMinMax;
        t1 = tMaxMin;

        return hit;
}

vec3 sampleGrad(sampler3D sampler, vec3 coord)
{
        const int offset = 1;
        float dx = textureOffset(sampler, coord, ivec3(offset, 0, 0)).r - textureOffset(sampler, coord, ivec3(-offset, 0, 0)).r;
        float dy = textureOffset(sampler, coord, ivec3(0, offset, 0)).r - textureOffset(sampler, coord, ivec3(0, -offset, 0)).r;
        float dz = textureOffset(sampler, coord, ivec3(0, 0, offset)).r - textureOffset(sampler, coord, ivec3(0, 0, -offset)).r;
        return normalize(vec3(dx, dy, dz));
}

bool getBoundingBox(vec3 pos)
{
//    pos = CameraPos + CameraDir*t0;
//    vec3 pos1 = CameraPos + CameraDir*t1;

    if (BoundingBox==1){
    float outline;

    // outline is the size of the line in the bounding box

//      /------/|
//     /      / |
//    /------/  |
//    |      |  |
//    |      | /
//    |------|/
//               Idea is to have a bounding box of outline length Sorry for being inefficient with the code

    // Starting from origin 0,0,0
    outline = 0.006;
//    float outline2 = 0.005;
    if (pos.x < outline && pos.y < outline)
        return false;
    else if (pos.x < outline && pos.z < outline)
        return false;
    else if (pos.y < outline && pos.z < outline)
        return false;

    // Starting from 1,1,1
    else if (pos.x > 1-outline && pos.y > 1-outline)
        return false;
    else if (pos.x > 1-outline && pos.z > 1-outline)
        return false;
    else if (pos.y > 1-outline && pos.z > 1-outline)
        return false;


    //Starting from 1,0,0
    else if (pos.x > 1-outline && pos.y < outline)
        return false;
    else if (pos.x > 1-outline && pos.z < outline)
        return false;


    // Starting from 0,1,0
    else if (pos.y > 1-outline && pos.z < outline)
        return false;
    else if (pos.y > 1-outline && pos.x < outline)
        return false;


    // Starting from 0,0,1
    else if (pos.z > 1-outline && pos.x < outline)
        return false;
    else if (pos.z > 1-outline && pos.y < outline)
        return false;
}
    return true;
}

bool SliceViews(vec3 pos)
{
if ((pos.x > SliceXleft) && (pos.x < SliceXright) && (pos.y > SliceYleft) && (pos.y < SliceYright) && (pos.z > SliceZleft) && (pos.z < SliceZright))
    return true;

    return false;
}

float getLightIntensity(vec3 norm, vec3 pos, vec3 boxMin, vec3 boxDim)
{
    //vec3 dir = normalize(pos);
    float LightIntensity = 1.0f;
    // L->
    vec3 lightVec = normalize(lightPos - pos);
    // V->
    vec3 viewVec = normalize(CameraPos-pos);
    //R->
    vec3 reflectvec = -reflect(lightVec,norm);

    vec3 voxelCoord = (pos - boxMin)/(boxDim);


    float Iamb = AmbienceCoefficient;
    if (checkAmbient==1)
        Iamb = texture(AmbbientTex, voxelCoord).r*AmbienceCoefficient;
    else
        Iamb = AmbienceCoefficient;

    //calculate Diffuse Term:
    float Idiff =   DiffuseContribution * max(dot(norm, lightVec), 0.0);
    Idiff = clamp(Idiff, 0.0, 1.0);

    // calculate Specular Term:
    float Ispec = SpecularContribution*pow(max(dot(reflectvec,viewVec),0.0),Shininess);
    Ispec = clamp(Ispec, 0.0, 1.0);

    return (Idiff+Iamb+Ispec);
}

void main(void)
{
        vec3 boxMin = -volumeScale;
        vec3 boxMax = volumeScale;
        vec3 boxDim = boxMax - boxMin;
       // discard if ray-box intersection test fails
        vec3 dir = normalize(CameraDir);
        float t0, t1;
        bool hit = intersectBox(CameraPos, dir, boxMin, boxMax, t0, t1);
        if(!hit)
                discard;

       // discard if the volume is behind the camera
        t0 = max(t0, 0.0);

        if(t1 <= t0)
                discard;

        //Defining the variables
        vec3 pos = CameraPos + dir* t0;
        float t= t0;

        vec3 deltaDir = dir * SamplingRate;
        vec3 voxelCoord;
        vec3 LocalCoord;
        vec4 colorAcum = vec4(0.0); // The dest color
        colorAcum = vec4(0);

        float intensity = 0.0f;
        vec4 colorSample; // The src color

        float  LightIntensity =0.0f;

        vec2 lookup;

if (preIntCheck == 0){

    for(int i = 0; i < 700; i++)
    {

        //RAY MARCHING
        pos +=deltaDir;

        // Transforming to local co-ordinates
        voxelCoord = (pos - boxMin)/(boxDim);

            if (getBoundingBox(voxelCoord)){
                if(SliceViews(voxelCoord))
                {
                    //Sampling

                    intensity =  texture(volumeTex, voxelCoord).r;
                    lookup = vec2(intensity,0);
                    colorSample = texture(transferFuncTex,(lookup-transferOffset)*transferScale);

                    if(colorSample.w> 0.0){

                    // Phongs model
                    LightIntensity = getLightIntensity(-sampleGrad(volumeTex,voxelCoord),pos,boxMin,boxDim);

                    // Opacity correction
                    colorSample.a = (1.0 - pow(1.0 - colorSample.a,SamplingRate/0.01));

//                   //colorsample
                    colorSample.rgb*=colorSample.a;

//                  //phongs
                    colorSample.rgb*=LightIntensity;

                    //alpha accumalation
                    colorAcum += (1.0-colorAcum.a)*colorSample;
                    }

                }
                    if(colorAcum.a > 0.95f)
                        break;

                    t += SamplingRate;

                    if( t > t1 )
                        break;

                    if ((voxelCoord.x > 1.0f) || (voxelCoord.y > 1.0f) || (voxelCoord.z > 1.0f))
                        break;

                    if ((voxelCoord.x < 0.0f) || (voxelCoord.y < 0.0f) || (voxelCoord.z < 0.0f))
                        break;

                }
                else{
                    // Bounding box
                    colorAcum = vec4(1,0,0,1);
                    FragColor = colorAcum;
                    break;

                    }
                            }
                                }

        else{
            //Pre integration term
            //ray macrching
            voxelCoord = (pos - boxMin)/(boxDim);
            LocalCoord = voxelCoord;

            float FrontSample = texture(volumeTex, voxelCoord).r;

            //ray marching
            for(int i=0; i<700; i++){

            pos+=deltaDir;
            vec3 voxelCoord = (pos - boxMin)/(boxDim);
            vec3 LocalCoord = voxelCoord;

            if (getBoundingBox(LocalCoord)){

        if(SliceViews(voxelCoord))
        {
            float BackSample = texture(volumeTex, voxelCoord).r;
            vec4 colorSample = texture(PreIntTex , vec2(FrontSample, BackSample));

            if(colorSample.w> 0.0){

            // Phongs model
            LightIntensity = getLightIntensity(-sampleGrad(volumeTex,voxelCoord),pos,boxMin,boxDim);

            //Color multiplication
            colorSample.rgb*=LightIntensity;

            //alpha compositing
            colorAcum+= (1.0 - colorAcum.a)*colorSample;
            }
            //Front sample equal to back sample
            FrontSample=BackSample;
            //Reaching absolute opacity
            if(colorAcum.a > 0.95f)
                break;
                }
            // Sampling length of the ray caster
            t += SamplingRate;

            // End cases
            if( t > t1 )
                break;

            if ((voxelCoord.x > 1.0f) || (voxelCoord.y > 1.0f) || (voxelCoord.z > 1.0f))
                break;

            if ((voxelCoord.x < 0.0f) || (voxelCoord.y < 0.0f) || (voxelCoord.z < 0.0f))
                break;

            }
            else{
                // Bounding box
                colorAcum = vec4(1,0,0,1);
                FragColor = colorAcum;
                break;
                    }
                        }
                          }

        // Idea to sample the volumne at a constant rate for the bounding box
             FragColor = colorAcum;
}
