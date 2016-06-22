#version 330
layout(location=0) out vec4 accum;
in vec2 pos;

uniform sampler2D transferFuncTex;
uniform float d; //sampling period
//uniform float d0; //d0 for opacity correction

void main(){
    accum = vec4(0,0,0,0);
    float TFSize = float(textureSize(transferFuncTex,0).x);
    float s = pos.x, t = pos.y;
    int steps = int(round(abs(t-s)*TFSize)) + 1;
    float delta = sign(t-s)/TFSize;
    float OCFact = d/(0.01*float(steps));

for(int i=0; i<steps; i++){
        vec4 c = texture(transferFuncTex, vec2(s,0));
        c.a = 1.0 - pow(1.0 - c.a, OCFact);
        c.rgb *= c.a;
        accum += (1.0-accum.a)*c;
        s += delta;
            }

    accum = clamp(accum, vec4(0.0), vec4(1.0));
}
