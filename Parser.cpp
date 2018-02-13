#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Parser.h"
using namespace std;

bool parsePoints(const char* filePath, std::vector<Vertex> &vertices){
	float a, b, c;
	char v;
	string line;
	ifstream myfile(filePath);

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			stringstream linestream(line);
			if (linestream >> a >> b >> c)
			{
				Vertex vertexLine;
				vertexLine.x = a;
				vertexLine.y = b;
				vertexLine.z = c;

				vertices.push_back(vertexLine);
			}
		}
		myfile.close();
		return true;
	}
	return false;
}
