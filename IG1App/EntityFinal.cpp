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

	mTexturePaths = { "../bmps/atalaya.bmp" };

	std::vector<dvec3> perfil;

	GLdouble cx = 0.0;
	GLdouble cy = 0.0;

	GLdouble initialAngle = 90.0;

	// Arriba
	perfil.push_back({ rU / 2, h - (h / 10.0), 0.0 });
	perfil.push_back({ rU / 2, h, 0.0 });
	perfil.push_back({ rU, h, 0.0 });
	perfil.push_back({ rU, h - (h / 5.0), 0.0 });

	// Cilindro
	perfil.push_back({ rB, h - (h / 5.0), 0.0}); // Punto superior del perfil
	perfil.push_back({ rB, (h - (h / 5.0)) / 2.0, 0.0 }); // Punto inferior del perfil
	perfil.push_back({ rB, 0, 0.0 }); // bmp cabecera 40 píxeles

	this->mMesh = MbR::generaIndexAtalaya(perfil.size(), p, perfil.data());
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

		mTextures[0]->bind(GL_MODULATE);

		mMesh->render();

		mTextures[0]->unbind();
		glPointSize(1);
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
