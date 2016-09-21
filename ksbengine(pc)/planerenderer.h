#pragma once
#include "vec3.h"
#include "shader.h"
#include "camera.h"
namespace ksbengine{ namespace coreengine{
	class planerenderer{
	public:
		GLfloat points[12];
	private:
		shader *planeshader;
		camera *thecam;
		GLuint pointbuffer;
	public:
		planerenderer(vec3& lefttop,vec3& leftbottom,vec3& rightbottom,vec3& righttop,shader &theshader,camera *mycam);
		void renderplane();
	};

} }