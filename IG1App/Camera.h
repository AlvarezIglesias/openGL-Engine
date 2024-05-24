#ifndef _H_Camera_H_
#define _H_Camera_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Viewport.h"

class Camera
{
public:
	explicit Camera(Viewport* vp);
	~Camera() = default;

	// viewPort
	Viewport const& viewPort() const { return *mViewPort; };

	// view matrix
	glm::dmat4 const& viewMat() const { return mViewMat; };

	void set2D();
	void set3D();

	void pitch(GLdouble a); // rotates a degrees on the X axis
	void yaw(GLdouble a);   // rotates a degrees on the Y axis
	void roll(GLdouble a);  // rotates a degrees on the Z axis

	void pitchReal(GLdouble a); // rotates a degrees on the X axis
	void yawReal(GLdouble a);   // rotates a degrees on the Y axis
	void rollReal(GLdouble a);  // rotates a degrees on the Z axis

	void orbit(GLdouble incAng, GLdouble incY); //APARTADO 48
	void setCenital(); //APARTADO 50

	void moveLR(GLdouble cs);
	void moveFB(GLdouble cs);
	void moveUD(GLdouble cs);

	void setEye(glm::dvec3 new_eye) { mEye = new_eye; };

	// projection matrix
	glm::dmat4 const& projMat() const { return mProjMat; };

	// sets scene visible area size
	void setSize(GLdouble xw, GLdouble yh);
	// updates the scale factor
	void setScale(GLdouble s);

	// transfers its viewport, the view matrix and projection matrix to the GPU
	void upload() const
	{
		mViewPort->upload();
		uploadVM();
		uploadPM();
	};

	// Apartado 42

	void changePrj();

	// Apartado 47
	void update();
	void setOnTriangle();

protected:
	glm::dvec3 mEye = {500.0, 500.0, 500.0}; // camera's position
	glm::dvec3 mLook = {0.0, 0.0, 0.0};  // target's position
	glm::dvec3 mUp = {0.0, 1.0, 0.0};    // the up vector

	glm::dvec3 mRight, mUpward, mFront;

	glm::dmat4 mViewMat;   // view matrix = inverse of modeling matrix
	void uploadVM() const; // transfers viewMat to the GPU

	glm::dmat4 mProjMat;   // projection matrix
	void uploadPM() const; // transfers projMat to the GPU

	GLdouble xRight, xLeft, yTop, yBot;     // size of scene visible area
	GLdouble mNearVal = 1, mFarVal = 10000; // view volume
	GLdouble mScaleFact = 1;                // scale factor
	GLdouble mFovy = 60.0;
	bool bOrto = true;                      // orthogonal or perspective projection
	GLdouble mAng = 45.0;
	GLdouble mRadio = 500.0;

	Viewport* mViewPort; // the viewport


	void setVM();
	void setPM();

	// APARTADO 40
	void setAxes();

	// APARTADO 47
	float time_step = 0;
};

#endif //_H_Camera_H_
