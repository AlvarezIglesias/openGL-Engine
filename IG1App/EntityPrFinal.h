#pragma once


#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include "EntityPr4.h"
#include "EntityPr5.h"
#include "Texture.h"

class ChessBoard : public EntityWithMaterial
{
public:
	~ChessBoard() {};
	explicit ChessBoard();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Peon : public EntityWithMaterial
{
public:
	~Peon() {};
	explicit Peon();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Torre : public EntityWithMaterial
{
public:
	~Torre() {};
	explicit Torre();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Alfil : public EntityWithMaterial
{
public:
	~Alfil() {};
	explicit Alfil();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Reina : public EntityWithMaterial
{
public:
	~Reina() {};
	explicit Reina();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Rey : public EntityWithMaterial
{
public:
	~Rey() {};
	explicit Rey();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};


class BaseCaballo : public EntityWithMaterial
{
public:
	~BaseCaballo() {};
	explicit BaseCaballo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};


class CabezaCaballo : public EntityWithMaterial
{
public:
	~CabezaCaballo() {};
	explicit CabezaCaballo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Caballo : public CompoundEntity
{
public:
	~Caballo() {};
	explicit Caballo();
};


class PantallaFlexo : public EntityWithMaterial
{
public:
	static SpotLight* spotLight;
	~PantallaFlexo() {};
	explicit PantallaFlexo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	float counter = 0.0;
	void update();

};

class Luz : public QuadricEntity
{
public:
	explicit Luz(GLdouble ru, GLdouble rd, GLdouble h);
	virtual void render(glm::dmat4 const& modelViewMat) const;
	void initTextures(std::vector<Texture*>& sceneTextures);
protected:
	GLdouble ru, rd, h;
};

class Eje : public CompoundEntity
{
public:
	~Eje(){};
	Eje(float _apertura, float _inicial, float _desfase) : apertura(_apertura), inicial(_inicial), desfase(_desfase) {};
	void update();

private:
	float counter = 0.0;
	float apertura = 0.0;
	float inicial = 0.0;
	float desfase = 0.0;
};

class DensePlain : public EntityWithMaterial
{
public:
	~DensePlain() {};
	explicit DensePlain(int& density, float textCoorRepeat = 1.0);
	virtual void render(glm::dmat4 const& modelViewMat) const;
};