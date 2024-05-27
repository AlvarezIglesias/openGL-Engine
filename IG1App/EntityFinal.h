#pragma once

#include "EntityPr5.h"

//----------------------------------------------------------------------------------------------
// Atalaya
//----------------------------------------------------------------------------------------------
class Atalaya : public EntityWithMaterial
{
public:
	~Atalaya() {};
	explicit Atalaya(GLdouble rU, GLdouble rB, GLdouble h, GLuint m, GLuint p);
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//----------------------------------------------------------------------------------------------
// IndexedBoxWithMaterial
//----------------------------------------------------------------------------------------------
class IndexedBoxWithMaterial : public EntityWithMaterial {
public:
	IndexedBoxWithMaterial(int m);
	~IndexedBoxWithMaterial() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//----------------------------------------------------------------------------------------------
// IndexedPiramidWithMaterial
//----------------------------------------------------------------------------------------------
class IndexedPiramidWithMaterial : public EntityWithMaterial {
public:
	IndexedPiramidWithMaterial(int m);
	~IndexedPiramidWithMaterial() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//----------------------------------------------------------------------------------------------
// GroundWithMaterial
//----------------------------------------------------------------------------------------------
class GroundWithMaterial : public EntityWithMaterial
{
public:
	~GroundWithMaterial();
	explicit GroundWithMaterial(GLdouble w, GLdouble h);
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//----------------------------------------------------------------------------------------------
// Casa
//----------------------------------------------------------------------------------------------
class Casa : public CompoundEntity {
public:
	Casa(int m, bool fa = false);
	~Casa() {}

	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
	void enableLight();
	void disableLight();
};

//----------------------------------------------------------------------------------------------
// RevCilinder
//----------------------------------------------------------------------------------------------
class RevCilinder : public EntityWithMaterial
{
public:
	~RevCilinder() {};
	explicit RevCilinder(GLdouble r, GLdouble h, GLuint m, GLuint p);
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//----------------------------------------------------------------------------------------------
// QuadricWithMaterialEntity
//----------------------------------------------------------------------------------------------
class QuadricWithMaterialEntity : public EntityWithMaterial {
public:
	QuadricWithMaterialEntity() : EntityWithMaterial() { q = gluNewQuadric(); };
	~QuadricWithMaterialEntity() { gluDeleteQuadric(q); };
protected:
	GLUquadricObj* q;
};

//----------------------------------------------------------------------------------------------
// DiskWithMaterial
//----------------------------------------------------------------------------------------------
class DiskWithMaterial : public QuadricWithMaterialEntity
{
public:
	explicit DiskWithMaterial(GLdouble rri, GLdouble rro);
	virtual void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble ri, ro;
};

//----------------------------------------------------------------------------------------------
// Farolillo
//----------------------------------------------------------------------------------------------

class Farolillo : public CompoundEntity {
public:
	Farolillo(int m);
	~Farolillo() {
		delete light;
		light = nullptr;
	}

	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
	void enableLight();
	void disableLight();

protected:
	PosLight* light;
	int period = 0;
	bool color = true; // true = red, false = yellow
};

//----------------------------------------------------------------------------------------------
// Luna
//----------------------------------------------------------------------------------------------
class Luna : public CompoundEntity {
public:
	Luna(double r);
	~Luna() {
		delete light;
		light = nullptr;
	};
	void update();
	void enableLight();
	void disableLight();
	virtual void render(glm::dmat4 const& modelViewMat) const;

protected:
	SpotLight* light;
};

//----------------------------------------------------------------------------------------------
// IndexedOpenBox
//----------------------------------------------------------------------------------------------
class IndexedOpenBox : public EntityWithMaterial {
public:
	IndexedOpenBox(int m);
	~IndexedOpenBox() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//----------------------------------------------------------------------------------------------
// Carromato
//----------------------------------------------------------------------------------------------
class Carromato : public CompoundEntity {
public:
	Carromato(int m);
	~Carromato() {}

	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();

protected:
	bool incrementando = true;
};
