#pragma once
#include"filereader.h"
#include<iostream>
#define GLEW_STATIC
#include<glew.h>
#include<glfw3.h>
#include<string>
#include<vector>
namespace ksbengine{ namespace coreengine{
class objfileloader{
private:
	std::vector<GLfloat>verticesdata;
	std::vector<GLfloat>texcoordsdata;
	std::vector<GLfloat> normalsdata;
	std::vector<GLuint> vertexdataindex;
	GLfloat *vertices;
	GLfloat *normals;
	GLfloat *texcoord;
	GLuint *indices;
	int vertexdataindexsize;
private:
	GLuint vertexbuffer;
	GLuint normalbuffer;
	GLuint indexbuffer;
public:
	objfileloader(char *filepath);
private:
	void createbuffer();
	void bindbuffer();
	void unbindbuffer();
public:
	void rendermodel();
	~objfileloader();
};
}}