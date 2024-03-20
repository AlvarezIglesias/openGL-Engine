#include "EntityPr1.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;


RegularPolygon::RegularPolygon(GLuint num, GLdouble r) 
	: Abs_Entity()
{
	mMesh = Mesh::generateRegularPolygon(num, r);
}


RegularPolygon::RegularPolygon(GLuint num, GLdouble r, dvec4 c)
	: RegularPolygon(num, r)
{
	mColor = c;
}

RegularPolygon::~RegularPolygon()
{
	delete mMesh;
	mMesh = nullptr;
};


void
RegularPolygon::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		// APARTADO 4
		glColor4d(mColor.r, mColor.g, mColor.b, mColor.a);
		mMesh->render();
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0); // Default color?
	}
}

//----------------------------------------------------------------------------------------------
// RGBTriangle
//----------------------------------------------------------------------------------------------


RGBTriangle::RGBTriangle(GLdouble r)
	: Abs_Entity()
{
	mMesh = Mesh::generateRGBTriangle(r);
	mPosition = dvec3(200, 0, 0);		// Apartado 14
}

RGBTriangle::~RGBTriangle()
{
	delete mMesh;
	mMesh = nullptr;
};

void
RGBTriangle::update() {
	time_step += 1;
	double r = 200.0;

	mPosition = dvec3(r * cos(radians(time_step)), r * sin(radians(time_step)) , 0);
	mRotation.z = -time_step;
}

void
RGBTriangle::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat 
					* mModelMat 
					* translate(dmat4(1), mPosition) 
					* rotate(dmat4(1), radians(mRotation.z), dvec3(0,0,1)); // glm matrix multiplication
		upload(aMat);

		glPolygonMode(GL_FRONT, GL_FILL);
		//APARTADO 7
		glPointSize(5); // No lo pide pero si no, no se ve.
		// glPolygonMode(GL_BACK, GL_LINE);
		glPolygonMode(GL_BACK, GL_POINT);
		mMesh->render();

		glPointSize(1);
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0); // Default color?
		glPolygonMode(GL_FRONT, GL_FILL);
	}
}

//----------------------------------------------------------------------------------------------
// RGBRectangle
//----------------------------------------------------------------------------------------------


RGBRectangle::RGBRectangle(GLdouble w, GLdouble h)
	: Abs_Entity()
{
	mMesh = Mesh::generateRGBRectangle(w, h);
}

RGBRectangle::~RGBRectangle()
{
	delete mMesh;
	mMesh = nullptr;
};

void
RGBRectangle::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);

		glPolygonMode(GL_BACK, GL_FILL);
		glPointSize(5); // No lo pide pero si no, no se ve.

		glPolygonMode(GL_FRONT, GL_LINE);
		mMesh->render();


		glPointSize(1);
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0); // Default color?
		glPolygonMode(GL_FRONT, GL_FILL);
	}
}


//----------------------------------------------------------------------------------------------
// Cube
//----------------------------------------------------------------------------------------------


Cube::Cube(GLdouble length)
	: Abs_Entity()
{
	mMesh = Mesh::generateCube(length);
}

Cube::~Cube()
{
	delete mMesh;
	mMesh = nullptr;
};

void
Cube::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);

		glColor4d(0.0, 0.0, 0.0, 0.0); // Default color?


		glPointSize(5); // No lo pide pero si no, no se ve.
		glPolygonMode(GL_BACK, GL_POINT);

		glPolygonMode(GL_FRONT, GL_LINE);
		mMesh->render();


		glPointSize(1);
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0); // Default color?
		glPolygonMode(GL_FRONT, GL_FILL);
	}
}


//----------------------------------------------------------------------------------------------
// Cube
//----------------------------------------------------------------------------------------------


RGBCube::RGBCube(GLdouble length)
	: Abs_Entity()
{
	mMesh = Mesh::generateRGBCube(length);
	mPosition = dvec3(100, 100, -100);
}

RGBCube::~RGBCube()
{
	delete mMesh;
	mMesh = nullptr;
};

void
RGBCube::update() {

	switch (mode)
	{
		case 0:
			mRotation.x += 1;
			if (mRotation.x >= 180) mode = 1;
			break;
		case 1:
			mRotation.z -= 1;
			if (mRotation.z <= -180) mode = 2;
			break;
		case 2:
			mRotation.y -= 1;
			if (mRotation.y <= -180) {
				mode = 0;
				mRotation = dvec3(0);
			}
			break;

		default:
			break;
	}


	//printf("%f, %f, %f \n", mRotation.x, mRotation.y, mRotation.z);

}

void
RGBCube::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		//Apartado 17
		//Importante orden de operaciones
		dmat4 aMat = modelViewMat
			* mModelMat
			* rotate(dmat4(1), radians(mRotation.x), dvec3(1, 0, 0))
			* rotate(dmat4(1), radians(mRotation.y), dvec3(0, 1, 0))
			* rotate(dmat4(1), radians(mRotation.z), dvec3(0, 0, 1)) // glm matrix multiplication
			* translate(dmat4(1), mPosition);

		upload(aMat);

		glColor4d(0.0, 0.0, 0.0, 0.0); // Default color?


		glPointSize(5); // No lo pide pero si no, no se ve.
		glPolygonMode(GL_BACK, GL_POINT);

		glPolygonMode(GL_FRONT, GL_FILL);
		mMesh->render();


		glPointSize(1);
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0); // Default color?
		glPolygonMode(GL_FRONT, GL_FILL);
	}
}