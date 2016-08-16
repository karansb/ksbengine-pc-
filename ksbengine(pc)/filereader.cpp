#define _CRT_SECURE_NO_WARNINGS
#include"filereader.h"
namespace ksbengine{
	namespace coreengine{
		filereader::filereader(char *path){
			filepath = path;
			FILE *myfile = fopen(filepath, "rb");
			fseek(myfile, 0, SEEK_END);
			filelength = ftell(myfile);
			fclose(myfile);
			

		}
		char* filereader::readfile(){
			FILE *myfile = fopen(filepath, "rb");
			insidefile = new char[filelength+1];
			memset(insidefile,0 ,filelength+1);
			fread(insidefile, 1,filelength, myfile);
			fclose(myfile);
			return insidefile;
		}
	}
}
