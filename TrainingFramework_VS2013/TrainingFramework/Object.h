#pragma once
#include <math.h>
#include "Shaders.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "../Utilities/utilities.h"

#define PI 3.1459f


class Object {
public:
	Texture m_texture;
	Model m_model;
	Shaders m_shaders;
	Matrix m_worldMatrix;
	Matrix m_WVP;

	int m_iObjectID;
	GLuint vboId;
	GLuint iboId;
	GLuint textureID;
	Vector3 m_position;
	Vector3 m_scale;
	Vector3 m_rotation;

	Object();
	~Object();
	void SetPosition(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void Init(char* fileTexture, char* fileModel);
	void Draw();
	void IntMVP();
	void CleanUp();
	void Update(float deltaTime);
};