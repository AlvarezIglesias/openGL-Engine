#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
#include <iostream>
using namespace std;
using namespace glm;

void
Mesh::draw() const
{
	glDrawArrays(
	  mPrimitive,
	  0,
	  size()); // primitive graphic, first index and number of elements to be rendered
}

void
Mesh::render() const
{
	if (vVertices.size() > 0) { // transfer data
		// transfer the coordinates of the vertices
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());
		glVertexPointer(
		  3, GL_DOUBLE, 0, vVertices.data()); // number of coordinates per vertex, type of
		                                      // each coordinate, stride, pointer
		if (vColors.size() > 0) {             // transfer colors
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(
			  4, GL_DOUBLE, 0, vColors.data()); // components number (rgba=4), type of
			                                    // each component, stride, pointer
		}

		if (vNormals.size() > 0) {
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_DOUBLE, 0, vNormals.data());
		}

		draw();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}
}

// Apartado 2
Mesh* Mesh::generateRegularPolygon(GLuint num, GLdouble r)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINE_LOOP;
	mesh->mNumVertices = num;
	mesh->vVertices.reserve(mesh->mNumVertices);

	GLdouble cx = 0.0;
	GLdouble cy = 0.0;

	GLdouble step = 360.0 / GLdouble(num);
	GLdouble initialAngle = 90.0;
	for (int i = 0; i < num; i++)
	{
		GLdouble currentAngle = initialAngle + step * i;
		GLdouble alpha = radians(currentAngle);

		GLdouble x = cx + r * glm::cos(alpha);
		GLdouble y = cy + r * glm::sin(alpha);
		mesh->vVertices.emplace_back(x, y, 0.0);
	}

	return mesh;
}

// APARTADO 6	
Mesh* Mesh::generateRGBTriangle(GLdouble r) {
	
	Mesh* mesh = Mesh::generateRegularPolygon(3, r);
	mesh->mNumVertices = 3;
	mesh->mPrimitive = GL_TRIANGLES;
	mesh->vColors.reserve(mesh->mNumVertices);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);


	return mesh;
}

// APARTADO 8
Mesh* Mesh::generateRectangle(GLdouble w, GLdouble h)
{
	GLuint num = 4;

	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_FAN;
	mesh->mNumVertices = num;
	mesh->vVertices.reserve(mesh->mNumVertices);

	GLdouble x = w / 2;
	GLdouble y = h / 2;
	mesh->vVertices.emplace_back(-x, -y, 0.0);
	mesh->vVertices.emplace_back(x, -y, 0.0);
	mesh->vVertices.emplace_back(x, y, 0.0);
	mesh->vVertices.emplace_back(-x, y, 0.0);


	return mesh;
}

Mesh* Mesh::generateRGBRectangle(GLdouble w, GLdouble h) {

	Mesh* mesh = Mesh::generateRectangle(w, h);
	mesh->mNumVertices = 4;
	mesh->mPrimitive = GL_TRIANGLE_FAN;
	mesh->vColors.reserve(mesh->mNumVertices);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0); // Hacer que se dibuje centrado
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0); // Mirar colores que no están igual igual

	return mesh;
}

