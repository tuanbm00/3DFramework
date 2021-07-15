#include "stdafx.h"
#include "Camera.h"
#include "Globals.h"
#include<iostream>

Camera* Camera::s_instance = NULL;

Camera::Camera() {

}

Camera::~Camera() {

}

void Camera::Init() {

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