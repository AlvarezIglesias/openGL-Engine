#include "Light.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

//----------------------------------------------------------------------------------------------
// Material
//----------------------------------------------------------------------------------------------

void Material::upload() {
	glMaterialfv(face, GL_AMBIENT, value_ptr(ambient));
	glMaterialfv(face, GL_DIFFUSE, value_ptr(diffuse));
	glMaterialfv(face, GL_SPECULAR, value_ptr(specular));
	glMaterialf(face, GL_SHININESS, expF);
	glShadeModel(sh);
	// glLightModeli ( GL_LIGHT_MODEL_TWO_SIDE , GL_FALSE ); // Defecto
}
void Material::setCopper() {
	ambient = { 0.19125 , 0.0735 , 0.0225 , 1 };
	diffuse = { 0.7038 , 0.27048 , 0.0828 , 1 };
	specular = { 0.256777 , 0.137622 , 0.086014 , 1 };
	expF = 12.8;

}void Material::setGold() {
	ambient = { 0.24725 , 0.1995 , 0.0745 , 1 };
	diffuse = { 0.75164 , 0.60648 , 0.22648 , 1 };
	specular = { 0.628281 , 0.555802 , 0.366065 , 1 };
	expF = 12.8;
}

void Material::setStone() { 
	ambient = { 0.135, 0.2225, 0.1575, 1 };
	diffuse = { 1.0, 1.0, 1.0, 1 };
	specular = { 0.316228, 0.316228, 0.316228, 1 };
	expF = 10.0;
}

void Material::setGlass() {
	ambient = { 0.0, 0.0, 0.0, 1 };
	diffuse = { 1.0, 1.0, 1.0, 1.0 };
	specular = { 0.7, 0.7, 0.7, 1 };
	expF = 96.0;
}

void Material::setWood() {
	ambient = { 0.3, 0.2, 0.1, 1 };
	diffuse = { 1.0, 1.0, 1.0, 1 };
	specular = { 0.1, 0.1, 0.1, 1 };
	expF = 20.0; 
}

void Material::setBrass() {
	ambient = { 0.329412, 0.223529, 0.027451, 1 };
	diffuse = { 0.780392, 0.568627, 0.113725, 1 };
	specular = { 0.992157, 0.941176, 0.807843, 1 };
	expF = 21.794872;
}

//----------------------------------------------------------------------------------------------
// Light
//----------------------------------------------------------------------------------------------

GLuint Light::cont = 0;

Light::Light() {
	if (cont < GL_MAX_LIGHTS) {
		id = GL_LIGHT0 + cont;
		++cont;
		glEnable(id);
	}
};

void Light::uploadL() const {
	// Transfiere las características de la luz a la GPU
	glLightfv(id, GL_AMBIENT, value_ptr(ambient));
	glLightfv(id, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(id, GL_SPECULAR, value_ptr(specular));
}

void Light::disable() { if (id < GL_LIGHT0 + GL_MAX_LIGHTS) glDisable(id); };

void Light::enable() { if (id < GL_LIGHT0 + GL_MAX_LIGHTS) glEnable(id); };

void Light::setAmb(glm::fvec4 amb) {
	ambient = amb; uploadL();
};

void Light::setDiff(glm::fvec4 diff) {
	diffuse = diff; uploadL();
};

void Light::setSpec(glm::fvec4 sp) {
	specular= sp; uploadL();
};

/*void Light::setPosDir(glm::fvec4 pd) {
	posDir = pd; uploadL();
};*/

//----------------------------------------------------------------------------------------------
// DirLight
//----------------------------------------------------------------------------------------------
void DirLight::upload(glm::dmat4 const& modelViewMat) const {
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));
	glLightfv(id, GL_POSITION, value_ptr(posDir));

	uploadL();
}
// Ojo al 0.0 que determina que la luz sea remota
void DirLight::setPosDir(glm::fvec3 dir) {
	posDir = glm::fvec4(dir, 0.0);
}

//----------------------------------------------------------------------------------------------
// PosLight
//----------------------------------------------------------------------------------------------
void PosLight::upload(glm::dmat4 const& modelViewMat) const {
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));
	glLightfv(id, GL_POSITION, value_ptr(posDir));
	glLightf(id, GL_CONSTANT_ATTENUATION, kc);
	glLightf(id, GL_LINEAR_ATTENUATION, kl);
	glLightf(id, GL_QUADRATIC_ATTENUATION, kq);
	uploadL();
}
// Ojo al 1.0 que determina que la luz sea local
void PosLight::setPosDir(glm::fvec3 dir) {
	posDir = glm::fvec4(dir, 1.0);
}

void PosLight::setAtte(GLfloat kcc, GLfloat kll, GLfloat kqq) {
	kc = kcc;
	kl = kll;
	kq = kqq;
}

//----------------------------------------------------------------------------------------------
// SpotLight
//----------------------------------------------------------------------------------------------
void SpotLight::upload(glm::dmat4 const& modelViewMat) const {
	PosLight::upload(modelViewMat);
	glLightfv(id, GL_SPOT_DIRECTION, value_ptr(direction));
	glLightf(id, GL_SPOT_CUTOFF, cutoff);
	glLightf(id, GL_SPOT_EXPONENT, exp);
}
// Ojo al 0.0: la dirección de emisión del foco es vector
void SpotLight::setSpot(glm::fvec3 dir, GLfloat cf, GLfloat e) {
	direction = glm::fvec4(dir, 0.0); cutoff = cf;
	exp = e;
}
