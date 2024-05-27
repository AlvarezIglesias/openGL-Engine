#include "IG1App.h"
#include "CheckML.h"
#include <iostream>

#define UPDATE_PERIOD 10
using namespace std;

// static single instance (singleton pattern)

IG1App IG1App::s_ig1app; // default constructor (constructor with no parameters)

void
IG1App::close()
{
	if (!mStop) { // if main loop has not stopped
		cout << "Closing glut...\n";
		glutLeaveMainLoop(); // stops main loop and destroy the OpenGL context
		mStop = true;        // main loop stopped
	}
	free();
}

void
IG1App::run() // enters the main event processing loop
{
	if (mWinId == 0) {      // if not initialized
		init();         // initialize the application
		glutMainLoop(); // enters the main event processing loop
		mStop = true;   // main loop has stopped
	}
}

void
IG1App::init()
{
	// create an OpenGL Context
	iniWinOpenGL();

	// create the scene after creating the context
	// allocate memory and resources
	mViewPorts =
	{ new Viewport(mWinW, mWinH), new Viewport(mWinW, mWinH) };

	for (Viewport* vp : mViewPorts) mCameras.push_back(new Camera(vp));

	// Set Lights
	glEnable(GL_LIGHTING);

	Scene::initDirLight(); // APARTADO 76
	Scene::initPosLight(); // APARTADO 77
	Scene::initSpotLight(); // APARTADO 78

	// Pr4

	std::vector<Abs_Entity*> objects;

	Scene* sP4 = new Scene();

	Material::whitePlastic->setWhitePlastic();
	Material::blackPlastic->setBlackPlastic();
	Material::copper->setCopper();
	glm::dvec4 whiteColor = { 237.0 / 255.0, 215.0 / 255.0, 149.0 / 255.0 , 1.0 };
	glm::dvec4 blackColor = { 0.1, 0.1, 0.1 , 1.0 };

	// ********************************************************** Piezas ajedrez


	Material* material = Material::whitePlastic;
	for (int i = 0; i < 8; i++)
	{

		Peon* p = new Peon();
		p->mPosition = { i * 100 - 350, 0, 50 * 5 };
		p->mScale = { 15,15,15 };
		p->mColor = whiteColor;
		p->setMaterial(material);
		objects.push_back(p);
	}

	Torre* torre = new Torre();
	torre->mPosition = { -350,0,50 * 7 };
	torre->mScale = { 15,15,15 };
	torre->mColor = whiteColor;
	torre->setMaterial(material);
	objects.push_back(torre);

	Torre* torre2 = new Torre();
	torre2->mPosition = { 350,0,50 * 7 };
	torre2->mScale = { 15,15,15 };
	torre2->mColor = whiteColor;
	torre2->setMaterial(material);
	objects.push_back(torre2);


	CompoundEntity* caballo = new Caballo();
	caballo->mPosition = { -250,0,50 * 7 };
	caballo->mScale = { 15,15,15 };
	caballo->mRotation = { 0, -90, 0 };
	((EntityWithMaterial*)caballo->getChildren(0))->setMaterial(Material::whitePlastic);
	((EntityWithMaterial*)caballo->getChildren(1))->setMaterial(Material::whitePlastic);
	objects.push_back(caballo);


	CompoundEntity* caballo2 = new Caballo();
	caballo2->mPosition = { 250,0,50 * 7 };
	caballo2->mScale = { 15,15,15 };
	caballo2->mRotation = { 0, -90, 0 };
	((EntityWithMaterial*)caballo2->getChildren(0))->setMaterial(Material::whitePlastic);
	((EntityWithMaterial*)caballo2->getChildren(1))->setMaterial(Material::whitePlastic);
	objects.push_back(caballo2);

	Alfil* alfil = new Alfil();
	alfil->mPosition = { -150,0,50 * 7 };
	alfil->mScale = { 15,15,15 };
	alfil->mColor = whiteColor;
	alfil->setMaterial(material);
	objects.push_back(alfil);

	Alfil* alfil2 = new Alfil();
	alfil2->mPosition = { 150,0,50 * 7 };
	alfil2->mScale = { 15,15,15 };
	alfil2->mColor = whiteColor;
	alfil2->setMaterial(material);
	objects.push_back(alfil2);

	Reina* reina = new Reina();
	reina->mPosition = { -50,0,50 * 7 };
	reina->mScale = { 15,15,15 };
	reina->mColor = whiteColor;
	reina->setMaterial(material);
	objects.push_back(reina);

	Rey* rey = new Rey();
	rey->mPosition = { 50,0,50 * 7 };
	rey->mScale = { 15,15,15 };
	rey->mColor = whiteColor;
	rey->setMaterial(material);
	objects.push_back(rey);


	material = Material::blackPlastic;
	for (int i = 0; i < 8; i++)
	{
		Peon* p = new Peon();
		p->mPosition = { i * 100 - 350, 0, 50 * -5 };
		p->mScale = { 15,15,15 };
		p->mColor = blackColor;
		p->setMaterial(material);
		objects.push_back(p);
	}

	Torre* torreN = new Torre();
	torreN->mPosition = { -350,0,-50 * 7 };
	torreN->mScale = { 15,15,15 };
	torreN->mColor = blackColor;
	torreN->setMaterial(material);
	objects.push_back(torreN);

	Torre* torreN2 = new Torre();
	torreN2->mPosition = { 350,0,-50 * 7 };
	torreN2->mScale = { 15,15,15 };
	torreN2->mColor = blackColor;
	torreN2->setMaterial(material);
	objects.push_back(torreN2);


	CompoundEntity* caballoN = new Caballo();
	caballoN->mPosition = { -250,0,-50 * 7 };
	caballoN->mScale = { 15,15,15 };
	caballoN->mRotation = { 0, 90, 0 };
	((EntityWithMaterial*)caballoN->getChildren(0))->setMaterial(Material::blackPlastic);
	((EntityWithMaterial*)caballoN->getChildren(1))->setMaterial(Material::blackPlastic);
	objects.push_back(caballoN);


	CompoundEntity* caballoN2 = new Caballo();
	caballoN2->mPosition = { 250,0,-50 * 7 };
	caballoN2->mScale = { 15,15,15 };
	caballoN2->mRotation = { 0, 90, 0 };
	((EntityWithMaterial*)caballoN2->getChildren(0))->setMaterial(Material::blackPlastic);
	((EntityWithMaterial*)caballoN2->getChildren(1))->setMaterial(Material::blackPlastic);
	objects.push_back(caballoN2);

	Alfil* alfilN = new Alfil();
	alfilN->mPosition = { -150,0,-50 * 7 };
	alfilN->mScale = { 15,15,15 };
	alfilN->mColor = blackColor;
	alfilN->setMaterial(material);
	objects.push_back(alfilN);

	Alfil* alfilN2 = new Alfil();
	alfilN2->mPosition = { 150,0,-50 * 7 };
	alfilN2->mScale = { 15,15,15 };
	alfilN2->mColor = blackColor;
	alfilN2->setMaterial(material);
	objects.push_back(alfilN2);

	Reina* reinaN = new Reina();
	reinaN->mPosition = { 50,0,-50 * 7 };
	reinaN->mScale = { 15,15,15 };
	reinaN->mColor = blackColor;
	reinaN->setMaterial(material);
	objects.push_back(reinaN);

	Rey* reyN = new Rey();
	reyN->mPosition = { -50,0,-50 * 7 };
	reyN->mScale = { 15,15,15 };
	reyN->mColor = blackColor;
	reyN->setMaterial(material);
	objects.push_back(reyN);

	// ********************************************************** Flexo

	CompoundEntity* compoundBaseFlexo = new CompoundEntity();

	Cylinder* baseFlexo = new Cylinder(100, 100, 30);
	baseFlexo->mRotation = { -90,0,0 };
	baseFlexo->mColor = blackColor;
	compoundBaseFlexo->addEntity(baseFlexo);

	Disk* tapaBaseFlexo = new Disk(0, 100);
	tapaBaseFlexo->mRotation = { -90,0,0 };
	tapaBaseFlexo->mPosition = { 0,30,0 };
	tapaBaseFlexo->mColor = blackColor;
	compoundBaseFlexo->addEntity(tapaBaseFlexo);

	Cylinder* primerEjeFlexo = new Cylinder(30, 30, 30);
	primerEjeFlexo->mRotation = { -90,0,0 };
	primerEjeFlexo->mPosition = { 60,30,0 };
	primerEjeFlexo->mColor = blackColor;
	compoundBaseFlexo->addEntity(primerEjeFlexo);

	Disk* tapaPrimerEjeFlexo = new Disk(0, 30);
	tapaPrimerEjeFlexo->mRotation = { -90,0,0 };
	tapaPrimerEjeFlexo->mPosition = { 60,60,0 };
	tapaPrimerEjeFlexo->mColor = blackColor;
	compoundBaseFlexo->addEntity(tapaPrimerEjeFlexo);

	// Brazo 1

	Eje* pivotePrimerEje = new Eje(7, -30, 30);
	pivotePrimerEje->mPosition = { 60,30,0 };
	pivotePrimerEje->mRotation = { 0,0,-30 };
	compoundBaseFlexo->addEntity(pivotePrimerEje);

	Cylinder* brazo1Flexo = new Cylinder(10, 10, 400);
	brazo1Flexo->mRotation = { -90,0,0 };
	brazo1Flexo->mPosition = { 0,0,0 };
	brazo1Flexo->mColor = blackColor;
	pivotePrimerEje->addEntity(brazo1Flexo);

	Sphere* bolaSegundoEje = new Sphere(30);
	bolaSegundoEje->mPosition = { 0,385,0 };
	bolaSegundoEje->mColor = blackColor;
	pivotePrimerEje->addEntity(bolaSegundoEje);

	//Brazo 2

	Eje* pivoteSegundoEje = new Eje(15, 90, 60);
	pivoteSegundoEje->mPosition = { 0,385,0 };
	pivoteSegundoEje->mRotation = { 0,0,60 };
	pivotePrimerEje->addEntity(pivoteSegundoEje);

	Cylinder* brazo2Flexo = new Cylinder(10, 10, 400);
	brazo2Flexo->mRotation = { -90,0,0 };
	brazo2Flexo->mPosition = { 0,0,0 };
	brazo2Flexo->mColor = blackColor;
	pivoteSegundoEje->addEntity(brazo2Flexo);

	Sphere* bolaTercerEje = new Sphere(30);
	bolaTercerEje->mPosition = { 0,385,0 };
	bolaTercerEje->mColor = blackColor;
	pivoteSegundoEje->addEntity(bolaTercerEje);

	//Brazo 3

	Eje* pivoteTercerEje = new Eje(-30, 0, 30);
	pivoteTercerEje->mPosition = { 0,385,0 };
	pivoteTercerEje->mRotation = { 0,0,60 };
	pivoteSegundoEje->addEntity(pivoteTercerEje);

	Cylinder* brazo3Flexo = new Cylinder(10, 10, 200);
	brazo3Flexo->mRotation = { -90,0,0 };
	brazo3Flexo->mPosition = { 0,0,0 };
	brazo3Flexo->mColor = blackColor;
	pivoteTercerEje->addEntity(brazo3Flexo);

	PantallaFlexo* pantallaFlexo = new PantallaFlexo();
	pantallaFlexo->mScale = { 30,20,20 };
	pantallaFlexo->mRotation = { 0,0,90 };
	pantallaFlexo->mPosition = { +20,175,0 };
	pantallaFlexo->mColor = blackColor;
	pivoteTercerEje->addEntity(pantallaFlexo);

	Sphere* bombilla = new Sphere(30);
	bombilla->mPosition = { -80,175,0 };
	bombilla->mColor = { 1,1,0,1 };
	pivoteTercerEje->addEntity(bombilla);

	//*********************************************************** Mesa

	Disk* superficieMesa = new Disk(0, 1000);
	superficieMesa->addTexturePath("../bmps/terciopelo.bmp");
	superficieMesa->mPosition = { 0,-30,0 };
	superficieMesa->mRotation = { -90,0,0 };
	objects.push_back(superficieMesa);

	Cylinder* faldaMesa = new Cylinder(1000, 1100, 1000);
	faldaMesa->addTexturePath("../bmps/terciopelo.bmp");
	faldaMesa->mPosition = { 0,-30,0 };
	faldaMesa->mRotation = { 90,0,0 };
	objects.push_back(faldaMesa);

	Reina* pataMesa = new Reina();
	pataMesa->shouldUpdate = false;
	pataMesa->mScale = { 160,200,160 };
	pataMesa->mRotation = { 0,0,0 };
	pataMesa->mPosition = { 0,-2000,0 };
	pataMesa->mColor = { 56.0 / 255.0, 29.0 / 255.0, 7.0 / 255.0 , 255.0 / 255.0 };
	pataMesa->setMaterial(material);
	objects.push_back(pataMesa);

	Luz* luz = new Luz(30, 200, 300);
	luz->mPosition = { -80,175,0 };
	luz->mRotation = { 0,-90,0 };
	luz->mColor = { 1,1,0,1 };
	pivoteTercerEje->addEntity(luz);

	compoundBaseFlexo->mPosition = { 600,0,0 };

	DensePlain* cb = new DensePlain(50);
	cb->addTexturePath("../bmps/chessBoard.bmp");
	cb->mScale = { 800,800,800 };
	cb->mRotation = { -90,0,0 };
	cb->mPosition = { 0,0,0 };
	cb->setMaterial(Material::whitePlastic);
	objects.push_back(cb);

	DensePlain* cbLateral1 = new DensePlain(5);
	cbLateral1->addTexturePath("../bmps/container.bmp");
	cbLateral1->mScale = { 800,30,1 };
	cbLateral1->mRotation = { 0,0,0 };
	cbLateral1->mPosition = { 0,-15,400 };
	cbLateral1->setMaterial(material);
	objects.push_back(cbLateral1);

	DensePlain* cbLateral2 = new DensePlain(5);
	cbLateral2->addTexturePath("../bmps/container.bmp");
	cbLateral2->mScale = { 800,30,1 };
	cbLateral2->mRotation = { 0,180,0 };
	cbLateral2->mPosition = { 0,-15,-400 };
	cbLateral2->setMaterial(material);
	objects.push_back(cbLateral2);

	DensePlain* cbLateral3 = new DensePlain(5);
	cbLateral3->addTexturePath("../bmps/container.bmp");
	cbLateral3->mScale = { 1,30,800 };
	cbLateral3->mRotation = { 0,90,0 };
	cbLateral3->mPosition = { 400,-15,0 };
	cbLateral3->setMaterial(material);
	objects.push_back(cbLateral3);

	DensePlain* cbLateral4 = new DensePlain(5);
	cbLateral4->addTexturePath("../bmps/container.bmp");
	cbLateral4->mScale = { 1,30,800 };
	cbLateral4->mRotation = { 0,270,0 };
	cbLateral4->mPosition = { -400,-15,0 };
	cbLateral4->setMaterial(material);
	objects.push_back(cbLateral4);


	DensePlain* suelo = new DensePlain(200, 5);
	suelo->addTexturePath("../bmps/baldosa.bmp");
	suelo->mScale = { 5000,5000,5000 };
	suelo->mRotation = { -90,0,0 };
	suelo->mPosition = { 0,-2000,0 };
	objects.push_back(suelo);


	Vela* vela = new Vela(400, 400, 20);
	vela->initialPos = { 1800, -2000, 0 };
	vela->mPosition = { 1800, -2000, 0 };
	objects.push_back(vela);

	Vela* vela1 = new Vela(300, 300, 60);
	vela1->initialPos = { -1800, -2000, 0 };
	vela1->mPosition = { -1800, -2000, 0 };
	objects.push_back(vela1);

	Vela* vela2 = new Vela(250, 250, 120);
	vela2->initialPos = { 0, -2000, 1800 };
	vela2->mPosition = { 0, -2000, 1800 };
	objects.push_back(vela2);

	Vela* vela3 = new Vela(400, 400, 240);
	vela3->initialPos = { 0 , -2000, -1800 };
	vela3->mPosition = { 0 , -2000, -1800 };
	objects.push_back(vela3);



	compoundBaseFlexo->mScale = { 1.5,1.5,1.5 };
	objects.push_back(compoundBaseFlexo); //Ultimo en aniadirse para que el cono de luz se renderice bien

	CirculoMagia* letras = new CirculoMagia(1200, 1200, 1000);
	letras->mRotation = { -90,0,0 };
	letras->mScale = { 2,2,2 };
	letras->mPosition = { 0,-1800,0 };
	objects.push_back(letras);

	sP4->backgroundColor = { 21.0 / 255.0, 13.0 / 255.0, 41.0 / 255.0, 1.0 };
	sP4->initPr3({ std::vector<Abs_Entity*>(objects) });
	mScenes.push_back(sP4);


	setScene(0);
	current_camera()->set3D();
	current_camera()->upload();


}

