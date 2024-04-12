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
	dmat4 aMat = modelViewMat * mModelMat;
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
	dmat4 aMat = modelViewMat * mModelMat;
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
	dmat4 aMat = modelViewMat * mModelMat;
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
Disk::Disk(GLdouble rri, GLdouble rro) { ri = rri; ro = rro; }
void Disk::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = modelViewMat * mModelMat;
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

void CompoundEntity::render(glm::dmat4 const& modelViewMat) const {
	for (Abs_Entity* ent : gObjects) {
		ent->render(modelViewMat);
	}
}
