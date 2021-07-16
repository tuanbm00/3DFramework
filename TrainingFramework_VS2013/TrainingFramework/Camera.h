#pragma once
#include <math.h>
#include "../Utilities/utilities.h"

class Camera {
private:
	static Camera* s_instance;
	float m_FOV;
	float m_Near;
	float m_Far;
	float m_speed;
	float m_rotFlag;
	Vector3 m_position;
	Vector3 m_target;
	Vector3 m_up;
	Vector3 m_move;
	Matrix m_viewMatrix;
	Matrix m_worldMatrix;
public:
	Camera();
	~Camera();
	void Init(float m_fov, float m_near, float m_far);
	void SetPosition(float x, float y, float z);
	void SetTarget(float x, float y, float z);
	void SetUp(float x, float y, float z);
	void Update(float deltatime);
	void Move(char key);
	void CleanUp();
	static Camera* GetInstance();
	Matrix GetPerspective();
	Matrix GetViewMatrix();
	Matrix GetWorldMatrix();
	Matrix RotationMatrixAroundY(float angle);
};
