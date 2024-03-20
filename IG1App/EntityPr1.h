#pragma once


#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "Entity.h"
#include "Mesh.h"


// APARTADO 3
class RegularPolygon : public Abs_Entity
{
public:
	~RegularPolygon();
	explicit RegularPolygon(GLuint num, GLdouble r) ;
	explicit RegularPolygon(GLuint num, GLdouble r, glm::dvec4 c) ;

	virtual void render(glm::dmat4 const& modelViewMat) const;
	

private:

};

// APARTADO 6
class RGBTriangle : public Abs_Entity
{
public:
	~RGBTriangle();
	explicit RGBTriangle(GLdouble r);
	virtual void render(glm::dmat4 const& modelViewMat) const;
	void update();


private:

	double time_step = 0;

};

// APARTADO 8
class RGBRectangle : public Abs_Entity
{
public:
	~RGBRectangle();
	explicit RGBRectangle(GLdouble w, GLdouble h);
	virtual void render(glm::dmat4 const& modelViewMat) const;


private:

};


// APARTADO 9
class Cube : public Abs_Entity
{
public:
	~Cube();
	explicit Cube(GLdouble length);
	virtual void render(glm::dmat4 const& modelViewMat) const;


private:

};

// APARTADO 10
class RGBCube : public Abs_Entity
{
public:
	~RGBCube();
	explicit RGBCube(GLdouble length);
	virtual void render(glm::dmat4 const& modelViewMat) const;
	void update() ;


private:

	int mode = 0;
};

