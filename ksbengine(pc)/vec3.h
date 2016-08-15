#pragma once
#include<iostream>
#include<sstream>
#include<string>
namespace ksbengine{namespace coreengine{
	class vec3{
		public:
			float x, y, z;
			vec3(float,float,float);
			vec3();
			vec3 operator +(vec3);
			vec3 operator -(vec3);
			vec3 operator *(float);
			vec3 operator /(float);
			void operator =(vec3);
			std::string stringify();
			inline ~vec3(){ }
		};
}}