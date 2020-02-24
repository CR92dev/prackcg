#include "Include/freeglut.h"
#include "SOIL.h"
#include <iostream>
#include "Include/glext.h"


GLuint createTexture(const char* imgname, GLenum type = GL_TEXTURE_2D) {
	int w, h;
	GLuint tex;
	unsigned char* image = SOIL_load_image(imgname, &w, &h, NULL, SOIL_LOAD_RGBA);

	glGenTextures(1, &tex);
	glBindTexture(type, tex);

	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT); // Repeat s(x) coordinate
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT); // Repeat t(y) coordinate - evtl ist s auch y und t x - egal erstmal


	if (image)
	{
		glTexImage2D(type, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		//glGenerateMipMap(type); Die methode gibt es anscheinend nicht mehr???
	}
	else
	{
		std::cout << "ERROR while loading: " << imgname << std::endl;
	}

	//glActiveTexture(0);  Die methode gibt es anscheinend nicht mehr???
	glBindTexture(type, 0);
	SOIL_free_image_data(image);

	return tex;
}