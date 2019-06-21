#version 410

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 col;
layout(location = 3) in vec3 norm;


uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform vec4 lp;    // współrzedne źródła światła

out vec3 iColor;




void main(void){
    vec3 kd=col; //Kolor obiektu
    vec3 ld=vec3(1,1,1); //Kolor œwiat³a



    vec4 l=normalize(V*(lp-M*vec4(pos,1.0))); //Wektor "do œwiat³a" w przestrzeni oka
    vec4 n=normalize(V*M*vec4(norm, 1.0)); //Wektor normalny w przestrzeni oka

    float nl=clamp(dot(n,l),0,1);

    iColor=kd.rgb*nl;
//    iColor = col;
    gl_Position = MVP * vec4(pos, 1.0);
}