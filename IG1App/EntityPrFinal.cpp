#include "EntityPr5.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "EntityPrFinal.h"

#include <iostream>

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

		mTextures[0]->bind(GL_ADD);

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
	perfil.push_back(perfil.back() + dvec3(-1, 0, 0));

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


BaseCaballo::BaseCaballo()
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
	perfil.push_back(perfil.back() + dvec3(-1, 0.0, 0));

	this->mMesh = MbR::generaIndexMbR(perfil.size(), 100, perfil.data());
}

void BaseCaballo::render(glm::dmat4 const& modelViewMat) const
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

CabezaCaballo::CabezaCaballo()
{
	
	this->mMesh = IndexMesh::generateCaballo();
}

void CabezaCaballo::render(glm::dmat4 const& modelViewMat) const
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



Caballo::Caballo()
{
	
	BaseCaballo* bc = new BaseCaballo();
	bc->mScale = { 1 ,1, 1 };
	CabezaCaballo* cc = new CabezaCaballo();
	cc->mPosition = { 0,1.8,0 };
	cc->mScale = { 1.7,2.8,1.7 };
	addEntity(cc);
	addEntity(bc);


}



Luz::Luz(GLdouble rru, GLdouble rrd, GLdouble hh): QuadricEntity() { ru = rru; rd = rrd; h = hh; mTexturePaths = { "../bmps/luz.bmp" };
}
void Luz::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = complete_transform(modelViewMat);
	upload(aMat);
	// Aquí se puede fijar el color de la esfera así:
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST); // Si no, no se transparentan los otros hierbajos renderizados

	//glColor3f(mColor[0], mColor[1], mColor[2]);
	// Aquí se puede fijar el modo de dibujar la esfera :
	gluQuadricDrawStyle (q, GLU_FILL);
	gluQuadricTexture(q, GL_TRUE);
	mTextures[0]->bind(GL_REPLACE);
	gluCylinder(q, ru, rd, h, 50, 50);
	mTextures[0]->unbind();
	glEnable(GL_DEPTH_TEST); // Si no, no se transparentan los otros hierbajos renderizados

	// Aquí se debe recuperar el color :
	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_COLOR_MATERIAL);

}

void
Luz::initTextures(std::vector<Texture*>& sceneTextures) {
	for (std::string s : mTexturePaths) {
		Texture* text = new Texture();
		text->load(s, u8vec3(0.0, 0.0, 0.0), GLubyte(0.0));
		mTextures.push_back(text);
		sceneTextures.push_back(text);
	}
}

SpotLight* PantallaFlexo::spotLight = new SpotLight();


PantallaFlexo::PantallaFlexo() : EntityWithMaterial()
{
	std::vector<dvec3> perfil;
	// y positivo arriba
	// x positivo derecha
	perfil.push_back(dvec3(0, 0, 0));
	perfil.push_back(perfil.back() + dvec3(1, 0, 0));
	perfil.push_back(perfil.back() + dvec3(0.3, 0.6, 0));
	perfil.push_back(perfil.back() + dvec3(0.2, 0.9, 0));
	perfil.push_back(perfil.back() + dvec3(0.1, 1.2, 0));
	perfil.push_back(perfil.back() + dvec3(0.1 , 0.1, 0));
	perfil.push_back(perfil.back() + dvec3(2 , 0, 0));
	perfil.push_back(perfil.back() + dvec3(0.3, 0.4, 0));
	perfil.push_back(perfil.back() + dvec3(0.1, 1, 0));
	perfil.push_back(perfil.back() + dvec3( 0.1, 2, 0));

	this->mMesh = MbR::generaIndexMbR(perfil.size(), 100, perfil.data());


	spotLight->setAmb(glm::fvec4{ 0, 0, 0, 1 });
	spotLight->setDiff(glm::fvec4{ 1, 1, 1, 1 });
	spotLight->setSpec(glm::fvec4{ 0.5, 0.5, 0.5, 1 });
	spotLight->setPosDir(glm::fvec3{ mPosition.x, mPosition.y, mPosition.z });
	spotLight->enable();

}

void PantallaFlexo::render(glm::dmat4 const& modelViewMat) const
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


		spotLight->setPosDir(glm::fvec3{ mPosition.x, mPosition.y, mPosition.z });
		spotLight->setSpot(glm::fvec3{ -1.0, 0, 0}, 40, 3);
		spotLight->setAtte(1, 0, 0.000002);
		spotLight->upload(modelViewMat);
	}
}

void PantallaFlexo::update() {
	counter += 0.000001;
	std::cout << counter << std::endl;
}

void Eje::update()
{
	counter+= 0.1 ;

	mRotation = { 0,0, inicial + glm::sin(glm::radians(counter + desfase)) * apertura };

	for (Abs_Entity* ent : gObjects) {
		ent->update();
	}


}



DensePlain::DensePlain(int& density, float textCoorRepeat)
{

	this->mMesh = IndexMesh::generateDensePlain(density, textCoorRepeat);
	material = new Material();
	material->setCopper();
}

void DensePlain::render(glm::dmat4 const& modelViewMat) const
{

	if (mMesh != nullptr) {

		dmat4 aMat = complete_transform(modelViewMat);

		upload(aMat);

		glColor4d(mColor[0], mColor[1], mColor[2], mColor[3]);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_NORMALIZE);


		glEnable(GL_COLOR_MATERIAL);
		material->upload();

		if (mTexturePaths.size() > 0) { mTextures[0]->bind(GL_MODULATE); }
		mMesh->render();
		if (mTexturePaths.size() > 0) { mTextures[0]->unbind(); }

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


