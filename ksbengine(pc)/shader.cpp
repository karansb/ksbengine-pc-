#include"shader.h"
namespace ksbengine{
	namespace coreengine{
		shader::shader(char *vertpath, char *fragpath){
			filereader vertfile(vertpath);
			filereader fragfile(fragpath);
			shaderid = glCreateProgram();
			GLuint vertexprogram = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragprogram = glCreateShader(GL_FRAGMENT_SHADER);
			char *vert = vertfile.readfile();
			char *frag = fragfile.readfile();
			glShaderSource(vertexprogram, 1, &vert, NULL);
			glShaderSource(fragprogram, 1, &frag, NULL);
			glCompileShader(vertexprogram);
			GLint vertexcompileresult;
			glGetShaderiv(vertexprogram,GL_COMPILE_STATUS,&vertexcompileresult);
			if (vertexcompileresult==false){
				std::cout << "vertex compile failed"<<std::endl;
			}
			glCompileShader(fragprogram);
			GLint fragcompileresult;
			glGetShaderiv(fragprogram, GL_COMPILE_STATUS, &fragcompileresult);
			if (fragcompileresult==false){
				std::cout << "fragment compile failed"<<std::endl;
			}
			glAttachShader(shaderid, vertexprogram);
			glAttachShader(shaderid, fragprogram);
			glLinkProgram(shaderid);
			glValidateProgram(shaderid);
			glDeleteShader(vertexprogram);
			glDeleteShader(fragprogram);
			
		}
	}
}
