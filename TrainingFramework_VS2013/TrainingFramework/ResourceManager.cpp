#include <stdafx.h>
#include "ResourceManager.h"
#include "SceneManager.h"
#include <stdio.h>

ResourceManager* ResourceManager::s_instance = NULL;

ResourceManager::ResourceManager() {

}

ResourceManager::~ResourceManager() {

}

ResourceManager* ResourceManager::GetInstance() {
	if (!s_instance) 
		s_instance = new ResourceManager();
	return s_instance;
}

void ResourceManager::CleanUp() {
	if (s_instance) {
		delete s_instance;
		s_instance = NULL;
	}
}

void ResourceManager::Init() {
	int numOfObject = SceneManager::GetInstance()->GetNumOfObject();
	Object *listObject = SceneManager::GetInstance()->GetListObject();
	FILE* file = fopen("..\\Resources\\ResourceManager.txt", "r");
	char *buff = new char[256];
	int numOfModels, numOfTextures, numOfCube;
	fscanf(file, "#Models: %d\n", &numOfModels);
	m_listModelFile = new char*[numOfModels];
	for (int i = 0; i < numOfModels; i++) {
		m_listModelFile[i] = new char[256];
		int id;
		fscanf(file, "ID %d\n", &id);
		fscanf(file, "FILE %s\n", m_listModelFile[i]);
	}
	fscanf(file, "\n", buff);

	fscanf(file, "#2D Textures: %d\n", &numOfTextures);
	m_listTextureFile = new char*[numOfTextures];
	for (int i = 0; i < numOfModels; i++) {
		m_listTextureFile[i] = new char[256];
		int id;
		fscanf(file, "ID %d\n", &id);
		fscanf(file, "FILE %s\n", m_listTextureFile[i]);
		fgets(buff, 255, file);
		fgets(buff, 255, file);
	}
	fscanf(file, "\n", buff);

	fscanf(file, "#Cube Textures: %d\n", &numOfCube);
	m_listCubeFile = new char*[6];
	for (int i = 0; i < 6; i++) {
		m_listCubeFile[i] = new char[256];
	}
	for (int i = 0; i < numOfModels; i++) {
		int id;
		fscanf(file, "ID %d\n", &id);
		fscanf(file, "FILE %s , %s , %s , %s , %s , %s\n", m_listCubeFile[0], m_listCubeFile[1], m_listCubeFile[2], m_listCubeFile[3], m_listCubeFile[4], m_listCubeFile[5]);
		fgets(buff, 255, file);
		fgets(buff, 255, file);
	}
	fclose(file);

	for (int i = 0; i < numOfObject; i++) {
		if (listObject[i].m_numOfCube == 0) {
			int id = listObject[i].m_iObjectID;
			listObject[i].Init(m_listTextureFile[id], m_listModelFile[id]);
		}
		else {
			listObject[i].loadCube(m_listCubeFile[0], m_listCubeFile[1], m_listCubeFile[2], m_listCubeFile[3], m_listCubeFile[4], m_listCubeFile[5]);
		}
	}
	for (int i = 0; i < numOfModels; i++) {
		delete m_listModelFile[i];
	}
	for (int i = 0; i < numOfTextures; i++) {
		delete m_listTextureFile[i];
	}
	for (int i = 0; i < 6; i++) {
		delete m_listCubeFile[i];
	}
	delete[] m_listCubeFile;
	delete[] m_listModelFile;
	delete[] m_listTextureFile;
	delete[] buff;
}
