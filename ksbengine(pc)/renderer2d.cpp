#include "renderer2d.h"
namespace ksbengine{namespace coreengine{
	renderer2d::renderer2d(){
		glGenBuffers(1, &vertexarraybuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexarraybuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * 4 * max_sprite,NULL,GL_DYNAMIC_DRAW);
		glGenBuffers(1, &indexbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*6*max_sprite, NULL, GL_DYNAMIC_DRAW);
		glGenBuffers(1, &texcoordbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, texcoordbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint) * 2 * 4 * max_sprite, NULL, GL_DYNAMIC_DRAW);
		
		glGenBuffers(1, &texidbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, texidbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 1 * 4 * max_sprite, NULL, GL_DYNAMIC_DRAW);
		spritecount = 0;
		glBindBuffer(GL_ARRAY_BUFFER,0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void renderer2d::bindbuffer(){
		glBindBuffer(GL_ARRAY_BUFFER, vertexarraybuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	}
	void renderer2d::unbindbuffer(){
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void renderer2d::submit(sprites2d &thesprite){
		bindbuffer();
		if (spritecount<max_sprite){
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * 4 * spritecount, sizeof(GLfloat) * 3 * 4, thesprite.vertexarray);
			
			//glEnableVertexAttribArray(0);//vertex position index in shader
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, NULL, NULL);

			GLuint index[6] = { 0 + 4 * spritecount, 1 + 4 * spritecount, 2 + 4 * spritecount, 2 + 4 * spritecount, 3 + 4 * spritecount, 0 + 4 * spritecount };
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6 * spritecount, sizeof(GLuint) * 6, index);
			
			if (thesprite.mytexture!=NULL&&texturecount<max_texture){
				GLuint texcoordinate[] = { 1, 1, 0, 1, 0, 0, 1, 0 };
				glBindBuffer(GL_ARRAY_BUFFER, texcoordbuffer);
				glBufferSubData(GL_ARRAY_BUFFER, sizeof(texcoordinate)*spritecount, sizeof(texcoordinate), texcoordinate);
			
				//check if texture already exists
				GLint indexoftexture;
				bool texturefound = false;
				for (int i = 0; i < textureptrarray.size();i++){
					if (thesprite.mytexture->textureid==textureptrarray[i]->textureid){
						texturefound = true;
						indexoftexture = i;
						break;
					}
				}
				if (!texturefound){
					GLfloat texids[] = { 0 + texturecount, 0 + texturecount, 0 + texturecount, 0 + texturecount };
					glBindBuffer(GL_ARRAY_BUFFER, texidbuffer);
					glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 1 * 4 * spritecount, sizeof(texids), texids);

					textureptrarray.push_back(thesprite.mytexture);
					texturecount++;
				}
				else{
				std::cout << "in here" << std::endl;
					GLfloat texids[] = { indexoftexture, indexoftexture, indexoftexture, indexoftexture };
					glBindBuffer(GL_ARRAY_BUFFER, texidbuffer);
					glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 1 * 4 * spritecount, sizeof(texids), texids);
				}
			}
			else{

				GLfloat texids[] = {-1,-1,-1,-1 };
				glBindBuffer(GL_ARRAY_BUFFER, texidbuffer);
				glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 1 * 4 * spritecount, sizeof(texids), texids);

			}
			spritecount++;
		}
		unbindbuffer();
		
		}
	void renderer2d::renderall(){
		for (int i = 0; i < textureptrarray.size();i++){
			glActiveTexture(GL_TEXTURE0+i);
			textureptrarray[i]->bindtexture();
		}
		bindbuffer();
		glEnableVertexAttribArray(0);//vertex position index in shader
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, NULL, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, texcoordbuffer);
		glEnableVertexAttribArray(1);//vertex position index in shader
		glVertexAttribPointer(1, 2, GL_UNSIGNED_INT, GL_FALSE, NULL, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, texidbuffer);
		glEnableVertexAttribArray(2);//vertex position index in shader
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, NULL, NULL);

		glDrawElements(GL_TRIANGLES, 6*spritecount, GL_UNSIGNED_INT, 0);

		unbindbuffer();
	}
	renderer2d::~renderer2d(){
		glBindBuffer(GL_ARRAY_BUFFER,0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
		glDeleteBuffers(1, &vertexarraybuffer);
		glDeleteBuffers(1, &indexbuffer);
	}

}}