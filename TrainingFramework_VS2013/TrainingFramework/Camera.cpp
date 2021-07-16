#include "stdafx.h"
#include "Camera.h"
#include "Globals.h"
#include<iostream>

Camera* Camera::s_instance = NULL;

Camera::Camera() {

}

Camera::~Camera() {

}

void Camera::Init(float m_fov, float m_near, float m_far) {
	m_FOV = m_fov;
	m_Near = m_near;
	m_Far = m_far;
	m_speed = 20.0f;
	m_move = Vector3(0, 0, 0);
	m_rotFlag = 0.0f;
}

void Camera::SetPosition(float x, float y, float z) {
	m_position = Vector3(x, y, z);
}

void Camera::SetTarget(float x, float y, float z) {
	m_target = Vector3(x, y, z);
}

void Camera::SetUp(float x, float y, float z) {
	m_up = Vector3(x, y, z);
}

void Camera::Update(float deltatime) {
	m_position += m_move * deltatime*m_speed;
	m_target += m_move * deltatime*m_speed;
	m_move = Vector3(0, 0, 0);
	Vector4 localTarget = Vector4(0, 0, -(m_position - m_target).Length(), 1);
	localTarget = localTarget * RotationMatrixAroundY(m_rotFlag*deltatime*m_speed);
	localTarget = localTarget * GetWorldMatrix();
	m_target.x = localTarget.x;
	m_target.y = localTarget.y;
	m_target.y = localTarget.y;
	m_rotFlag = 0.0f;
}

Camera* Camera::GetInstance() {
	if (!s_instance)
		s_instance = new Camera();
	return s_instance;
}

Matrix Camera::GetPerspective() {
	float aspect = (float)Globals::screenWidth / Globals::screenHeight;
	Matrix Perspective;
	Perspective.SetPerspective(m_FOV, aspect, m_Near, m_Far);
	return Perspective;
}

Matrix Camera::GetWorldMatrix() {
	Vector3 xaxis, yaxis, zaxis;
	zaxis = (m_position - m_target).Normalize();
	xaxis = (m_up.Cross(zaxis)).Normalize();
	yaxis = (zaxis.Cross(xaxis)).Normalize();
	Matrix R, T;
	R.m[0][0] = xaxis.x;
	R.m[0][1] = xaxis.y;
	R.m[0][2] = xaxis.z;
	R.m[0][3] = 0;

	R.m[1][0] = yaxis.x;
	R.m[1][1] = yaxis.y;
	R.m[1][2] = yaxis.z;
	R.m[1][3] = 0;

	R.m[2][0] = zaxis.x;
	R.m[2][1] = zaxis.y;
	R.m[2][2] = zaxis.z;
	R.m[2][3] = 0;

	R.m[3][0] = 0;
	R.m[3][1] = 0;
	R.m[3][2] = 0;
	R.m[3][3] = 1;

	T.m[0][0] = 1;
	T.m[0][1] = 0;
	T.m[0][2] = 0;
	T.m[0][3] = 0;

	T.m[1][0] = 0;
	T.m[1][1] = 1;
	T.m[1][2] = 0;
	T.m[1][3] = 0;

	T.m[2][0] = 0;
	T.m[2][1] = 0;
	T.m[2][2] = 1;
	T.m[2][3] = 0;

	T.m[3][0] = m_position.x;
	T.m[3][1] = m_position.y;
	T.m[3][2] = m_position.z;
	T.m[3][3] = 1;
	
	m_worldMatrix = R * T;
	return m_worldMatrix;
}

Matrix Camera::GetViewMatrix() {
	Vector3 xaxis, yaxis, zaxis;
	zaxis = (m_position - m_target).Normalize();
	xaxis = (m_up.Cross(zaxis)).Normalize();
	yaxis = (zaxis.Cross(xaxis)).Normalize();
	m_viewMatrix.m[0][0] = xaxis.x;
	m_viewMatrix.m[0][1] = yaxis.x;
	m_viewMatrix.m[0][2] = zaxis.x;
	m_viewMatrix.m[0][3] = 0;

	m_viewMatrix.m[1][0] = xaxis.y;
	m_viewMatrix.m[1][1] = yaxis.y;
	m_viewMatrix.m[1][2] = zaxis.y;
	m_viewMatrix.m[1][3] = 0;

	m_viewMatrix.m[2][0] = xaxis.z;
	m_viewMatrix.m[2][1] = yaxis.z;
	m_viewMatrix.m[2][2] = zaxis.z;
	m_viewMatrix.m[2][3] = 0;

	m_viewMatrix.m[3][0] = -m_position.Dot(xaxis);
	m_viewMatrix.m[3][1] = -m_position.Dot(yaxis);
	m_viewMatrix.m[3][2] = -m_position.Dot(zaxis);
	m_viewMatrix.m[3][3] = 1;

	return m_viewMatrix;
}

Matrix Camera::RotationMatrixAroundY(float angle) {
	Vector3 xaxis, yaxis, zaxis;
	zaxis = (m_position - m_target).Normalize();
	xaxis = (m_up.Cross(zaxis)).Normalize();
	yaxis = (zaxis.Cross(xaxis)).Normalize();
	Matrix rotationAxis;
	return rotationAxis.SetRotationAngleAxis(angle, yaxis.x, yaxis.y, yaxis.z);
}

void Camera::Move(char key) {
	if (key == 'w') {
		m_move = -(m_position - m_target).Normalize();
	}
	if (key == 's') {
		m_move = (m_position - m_target).Normalize();
	}
	if (key == 'a') {
		m_move = (m_up.Cross((m_position - m_target).Normalize())).Normalize();
	}
	if (key == 'd') {
		m_move = -(m_up.Cross((m_position - m_target).Normalize())).Normalize();
	}
	if (key == '\%') {
		m_rotFlag = 1.0f;
	}
	if (key == '\'') {
		m_rotFlag = -1.0f;
	}
}

void Camera::CleanUp() {
	if (s_instance) {
		delete s_instance;
		s_instance = NULL;
	}
}