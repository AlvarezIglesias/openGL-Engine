#pragma once


#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>

#include "EntityPr4.h"
#include "Texture.h"

// Apartado 74
class EntityWithMaterial : public Abs_Entity {
public:
	EntityWithMaterial() : Abs_Entity() { };
	virtual ~EntityWithMaterial() { };
	void setMaterial(Material* matl) { material = matl; };
protected:
	Material* material = nullptr;
};

class Cone : public Abs_Entity
{
public:
	~Cone() {};
	explicit Cone(GLdouble h, GLdouble r, GLuint n);
	virtual void render(glm::dmat4 const& modelViewMat) const;
};


class RevSphere : public EntityWithMaterial
{
public:
	~RevSphere() {};
	explicit RevSphere(GLdouble r, GLuint m, GLuint n);
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Toroid : public EntityWithMaterial
{
public:
	~Toroid() {};
	explicit Toroid(GLdouble r, GLdouble R, GLuint m, GLuint p) ;
	virtual void render(glm::dmat4 const& modelViewMat) const;
};