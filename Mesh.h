#pragma once

#include <vector>

struct Vertex
{
	float x;
	float y;
	float z;
};

struct Face
{
	unsigned int a;
	unsigned int b;
	unsigned int c;
};

struct Mesh
{
	std::vector< Vertex > vertices;
	std::vector< Face > faces;
};

bool saveMeshToPLY(const Mesh &mesh, const char* path);