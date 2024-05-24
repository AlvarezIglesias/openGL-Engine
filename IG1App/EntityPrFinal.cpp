#include "EntityPr5.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "EntityPrFinal.h"

using namespace glm;

ChessBoard::ChessBoard()
{
	mTexturePaths = { "../bmps/chessBoard.bmp" };
	mMesh = Mesh::generateRectangleTexCor(1, 1, 1, 1);
	mRotation = dvec3(90, 0, 90);
}

void ChessBoard::render(glm::dmat4 const& modelViewMat) const
{

	if (mMesh != nullptr) {

		dmat4 aMat = complete_transform(modelViewMat);

		upload(aMat);

		glColor4d(1.0, 1.0, 1.0, 1.0);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		mTextures[0]->bind(GL_REPLACE);

		mMesh->render();

		mTextures[0]->unbind();
		glPointSize(1);
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glPolygonMode(GL_FRONT, GL_FILL);
	}
}


Peon::Peon()
{
	std::vector<dvec3> perfil;

	// y positivo arriba
	// x positivo derecha

	perfil.push_back(dvec3(0, 0, 0));
	perfil.push_back(perfil.back() + dvec3(1.5, 0, 0));
	perfil.push_back(perfil.back() + dvec3(0, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(-0.1, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.1, 0));
	perfil.push_back(perfil.back() + dvec3(0.0, 0.3, 0));
	perfil.push_back(perfil.back() + dvec3(-0.3, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(0.0, 0.5, 0));
	perfil.push_back(perfil.back() + dvec3(-0.4, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(-0.2, 0.5, 0));
	perfil.push_back(perfil.back() + dvec3(0, 0.5, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.5, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(0, 0.2, 0));//bump
	perfil.push_back(perfil.back() + dvec3(-0.2, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(+0.2, 0.2, 0));//end bump
	perfil.push_back(perfil.back() + dvec3(0, 0.1, 0));//bump
	perfil.push_back(perfil.back() + dvec3(-0.2, 0.1, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.1, 0));//end bump
	perfil.push_back(perfil.back() + dvec3(0, 0.1, 0));//bump
	perfil.push_back(perfil.back() + dvec3(-0.2, 0.1, 0));

	GLdouble cx = 0.0;
	GLdouble cy = perfil.back().y + 1.0;
	GLdouble r = 1.0;

	GLdouble step = 180.0 / GLdouble(10);
	GLdouble initialAngle = -90.0;
	for (int i = 1; i < 10+1; i++)
	{
		GLdouble currentAngle = initialAngle + step * i;
		GLdouble alpha = radians(currentAngle);

		GLdouble x = cx + r * glm::cos(alpha);
		GLdouble y = cy + r * glm::sin(alpha);
		perfil.push_back({ x, y, 0.0 });
	}





	this->mMesh = MbR::generaIndexMbR(perfil.size(), 100, perfil.data());
}

void Peon::render(glm::dmat4 const& modelViewMat) const
{

	if (mMesh != nullptr) {

		dmat4 aMat = complete_transform(modelViewMat);

		upload(aMat);

		glColor4d(mColor[0], mColor[1], mColor[2], mColor[3]);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_NORMALIZE);
		glEnable(GL_COLOR_MATERIAL);


		material->upload();

		mMesh->render();
		
		glDisable(GL_NORMALIZE);
		glDisable(GL_COLOR_MATERIAL);
		glPointSize(1);
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

Torre::Torre()
{
	std::vector<dvec3> perfil;
	// y positivo arriba
	// x positivo derecha
	perfil.push_back(dvec3(0, 0, 0));
	perfil.push_back(perfil.back() + dvec3(2, 0, 0));
	perfil.push_back(perfil.back() + dvec3(0, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(-0.1, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(0.0, 0.4, 0));
	perfil.push_back(perfil.back() + dvec3(-0.3, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(0.0, 0.5, 0));
	perfil.push_back(perfil.back() + dvec3(-0.3, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(-0.2, 1, 0));
	perfil.push_back(perfil.back() + dvec3( 0, 0.5, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 1, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(0, 0.2, 0));//bump
	perfil.push_back(perfil.back() + dvec3(-0.1, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.2, 0));//end bump
	perfil.push_back(perfil.back() + dvec3(0, 1, 0));
	perfil.push_back(perfil.back() + dvec3(-0.5, 0, 0));
	perfil.push_back(perfil.back() + dvec3(0, -0.5, 0));
	perfil.push_back(perfil.back() + dvec3(-0.5, 0, 0));

	this->mMesh = MbR::generaIndexMbR(perfil.size(), 100, perfil.data());
}

void Torre::render(glm::dmat4 const& modelViewMat) const
{

	if (mMesh != nullptr) {

		dmat4 aMat = complete_transform(modelViewMat);

		upload(aMat);

		glColor4d(mColor[0], mColor[1], mColor[2], mColor[3]);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_NORMALIZE);
		glEnable(GL_COLOR_MATERIAL);


		//material->upload();

		mMesh->render();

		glDisable(GL_NORMALIZE);
		glDisable(GL_COLOR_MATERIAL);
		glPointSize(1);
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}


Alfil::Alfil()
{
	std::vector<dvec3> perfil;
	// y positivo arriba
	// x positivo derecha
	perfil.push_back(dvec3(0, 0, 0));
	perfil.push_back(perfil.back() + dvec3(1.75, 0, 0));
	perfil.push_back(perfil.back() + dvec3(0, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(-0.1, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(0.0, 0.4, 0));
	perfil.push_back(perfil.back() + dvec3(-0.3, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(0.0, 0.5, 0));
	perfil.push_back(perfil.back() + dvec3(-0.4, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(-0.2, 0.8, 0));
	perfil.push_back(perfil.back() + dvec3(0, 0.5, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.8, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(0, 0.2, 0));//bump
	perfil.push_back(perfil.back() + dvec3(-0.2, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(+0.2, 0.2, 0));//end bump
	perfil.push_back(perfil.back() + dvec3(0, 0.1, 0));//bump
	perfil.push_back(perfil.back() + dvec3(-0.2, 0.1, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.1, 0));//end bump
	perfil.push_back(perfil.back() + dvec3(0, 0.1, 0));//bump
	perfil.push_back(perfil.back() + dvec3(-0.2, 0.1, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.1, 0));//end bump
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 1, 0));
	perfil.push_back(perfil.back() + dvec3(-0.3, 1, 0));
	perfil.push_back(perfil.back() + dvec3(-0.4, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(-0, 0.5, 0));
	perfil.push_back(perfil.back() + dvec3(-0.5, 0, 0));


	this->mMesh = MbR::generaIndexMbR(perfil.size(), 100, perfil.data());
}

void Alfil::render(glm::dmat4 const& modelViewMat) const
{

	if (mMesh != nullptr) {

		dmat4 aMat = complete_transform(modelViewMat);

		upload(aMat);

		glColor4d(mColor[0], mColor[1], mColor[2], mColor[3]);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_NORMALIZE);
		glEnable(GL_COLOR_MATERIAL);


		//material->upload();

		mMesh->render();

		glDisable(GL_NORMALIZE);
		glDisable(GL_COLOR_MATERIAL);
		glPointSize(1);
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}


Reina::Reina()
{
	std::vector<dvec3> perfil;
	// y positivo arriba
	// x positivo derecha
	perfil.push_back(dvec3(0, 0, 0));
	perfil.push_back(perfil.back() + dvec3(1.75, 0, 0));
	perfil.push_back(perfil.back() + dvec3(0, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(-0.1, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(0.0, 0.4, 0));
	perfil.push_back(perfil.back() + dvec3(-0.3, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(0.0, 0.5, 0));
	perfil.push_back(perfil.back() + dvec3(-0.4, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(-0.2, 1.5, 0));
	perfil.push_back(perfil.back() + dvec3(0, 0.5, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 1.5, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(0, 0.2, 0));//bump
	perfil.push_back(perfil.back() + dvec3(-0.2, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(+0.2, 0.2, 0));//end bump
	perfil.push_back(perfil.back() + dvec3(0, 0.1, 0));//bump
	perfil.push_back(perfil.back() + dvec3(-0.2, 0.1, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.1, 0));//end bump
	perfil.push_back(perfil.back() + dvec3(0, 0.1, 0));//bump
	perfil.push_back(perfil.back() + dvec3(-0.2, 0.1, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.1, 0));//end bump
	perfil.push_back(perfil.back() + dvec3(+0, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(-0.2, 0.5, 0));
	perfil.push_back(perfil.back() + dvec3(0.3, 0.8, 0));
	perfil.push_back(perfil.back() + dvec3(0.2, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3( 0, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(-0.2, -0.2, 0));
	perfil.push_back(perfil.back() + dvec3(-0.6, 0, 0));
	perfil.push_back(perfil.back() + dvec3(0.1, 0.4, 0));
	perfil.push_back(perfil.back() + dvec3(-0.2, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(-0.4, 0.1, 0));


	this->mMesh = MbR::generaIndexMbR(perfil.size(), 100, perfil.data());
}

void Reina::render(glm::dmat4 const& modelViewMat) const
{

	if (mMesh != nullptr) {

		dmat4 aMat = complete_transform(modelViewMat);

		upload(aMat);

		glColor4d(mColor[0], mColor[1], mColor[2], mColor[3]);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_NORMALIZE);
		glEnable(GL_COLOR_MATERIAL);


		//material->upload();

		mMesh->render();

		glDisable(GL_NORMALIZE);
		glDisable(GL_COLOR_MATERIAL);
		glPointSize(1);
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}


Rey::Rey()
{
	std::vector<dvec3> perfil;
	// y positivo arriba
	// x positivo derecha
	perfil.push_back(dvec3(0, 0, 0));
	perfil.push_back(perfil.back() + dvec3(1.75, 0, 0));
	perfil.push_back(perfil.back() + dvec3(0, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(-0.1, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(0.0, 0.4, 0));
	perfil.push_back(perfil.back() + dvec3(-0.3, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(0.0, 0.5, 0));
	perfil.push_back(perfil.back() + dvec3(-0.4, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(-0.2, 1.5, 0));
	perfil.push_back(perfil.back() + dvec3(0, 0.5, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 1.5, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(0, 0.2, 0));//bump
	perfil.push_back(perfil.back() + dvec3(-0.2, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(+0.2, 0.2, 0));//end bump
	perfil.push_back(perfil.back() + dvec3(0, 0.1, 0));//bump
	perfil.push_back(perfil.back() + dvec3(-0.2, 0.1, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.1, 0));//end bump
	perfil.push_back(perfil.back() + dvec3(0, 0.1, 0));//bump
	perfil.push_back(perfil.back() + dvec3(-0.2, 0.1, 0));
	perfil.push_back(perfil.back() + dvec3(+0.1, 0.1, 0));//end bump
	perfil.push_back(perfil.back() + dvec3(+0, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(-0.1, 0.1, 0));
	perfil.push_back(perfil.back() + dvec3(0.3, 1.5, 0));
	perfil.push_back(perfil.back() + dvec3(0, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3(-0.2, 0, 0));
	perfil.push_back(perfil.back() + dvec3(-0.7, 0.1, 0));
	perfil.push_back(perfil.back() + dvec3( 0, 0.2, 0));
	perfil.push_back(perfil.back() + dvec3( -0.1, 0.05, 0));
	perfil.push_back(perfil.back() + dvec3(  0, 0.6, 0));
	perfil.push_back(perfil.back() + dvec3( -0.2, 0, 0));



	this->mMesh = MbR::generaIndexMbR(perfil.size(), 100, perfil.data());
}

void Rey::render(glm::dmat4 const& modelViewMat) const
{

	if (mMesh != nullptr) {

		dmat4 aMat = complete_transform(modelViewMat);

		upload(aMat);

		glColor4d(mColor[0], mColor[1], mColor[2], mColor[3]);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_NORMALIZE);
		glEnable(GL_COLOR_MATERIAL);


		//material->upload();

		mMesh->render();

		glDisable(GL_NORMALIZE);
		glDisable(GL_COLOR_MATERIAL);
		glPointSize(1);
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}


