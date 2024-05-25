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
	perfil.push_back({ rB, h - (h / 5.0), 0.0}); 
	perfil.push_back({ rB, (h - (h / 5.0)) / 2.0, 0.0 }); 
	perfil.push_back({ rB, 0, 0.0 }); 	

	this->mMesh = MbR::generaIndexAtalaya(perfil.size(), p, perfil.data());

	Material* mat = new Material();
	mat->upload();
	mat->setStone();
	setMaterial(mat);
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
		glDisable(GL_COLOR_MATERIAL);

		mTextures[0]->bind(GL_MODULATE);
		material->upload();

		mMesh->render();

		mTextures[0]->unbind();

		glEnable(GL_COLOR_MATERIAL);
		glPointSize(1);
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

//----------------------------------------------------------------------------------------------
// IndexedBoxWithMaterial
//----------------------------------------------------------------------------------------------

IndexedBoxWithMaterial::IndexedBoxWithMaterial(int m) {
	mTexturePaths = { "../bmps/houseWall.bmp" };

	mMesh = IndexMesh::generateIndexedBox(m);
}

void
IndexedBoxWithMaterial::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = complete_transform(modelViewMat);
	upload(aMat);

	glPolygonMode(GL_BACK, GL_FILL);
	glDisable(GL_COLOR_MATERIAL);

	mTextures[0]->bind(GL_MODULATE);
	material->upload();

	mMesh->render();

	mTextures[0]->unbind();

	glEnable(GL_COLOR_MATERIAL);
	glPointSize(1);
	glLineWidth(1);
	glColor4d(1.0, 1.0, 1.0, 1.0);
	glPolygonMode(GL_FRONT, GL_FILL);
}

//----------------------------------------------------------------------------------------------
// IndexedPiramidWithMaterial
//----------------------------------------------------------------------------------------------

IndexedPiramidWithMaterial::IndexedPiramidWithMaterial(int m) {
	mTexturePaths = { "../bmps/roof.bmp" };

	mMesh = IndexMesh::generateIndexedPiramid(m);
}

void
IndexedPiramidWithMaterial::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = complete_transform(modelViewMat);
	upload(aMat);

	glPolygonMode(GL_BACK, GL_FILL);
	glDisable(GL_COLOR_MATERIAL);

	mTextures[0]->bind(GL_MODULATE);
	material->upload();

	mMesh->render();

	mTextures[0]->unbind();

	glEnable(GL_COLOR_MATERIAL);
	glPointSize(1);
	glLineWidth(1);
	glColor4d(1.0, 1.0, 1.0, 1.0);
	glPolygonMode(GL_FRONT, GL_FILL);
}

//----------------------------------------------------------------------------------------------
// Casa
//----------------------------------------------------------------------------------------------

Casa::Casa(int m)
	: CompoundEntity() {

	// Square Structure
	EntityWithMaterial* main_structure = new IndexedBoxWithMaterial(m);

	Material* mat = new Material();
	mat->upload();
	mat->setStone();
	main_structure->setMaterial(mat);

	main_structure->mPosition.y += m / 2;

	addEntity(main_structure);

	// Roof
	EntityWithMaterial* roof = new IndexedPiramidWithMaterial(m * 1.2);

	Material* mat2 = new Material();
	mat2->upload();
	mat2->setStone();
	roof->setMaterial(mat2);

	roof->mPosition.y += m * 1.5;

	addEntity(roof);

	// Door
	Abs_Entity* door = new Ground(m / 2, m * 0.75);
	door->mTexturePaths = { "../bmps/door.bmp" };
	
	door->mPosition.z -= (m / 2) + 0.1;
	door->mPosition.y += (m * 0.75) / 2;
	
	door->mRotation.x += 90;
	door->mRotation.z += 90;

	addEntity(door);

	// Right Window
	Abs_Entity* rWindow = new Ground(m / 2, m / 4);
	rWindow->mTexturePaths = { "../bmps/ventana.bmp" };

	rWindow->mPosition.x -= (m / 2) + 0.1;
	rWindow->mPosition.y += m / 2;

	rWindow->mRotation.x += 90;
	rWindow->mRotation.z += 90;
	rWindow->mRotation.y += 90;

	addEntity(rWindow);

	// Left Window
	Abs_Entity* lWindow = new Ground(m / 2, m / 4);
	lWindow->mTexturePaths = { "../bmps/ventana.bmp" };

	lWindow->mPosition.x += (m / 2) + 0.1;
	lWindow->mPosition.y += m / 2;

	lWindow->mRotation.x += 90;
	lWindow->mRotation.z += 90;
	lWindow->mRotation.y -= 90;

	addEntity(lWindow);

	// Farol


}

void Casa::render(glm::dmat4 const& modelViewMat) const {

	glm::dmat4 modelViewMatComp = complete_transform(modelViewMat) * mModelMat;
	upload(modelViewMatComp);

	for (Abs_Entity* ent : gObjects) {
		ent->render(modelViewMatComp);
	}
}