void
IG1App::iniWinOpenGL()
{ // Initialization
	cout << "Starting glut...\n";
	int argc = 0;
	glutInit(&argc, nullptr);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE); // GLUT_CORE_PROFILE
	glutInitContextFlags(GLUT_DEBUG);                   // GLUT_FORWARD_COMPATIBLE

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(mWinW, mWinH); // window size
	// glutInitWindowPosition (140, 140);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE |
		GLUT_DEPTH /*| GLUT_STENCIL*/); // RGBA colors, double buffer, depth
	// buffer and stencil buffer

	mWinId = glutCreateWindow(
		"IG1App"); // with its associated OpenGL context, return window's identifier

	// Callback registration
	glutReshapeFunc(s_resize);
	glutKeyboardFunc(s_key);
	glutSpecialFunc(s_specialKey);
	glutDisplayFunc(s_display);
	glutMouseFunc(s_mouse);
	glutMotionFunc(s_motion);
	glutMouseWheelFunc(s_mouseWheel);



	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}

void
IG1App::free()
{ // release memory and resources
	for (Scene* s : mScenes)
		delete s;

	for (Camera* c : mCameras) delete c;
	for (Viewport* vp : mViewPorts) delete vp;

	delete Material::whitePlastic;
	delete Material::blackPlastic;
	delete Material::copper;

}

