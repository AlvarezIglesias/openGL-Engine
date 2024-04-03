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

	Scene* sPr2 = new Scene();
	photo = new Photo(200, 100);
	sPr2->init({ 
		  new Ground(400,400)
		, new Box(100)
		, new Star3D(30, 8, 30)
		, new GlassParapet(400)
		, new Grass(60,60)
		, photo
		});



	mScenes.push_back(sPr2);
	mCameras[0]->set3D();
	mCameras[1]->set3D();
	mCameras[1]->setCenital();
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
	(*mCameras[0]).setSize(mViewPorts[0]->width(), mViewPorts[0]->height());
	current_scene()->render(*mCameras[0]); // uploads the viewport and camera to the GPU
}

void 
IG1App::display2V() const{

	for (int i = 0; i < 2; i++)
	{
		mViewPorts[i]->setSize(mWinW / 2, mWinH);
		(*mCameras[i]).setSize(mViewPorts[i]->width(), mViewPorts[i]->height());
	}


	current_scene()->render(*mCameras[0]);

	mViewPorts[1]->setPos(mWinW / 2, 0);
	//(*mCameras[1]).setCenital();
	current_scene()->render((*mCameras[1]));
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
			mCameras[0]->setScale(+0.01); // zoom in  (increases the scale)
			break;
		case '-':
			mCameras[0]->setScale(-0.01); // zoom out (decreases the scale)
			break;
		case 'l':
			mCameras[0]->set3D();
			break;
		case 'o':
			mCameras[0]->set2D();
			break;
		case '0':
			setScene(0);
			break;
		case '1':
			setScene(1);
			break;
		case '2':
			setScene(21010);
			break;
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
			mCameras[0]->changePrj();
			break;
		case 'O':
			mCameras[0]->orbit(1, 1);
			break;
		case 'c':
			mCameras[0]->setCenital();
			break;
		case 'k':
			m2Vistas = !m2Vistas;
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
				mCameras[0]->pitchReal(-5);
			else
				//mCamera->pitch(1); // rotates 1 on the X axis
				mCameras[0]->pitchReal(5);
			break;
		case GLUT_KEY_LEFT:
			if (mdf == GLUT_ACTIVE_CTRL)
				//mCamera->yaw(1); // rotates 1 on the Y axis
				mCameras[0]->yawReal(5);
			else
				//mCamera->yaw(-1); // rotate -1 on the Y axis
				mCameras[0]->yawReal(-5);
			break;
		case GLUT_KEY_UP:
			//mCamera->roll(1); // rotates 1 on the Z axis
			mCameras[0]->rollReal(0.01);
			break;
		case GLUT_KEY_DOWN:
			//mCamera->roll(-1); // rotates -1 on the Z axis
			mCameras[0]->rollReal(-0.01);
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

}
void 
IG1App::motion(int x, int y) {

}
void 
IG1App::mouseWheel(int n, int d, int x, int y) {

}


void
IG1App::update() {
	current_scene()->update();
	glutPostRedisplay();
}