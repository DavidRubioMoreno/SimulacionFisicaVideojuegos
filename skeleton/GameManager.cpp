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

	car = nullptr;

}

void GameManager::onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
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


	camera->setPos(Vector3(150, 0, 0));
	camera->setDir(Vector3(-1, 0, 0));


	mainSpawner = pSys->addSolidGenerator(ParticleSystem::NONE, ParticleSystem::BOX, Vector3(0, 50, 0));
	pSys->setGeneratorParticleSize(mainSpawner, Vector3(10, 1, 50));
	pSys->setGeneratorRandomColor(mainSpawner, true);
	pSys->setGeneratorLifeTime(mainSpawner, LIFETIME);

	ballSpawner = pSys->addSolidGenerator(ParticleSystem::NONE, ParticleSystem::SPHERE, Vector3(0, 50, 0));
	pSys->setGeneratorDensity(ballSpawner, 0.1);
	pSys->setGeneratorParticleSize(ballSpawner, Vector3(10, 0, 0));
	pSys->setGeneratorRandomColor(ballSpawner, true);
	pSys->setGeneratorLifeTime(ballSpawner, LIFETIME);

	blockSpawner = pSys->addSolidGenerator(ParticleSystem::NONE, ParticleSystem::BOX, Vector3(0, 50, 0));
	pSys->setGeneratorParticleSize(blockSpawner, Vector3(5, 5, 5));
	//pSys->setGeneratorDensity(blockSpawner, 1000000.0);
	pSys->setGeneratorRandomColor(blockSpawner, true);
	pSys->setGeneratorLifeTime(blockSpawner, LIFETIME);

	carSpawner = pSys->addSolidGenerator(ParticleSystem::NONE, ParticleSystem::CAPSULE, Vector3(0, 10, 150));
	pSys->setGeneratorParticleSize(carSpawner, Vector3(5, 10, 0));
	pSys->setGeneratorDensity(carSpawner, 0.9);
	pSys->setGeneratorDestroyRange(carSpawner, 500.0);
	pSys->setGeneratorLifeTime(carSpawner, LIFETIME);

	auto wind = pSys->addForceGenerator(ParticleSystem::WIND, Vector3(0, 0, 0), Vector3(0, 0, -10000000), Vector3(1000, 1000, 1000));
	pSys->applyForceGenerator(carSpawner, wind);

	auto water = pSys->addForceGenerator(ParticleSystem::BUOYANCY, Vector3(0, -50, 0), Vector3(0, 0, 0), Vector3(90, 20, 300), 1000);
	pSys->applyForceAllGenerators(water);

}

void GameManager::keyPress(unsigned char key, const PxTransform& camTr)
{

	switch (currentState)
	{
	case GameManager::INTRO:
		switch (toupper(key))
		{
		case ' ':
			updateState(GAME);
			break;
		default:
			break;
		}
		break;
	case GameManager::GAME:
		updateGameGenerators();
		switch (toupper(key))
		{
		case '1':
			if (!crossing)pSys->generatorCreateObject(mainSpawner);
			break;
		case '2':
			if (!crossing)pSys->generatorCreateObject(ballSpawner);
			break;
		case '3':
			if (!crossing)pSys->generatorCreateObject(blockSpawner);
			break;
		case ' ':
			startCrossing();
			break;
		default:
			break;
		}
		break;
	case GameManager::FINAL:
		break;
	default:
		break;
	}

	//std::cout << key << "\n";

	
}


void GameManager::updateIntroState()
{

}

void GameManager::startCrossing()
{
	crossing = !crossing;

	if (crossing) {
		car = pSys->generatorCreateObject(carSpawner);
	}
	else {
		car->addAccel(Vector3(0, LIFETIME * LIFETIME, 0));
		car = nullptr;
	}
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
		init();
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

void GameManager::updateGameGenerators()
{
	Vector3 mappingVector = Vector3(0, mapCoordinates().y, mapCoordinates().x);

	pSys->setGeneratorPosition(mainSpawner, mappingVector);
	pSys->setGeneratorPosition(ballSpawner, mappingVector);
	pSys->setGeneratorPosition(blockSpawner, mappingVector);
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
		if (crossing && car->getPos().y < HEIGHTLIMIT) {
			car->addAccel(Vector3(0, LIFETIME * LIFETIME, 0));
			crossing = false;
			car = nullptr;
		}
		break;
	case GameManager::FINAL:
		break;
	default:
		break;
	}

}





void GameManager::playerHit()
{

}


