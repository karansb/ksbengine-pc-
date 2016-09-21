#pragma once
#include<iostream>
#include<sstream>
#include<string>
namespace ksbengine{namespace coreengine{
	class vec2{
	public:
		float x, y;
	public:
		vec2(float,float);
		vec2();
		vec2 operator +(vec2);
		vec2 operator -(vec2);
		vec2 operator *(float);
		vec2 operator /(float);
		void operator =(vec2);
		std::string stringify();
	};
}}