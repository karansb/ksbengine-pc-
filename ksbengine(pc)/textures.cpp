#include"textures.h"
namespace ksbengine{namespace coreengine{
	textures::textures(const char *imagepath){
		imgpath = imagepath;
		glGenTextures(1, &textureid);
		//load image using freeimg
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *dib(0);
		unsigned int width(0), height(0);
		fif = FreeImage_GetFileType(imgpath, 0);
		if (fif == FIF_UNKNOWN){
			fif = FreeImage_GetFIFFromFilename(imgpath);
		}
		if (FreeImage_FIFSupportsReading(fif)){
			dib = FreeImage_Load(fif, imgpath);
		}
		unsigned char *bits;
		bits = FreeImage_GetBits(dib);
		width = FreeImage_GetWidth(dib);
		height = FreeImage_GetHeight(dib);
		unsigned char *pixel;
		pixel = (unsigned char*)bits;
		//end of image loading
		glBindTexture(GL_TEXTURE_2D, textureid);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_BGRA,GL_UNSIGNED_BYTE,pixel);
		glBindTexture(GL_TEXTURE_2D, 0);
		FreeImage_Unload(dib);
	}
	void textures::bindtexture(){
		glBindTexture(GL_TEXTURE_2D, textureid);
	}
	void textures::unbindtexture(){
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	textures::~textures(){
		unbindtexture();
		glDeleteTextures(1, &textureid);
		
	}
}}