#include <stdafx.h>
#include "Object.h"

Object::Object() {

}

Object::~Object() {


}

void Object::SetID(int id) {
	m_iObjectID = id;
}

void Object::SetnumOfCube(int numOfCube) {
	m_numOfCube = numOfCube;
}

void Object::SetnumOfShader(int shaderID) {
	m_shaderID = shaderID;
}

void Object::SetnumOfTexture(int numOfTexture) {
	if (numOfTexture == 0) {
		numOfTexture = 1;
	}
	m_numOfTexture = numOfTexture;
	textureID = new GLuint[numOfTexture];
	m_texture = new Texture[numOfTexture];
}

void Object::SetPosition(float x, float y, float z) {
	m_position = Vector3(x, y, z);
}

void Object::SetScale(float x, float y, float z) {
	m_scale = Vector3(x, y, z);
}

void Object::SetRotation(float x, float y, float z) {
	m_rotation = Vector3(x, y, z);
}

void Object::Init(char** fileTexture, char* fileModel, char* fileVS, char* fileFS) {
	m_model.Init(fileModel);
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, m_model.numOfVertices * sizeof(Vertex), m_model.vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_model.numOfIndices * sizeof(int), m_model.indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenTextures(m_numOfTexture, textureID);
	for (int i = 0; i < m_numOfTexture; i++) {
		glBindTexture(GL_TEXTURE_2D, textureID[i]);
		m_texture[i].Init(fileTexture[i]);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	delete[] m_model.indices;
	delete[] m_model.vertices;
	m_shaders.Init(fileVS, fileFS);
}

void Object::loadCube(char* fileModel, char* rightfile, char* leftfile, char* topfile, char* botfile, char* frontfile, char* backfile) {
	//float skyboxVertices[] = {
	//	// positions          
	//	-1.0f,  1.0f, -1.0f,
	//	 1.0f,  1.0f, -1.0f,
	//	 1.0f,  1.0f,  1.0f,
	//	-1.0f,  1.0f,  1.0f,
	//	-1.0f, -1.0f, -1.0f,
	//	-1.0f, -1.0f,  1.0f,
	//	 1.0f, -1.0f, -1.0f,
	//	 1.0f, -1.0f,  1.0f,
	//};

	//int indices[] = {
	//	0, 1, 2,
	//	2, 3, 0,

	//	4, 6, 7,
	//	7, 5, 4,

	//	2, 3, 5,
	//	5, 7, 2,

	//	0, 1, 4,
	//	4, 6, 1,

	//	0, 3, 4,
	//	4, 5, 3,

	//	1, 2, 6,
	//	6, 7, 2
	//};
	m_model.Init(fileModel);

	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, m_model.numOfVertices * sizeof(Vertex), m_model.vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_model.numOfIndices * sizeof(int), m_model.indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenTextures(1, textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID[0]);
	m_texture[0].loadCube(rightfile, leftfile, topfile, botfile, frontfile, backfile);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	
	delete[] m_model.indices;
	delete[] m_model.vertices;
	m_shaders.Init("../Resources/Shaders/CubeShaderVS.vs", "../Resources/Shaders/CubeShaderFS.fs");
}

void Object::IntMVP() {
	Matrix Rx, Ry, Rz;
	Matrix viewMatrix;
	Matrix perspective;
	viewMatrix.SetIdentity();
	perspective.SetIdentity();
	Matrix translationMatrix, rotationMatrix, scaleMatrix;
	scaleMatrix.SetScale(m_scale.x, m_scale.y, m_scale.z);
	rotationMatrix = Rz.SetRotationZ(m_rotation.z * float(PI / 180.0f)) * Rx.SetRotationX(m_rotation.x * float(PI / 180.0f)) * Ry.SetRotationY(m_rotation.y * float(PI / 180.0f));
	translationMatrix.SetTranslation(m_position.x, m_position.y, m_position.z);
	m_worldMatrix = scaleMatrix * rotationMatrix * translationMatrix;
	
	m_WVP = m_worldMatrix * Camera::GetInstance()->GetViewMatrix() * Camera::GetInstance()->GetPerspective();
}

void Object::Draw() {
	IntMVP();
	if (m_numOfCube) {
		glUseProgram(m_shaders.program);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID[0]);
//		glUniform1i(m_shaders.uniformLocation, 0);

//		glUniform1i(m_shaders.cubeAttribute, 0);


		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glEnableVertexAttribArray(m_shaders.positionAttribute);
		glVertexAttribPointer(m_shaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
//		glEnableVertexAttribArray(m_shaders.cubeAttribute);
//		glVertexAttribPointer(m_shaders.cubeAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(float), 0);

//		glEnableVertexAttribArray(m_shaders.mvpUniform);
		glUniformMatrix4fv(m_shaders.mvpUniform, 1, GL_FALSE, (GLfloat*)m_WVP.m);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	else {
		glUseProgram(m_shaders.program);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID[0]);
		glUniform1i(m_shaders.uniformLocation, 0);
		if (m_numOfTexture > 1) {
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, textureID[1]);
			glUniform1i(m_shaders.rUniform, 1);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, textureID[2]);
			glUniform1i(m_shaders.gUniform, 2);
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, textureID[3]);			
			glUniform1i(m_shaders.bUniform, 3);
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, textureID[4]);
			glUniform1i(m_shaders.heightMapUniform, 4);
		}
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glEnableVertexAttribArray(m_shaders.positionAttribute);
		glVertexAttribPointer(m_shaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

		glEnableVertexAttribArray(m_shaders.normalAttribute);
		glVertexAttribPointer(m_shaders.uvAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)(0 + sizeof(Vector3)));

		glEnableVertexAttribArray(m_shaders.uvAttribute);
		glVertexAttribPointer(m_shaders.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)(0 + sizeof(Vector3)*4));
	
		glEnableVertexAttribArray(m_shaders.mvpUniform);
		glUniformMatrix4fv(m_shaders.mvpUniform, 1, GL_FALSE, (GLfloat*) m_WVP.m);
	
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
		glDrawElements(GL_TRIANGLES, m_model.numOfIndices, GL_UNSIGNED_INT, 0);

		glBindTexture(GL_TEXTURE_2D, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}

void Object::Update(float deltatime) {

}

void Object::CleanUp() {
	glDeleteBuffers(1, &vboId);
	glDeleteBuffers(1, &iboId);
	glDeleteBuffers(1, textureID);
}
