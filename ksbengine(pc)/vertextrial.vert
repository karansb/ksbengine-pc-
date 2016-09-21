#version 330 core
layout(location=0)in vec4 vertpos;
layout(location=1)in vec2 texcoord;
layout(location=2)in float tex_id; 
uniform mat4 projmat;
out vec2 thetexcoord;
out float texid;
void main(){
texid=tex_id;
thetexcoord=texcoord;
gl_Position=projmat*vertpos;
}

 