// APARTADO 9
Mesh* Mesh::generateCube(GLdouble length){
	
	GLuint num = 4;
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLES;
	mesh->mNumVertices = 6*6;
	mesh->vVertices.reserve(mesh->mNumVertices);

	GLdouble x ,y ,z = x = y = length / 2;

	// Front face
	mesh->vVertices.emplace_back(-x, -y, z);
	mesh->vVertices.emplace_back(x, -y, z);
	mesh->vVertices.emplace_back(x, y, z);
	mesh->vVertices.emplace_back(x, y, z);
	mesh->vVertices.emplace_back(-x, y, z);
	mesh->vVertices.emplace_back(-x, -y, z);

	// Back face
	mesh->vVertices.emplace_back(-x, -y, -z);
	mesh->vVertices.emplace_back(-x, y, -z);
	mesh->vVertices.emplace_back(x, y, -z);
	mesh->vVertices.emplace_back(x, y, -z);
	mesh->vVertices.emplace_back(x, -y, -z);
	mesh->vVertices.emplace_back(-x, -y, -z);

	// Left face
	mesh->vVertices.emplace_back(-x, -y, -z);
	mesh->vVertices.emplace_back(-x, -y, z);
	mesh->vVertices.emplace_back(-x, y, z);
	mesh->vVertices.emplace_back(-x, y, z);
	mesh->vVertices.emplace_back(-x, y, -z);
	mesh->vVertices.emplace_back(-x, -y, -z);

	// Right face
	mesh->vVertices.emplace_back(x, -y, -z);
	mesh->vVertices.emplace_back(x, y, -z);
	mesh->vVertices.emplace_back(x, y, z);
	mesh->vVertices.emplace_back(x, y, z);
	mesh->vVertices.emplace_back(x, -y, z);
	mesh->vVertices.emplace_back(x, -y, -z);

	// Top face
	mesh->vVertices.emplace_back(-x, y, -z);
	mesh->vVertices.emplace_back(-x, y, z);
	mesh->vVertices.emplace_back(x, y, z);
	mesh->vVertices.emplace_back(x, y, z);
	mesh->vVertices.emplace_back(x, y, -z);
	mesh->vVertices.emplace_back(-x, y, -z);

	// Bottom face
	mesh->vVertices.emplace_back(-x, -y, -z);
	mesh->vVertices.emplace_back(x, -y, -z);
	mesh->vVertices.emplace_back(x, -y, z);
	mesh->vVertices.emplace_back(x, -y, z);
	mesh->vVertices.emplace_back(-x, -y, z);
	mesh->vVertices.emplace_back(-x, -y, -z);

	return mesh;
}

// APARTADO 10
Mesh* Mesh::generateRGBCube(GLdouble length) {

	GLuint num = 4;
	Mesh* mesh = generateCube(length);

	mesh->vColors.reserve(mesh->mNumVertices);

	GLdouble x, y, z = x = y = length / 2;

	// Front face
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);

	// Back face
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);


	// Left face
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);

	// Right face
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);

	// Top face
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	// Bottom face
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}

/*******************************PARTE 2 * ******************************/

// Apartado 19
Mesh *
Mesh::generateRectangleTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	Mesh* mesh = generateRectangle(w, h);

	mesh->vTexCoords.reserve(mesh->mNumVertices);
	mesh->vTexCoords.emplace_back(0, 0);
	mesh->vTexCoords.emplace_back(rw, 0);
	mesh->vTexCoords.emplace_back(rw, rh);
	mesh->vTexCoords.emplace_back(0, rh);

	return mesh;
}

// Apartado 19
Mesh*
Mesh::generateBoxOutline(GLdouble length)
{
	GLuint num = 10;
	Mesh* mesh = new Mesh();
	GLdouble l = length/2.0;

	mesh->mPrimitive = GL_TRIANGLE_STRIP;
	mesh->mNumVertices = num;
	mesh->vVertices.reserve(mesh->mNumVertices);

	//Cara 1
	mesh->vVertices.emplace_back(-l,-l,-l);
	mesh->vVertices.emplace_back(-l,l,-l);
	mesh->vVertices.emplace_back(l, -l, -l);
	mesh->vVertices.emplace_back(l,l,-l);

	//Cara 2
	mesh->vVertices.emplace_back(l, -l, l);
	mesh->vVertices.emplace_back(l, l, l);

	//Cara 3
	mesh->vVertices.emplace_back(-l, -l, l);
	mesh->vVertices.emplace_back(-l, l, l);

	//Cara 4
	mesh->vVertices.emplace_back(-l, -l, -l);
	mesh->vVertices.emplace_back(-l, l, -l);


	mesh->vTexCoords.reserve(mesh->mNumVertices);

	mesh->vTexCoords.emplace_back(0.0, 0.0);
	mesh->vTexCoords.emplace_back(0.0, 1.0);

	mesh->vTexCoords.emplace_back(1.0, 0.0);
	mesh->vTexCoords.emplace_back(1.0, 1.0);

	mesh->vTexCoords.emplace_back(0.0, 0.0);
	mesh->vTexCoords.emplace_back(0.0, 1.0);

	mesh->vTexCoords.emplace_back(1.0, 0.0);
	mesh->vTexCoords.emplace_back(1.0, 1.0);

	mesh->vTexCoords.emplace_back(0.0, 0.0);
	mesh->vTexCoords.emplace_back(0.0, 1.0);


	return mesh;
}


