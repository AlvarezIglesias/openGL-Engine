#include "Entity.h"
#include "EntityPr2.h"
#include "Texture.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

//----------------------------------------------------------------------------------------------
// Ground
//----------------------------------------------------------------------------------------------


Ground::Ground(GLdouble w, GLdouble h)
	: Abs_Entity()
{
	mTexturePaths = { "../bmps/baldosaC.bmp" };
	mMesh = Mesh::generateRectangleTexCor(w, h, 4, 4);
	mRotation = dvec3(90, 0, 90);
}

Ground::~Ground()
{
	delete mMesh;
	mMesh = nullptr;
};

void
Ground::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat
			* mModelMat
			* rotate(dmat4(1), radians(mRotation.x), dvec3(1, 0, 0))
			* rotate(dmat4(1), radians(mRotation.z), dvec3(0, 0, 1)) // glm matrix multiplication
			* translate(dmat4(1), mPosition);

		upload(aMat);

		glColor4d(1.0, 1.0, 1.0, 1.0);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		mTextures[0]->bind(GL_REPLACE);
		
		mMesh->render();

		mTextures[0]->unbind();
		glPointSize(1);
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glPolygonMode(GL_FRONT, GL_FILL);
	}
}



//----------------------------------------------------------------------------------------------
// BoxOutline
//----------------------------------------------------------------------------------------------

BoxOutline::BoxOutline(GLdouble length)
	: Abs_Entity()
{
	mTexturePaths = { "../bmps/container.bmp", "../bmps/papelE.bmp" };
	mMesh = Mesh::generateBoxOutline(length);
	//mRotation = dvec3(90, 0, 90);
}

BoxOutline::~BoxOutline()
{
	delete mMesh;
	mMesh = nullptr;
};

void
BoxOutline::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		glColor4d(1.0, 1.0, 1.0, 1.0);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glEnable(GL_CULL_FACE);

		mTextures[0]->bind(GL_MODULATE);
		glCullFace(GL_BACK);
		mMesh->render();
		mTextures[0]->unbind();

		mTextures[1]->bind(GL_MODULATE);
		glCullFace(GL_FRONT);
		mMesh->render();
		mTextures[1]->unbind();

		glDisable(GL_CULL_FACE);


		glPointSize(1);
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glPolygonMode(GL_FRONT, GL_FILL);


	}
}

//----------------------------------------------------------------------------------------------
// Star3D
//----------------------------------------------------------------------------------------------


Star3D::Star3D(GLdouble re, GLuint np, GLdouble h)
	: Abs_Entity()
{
	mTexturePaths = { "../bmps/baldosaP.bmp" };
	mMesh = Mesh::generateStar3DTexCor(re, np, h);
	mPosition = dvec3(-140, 200, -140);
}

Star3D::~Star3D()
{
	delete mMesh;
	mMesh = nullptr;
};

void
Star3D::update()
{
	mRotation = dvec3(0.0, mRotation.y + 0.1, mRotation.z + 0.1);
};

void
Star3D::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat
			* mModelMat;

		dmat4 aMat1 = aMat
			* translate(dmat4(1), mPosition)
			* rotate(dmat4(1), radians(mRotation.y), dvec3(0, 1, 0))
			* rotate(dmat4(1), radians(mRotation.z), dvec3(0, 0, 1)) 
			;

		upload(aMat1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mTextures[0]->bind(GL_REPLACE);
		mMesh->render();
		mTextures[0]->unbind();

		dmat4 aMat2 = aMat1
			* rotate(dmat4(1), radians(180.0), dvec3(0, 1, 0));
			//* translate(dmat4(1), mPosition);

		upload(aMat2);
		mTextures[0]->bind(GL_REPLACE);
		mMesh->render();
		mTextures[0]->unbind();

		glPointSize(1);
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glPolygonMode(GL_FRONT, GL_FILL);
	}
}


//----------------------------------------------------------------------------------------------
// GlassParapet
//----------------------------------------------------------------------------------------------

GlassParapet::GlassParapet(GLdouble _length)
	: Abs_Entity()
{
	mTexturePaths = { "../bmps/windowV.bmp" };
	mMesh = Mesh::generateBoxOutline(_length);
	length = _length;
	
}

GlassParapet::~GlassParapet()
{
	delete mMesh;
	mMesh = nullptr;
};

void
GlassParapet::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		dmat4 aMat = modelViewMat
			* mModelMat
			* scale(dmat4(1), dvec3(1.0, 0.3, 1.0))
			* translate(dmat4(1), dvec3(0.0, length / 2, 0.0))
			;

		upload(aMat);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4d(1.0, 1.0, 1.0, 0.2);
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);// Si no, hay caras que no estan bien ordenadas en z


		mTextures[0]->bind(GL_MODULATE);
		mMesh->render();
		mTextures[0]->unbind();

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		
	}
}


//----------------------------------------------------------------------------------------------
// Photo
//----------------------------------------------------------------------------------------------

Photo::Photo(GLdouble w, GLdouble h)
	: Abs_Entity()
{
	mTexturePaths = { "../bmps/noche.bmp" };
	mMesh = Mesh::generateRectangleTexCor(w, h, 1, 1);
	mRotation = dvec3(90, 0, 90);
	mPosition = dvec3(mPosition.x, mPosition.y + 1, mPosition.z);
}

Photo::~Photo()
{
	delete mMesh;
	mMesh = nullptr;
};

