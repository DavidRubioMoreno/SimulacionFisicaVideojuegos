#include "GameManager.h"
#include "Particle.h"
#include "ProyectileController.h"
#include "ParticleSystem.h"
#include "ParticleGenerator.h"
#include "RigidDynamicObject.h"
#include "RigidStaticObject.h"

using namespace physx;

GameManager::GameManager(ParticleSystem* sys, Camera* cam, PxVec3* window) : currentState(INTRO), pSys(sys), camera(cam), window(window)
{
	init();
}

GameManager::~GameManager()
{
	switch (currentState)
	{
	case GameManager::INTRO:
		break;
	case GameManager::GAME:
		break;
	case GameManager::FINAL:
		break;
	default:
		break;
	}

	for (auto& solid : statics)
	{
		delete solid;
	}

	statics.clear();

	for (auto& solid : dynamics)
	{
		delete solid;
	}

	dynamics.clear();

}

void GameManager::init()
{
	//auto gDynamic = new RigidDynamicObject(pSys->getScene(), colorGreen, Vector3(50, 0, 0), 5.0f, Vector3(-10, 10, 0), RigidDynamicObject::BOX, Vector3(4, 4, 4), 1.0f, Vector3(5, 0, 5));
	statics.push_back(new RigidStaticObject(pSys->getScene(), colorRed, Vector3(0, -50, 0), RigidStaticObject::PLANE, Vector3(50, 5, 150)));
	//statics.push_back(new RigidStaticObject(pSys->getScene(), colorRed, Vector3(0, 100, 0), RigidStaticObject::PLANE, Vector3(50, 5, 100)));
	//statics.push_back(new RigidStaticObject(pSys->getScene(), colorRed, Vector3(0, 5, 60), RigidStaticObject::PLANE, Vector3(50, 50, 5)));
	//statics.push_back(new RigidStaticObject(pSys->getScene(), colorRed, Vector3(0, 20, -60), RigidStaticObject::PLANE, Vector3(50, 50, 5)));

	camera->setPos(Vector3(150, 0, 0));
	camera->setDir(Vector3(-1, 0, 0));

	Vector3 initialWallPos(0, 10, -50);

	mainSpawner = pSys->addSolidGenerator(ParticleSystem::NONE, ParticleSystem::BOX, Vector3(0, 50, 0));
	pSys->setGeneratorParticleSize(mainSpawner, Vector3(20, 5, 8));
	pSys->setGeneratorRandomColor(mainSpawner, true);

	/*for (size_t i = 0; i < 10; i++)
	{
		auto gen = pSys->addSolidGenerator(ParticleSystem::UNIFORM, ParticleSystem::SPHERE, Vector3(initialWallPos));
		pSys->setGeneratorPosUniform(gen, { 0,0 });
		pSys->setGeneratorVelUniform(gen, { 0,0 });
		pSys->setGeneratorRandomColor(gen, true);
		pSys->setGeneratorParticleSize(gen, Vector3(2.5, 0, 0));
		pSys->setGeneratorSpeed(gen, 0.15);
		pSys->setGeneratorDestroyRange(gen, 500);

		initialWallPos.z += 10;
	}*/

	

	/*for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			dynamics.push_back(new RigidDynamicObject(pSys->getScene(), colorBlue, initialWallPos, 10.0, Vector3(0, 0, 0), RigidDynamicObject::BOX, Vector3(2, 2, 4), 1000));
			initialWallPos.z += 10;
		}
		initialWallPos.y += 4.5;
		initialWallPos.z = -50;
	}*/
	
	//onCollision(gDynamic->getActor(), gStatic->getActor());
}

//void GameManager::setPlayer(Player* p)
//{
//	player = p;
//}
//
//void GameManager::setHead(IntroHead* h)
//{
//	head = h;
//}
//
//void GameManager::setEnemies(std::vector<Enemy*>* e)
//{
//	enemies = e;
//}
//
//void GameManager::setTextBox(OgreBites::TextBox* t)
//{
//	gameInfo = t;
//}

void GameManager::updateIntroState()
{

}

void GameManager::emitFire(bool emit)
{
	
}

void GameManager::updateState(State next)
{
	switch (currentState)
	{
	case GameManager::INTRO:
		if (next == GAME) setState(next);
		break;
	case GameManager::GAME:
		if (next == FINAL) setState(next);
		break;
	case GameManager::FINAL:
		if (next == INTRO) setState(next);
		break;
	default:
		break;
	}
}

//bool GameManager::keyPressed(const OgreBites::KeyboardEvent& evt)
//{
//	if (evt.keysym.sym == SDLK_SPACE) {
//		updateState(GAME);
//	}
//
//	return true;
//}

void GameManager::setState(State next)
{
	exitState(currentState);
	currentState = next;
	enterState(currentState);
	//cout << currentState << "\n";
}

void GameManager::enterState(State state)
{
	switch(state)
	{
	case GameManager::INTRO:
		updateUI();
		break;
	case GameManager::GAME:
		break;
	case GameManager::FINAL:
		break;
	default:
		break;
	}
}

void GameManager::exitState(State state)
{
	switch (state)
	{
	case GameManager::INTRO:
		break;
	case GameManager::GAME:
		break;
	case GameManager::FINAL:
		break;
	default:
		break;
	}
}

void GameManager::updateUI()
{
	switch (currentState)
	{
	case GameManager::INTRO:
		break;
	case GameManager::GAME:
		break;
	case GameManager::FINAL:
		break;
	default:
		break;
	}
}

physx::PxVec2 GameManager::mapCoordinates()
{
	return physx::PxVec2(x_max - (camera->getMousePos().x / window->x) * (x_max - x_min),
		y_max - (camera->getMousePos().y / window->y) * (y_max - y_min));
}

void GameManager::update(double t)
{
	//std::cout << "X: " << camera->getMousePos().x << " Y: " << camera->getMousePos().y << "\n";
	//std::cout << "X: " << window->x << " Y: " << window->y << "\n";

	switch (currentState)
	{
	case GameManager::INTRO:
		break;
	case GameManager::GAME:
		break;
	case GameManager::FINAL:
		break;
	default:
		break;
	}

}

void GameManager::onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}

void GameManager::keyPress(unsigned char key, const PxTransform& camTr)
{
	Vector3 mousePos = camera->getMousePos();

	switch (toupper(key))
	{
	case 'E':
		pSys->setGeneratorPosition(mainSpawner, Vector3(0, mapCoordinates().y, mapCoordinates().x));
		pSys->generatorCreateObject(mainSpawner);
		break;
	default:
		break;
	}
}

void GameManager::playerHit()
{

}


