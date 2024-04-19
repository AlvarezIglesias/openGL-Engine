#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Mesh.h"
#include "Texture.h"

class Abs_Entity // abstract class
{
public:
	Abs_Entity()
	  : mModelMat(1.0), mColor(1), mPosition(0), mRotation(0){}; // 4x4 identity matrix
	virtual ~Abs_Entity() = default;

	Abs_Entity(const Abs_Entity& e) = delete;            // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete; // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0; // abstract method

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };

	//APARTADO 4
	glm::dvec4 getMColor() { return mColor; }
	glm::dvec4 getMColor(glm::dvec4 _mColor) { mColor = _mColor; }

	// APARTADO 13
	virtual void update() {};

	// APARTADO 19
	void setTexture1(Texture* aText) { mTexture1 = aText; };
	void setTexture2(Texture* aText) { mTexture2 = aText; };

	std::string mTexture1Path = "";
	std::string mTexture2Path = "";

protected:
	Mesh* mMesh = nullptr; // the mesh
	glm::dmat4 mModelMat;  // modeling matrix
	glm::dvec4 mColor;	   // APARTADO 4

	glm::dvec3 mPosition;	   // APARTADO 14, position
	glm::dvec3 mRotation;	   // APARTADO 14, rotation

	Texture* mTexture1 = nullptr;
	Texture* mTexture2 = nullptr;

	// transfers modelViewMat to the GPU
	virtual void upload(glm::dmat4 const& mModelViewMat) const;
};

class EjesRGB : public Abs_Entity
{
public:
	explicit EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

#endif //_H_Entities_H_
