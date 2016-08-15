#include"vec3.h"
namespace ksbengine{
	namespace coreengine{
		vec3::vec3(float otherx, float othery, float otherz){
			x = otherx;
			y = othery;
			z = otherz;
		}
		vec3::vec3(){
			x = 0;
			y = 0;
			z = 0;
		}
		vec3 vec3::operator +(vec3 other){
			vec3 result;
			result.x = x + other.x;
			result.y = y + other.y;
			result.z = z + other.z;
			return result;

		}
		vec3 vec3::operator -(vec3 other){
			vec3 result;
			result.x = x - other.x;
			result.y = y - other.y;
			result.z = z - other.z;
			return result;
		}

		vec3 vec3::operator *(float other){
			vec3 result;
			result.x = x * other;
			result.y = y * other;
			result.z = z * other;
			return result;
		}
		vec3 vec3::operator /(float other){
			vec3 result;
			result.x = x / other;
			result.y = y / other;
			result.z = z / other;
			return result;
		}
		std::string vec3::stringify(){
			std::stringstream str;
			str << x << "," << y << "," << z;
			const std::string tmp = str.str();
			return tmp;
		}
		void vec3::operator =(vec3 other){
			x = other.x;
			y = other.y;
			z = other.z;
		}
		
}}