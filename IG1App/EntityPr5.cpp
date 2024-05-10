#include "Entity.h"
#include "EntityPr4.h"
#include "EntityPr5.h"
#include "EntityPr1.h"
#include "Texture.h"
#include "Light.h"

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


RevSphere::RevSphere(GLdouble r, GLuint m, GLuint n) {
	
	dvec3* perfil = new dvec3[m+1];

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
		perfil[i] = { x, y, 0.0 };
	}

	this->mMesh = MbR::generaIndexMbR(m+1, n, perfil);
}


void RevSphere::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {

		dmat4 aMat = complete_transform(modelViewMat);

		upload(aMat);

		glColor4d(1.0, 1.0, 1.0, 0.5);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		mMesh->render();


		glPointSize(1);
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glPolygonMode(GL_FRONT, GL_FILL);
	}
}



Toroid::Toroid(GLdouble r, GLdouble R, GLuint m, GLuint p) {

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
}


void Toroid::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {

		dmat4 aMat = complete_transform(modelViewMat);

		upload(aMat);

		glColor4d(1.0, 1.0, 1.0, 0.5);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		mMesh->render();


		glPointSize(1);
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glPolygonMode(GL_FRONT, GL_FILL);
	}
}
// Apartado 73
class EntityWithMaterial : public Abs_Entity {
public:
	EntityWithMaterial() : Abs_Entity() { };
	virtual ~EntityWithMaterial() { };
	void setMaterial(Material* matl) { material = matl; };
protected:
	Material* material = nullptr;
};
