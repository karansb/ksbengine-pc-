#version 330 core
layout(location=0)in vec4 vertices;
layout(location=1)in vec3 normals;
uniform mat4 projmat;
uniform mat4 translation;
uniform mat4 rotation;
out vec3 thenormals;
void main(){
thenormals=(rotation*vec4(normals,0)).xyz;
gl_Position=projmat*((rotation*vertices)*translation);
}