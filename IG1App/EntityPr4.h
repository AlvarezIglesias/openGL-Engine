#pragma once


#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "Entity.h"
#include "Mesh.h"

// APARTADO 57
class QuadricEntity : public Abs_Entity {
public:
	QuadricEntity();
	~QuadricEntity() { gluDeleteQuadric(q); };
protected:
	GLUquadricObj* q;
};
QuadricEntity::QuadricEntity() {
	q = gluNewQuadric();
}

class Sphere : public QuadricEntity {
public:
	Sphere(GLdouble r); // r es el radio de la esfera
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble r;
};


class Cylinder : public QuadricEntity
{
public:
	~Cylinder() {};
	explicit Cylinder(GLdouble ru, GLdouble rd, GLdouble h);
	virtual void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble ru, rd, h;
};

class Disk : public QuadricEntity
{
public:
	~Disk() {}
	explicit Disk(GLdouble rri, GLdouble rro);
	virtual void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble ri, ro;
};

class PartialDisk : public QuadricEntity
{
public:
	~PartialDisk();
	explicit PartialDisk(GLdouble w, GLdouble h);
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
