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