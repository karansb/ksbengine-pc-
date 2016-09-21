#include"mat4.h"
#define elements_per_row 4
namespace ksbengine{namespace coreengine{
	float toradians(float);
		mat4::mat4(float diagonal=1){
			for (int i = 0; i < 16;i++){
				mymatrix4x4[i] = 0;
			}
			mymatrix4x4[0 * elements_per_row + 0] = diagonal;
			mymatrix4x4[1 * elements_per_row + 1] = diagonal;
			mymatrix4x4[2 * elements_per_row + 2] = diagonal;
			mymatrix4x4[3 * elements_per_row + 3] = diagonal;

		}
		mat4 mat4::orthographic(float right, float left, float top, float bottom, float far, float near){
			mat4 result;
			result.mymatrix4x4[0 * elements_per_row + 0] = 2 / (right - left);
			result.mymatrix4x4[1 * elements_per_row +1] = 2 / (top - bottom);
			result.mymatrix4x4[2 * elements_per_row + 2] = -2 / (far - near);
			result.mymatrix4x4[0 * elements_per_row + 3] = (right+left) / (right- left)*-1;
			result.mymatrix4x4[1 * elements_per_row + 3] = (top + bottom) / (top- bottom)*-1;
			result.mymatrix4x4[2 * elements_per_row + 3] = (far + near) / (far- near)*-1;
			return result;
		}
		mat4 mat4::perspective(float aspectratio, float fieldofview, float nearz, float farz){
			mat4 result;
			float f = 1 / (tan((toradians(fieldofview))/2));
			result.mymatrix4x4[0 * elements_per_row + 0] = f / aspectratio;
			result.mymatrix4x4[1 * elements_per_row + 1] = f;
			result.mymatrix4x4[2 * elements_per_row + 2] = (farz + nearz) / (nearz - farz);
			result.mymatrix4x4[3 * elements_per_row + 3] = 0;
			result.mymatrix4x4[3 * elements_per_row + 2] =(2*farz*nearz)/(nearz-farz);
			result.mymatrix4x4[2 * elements_per_row + 3] =-1;
				return result;
				
		}
		mat4 mat4::translation(vec3 &thevector){
			mat4 result;
			result.mymatrix4x4[3 * elements_per_row + 0] = thevector.x;
			result.mymatrix4x4[3 * elements_per_row + 1] = thevector.y;
			result.mymatrix4x4[3 * elements_per_row + 2] = thevector.z;
			return result;
		}
		mat4 mat4::scaling(vec3 &scalevector){
			mat4 result;
			result.mymatrix4x4[0 * elements_per_row + 0] = scalevector.x;
			result.mymatrix4x4[1 * elements_per_row + 1] = scalevector.y;
			result.mymatrix4x4[2 * elements_per_row + 2] = scalevector.z;
			return result;
		}
		mat4 mat4::rotation(float angledegree,vec3 &axis){
			mat4 result;
			float rad = toradians(angledegree);
			float c = cos(rad);
			float s = sin(rad);
			float f = 1 - c;

			result.mymatrix4x4[0 * elements_per_row + 0] = f*axis.x*axis.x + c;
			result.mymatrix4x4[1 * elements_per_row + 0] = f*axis.x*axis.y - s*axis.z;
			result.mymatrix4x4[2 * elements_per_row + 0] = f*axis.x*axis.z + s*axis.y;

			result.mymatrix4x4[0 * elements_per_row + 1] = f*axis.x*axis.y + s*axis.z;
			result.mymatrix4x4[1 * elements_per_row + 1] = f*axis.y*axis.y + c;
			result.mymatrix4x4[2 * elements_per_row + 1] = f*axis.y*axis.z - s*axis.x;

			result.mymatrix4x4[0 * elements_per_row + 2] = f*axis.x*axis.z - s*axis.y;
			result.mymatrix4x4[1 * elements_per_row + 2] = f*axis.y*axis.z + s*axis.x;
			result.mymatrix4x4[2 * elements_per_row + 2] = f*axis.z*axis.z + c;
			return result;
		}

