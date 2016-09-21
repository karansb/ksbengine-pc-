#include"windowmaker.h"
namespace ksbengine{
	namespace coreengine{
		void resizewindow(GLFWwindow*, int, int);


		windowmaker::windowmaker(const char *thegamename, int thewindowwidth, int thewindowheight){
			gamename = thegamename;
			windowwidth = thewindowwidth;
			windowheight = thewindowheight;
			windowinit();
		}
		void windowmaker::windowinit(){
			if (glfwInit()){
				mywindow = glfwCreateWindow(windowwidth, windowheight, gamename, NULL, NULL);

				glfwMakeContextCurrent(mywindow);
				if (glewInit() != GLEW_OK){
					std::cout << "glew failed" << std::endl;
				}

				glfwSetWindowSizeCallback(mywindow, resizewindow);
			}
			else{
				std::cout << "glfw failed" << std::endl;
			}
		}
		bool windowmaker::checkwindowclosed(){
			return !glfwWindowShouldClose(mywindow);
		}

		void resizewindow(GLFWwindow *window, int width, int height){
			glViewport(0, 0, width, height);
		}
		

		windowmaker::~windowmaker(){
			glfwTerminate();
			
		}
	}
}