Mesh*
Mesh::createRGBAxes(GLdouble l)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINES;

	mesh->mNumVertices = 6;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// X axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(l, 0.0, 0.0);
	// Y axis vertices
	mesh->vVertices.emplace_back(0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, l, 0.0);
	// Z axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, 0.0, l);

	mesh->vColors.reserve(mesh->mNumVertices);
	// X axis color: red  (Alpha = 1 : fully opaque)
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	// Y axis color: green 
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	// Z axis color: blue
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}

// APARTADO 25
Mesh* 
Mesh::generateStar3D(GLdouble re, GLuint np, GLdouble h)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_FAN;
	mesh->mNumVertices = np * 2 + 2;
	mesh->vVertices.reserve(mesh->mNumVertices);

	GLdouble cx = 0.0;
	GLdouble cy = 0.0;

	GLdouble step = 360.0 / GLdouble(np * 2);
	GLdouble initialAngle = 90.0;

	// Primer vertice, cuspide
	mesh->vVertices.emplace_back(0, 0, 0);

	for (int i = 0; i < np * 2; i++)
	{
		GLdouble currentAngle = initialAngle + step * i;
		GLdouble alpha = radians(currentAngle);

		GLdouble ra = (i % 2 == 0) ? re : re / 2; //Radio actual, alternando exterior e interior

		GLdouble x = cx + ra * glm::cos(alpha);
		GLdouble y = cy + ra * glm::sin(alpha);
		mesh->vVertices.emplace_back(x, y, h);
	}

	// Cerrar 
	mesh->vVertices.emplace_back(mesh->vVertices[1]);
	

	return mesh;
}


// APARTADO 25
Mesh*
Mesh::generateStar3DTexCor(GLdouble re, GLuint np, GLdouble h)
{
	Mesh* mesh = generateStar3D(re, np, h);

	mesh->vTexCoords.reserve(mesh->mNumVertices);

	// Centro
	mesh->vTexCoords.emplace_back(0.5, 0.5);

	mesh->vTexCoords.emplace_back(0.5, 1.0);
	mesh->vTexCoords.emplace_back(0.25, 1.0);
	mesh->vTexCoords.emplace_back(0.0, 1.0);
	mesh->vTexCoords.emplace_back(0.0, 0.75);
	mesh->vTexCoords.emplace_back(0.0, 0.5);
	mesh->vTexCoords.emplace_back(0.0, 0.25);
	mesh->vTexCoords.emplace_back(0.0, 0.0);
	mesh->vTexCoords.emplace_back(0.25, 0.0);
	mesh->vTexCoords.emplace_back(0.5, 0.0);
	mesh->vTexCoords.emplace_back(0.75, 0.0);
	mesh->vTexCoords.emplace_back(1.0, 0.0);
	mesh->vTexCoords.emplace_back(1.0, 0.25);
	mesh->vTexCoords.emplace_back(1.0, 0.5);
	mesh->vTexCoords.emplace_back(1.0, 0.75);
	mesh->vTexCoords.emplace_back(1.0, 1.0);
	mesh->vTexCoords.emplace_back(0.75, 1.0);
	mesh->vTexCoords.emplace_back(0.5, 1.0);



	return mesh;
}


