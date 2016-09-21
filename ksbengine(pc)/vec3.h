#pragma once
#include<iostream>
#include<sstream>
#include<string>
#include<math.h>
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
			vec3 cross(vec3&);
			float dot(vec3&);
			void normalize();
			float getlength();
			std::string stringify();
			inline ~vec3(){ }
		};
}}