void
Photo::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat
			* mModelMat
			* translate(dmat4(1), mPosition)
			* rotate(dmat4(1), radians(mRotation.x), dvec3(1, 0, 0))
			* rotate(dmat4(1), radians(mRotation.z), dvec3(0, 0, 1)); // glm matrix multiplication

		upload(aMat);

		glColor4d(1.0, 1.0, 1.0, 1.0);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		mTextures[0]->bind(GL_REPLACE);

		mMesh->render();

		mTextures[0]->unbind();
		glPointSize(1);
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glPolygonMode(GL_FRONT, GL_FILL);
	}
}

void
Photo::update() {
	mTextures[0]->loadColorBuffer(800, 600); // Tamaño de la ventana
}


void 
Photo::save(const std::string filename) const{
	mTextures[0]->save(filename);
}



//----------------------------------------------------------------------------------------------
// Box (Opcional)
//----------------------------------------------------------------------------------------------

Box::Box(GLdouble _length)
	: Abs_Entity()
{
	mTexturePaths = { "../bmps/container.bmp", "../bmps/papelE.bmp" };

	length = _length;
	mMesh = Mesh::generateBoxOutline(_length);
	mMeshTopLid = Mesh::generateRectangleTexCor(length, length, 1, 1);
	mMeshBotLid = Mesh::generateRectangleTexCor(length, length, 1, 1);

	mPosition = dvec3(-140, length/2 + 1, -140);

}

Box::~Box()
{
	delete mMesh;
	mMesh = nullptr;
};

void 
Box::update() {
	lidRotation += 0.0001;
}

void
Box::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		double angle = lidRotation + radians(-90.0);
		double amplitude = 90.0;
		dmat4 aMat = modelViewMat * mModelMat * translate(dmat4(1), mPosition);
		dmat4 aMatTopLid = modelViewMat * mModelMatTopLid
			* translate(dmat4(1), mPosition)
			* translate(dmat4(1), { 0.0, length/2,length / 2 })
			* rotate(dmat4(1), radians(sin(angle) * amplitude), dvec3(1, 0, 0))
			* translate(dmat4(1), { 0.0, length/2, 0.0 })
			;

		dmat4 aMatBotLid = modelViewMat * mModelMatTopLid
			* translate(dmat4(1), mPosition)
			* translate(dmat4(1), { 0.0, - length / 2, 0.0 })
			* rotate(dmat4(1), radians(90.0), dvec3(1, 0, 0))
			;


		glColor4d(1.0, 1.0, 1.0, 1.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_CULL_FACE);

		// Box outline
		upload(aMat);
		
		mTextures[0]->bind(GL_MODULATE);
		glCullFace(GL_BACK);
		mMesh->render();
		mTextures[0]->unbind();

		mTextures[1]->bind(GL_MODULATE);
		glCullFace(GL_FRONT);
		mMesh->render();
		mTextures[1]->unbind();
		//End Box outline

		// Box Top lid
		upload(aMatTopLid);

		mTextures[0]->bind(GL_MODULATE);
		glCullFace(GL_BACK);
		mMeshTopLid->render();
		mTextures[0]->unbind();

		mTextures[1]->bind(GL_MODULATE);
		glCullFace(GL_FRONT);
		mMeshTopLid->render();
		mTextures[1]->unbind();
		//End

		// Box bot lid
		upload(aMatBotLid);

		mTextures[0]->bind(GL_MODULATE);
		glCullFace(GL_BACK);
		mMeshBotLid->render();
		mTextures[0]->unbind();

		mTextures[1]->bind(GL_MODULATE);
		glCullFace(GL_FRONT);
		mMeshBotLid->render();
		mTextures[1]->unbind();
		//End

		glDisable(GL_CULL_FACE);
		glPointSize(1);
		glLineWidth(1);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glPolygonMode(GL_FRONT, GL_FILL);
	}
}

//----------------------------------------------------------------------------------------------
// Grass
//----------------------------------------------------------------------------------------------

Grass::Grass(GLdouble w, GLdouble h)
	: Abs_Entity()
{
	mTexturePaths = { "../bmps/grass.bmp" };
	mMesh = Mesh::generateRectangleTexCor(w, h, 1, 1);
	mPosition = dvec3(170, h / 2, 170);
}

Grass::~Grass()
{
	delete mMesh;
	mMesh = nullptr;
};

void
Grass::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		dvec3 nRotation = dvec3(0, 0, 0);

		for (int i = 0; i < 3; i++) {
			dmat4 aMat = modelViewMat
				* mModelMat
				* translate(dmat4(1), mPosition)
				* rotate(dmat4(1), radians(nRotation.y), dvec3(0, 1, 0));

			upload(aMat);

			glColor4d(1.0, 1.0, 1.0, 1.0);

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDisable(GL_DEPTH_TEST); // Si no, no se transparentan los otros hierbajos renderizados
			glEnable(GL_BLEND);

			mTextures[0]->bind(GL_REPLACE);

			mMesh->render();

			mTextures[0]->unbind();
			glEnable(GL_DEPTH_TEST);
			glDisable(GL_BLEND);

			glPointSize(1);
			glLineWidth(1);
			glColor4d(1.0, 1.0, 1.0, 1.0);
			glPolygonMode(GL_FRONT, GL_FILL);

			nRotation.y += 45;
		}
	}
}