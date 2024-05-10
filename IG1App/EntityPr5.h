#pragma once


#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include "Entity.h"
#include "Mesh.h"





class Cone : public Abs_Entity
{
public:
	~Cone() {};
	explicit Cone(GLdouble h, GLdouble r, GLuint n);
	virtual void render(glm::dmat4 const& modelViewMat) const;
};


class RevSphere : public Abs_Entity
{
public:
	~RevSphere() {};
	explicit RevSphere(GLdouble r, GLuint m, GLuint n);
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Toroid : public Abs_Entity
{
public:
	~Toroid() {};
	explicit Toroid(GLdouble r, GLdouble R, GLuint m, GLuint p) ;
	virtual void render(glm::dmat4 const& modelViewMat) const;
};