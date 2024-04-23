#include "Entity.h"
#include "EntityPr4.h"
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
	// glColor3f (...);
	// Aquí se puede fijar el modo de dibujar la esfera :
	// gluQuadricDrawStyle (q, ...);
	gluSphere(q, r, 50, 50);
	// Aquí se debe recuperar el color :
	// glColor3f (1.0 , 1.0 , 1.0);
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
	// glColor3f (...);
	// Aquí se puede fijar el modo de dibujar la esfera :
	// gluQuadricDrawStyle (q, ...);
	gluCylinder(q, ru, rd, h, 50, 50);
	// Aquí se debe recuperar el color :
	// glColor3f (1.0 , 1.0 , 1.0);
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
	// glColor3f (...);
	// Aquí se puede fijar el modo de dibujar la esfera :
	// gluQuadricDrawStyle (q, ...);
	gluDisk(q, ri, ro, 50, 50);
	// Aquí se debe recuperar el color :
	// glColor3f (1.0 , 1.0 , 1.0);
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
	// glColor3f (...);
	// Aquí se puede fijar el modo de dibujar la esfera :
	// gluQuadricDrawStyle (q, ...);
	gluPartialDisk(q, ri, ro, 50, 50, 90, 270); // Dos últimos: Ángulos en grados
	// Aquí se debe recuperar el color :
	// glColor3f (1.0 , 1.0 , 1.0);
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
	for (Abs_Entity* ent : gObjects) {
		ent->render(modelViewMat);
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
// Compound Entity
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


//----------------------------------------------------------------------------------------------
// Compound Entity
//----------------------------------------------------------------------------------------------

AdvancedTIE::AdvancedTIE()
	: CompoundEntity() {
	Abs_Entity* left_wing = new WingAdvancedTIE(50, 100);
	left_wing->mPosition.z = 50;
	addEntity(left_wing);
	Abs_Entity* right_wing = new WingAdvancedTIE(50, 100);
	right_wing->mRotation.x = 180;
	right_wing->mPosition.z = 50;
	addEntity(right_wing);
	Abs_Entity* sphere = new Sphere(50);
	addEntity(sphere);

	Abs_Entity* conection_left_wing = new Cylinder(80, 80, 80);
	conection_left_wing->mPosition.y = 100;
}

