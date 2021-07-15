// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Texture.h"
#include "Globals.h"
#include "Model.h"
#include "Object.h"
#include <conio.h>
#include <iostream>

Object obj;

int Init ( ESContext *esContext )
{	
	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );
	glEnable(GL_DEPTH_TEST);
	obj.SetPosition(-0.4f, -0.8f, 0.0f);
	obj.SetScale(0.5f, 0.8f, 0.5f);
	obj.SetRotation(0.0f, 200.0f, 0.0f);
	obj.Init("..\\Resources\\Woman2.tga", "..\\Resources\\Woman2.nfg");
	return 0;

}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	obj.Draw();
	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{

}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{

}

void CleanUp()
{
	obj.CleanUp();
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

