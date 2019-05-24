#version 410

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 col;


uniform mat4 MVP;

out vec3 iColor;

void main(void){
    iColor = col;
    gl_Position = MVP * vec4(pos, 1);
}