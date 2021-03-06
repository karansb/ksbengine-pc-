#version 330 core
out vec4 color;
in vec3 thenormals;
uniform vec3 lightdir=vec3(1,-1,0);
void main(){
float brightness=dot(thenormals,-lightdir);
brightness=max(brightness,0.2);
vec3 lightcolor=vec3(brightness,brightness,brightness);
vec4 mycolor=vec4(0.3,0,0.3,1);
vec3 lightcol=vec3(0,0,0.5);
color=vec4(lightcolor,1);
}