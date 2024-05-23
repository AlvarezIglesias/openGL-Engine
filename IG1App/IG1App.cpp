#include "IG1App.h"
#include "CheckML.h"
#include <iostream>


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

	Scene* sP4 = new Scene();
	Peon* p = new Peon();
	p->mScale = { 100,100,100 };
	p->mColor = { 237.0 / 255.0, 215.0 / 255.0, 149.0/255.0 , 1};
	sP4->initPr3({p, new BoxOutline(100)});
	mScenes.push_back(sP4);

	setScene(0);

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
	for( Scene* s : mScenes)
		delete s;

	for(Camera* c : mCameras) delete c;
	for(Viewport* vp : mViewPorts) delete vp;

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
IG1App::display2V() const{

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
			if (current_scene()->hasAdvandcedTIE()) current_scene()->disableTieLight();
			setScene(--mId);
			current_scene()->setBackground();
			break;
		case '1':
			if (current_scene()->hasAdvandcedTIE()) current_scene()->disableTieLight();
			setScene(++mId);
			current_scene()->setBackground();
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
			photo->save("image.bmp");
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
			m2Vistas = !m2Vistas;
			break;
		case 'q':
			// APARTADO 76
			current_scene()->dirLight->enable();
			break;
		case 'w':
			// APARTADO 76
			current_scene()->dirLight->disable();
			break;
		case 'a':
			// APARTADO 77
			current_scene()->posLight->enable();
			break;
		case 's':
			// APARTADO 77
			current_scene()->posLight->disable();
			break;
		case 'z':
			// APARTADO 78
			current_scene()->spotLight->enable();
			break;
		case 'x':
			// APARTADO 78
			current_scene()->spotLight->disable();
			break;
		case 'v':
			// APARTADO 79
			if (current_scene()->hasAdvandcedTIE()) current_scene()->enableTieLight();
			break;
		case 'b':
			// APARTADO 79
			if (current_scene()->hasAdvandcedTIE()) current_scene()->disableTieLight();
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
	
	if (mMouseButt==0) {
		current_camera()->moveLR(delta.x);
		current_camera()->moveUD(delta.y);
	}else if (mMouseButt == 2) {
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
		current_camera()->moveFB(d*5);
	}
	else {
		current_camera()->setScale(d*0.10);

	}
	glutPostRedisplay();

}


void
IG1App::update() {
	
	if (current_camera() == mCameras[1]) {
		mCameras[1]->update();
		mScenes[0]->update();
	}
	else {
		//mScenes[2]->update();
		mScenes[mId]->update();
	}

	glutPostRedisplay();
}


Camera* 
IG1App::current_camera() const {
	if (!m2Vistas) return mCameras[0];
	else {
		if (mMouseCoord.x <= glutGet(GLUT_WINDOW_HEIGHT) / 2.0) return mCameras[0];
		else return mCameras[1];
	}
}
