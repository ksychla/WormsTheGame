#version 410

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 col;
layout(location = 2) in vec2 uvs;
layout(location = 3) in vec3 norm;


uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform vec4 lp;    // współrzedne źródła światła

out vec4 l;
out vec4 n;
out vec4 v;

out vec3 iColor;
//out vec2 texCoord;

void main() {
    l=normalize(V*(M*lp-M*vec4(pos, 1.0))); //Wektor "do œwiat³a" w przestrzeni oka
    n=normalize(V*M*vec4(norm, 0.0)); //Wektor normalny w przestrzeni oka
    v=normalize(vec4(0,0,0,1)-V*M*vec4(pos, 1.0)); //Wektor "do obserwatora" w przestrzeni oka
    iColor = col;

//    l=normalize(V*(lp-M*vec4(pos,1.0))); //Wektor "do światła" w przestrzeni oka
//    n=normalize(V*M*vec4(norm,0.0)); //Wektor normalny w przestrzeni oka
//    v=normalize(vec4(0,0,0,1)-V*M*vec4(pos,1.0)); //Wektor "do obserwatora" w przestrzeni oka
//
//    texCoord=uvs;

    gl_Position = MVP * vec4(pos, 1.0);
}
