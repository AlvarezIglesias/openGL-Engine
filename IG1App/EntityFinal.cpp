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

Atalaya::Atalaya(GLdouble rU, GLdouble rB, GLdouble h, GLuint m, GLuint p) : EntityWithMaterial() {

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

	this->mMesh = MbR::generaIndexTextCords(perfil.size(), p, perfil.data());

	Material* mat = new Material();
	mat->upload();
	mat->setStone();
	setMaterial(mat);
}

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

IndexedBoxWithMaterial::IndexedBoxWithMaterial(int m) : EntityWithMaterial() {
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

IndexedPiramidWithMaterial::IndexedPiramidWithMaterial(int m) : EntityWithMaterial() {

	mMesh = IndexMesh::generateIndexedPiramid(m);
}

void
IndexedPiramidWithMaterial::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = complete_transform(modelViewMat);
	upload(aMat);

	glPolygonMode(GL_BACK, GL_FILL);
	glDisable(GL_COLOR_MATERIAL);

	if (mTexturePaths.size() > 0) { mTextures[0]->bind(GL_MODULATE); }
	material->upload();

	mMesh->render();

	if (mTexturePaths.size() > 0) { mTextures[0]->unbind(); }

	glEnable(GL_COLOR_MATERIAL);
	glPointSize(1);
	glLineWidth(1);
	glColor4d(1.0, 1.0, 1.0, 1.0);
	glPolygonMode(GL_FRONT, GL_FILL);
}

//----------------------------------------------------------------------------------------------
// GroundWithMaterial
//----------------------------------------------------------------------------------------------

GroundWithMaterial::GroundWithMaterial(GLdouble w, GLdouble h)
	: EntityWithMaterial()
{
	//mTexturePaths = { "../bmps/grassPaint.bmp" };
	mMesh = Mesh::generateRectangleTexCor(w, h, 4, 4);
	mRotation = dvec3(270, 0, 270);
}

GroundWithMaterial::~GroundWithMaterial()
{
	delete mMesh;
	mMesh = nullptr;
};

void
GroundWithMaterial::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat
			* mModelMat
			* translate(dmat4(1), mPosition)
			* rotate(dmat4(1), radians(mRotation.x), dvec3(1, 0, 0))
			* rotate(dmat4(1), radians(mRotation.y), dvec3(0, 1, 0))
			* rotate(dmat4(1), radians(mRotation.z), dvec3(0, 0, 1)); // glm matrix multiplication

		upload(aMat);

		glColor4d(1.0, 1.0, 1.0, 1.0);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_COLOR_MATERIAL);

		if (mTexturePaths.size() > 0) { mTextures[0]->bind(GL_MODULATE); }
		material->upload();

		mMesh->render();

		if (mTexturePaths.size() > 0) { mTextures[0]->unbind(); }
		glEnable(GL_COLOR_MATERIAL);
		glPointSize(1);
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glPolygonMode(GL_FRONT, GL_FILL);
	}
}

//----------------------------------------------------------------------------------------------
// RevCilinder
//----------------------------------------------------------------------------------------------

RevCilinder::RevCilinder(GLdouble r, GLdouble h, GLuint m, GLuint p) 
	: EntityWithMaterial() 
{

	std::vector<dvec3> perfil;

	GLdouble cx = 0.0;
	GLdouble cy = 0.0;

	GLdouble initialAngle = 90.0;

	// Cilindro
	perfil.push_back({ r, h, 0.0 });
	perfil.push_back({ r, h / 2.0, 0.0 });
	perfil.push_back({ r, 0, 0.0 });

	this->mMesh = MbR::generaIndexTextCords(perfil.size(), p, perfil.data());

	Material* mat = new Material();
	mat->upload();
	mat->setStone();
	setMaterial(mat);
}

void RevCilinder::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {

		dmat4 aMat = complete_transform(modelViewMat);

		upload(aMat);

		glColor4d(mColor[0], mColor[1], mColor[2], mColor[3]);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_COLOR_MATERIAL);

		if (mTexturePaths.size() > 0) { mTextures[0]->bind(GL_MODULATE); }
		material->upload();

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

