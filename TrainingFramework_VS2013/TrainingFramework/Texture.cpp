#include <stdafx.h>

#include "Texture.h"

//Texture* Texture::s_Instance = NULL;

Texture::Texture() {

}

Texture::~Texture() {
	
}

void Texture::Init(char *filename) {
	int width = 0;
	int height = 0;
	int bpp = 0;

	char *imageData = LoadTGA(filename, &width, &height, &bpp);

	//load the image data into OpenGL ES texture resource
	if (bpp == 24) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	}

	// free the client memory
	delete[] imageData;

	//set the filters for minification and magnification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// generate the mipmap chain
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

//Texture* Texture::GetInstance() {
//	if (!s_Instance)
//		s_Instance = new Texture();
//	return s_Instance;
//}