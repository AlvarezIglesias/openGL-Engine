#include "EntityPr5.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "EntityPrFinal.h"

using namespace glm;

Peon::Peon()
{
	std::vector<dvec3> perfil;
	GLdouble cx = 0.0;
	GLdouble cy = 0.0;
	GLdouble r = 1.0;

	GLdouble step = 180.0 / GLdouble(10);
	GLdouble initialAngle = 90.0;
	for (int i = 0; i < 10 ; i++)
	{
		GLdouble currentAngle = initialAngle + step * i;
		GLdouble alpha = radians(currentAngle);

		GLdouble x = cx + r * glm::cos(alpha);
		GLdouble y = cy + r * glm::sin(alpha);
		perfil.push_back({x, y, 0.0});
	}

	// y positivo arriba
	// x positivo derecha

	perfil.push_back(perfil.back() + dvec3(1, 0, 0));
	perfil.push_back(perfil.back() + dvec3(0.5, -0.3, 0));
	perfil.push_back(perfil.back() + dvec3(0, -0.3, 0));
	perfil.push_back(perfil.back() + dvec3(-0.5, -0.3, 0));
	perfil.push_back(perfil.back() + dvec3(0.2, -2.5, 0));
	perfil.push_back(perfil.back() + dvec3(0.4, -0.5, 0));
	perfil.push_back(perfil.back() + dvec3(0.8, -0.2, 0));
	perfil.push_back(perfil.back() + dvec3(0.2, -1, 0));




	this->mMesh = MbR::generaIndexMbR(perfil.size(), 100, perfil.data());
}

void Peon::render(glm::dmat4 const& modelViewMat) const
{

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
