#pragma once

#include "../Utilities/utilities.h"
#include "Vertex.h"

class Model {
public:
	Vertex* vertices;
	int* indices;
	int numOfVertices;
	int numOfIndices;
	Model();
	~Model();
	bool Init(char *filename);
};