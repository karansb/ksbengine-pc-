#include"sprites2d.h"
namespace ksbengine{namespace coreengine{
	sprites2d::sprites2d(GLfloat *vertexarraypassed,textures &texturepassed){
		mytexture = &texturepassed;
		vertexarray = vertexarraypassed;
	}
	sprites2d::sprites2d(GLfloat *vertexarraypassed){
		vertexarray = vertexarraypassed;
		mytexture = NULL;

	}

}}