#include "EntityFinal.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

//----------------------------------------------------------------------------------------------
// Yunque
//----------------------------------------------------------------------------------------------

Yunque::Yunque() {
	mMesh = IndexMesh::generateIndexedBox(200);
}

void
Yunque::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = complete_transform(modelViewMat);
	upload(aMat);

	glPolygonMode(GL_BACK, GL_FILL);
	mMesh->render();

	glPointSize(1);
	glLineWidth(1);
	glColor4d(1.0, 1.0, 1.0, 1.0);
	glPolygonMode(GL_FRONT, GL_FILL);
}

//----------------------------------------------------------------------------------------------
// Atalaya
//----------------------------------------------------------------------------------------------

Atalaya::Atalaya(GLdouble rU, GLdouble rB, GLdouble h, GLuint m, GLuint p) {

	dvec3* perfil = new dvec3[m + 1];

	GLdouble cx = 0.0;
	GLdouble cy = 0.0;

	GLdouble step = 360.0 / GLdouble(m);
	GLdouble initialAngle = 90.0;
	
	perfil[0] = { 0.0, h / 2.0, rB }; // Punto superior del perfil
	perfil[1] = { 0.0, -h / 2.0, rB }; // Punto inferior del perfil

	this->mMesh = MbR::generaIndexMbR(m + 1, p, perfil);
}

/* Plato?
	for (GLuint i = 0; i < m + 1; i++) {
		GLdouble currentAngle = initialAngle + step * i;
		GLdouble alpha = glm::radians(currentAngle);

		// Radio en la base y en la cima
		GLdouble t = (GLdouble)i / (GLdouble)m;
		GLdouble r = (1.0 - t) * rB + t * rU;

		// Coordenadas x e y
		GLdouble x = cx + r * glm::cos(alpha);
		GLdouble y = cy + r * glm::sin(alpha);
		GLdouble z = t * h;

		perfil[i] = { x, y, z };
	}
*/

void Atalaya::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {

		dmat4 aMat = complete_transform(modelViewMat);

		upload(aMat);

		glColor4d(mColor[0], mColor[1], mColor[2], mColor[3]);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		mMesh->render();

		glPointSize(1);
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
