#include <iostream>
#include "Parser.h"
#include "Delaunay.h"

int main(int argc, const char* argv[])
{
	Mesh mesh;
	std::cout << "Parsing input file. Please wait...\n";

	if (!parsePoints("../input.txt", mesh.vertices))
	{
		printf("ERROR! Could not parse input file\n");
		return 0;
	}

	std::cout << " [Done]\n" << std::endl;
	std::cout << "Creating mesh. Please wait...\n";

	triangulateMesh(mesh);

	std::cout << " [Done]\n" << std::endl;
	std::cout << "Saving PLY file. Please wait...\n";

	if (!saveMeshToPLY(mesh, "ouput.ply"))
	{
		printf("ERROR! Could not save mesh to PLY file\n");
		return 0;
	}

	std::cout << " [Done]\n" << std::endl;
}

