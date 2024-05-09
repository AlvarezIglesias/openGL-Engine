#pragma once

#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "Entity.h"
#include "Mesh.h"

// Apartado 73
class Material {
protected:
	// Coeficientes de reflexi�n
	glm::fvec4 ambient = { 0.2 , 0.2 , 0.2 , 1.0 };
	glm::fvec4 diffuse = { 0.8 , 0.8 , 0.8 , 1.0 };
	glm::fvec4 specular = { 0.0 , 0.0 , 0.0 , 1.0 };
	GLfloat expF = 0; // Exponente para la reflexi�n especular
	GLuint face = GL_FRONT_AND_BACK;
	GLuint sh = GL_SMOOTH; // Tipo de matizado
public:
	Material() {};
	virtual ~Material() {};
	virtual void upload();
	void setCopper();
};

// Apartado 75
class Light { // Abstract class
protected:
	static GLuint cont; // Atributo para poder generar un nuevo id cada vez
	GLuint id = GL_LIGHT0 + GL_MAX_LIGHTS; // Primer id no v�lido
	// Atributos lum�nicos y geom�trico de la fuente de luz
	glm::fvec4 ambient = { 0.1 , 0.1 , 0.1 , 1 };
	glm::fvec4 diffuse = { 0.5 , 0.5 , 0.5 , 1 };
	glm::fvec4 specular = { 0.5 , 0.5 , 0.5 , 1 };
	glm::fvec4 posDir = { 0 , 0 , 1 , 0 };
	// A�ade setters para cambiar el valor de los atributos lum�nicos
public:
	Light();
	virtual ~Light() { disable(); }
	void uploadL() const;
	// M�todo abstracto
	virtual void upload(glm::dmat4 const& modelViewMat) const = 0;
	//...
	void disable();
	void enable();
	void setAmb(glm::fvec4 amb);
	void setDiff(glm::fvec4 diff);
	void setSpec(glm::fvec4 sp);
	//void setPosDir(glm::fvec4 pd);
};

// Apartado 75
class DirLight : public Light {
public:
	virtual void upload(glm::dmat4 const& modelViewMat) const;
	void setPosDir(glm::fvec3 dir);
};

// Apartado 75
class PosLight : public Light {
protected:
	// Factores de atenuaci�n
	GLfloat kc = 1, kl = 0, kq = 0;
public:
	virtual void upload(glm::dmat4 const& modelViewMat) const;
	void setPosDir(glm::fvec3 dir);
	void setAtte(GLfloat kc, GLfloat kl, GLfloat kq);
};

// Apartado 75
class SpotLight : public PosLight {
protected:
	// Atributos del foco
	glm::fvec4 direction = { 0 , 0 , -1 , 0 };
	GLfloat cutoff = 180;
	GLfloat exp = 0;
public:
	SpotLight(glm::fvec3 pos = { 0 , 0 , 0 }) : PosLight() {
		posDir = glm::fvec4(pos, 1.0);
	};
	virtual void upload(glm::dmat4 const& modelViewMat) const;
	void setSpot(glm::fvec3 dir, GLfloat cf, GLfloat e);
};
