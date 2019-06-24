#version 410

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 col;


uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;   // współrzedne źródła światła

out vec3 iColor;

void main() {
    iColor=col;

    gl_Position = MVP * vec4(pos, 1.0);
}
