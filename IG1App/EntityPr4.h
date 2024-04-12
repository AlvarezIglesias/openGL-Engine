#pragma once


#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
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
	explicit Cylinder(GLdouble ru, GLdouble rd, GLdouble h);
	virtual void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble ru, rd, h;
};

class Disk : public QuadricEntity
{
public:
	explicit Disk(GLdouble rri, GLdouble rro);
	virtual void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble ri, ro;
};

class PartialDisk : public QuadricEntity
{
public:
	explicit PartialDisk(GLdouble rri, GLdouble rro);
	virtual void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble ri, ro;
};

// APARTADO 59
class CompoundEntity : public Abs_Entity {
public:
	~CompoundEntity();
	void addEntity(Abs_Entity* ae);
	virtual void render(glm::dmat4 const& modelViewMat) const;
protected:
	std::vector<Abs_Entity*> gObjects;
};

