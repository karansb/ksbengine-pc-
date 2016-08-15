#pragma once
#include<iostream>
namespace ksbengine{namespace coreengine{
		class filereader{
		private:
			char *filepath;
			char *insidefile;
		public:
			int filelength;
			filereader(char*);
			char* readfile();
			inline ~filereader(){ delete[] insidefile;  std::cout << "file memory freed" << std::endl; };
		};
}}