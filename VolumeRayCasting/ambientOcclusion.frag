#version 330
layout(location=0) out vec4 accum;

in vec2 pos;
const float numRays = 8;
uniform float layer;
const float Pi = 3.14159265358979323846264;
uniform vec3 volumeScale;

// Sample texture volumne from CPU
uniform sampler3D volumeTex;
uniform sampler2D PreIntTex;
uniform sampler2D transferFuncTex;
uniform float Zvolume;
uniform float RayStepSize;

//const float rayStepSize = 0.03;

const float numRaySamples = 4;

mat3  rotateRayX(float deltaTheta){
    return mat3(1, 0, 0,0, cos(deltaTheta), sin(deltaTheta),0, -1*sin(deltaTheta), cos(deltaTheta));
}

mat3  rotateRayY(float deltaTheta){
    return mat3(cos(deltaTheta), 0, -1*sin(deltaTheta),0, 1, 0,sin(deltaTheta), 0, cos(deltaTheta));
}

mat3  rotateRayZ(float deltaTheta){
    return mat3(cos(deltaTheta), sin(deltaTheta), 0,-1*sin(deltaTheta), cos(deltaTheta), 0,0, 0, 1);
}
void main(){

    float deltaTheta;
    deltaTheta = (2 * Pi)/numRays;

    mat3 RotateRayX;
    mat3 RotateRayY;
    mat3 RotateRayZ;

    //Get the direction of the ray that needs to be
    vec3 dir = normalize(vec3(1,0,0));

    float XTheta=0,YTheta=0,ZTheta=0;

    accum =vec4(0,0,0,0);
    //Number of rays
    for (int xray=0; xray < 2; xray++) {
    for (int yray=0; yray < 2; yray++) {
    for (int zray=0; zray < 2; zray++) {
            //Preprocessing before sending the ambient occlsuion shader

            RotateRayX = rotateRayX(XTheta);
            RotateRayY = rotateRayY(YTheta);
            RotateRayZ = rotateRayZ(ZTheta);

            dir = RotateRayX*RotateRayY*RotateRayZ*dir;

            vec3 PosCurrent = vec3(pos,layer);

            vec3 deltaRay = dir*RayStepSize;

            // Single Ray
            float s = texture(volumeTex , vec3(pos, layer)).r;
            PosCurrent = vec3(pos,layer) + deltaRay;

            vec4 singleRayAccum = vec4(0);

            for (int i=0; i<numRaySamples; i++){

                float t = texture(volumeTex, PosCurrent).r;
                float a = texture(PreIntTex, vec2(s,t)).a;

                singleRayAccum += (1.0/numRays)*(1.0 - singleRayAccum.a)*a;
                s = t;
                PosCurrent += deltaRay;
            }
            accum += singleRayAccum;

            ZTheta += deltaTheta;
        }
        YTheta += deltaTheta;
    }
    XTheta += deltaTheta;
}

////    accum = vec4(1,0,1,1);
    accum = clamp(accum, vec4(0.0), vec4(1.0));
}
