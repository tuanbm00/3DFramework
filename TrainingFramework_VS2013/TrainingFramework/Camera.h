#pragma once
#include <math.h>
#include "../Utilities/utilities.h"

class Camera {
private:
	static Camera* s_instance;
	float m_FOV;
	float m_Near;
	float m_Far;
public:
	Camera();
	~Camera();
	void Init();
	static Camera* GetInstance();
	Matrix GetPerspective();
};