// APARTADO 60
Mesh* 
Mesh::generateWingAdvancedTIE(GLdouble w, GLdouble h) {

	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;
	mesh->mNumVertices = 8;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vTexCoords.reserve(mesh->mNumVertices);

	GLdouble x = w / 2;
	GLdouble y = h / 2;

	// vertices
	mesh->vVertices.emplace_back(-x, -h + y, 0.0);
	mesh->vVertices.emplace_back(x, -h + y, 0.0);

	mesh->vVertices.emplace_back(-x, -h * 0.666 + y, h * 0.333);
	mesh->vVertices.emplace_back(x, -h * 0.666 + y, h * 0.333);

	mesh->vVertices.emplace_back(-x, -h * 0.333 + y, h * 0.333);
	mesh->vVertices.emplace_back(x, -h * 0.333 + y, h * 0.333);

	mesh->vVertices.emplace_back(-x, 0.0 + y, 0.0);
	mesh->vVertices.emplace_back(x, 0.0 + y, 0.0);

	// texCoords
	mesh->vTexCoords.emplace_back(0.0, 0.0);
	mesh->vTexCoords.emplace_back(1.0, 0.0);

	mesh->vTexCoords.emplace_back(0.0, 0.333);
	mesh->vTexCoords.emplace_back(1.0, 0.333);

	mesh->vTexCoords.emplace_back(0.0, 0.666);
	mesh->vTexCoords.emplace_back(1.0, 0.666);

	mesh->vTexCoords.emplace_back(0.0, 1.0);
	mesh->vTexCoords.emplace_back(1.0, 1.0);

	return mesh;
}

/*******************************PARTE 4 * ******************************/

glm::dvec3
IndexMesh::buildNormalVectors(int init) {
	dvec3 n = dvec3(0, 0, 0);
	/*dvec3 vertActual;
	dvec3 vertSiguiente;
	for (int i = 0; i < 3; i++) {
		vertActual = vVertices[vIndexes[init +i]];
		vertSiguiente = vVertices[vIndexes[ init + ((i + 1) % 3)]];
		n.x += (vertActual.y - vertSiguiente.y) * (vertActual.z + vertSiguiente.z);
		n.y += (vertActual.z - vertSiguiente.z) * (vertActual.x + vertSiguiente.x);
		n.z += (vertActual.x - vertSiguiente.x) * (vertActual.y + vertSiguiente.y);
	}*/


	//return -normalize(n);
	return cross((vVertices[vIndexes[init + 1]] - vVertices[vIndexes[init + 0]]), (vVertices[vIndexes[init + 2]] - vVertices[vIndexes[init + 0]]));
}

void
IndexMesh::draw() const {
	glDrawElements(mPrimitive, nNumIndices, GL_UNSIGNED_INT, vIndexes.data());
}

void 
IndexMesh::buildNormalVectors() {

	vNormals.clear();
	vNormals.resize(mNumVertices, dvec3(0.0, 0.0, 0.0));
	
	for (int i = 0; i < nNumIndices; i+=3)
	{
		glm::dvec3 a = vVertices[vIndexes[i]];
		glm::dvec3 b = vVertices[vIndexes[i+1]];
		glm::dvec3 c = vVertices[vIndexes[i+2]];

		glm::dvec3 normal = cross(b - a, c - a);

		vNormals[vIndexes[i]] += normal;
		vNormals[vIndexes[i+1]] += normal;
		vNormals[vIndexes[i+2]] += normal;
	}
	
	for (int i = 0;  i < vNormals.size(); i++) {
		vNormals[i] = normalize(vNormals[i]);
	}
}


