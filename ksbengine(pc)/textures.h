#pragma once
#define GLEW_STATIC
#include<glew.h>
#include<glfw3.h>
#include<FreeImage.h>
#include<iostream>
namespace ksbengine{namespace coreengine{
	class textures{
	private:
		const char *imgpath;
	public:
		GLuint textureid;
		textures(const char *imagepath);
		void bindtexture();
		void unbindtexture();
		~textures();
	};
}}