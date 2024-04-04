#include "Scene.h"
#include "CheckML.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "EntityPr1.h"

using namespace glm;

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
	Texture* text_bc = new Texture();
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
	_gObjects[5]->setTexture1(gTextures.back());

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
}
void
Scene::setGL()
{
	// OpenGL basic setting
	//glClearColor(1.0, 1.0, 1.0, 1.0); // background color (alpha=1 -> opaque)
	
	//APARTADO 1
	glClearColor(0.6, 0.7, 0.8, 1.0);

	glEnable(GL_DEPTH_TEST);          // enable Depth test

	//APARTADO 19
	glEnable(GL_TEXTURE_2D);
}
void
Scene::resetGL()
{
	glClearColor(1.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test

	glDisable(GL_TEXTURE_2D);
}

void
Scene::render(Camera const& cam) const
{
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