// APARTADO 10
IndexMesh* IndexMesh::generateIndexedBox(GLdouble length) {


	IndexMesh* mesh = new IndexMesh();
	mesh->mNumVertices = 24; // Necesitamos vértices para cada cara por tema texturas
	mesh->nNumIndices = 36;
	mesh->mPrimitive = GL_TRIANGLES;

	GLdouble x, y, z = x = y = length / 2;

	mesh->vVertices = {
		// Front Face
		{-x, -y, -z,},  // 0 Front, Bottom, Left
		{ x, -y, -z,},  // 1 Front, Bottom, Right
		{ x,  y, -z,},  // 2 Front, Top, Right
		{-x,  y, -z,},  // 3 Front, Top, Left
		//Back Face
		{-x, -y,  z,},  // 4 Back, Bottom, Left
		{ x, -y,  z,},  // 5 Back, Bottom, Right
		{ x,  y,  z,},  // 6 Back, Top, Right
		{-x,  y,  z },  // 7 Back, Top, Left
		// Left face
		{-x, -y,  z,},  // 4 Back, Bottom, Left
		{-x, -y, -z,},  // 0 Front, Bottom, Left
		{-x,  y, -z,},  // 3 Front, Top, Left
		{-x,  y,  z },  // 7 Back, Top, Left
		// Right face
		{ x, -y, -z,},  // 1 Front, Bottom, Right
		{ x, -y,  z,},  // 5 Back, Bottom, Right
		{ x,  y,  z,},  // 6 Back, Top, Right
		{ x,  y, -z,},  // 2 Front, Top, Right
		// Top face
		{-x,  y, -z,},  // 3 Front, Top, Left
		{ x,  y, -z,},  // 2 Front, Top, Right
		{ x,  y,  z,},  // 6 Back, Top, Right
		{-x,  y,  z },  // 7 Back, Top, Left
		// Bottom face
		{-x, -y,  z,},  // 4 Back, Bottom, Left
		{ x, -y,  z,},  // 5 Back, Bottom, Right
		{ x, -y, -z,},  // 1 Front, Bottom, Right
		{-x, -y, -z,},  // 0 Front, Bottom, Left
	};

	//green
	mesh->vColors = {
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,

		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,

		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,

		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
	};

	mesh->vIndexes = {
			//front
			0,1,2,
			2,3,0,
			//back
			6,5,4,
			6,4,7,
			// Left face
			8,9,10,
			10,11,8,
			// Right face
			12,13,14,
			14,15,12,
			// Top face
			16,17,18,
			18,19,16,
			// Bottom face
			20,21,22,
			22,23,20
	};

	mesh->vTexCoords.reserve(mesh->mNumVertices);
	mesh->vTexCoords = {
		// Front face
		{0.0, 0.0},
		{1.0, 0.0},
		{1.0, 1.0},
		{0.0, 1.0},

		// Back face
		{0.0, 0.0}, 
		{1.0, 0.0}, 
		{1.0, 1.0}, 
		{0.0, 1.0}, 

		// Bottom face
		{0.0, 1.0},
		{1.0, 1.0},
		{1.0, 0.0},
		{0.0, 0.0},

		// Top face
		{0.0, 0.0},
		{1.0, 0.0},
		{1.0, 1.0},
		{0.0, 1.0},

		// Left face
		{0.0, 0.0},
		{1.0, 0.0},
		{1.0, 1.0},
		{0.0, 1.0},

		// Right face
		{0.0, 0.0},
		{1.0, 0.0},
		{1.0, 1.0},
		{0.0, 1.0}
	};

	mesh->buildNormalVectors();
	return mesh;
}