//----------------------------------------------------------------------------------------------
// DiskWithMaterial
//----------------------------------------------------------------------------------------------
DiskWithMaterial::DiskWithMaterial(GLdouble rri, GLdouble rro) : QuadricWithMaterialEntity() { ri = rri; ro = rro; }
void DiskWithMaterial::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = complete_transform(modelViewMat);
	upload(aMat);

	//glColor3f(mColor[0], mColor[1], mColor[2]);
	glDisable(GL_COLOR_MATERIAL);

	material->upload();
	if (mTexturePaths.size() > 0) { mTextures[0]->bind(GL_MODULATE); gluQuadricTexture(q, GL_TRUE); }

	gluDisk(q, ri, ro, 50, 50);
	
	if (mTexturePaths.size() > 0) { mTextures[0]->unbind(); gluQuadricTexture(q, GL_FALSE); }
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1.0, 1.0, 1.0);
}

//----------------------------------------------------------------------------------------------
// Farolillo
//----------------------------------------------------------------------------------------------

Farolillo::Farolillo(int m)
	: CompoundEntity() {

	// Soporte
	Material* mat = new Material();
	mat->upload();
	mat->setWood();

	EntityWithMaterial* soporte = new RevCilinder(m/18.75, m/2.5, 200, 200);
	soporte->mTexturePaths = { "../bmps/wood.bmp" };

	soporte->mRotation.x += 90;

	soporte->setMaterial(mat);

	addEntity(soporte);

	// Soporte de Apoyo
	EntityWithMaterial* soporteApoyo = new RevCilinder(m/18.75, m/2.5, 200, 200);
	soporteApoyo->mTexturePaths = { "../bmps/wood.bmp" };

	soporteApoyo->mRotation.x += 45;
	soporteApoyo->mPosition.y -= m / 3.25;

	soporteApoyo->setMaterial(mat);

	addEntity(soporteApoyo);

	// Cierres Soporte
	Material* mat2 = new Material();
	mat2->upload();
	mat2->setWood();

	EntityWithMaterial* cierre = new DiskWithMaterial(0, m / 18.75);

	cierre->setMaterial(mat2);

	cierre->mTexturePaths = { "../bmps/wood2.bmp" };

	addEntity(cierre);

	EntityWithMaterial* cierre2 = new DiskWithMaterial(0, m / 18.75);
	cierre2->mPosition.z += m / 2.5;

	cierre2->mTexturePaths = { "../bmps/wood2.bmp" };

	cierre2->setMaterial(mat2);

	addEntity(cierre2);

	// Estructura farol
	Material* mat3 = new Material();
	mat3->upload();
	mat3->setBrass();
	
	// Cadena
	EntityWithMaterial* cadena = new Toroid(m / 400, m / 18.75, 200, 200);
	cadena->setMaterial(mat3);

	cadena->mRotation.x += 90;
	cadena->mPosition.z += m / 2.75;

	addEntity(cadena);

	// Arriba
	EntityWithMaterial* arriba = new IndexedPiramidWithMaterial(m / 18.75);
	arriba->setMaterial(mat3);

	arriba->mPosition.z += m / 2.75;
	arriba->mPosition.y -= m / 15;

	addEntity(arriba);

	// Cristales
	Material* mat4 = new Material();
	mat4->upload();
	mat4->setGlass();

	// Cristal derecho
	EntityWithMaterial* rGlass = new GroundWithMaterial(m / 19.75, m / 19.75);
	rGlass->setMaterial(mat4);

	rGlass->mPosition.z += m / 2.75;
	rGlass->mPosition.y -= (m / 19.75) + (m / 15);
	rGlass->mPosition.x += (m / 19.75) / 2;

	rGlass->mRotation.x += 90;
	rGlass->mRotation.z += 90;
	rGlass->mRotation.y -= 90;

	addEntity(rGlass);

	// Cristal izquierdo
	EntityWithMaterial* lGlass = new GroundWithMaterial(m / 19.75, m / 19.75);
	lGlass->setMaterial(mat4);

	lGlass->mPosition.z += m / 2.75;
	lGlass->mPosition.y -= (m / 19.75) + (m / 15);
	lGlass->mPosition.x -= (m / 19.75) / 2;

	lGlass->mRotation.x += 90;
	lGlass->mRotation.z += 90;
	lGlass->mRotation.y += 90;

	addEntity(lGlass);

	// Cristal frontal
	EntityWithMaterial* fGlass = new GroundWithMaterial(m / 19.75, m / 19.75);
	fGlass->setMaterial(mat4);

	fGlass->mPosition.z += m / 2.75 + (m / 19.75) / 2;
	fGlass->mPosition.y -= (m / 19.75) + (m / 15);
	//bGlass->mPosition.x -= (m / 19.75) / 2;

	fGlass->mRotation.x += 90;
	fGlass->mRotation.z += 90;
	//bGlass->mRotation.y -= 90;

	addEntity(fGlass);

	// Cristal trasero
	EntityWithMaterial* bGlass = new GroundWithMaterial(m / 19.75, m / 19.75);
	bGlass->setMaterial(mat4);

	bGlass->mPosition.z += m / 2.75 - (m / 19.75) / 2;
	bGlass->mPosition.y -= (m / 19.75) + (m / 15);
	//bGlass->mPosition.x -= (m / 19.75) / 2;

	bGlass->mRotation.x += 90;
	bGlass->mRotation.z += 90;
	bGlass->mRotation.y -= 180;

	addEntity(bGlass);

	// Base
	EntityWithMaterial* base = new GroundWithMaterial(m / 19.75, m / 19.75);
	mat3->upload();
	base->setMaterial(mat3);

	base->mPosition.z += m / 2.75;
	base->mPosition.y -= m / 15 + ((m / 19.75) * 1.5);
	//bGlass->mPosition.x -= (m / 19.75) / 2;

	base->mRotation.x += 180;
	//base->mRotation.z += 90;
	//base->mRotation.y -= 180;

	addEntity(base);

	// Soportes del farol
	// Left Back
	EntityWithMaterial* sbl = new RevCilinder(m / 400, m / 19.75, 200, 200);

	sbl->mPosition.z += m / 2.75 - (m / 19.75) / 2;
	sbl->mPosition.y -= m / 15 + ((m / 19.75) * 1.5);
	sbl->mPosition.x -= (m / 19.75) / 2;

	//sbl->mRotation.x += 90;

	sbl->setMaterial(mat3);

	addEntity(sbl);

	// Right Back
	EntityWithMaterial* sbr = new RevCilinder(m / 400, m / 19.75, 200, 200);

	sbr->mPosition.z += m / 2.75 - (m / 19.75) / 2;
	sbr->mPosition.y -= m / 15 + ((m / 19.75) * 1.5);
	sbr->mPosition.x += (m / 19.75) / 2;

	//sbl->mRotation.x += 90;

	sbr->setMaterial(mat3);

	addEntity(sbr);

	// Right Front
	EntityWithMaterial* sfr = new RevCilinder(m / 400, m / 19.75, 200, 200);

	sfr->mPosition.z += m / 2.75 + (m / 19.75) / 2;
	sfr->mPosition.y -= m / 15 + ((m / 19.75) * 1.5);
	sfr->mPosition.x += (m / 19.75) / 2;

	//sbl->mRotation.x += 90;

	sfr->setMaterial(mat3);

	addEntity(sfr);

	// Left Front
	EntityWithMaterial* sfl = new RevCilinder(m / 400, m / 19.75, 200, 200);

	sfl->mPosition.z += m / 2.75 + (m / 19.75) / 2;
	sfl->mPosition.y -= m / 15 + ((m / 19.75) * 1.5);
	sfl->mPosition.x -= (m / 19.75) / 2;

	//sbl->mRotation.x += 90;

	sfl->setMaterial(mat3);

	addEntity(sfl);

	// Tapas

	// Left Front
	// Bottom
	EntityWithMaterial* tapa = new DiskWithMaterial(0, m / 400);
	tapa->setMaterial(mat3);

	tapa->mPosition.z += m / 2.75 + (m / 19.75) / 2;
	tapa->mPosition.y -= m / 15 + ((m / 19.75) * 1.5);
	tapa->mPosition.x -= (m / 19.75) / 2;

	tapa->mRotation.x += 90;

	addEntity(tapa);

	// Up
	EntityWithMaterial* tapa2 = new DiskWithMaterial(0, m / 400);
	tapa2->setMaterial(mat3);

	tapa2->mPosition.z += m / 2.75 + (m / 19.75) / 2;
	tapa2->mPosition.y -= m / 15 + m / 39.5;
	tapa2->mPosition.x -= (m / 19.75) / 2;

	tapa2->mRotation.x += 90;

	addEntity(tapa2);

	// Right Front
	// Bottom
	EntityWithMaterial* tapa3 = new DiskWithMaterial(0, m / 400);
	tapa3->setMaterial(mat3);

	tapa3->mPosition.z += m / 2.75 + (m / 19.75) / 2;
	tapa3->mPosition.y -= m / 15 + ((m / 19.75) * 1.5);
	tapa3->mPosition.x += (m / 19.75) / 2;

	tapa3->mRotation.x += 90;

	addEntity(tapa3);

	// Up
	EntityWithMaterial* tapa4 = new DiskWithMaterial(0, m / 400);
	tapa4->setMaterial(mat3);

	tapa4->mPosition.z += m / 2.75 + (m / 19.75) / 2;
	tapa4->mPosition.y -= m / 15 + m / 39.5;
	tapa4->mPosition.x += (m / 19.75) / 2;

	tapa4->mRotation.x += 90;

	addEntity(tapa4);

	// Right Back
	// Bottom
	EntityWithMaterial* tapa5 = new DiskWithMaterial(0, m / 400);
	tapa5->setMaterial(mat3);

	tapa5->mPosition.z += m / 2.75 - (m / 19.75) / 2;
	tapa5->mPosition.y -= m / 15 + ((m / 19.75) * 1.5);
	tapa5->mPosition.x += (m / 19.75) / 2;

	tapa5->mRotation.x += 90;

	addEntity(tapa5);

	// Up
	EntityWithMaterial* tapa6 = new DiskWithMaterial(0, m / 400);
	tapa6->setMaterial(mat3);

	tapa6->mPosition.z += m / 2.75 - (m / 19.75) / 2;
	tapa6->mPosition.y -= m / 15 + m / 39.5;
	tapa6->mPosition.x += (m / 19.75) / 2;

	tapa6->mRotation.x += 90;

	addEntity(tapa6);

	// Left Back
	// Bottom
	EntityWithMaterial* tapa7 = new DiskWithMaterial(0, m / 400);
	tapa7->setMaterial(mat3);

	tapa7->mPosition.z += m / 2.75 - (m / 19.75) / 2;
	tapa7->mPosition.y -= m / 15 + ((m / 19.75) * 1.5);
	tapa7->mPosition.x -= (m / 19.75) / 2;

	tapa7->mRotation.x += 90;

	addEntity(tapa7);

	// Up
	EntityWithMaterial* tapa8 = new DiskWithMaterial(0, m / 400);
	tapa8->setMaterial(mat3);

	tapa8->mPosition.z += m / 2.75 - (m / 19.75) / 2;
	tapa8->mPosition.y -= m / 15 + m / 39.5;
	tapa8->mPosition.x -= (m / 19.75) / 2;

	tapa8->mRotation.x += 90;

	addEntity(tapa8);

}

