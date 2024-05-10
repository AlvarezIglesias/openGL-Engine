#include "Entity.h"
#include "EntityPr4.h"
#include "EntityPr1.h"
#include "Texture.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

//----------------------------------------------------------------------------------------------
// Sphere
//----------------------------------------------------------------------------------------------
Sphere::Sphere(GLdouble rr) { r = rr; }
void Sphere::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = complete_transform(modelViewMat);
	upload(aMat);
	// Aquí se puede fijar el color de la esfera así:
	// glEnable ( GL_COLOR_MATERIAL );
	glColor3f(mColor[0], mColor[1], mColor[2]);
	// Aquí se puede fijar el modo de dibujar la esfera :
	// gluQuadricDrawStyle (q, ...);
	gluSphere(q, r, 50, 50);
	// Aquí se debe recuperar el color :
	glColor3f (1.0 , 1.0 , 1.0);
}

//----------------------------------------------------------------------------------------------
// Cylinder
//----------------------------------------------------------------------------------------------
Cylinder::Cylinder(GLdouble rru, GLdouble rrd, GLdouble hh) { ru = rru; rd = rrd; h = hh; }
void Cylinder::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = complete_transform(modelViewMat);
	upload(aMat);
	// Aquí se puede fijar el color de la esfera así:
	// glEnable ( GL_COLOR_MATERIAL );
	glColor3f(mColor[0], mColor[1], mColor[2]);
	// Aquí se puede fijar el modo de dibujar la esfera :
	// gluQuadricDrawStyle (q, ...);
	gluCylinder(q, ru, rd, h, 50, 50);
	// Aquí se debe recuperar el color :
	glColor3f (1.0 , 1.0 , 1.0);
}

//----------------------------------------------------------------------------------------------
// Disk
//----------------------------------------------------------------------------------------------
Disk::Disk(GLdouble rri, GLdouble rro) { ri = rri; ro = rro; }
void Disk::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = complete_transform(modelViewMat);
	upload(aMat);
	// Aquí se puede fijar el color de la esfera así:
	// glEnable ( GL_COLOR_MATERIAL );
	glColor3f(mColor[0], mColor[1], mColor[2]);
	// Aquí se puede fijar el modo de dibujar la esfera :
	// gluQuadricDrawStyle (q, ...);
	gluDisk(q, ri, ro, 50, 50);
	// Aquí se debe recuperar el color :
	glColor3f (1.0 , 1.0 , 1.0);
}

//----------------------------------------------------------------------------------------------
// Partial Disk
//----------------------------------------------------------------------------------------------
PartialDisk::PartialDisk(GLdouble rri, GLdouble rro) { ri = rri; ro = rro; }
void PartialDisk::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = complete_transform(modelViewMat);
	upload(aMat);
	// Aquí se puede fijar el color de la esfera así:
	// glEnable ( GL_COLOR_MATERIAL );
	glColor3f(mColor[0], mColor[1], mColor[2]);
	// Aquí se puede fijar el modo de dibujar la esfera :
	// gluQuadricDrawStyle (q, ...);
	gluPartialDisk(q, ri, ro, 50, 50, 90, 270); // Dos últimos: Ángulos en grados
	// Aquí se debe recuperar el color :
	glColor3f (1.0 , 1.0 , 1.0);
}

//----------------------------------------------------------------------------------------------
// Compound Entity
//----------------------------------------------------------------------------------------------

CompoundEntity::~CompoundEntity(){
	for (Abs_Entity* ent : gObjects) {
		delete ent;
	}
}

void CompoundEntity::addEntity(Abs_Entity* ae) {
	gObjects.push_back(ae);
}

void CompoundEntity::addEntity(std::vector<Abs_Entity*> & aes) {
	for (Abs_Entity* ae : aes) gObjects.push_back(ae);
}

void CompoundEntity::render(glm::dmat4 const& modelViewMat) const {
	
	glm::dmat4 modelViewMatComp = complete_transform(modelViewMat) * mModelMat;
	upload(modelViewMatComp);

	for (Abs_Entity* ent : gObjects) {
		ent->render(modelViewMatComp);
	}
}
void CompoundEntity::initTextures(std::vector<Texture*>& sceneTextures) {
	for (std::string s : mTexturePaths) {
		Texture* text = new Texture();
		text->load(s);
		mTextures.push_back(text);
		sceneTextures.push_back(text);
	}
	for (Abs_Entity* ent : gObjects) {
		ent->initTextures(sceneTextures);
	}
}


//----------------------------------------------------------------------------------------------
// Wing Advanced TIE
//----------------------------------------------------------------------------------------------

