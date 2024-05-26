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

	mesh->vNormals.reserve(mesh->mNumVertices);
	mesh->vNormals.push_back({0.0,1.0,0.0});
	mesh->vNormals.push_back({0.0,1.0,0.0});
	mesh->vNormals.push_back({0.0,1.0,0.0});
	mesh->vNormals.push_back({0.0,1.0,0.0});

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
	mesh->mNumVertices = 8;
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


Mesh* IndexMesh::generateCaballo()
{
	IndexMesh* mesh = new IndexMesh();

	mesh->mPrimitive = GL_TRIANGLES;


	mesh->vVertices = {

		// Cara A

		{	0.6 ,	0.0 ,	0.3		},  //0
		{	1.0 ,	0.6 ,	0.3		},  //1
		{	1.1 ,	0.9 ,	0.3		},  //2
		{	1.1 ,	1.2 ,	0.3		},  //3
		{	0.9 ,	1.7 ,	0.3		},  //4
		{	0.4 ,	2.0 ,	0.3		},  //5
		{-	0.8 ,	2.0 ,	0.3		}, 	//6
		{-	0.8 ,	1.1 ,	0.3		}, 	//7
		{-	0.4 ,	1.1 ,	0.3		}, 	//8
		{	0.2 ,	1.4 ,	0.3		},  //9
		{	0.3 ,	1.3 ,	0.3		},  //10
		{-	0.8 ,	0.4 ,	0.3		}, 	//11
		{-	0.8 ,	0.3 ,	0.3		}, 	//12
		{-	0.7 ,	0.0 ,	0.3		}, 	//13

		// Cara B


		{	0.6 ,	0.0 ,	-0.3	},	//14
		{	1.0 ,	0.6 ,	-0.3	},	//15
		{	1.1 ,	0.9 ,	-0.3	},	//16
		{	1.1 ,	1.2 ,	-0.3	},	//17
		{	0.9 ,	1.7 ,	-0.3	},	//18
		{	0.4 ,	2.0 ,	-0.3	},	//19
		{-	0.8 ,	2.0 ,	-0.3	},	//20
		{-	0.8 ,	1.1 ,	-0.3	},	//21
		{-	0.4 ,	1.1 ,	-0.3	},	//22
		{	0.2 ,	1.4 ,	-0.3	},	//23
		{	0.3 ,	1.3 ,	-0.3	},	//24
		{-	0.8 ,	0.4 ,	-0.3	},	//25
		{-	0.8 ,	0.3 ,	-0.3	},	//26
		{-	0.7 ,	0.0 ,	-0.3	},	//27
	};

	

	mesh->vIndexes = {
		//Cara A
		13,0,1,
		12,13,1,
		11,12,1,
		11,1,2,
		10,11,2,
		10,2,3,
		10,3,4,
		5,9,4,
		4,10,9,
		9,5,6,
		6,7,9,
		7,8,9,

		//Cara B
		14,27,26,
		25,14,26,
		25,15,14,
		24,15,25,
		24,17,16,
		24,16,15,
		24,18,17,
		23,18,24,
		23,19,18,
		20,19,23,
		21,20,23,
		21,23,22,

		//Puente
		0,14,15,
		0,15,1,
		1,15,16,
		1,16,2,
		2,16,17,
		2,17,3,
		3,17,18,
		3,18,4,
		4,18,19,
		4,19,5,
		5,19,20,
		5,20,6,
		6,20,21,
		6,21,7,
		21,7,8,
		8,22,21,
		22,9,8,
		22,23,9,
		9,10,24,
		9,24,23,
		10,25,24,
		10,11,25,
		11,26,25,
		11,12,26,
		12,13,26,
		13,27,26,



	};


	mesh->mNumVertices = mesh->vVertices.size();
	mesh->nNumIndices = mesh->vIndexes.size();
	mesh->buildNormalVectors();
	return mesh;
}

Mesh* IndexMesh::generateDensePlain(int& density, float textCoorRepeat)
{
	IndexMesh* mesh = new IndexMesh();

	mesh->mPrimitive = GL_TRIANGLES;

	for (int i = 0; i < density; i++)
	{
		for (int j = 0; j < density; j++)
		{
			mesh->vVertices.push_back({ float(i) / float(density) - 0.5,float(j) / float(density) - 0.5,0.0 });
			//mesh->vNormals.push_back({ 0, 1, 0 });
			mesh->vTexCoords.push_back({ (float(i) / float(density)) * textCoorRepeat , (float(j) / float(density)) * textCoorRepeat });
		}
	}

	mesh->mNumVertices = mesh->vVertices.size();

	// El contador i recorre las muestras alrededor del eje Y
	for (int i = 0; i < density - 1; i++) {
		// El contador j recorre los vértices del perfil ,
		// de abajo arriba . Las caras cuadrangulares resultan
		// al unir la muestra i- ésima con la (i +1)% nn - ésima
		for (int j = 0; j < density - 1; j++) {
			// El contador indice sirve para llevar cuenta
			// de los índices generados hasta ahora . Se recorre
			// la cara desde la esquina inferior izquierda
			int topLeft = i * density + j;
			int topRight = (i + 1) * density + j;
			int bottomLeft = i * density + (j + 1);
			int bottomRight = (i + 1) * density + (j + 1);

			mesh->vIndexes.push_back(topLeft);
			mesh->vIndexes.push_back(topRight);
			mesh->vIndexes.push_back(bottomLeft);
			mesh->vIndexes.push_back(topRight);
			mesh->vIndexes.push_back(bottomRight);
			mesh->vIndexes.push_back(bottomLeft);


		}
	}

	mesh->nNumIndices = mesh->vIndexes.size();
	mesh->buildNormalVectors();

	return mesh;
}
