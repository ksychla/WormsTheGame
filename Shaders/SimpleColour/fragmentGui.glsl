#version 410

in vec3 iColor;

layout(location = 0) out vec4 out_Color;

void main() {
    out_Color = vec4(iColor,1.f);
}