void
IG1App::display() const
{ // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clears the back buffer
	if (!m2Vistas) display1V(); // uploads the viewport and camera to the GPU
	else display2V();
	glutSwapBuffers(); // swaps the front and back buffer
}

void
IG1App::display1V() const
{
	mViewPorts[0]->setSize(mWinW, mWinH);
	mCameras[0]->setSize(mViewPorts[0]->width(), mViewPorts[0]->height());
	current_scene()->render(*mCameras[0]); // uploads the viewport and camera to the GPU
}

void
IG1App::display2V() const {

	for (int i = 0; i < 2; i++)
	{
		mViewPorts[i]->setSize(mWinW / 2, mWinH);
		(*mCameras[i]).setSize(mViewPorts[i]->width(), mViewPorts[i]->height());
	}


	mScenes[2]->render(*mCameras[0]);

	mViewPorts[1]->setPos(mWinW / 2, 0);
	mScenes[0]->render((*mCameras[1]));
}


void
IG1App::resize(int newWidth, int newHeight)
{
	mWinW = newWidth;
	mWinH = newHeight;

	for (int i = 0; i < mViewPorts.size(); i++) {
		// Resize Viewport to the new window size
		mViewPorts[i]->setSize(newWidth, newHeight);
		// Resize Scene Visible Area such that the scale is not modified
		mCameras[i]->setSize(mViewPorts[i]->width(), mViewPorts[i]->height());
	}
}

