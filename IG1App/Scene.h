#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Light.h"
#include "Entity.h"
#include "EntityPr4.h"

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
	void initPr3(std::vector<Abs_Entity*> && _gObjects);

	void render(Camera const& cam) const;

	// APARTADO 13
	void update() const;

	// APARTADO 56
	void sceneDirLight(Camera const& cam) const;

	void registerTexture(Texture* texture);

	// APARTADO 68

	void rotate();
	void orbit();
	void setShip(ShipOrbit* _ship) { ship = _ship; };

	// APARTADO 76
	static DirLight* dirLight;
	static void initDirLight();

	// APARTADO 77
	static PosLight* posLight;
	static void initPosLight();

	// APARTADO 78
	static SpotLight* spotLight;
	static void initSpotLight();

protected:
	void free();
	void setGL();
	void resetGL();

	ShipOrbit * ship = nullptr;

	std::vector<Abs_Entity*> gObjects; // Entities (graphic objects) of the scene
	std::vector<Texture*> gTextures; // APARTADO 19
};

#endif //_H_Scene_H_
