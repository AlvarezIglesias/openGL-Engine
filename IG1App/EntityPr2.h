#pragma once


#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "Entity.h"
#include "Mesh.h"

// APARTADO 18
class Ground : public Abs_Entity
{
public:
	~Ground();
	explicit Ground(GLdouble w, GLdouble h);
	virtual void render(glm::dmat4 const& modelViewMat) const;
};



// APARTADO 22
class BoxOutline : public Abs_Entity
{
public:
	~BoxOutline();
	explicit BoxOutline(GLdouble length);
	virtual void render(glm::dmat4 const& modelViewMat) const;
};


// APARTADO 25
class Star3D : public Abs_Entity
{
public:
	~Star3D();
	explicit Star3D(GLdouble re, GLuint np, GLdouble h);
	void update();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};



// APARTADO 25
class GlassParapet : public Abs_Entity
{
public:
	~GlassParapet();
	explicit GlassParapet(GLdouble length);
	virtual void render(glm::dmat4 const& modelViewMat) const;

protected:
	double length;
};

// APARTADO 36
class Photo : public Abs_Entity
{
public:
	~Photo();
	explicit Photo(GLdouble w, GLdouble h);
	virtual void render(glm::dmat4 const& modelViewMat) const;
	void update();

	void save(const std::string filename) const;
};


// APARTADO 29 (Opcional)
class Box : public Abs_Entity
{
public:
	~Box();
	explicit Box(GLdouble length);
	void update();
	virtual void render(glm::dmat4 const& modelViewMat) const;

protected:
	double length;
	double lidRotation = 0.0;

	glm::dmat4 mModelMatTopLid = glm::dmat4(1);
	glm::dmat4 mModelMatBotLid = glm::dmat4(1);

	Mesh* mMeshTopLid = nullptr; // the mesh
	Mesh* mMeshBotLid = nullptr; // the mesh


};

// APARTADO 34
class Grass : public Abs_Entity
{
public:
	~Grass();
	explicit Grass(GLdouble w, GLdouble h);
	virtual void render(glm::dmat4 const& modelViewMat) const;
};