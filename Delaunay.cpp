#include <iostream>
#include <list>
#include "Delaunay.h"

//this function is called from main, receives a Mesh object
//which containss a std::vector of vertices and another of faces
void triangulateMesh(Mesh &mesh){

	//create temporary triangle that contains all vertices
	//(adds three temporary vertices to mesh)
	superTriangle(mesh);

	//for all vertices in mesh
	for (int i = 0; i < mesh.vertices.size() - 3; i++){
		//add vertex to the delaunay triangulation
		addVertex(mesh, i);
		//record progress
		if (i % 1 == 0) std::cout << i << " of " << mesh.vertices.size() << " completed.\n";
	}

	//remove any faces that were connected to the temporary super triangle
	for (int i = 0; i < mesh.faces.size(); i++){
		if ((mesh.faces[i].a == mesh.vertices.size() - 3) || (mesh.faces[i].a == mesh.vertices.size() - 2) || (mesh.faces[i].a == mesh.vertices.size() - 1) ||
			(mesh.faces[i].b == mesh.vertices.size() - 3) || (mesh.faces[i].b == mesh.vertices.size() - 2) || (mesh.faces[i].b == mesh.vertices.size() - 1) ||
			(mesh.faces[i].c == mesh.vertices.size() - 3) || (mesh.faces[i].c == mesh.vertices.size() - 2) || (mesh.faces[i].c == mesh.vertices.size() - 1))
		{
			mesh.faces.erase(mesh.faces.begin() + i);
			i = i - 1;
		}
	}
}

//create temporary triangle that contains all vertices
//(adds three temporary vertices to mesh)
void superTriangle(Mesh &mesh){

	double
		xmin = mesh.vertices[0].x,
		xmax = xmin,
		ymin = mesh.vertices[0].y,
		ymax = ymin;

	for (int i = 1; i < mesh.vertices.size(); i++){
		if (mesh.vertices[i].x < xmin) xmin = mesh.vertices[i].x;
		if (mesh.vertices[i].x > xmax) xmax = mesh.vertices[i].x;
		if (mesh.vertices[i].y < ymin) ymin = mesh.vertices[i].y;
		if (mesh.vertices[i].y > ymax) ymax = mesh.vertices[i].y;
	}

	double
		dx = xmax - xmin,
		dy = ymax - ymin,
		dmax = (dx > dy) ? dx : dy,
		xmid = (xmax + xmin) / 2.0,
		ymid = (ymax + ymin) / 2.0;

	Vertex
		v1{ xmid - 20 * dmax, ymid - dmax, 0.0 },
		v2{ xmid + 20 * dmax, ymid - dmax, 0.0 },
		v3{ xmid, ymid + 20 * dmax, 0.0 };

	mesh.vertices.push_back(v1);
	mesh.vertices.push_back(v2);
	mesh.vertices.push_back(v3);
	mesh.faces.push_back(Face{ mesh.vertices.size() - 3, mesh.vertices.size() - 2, mesh.vertices.size() - 1 });

}

//Implement this function
void addVertex(Mesh &mesh, const int vertexIndex){
	Vertex vi = mesh.vertices[vertexIndex];
	std::vector<Edge> edges_list;
	// For triangle ti in triangle_list {
	for (size_t i = 0; i < mesh.faces.size(); i++) {
		// If vi is inside circumcircle of ti {
		// Receives three vertices of a triangle(A, B, C) and returns true if point is inside the circumcircle of that triangle, otherwiser returns false
		Face ti = mesh.faces[i];
		if (isInsideCircumCircle(mesh.vertices[ti.a], mesh.vertices[ti.b], mesh.vertices[ti.c], vi)) {
			// Save edges of ti to edges_list
			Edge edge1;
			edge1.v1 = ti.a;
			edge1.v2 = ti.b;
			Edge edge2;
			edge2.v1 = ti.b;
			edge2.v2 = ti.c;
			Edge edge3;
			edge3.v1 = ti.c;
			edge3.v2 = ti.a;
			edges_list.push_back(edge1);
			edges_list.push_back(edge2);
			edges_list.push_back(edge3);
			// Delete triangle ti
			mesh.faces.erase(mesh.faces.begin() + i);
		}
	}

	// Remove duplicate edges in edges_list
	for (size_t i = 0; i < edges_list.size(); i++) {
		Edge edge1 = edges_list[i];
		bool deleted = false;
		for (size_t j = i + 1; j < edges_list.size(); j++) {
			Edge edge2 = edges_list[j];
			if ((edge1.v1 == edge2.v1 && edge1.v2 == edge2.v2) || (edge1.v1 == edge2.v2 && edge1.v2 == edge2.v1)) {
				edges_list.erase(edges_list.begin() + j);
				if (!deleted) {
					edges_list.erase(edges_list.begin() + i);
					deleted = true;
				}
			}
		}
	}

	// For edge ei in edges_list {
	for (size_t i = 0; i < edges_list.size(); i++) {
		Edge ei = edges_list[i];
		// Create triangle which links vertices of ei with vi
		Face face;
		face.a = ei.v1;
		face.b = ei.v2;
		face.c = vertexIndex;
		mesh.faces.push_back(face);
	}

	// Clear edges_list
	edges_list.clear();
}

//returns true if Vertex 'point' is within the circumcircle of triangle ABV
bool isInsideCircumCircle(const Vertex A, const Vertex B, const Vertex C, const Vertex &point){
	double m1, m2, mx1, mx2, my1, my2, xc, yc, r;
	double dx, dy, rsqr, drsqr;

	if (abs(A.y - B.y) < EPSILON && abs(B.y - C.y) < EPSILON)
		return(false);
	if (abs(B.y - A.y) < EPSILON){
		m2 = -(C.x - B.x) / (C.y - B.y);
		mx2 = (B.x + C.x) / 2.0;
		my2 = (B.y + C.y) / 2.0;
		xc = (B.x + A.x) / 2.0;
		yc = m2 * (xc - mx2) + my2;
	}
	else if (abs(C.y - B.y) < EPSILON){
		m1 = -(B.x - A.x) / (B.y - A.y);
		mx1 = (A.x + B.x) / 2.0;
		my1 = (A.y + B.y) / 2.0;
		xc = (C.x + B.x) / 2.0;
		yc = m1 * (xc - mx1) + my1;
	}
	else{
		m1 = -(B.x - A.x) / (B.y - A.y);
		m2 = -(C.x - B.x) / (C.y - B.y);
		mx1 = (A.x + B.x) / 2.0;
		mx2 = (B.x + C.x) / 2.0;
		my1 = (A.y + B.y) / 2.0;
		my2 = (B.y + C.y) / 2.0;
		xc = (m1 * mx1 - m2 * mx2 + my2 - my1) / (m1 - m2);
		yc = m1 * (xc - mx1) + my1;
	}
	dx = B.x - xc;
	dy = B.y - yc;
	rsqr = dx * dx + dy * dy;
	dx = point.x - xc;
	dy = point.y - yc;
	drsqr = dx * dx + dy * dy;
	return((drsqr <= rsqr) ? true : false);

}






