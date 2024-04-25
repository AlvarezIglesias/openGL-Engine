#pragma once


#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include "Entity.h"
#include "Mesh.h"

// APARTADO 57
class QuadricEntity : public Abs_Entity {
public:
	QuadricEntity() { q = gluNewQuadric(); };
	~QuadricEntity() { gluDeleteQuadric(q); };
protected:
	GLUquadricObj* q;
};

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
	void addEntity(std::vector<Abs_Entity*>& aes);
	virtual void render(glm::dmat4 const& modelViewMat) const;
	void initTextures(std::vector<Texture*>& sceneTextures);
protected:
	std::vector<Abs_Entity*> gObjects;
};

// APARTADO 60
class WingAdvancedTIE : public Abs_Entity {
public:
	WingAdvancedTIE(GLdouble w, GLdouble h);
	~WingAdvancedTIE() {}
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

// APARTADO 60
class AdvancedTIE : public CompoundEntity {
public:
	AdvancedTIE();
	~AdvancedTIE() {}
};

// APARTADO 64
class IndexedBox : public Abs_Entity {
public:
	IndexedBox();
	~IndexedBox() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

// APARTADO 64
class TrianguloFicticio : public CompoundEntity {
public:
	TrianguloFicticio();
	~TrianguloFicticio() {};
	void update();
};

