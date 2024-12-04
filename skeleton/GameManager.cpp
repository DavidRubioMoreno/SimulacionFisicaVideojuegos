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
	//FLOOR
	statics.push_back(new RigidStaticObject(pSys->getScene(), colorOrange, Vector3(0, -60, 0), RigidStaticObject::PLANE, Vector3(50, 5, 150)));

	statics.push_back(new RigidStaticObject(pSys->getScene(), colorOrange, Vector3(0, -40, -150), RigidStaticObject::PLANE, Vector3(50, 25, 20)));
	statics.push_back(new RigidStaticObject(pSys->getScene(), colorOrange, Vector3(0, -40, 150), RigidStaticObject::PLANE, Vector3(50, 25, 20)));

	statics.push_back(new RigidStaticObject(pSys->getScene(), colorBlack, Vector3(0, -50, 70), RigidStaticObject::PLANE, Vector3(20, 25, 3)));
	statics.push_back(new RigidStaticObject(pSys->getScene(), colorBlack, Vector3(0, -50, -70), RigidStaticObject::PLANE, Vector3(20, 25, 3)));
	statics.push_back(new RigidStaticObject(pSys->getScene(), colorBlack, Vector3(0, -50, 0), RigidStaticObject::PLANE, Vector3(20, 50, 3)));
	//statics.push_back(new RigidStaticObject(pSys->getScene(), colorRed, Vector3(0, 5, 60), RigidStaticObject::PLANE, Vector3(50, 50, 5)));
	//statics.push_back(new RigidStaticObject(pSys->getScene(), colorRed, Vector3(0, 20, -60), RigidStaticObject::PLANE, Vector3(50, 50, 5)));

	camera->setPos(Vector3(150, 0, 0));
	camera->setDir(Vector3(-1, 0, 0));

	Vector3 initialWallPos(0, 10, -50);

	mainSpawner = pSys->addSolidGenerator(ParticleSystem::NONE, ParticleSystem::BOX, Vector3(0, 50, 0));
	pSys->setGeneratorParticleSize(mainSpawner, Vector3(10, 1, 20));
	pSys->setGeneratorRandomColor(mainSpawner, true);
	pSys->setGeneratorLifeTime(mainSpawner, 10000);

	ballSpawner = pSys->addSolidGenerator(ParticleSystem::NONE, ParticleSystem::SPHERE, Vector3(0, 50, 0));
	pSys->setGeneratorParticleSize(ballSpawner, Vector3(10, 0, 0));
	pSys->setGeneratorRandomColor(ballSpawner, true);
	pSys->setGeneratorLifeTime(ballSpawner, 10000);

	blockSpawner = pSys->addSolidGenerator(ParticleSystem::NONE, ParticleSystem::BOX, Vector3(0, 50, 0));
	pSys->setGeneratorParticleSize(blockSpawner, Vector3(5, 5, 5));
	pSys->setGeneratorRandomColor(blockSpawner, true);
	pSys->setGeneratorLifeTime(blockSpawner, 10000);

}

void GameManager::keyPress(unsigned char key, const PxTransform& camTr)
{
	Vector3 mousePos = camera->getMousePos();
	Vector3 mappingVector = Vector3(0, mapCoordinates().y, mapCoordinates().x);

	pSys->setGeneratorPosition(mainSpawner, mappingVector);
	pSys->setGeneratorPosition(ballSpawner, mappingVector);
	pSys->setGeneratorPosition(blockSpawner, mappingVector);

	switch (toupper(key))
	{
	case 'B':
		pSys->generatorCreateObject(mainSpawner);
		break;
	case 'N':
		pSys->generatorCreateObject(ballSpawner);
		break;
	case 'M':
		pSys->generatorCreateObject(blockSpawner);
		break;
	default:
		break;
	}
}


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

	return PxVec2((x_max + camera->getEye().z) - (camera->getMousePos().x / window->x) * (x_max - x_min),
		(y_max + camera->getEye().y) - (camera->getMousePos().y / window->y) * (y_max - y_min));
}

void GameManager::update(double t)
{
	//std::cout << "X: " << camera->getMousePos().x << " Y: " << camera->getMousePos().y << "\n";
	//std::cout << "X: " << window->x << " Y: " << window->y << "\n";
	//std::cout << "X: " << camera->getEye().z << " Y: " << camera->getEye().y << "\n";

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



void GameManager::playerHit()
{

}


