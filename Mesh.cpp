#include "Mesh.h"
#include <iostream>
#include <fstream>

using namespace std;

bool saveMeshToPLY(const Mesh &mesh, const char* path)
{
	ofstream outputFile(path);
	if (!outputFile.is_open())
	{
		cout << "Cannot open " << path << " for writing" << endl;
		return false;
	}

	// Write header
	outputFile << "ply" << endl;
	outputFile << "format ascii 1.0" << endl;
	outputFile << "element vertex " << mesh.vertices.size() << endl;
	outputFile << "property float x" << endl;
	outputFile << "property float y" << endl;
	outputFile << "property float z" << endl;
	outputFile << "element face " << mesh.faces.size() << endl;
	outputFile << "property list uchar int vertex_index" << endl;
	outputFile << "end_header" << endl;

	// Write vertices
	for (int i = 0; i < mesh.vertices.size(); i++)
	{
		outputFile << mesh.vertices[i].x << " " << mesh.vertices[i].y << " " << mesh.vertices[i].z << endl;
	}

	// Write faces
	for (int i = 0; i < mesh.faces.size(); i++)
	{
		outputFile << "3 " << mesh.faces[i].a << " " << mesh.faces[i].b << " " << mesh.faces[i].c << endl;
	}
	
	outputFile.close();
	
	return true;
}