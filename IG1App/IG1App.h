#ifndef _H_IG1App_H_
#define _H_IG1App_H_

// #include <gl/GL.h>    // OpenGL
// #include <gl/GLU.h>   // OpenGL Utility Library
// #include <GL/glut.h>  // OpenGL Utility Toolkit

#include <GL/freeglut.h> // OpenGL Utility Toolkit
#include <glm/glm.hpp>   // OpenGL Mathematics

#include <vector>

#include "Camera.h"
#include "Scene.h"
#include "Viewport.h"

#include "Light.h"

#include "EntityPr4.h"
#include "EntityPr2.h"
#include "EntityPr1.h"
#include "Entity.h"

class IG1App
{
public:
	// static single instance (singleton pattern)
	static IG1App s_ig1app;

	IG1App(IG1App const& J) = delete;         // no copy constructor
	void operator=(IG1App const& J) = delete; // no copy assignment

	// Viewport position and size
	Viewport const& viewPort() { return *(mViewPorts[0]); };
	// Camera position, view volume and projection
	Camera const& camera() { return *(mCameras[0]); };
	// Graphics objects of the scene
	std::vector<Scene*> const& scene() { return mScenes; };

	void run();   // the main event processing loop
	void close(); // the application

protected:
	IG1App(){};
	~IG1App() { close(); };

	void init();
	void iniWinOpenGL();
	void free();

	void display() const;                      // the scene
	void display1V() const;
	void display2V() const;
	void resize(int newWidth, int newHeight);  // the viewport (without changing the scale)
	void key(unsigned char key, int x, int y); // keypress event
	void specialKey(int key, int x, int y);    // keypress event for special characters

	void mouse(int button, int state, int x, int y);
	void motion(int x, int y);
	void mouseWheel(int n, int d, int x, int y);

	// APARTADO 12
	void setScene(int id) { mId = id; };


	// APARTADO 16
	static void s_update() { s_ig1app.update(); };
	// APARTADO 13
	void update();

	Scene* current_scene() const { return mScenes[mId % mScenes.size()]; };
	Camera* current_camera() const;

	// static callbacks
	static void s_display() { s_ig1app.display(); };
	static void s_resize(int newWidth, int newHeight) { s_ig1app.resize(newWidth, newHeight); };
	static void s_key(unsigned char key, int x, int y) { s_ig1app.key(key, x, y); };
	static void s_specialKey(int key, int x, int y) { s_ig1app.specialKey(key, x, y); };

	static void s_mouse(int button, int state, int x, int y) { s_ig1app.mouse(button, state, x, y); };
	static void s_motion(int x, int y) { s_ig1app.motion(x, y); };
	static void s_mouseWheel(int n, int d, int x, int y) { s_ig1app.mouseWheel(n, d, x, y); };

	// Viewport position and size
	std::vector<Viewport*> mViewPorts;
	// Camera position, view volume and projection
	std::vector<Camera*> mCameras;
	// Graphics objects of the scene
	std::vector<Scene*> mScenes;

	bool mStop = false; // main event processing loop
	int mWinId = 0;     // window's identifier
	int mWinW = 800;    // window's width
	int mWinH = 600;    // window's height

	int mId = 0;		// current scene
	bool m2Vistas = false;  // APARTADO 51 -> 0=normal, 1=2V

	Photo* photo;

	//APARTADO 52
	glm::dvec2 mMouseCoord = glm::dvec2(0, 0);
	int mMouseButt = 0;

};

#endif //_H_IG1App_H_