MbR* MbR::generaIndexMbR(GLuint mm, GLuint nn, glm::dvec3* perfil)
{
	MbR* mesh = new MbR();
	mesh->mNumVertices = mm * nn;
	
	mesh->mPrimitive = GL_TRIANGLES;

	// Definir la primitiva como GL_TRIANGLES
	// Definir el número de vértices como nn*mm
	// Usar un vector auxiliar de vértices
	dvec3* vs = new dvec3[mesh->mNumVertices];
	for (int i = 0; i < nn; i++) {
		// Generar la muestra i- ésima de vértices
		GLdouble theta = i * 360 / nn;
		GLdouble c = cos(radians(theta));
		GLdouble s = sin(radians(theta));

		for (int j = 0; j < mm; j++) {
			GLdouble z = -s * perfil[j].x + c * perfil[j].z;
			GLdouble x = c * perfil[j].x + s * perfil[j].z;
			vs[i] = dvec3(perfil[j].x, perfil[j].y, z);
			mesh->vVertices.push_back(dvec3(x, perfil[j].y, z));
		}
	}

	int indiceMayor = 0;
	// El contador i recorre las muestras alrededor del eje Y
	for (int i = 0; i < nn; i++){
		// El contador j recorre los vértices del perfil ,
		// de abajo arriba . Las caras cuadrangulares resultan
		// al unir la muestra i- ésima con la (i +1)% nn - ésima
		for (int j = 0; j < mm - 1; j++){
			// El contador indice sirve para llevar cuenta
			// de los índices generados hasta ahora . Se recorre
			// la cara desde la esquina inferior izquierda
			int indice = i * mm + j;
			mesh->vIndexes.push_back(indice);
			mesh->vIndexes.push_back((indice + mm) % (nn * mm));
			mesh->vIndexes.push_back((indice + mm + 1) % (nn * mm));
			mesh->vIndexes.push_back((indice + mm + 1) % (nn * mm));
			mesh->vIndexes.push_back(indice + 1);
			mesh->vIndexes.push_back(indice);

		}
	}

	mesh->nNumIndices = mesh->vIndexes.size();
	mesh->buildNormalVectors();
	return mesh;
}

//----------------------------------------------------------------------------------------------
// Atalaya
//----------------------------------------------------------------------------------------------
MbR* MbR::generaIndexAtalaya(GLuint mm, GLuint nn, glm::dvec3* perfil)
{
	MbR* mesh = MbR::generaIndexMbR(mm, nn, perfil);

	mesh->vTexCoords.reserve(mesh->mNumVertices);

	// Añadimos las textcoords
	for (GLuint i = 0; i < nn; ++i) {
		GLdouble u = static_cast<GLdouble>(i) / (nn - 1); // Asegúrate de que 'u' esté en el rango [0, 1]
		for (GLuint j = 0; j < mm; ++j) {
			GLdouble v = static_cast<GLdouble>(j) / (mm - 1); // Calcula el valor de 'v'
			mesh->vTexCoords.push_back(dvec2(u, v));
		}
	}

	return mesh;
}

