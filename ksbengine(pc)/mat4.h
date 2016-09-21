#pragma once
#include"vec2.h"
#include"vec3.h"
#include"sprites2d.h"
#define PI 3.14159265
namespace ksbengine{namespace coreengine{
		class mat4{
		public:
			float mymatrix4x4[16];
		public:
			mat4(float diagonal);
			static mat4 orthographic(float, float, float, float, float, float);
			static mat4 perspective(float, float, float, float);
			static mat4 translation(vec3&);
			static mat4 scaling(vec3&);
			static mat4 rotation(float,vec3&);
			static mat4 rotation(vec3&);
			mat4 mul(mat4&);
			static void transformit(mat4&,vec3&);
			static void transformit(mat4&,vec2&);
			static void transformit(mat4&, sprites2d&);
			void operator =(mat4&);
			inline ~mat4(){ };
		};
		
}}