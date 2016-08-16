#include"objfileloader.h"
namespace ksbengine{namespace coreengine{
	objfileloader::objfileloader(char *filepath){
		filereader thefile(filepath);
		char *inthefile;
		float beforetime = glfwGetTime();
		inthefile = thefile.readfile();
		std::cout << "file read in " << glfwGetTime() - beforetime << " s" << std::endl;
		
		for (int i = 0; inthefile[i] != '\0';i++){
			//check for texcoords line
			if (inthefile[i]=='\n'&&inthefile[i+1]=='v'&&inthefile[i+2]=='t'){
				int numcount=0;
				char thenum[20];
				int j = 0;
				for (j = i + 3; inthefile[j] != '\n';j++){
					if (inthefile[j]==' '){
						if (numcount!=0){
							thenum[numcount] = '\0';
							texcoordsdata.push_back(std::stof(thenum));
							numcount = 0;
						}
					}
					else{
						thenum[numcount] = inthefile[j];
						numcount++;
					}
				}
				thenum[numcount] = '\0';
				texcoordsdata.push_back(std::stof(thenum));
				numcount = 0;
				i = j - 1;
			}
			//end of texcoords line
			//check normals line
			else if (inthefile[i]=='\n'&&inthefile[i+1]=='v'&&inthefile[i+2]=='n'){
				int j = 0;
				int numcount=0;
				char thenum[20];
				for (j = i + 3; inthefile[j] != '\n'; j++){
					if (inthefile[j]==' '){
						if (numcount!=0){
							thenum[numcount] = 0;
							normalsdata.push_back(std::stof(thenum));
							numcount = 0;
						}
					}
					else{
						thenum[numcount] = inthefile[j];
						numcount++;
					}
				}
				thenum[numcount] = 0;
				normalsdata.push_back(std::stof(thenum));
				numcount = 0;
				i = j - 1;
			}
			//end of normals line
			//start of vertices line
			else if (inthefile[i]=='\n'&&inthefile[i+1]=='v'){
				int j = 0;
				int numcount = 0;
				char thenum[20];
				for (j = i + 2; inthefile[j] != '\n';j++){
					if (inthefile[j]==' '){
						if (numcount!=0){
							thenum[numcount] = '\0';
							verticesdata.push_back(std::stof(thenum));
							numcount = 0;
						}
					}
					else{
						thenum[numcount] = inthefile[j];
						numcount++;
					}
				}
				thenum[numcount] = '\0';
				verticesdata.push_back(std::stof(thenum));
				numcount = 0;
				i = j - 1;
			}
			//end of vertices line
			//check vertexdataindex line
			else if(inthefile[i]=='\n'&&inthefile[i+1]=='f'){
				int j = 0;
				int numcount = 0;
				char thenum[20];
				for (j = i + 2; inthefile[j] != '\n';j++){
					if (inthefile[j]==' '||inthefile[j]=='/'){
						if (inthefile[j-1]=='/'){
							vertexdataindex.push_back(0);
							numcount = 0;
						}
						else if (numcount!=0){
							thenum[numcount] = '\0';
							vertexdataindex.push_back(std::stof(thenum));
							numcount = 0;
						}
					}
					else{
						thenum[numcount] = inthefile[j];
						numcount++;
					}
				}
				thenum[numcount] = '\0';
				vertexdataindex.push_back(std::stof(thenum));
				numcount = 0;
				i = j - 1;
			}
			//end of vertexdataindex line
		}


		std::cout << normalsdata.size() / 3 << " normals" << std::endl;
		std::cout << verticesdata.size()/3  << " vertices" << std::endl;

		std::cout << vertexdataindex.size() / 3 / 3 << " triangles"<<std::endl;
		//vertexindexfilled;
		std::cout << "object loaded in " << glfwGetTime() - beforetime <<" s"<< std::endl;

		vertices = new GLfloat[vertexdataindex.size()];
		normals = new GLfloat[vertexdataindex.size()];
		indices = new GLuint[vertexdataindex.size()/3];

		unsigned int indexcount=0;
		unsigned int normalcount = 0;
		unsigned int vertexcount = 0;
		
		for (unsigned int i = 0; i < vertexdataindex.size(); i += 3){
			indices[indexcount] = indexcount;
			indexcount++;

			vertices[vertexcount] = verticesdata[3*(vertexdataindex[i] - 1)+0];
			vertexcount++;
			vertices[vertexcount] = verticesdata[3*(vertexdataindex[i]-1)+1];
			vertexcount++;
			vertices[vertexcount] = verticesdata[3*(vertexdataindex[i]-1) + 2];
			vertexcount++;

			normals[normalcount] = normalsdata[3*(vertexdataindex[i + 2] - 1)+0];
			normalcount++;
			normals[normalcount] = normalsdata[3*(vertexdataindex[i + 2]-1)+1];
			normalcount++;
			normals[normalcount] = normalsdata[3*(vertexdataindex[i + 2]-1) + 2];
			normalcount++;

			
		}
		vertexdataindexsize = vertexdataindex.size();
		printf("index count %d\nobject loaded\n",indexcount);
		//clear all read data
		verticesdata.clear();
		texcoordsdata.clear();
		normalsdata.clear();
		vertexdataindex.clear();
		
		createbuffer();
		
	}
	void objfileloader::createbuffer(){
		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*vertexdataindexsize, vertices, GL_STATIC_DRAW);

		glGenBuffers(1,&normalbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*vertexdataindexsize, normals, GL_STATIC_DRAW);

		glGenBuffers(1,&indexbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexbuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*vertexdataindexsize / 3, indices, GL_STATIC_DRAW);
	}
	void objfileloader::bindbuffer(){
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	}
	void objfileloader::unbindbuffer(){
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	void objfileloader::rendermodel(){
		bindbuffer();
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, NULL, NULL);
		glBindBuffer(GL_ARRAY_BUFFER,normalbuffer);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, NULL, NULL);
		glDrawElements(GL_TRIANGLES,vertexdataindexsize / 3, GL_UNSIGNED_INT, 0);
		unbindbuffer();
		
	}
}}