void
IG1App::key(unsigned char key, int x, int y)
{
	bool need_redisplay = true;

	switch (key) {
	case 27:                     // Escape key
		glutLeaveMainLoop(); // stops main loop and destroy the OpenGL context
		break;
	case '+':
		current_camera()->setScale(+0.01); // zoom in  (increases the scale)
		break;
	case '-':
		current_camera()->setScale(-0.01); // zoom out (decreases the scale)
		break;
	case 'l':
		current_camera()->set3D();
		break;
	case 'o':
		current_camera()->set2D();
		break;
	case '0':
		//if (current_scene()->hasAdvandcedTIE()) current_scene()->disableTieLight();
		//setScene(--mId);
		//current_scene()->setBackground();
		break;
	case '1':
		//if (current_scene()->hasAdvandcedTIE()) current_scene()->disableTieLight();
		//setScene(++mId);
		//current_scene()->setBackground();
		break;
		//case '2':
		//	setScene(2);
		//	break;
	case 'u':
		update();
		break;
	case 'U':
		// APARTADO 16
		glutIdleFunc(s_update);
		break;
	case 'F':
		// APARTADO 37
		//photo->save("image.bmp");
		break;
	case 'p':
		current_camera()->changePrj();
		break;
	case 'O':
		current_camera()->orbit(1, 1);
		break;
	case 'c':
		current_camera()->setCenital();
		break;
	case 'f':
		current_scene()->rotate();
		break;
	case 'g':
		current_scene()->orbit();
		break;
	case 'k':
		//m2Vistas = !m2Vistas;
		break;
	case 'q':
		// APARTADO 76
		PantallaFlexo::spotLight->enable();
		break;
	case 'w':
		// APARTADO 76
		PantallaFlexo::spotLight->disable();
		break;
	case 'a':
		// APARTADO 77
		current_scene()->dirLight->enable();
		current_scene()->backgroundColor = { 100.0 / 255.0, 103.0 / 255.0, 41.0 / 255.0, 1.0 };
		current_scene()->setBackground();

		break;
	case 's':
		// APARTADO 77
		current_scene()->dirLight->disable();
		current_scene()->backgroundColor = { 21.0 / 255.0, 13.0 / 255.0, 41.0 / 255.0, 1.0 };
		current_scene()->setBackground();
		break;
	case 'z':
		// APARTADO 78
		//current_scene()->spotLight->enable();
		break;
	case 'x':
		// APARTADO 78
		//current_scene()->spotLight->disable();
		break;
	case 'v':
		// APARTADO 79
		//if (current_scene()->hasAdvandcedTIE()) current_scene()->enableTieLight();
		break;
	case 'b':
		// APARTADO 79
		//if (current_scene()->hasAdvandcedTIE()) current_scene()->disableTieLight();
		break;
	default:
		need_redisplay = false;
		break;
	} // switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to
	// display()
}

