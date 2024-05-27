#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include <vector>

class Mesh
{
public:
	static Mesh* createRGBAxes(GLdouble l); // creates a new 3D-RGB axes mesh

	Mesh() = default;
	virtual ~Mesh() = default;

	Mesh(const Mesh& m) = delete;            // no copy constructor
	Mesh& operator=(const Mesh& m) = delete; // no copy assignment

	virtual void render() const;

	GLuint size() const { return mNumVertices; }; // number of elements
	std::vector<glm::dvec3> const& vertices() const { return vVertices; };
	std::vector<glm::dvec4> const& colors() const { return vColors; };

	// APARTADO 2
	static Mesh* generateRegularPolygon(GLuint num, GLdouble r);
	// APARTADO 6
	static Mesh* generateRGBTriangle(GLdouble r);
	// APARTADO 8
	static Mesh* generateRectangle(GLdouble w, GLdouble h);
	static Mesh* generateRGBRectangle(GLdouble w, GLdouble h);
	// APARTADO 9
	static Mesh* generateCube(GLdouble length);
	// APARTADO 10
	static Mesh* generateRGBCube(GLdouble length);

	/******************************* PARTE 2 *******************************/

	// Apartado 19
	static Mesh* generateRectangleTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	static Mesh* generateBoxOutline(GLdouble length);

	// Apartado 25
	static Mesh* generateStar3D(GLdouble re, GLuint np, GLdouble h);

	// Apartado 28
	static Mesh* generateStar3DTexCor(GLdouble re, GLuint np, GLdouble h);

	/******************************** PARTE 4 ******************************/

	static Mesh* generateWingAdvancedTIE(GLdouble w, GLdouble h);




protected:
	GLuint mPrimitive =
	  GL_TRIANGLES;          // graphic primitive: GL_POINTS, GL_LINES, GL_TRIANGLES, ...
	GLuint mNumVertices = 0; // number of elements ( = vVertices.size())
	std::vector<glm::dvec3> vVertices; // vertex array
	std::vector<glm::dvec4> vColors;   // color array
	std::vector<glm::dvec2> vTexCoords;   // coords array
	std::vector<glm::dvec3> vNormals; // APARTADO 61 // Vectores normales
	virtual void draw() const;
};

// INDEX MESH

// Apartado 62
class IndexMesh : public Mesh {
public:
	//~IndexMesh() = default;
	GLuint index_size() const { return nNumIndices; }; // number of elements
	std::vector<GLuint> const& indices() const { return vIndexes; };

	static IndexMesh* generateIndexedBox(GLdouble length);
	glm::dvec3 buildNormalVectors(int init);

	/******************************** PARTE FINAL ******************************/

	static Mesh* generateCaballo();
	static Mesh* generateDensePlain(const int& density, float textCoorRepeat = 1.0);


protected:
	void draw() const;
	void buildNormalVectors();
	GLuint nNumIndices = 0;
	std::vector<GLuint> vIndexes;
};

// APARTADO 69
class MbR : public IndexMesh
{
public:
	//~MbR() = default;
	static Mesh* generaIndexMbR(GLuint mm, GLuint mn, glm::dvec3* perfil);

protected:


};



#endif //_H_Scene_H_
