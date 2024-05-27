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
	  : mModelMat(1.0), mColor(1), mPosition(0), mRotation(0), mScale(1){}; // 4x4 identity matrix
	virtual ~Abs_Entity() {
		if(mMesh != nullptr){
		delete mMesh;
		mMesh = nullptr;
		}
	};;

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

	glm::dmat4 complete_transform(glm::dmat4 const& modelViewMat) const;

	virtual void initTextures(std::vector<Texture*>& sceneTextures);
	std::vector<std::string> mTexturePaths;
	void addTexturePath(std::string path) { mTexturePaths.push_back(path); };


	std::string name = "Entity";
	glm::dvec3 mPosition;
	glm::dvec3 mRotation;
	glm::dvec3 mScale;
	glm::dvec4 mColor;	   // APARTADO 4 


protected:
	Mesh* mMesh = nullptr; // the mesh
	glm::dmat4 mModelMat;  // modeling matrix

	std::vector<Texture*> mTextures;

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
