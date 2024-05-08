#include "Entity.h"
#include "EntityPr4.h"
#include "EntityPr5.h"
#include "EntityPr1.h"
#include "Texture.h"

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