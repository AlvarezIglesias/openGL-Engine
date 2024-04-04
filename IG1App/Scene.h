#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Entity.h"

#include <vector>

class Scene
{
public:
	Scene() = default;
	~Scene()
	{
		free();
		resetGL();
	};

	Scene(const Scene& s) = delete;            // no copy constructor
	Scene& operator=(const Scene& s) = delete; // no copy assignment

	void init();
	void init(std::vector<Abs_Entity*> _gObjects);
	void initPr2(std::vector<Abs_Entity*> _gObjects);

	void render(Camera const& cam) const;

	// APARTADO 13
	void update() const;

protected:
	void free();
	void setGL();
	void resetGL();

	std::vector<Abs_Entity*> gObjects; // Entities (graphic objects) of the scene
	std::vector<Texture*>gTextures; // APARTADO 19
};

#endif //_H_Scene_H_
