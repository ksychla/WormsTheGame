#version 410

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 col;
layout(location = 3) in vec3 norm;


uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform vec4 lp;    // współrzedne źródła światła
uniform vec4 lp2;

out vec4 l;
out vec4 n;
out vec4 v;

out vec3 iColor;


vec3 lighting(){
    vec3 ld = vec3(0.5,0.5,0.5);
    vec3 normal = norm;
    float brightness = max(dot(lp.xyz, norm), 0.0);
    return ld*0.5 + brightness * ld * 0.5;
}

float light(vec4 lc){
    vec3 kd=col; //Kolor obiektu
    vec3 ld=vec3(1,1,1); //Kolor œwiat³a

    vec4 l=normalize(V*(lc-M*vec4(pos,1.0))); //Wektor "do œwiat³a" w przestrzeni oka
    vec4 n=normalize(V*M*vec4(norm, 0.0)); //Wektor normalny w przestrzeni oka

    return clamp(dot(n,l),0,1);
}

void main(void){
//    l=normalize(V*(M*lp-M*vec4(pos, 1.0))); //Wektor "do œwiat³a" w przestrzeni oka
//    n=normalize(V*M*vec4(norm, 0.0)); //Wektor normalny w przestrzeni oka
//    v=normalize(vec4(0,0,0,1)-V*M*vec4(pos, 1.0)); //Wektor "do obserwatora" w przestrzeni oka
//    iColor = col;

    vec3 kd=col;
    float nl = light(lp);
    float nl2 = light(lp2);
    iColor=kd.rgb*nl/2 + kd.rgb*nl2/2;// + kd.rgb/5 ;


    gl_Position = MVP * vec4(pos, 1.0);
}