WingAdvancedTIE::WingAdvancedTIE(GLdouble w, GLdouble h)
			: Abs_Entity() {
	mMesh = Mesh::generateWingAdvancedTIE(w, h);
	mTexturePaths = { "../bmps/noche.bmp" };
}


void WingAdvancedTIE::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {

		dmat4 aMat = complete_transform(modelViewMat);
		
		upload(aMat);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glColor4d(1.0, 1.0, 1.0, 0.5);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		mTextures[0]->bind(GL_MODULATE);
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);

		mMesh->render();

		mTextures[0]->unbind();
		glPointSize(1);
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glPolygonMode(GL_FRONT, GL_FILL);
	}
}


//----------------------------------------------------------------------------------------------
// AdvancedTIE
//----------------------------------------------------------------------------------------------

AdvancedTIE::AdvancedTIE()
	: CompoundEntity() {

	// Left Wing
	Abs_Entity* left_wing = new WingAdvancedTIE(50, 100);
	left_wing->mPosition.z = 50;
	addEntity(left_wing);
	
	// Right Wing
	Abs_Entity* right_wing = new WingAdvancedTIE(50, 100);
	right_wing->mRotation.x = 180;
	right_wing->mPosition.z = -50;
	addEntity(right_wing);
	
	// Sphere
	Abs_Entity* sphere = new Sphere(50);
	sphere->mColor = dvec4(0.0, 65.0 / 255.0, 106.0 / 255.0, 1.0);
	addEntity(sphere);

	// Connection
	Abs_Entity* connection = new Cylinder(10, 10, 180);
	connection->mPosition.z = -90;
	connection->mColor = dvec4(0.0, 65.0 / 255.0, 106.0 / 255.0, 1.0);
	addEntity(connection);

	// 0 65 106 / 255

	// Frontfff
	Abs_Entity* front = new Cylinder(10, 10, 100);
	front->mRotation.y += 90;
	front->mColor = dvec4(0.0, 65.0 / 255.0, 106.0 / 255.0, 1.0);
	addEntity(front);

	// Disk
	Abs_Entity* disk = new Disk(0, 10);
	disk->mPosition.z += 60;
	disk->mRotation.y += 90;
	disk->mColor = dvec4(0.0, 65.0 / 255.0, 106.0 / 255.0, 1.0);
	addEntity(disk);

	// APARTADO 79 FOCO
	spotLight->setAmb(glm::fvec4{ 0, 0, 0, 1 });
	spotLight->setDiff(glm::fvec4{ 1, 1, 1, 1 });
	spotLight->setSpec(glm::fvec4{ 0.5, 0.5, 0.5, 1 });
	spotLight->setPosDir(glm::fvec3{ mPosition.x, mPosition.y, mPosition.z });

	// spotLight->setSpot(glm::vec3{ 0.0, 0.0, -1.0 }, 95, 0); // No consigo hacerlo más pequeño

	spotLight->enable();

}

void AdvancedTIE::render(glm::dmat4 const& modelViewMat) const {

	glm::dmat4 modelViewMatComp = complete_transform(modelViewMat) * mModelMat;
	upload(modelViewMatComp);

	for (Abs_Entity* ent : gObjects) {
		ent->render(modelViewMatComp);
	}

	spotLight->setPosDir(glm::fvec3{ mPosition.x, mPosition.y, mPosition.z });
	spotLight->upload(modelViewMat);
}

//----------------------------------------------------------------------------------------------
// Indexed Box
//----------------------------------------------------------------------------------------------

IndexedBox::IndexedBox() {
	mMesh = IndexMesh::generateIndexedBox(200);
}

void
IndexedBox::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = complete_transform(modelViewMat);
	upload(aMat);

	glPolygonMode(GL_BACK, GL_FILL);
	mMesh->render();

	glPointSize(1);
	glLineWidth(1);
	glColor4d(1.0, 1.0, 1.0, 1.0);
	glPolygonMode(GL_FRONT, GL_FILL);
}


TrianguloFicticio::TrianguloFicticio() {
	Abs_Entity* triangle = new RGBTriangle(50);
	triangle->mPosition.x = 300;
	addEntity(triangle);
	Abs_Entity* circle = new RegularPolygon(20, 300);
	addEntity(circle);

}

void
TrianguloFicticio::update() {
	mRotation.z += 5;
	gObjects[0]->mRotation.y -= 5;
}




ShipOrbit::ShipOrbit(GLdouble orbitRaidus) {
	Abs_Entity* ship = new AdvancedTIE();
	ship->mPosition.x = orbitRaidus;
	ship->mRotation.z = 90;
	addEntity(ship);
	Abs_Entity* circle = new RegularPolygon(100, orbitRaidus);
	addEntity(circle);

}

void
ShipOrbit::update() {
	
}