void Farolillo::render(glm::dmat4 const& modelViewMat) const {

	glm::dmat4 modelViewMatComp = complete_transform(modelViewMat) * mModelMat;
	upload(modelViewMatComp);

	for (Abs_Entity* ent : gObjects) {
		ent->render(modelViewMatComp);
	}
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
	roof->mTexturePaths = { "../bmps/roof.bmp" };

	Material* mat2 = new Material();
	mat2->upload();
	mat2->setStone();
	roof->setMaterial(mat2);

	roof->mPosition.y += m * 1.5;

	addEntity(roof);

	// Door
	EntityWithMaterial* door = new GroundWithMaterial(m / 2, m * 0.75);
	door->mTexturePaths = { "../bmps/door.bmp" };

	Material* mat3 = new Material();
	mat3->upload();
	mat3->setWood();
	door->setMaterial(mat3);
	
	door->mPosition.z -= (m / 2) + 0.1;
	door->mPosition.y += (m * 0.75) / 2;
	
	door->mRotation.x += 90;
	door->mRotation.z += 90;

	addEntity(door);

	// Right Window
	EntityWithMaterial* rWindow = new GroundWithMaterial(m / 2, m / 4);
	rWindow->mTexturePaths = { "../bmps/ventana.bmp" };

	Material* mat4 = new Material();
	mat4->upload();
	mat4->setGlass();
	rWindow->setMaterial(mat4);

	rWindow->mPosition.x -= (m / 2) + 0.1;
	rWindow->mPosition.y += m / 2;

	rWindow->mRotation.x += 90;
	rWindow->mRotation.z += 90;
	rWindow->mRotation.y += 90;

	addEntity(rWindow);

	// Left Window
	EntityWithMaterial* lWindow = new GroundWithMaterial(m / 2, m / 4);
	lWindow->mTexturePaths = { "../bmps/ventana.bmp" };

	lWindow->setMaterial(mat4);

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
