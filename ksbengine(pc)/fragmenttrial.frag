#version 330 core
out vec4 color;
in vec2 thetexcoord;
in float texid;
uniform sampler2D textures[16];
void main(){
int a=int(texid);
color=vec4(1,0,1,1);
if(texid>0||texid==0){
color=texture(textures[a],thetexcoord);
}
}