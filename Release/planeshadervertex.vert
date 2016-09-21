#version 330 core
layout(location=0)in vec4 vertices;
uniform mat4 projmat=mat4(1);
uniform mat4 ml_translation=mat4(1);
uniform mat4 ml_rotation=mat4(1);
uniform mat4 ml_scale=mat4(1);
uniform mat4 cam_translation=mat4(1);
uniform mat4 cam_rotation=mat4(1);
void main(){
gl_Position=projmat*(vertices*ml_scale*ml_rotation*ml_translation*cam_rotation*cam_translation);
}