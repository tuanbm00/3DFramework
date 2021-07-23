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
#include "Camera.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include <conio.h>
#include <iostream>

//Object obj1, obj2, skyBox;

int Init ( ESContext *esContext )
{	
	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	SceneManager::GetInstance()->Init();
	ResourceManager::GetInstance()->Init();
	return 0;
}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	skyBox.Draw();	
//	obj1.Draw();
//	obj2.Draw();
	SceneManager::GetInstance()->Draw();
	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	SceneManager::GetInstance()->Update(deltaTime);
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	SceneManager::GetInstance()->MoveCamera(key, bIsPressed);
}

void CleanUp()
{
	SceneManager::GetInstance()->CleanUP();
	ResourceManager::GetInstance()->CleanUp();
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

	SceneManager::GetInstance()->MemoryClear();
	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

