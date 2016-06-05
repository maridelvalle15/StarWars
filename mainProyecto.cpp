#include "Ogre\ExampleApplication.h"
#include "stdafx.h"

Ogre::AnimationState* AnimacionLaser;
Ogre::AnimationState* AnimacionLaser2;
Ogre::AnimationState* AnimacionLaser3;
Ogre::AnimationState* AnimacionLaser4;
float r=1.0;

class FrameListenerClase : public Ogre::FrameListener{
private:
	OIS::InputManager* _man;
	Ogre::Camera* _cam;
	OIS::Keyboard* _key;
	OIS::Mouse* _mouse;

public:
	FrameListenerClase( Ogre::Camera* cam,  RenderWindow* win){
		size_t windowHnd = 0;
		std::stringstream windowHndStr;
		win->getCustomAttribute("WINDOW",&windowHnd);
		windowHndStr << windowHnd;

		OIS::ParamList pl;
		pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str())); 

		_man = OIS::InputManager::createInputSystem(pl);
		_key= static_cast<OIS::Keyboard*>(_man->createInputObject(OIS::OISKeyboard,false));
		_mouse= static_cast<OIS::Mouse*>(_man->createInputObject(OIS::OISMouse,false));
		_cam = cam;
	}

	bool frameStarted(const Ogre::FrameEvent &evt){
		_key->capture();
		_mouse->capture();


		float movSpeed = 10.0f;
		Ogre::Vector3 tmov(0,0,0);
		Ogre::Vector3 tcam(0,0,0);

		if(_key->isKeyDown(OIS::KC_ESCAPE))
			return false;
		
		if(_key->isKeyDown(OIS::KC_W))
			tcam += Ogre::Vector3(0,0,-10);

		if(_key->isKeyDown(OIS::KC_S))
			tcam += Ogre::Vector3(0,0,10);

		if(_key->isKeyDown(OIS::KC_A))
			tcam += Ogre::Vector3(-10,0,0);

		if(_key->isKeyDown(OIS::KC_D))
			tcam += Ogre::Vector3(10,0,0);

		if(_key->isKeyDown(OIS::KC_K))
			tmov += Ogre::Vector3(20,0,0);

		if(_key->isKeyDown(OIS::KC_H))
			tmov += Ogre::Vector3(-20,0,0);

		if(_key->isKeyDown(OIS::KC_U))
			tmov += Ogre::Vector3(0,0,20);

		if(_key->isKeyDown(OIS::KC_J))
			tmov += Ogre::Vector3(0,0,-20);

		float rotX =_mouse->getMouseState().X.rel * evt.timeSinceLastFrame *-1;
		float rotY =_mouse->getMouseState().Y.rel * evt.timeSinceLastFrame *-1;
		_cam->yaw(Ogre::Radian(rotX));
		_cam->pitch(Ogre::Radian(rotY));
		_cam->moveRelative(tcam*movSpeed*evt.timeSinceLastFrame);


		AnimacionLaser->addTime(evt.timeSinceLastFrame);
		AnimacionLaser2->addTime(evt.timeSinceLastFrame);
		AnimacionLaser3->addTime(evt.timeSinceLastFrame);
		AnimacionLaser4->addTime(evt.timeSinceLastFrame);
		return true;
	}

};


ManualObject* createPlane(SceneManager* mSceneMgr, float x00, float x10, float x11, float x01, float y00, float y10, float y11, float y01, float z00, float z10, float z11, float z01, String name, String matN){

	ManualObject* moPlane = mSceneMgr->createManualObject(name);
	moPlane->begin(matN, RenderOperation::OT_TRIANGLE_STRIP);
	 
	// define vertex position of index 0..3

	//2,125-0.5-0.5
	moPlane->position(x00, y00, z00);
	moPlane->normal(x00, y00, z00);
	moPlane->textureCoord(0,0);
	moPlane->position(x10, y10, z10);
	moPlane->normal(x10, y10, z10);
	moPlane->textureCoord(1,0);
	moPlane->position(x11, y11, z11);
	moPlane->normal(x11, y11, z11);
	moPlane->textureCoord(1,1);
	moPlane->position(x01, y01, z01);
	moPlane->normal(x01, y01, z01);
	moPlane->textureCoord(0,1);


	moPlane->index(0);
	moPlane->index(1);
	moPlane->index(2);
	moPlane->index(3);
	moPlane->index(0);


	moPlane->end();		

	return moPlane;

}


ManualObject* createTriangle(SceneManager* mSceneMgr, float x00, float x10, float x11, float y00, float y10, float y11, float z00, float z10, float z11,    String name, String matN){

	ManualObject* moTriag = mSceneMgr->createManualObject(name);
	moTriag->begin(matN, RenderOperation::OT_TRIANGLE_LIST);
	 
	// define vertex position of index 0..3

	//2,125-0.5-0.5
	moTriag->position(x00, y00, z00);
	moTriag->normal(x00, y00, z00);
	moTriag->textureCoord(0,0);
	moTriag->position(x10, y10, z10);
	moTriag->normal(x10, y10, z10);
	moTriag->textureCoord(1,0);
	moTriag->position(x11, y11, z11);
	moTriag->normal(x11, y11, z11);
	moTriag->textureCoord(0.5f,0.5f);
	//moTriag->position(x01, y01, z01);
	//moTriag->normal(x01, y01, z01);
	//moTriag->textureCoord(0,1);


	moTriag->index(0);
	moTriag->index(1);
	moTriag->index(2);
	moTriag->index(3);
	moTriag->index(0);


	moTriag->end();		

	return moTriag;

}


class Example1 : public ExampleApplication
{

public:

