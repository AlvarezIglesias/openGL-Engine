#pragma once


#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include "EntityPr4.h"
#include "EntityPr5.h"
#include "Texture.h"

class Peon : public EntityWithMaterial
{
public:
	~Peon() {};
	explicit Peon();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};