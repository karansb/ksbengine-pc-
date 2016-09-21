#include "camera.h"
namespace ksbengine{namespace coreengine{
	camera::camera(vec3& rot,vec3& pos){
		rotation.x = rot.x;
		rotation.y = rot.y;
		rotation.z = rot.z;

		position.x = pos.x;
		position.y = pos.y;
		position.z = pos.z;

		updatecamera(rot,pos);

	}
	void camera::updatecamera(vec3& rot, vec3& pos){
		
		rotmatix= &( mat4::rotation(rot.y, vec3(0, 1, 0)).mul(mat4::rotation(rot.x, vec3(1, 0, 0)).mul(mat4::rotation(rot.z, vec3(0, 0, 1)))));
		posmatix = &(mat4::translation(pos));
	}
}}