//----------------------------------------------------------------------------------------------
// Tejado
//----------------------------------------------------------------------------------------------
IndexMesh* IndexMesh::generateIndexedPiramid(GLdouble length) {


	IndexMesh* mesh = new IndexMesh();
	mesh->mNumVertices = 16; // Necesitamos vértices para cada cara por tema texturas
	mesh->nNumIndices = 18;
	mesh->mPrimitive = GL_TRIANGLES;

	GLdouble x, y, z = x = y = length / 2;

	mesh->vVertices = {
		// Front Face
		{-x,   -y,  -z, },  // 0 Front, Bottom, Left
		{ x,   -y,  -z, },  // 1 Front, Bottom, Right
		{ 0,    y,  0,  },   // 2 Front, Top
		//Back Face
		{ x,   -y,  z,  },  // 3 Back, Bottom, Right
		{-x,   -y,  z,  },  // 4 Back, Bottom, Left
		{ 0,    y,  0,  },  // 5 Front, Top
		// Left face
		{-x,   -y,  z,  },  // 6 Back, Bottom, Left
		{-x,   -y, -z,  },  // 7 Front, Bottom, Left
		{ 0,    y,  0,  },  // 8 Front, Top
		// Right face
		{ x,   -y, -z,  },  // 9 Front, Bottom, Right
		{ x,   -y,  z,  },  // 10 Back, Bottom, Right
		{ 0,    y,  0,  },  // 11 Front, Top
		// Bottom face
		{-x,   -y,  z,  },  // 12 Back, Bottom, Left
		{ x,   -y,  z,  },  // 13 Back, Bottom, Right
		{ x,   -y, -z,  },  // 14 Front, Bottom, Right
		{-x,   -y,  -z,  }, // 15 Front, Bottom, Left

	};

	//green
	mesh->vColors = {
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,

		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,
		{1.0 , 1.0 , 1.0 , 1.0} ,

	};

	mesh->vIndexes = {
		//front
		0,1,2,
		//back
		3,4,5,
		// Left face
		6,7,8,
		// Right face
		9,10,11,
		// Bottom face
		12,13,14,
		14,15,12
	};

	mesh->vTexCoords.reserve(mesh->mNumVertices);
	mesh->vTexCoords = {
		// Front face
		{0.0, 0.0},
		{1.0, 0.0},
		{0.5, 1.0},

		// Back face
		{0.0, 0.0},
		{1.0, 0.0},
		{0.5, 1.0},

		// Left face
		{0.0, 0.0},
		{1.0, 0.0},
		{0.5, 1.0},

		// Right face
		{0.0, 0.0},
		{1.0, 0.0},
		{0.5, 1.0},

		// Bottom face
		{0.0, 0.0},
		{1.0, 0.0},
		{1.0, 1.0},
		{0.0, 1.0}
	};

	mesh->buildNormalVectors();
	return mesh;
}

//----------------------------------------------------------------------------------------------
// Yunque
//----------------------------------------------------------------------------------------------
IndexMesh* IndexMesh::generateYunque(GLdouble length, GLdouble base, GLdouble top) {


	IndexMesh* mesh = new IndexMesh();
	mesh->mNumVertices = 24;
	mesh->nNumIndices = 36;
	mesh->mPrimitive = GL_TRIANGLES;
	//mesh->vColors.reserve(mesh->mNumVertices);
	//mesh->vVertices.reserve(mesh->mNumVertices);
	//mesh->vNormals.reserve(mesh->mNumVertices);
	//mesh->vIndexes.reserve(mesh->mNumVertices);

	GLdouble x, y, z = x = y = length / 2;

	mesh->vVertices = {
		{-x, -y, -z,},  // 0 Front, Bottom, Left
		{ x, -y, -z,},  // 1 Front, Bottom, Right
		{ x,  y, -z,},  // 2 Front, Top, Right
		{-x,  y, -z,},  // 3 Front, Top, Left
		{-x, -y,  z,},  // 4 Back, Bottom, Left
		{ x, -y,  z,},  // 5 Back, Bottom, Right
		{ x,  y,  z,},  // 6 Back, Top, Right
		{-x,  y,  z },  // 7 Back, Top, Left
	};

	//green
	mesh->vColors = {
		{0.0 , 1.0 , 0.0 , 1.0} ,
		{0.0 , 1.0 , 0.0 , 1.0} ,
		{0.0 , 1.0 , 0.0 , 1.0} ,
		{0.0 , 1.0 , 0.0 , 1.0} ,
		{0.0 , 1.0 , 0.0 , 1.0} ,
		{0.0 , 1.0 , 0.0 , 1.0} ,
		{0.0 , 1.0 , 0.0 , 1.0} ,
		{0.0 , 1.0 , 0.0 , 1.0}
	};

	mesh->vIndexes = {
		//front
		0,1,2,
		2,3,0,
		//back
		6,5,4,
		6,4,7,
		//bottom
		0,4,1,
		1,4,5,
		//top
		6,7,3,
		6,3,2,
		//left
		4,0,3,
		4,3,7,
		//right
		5,6,2,
		5,2,1 //1,5,2
	};

	mesh->buildNormalVectors();
	return mesh;
}



