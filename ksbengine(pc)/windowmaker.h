#pragma once
#define GLEW_STATIC
#include<glew.h>
#include<glfw3.h>
#include<iostream>
namespace ksbengine{namespace coreengine{
		class windowmaker{
		private:
			const char *gamename;
			int windowwidth;
			int windowheight;
		public:
			GLFWwindow *mywindow;
			windowmaker(const char *, int, int);
		private:
			void windowinit();
		public:
			bool checkwindowclosed();
			~windowmaker();
		};
}}