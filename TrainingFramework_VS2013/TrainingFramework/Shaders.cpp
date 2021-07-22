#include <stdafx.h>
#include "Shaders.h"

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if ( vertexShader == 0 )
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if ( fragmentShader == 0 )
	{
		glDeleteShader( vertexShader );
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_posL");
	uvAttribute = glGetAttribLocation(program, "a_uv");
	colorAttribute = glGetAttribLocation(program, "a_color");
	cubeAttribute = glGetUniformLocation(program, "u_samplerCubeMap");
	uniformLocation = glGetUniformLocation(program, "u_texture");
	mvpUniform = glGetUniformLocation(program, "u_mvpMatrix");
	rUniform = glGetUniformLocation(program, "r_texture");
	gUniform = glGetUniformLocation(program, "g_texture");
	bUniform = glGetUniformLocation(program, "b_texture");
	return 0;
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}