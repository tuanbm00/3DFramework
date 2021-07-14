#pragma once

#include "../Utilities/utilities.h"

class Texture {
//private:
//	static Texture* s_Instance;
public:
	Texture();
	~Texture();
	void Init(char* filename);
//	static Texture* GetInstance();
};