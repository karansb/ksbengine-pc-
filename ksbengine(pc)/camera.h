#pragma once
#include "vec3.h"
#include "mat4.h"
namespace ksbengine{namespace coreengine{
	class camera{
	public:
		vec3 rotation;
		vec3 position;
		mat4 *rotmatix;
		mat4 *posmatix;
	public:
		camera(vec3& rot,vec3& pos);
		void updatecamera(vec3& rot,vec3& pos);
	};
}}
