#include <stdafx.h>
#include "Object.h"

Object::Object() {

}

Object::~Object() {


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

void Object::Init(char* fileTexture, char* fileModel) {
	m_model.Init(fileModel);
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, m_model.numOfVertices * sizeof(Vertex), m_model.vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_model.numOfIndices * sizeof(int), m_model.indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	m_texture.Init(fileTexture);
	glBindTexture(GL_TEXTURE_2D, 0);
	delete[] m_model.indices;
	delete[] m_model.vertices;

	m_shaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
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
	glUseProgram(m_shaders.program);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(m_shaders.uniformLocation, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glEnableVertexAttribArray(m_shaders.positionAttribute);
	glVertexAttribPointer(m_shaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
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

void Object::Update(float deltatime) {

}

void Object::CleanUp() {
	glDeleteBuffers(1, &vboId);
	glDeleteBuffers(1, &iboId);
	glDeleteBuffers(1, &textureID);
}
