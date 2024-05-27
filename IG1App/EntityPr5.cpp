#include "EntityPr5.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

Cone::Cone(GLdouble h, GLdouble r, GLuint n) {
	// h= altura del cono , r= radio de la base
	// n= n�mero de muestras , m= n�mero de puntos del perfil
	int m = 3;
	dvec3* perfil = new dvec3[m];
	perfil[0] = dvec3(0.5, 0.0, 0.0);
	perfil[1] = dvec3(r, 0.0, 0.0);
	perfil[2] = dvec3(0.5, h, 0.0);
	this->mMesh = MbR::generaIndexMbR(m, n, perfil);

	delete[] perfil;
}


void Cone::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {

		dmat4 aMat = complete_transform(modelViewMat);

		upload(aMat);

		glColor4d(1.0, 1.0, 1.0, 0.5);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		mMesh->render();

		
		glPointSize(1);
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glPolygonMode(GL_FRONT, GL_FILL);
	}
}


RevSphere::RevSphere(GLdouble r, GLuint m, GLuint n) : EntityWithMaterial() {
	
	std::vector<dvec3> perfil;
	//dvec3* perfil = new dvec3[m+1];

	GLdouble cx = 0.0;
	GLdouble cy = 0.0;

	GLdouble step = 180.0 / GLdouble(m);
	GLdouble initialAngle = 90.0;
	for (int i = 0; i < m+1; i++)
	{
		GLdouble currentAngle = initialAngle + step * i;
		GLdouble alpha = radians(currentAngle);

		GLdouble x = cx + r * glm::cos(alpha);
		GLdouble y = cy + r * glm::sin(alpha);
		perfil.push_back({ x, y, 0.0 });
	}

	//this->mMesh = MbR::generaIndexMbR(m+1, n, perfil);
	this->mMesh = MbR::generaIndexTextCords(perfil.size(), n, perfil.data());
}


void RevSphere::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {

		dmat4 aMat = complete_transform(modelViewMat);

		upload(aMat);

		if (mTexturePaths.size() > 0) { mTextures[0]->bind(GL_MODULATE);}

		if (material != nullptr) {
			glDisable(GL_COLOR_MATERIAL);
			glColor4d(1.0, 1.0, 1.0, 1.0);
			material->upload();
			//glColorMaterial(GL_NONE, GL_AMBIENT);
		}

		else {
			//glEnable(GL_COLOR_MATERIAL);
			glColor4d(mColor[0], mColor[1], mColor[2], mColor[3]);
		}

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		mMesh->render();

		if (mTexturePaths.size() > 0) { mTextures[0]->unbind(); }

		glEnable(GL_COLOR_MATERIAL);
		glPointSize(1);
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}



Toroid::Toroid(GLdouble r, GLdouble R, GLuint m, GLuint p) : EntityWithMaterial() {

	dvec3* perfil = new dvec3[m + 1];

	GLdouble cx = 0.0;
	GLdouble cy = 0.0;

	GLdouble step = 360.0 / GLdouble(m);
	GLdouble initialAngle = 90.0;
	for (int i = 0; i < m + 1; i++)
	{
		GLdouble currentAngle = initialAngle + step * i;
		GLdouble alpha = radians(currentAngle);

		GLdouble x = cx + r * glm::cos(alpha) + R;
		GLdouble y = cy + r * glm::sin(alpha);
		perfil[i] = { x, y, 0.0 };
	}

	this->mMesh = MbR::generaIndexMbR(m + 1, p, perfil);

	delete[] perfil;
}


void Toroid::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {

		dmat4 aMat = complete_transform(modelViewMat);

		upload(aMat);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		if (material != nullptr) {
			glDisable(GL_COLOR_MATERIAL);
			glColor4d(1.0, 1.0, 1.0, 1.0);
			material->upload();
			//glColorMaterial(GL_NONE, GL_AMBIENT);
		}

		else {
			//glEnable(GL_COLOR_MATERIAL);
			glColor4d(mColor[0], mColor[1], mColor[2], mColor[3]);
		}

		mMesh->render();

		glEnable(GL_COLOR_MATERIAL);
		glPointSize(1);
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
