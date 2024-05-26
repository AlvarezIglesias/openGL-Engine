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

class ChessPiece : public EntityWithMaterial
{
public:
	~ChessPiece() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
	void update();
	bool shouldUpdate = true;
protected:
	float counter = 0;
	float phase = rand() % 360;

};

class Peon : public ChessPiece
{
public:
	~Peon() {};
	explicit Peon();
};

class Torre : public ChessPiece
{
public:
	~Torre() {};
	explicit Torre();
};

class Alfil : public ChessPiece
{
public:
	~Alfil() {};
	explicit Alfil();
};

class Reina : public ChessPiece
{
public:
	~Reina() {};
	explicit Reina();
};

class Rey : public ChessPiece
{
public:
	~Rey() {};
	explicit Rey();
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
	explicit DensePlain(const int& density, float textCoorRepeat = 1.0);
	virtual void render(glm::dmat4 const& modelViewMat) const;
};