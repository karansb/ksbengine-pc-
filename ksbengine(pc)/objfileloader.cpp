#include"objfileloader.h"
namespace ksbengine{namespace coreengine{
	objfileloader::objfileloader(char *filepath){
		filereader thefile(filepath);
		char *inthefile;
		float beforetime = glfwGetTime();
		inthefile = thefile.readfile();
		std::cout << "file read in " << glfwGetTime() - beforetime << " s" << std::endl;
		int i = 0;
		int printcounter;
		for (i = 0; inthefile[i] != '\0'; i++){
			if (inthefile[i] == 'v'&&inthefile[i + 1] != ' '){
				break;
			}
			if (inthefile[i] == 'v'&&inthefile[i + 1] == ' '){
				char thenum[20];
				int countnum = 0;
				int j = 0;
				for (j = i + 1; inthefile[j] != 'v'; j++){
					if (inthefile[j] == ' '){
						if (countnum != 0){
							thenum[countnum] = '\0';
							verticesdata.push_back((GLfloat)std::stof(thenum));
						}
						countnum = 0;
						continue;
					}
					else{
						thenum[countnum] = inthefile[j];
						countnum++;
					}
				}
				thenum[countnum] = '\0';
				verticesdata.push_back(std::stof(thenum));
				i = j-1;
			}
		}
		
		//filled vertex array
		for (i; inthefile[i] != '\0'; i++){
			if (inthefile[i] == 'v'&&inthefile[i + 1] != 't'){
				break;
			}
			if (inthefile[i] == 'v'&&inthefile[i + 1] == 't'&&inthefile[i + 2] == ' '){
				char thenum[20];
				int thecount = 0;
				int j = 0;
				for (j = i + 2; inthefile[j] != 'v'; j++){
					if (inthefile[j] == ' '){
						if (thecount != 0){
							thenum[thecount] = '\0';
							texcoordsdata.push_back(std::stof(thenum));
						}
						thecount = 0;
						continue;
					}
					else{
						thenum[thecount] = inthefile[j];
						thecount++;
					}
				}
				thenum[thecount] = '\0';
				texcoordsdata.push_back(std::stof(thenum));
				i = j-1;
			}
		}
		
		//texcoords array filled
		for (i; inthefile[i] != '\0'; i++){
			if (inthefile[i] == 's'){
				break;
			}
			if (inthefile[i] == 'v'&&inthefile[i + 1] == 'n'&&inthefile[i + 2] == ' '){
				int thecount = 0;
				char thenum[20];
				int j = 0;
				for (j = i + 2; inthefile[j] != 'v' && inthefile[j] != 's'; j++){
					if (inthefile[j] == ' '){
						if (thecount != 0){
							thenum[thecount] = '\0';
							normalsdata.push_back(std::stof(thenum));
						}
						thecount = 0;
						continue;
					}
					else{
						thenum[thecount] = inthefile[j];
						thecount++;
					}
				}
				thenum[thecount] = '\0';
				normalsdata.push_back(std::stof(thenum));
				i = j-1;
			}
		}
		
		//normals array filled
		for (i; inthefile[i] != '\0'; i++){
			if (inthefile[i] == 'f'&&inthefile[i + 1] == ' '){
				char thenum[20];
				int numcount = 0;
				int j = 0;
				for (j = i + 1; inthefile[j] != 'f' && inthefile[j] != '\0'&&inthefile[j]!='s'; j++){
					if (inthefile[j] == ' ' || inthefile[j] == '/'){
						//special check for no texcoord
						if (inthefile[j]=='/'&&inthefile[j-1]=='/'){
							vertexdataindex.push_back(0);
						}
						//end of special check
						if (numcount != 0){
							thenum[numcount] = '\0';
							vertexdataindex.push_back(std::stof(thenum));
						}
						numcount = 0;
						continue;
					}
					else{
						thenum[numcount] = inthefile[j];
						numcount++;
					}
				}
				thenum[numcount] = '\0';
				vertexdataindex.push_back(std::stof(thenum));
				i = j-1;
			}
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