	void createCamera() {

		mCamera = mSceneMgr->createCamera("MyCamera1");
		mCamera->setPosition(0,10,50);
		mCamera->lookAt(0,0,-50);
		mCamera->setNearClipDistance(5);

	}

	void createFrameListener(){
		Ogre::FrameListener* FrameListener01 = new FrameListenerClase(mCamera,mWindow);
		mRoot->addFrameListener(FrameListener01);

	}

	void createScene()
	{

		mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));
		mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
		
		// Inicializacion de la escena
		/*Ogre::Entity* ent01 = mSceneMgr->createEntity("MyEntity1","ejes01.mesh");
		Ogre::SceneNode* node01 = mSceneMgr->createSceneNode("Node01");
		mSceneMgr->getRootSceneNode()->addChild(node01);
		node01->attachObject(ent01);*/
		

		Ogre::Entity* entEscena01 = mSceneMgr->createEntity("ogre_base01.mesh");
		mSceneMgr->getRootSceneNode()->attachObject(entEscena01);

		Ogre::Entity* entEscena02 = mSceneMgr->createEntity("ogre_fondo01.mesh");
		mSceneMgr->getRootSceneNode()->attachObject(entEscena02);

		Ogre::Entity* entEscena03 = mSceneMgr->createEntity("ogre_pared01.mesh");
		mSceneMgr->getRootSceneNode()->attachObject(entEscena03);

		Ogre::Entity* entEscena04 = mSceneMgr->createEntity("ogre_pared02.mesh");
		mSceneMgr->getRootSceneNode()->attachObject(entEscena04);

		Ogre::Entity* entEscena05 = mSceneMgr->createEntity("ogre_pared03.mesh");
		mSceneMgr->getRootSceneNode()->attachObject(entEscena05);

		Ogre::Entity* entEscena06 = mSceneMgr->createEntity("ogre_torretas01.mesh");
		mSceneMgr->getRootSceneNode()->attachObject(entEscena06);

		// Creamos la textura de la torreta
		Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().create(
			"CilindroText", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

		Ogre::TextureUnitState* torretaTexture =
			mat ->getTechnique(0) ->getPass(0)->createTextureUnitState("tex_mTorretas01.png");
		// Creamos la textura del laser 
		Ogre::MaterialPtr matLaser = Ogre::MaterialManager::getSingleton().create(
			"LaserText", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

		Ogre::TextureUnitState* laserTexture =
			matLaser ->getTechnique(0) ->getPass(0)->createTextureUnitState("nm_rt.png");
		
		// TORRETA 1

		// Creamos la cabeza de la torreta junto con su eje y le agregamos textura
		//Ogre::Entity* entEjeCabezaTorreta = mSceneMgr ->createEntity("ejes01.mesh");
		Ogre::Entity* entEscena07 = mSceneMgr->createEntity("usb_cubomod01.mesh");
		entEscena07->setMaterial(mat);
		Ogre::SceneNode* nodeTopeTorreta = mSceneMgr ->createSceneNode("nodeTopeTorreta");
		// Posicionamos la cabeza de la torreta
		mSceneMgr->getRootSceneNode()->addChild(nodeTopeTorreta);
		nodeTopeTorreta->attachObject(entEscena07);
		//nodeTopeTorreta->attachObject(entEjeCabezaTorreta);
		nodeTopeTorreta->rotate(Ogre::Quaternion(Ogre::Degree(315), Ogre::Vector3(0,1,0)) , Ogre::Node::TransformSpace::TS_WORLD);
		nodeTopeTorreta->setPosition(-21.7,4.7,-227.4);
		
		// Ca�on de la torreta
		Ogre::Entity* entEscena11 = mSceneMgr->createEntity("usb_cilindro02.mesh");
		entEscena11->setMaterial(mat);
		Ogre::SceneNode* nodeTuboTorreta = mSceneMgr ->createSceneNode("nodeTuboTorreta");
		nodeTopeTorreta->addChild(nodeTuboTorreta);
		nodeTuboTorreta->attachObject(entEscena11);
		nodeTuboTorreta->setScale(0.5,1.0,0.5);
		nodeTuboTorreta->rotate(Ogre::Quaternion(Ogre::Degree(-90), Ogre::Vector3(0,0,1)) , Ogre::Node::TransformSpace::TS_WORLD);
		nodeTuboTorreta->rotate(Ogre::Quaternion(Ogre::Degree(315), Ogre::Vector3(0,1,0)) , Ogre::Node::TransformSpace::TS_WORLD);
		nodeTuboTorreta->translate(6,1,0);

		// Cuerpo de la torreta
		Ogre::Entity* entEscena08 = mSceneMgr->createEntity("usb_cilindro.mesh");
		entEscena08->setMaterial(mat);
		Ogre::SceneNode* nodeCuerpoTorreta = mSceneMgr ->createSceneNode("nodeCuerpoTorreta");
		nodeTopeTorreta->addChild(nodeCuerpoTorreta);
		nodeCuerpoTorreta->attachObject(entEscena08);
		nodeCuerpoTorreta->translate(0.0,-8.0,0.0);
		
		// Espiral que rodea cuerpo de la torreta
		Ogre::Entity* entEscena09 = mSceneMgr->createEntity("usb_helix.mesh");
		entEscena09->setMaterial(mat);
		Ogre::SceneNode* nodeEspiralTorreta = mSceneMgr ->createSceneNode("nodeEspiralTorreta");
		nodeCuerpoTorreta->addChild(nodeEspiralTorreta);
		nodeEspiralTorreta->attachObject(entEscena09);
		
		// Base de la torreta
		Ogre::Entity* entEscena10 = mSceneMgr->createEntity("usb_pipe.mesh");
		entEscena10->setMaterial(mat);
		Ogre::SceneNode* nodeBaseTorreta = mSceneMgr ->createSceneNode("nodeBaseTorreta");
		nodeEspiralTorreta->addChild(nodeBaseTorreta);
		nodeBaseTorreta->attachObject(entEscena10);
		nodeBaseTorreta->setScale(0.88,1.0,1.0);
		nodeBaseTorreta->translate(0,-6,0);
		
		// Laser
		Ogre::Entity* entEscena12 = mSceneMgr->createEntity("usb_laser.mesh");
		entEscena12->setMaterial(matLaser);
		Ogre::SceneNode* nodeLaser = mSceneMgr ->createSceneNode("nodeLaser");
		nodeTuboTorreta->addChild(nodeLaser);
		nodeLaser->attachObject(entEscena12);
		entEscena12->setCastShadows(false);
		nodeLaser->setScale(0.7,0.2,0.4);
		//nodeLaser->rotate(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3(0,0,0)) , Ogre::Node::TransformSpace::TS_WORLD);
		nodeLaser->setPosition(0,10,0);

		// TORRETA 2

		// Creamos la cabeza de la torreta junto con su eje y le agregamos textura
		//Ogre::Entity* entEjeCabezaTorreta = mSceneMgr ->createEntity("ejes01.mesh");
		Ogre::Entity* CabezaT2 = mSceneMgr->createEntity("usb_cubomod01.mesh");
		CabezaT2->setMaterial(mat);
		Ogre::SceneNode* nodeTopeTorreta2 = mSceneMgr ->createSceneNode("nodeTopeTorreta2");
		// Posicionamos la cabeza de la torreta
		mSceneMgr->getRootSceneNode()->addChild(nodeTopeTorreta2);
		nodeTopeTorreta2->attachObject(CabezaT2);
		//nodeTopeTorreta->attachObject(entEjeCabezaTorreta);
		nodeTopeTorreta2->rotate(Ogre::Quaternion(Ogre::Degree(45), Ogre::Vector3(0,1,0)) , Ogre::Node::TransformSpace::TS_WORLD);
		nodeTopeTorreta2->setPosition(21.7,4.7,-408.0);
		
		// Ca�on de la torreta
		Ogre::Entity* CanonT2 = mSceneMgr->createEntity("usb_cilindro02.mesh");
		CanonT2->setMaterial(mat);
		Ogre::SceneNode* nodeTuboTorreta2 = mSceneMgr ->createSceneNode("nodeTuboTorreta2");
		nodeTopeTorreta2->addChild(nodeTuboTorreta2);
		nodeTuboTorreta2->attachObject(CanonT2);
		nodeTuboTorreta2->setScale(0.5,1.0,0.5);
		nodeTuboTorreta2->rotate(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3(0,0,1)) , Ogre::Node::TransformSpace::TS_WORLD);
		nodeTuboTorreta2->rotate(Ogre::Quaternion(Ogre::Degree(45), Ogre::Vector3(0,1,0)) , Ogre::Node::TransformSpace::TS_WORLD);
		nodeTuboTorreta2->translate(-6,1,0);

		// Cuerpo de la torreta
		Ogre::Entity* CuerpoT2 = mSceneMgr->createEntity("usb_cilindro.mesh");
		CuerpoT2->setMaterial(mat);
		Ogre::SceneNode* nodeCuerpoTorreta2 = mSceneMgr ->createSceneNode("nodeCuerpoTorreta2");
		nodeTopeTorreta2->addChild(nodeCuerpoTorreta2);
		nodeCuerpoTorreta2->attachObject(CuerpoT2);
		nodeCuerpoTorreta2->translate(0.0,-8.0,0.0);
		
		// Espiral que rodea cuerpo de la torreta
		Ogre::Entity* EspiralT2 = mSceneMgr->createEntity("usb_helix.mesh");
		EspiralT2->setMaterial(mat);
		Ogre::SceneNode* nodeEspiralTorreta2 = mSceneMgr ->createSceneNode("nodeEspiralTorreta2");
		nodeCuerpoTorreta2->addChild(nodeEspiralTorreta2);
		nodeEspiralTorreta2->attachObject(EspiralT2);
		
		// Base de la torreta
		Ogre::Entity* BaseT2 = mSceneMgr->createEntity("usb_pipe.mesh");
		BaseT2->setMaterial(mat);
		Ogre::SceneNode* nodeBaseTorreta2 = mSceneMgr ->createSceneNode("nodeBaseTorreta2");
		nodeEspiralTorreta2->addChild(nodeBaseTorreta2);
		nodeBaseTorreta2->attachObject(BaseT2);
		nodeBaseTorreta2->setScale(0.88,1.0,1.0);
		nodeBaseTorreta2->translate(0,-6,0);
		
		// Laser
		Ogre::Entity* LaserT2 = mSceneMgr->createEntity("usb_laser.mesh");
		LaserT2->setMaterial(matLaser);
		Ogre::SceneNode* nodeLaser2 = mSceneMgr ->createSceneNode("nodeLaser2");
		nodeTuboTorreta2->addChild(nodeLaser2);
		nodeLaser2->attachObject(LaserT2);
		nodeLaser2->setScale(0.7,0.2,0.4);
		nodeLaser2->rotate(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3(0,0,1)) , Ogre::Node::TransformSpace::TS_WORLD);
		nodeLaser2->setPosition(0.7,0.2,0.4);

		// TORRETA 3

		// Creamos la cabeza de la torreta junto con su eje y le agregamos textura
		//Ogre::Entity* entEjeCabezaTorreta = mSceneMgr ->createEntity("ejes01.mesh");
		Ogre::Entity* CabezaT3 = mSceneMgr->createEntity("usb_cubomod01.mesh");
		CabezaT3->setMaterial(mat);
		Ogre::SceneNode* nodeTopeTorreta3 = mSceneMgr ->createSceneNode("nodeTopeTorreta3");
		// Posicionamos la cabeza de la torreta
		mSceneMgr->getRootSceneNode()->addChild(nodeTopeTorreta3);
		nodeTopeTorreta3->attachObject(CabezaT3);
		//nodeTopeTorreta->attachObject(entEjeCabezaTorreta);
		nodeTopeTorreta3->setPosition(-22.7,4.7,-637.4);
		
		// Ca�on de la torreta
		Ogre::Entity* CanonT3 = mSceneMgr->createEntity("usb_cilindro02.mesh");
		CanonT3->setMaterial(mat);
		Ogre::SceneNode* nodeTuboTorreta3 = mSceneMgr ->createSceneNode("nodeTuboTorreta3");
		nodeTopeTorreta3->addChild(nodeTuboTorreta3);
		nodeTuboTorreta3->attachObject(CanonT3);
		nodeTuboTorreta3->setScale(0.5,1.0,0.5);
		nodeTuboTorreta3->rotate(Ogre::Quaternion(Ogre::Degree(-90), Ogre::Vector3(0,0,1)) , Ogre::Node::TransformSpace::TS_WORLD);
		nodeTuboTorreta3->translate(6,1,0);

		// Cuerpo de la torreta
		Ogre::Entity* CuerpoT3 = mSceneMgr->createEntity("usb_cilindro.mesh");
		CuerpoT3->setMaterial(mat);
		Ogre::SceneNode* nodeCuerpoTorreta3 = mSceneMgr ->createSceneNode("nodeCuerpoTorreta3");
		nodeTopeTorreta3->addChild(nodeCuerpoTorreta3);
		nodeCuerpoTorreta3->attachObject(CuerpoT3);
		nodeCuerpoTorreta3->translate(0.0,-8.0,0.0);
		
		// Espiral que rodea cuerpo de la torreta
		Ogre::Entity* EspiralT3 = mSceneMgr->createEntity("usb_helix.mesh");
		EspiralT3->setMaterial(mat);
		Ogre::SceneNode* nodeEspiralTorreta3 = mSceneMgr ->createSceneNode("nodeEspiralTorreta3");
		nodeCuerpoTorreta3->addChild(nodeEspiralTorreta3);
		nodeEspiralTorreta3->attachObject(EspiralT3);
		
		// Base de la torreta
		Ogre::Entity* BaseT3 = mSceneMgr->createEntity("usb_pipe.mesh");
		BaseT3->setMaterial(mat);
		Ogre::SceneNode* nodeBaseTorreta3 = mSceneMgr ->createSceneNode("nodeBaseTorreta3");
		nodeEspiralTorreta3->addChild(nodeBaseTorreta3);
		nodeBaseTorreta3->attachObject(BaseT3);
		nodeBaseTorreta3->setScale(0.88,1.0,1.0);
		nodeBaseTorreta3->translate(0,-6,0);
		
		// Laser
		Ogre::Entity* LaserT3 = mSceneMgr->createEntity("usb_laser.mesh");
		LaserT3->setMaterial(matLaser);
		Ogre::SceneNode* nodeLaser3 = mSceneMgr ->createSceneNode("nodeLaser3");
		nodeTuboTorreta3->addChild(nodeLaser3);
		nodeLaser3->attachObject(LaserT3);
		nodeLaser3->setScale(0.7,0.2,0.4);
		nodeLaser3->rotate(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3(0,0,1)) , Ogre::Node::TransformSpace::TS_WORLD);
		nodeLaser3->translate(0,10,0);
		
		// TORRETA 4

		// Creamos la cabeza de la torreta junto con su eje y le agregamos textura
		//Ogre::Entity* entEjeCabezaTorreta = mSceneMgr ->createEntity("ejes01.mesh");
		Ogre::Entity* CabezaT4 = mSceneMgr->createEntity("usb_cubomod01.mesh");
		CabezaT4->setMaterial(mat);
		Ogre::SceneNode* nodeTopeTorreta4 = mSceneMgr ->createSceneNode("nodeTopeTorreta4");
		// Posicionamos la cabeza de la torreta
		mSceneMgr->getRootSceneNode()->addChild(nodeTopeTorreta4);
		nodeTopeTorreta4->attachObject(CabezaT4);
		//nodeTopeTorreta->attachObject(entEjeCabezaTorreta);
		nodeTopeTorreta4->setPosition(21.7,4.7,-882.8);
		
		// Ca�on de la torreta
		Ogre::Entity* CanonT4 = mSceneMgr->createEntity("usb_cilindro02.mesh");
		CanonT4->setMaterial(mat);
		Ogre::SceneNode* nodeTuboTorreta4 = mSceneMgr ->createSceneNode("nodeTuboTorreta4");
		nodeTopeTorreta4->addChild(nodeTuboTorreta4);
		nodeTuboTorreta4->attachObject(CanonT4);
		nodeTuboTorreta4->setScale(0.5,1.0,0.5);
		nodeTuboTorreta4->rotate(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3(0,0,1)) , Ogre::Node::TransformSpace::TS_WORLD);
		nodeTuboTorreta4->translate(-6,1,0);

		// Cuerpo de la torreta
		Ogre::Entity* CuerpoT4 = mSceneMgr->createEntity("usb_cilindro.mesh");
		CuerpoT4->setMaterial(mat);
		Ogre::SceneNode* nodeCuerpoTorreta4 = mSceneMgr ->createSceneNode("nodeCuerpoTorreta4");
		nodeTopeTorreta4->addChild(nodeCuerpoTorreta4);
		nodeCuerpoTorreta4->attachObject(CuerpoT4);
		nodeCuerpoTorreta4->translate(0.0,-8.0,0.0);
		
		// Espiral que rodea cuerpo de la torreta
		Ogre::Entity* EspiralT4 = mSceneMgr->createEntity("usb_helix.mesh");
		EspiralT4->setMaterial(mat);
		Ogre::SceneNode* nodeEspiralTorreta4 = mSceneMgr ->createSceneNode("nodeEspiralTorreta4");
		nodeCuerpoTorreta4->addChild(nodeEspiralTorreta4);
		nodeEspiralTorreta4->attachObject(EspiralT4);
		
		// Base de la torreta
		Ogre::Entity* BaseT4 = mSceneMgr->createEntity("usb_pipe.mesh");
		BaseT4->setMaterial(mat);
		Ogre::SceneNode* nodeBaseTorreta4 = mSceneMgr ->createSceneNode("nodeBaseTorreta4");
		nodeEspiralTorreta4->addChild(nodeBaseTorreta4);
		nodeBaseTorreta4->attachObject(BaseT4);
		nodeBaseTorreta4->setScale(0.88,1.0,1.0);
		nodeBaseTorreta4->translate(0,-6,0);
		
		// Laser
		Ogre::Entity* LaserT4 = mSceneMgr->createEntity("usb_laser.mesh");
		LaserT4->setMaterial(matLaser);
		Ogre::SceneNode* nodeLaser4 = mSceneMgr ->createSceneNode("nodeLaser4");
		nodeTuboTorreta4->addChild(nodeLaser4);
		nodeLaser4->attachObject(LaserT4);
		nodeLaser4->setScale(0.7,0.2,0.4);
		nodeLaser4->rotate(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3(0,0,1)) , Ogre::Node::TransformSpace::TS_WORLD);
		nodeLaser4->translate(0,10,0);

		
		//Animacion del laser 1
		float duration = 4.0;
		Ogre::Animation* animationLaser = mSceneMgr->createAnimation("AnimLaser",duration);
		animationLaser->setInterpolationMode(Animation::IM_SPLINE);

		Ogre::NodeAnimationTrack* LaserTrack = animationLaser->createNodeTrack(0,nodeLaser);
		Ogre::TransformKeyFrame* key;

		key = LaserTrack->createNodeKeyFrame(0.0);
		key->setTranslate(Vector3(0,6.3f,0));
		key->setScale(Vector3(2.0f,0.05f,2.0f));

		key = LaserTrack->createNodeKeyFrame(0.9f);
		key->setTranslate(Vector3(0,65,0));
		key->setScale(Vector3(0.9f,0.2f,0.9f));
		//key->setScale(Vector3(0.03,0.03,0.03));
		//nodeLaser->rotate(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3(0,0,0)) , Ogre::Node::TransformSpace::TS_WORLD);

		key = LaserTrack->createNodeKeyFrame(1.3f);
		//key->setTranslate(Vector3(0,48.5f,0));
		key->setTranslate(Vector3(0,75,0));
		key->setScale(Vector3(0.9f,0.2f,0.9f));
		//key->setScale(Vector3(0.03,0.03,0.03));

		key = LaserTrack->createNodeKeyFrame(2.0f);
		//key->setTranslate(Vector3(0,50.5,0));
		key->setTranslate(Vector3(0,77,0));
		key->setScale(Vector3(8.0f,-0.3,8.0f));
		//key->setScale(Vector3(0.03,0.03,0.03));

		key = LaserTrack->createNodeKeyFrame(2.7f);
		//key->setTranslate(Vector3(0,55.5,0));
		key->setTranslate(Vector3(0,82,0));
		key->setScale(Vector3(0,0,0));
		//key->setScale(Vector3(0.03,0.03,0.03));

		AnimacionLaser=mSceneMgr->createAnimationState("AnimLaser");
		AnimacionLaser->setEnabled(true);
		AnimacionLaser->setLoop(true);


		//Animacion del laser 2
		float duration2 = 4.0;
		Ogre::Animation* animationLaser2 = mSceneMgr->createAnimation("AnimLaser2",duration2);
		animationLaser2->setInterpolationMode(Animation::IM_SPLINE);

		Ogre::NodeAnimationTrack* LaserTrack2 = animationLaser2->createNodeTrack(0,nodeLaser2);
		Ogre::TransformKeyFrame* key2;

		key2 = LaserTrack2->createNodeKeyFrame(0.0);
		key2->setTranslate(Vector3(0,6.3f,0));
		key2->setScale(Vector3(2.0f,0.05f,2.0f));

		key2 = LaserTrack2->createNodeKeyFrame(0.9f);
		key2->setTranslate(Vector3(0,65,0));
		key2->setScale(Vector3(0.9f,0.2f,0.9f));
		//key->setScale(Vector3(0.03,0.03,0.03));
		//nodeLaser->rotate(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3(0,0,0)) , Ogre::Node::TransformSpace::TS_WORLD);

		key2 = LaserTrack2->createNodeKeyFrame(1.3f);
		//key->setTranslate(Vector3(0,48.5f,0));
		key2->setTranslate(Vector3(0,75,0));
		key2->setScale(Vector3(0.9f,0.2f,0.9f));
		//key->setScale(Vector3(0.03,0.03,0.03));

		key2 = LaserTrack2->createNodeKeyFrame(2.0f);
		//key->setTranslate(Vector3(0,50.5,0));
		key2->setTranslate(Vector3(0,77,0));
		key2->setScale(Vector3(8.0f,-0.3,8.0f));
		//key->setScale(Vector3(0.03,0.03,0.03));

		key2 = LaserTrack2->createNodeKeyFrame(2.7f);
		//key->setTranslate(Vector3(0,55.5,0));
		key2->setTranslate(Vector3(0,82,0));
		key2->setScale(Vector3(0,0,0));
		//key->setScale(Vector3(0.03,0.03,0.03));

		AnimacionLaser2=mSceneMgr->createAnimationState("AnimLaser2");
		AnimacionLaser2->setEnabled(true);
		AnimacionLaser2->setLoop(true);
		
		//Animacion del laser 3
		float duration3 = 4.0;
		Ogre::Animation* animationLaser3 = mSceneMgr->createAnimation("AnimLaser3",duration3);
		animationLaser3->setInterpolationMode(Animation::IM_SPLINE);

		Ogre::NodeAnimationTrack* LaserTrack3 = animationLaser3->createNodeTrack(0,nodeLaser3);
		Ogre::TransformKeyFrame* key3;

		key3 = LaserTrack3->createNodeKeyFrame(0.0);
		key3->setTranslate(Vector3(0,6.3f,0));
		key3->setScale(Vector3(2.0f,0.05f,2.0f));

		key3 = LaserTrack3->createNodeKeyFrame(0.4f);
		key3->setTranslate(Vector3(0,15,0));
		key3->setScale(Vector3(0.9f,0.2f,0.9f));
		//key->setScale(Vector3(0.03,0.03,0.03));
		//nodeLaser->rotate(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3(0,0,0)) , Ogre::Node::TransformSpace::TS_WORLD);

		key3 = LaserTrack3->createNodeKeyFrame(1.0);
		key3->setTranslate(Vector3(0,48.5f,0));
		key3->setScale(Vector3(0.9f,0.2f,0.9f));
		//key->setScale(Vector3(0.03,0.03,0.03));

		key3 = LaserTrack3->createNodeKeyFrame(1.4f);
		key3->setTranslate(Vector3(0,50.5,0));
		key3->setScale(Vector3(8.0f,-0.3,8.0f));
		//key->setScale(Vector3(0.03,0.03,0.03));

		key3 = LaserTrack3->createNodeKeyFrame(2.4f);
		key3->setTranslate(Vector3(0,55.5,0));
		key3->setScale(Vector3(0,0,0));
		//key->setScale(Vector3(0.03,0.03,0.03));

		AnimacionLaser3=mSceneMgr->createAnimationState("AnimLaser3");
		AnimacionLaser3->setEnabled(true);
		AnimacionLaser3->setLoop(true);

		//Animacion del laser 4
		float duration4 = 4.0;
		Ogre::Animation* animationLaser4 = mSceneMgr->createAnimation("AnimLaser4",duration4);
		animationLaser4->setInterpolationMode(Animation::IM_SPLINE);

		Ogre::NodeAnimationTrack* LaserTrack4 = animationLaser4->createNodeTrack(0,nodeLaser4);
		Ogre::TransformKeyFrame* key4;

		key4 = LaserTrack4->createNodeKeyFrame(0.0);
		key4->setTranslate(Vector3(0,6.3f,0));
		key4->setScale(Vector3(2.0f,0.05f,2.0f));

		key4 = LaserTrack4->createNodeKeyFrame(0.4f);
		key4->setTranslate(Vector3(0,15,0));
		key4->setScale(Vector3(0.9f,0.2f,0.9f));
		//key->setScale(Vector3(0.03,0.03,0.03));
		//nodeLaser->rotate(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3(0,0,0)) , Ogre::Node::TransformSpace::TS_WORLD);

		key4 = LaserTrack4->createNodeKeyFrame(1.0);
		key4->setTranslate(Vector3(0,48.5f,0));
		key4->setScale(Vector3(0.9f,0.2f,0.9f));
		//key->setScale(Vector3(0.03,0.03,0.03));

		key4 = LaserTrack4->createNodeKeyFrame(1.4f);
		key4->setTranslate(Vector3(0,50.5,0));
		key4->setScale(Vector3(8.0f,-0.3,8.0f));
		//key->setScale(Vector3(0.03,0.03,0.03));

		key4 = LaserTrack4->createNodeKeyFrame(2.4f);
		key4->setTranslate(Vector3(0,55.5,0));
		key4->setScale(Vector3(0,0,0));
		//key->setScale(Vector3(0.03,0.03,0.03));

		AnimacionLaser4=mSceneMgr->createAnimationState("AnimLaser4");
		AnimacionLaser4->setEnabled(true);
		AnimacionLaser4->setLoop(true);

		//mSceneMgr->setSkyBox(true, "matSkyBox", 300);









		// Para la nave
		// Creamos la textura del laser 
		Ogre::MaterialPtr matShip = Ogre::MaterialManager::getSingleton().create(
			"shipText", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

		Ogre::TextureUnitState* shipTexture =
			matShip ->getTechnique(0) ->getPass(0)->createTextureUnitState("usb_ship_mat.png");
			//matShip ->getTechnique(0) ->setCullingMode( CULL_NONE );



/*ManualObject* cabina01 = mSceneMgr->createManualObject("cabina01");
cabina01->begin("shipText", RenderOperation::OT_LINE_STRIP);
 
// define vertex position of index 0..3

//2,125-0.5-0.5
//sizq
cabina01->position(-1.35f, 10, 0.5f);
cabina01->normal(-1.35f, 10, 0.5f);
cabina01->textureCoord(0,1);
cabina01->position(-2.125f, 3, 1.5f);
cabina01->normal(-2.125f, 3, 1.5f);
cabina01->textureCoord(0,1);
cabina01->position(-2.125f, -3, 1.5f);
cabina01->normal(-2.125f, -3, 1.5f);
cabina01->textureCoord(0,0);



cabina01->position(-1.625f, -3, 3);
cabina01->normal(-1.625f, -3, 3);
cabina01->textureCoord(0,0);
cabina01->position( 1.625f, -3, 3);
cabina01->normal( 1.625f, -3, 3);
cabina01->textureCoord(1,0);
cabina01->position( 1.625f,  3, 3);
cabina01->normal( 1.625f,  3, 3);
cabina01->textureCoord(1,1);
cabina01->position(-1.625f,  3, 3);
cabina01->normal(-1.625f,  3, 3);
cabina01->textureCoord(0,1);


//pico
cabina01->position( 1.125f,  10, 2);
cabina01->normal( 1.125f,  10, 2);
cabina01->textureCoord(0,1);
cabina01->position( -1.125f,  10, 2);
cabina01->normal( -1.125f,  10, 2);
cabina01->textureCoord(1,1);


//sder
cabina01->position(1.35f, 10, 0.5f);
cabina01->normal(1.35f, 10, 0.5f);
cabina01->textureCoord(0,1);
cabina01->position(2.125f, 3, 1.5f);
cabina01->normal(2.125f, 3, 1.5f);
cabina01->textureCoord(0,1);
cabina01->position(2.125f, -3, 1.5f);
cabina01->normal(2.125f, -3, 1.5f);
cabina01->textureCoord(0,1);



 
// define usage of vertices by refering to the indexes
cabina01->index(9);
cabina01->index(7);
cabina01->index(0);
cabina01->index(8);
cabina01->index(6);
cabina01->index(1);
cabina01->index(2);
cabina01->index(3);
cabina01->index(6);
cabina01->index(4);
cabina01->index(5);
cabina01->index(6);
cabina01->index(8);
cabina01->index(5);
cabina01->index(7);
cabina01->index(9);
cabina01->index(10);
cabina01->index(5);
cabina01->index(11);
cabina01->index(4);
cabina01->index(2);
cabina01->index(3);


 

cabina01->end();		

		SceneNode* nodeCabina = mSceneMgr->createSceneNode("shipCabina");
		mSceneMgr->getRootSceneNode()->addChild(nodeCabina);
		nodeCabina->attachObject(cabina01); */



		//nodecabina01->setScale(0.02, 0.02, 0.02);

		//Tapa arriba cabina
	ManualObject* cabina010 = createTriangle(mSceneMgr,0.875f, 1.625f, 0.875f, 10, 10, 11, 1.5f, 0.5f, 0.5f, "cabina010MO", "shipText");
		ManualObject* cabina09 = createPlane(mSceneMgr,1.375f, 2.125f, 1.625f, 0.875f, 2.5, 2.5, 10, 10, 3, 0.5f, 0.5f, 1.5f, "cabina09MO", "shipText");
		ManualObject* cabina08 = createPlane(mSceneMgr,1.375f, 2.125f, 2.125f, 1.375f, -2.5, -2.5, 2.5, 2.5, 3, 0.5f, 0.5f, 3, "cabina08MO", "shipText");
		ManualObject* cabina07 = createPlane(mSceneMgr,-2.125f, 2.125f, 1.375f, -1.375f, -2.5, -2.5, -2.5, -2.5, 0.5f, 0.5f, 3, 3, "cabina07MO", "shipText");
		ManualObject* cabina06 = createPlane(mSceneMgr,-2.125f, -1.375f, -1.375f, -2.125f, -2.5, -2.5, 2.5, 2.5, 0.5f, 3, 3, 0.5f, "cabina06MO", "shipText");
		ManualObject* cabina05 = createPlane(mSceneMgr,-2.125f, -1.375f, -0.875f, -1.625f, 2.5, 2.5, 10, 10, 0.5f, 3, 1.5f, 0.5f, "cabina04MO", "shipText");
		ManualObject* cabina04 = createTriangle(mSceneMgr,-1.625f, -0.875f, -0.875f, 10, 10, 11, 0.5f, 1.5f, 0.5f, "cabina05MO", "shipText");
		ManualObject* cabina03 = createPlane(mSceneMgr,-0.875f, 0.875f, 0.875f, -0.875f, 10, 10, 11, 11, 1.5f, 1.5f, 0.5f, 0.5f, "cabina03MO", "shipText");
		ManualObject* cabina02 = createPlane(mSceneMgr,-1.375f, 1.375f, 0.875f, -0.875f, 2.5, 2.5, 10, 10, 3, 3, 1.5f, 1.5f, "cabina02MO", "shipText");
		ManualObject* cabina01 = createPlane(mSceneMgr,-1.375f, 1.375f, 1.375f, -1.375f, -2.5, -2.5, 2.5, 2.5, 3, 3, 3, 3, "cabina01MO", "shipText");
		SceneNode* nodeCabina01 = mSceneMgr->createSceneNode("nodeC01");
		mSceneMgr->getRootSceneNode()->addChild(nodeCabina01);
		nodeCabina01->attachObject(cabina01); 
		nodeCabina01->attachObject(cabina02); 
		nodeCabina01->attachObject(cabina03); 
		nodeCabina01->attachObject(cabina04); 
		nodeCabina01->attachObject(cabina05); 
		nodeCabina01->attachObject(cabina06); 
		nodeCabina01->attachObject(cabina07); 
		nodeCabina01->attachObject(cabina08); 
		nodeCabina01->attachObject(cabina09); 
		nodeCabina01->attachObject(cabina010); 

	    //TapaAbajo Cabina
	ManualObject* cabina110 = createTriangle(mSceneMgr,0.875f, 1.625f, 0.875f, 10, 10, 11, 1.5f, 0.5f, 0.5f, "cabina110MO", "shipText");
		ManualObject* cabina19 = createPlane(mSceneMgr,1.375f, 2.125f, 1.625f, 0.875f, 2.5, 2.5, 10, 10, 5, 0.5f, 0.5f, 1.5f, "cabina19MO", "shipText");
		ManualObject* cabina18 = createPlane(mSceneMgr,1.375f, 2.125f, 2.125f, 1.375f, -2.5, -2.5, 2.5, 2.5, 5, 0.5f, 0.5f, 5, "cabina18MO", "shipText");
		ManualObject* cabina17 = createPlane(mSceneMgr,-2.125f, 2.125f, 1.375f, -1.375f, -2.5, -2.5, -2.5, -2.5, 0.5f, 0.5f, 5, 5, "cabina17MO", "shipText");
		ManualObject* cabina16 = createPlane(mSceneMgr,-2.125f, -1.375f, -1.375f, -2.125f, -2.5, -2.5, 2.5, 2.5, 0.5f, 5, 5, 0.5f, "cabina16MO", "shipText");
		ManualObject* cabina15 = createPlane(mSceneMgr,-2.125f, -1.375f, -0.875f, -1.625f, 2.5, 2.5, 10, 10, 0.5f, 5, 1.5f, 0.5f, "cabina14MO", "shipText");
		ManualObject* cabina14 = createTriangle(mSceneMgr,-1.625f, -0.875f, -0.875f, 10, 10, 11, 0.5f, 1.5f, 0.5f, "cabina15MO", "shipText");
		ManualObject* cabina13 = createPlane(mSceneMgr,-0.875f, 0.875f, 0.875f, -0.875f, 10, 10, 11, 11, 1.5f, 1.5f, 0.5f, 0.5f, "cabina13MO", "shipText");
		ManualObject* cabina12 = createPlane(mSceneMgr,-1.375f, 1.375f, 0.875f, -0.875f, 2.5, 2.5, 10, 10, 5, 5, 1.5f, 1.5f, "cabina12MO", "shipText");
		ManualObject* cabina11 = createPlane(mSceneMgr,-1.375f, 1.375f, 1.375f, -1.375f, -2.5, -2.5, 2.5, 2.5, 5, 5, 5, 5, "cabina11MO", "shipText");
		SceneNode* nodeCabina11 = nodeCabina01->createChildSceneNode();
		nodeCabina11->attachObject(cabina11); 
		nodeCabina11->attachObject(cabina12); 
		nodeCabina11->attachObject(cabina13); 
		nodeCabina11->attachObject(cabina14); 
		nodeCabina11->attachObject(cabina15); 
		nodeCabina11->attachObject(cabina16); 
		nodeCabina11->attachObject(cabina17); 
		nodeCabina11->attachObject(cabina18); 
		nodeCabina11->attachObject(cabina19); 
		nodeCabina11->attachObject(cabina110); 
		nodeCabina11->setScale(1,1,-1);
		nodeCabina11->setPosition(0,0,1);
		//ManualObject* cabina02 = createPlane(mSceneMgr,-2.125f, -1.35f, -	1.35f, -2.125f, 3, 3, 10, 10, 0.5f, 1.5f, 1.5f, 0.5f, "cabina02MO", "shipText");


		/* Ala derecha */
		//-6.375f
		//5.578125f
		//2.921875f
		//-2.72265625f
		ManualObject* ala03 = createPlane(mSceneMgr,-2.72265625f, -1.8f, -1.8f, -2.72265625f, -1.8, -1.8, 1.5f, 1.5f, 1, 1, 1, 1, "ala03", "shipText");						
		ManualObject* ala02 = createPlane(mSceneMgr,-2.921875f, -2.72265625f, -2.72265625f, -2.921875f, -2, -1.8, 1.5f, 1.5f, 1, 1, 1, 1, "ala02", "shipText"); 						
		ManualObject* ala01 = createPlane(mSceneMgr,-8.5, -2.921875f, -2.921875f, -8.5, -1.5f, -2, 1.5f, 1.5f, 1, 1, 1, 1, "ala01", "shipText");

		SceneNode* nodeAla01 = mSceneMgr->createSceneNode("nodeA01");
		mSceneMgr->getRootSceneNode()->addChild(nodeAla01);
		nodeAla01->attachObject(ala01); 
		nodeAla01->attachObject(ala02); 
		nodeAla01->attachObject(ala03); 


		nodeCabina01->setPosition(0,0,0);


		ManualObject* ala023 = createPlane(mSceneMgr,-2.72265625f, -1.8f, -1.8f, -2.72265625f, -1.8, -1.8, 1.5f, 1.5f, 1, 1, 1, 1, "ala023", "shipText");						
		ManualObject* ala022 = createPlane(mSceneMgr,-2.921875f, -2.72265625f, -2.72265625f, -2.921875f, -2, -1.8, 1.5f, 1.5f, 1, 1, 1, 1, "ala022", "shipText"); 						
		ManualObject* ala021 = createPlane(mSceneMgr,-8.5, -2.921875f, -2.921875f, -8.5, -1.5f, -2, 1.5f, 1.5f, 1, 1, 1, 1, "ala021", "shipText");

		SceneNode* nodeAla02 = nodeAla01->createChildSceneNode("nodeA02");
		nodeAla02->attachObject(ala021); 
		nodeAla02->attachObject(ala022); 
		nodeAla02->attachObject(ala023); 
		nodeAla02->setScale(1,1,-1);
		nodeAla02->setPosition(1,1,0.5f);
		/*Ogre::Entity* test = mSceneMgr->createEntity("usb_planocurvo02.mesh");
		test->setMaterial(matShip);
		Ogre::SceneNode* nodeTest = mSceneMgr ->createSceneNode("nodeT");
		mSceneMgr->getRootSceneNode()->addChild(nodeTest);
		nodeTest->attachObject(test);
		nodeTest->setPosition(0,0,0);*/
		// Fin Nave
	}

};


int main (void)
{

	Example1 app;
	app.go();
	return 0;
}