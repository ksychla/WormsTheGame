#version 410

in vec3 iColor;

in vec4 l;
in vec4 n;
in vec4 v;
//in vec2 texCoord;

//uniform sampler2D textureMap;

layout(location = 0) out vec4 out_Color;

void main() {
    vec4 kd=vec4(iColor, 1.0); //Kolor materia�u dla �wiat�a rozpraszanego
    vec4 ld=vec4(1,1,1,1); //Kolor �wiat�a rozpraszanwego
    vec4 ks=vec4(1,1,1,1); //Kolor odbi� materia�u
    vec4 ls=vec4(1,1,1,1); //Kolor �wiat�a odbijanego

    vec4 ml=normalize(l);
    vec4 mn=normalize(n);
    vec4 mv=normalize(v);
    vec4 mr=reflect(-ml,mn); //Wektor kierunku odbicia w przestrzeni oka

    float nl=clamp(dot(mn,ml),0,1); //cos k�ta pomi�dzy wektorami n i l
    float rv=pow(clamp(dot(mr,mv),0,1),10); //cos k�ta pomi�dzy wektorami r i v podniesiony do pot�gi (wyk�adnik Phonga)

    out_Color=vec4(kd.rgb*ld.rgb*nl+ks.rgb*ls.rgb*rv,kd.a) + vec4(iColor/2, 1.0);
    //    out_Color = vec4(iColor,1.f);

//    vec4 kd=texture(textureMap,texCoord);  //Kolor materia?u dla ?wiat?a  rozpraszanego
//    vec4 ld=vec4(1,1,1,1); //Kolor ?wiat?a  rozpraszanego
//    vec4 ks=vec4(1,1,1,1); //Kolor odbi? materia?u
//    vec4 ls=vec4(1,1,1,1); //Kolor ?wiat?a odbijanego
//
//    vec4 ml=normalize(l);
//    vec4 mn=normalize(n);
//    vec4 mv=normalize(v);
//    vec4 mr=reflect(-ml,mn); //Wektor kierunku odbicia w przestrzeni oka
//
//    float nl=clamp(dot(mn,ml),0,1); //cos k?ta pomi?dzy wektorami n i l
//    float rv=pow(clamp(dot(mr,mv),0,1),25); //cos k?ta pomi?dzy wektorami r i v podniesiony do pot?gi (wyk?adnik Phonga)
//
//    out_Color=vec4(kd.rgb*ld.rgb*nl+ks.rgb*ls.rgb*rv,kd.a);
}
