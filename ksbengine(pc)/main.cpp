#define _CRT_SECURE_NO_WARNINGS
#include "wtypes.h"
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
#include"camera.h"
#include"planerenderer.h"
#include<math.h>

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
void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

bool leftmousepressed=false;
bool fpressed = false;
bool leftkeypressed=false;
bool rightkeypressed=false;
bool upkeypressed = false;
bool downkeypressed = false;
bool zpressed=false;
bool xpressed = false;
bool rightmousepressed = false;
bool escapepressed = false;
int main(){
	//filereader thefile("C:\\Users\\karan\\Desktop\\mayafbxtrial.fbx");
	//logit(thefile.readfile());
	// open it
	/*FILE *fin = fopen("C:\\Users\\karan\\Desktop\\home_data_ply", "rb");
	// get size in bytes
	fseek(fin, 0, SEEK_END);
	long long size = ftell(fin);
	logit(size);
	rewind(fin);
	unsigned char* bytes = (unsigned char*)malloc(1000);
	fread(bytes,1000, 1, fin);
	for (long long i = 0; i < 1000;i++){
		printf("%c", bytes[i]);
	}*/
	//logit("\n");
	// THAT'S ALL FOLKS!
	/*FILE *thefilefbx=fopen("C:\\Users\\karan\\Desktop\\mayafbxtrial.fbx", "rb+");
	fseek(thefilefbx, 0, SEEK_END);
	int filelen = ftell(thefilefbx);
	fseek(thefilefbx, 0, SEEK_SET);
	char *f=new char[filelen+1];
	memset(f, 0, filelen+1);
	fread(f, 1, filelen, thefilefbx);
	logit(f);*/

	int horizontal = 0;
	int vertical = 0;
	GetDesktopResolution(horizontal, vertical);
	


	const int width = 640;
	const int height = 480;
	windowmaker thewindow("trial",horizontal,vertical);
	glfwSetKeyCallback(thewindow.mywindow, key_callback);
	glfwSetMouseButtonCallback(thewindow.mywindow, mouse_button_callback);

	objfileloader theobj("..\\3d objects obj\\rabbidsproper.obj");
	

	camera thecam(vec3(0, 0, 0), vec3(0, 0, 0));
	shader mynewshader("planeshadervertex.vert", "planeshaderfragment.frag");
	planerenderer theplane(vec3(-1, 1, 1), vec3(-1, 1, -1), vec3(1, 0, -1), vec3(1, 0, 1),mynewshader, &thecam);
	planerenderer theplane1(vec3(-4, 0, 1), vec3(-4, -1, -1), vec3(-2, -1, -1), vec3(-2, 0, 1), mynewshader, &thecam);

	vec3 planenormal = (vec3(-1, 1, -1) - vec3(-1, 1, 1)).cross(vec3(1, 0, 1) - vec3(-1, 1, 1));
	planenormal.normalize();
	planenormal.x = -planenormal.x;
	planenormal.y = -planenormal.y;
	planenormal.z = -planenormal.z;
	logit(planenormal.stringify());

	//planenormal.normalize();
	float rotanglex = (planenormal.dot(vec3(0, 1, 0))) / (planenormal.getlength()*vec3(0, 1, 0).getlength());//((vec3(-1, 1, -1) - vec3(-1, 0, 1)).dot((vec3(1, 0, 1) - vec3(-1, 0, 1)))) / (vec3(-1, 1, -1) - vec3(-1, 0, 1)).getlength()*(vec3(1, 0, 1) - vec3(-1, 0, 1)).getlength();
	rotanglex = acos(rotanglex);
	rotanglex = rotanglex * 180 / 3.14159;//-152.97;//acos(rotanglex);
	rotanglex = rotanglex;
	logit(rotanglex);

	vec3 rotaxis = planenormal.cross(vec3(0,1,0));
	rotaxis.normalize();
	logit(rotaxis.stringify());

	if (rotanglex==0){
		rotaxis.x = 1;
		rotaxis.y = 0;
		rotaxis.z = 0;
	}

	vec3 planemidpoint((theplane.points[0] + theplane.points[3] + theplane.points[6] + theplane.points[9]) / 4, (theplane.points[1] + theplane.points[4] + theplane.points[7] + theplane.points[10]) / 4, (theplane.points[2] + theplane.points[5] + theplane.points[8] + theplane.points[11]) / 4);
	/*float r = sqrt(planenormal.x*planenormal.x + planenormal.y*planenormal.y + planenormal.z*planenormal.z);
	float t = atan(planenormal.y / planenormal.x);
	float p = acos(planenormal.z / r);

	float rotanglex = r * sin(p) * cos(t);
	logit(rotanglex);
	float rotangley = r * sin(p) * sin(t);
	float rotanglez = r * cos(p);*/


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
	GLfloat gridpoints[] = {
		-10,0,0,
		10,0,0,
		0,0,10,
		0,0,-10,
		2,0,10,
		2,0,-10,
		-2, 0, 10,
		-2, 0, -10,
		- 4, 0, 10,
		-4, 0, -10,
		4, 0, 10,
		4, 0, -10,
		6, 0, 10,
		6, 0, -10,
		8, 0, 10,
		8, 0, -10,
		-6, 0, 10,
		-6, 0, -10,
		-8, 0, 10,
		-8, 0, -10,
		-10,0,-2,
		10,0,-2,
		-10, 0, -4,
		10, 0, -4,
		-10, 0, -6,
		10, 0, -6,
		-10, 0, -8,
		10, 0, -8,
		-10, 0, 2,
		10, 0, 2,
		-10, 0, 4,
		10, 0, 4,
		-10, 0, 6,
		10, 0, 6,
		-10, 0, 8,
		10, 0, 8
	};
	GLuint gridbuffer;
	glGenBuffers(1, &gridbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, gridbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(gridpoints), gridpoints, GL_STATIC_DRAW);
	
	


	
	shader theshader("3dshadervertex.vert","3dshaderfragment.frag");
	theshader.enableshader();
	shader gridshader("gridshadervertex.vert","gridshaderfragment.frag");
	glUniformMatrix4fv(glGetUniformLocation(theshader.shaderid, "projmat"), 1, GL_TRUE, mat4::perspective(640 / 480, 60, -1, 1000).mymatrix4x4);//mat4::orthographic(100, -100, 100, -100, 100, -100).mymatrix4x4);
	gridshader.enableshader();
	glUniformMatrix4fv(glGetUniformLocation(gridshader.shaderid, "projmat"), 1, GL_TRUE, mat4::perspective(640 / 480, 60, -1, 1000).mymatrix4x4);//mat4::orthographic(100, -100, 100, -100, 100, -100).mymatrix4x4);
	
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);

	float oldtime=0;
	float newtime=0;
	float deltatime=0;
	float persecond=0;
	float framecount=0;
	float rotdel=0;

	horizontal /= 2;
	vertical /= 2;
	float camrotx=0;
	float camroty = 0;
	float mlrotx=0;
	float mlroty = 0;
	float distance = 30;
	float leftcamoffset = -10;
	float upcamoffset=0;
	while (thewindow.checkwindowclosed())
	{
		if (camrotx>=360){
			camrotx = 0;
		}
		if (camroty>=360){
			camroty = 0;

		}
		if (fpressed){
			camrotx = 0;
			camroty = 0;
			mlrotx = 0;
			mlroty = 0;
		leftcamoffset = -10;;
			upcamoffset = 0;
			distance = 30;
		}
		//mouse input
		double xpos, ypos;
		glfwSetInputMode(thewindow.mywindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		glfwGetCursorPos(thewindow.mywindow, &xpos, &ypos);
		if (leftmousepressed){
			camroty += deltatime*(horizontal - xpos) * 100;
			camrotx += deltatime*(vertical - ypos) * 100;
		}
		if (leftkeypressed){
			mlroty += deltatime * 40;
		}
		else if (rightkeypressed){
			mlroty -= deltatime * 40;

		}
		if (upkeypressed){
			mlrotx += deltatime * 40;
		}
		else if (downkeypressed){
			mlrotx -= deltatime * 40;

		}
		if (zpressed){
			distance -= deltatime * 5;
		}
		else if (xpressed){
			distance += deltatime * 5;

		}
		if (rightmousepressed){
			upcamoffset += deltatime*(horizontal - xpos) * 10;
			leftcamoffset += deltatime*(vertical - ypos) * 10;
		}
		 if (escapepressed){
			 glfwSetWindowShouldClose(thewindow.mywindow, true);
		}
		
		
		glfwSetCursorPos(thewindow.mywindow,horizontal,vertical);
		//logit("mouse x " << xpos<<" mouse y "<<ypos);

		//end mouse input

		framecount++;
		oldtime = newtime;
		newtime = glfwGetTime();
		deltatime = newtime - oldtime;
		persecond += deltatime;
		if (persecond>=1){
		//	logit("fps " <<framecount);
			persecond = 0;
			framecount = 0;
		}
		rotdel += deltatime*60;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//logit(rightaxis.stringify());
		

		theshader.enableshader();
		glUniformMatrix4fv(glGetUniformLocation(theshader.shaderid, "cam_translation"), 1, GL_TRUE, mat4::translation(vec3(-upcamoffset, leftcamoffset, distance)).mymatrix4x4);
	
		//glUniformMatrix4fv(glGetUniformLocation(theshader.shaderid, "cam_rotationx"), 1, GL_TRUE, mat4::rotation(camrotx, vec3(1, 0, 0)).mymatrix4x4);//mul(mat4::rotation(camroty,vec3(0,1,0))).mymatrix4x4);
		//glUniformMatrix4fv(glGetUniformLocation(theshader.shaderid, "cam_rotationy"), 1, GL_TRUE, mat4::rotation(camroty, vec3(0, 1, 0)).mymatrix4x4);//mul(mat4::rotation(camroty,vec3(0,1,0))).mymatrix4x4);

		//glClearColor(1, 0,1 , 1);
		//glColor3f(1,0,0);
		//glDrawElements(GL_TRIANGLES, theobj.vertexdataindex.size() / 3, GL_UNSIGNED_INT, 0);
		//logit("fine here");
		//glUniformMatrix4fv(glGetUniformLocation(theshader.shaderid, "ml_rotationy"), 1, GL_TRUE, mat4::rotation(camroty, vec3(0, 1, 0)).mymatrix4x4);//mul(mat4::rotation(camroty,vec3(0,1,0))).mymatrix4x4);
		glUniformMatrix4fv(glGetUniformLocation(theshader.shaderid, "cam_rotation"), 1, GL_TRUE, mat4::rotation(camroty, vec3(0, 1, 0)).mul(mat4::rotation(camrotx,vec3(1,0,0))).mymatrix4x4);//mul(mat4::rotation(camroty,vec3(0,1,0))).mymatrix4x4);
		glUniformMatrix4fv(glGetUniformLocation(theshader.shaderid, "ml_rotation"), 1, GL_TRUE, mat4::rotation(-rotanglex, rotaxis).mymatrix4x4);// mat4::rotation(mlroty, vec3(0, 1, 0)).mul(mat4::rotation(rotanglex, vec3(1, 0, 0))).mymatrix4x4);//mul(mat4::rotation(camroty,vec3(0,1,0))).mymatrix4x4);

		glUniformMatrix4fv(glGetUniformLocation(theshader.shaderid, "ml_translation"), 1, GL_TRUE, mat4::translation((vec3(planenormal.x, planenormal.y, planenormal.z)*11.57)+planemidpoint).mymatrix4x4);
		glUniformMatrix4fv(glGetUniformLocation(theshader.shaderid, "ml_scale"), 1, GL_TRUE, mat4::scaling(vec3(5, 5, 5)).mymatrix4x4);

		theobj.rendermodel();
		theshader.disableshader();
		//theshader.disableshader();
		gridshader.enableshader();
		glBindBuffer(GL_ARRAY_BUFFER,gridbuffer);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, NULL, NULL);
		//glColor3f(1, 0, 0);
		glUniformMatrix4fv(glGetUniformLocation(gridshader.shaderid, "cam_translation"), 1, GL_TRUE, mat4::translation(vec3(-upcamoffset, leftcamoffset, distance)).mymatrix4x4);
		//glUniformMatrix4fv(glGetUniformLocation(theshader.shaderid, "cam_rotationx"), 1, GL_TRUE, mat4::rotation(camrotx, vec3(1, 0, 0)).mymatrix4x4);//mul(mat4::rotation(camroty,vec3(0,1,0))).mymatrix4x4);
		//glUniformMatrix4fv(glGetUniformLocation(theshader.shaderid, "cam_rotationy"), 1, GL_TRUE, mat4::rotation(camroty, vec3(0, 1, 0)).mymatrix4x4);//mul(mat4::rotation(camroty,vec3(0,1,0))).mymatrix4x4);

		//glClearColor(1, 0,1 , 1);
		//glColor3f(1,0,0);
		//glDrawElements(GL_TRIANGLES, theobj.vertexdataindex.size() / 3, GL_UNSIGNED_INT, 0);
		//logit("fine here");
		//glUniformMatrix4fv(glGetUniformLocation(theshader.shaderid, "ml_rotationy"), 1, GL_TRUE, mat4::rotation(camroty, vec3(0, 1, 0)).mymatrix4x4);//mul(mat4::rotation(camroty,vec3(0,1,0))).mymatrix4x4);
		glUniformMatrix4fv(glGetUniformLocation(gridshader.shaderid, "cam_rotation"), 1, GL_TRUE, mat4::rotation(camroty, vec3(0, 1, 0)).mul(mat4::rotation(camrotx, vec3(1, 0, 0))).mymatrix4x4);//mul(mat4::rotation(camroty,vec3(0,1,0))).mymatrix4x4);
		//glUniformMatrix4fv(glGetUniformLocation(gridshader.shaderid, "ml_rotation"), 1, GL_TRUE, mat4::rotation(mlroty, vec3(0, 1, 0)).mul(mat4::rotation(mlrotx, vec3(1, 0, 0))).mymatrix4x4);//mul(mat4::rotation(camroty,vec3(0,1,0))).mymatrix4x4);

		glUniformMatrix4fv(glGetUniformLocation(gridshader.shaderid, "ml_translation"), 1, GL_TRUE, mat4::translation(vec3(0, 0, 0)).mymatrix4x4);
		glUniformMatrix4fv(glGetUniformLocation(gridshader.shaderid, "ml_scale"), 1, GL_TRUE, mat4::scaling(vec3(1, 1, 1)).mymatrix4x4);
		
		glDrawArrays(GL_LINES,0,36);

		thecam.updatecamera(vec3(camrotx, camroty, 0),vec3(-upcamoffset,leftcamoffset,distance));
		theplane.renderplane();
		theplane1.renderplane();

		glfwSwapBuffers(thewindow.mywindow);
		glfwPollEvents();
	}
	return 0;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_F && action == GLFW_PRESS){
		fpressed = true;
	}
	else if (key == GLFW_KEY_F && action == GLFW_RELEASE){
		fpressed = false;
	}
	if (key == GLFW_KEY_LEFT&& action == GLFW_PRESS){
		leftkeypressed = true;
	}
	else if (key == GLFW_KEY_LEFT&& action == GLFW_RELEASE){
		leftkeypressed = false;
	}
	if (key == GLFW_KEY_RIGHT&& action == GLFW_PRESS){
		rightkeypressed = true;
	}
	else if (key == GLFW_KEY_RIGHT&& action == GLFW_RELEASE){
		rightkeypressed = false;
	}
	if (key == GLFW_KEY_UP&& action == GLFW_PRESS){
		upkeypressed = true;
	}
	else if (key == GLFW_KEY_UP&& action == GLFW_RELEASE){
		upkeypressed = false;
	}
	if (key == GLFW_KEY_DOWN&& action == GLFW_PRESS){
		downkeypressed = true;
	}
	else if (key == GLFW_KEY_DOWN&& action == GLFW_RELEASE){
		downkeypressed = false;
	}
	if (key == GLFW_KEY_Z&& action == GLFW_PRESS){
		zpressed = true;
	}
	else if (key == GLFW_KEY_Z && action == GLFW_RELEASE){
		zpressed = false;
	}
	if (key == GLFW_KEY_X && action == GLFW_PRESS){
		xpressed = true;
	}
	else if (key == GLFW_KEY_X && action == GLFW_RELEASE){
		xpressed = false;
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		escapepressed = true;
	}
	else if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE){
		escapepressed = false;
	}
	


}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		leftmousepressed = true;
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		leftmousepressed = false;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		rightmousepressed = true;
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
		rightmousepressed = false;
}

#endif