		mat4 mat4::rotation(vec3 &angles){
			mat4 result;
			result = mat4::rotation(angles.x,vec3(1,0,0)).mul(mat4::rotation(angles.y,vec3(0,1,0)).mul(mat4::rotation(angles.z,vec3(0,0,1))));
			return result;
		}
		mat4 mat4::mul(mat4 &other){
			mat4 result;
			for (int i = 0; i <= 3; i++) {
				for (int j = 0; j <= 3; j++) {
					float sum = 0;
					for (int k = 0; k <= 3; k++) {
						sum = sum + mymatrix4x4[i*elements_per_row+k] * other.mymatrix4x4[k*elements_per_row+j];
					}
					result.mymatrix4x4[i*elements_per_row+j] = sum;
				}
			}
			/*for (int row = 0; row < 4;row++){
				float sum = 0;
				int column = 0;
				for (column = 0; column < 4; column++){
					sum += mymatrix4x4[row*elements_per_row + column] * other.mymatrix4x4[column*elements_per_row + row];
				}
				result.mymatrix4x4[row*column] = sum;
			}*/
			return result;
		}
		
		void mat4::transformit(mat4 &transformation,vec2 &point){
			vec2 temp;
			temp.x = (point.x*transformation.mymatrix4x4[0 * 4 + 0]) + (point.y*transformation.mymatrix4x4[1 * 4 + 0]) + (0 * transformation.mymatrix4x4[2 * 4 + 0]) + (1 * transformation.mymatrix4x4[3 * 4 + 0]);
			temp.y = (point.x*transformation.mymatrix4x4[0 * 4 + 1]) + (point.y*transformation.mymatrix4x4[1 * 4 + 1]) + (0 * transformation.mymatrix4x4[2 * 4 + 1]) + (1 * transformation.mymatrix4x4[3 * 4 + 1]);
			point = temp;
		}
		void mat4::transformit(mat4 &transformation, vec3 &point){
			vec3 temp;
			temp.x = (point.x*transformation.mymatrix4x4[0 * 4 + 0]) + (point.y*transformation.mymatrix4x4[1 * 4 + 0]) + (point.z*transformation.mymatrix4x4[2 * 4 + 0]) + (1 * transformation.mymatrix4x4[3 * 4 + 0]);
			temp.y = (point.x*transformation.mymatrix4x4[0 * 4 + 1]) + (point.y*transformation.mymatrix4x4[1 * 4 + 1]) + (point.z*transformation.mymatrix4x4[2 * 4 + 1]) + (1 * transformation.mymatrix4x4[3 * 4 + 1]);
			temp.z = (point.x*transformation.mymatrix4x4[0 * 4 + 2]) + (point.y*transformation.mymatrix4x4[1 * 4 + 2]) + (point.z*transformation.mymatrix4x4[2 * 4 + 2]) + (1 * transformation.mymatrix4x4[3 * 4 + 2]);
			point = temp;
		}
		void mat4::transformit(mat4 &transformation,sprites2d &thesprite){
			GLfloat theresult[12];
			for (int i = 0; i < 4;i++){
				theresult[i*3+0] = (thesprite.vertexarray[i*3+0]*transformation.mymatrix4x4[0 * 4 + 0]) + (thesprite.vertexarray[i*3+1]*transformation.mymatrix4x4[1 * 4 + 0]) + (thesprite.vertexarray[i*3+2]*transformation.mymatrix4x4[2 * 4 + 0]) + (1 * transformation.mymatrix4x4[3 * 4 + 0]);
				theresult[i * 3 + 1] = (thesprite.vertexarray[i * 3 + 0] * transformation.mymatrix4x4[0 * 4 + 1]) + (thesprite.vertexarray[i * 3 + 1] * transformation.mymatrix4x4[1 * 4 + 1]) + (thesprite.vertexarray[i * 3 + 2] * transformation.mymatrix4x4[2 * 4 + 1]) + (1 * transformation.mymatrix4x4[3 * 4 + 1]);
				theresult[i * 3 + 2] = (thesprite.vertexarray[i * 3 + 0] * transformation.mymatrix4x4[0 * 4 + 2]) + (thesprite.vertexarray[i * 3 + 1] * transformation.mymatrix4x4[1 * 4 + 2]) + (thesprite.vertexarray[i * 3 + 2] * transformation.mymatrix4x4[2 * 4 + 2]) + (1 * transformation.mymatrix4x4[3 * 4 + 2]);
			}

			for (int i = 0; i < 12;i++){
				thesprite.vertexarray[i] = theresult[i];
			}
			}
		void mat4::operator=(mat4 &other){
			for (int i = 0; i < 16;i++){
				mymatrix4x4[i] = other.mymatrix4x4[i];
			}
		}
		float toradians(float angledegree){
			return ((angledegree / 180) * PI);
		}

}}