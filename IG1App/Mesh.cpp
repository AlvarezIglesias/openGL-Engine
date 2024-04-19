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

		draw();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
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

	// vertices
	mesh->vVertices.emplace_back(-x, -h, 0.0);
	mesh->vVertices.emplace_back(x, -h, 0.0);

	mesh->vVertices.emplace_back(-x, -h * 0.666, h * 0.333);
	mesh->vVertices.emplace_back(x, -h * 0.666, h * 0.333);

	mesh->vVertices.emplace_back(-x, -h * 0.333, h * 0.333);
	mesh->vVertices.emplace_back(x, -h * 0.333, h * 0.333);

	mesh->vVertices.emplace_back(-x, 0.0, 0.0);
	mesh->vVertices.emplace_back(x, 0.0, 0.0);

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



