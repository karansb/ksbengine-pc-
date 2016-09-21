#include "planerenderer.h"
namespace ksbengine{ namespace coreengine{
	planerenderer::planerenderer(vec3& lefttop, vec3& leftbottom, vec3& rightbottom, vec3& righttop, shader &theshader,camera *mycam){
		thecam = mycam;
		planeshader = &theshader;
		points[9] = lefttop.x;
		points[10] = lefttop.y;
		points[11] = lefttop.z;

		points[6] = leftbottom.x;
		points[7] = leftbottom.y;
		points[8] = leftbottom.z;

		points[3] = rightbottom.x;
		points[4] = rightbottom.y;
		points[5] = rightbottom.z;

		points[0] = righttop.x;
		points[1] = righttop.y;
		points[2] = righttop.z;

		glGenBuffers(1, &pointbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, pointbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*12, points, GL_STATIC_DRAW);

	}
	void planerenderer::renderplane(){
		planeshader->enableshader();
		glUniformMatrix4fv(glGetUniformLocation(planeshader->shaderid, "projmat"), 1, GL_TRUE, mat4::perspective(640 / 480, 60, -1, 1090).mymatrix4x4);//mat4::orthographic(100, -100, 100, -100, 100, -100).mymatrix4x4);
		glBindBuffer(GL_ARRAY_BUFFER, pointbuffer);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, NULL, NULL);
		glUniformMatrix4fv(glGetUniformLocation(planeshader->shaderid, "cam_translation"), 1, GL_TRUE, thecam->posmatix->mymatrix4x4);
		
		glUniformMatrix4fv(glGetUniformLocation(planeshader->shaderid, "cam_rotation"), 1, GL_TRUE,thecam->rotmatix->mymatrix4x4);//mul(mat4::rotation(camroty,vec3(0,1,0))).mymatrix4x4);
		
		glUniformMatrix4fv(glGetUniformLocation(planeshader->shaderid, "ml_translation"), 1, GL_TRUE, mat4::translation(vec3(0, 0, 0)).mymatrix4x4);
		glUniformMatrix4fv(glGetUniformLocation(planeshader->shaderid, "ml_rotation"), 1, GL_TRUE, mat4::rotation(0,vec3(0,1,0)).mymatrix4x4);

		glUniformMatrix4fv(glGetUniformLocation(planeshader->shaderid, "ml_scale"), 1, GL_TRUE, mat4::scaling(vec3(5, 5, 5)).mymatrix4x4);
		
		glDrawArrays(GL_QUADS, 0,4);
		//planeshader->disableshader();
	}
} }