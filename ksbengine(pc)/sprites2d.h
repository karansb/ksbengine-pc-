#pragma once
#define GLEW_STATIC
#include<glew.h>
#include<glfw3.h>
#include"textures.h"
namespace ksbengine{namespace coreengine{
	class sprites2d{
	public:
		GLfloat *vertexarray;
		textures *mytexture;
	public:
		sprites2d(GLfloat *vertexarraypassed,textures &texturepassed);
		sprites2d(GLfloat *vertexarraypassed);
		//~sprites2d();
	};
}}