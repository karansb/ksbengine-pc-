#pragma once
#include"filereader.h"
#define GLEW_STATIC
#include<glew.h>
#include<glfw3.h>

namespace ksbengine{namespace coreengine{
		class shader{
		public:
			GLuint shaderid;
		public:
			shader(char*, char*);
			inline void enableshader(){ glUseProgram(shaderid); }
			inline void disableshader(){ glUseProgram(0); }
			inline ~shader(){ std::cout << "shader memory freed" << std::endl; disableshader(); glDeleteProgram(shaderid); }
		};
}}