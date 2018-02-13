#pragma once

#include <vector>

#include "Mesh.h"

// Reads points from file. Return true if there's no problem.
bool parsePoints(const char* filePath, std::vector<Vertex> &points);

