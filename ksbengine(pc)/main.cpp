#include"windowmaker.h"
#include"filereader.h"
#include"shader.h"
#include"vec2.h"
#include"vec3.h"
#include"mat4.h"
#include"renderer2d.h"
#include"textures.h"
#include"sprites2d.h"
#include"objfileloader.h"

using namespace ksbengine;
using namespace coreengine;

#define testing 1
#define debug 1
#if debug 1
#define logit(x) std::cout<<x<<std::endl
#else
#define logit(x)
#endif
#if !testing

//static sprites faster when renderer does not recreate buffer every frame
//moving sprites need to submit vertex data every frame, which means buffer need to be deleted after drawing and recreated before submission

int main(){
	const int screenwidth = 640;
	const int screenheight = 480;
	windowmaker mywindow("my game no engine",screenwidth,screenheight);
	GLfloat vertexarray[] = {
	1,-1,10,
	-1,-1,10,
	-1,-3,10,
	1 , -3, 10
	};
	renderer2d *therenderer=new renderer2d();
	textures *thetexture=new textures("..\\textures png\\testimage.png");
	textures *thetexture1 = new textures("..\\textures png\\imagetest.png");;
	sprites2d *thesprite=new sprites2d(vertexarray,*thetexture);

	GLfloat vertexarray1[] = {
		1, -1, 10,
		-1, -1, 10,
		-1, -3, 10,
		1, -3, 10
	};
	vertexarray1[2] += 5;
	vertexarray1[5] += 5;
	vertexarray1[8] += 5;
	vertexarray1[11] += 5;

	sprites2d *thesprite1 = new sprites2d(vertexarray1, *thetexture1);
	
	GLfloat vertexarray2[] = {
		1, -1, 10,
		-1, -1, 10,
		-1, -3, 10,
		1, -3, 10
	};
	

	vertexarray2[0] += 3;
	vertexarray2[3] += 3;
	vertexarray2[6] += 3;
	vertexarray2[9] += 3;
	sprites2d *thesprite2 = new sprites2d(vertexarray2, *thetexture1);
	
	GLfloat vertexarray3[] = {
		1, -1, 10,
		-1, -1, 10,
		-1, -3, 10,
		1, -3, 10
	};
	
	vertexarray3[0] += 3;
	vertexarray3[3] += 3;
	vertexarray3[6] += 3;
	vertexarray3[9] += 3;

	vertexarray3[2] += 5;
	vertexarray3[5] += 5;
	vertexarray3[8] += 5;
	vertexarray3[11] += 5;

	sprites2d *thesprite3 = new sprites2d(vertexarray3);

	//therenderer.submit(&thesprite);
	/*renderer2d therenderer1;
	vertexarray[0] += 3;
	vertexarray[3] += 3;
	vertexarray[6] += 3;
	vertexarray[9] += 3;
	therenderer1.submit(&thesprite);
	vertexarray[0] += 3;
	vertexarray[3] += 3;
	vertexarray[6] += 3;
	vertexarray[9] += 3;
	therenderer1.submit(&thesprite);*/
	/*GLuint thebuffer;
	glGenBuffers(1, &thebuffer);
	glBindBuffer(GL_ARRAY_BUFFER, thebuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexarray), vertexarray, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	

	GLuint index[] = {0,1,2,2,3,0};

	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

	GLuint texcoord[] = { 1, 1, 0, 1,0, 0, 1, 0 };
	GLuint texbuffer;
	glGenBuffers(1, &texbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, texbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texcoord), texcoord, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_UNSIGNED_INT, GL_FALSE, 0, 0); */

	//renderer2d therenderer;
		//therenderer.submit(vertexarray);
		//therenderer.renderall();
		//renderer2d therenderer1;
		//therenderer1.submit(vertexarray1);
		//therenderer.renderall();

		
	/*
	GLushort indexarray[] = {
	0,1,2,
	2,3,0
	};
	
	
	GLuint vertexbuffernum;
	glGenBuffers(1, &vertexbuffernum);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffernum);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexarray), vertexarray, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3,GL_FLOAT, GL_FALSE, NULL, NULL);
	
	GLuint indexbuffernum;
	glGenBuffers(1,&indexbuffernum);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffernum);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexarray),indexarray,GL_STATIC_DRAW);

	*/
		therenderer->submit(*thesprite);
		therenderer->submit(*thesprite1);
		therenderer->submit(*thesprite2);
		therenderer->submit(*thesprite3);
	

	shader *myshader=new shader("vertextrial.vert", "fragmenttrial.frag");
	myshader->enableshader();
	GLint texidshader[16];
	for (int i = 0; i < 16;i++){
		texidshader[i]=i;
	}
	glUniform1iv(glGetUniformLocation(myshader->shaderid, "textures"),16,texidshader);

	glUniformMatrix4fv(glGetUniformLocation(myshader->shaderid, "projmat"), 1, GL_TRUE, mat4::perspective(screenwidth / screenheight, 70, -1, 1000).mymatrix4x4);//mat4::orthographic(10, -10, 10, -10, 10, -10).mymatrix4x4);

	float newtime=0;
	float oldtime = 0;
	float timedelta = 0;
	float timer = 0;
	int framecount=0;
	glEnable(GL_DEPTH_TEST);
	while (mywindow.checkwindowclosed())
	{

		framecount++;
		oldtime = newtime;
		newtime = glfwGetTime();
		timedelta = newtime - oldtime;
		timer += timedelta;
		
		if (timer>=1){
			printf("fps: %d \n", framecount);
			framecount = 0;
			timer = 0;
		}

		//therenderer->createallbuffers();
		//enable shader for this batch
		//myshader->enableshader();
		//end of enable shader for this batch
		//transform all sprites
	//	mat4::transformit(mat4::rotation(timedelta*50,vec3(0,0,1)),*thesprite3);
		//end of transformation
		//submit all sprites here
		//end of all sprites submission
		//enable sprite shader
		//myshader->enableshader();
		//glUniform1iv(glGetUniformLocation(myshader->shaderid, "textures"), 16, texidshader);
		//glUniformMatrix4fv(glGetUniformLocation(myshader->shaderid, "projmat"), 1, GL_TRUE, mat4::perspective(screenwidth / screenheight, 70, -1, 1000).mymatrix4x4);//mat4::orthographic(10, -10, 10, -10, 10, -10).mymatrix4x4);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//end of enable sprite shader
		
		therenderer->renderall();
		//therenderer->deleteallbuffers();
		glfwSwapBuffers(mywindow.mywindow);
		glfwPollEvents();
	}
	return 0;
}
# else
int main(){
	const int width = 640;
	const int height = 480;
	windowmaker thewindow("trial",width,height);
	objfileloader theobj2("..\\3d objects obj\\cubetriangulate.obj");
	objfileloader theobj3("..\\3d objects obj\\newbunnytriangulate.obj");
	objfileloader theobj("..\\3d objects obj\\conetriangulate.obj");
	
	/*GLuint vertexbuffer;
	glGenBuffers(1,&vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*theobj.vertexdataindex.size(), theobj.vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, NULL, NULL);
	

	GLuint indexbuffer;
	glGenBuffers(1,&indexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*theobj.vertexdataindex.size()/3, theobj.indices, GL_STATIC_DRAW);
	*/
	
	shader theshader("3dshadervertex.vert","3dshaderfragment.frag");
	theshader.enableshader();
	glUniformMatrix4fv(glGetUniformLocation(theshader.shaderid, "projmat"), 1, GL_TRUE, mat4::perspective(640 / 480, 60, -1, 1090).mymatrix4x4);//mat4::orthographic(100, -100, 100, -100, 100, -100).mymatrix4x4);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	float oldtime=0;
	float newtime=0;
	float deltatime=0;
	float persecond=0;
	float framecount=0;
	float rotdel=0;
	while (thewindow.checkwindowclosed())
	{
		framecount++;
		oldtime = newtime;
		newtime = glfwGetTime();
		deltatime = newtime - oldtime;
		persecond += deltatime;
		if (persecond>=1){
			logit("fps " <<framecount);
			persecond = 0;
			framecount = 0;
		}
		rotdel += deltatime*60;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClearColor(1, 0,1 , 1);
		//glColor3f(1,0,0);
//glDrawElements(GL_TRIANGLES, theobj.vertexdataindex.size() / 3, GL_UNSIGNED_INT, 0);
		//logit("fine here");
		glUniformMatrix4fv(glGetUniformLocation(theshader.shaderid, "rotation"), 1, GL_TRUE, mat4::rotation(0, vec3(0, 1, 0)).mymatrix4x4);

		glUniformMatrix4fv(glGetUniformLocation(theshader.shaderid, "translation"), 1, GL_TRUE, mat4::translation(vec3(10, -10, 20)).mymatrix4x4);

		theobj2.rendermodel();
	glUniformMatrix4fv(glGetUniformLocation(theshader.shaderid, "rotation"), 1, GL_TRUE, mat4::rotation(rotdel,vec3(0,1,0)).mymatrix4x4);
		glUniformMatrix4fv(glGetUniformLocation(theshader.shaderid, "translation"), 1, GL_TRUE, mat4::translation(vec3(-2, -10, 20)).mymatrix4x4);

		theobj3.rendermodel();
		glUniformMatrix4fv(glGetUniformLocation(theshader.shaderid, "rotation"), 1, GL_TRUE, mat4::rotation(rotdel, vec3(1,0 , 0)).mymatrix4x4);

		glUniformMatrix4fv(glGetUniformLocation(theshader.shaderid, "translation"), 1, GL_TRUE, mat4::translation(vec3(-10, -10, 20)).mymatrix4x4);

		theobj.rendermodel(); 
		
			glUniformMatrix4fv(glGetUniformLocation(theshader.shaderid, "translation"), 1, GL_TRUE, mat4::translation(vec3(-2, -10, 40)).mymatrix4x4);

			theobj.rendermodel();
	
		glfwSwapBuffers(thewindow.mywindow);
		glfwPollEvents();
	}
	return 0;
}
#endif


