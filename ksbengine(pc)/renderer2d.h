#pragma once
#include<vector>
#define GLEW_STATIC
#include<glew.h>
#include<glfw3.h>
#include"sprites2d.h"
#include"textures.h"
#define max_sprite 60000
#define max_texture 16
namespace ksbengine{namespace coreengine{
	class renderer2d{
	public:
		unsigned int spritecount;
		unsigned int texturecount;
	private:
		GLuint vertexarraybuffer;
		GLuint indexbuffer;
		GLuint texcoordbuffer;
		GLuint texidbuffer;
		std::vector<textures*> textureptrarray;
	public:
		renderer2d();
		void submit(sprites2d &thesprite);
		void renderall();
	public:
		void createallbuffers();
		void deleteallbuffers();
	private:
		void bindbuffer();
		void unbindbuffer();
	public:
		~renderer2d();
	};
}}