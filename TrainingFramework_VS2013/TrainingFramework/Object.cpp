#include <stdafx.h>
#include "Object.h"

Object::Object() {
	m_deltatime = 0;
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
	glGenTextures(m_numOfTexture, textureID);
	for (int i = 0; i < m_numOfTexture; i++) {
		glBindTexture(GL_TEXTURE_2D, textureID[i]);
		m_texture[i].Init(fileTexture[i]);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	m_model.Init(fileModel);
	if (m_numOfTexture == 5) {
		m_model.loadHeight(fileTexture[4]);
	}
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, m_model.numOfVertices * sizeof(Vertex), m_model.vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_model.numOfIndices * sizeof(int), m_model.indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete[] m_model.indices;
	delete[] m_model.vertices;
	m_shaders.Init(fileVS, fileFS);
}

void Object::loadCube(char* fileModel, char* filename) {
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
	m_texture[0].loadCube(filename);
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

		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glEnableVertexAttribArray(m_shaders.positionAttribute);
		glVertexAttribPointer(m_shaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

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

		glBindBuffer(GL_ARRAY_BUFFER, vboId);

		glEnableVertexAttribArray(m_shaders.positionAttribute);
		glVertexAttribPointer(m_shaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

		glEnableVertexAttribArray(m_shaders.uvAttribute);
		glVertexAttribPointer(m_shaders.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)(0 + sizeof(Vector3)*4));
	
		glEnableVertexAttribArray(m_shaders.mvpUniform);
		glUniformMatrix4fv(m_shaders.mvpUniform, 1, GL_FALSE, (GLfloat*) m_WVP.m);

		glUniform1f(m_shaders.timeUniform, m_deltatime);
		glUniform1f(m_shaders.fogStartUniform, Camera::GetInstance()->GetFogStart());
		glUniform1f(m_shaders.fogLengthUniform, Camera::GetInstance()->GetFogLength());
		float v[3];
		v[0] = Camera::GetInstance()->GetFogColor().x;
		v[1] = Camera::GetInstance()->GetFogColor().y;
		v[2] = Camera::GetInstance()->GetFogColor().z;

		glUniform3fv(m_shaders.fogColorUniform, 1, v);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
		glDrawElements(GL_TRIANGLES, m_model.numOfIndices, GL_UNSIGNED_INT, 0);

		glBindTexture(GL_TEXTURE_2D, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

void Object::Update(float deltatime) {
	m_deltatime = deltatime;
}

void Object::CleanUp() {
	glDeleteBuffers(1, &vboId);
	glDeleteBuffers(1, &iboId);
	glDeleteBuffers(1, textureID);
}
