#include"vec2.h"
namespace ksbengine{namespace coreengine{
	vec2::vec2(float otherx,float othery){
		x = otherx;
		y = othery;
	}
	vec2::vec2(){
		x = 0;
		y =0;
	}

	vec2 vec2::operator +(vec2 other){
		vec2 result;
		result.x = x + other.x;
		result.y = y + other.y;
		return result;

	}
	vec2 vec2::operator -(vec2 other){
		vec2 result;
		result.x = x - other.x;
		result.y = y - other.y;
		return result;
	}
	
	vec2 vec2::operator *(float other){
		vec2 result;
		result.x = x * other;
		result.y = y * other;
		return result;
	}
	vec2 vec2::operator /(float other){
		vec2 result;
		result.x = x / other;
		result.y = y / other;
		return result;
	}
	std::string vec2::stringify(){
		std::stringstream str;
		str << x << "," << y;
		const std::string tmp = str.str();
		return tmp;
	}
	void vec2::operator =(vec2 other){
		x = other.x;
		y = other.y;
	}
	

}}