void
IG1App::specialKey(int key, int x, int y)
{
	bool need_redisplay = true;
	int mdf = glutGetModifiers(); // returns the modifiers (Shift, Ctrl, Alt)

	switch (key) {
	case GLUT_KEY_RIGHT:
		if (mdf == GLUT_ACTIVE_CTRL)
			//mCamera->pitch(-1); // rotates -1 on the X axis
			current_camera()->pitchReal(-5);
		else
			//mCamera->pitch(1); // rotates 1 on the X axis
			current_camera()->pitchReal(5);
		break;
	case GLUT_KEY_LEFT:
		if (mdf == GLUT_ACTIVE_CTRL)
			//mCamera->yaw(1); // rotates 1 on the Y axis
			current_camera()->yawReal(5);
		else
			//mCamera->yaw(-1); // rotate -1 on the Y axis
			current_camera()->yawReal(-5);
		break;
	case GLUT_KEY_UP:
		//mCamera->roll(1); // rotates 1 on the Z axis
		current_camera()->rollReal(0.01);
		break;
	case GLUT_KEY_DOWN:
		//mCamera->roll(-1); // rotates -1 on the Z axis
		current_camera()->rollReal(-0.01);
		break;
	default:
		need_redisplay = false;
		break;
	} // switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to
	// display()
}

