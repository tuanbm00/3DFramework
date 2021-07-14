#include <stdafx.h>

#include "Model.h"
#include <stdio.h>


Model::Model() {

}

Model::~Model(){
	delete[] this->vertices;
	delete[] this->indices;
}

bool Model::Init(char *filename) {
	FILE* file = fopen(filename, "r");
	int numberOfVertices;
	fscanf(file, "NrVertices: %d\n", &numberOfVertices);
	this->numOfVertices = numberOfVertices;
	if (numberOfVertices <= 0)
		return false;
	this->vertices = new Vertex[numberOfVertices];
	for (int i = 0; i < numberOfVertices; ++i)
	{
		fscanf(file, "   %*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%*f, %*f, %*f]; tgt:[%*f, %*f, %*f]; uv:[%f, %f];\n",
			&vertices[i].position.x, &vertices[i].position.y, &vertices[i].position.z,
			&vertices[i].normal.x, &vertices[i].normal.y, &vertices[i].normal.z,
			&vertices[i].uv.x, &vertices[i].uv.y);
	}

	int numberOfIndices;
	fscanf(file, "NrIndices: %d\n", &numberOfIndices);
	this->indices = new int[numberOfIndices];
	this->numOfIndices = numberOfIndices;
	for (int i = 0; i < numberOfIndices; i += 3)
	{
		fscanf(file, "   %*d.    %d,    %d,    %d\n", &indices[i], &indices[i + 1], &indices[i + 2]);
	}
}
