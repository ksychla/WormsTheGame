#version 410

in vec3 iColor;

in vec4 l;
in vec4 n;
in vec4 v;

//uniform sampler2D textureMap;

layout(location = 0) out vec4 out_Color;

void main() {
    out_Color = vec4(iColor,1.f);
}