void
IG1App::mouse(int button, int state, int x, int y) {
	mMouseButt = button;
	mMouseCoord = glm::dvec2(x, glutGet(GLUT_WINDOW_HEIGHT) - y);

}
void
IG1App::motion(int x, int y) {

	glm::dvec2 newPos = glm::dvec2(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
	glm::dvec2 delta = mMouseCoord - newPos;

	if (mMouseButt == 0) {
		current_camera()->moveLR(delta.x);
		current_camera()->moveUD(delta.y);
	}
	else if (mMouseButt == 2) {
		current_camera()->yawReal(delta.x);
		current_camera()->pitchReal(delta.y);
	}
	mMouseCoord = newPos;

	glutPostRedisplay();
}
void
IG1App::mouseWheel(int n, int d, int x, int y) {

	int mdf = glutGetModifiers(); // returns the modifiers (Shift, Ctrl, Alt)

	if (mdf == GLUT_ACTIVE_CTRL) {
		current_camera()->moveFB(d * 5);
	}
	else {
		current_camera()->setScale(d * 0.10);

	}
	glutPostRedisplay();

}


void IG1App::update()
{
	int now = glutGet(GLUT_ELAPSED_TIME);

	if (now - mLastUpdateTime >= UPDATE_PERIOD) {


		if (current_camera() == mCameras[1]) {
			mCameras[1]->update();
			mScenes[0]->update();
		}
		else {
			//mScenes[2]->update();
			mScenes[mId]->update();
		}

		glutPostRedisplay();


		mLastUpdateTime = now;
	}
}

Camera*
IG1App::current_camera() const {
	if (!m2Vistas) return mCameras[0];
	else {
		if (mMouseCoord.x <= glutGet(GLUT_WINDOW_HEIGHT) / 2.0) return mCameras[0];
		else return mCameras[1];
	}
}
