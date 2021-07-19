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
	SceneManager::GetInstance()->Init();
	ResourceManager::GetInstance()->Init();
	/*Camera::GetInstance()->Init(1.0f, 0.1f, 500.0f);
	Camera::GetInstance()->SetPosition(0.0f, 1.0f, 5.0f);
	Camera::GetInstance()->SetTarget(0.0f, 1.0f, -1.0f);
	Camera::GetInstance()->SetUp(0.0f, 1.0f, 0.0f);

	obj1.SetPosition(-0.4f, -0.8f, 0.0f);
	obj1.SetScale(0.5f, 0.8f, 0.5f);
	obj1.SetRotation(0.0f, 100.0f, 0.0f);
	obj1.Init("..\\Resources\\Woman1.tga", "..\\Resources\\Woman1.nfg");
	
	obj2.SetPosition(0.4f, -0.8f, 0.0f);
	obj2.SetScale(0.5f, 0.8f, 0.5f);
	obj2.SetRotation(0.0f, 200.0f, 0.0f);
	obj2.Init("..\\Resources\\Woman2.tga", "..\\Resources\\Woman2.nfg");

	skyBox.SetPosition(0.0f, 0.0f, 0.0f);
	skyBox.SetScale(200.0f, 200.0f, 200.0f);
	skyBox.SetRotation(0.0f, 0.0f, 0.0f);
	skyBox.loadCube("..\\Resources\\right.tga", "..\\Resources\\left.tga", "..\\Resources\\top.tga", "..\\Resources\\bottom.tga", "..\\Resources\\front.tga", "..\\Resources\\back.tga");*/
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
	switch (key)
	{
	case 'W':
	case 'w':
		SceneManager::GetInstance()->MoveCamera('w');
		break;
	case 'S':
	case 's':
		SceneManager::GetInstance()->MoveCamera('s');
		break;
	case 'A':
	case 'a':
		SceneManager::GetInstance()->MoveCamera('a');
		break;
	case 'D':
	case 'd':
		SceneManager::GetInstance()->MoveCamera('d');
		break;
	/*case '\&':
		Camera::GetInstance()->Move('\&');
		break;
	case '\(':
		Camera::GetInstance()->Move('\(');
		break;*/
	case '\%':
		SceneManager::GetInstance()->MoveCamera('\%');
		break;
	case '\'':
		SceneManager::GetInstance()->MoveCamera('\'');
		break;
	}
}

void CleanUp()
{
//	obj1.CleanUp();
//	obj2.CleanUp();
	SceneManager::GetInstance()->CleanUP();
	ResourceManager::GetInstance()->CleanUp();
//	Camera::GetInstance()->CleanUp();
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

