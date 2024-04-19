#include "Entity.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

void
Abs_Entity::upload(dmat4 const& modelViewMat) const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat)); // transfers modelView matrix to the GPU
}

dmat4 
Abs_Entity::complete_transform(dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat
		* mModelMat
		* scale(dmat4(1), mScale)
		* rotate(dmat4(1), radians(mRotation.x), dvec3(1, 0, 0))
		* rotate(dmat4(1), radians(mRotation.y), dvec3(0, 1, 0))
		* rotate(dmat4(1), radians(mRotation.z), dvec3(0, 0, 1)) // glm matrix multiplication
		* translate(dmat4(1), mPosition);

	return aMat;
}


EjesRGB::EjesRGB(GLdouble l)
  : Abs_Entity()
{
	mMesh = Mesh::createRGBAxes(l);
}

EjesRGB::~EjesRGB()
{
	delete mMesh;
	mMesh = nullptr;
};

void
EjesRGB::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
}

