#include "Scene.h"
#include "CheckML.h"
#include "Light.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "EntityPr1.h"

using namespace glm;

// Init Lights in order
DirLight* Scene::dirLight = new DirLight(); // GL_LIGHT0
PosLight* Scene::posLight = nullptr; // GL_LIGHT1
SpotLight* Scene::spotLight = nullptr; // GL_LIGHT2

void
Scene::init()
{
	setGL(); // OpenGL settings
	glEnable(GL_DEPTH_TEST);

	// allocate memory and load resources
	// Lights
	// Textures

	//gObjects.push_back(new RGBCube(200.0));
}

void
Scene::init(std::vector<Abs_Entity*> _gObjects) {
	setGL(); // OpenGL settings
	glEnable(GL_DEPTH_TEST);

	gObjects = _gObjects;
}

void
Scene::initPr2(std::vector<Abs_Entity*> _gObjects) {
	setGL(); // OpenGL settings
	glEnable(GL_DEPTH_TEST);

	gObjects = _gObjects;

	//Suelo
	/*Texture* text_bc = new Texture();
	text_bc->load("../bmps/baldosaC.bmp");
	gTextures.push_back(text_bc);
	_gObjects[0]->setTexture1(gTextures.back());

	//Caja
	Texture* text_box_1 = new Texture();
	text_box_1->load("../bmps/container.bmp");
	gTextures.push_back(text_box_1);
	_gObjects[1]->setTexture1(gTextures.back());

	Texture* text_box_2 = new Texture();
	text_box_2->load("../bmps/papelE.bmp");
	gTextures.push_back(text_box_2);
	_gObjects[1]->setTexture2(gTextures.back());

	//Estrella
	Texture* text_star = new Texture();
	text_star->load("../bmps/baldosaP.bmp");
	gTextures.push_back(text_star);
	_gObjects[2]->setTexture1(gTextures.back());

	//Parapet
	Texture* text_parapet = new Texture();
	text_parapet->load("../bmps/windowV.bmp");
	gTextures.push_back(text_parapet);
	_gObjects[3]->setTexture1(gTextures.back());

	//Grass
	Texture* text_grass = new Texture();
	text_grass->load("../bmps/grass.bmp", u8vec3(0.0,0.0,0.0), GLubyte(0.0));
	gTextures.push_back(text_grass);
	_gObjects[4]->setTexture1(gTextures.back());

	//Photo
	Texture* text_photo = new Texture();
	text_photo->load("../bmps/noche.bmp");
	gTextures.push_back(text_photo);
	_gObjects[5]->setTexture1(gTextures.back());*/

}

void
Scene::initPr3(std::vector<Abs_Entity*> && _gObjects) {
	setGL(); // OpenGL settings
	glEnable(GL_DEPTH_TEST);

	gObjects = _gObjects;

	for (Abs_Entity* e : gObjects) {
		e->initTextures(gTextures);
	}

}

void
Scene::free()
{ // release memory and resources

	for (Abs_Entity* el : gObjects) {
		delete el;
		el = nullptr;
	}

	for (Texture* t : gTextures){
		t->~Texture();
		delete t;
		t = nullptr;
	}

	delete dirLight;
	delete posLight;
}
void
Scene::setGL()
{
	// OpenGL basic setting
	//glClearColor(1.0, 1.0, 1.0, 1.0); // background color (alpha=1 -> opaque)
	
	glEnable(GL_COLOR_MATERIAL); // APARTADO 56

	//APARTADO 1
	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.a);

	glEnable(GL_DEPTH_TEST);          // enable Depth test

	//APARTADO 19
	glEnable(GL_TEXTURE_2D);
}
void
Scene::resetGL()
{
	glDisable(GL_COLOR_MATERIAL); // APARTADO 56

	glClearColor(1.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test

	glDisable(GL_TEXTURE_2D);
}

void
Scene::render(Camera const& cam) const
{
	//sceneDirLight(cam); // APARTADO 56
	dirLight->upload(cam.viewMat()); // APARTADO 76
	//posLight->upload(cam.viewMat()); // APARTADO 77
	//spotLight->upload(cam.viewMat()); // APARTADO 78

	cam.upload();

	for (Abs_Entity* el : gObjects) {
		el->render(cam.viewMat());
	}
}

// Apartado 13
void 
Scene::update() const
{
	for (Abs_Entity* el : gObjects) {
		el->update();
	}
}

// Apartado 56
void Scene::sceneDirLight(Camera const& cam) const {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glm::fvec4 posDir = { 1, 1, 1, 0 };
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(cam.viewMat()));
	glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(posDir));
	glm::fvec4 ambient = { 0, 0, 0, 1 };
	glm::fvec4 diffuse = { 1, 1, 1, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, value_ptr(ambient));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(GL_LIGHT0, GL_SPECULAR, value_ptr(specular));
}

// APARTADO 76
void Scene::initDirLight() {
	Scene::dirLight->setPosDir(glm::fvec3{1, 1, 1});
	Scene::dirLight->setAmb(glm::fvec4{ 0, 0, 0, 1 });
	Scene::dirLight->setDiff(glm::fvec4{ 1, 1, 1, 1 });
	Scene::dirLight->setSpec(glm::fvec4{ 0.5, 0.5, 0.5, 1 });
	
	Scene::dirLight->disable();
}

// APARTADO 77
void Scene::initPosLight() {
	/*Scene::posLight->setAmb(glm::fvec4{0, 0, 0, 1});
	Scene::posLight->setDiff(glm::fvec4{ 1, 1, 0, 1 });
	Scene::posLight->setSpec(glm::fvec4{ 0.5, 0.5, 0.5, 1 });
	Scene::posLight->setPosDir(glm::fvec3{ 100, 100, 0.0});

	Scene::posLight->enable();*/
}

// APARTADO 78
void Scene::initSpotLight() {
	/*Scene::spotLight->setAmb(glm::fvec4{0, 0, 0, 1});
	Scene::spotLight->setDiff(glm::fvec4{ 1, 1, 1, 1 });
	Scene::spotLight->setSpec(glm::fvec4{ 0.5, 0.5, 0.5, 1 });
	Scene::spotLight->setPosDir(glm::fvec3{ 0.0, 500, 500});

	Scene::spotLight->setSpot(glm::vec3{ 0.0, 0.0, -1.0 }, 20, 10);

	Scene::spotLight->enable();*/
}

void 
Scene::registerTexture(Texture* texture) {
	gTextures.push_back(texture);
}

void Scene::rotate()
{
	if (ship != nullptr) {
		ship->mRotation.y += 5;
		update();
	}
}

void Scene::orbit()
{
	if (ship != nullptr) {
		ship->mRotation.z += 5;
		update();
	}
}


