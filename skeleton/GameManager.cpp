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
	finishLine = nullptr;

}

void GameManager::onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
	if (crossing && (actor1 == finishLine->getActor() && actor2 == car->getActor()
		|| actor2 == finishLine->getActor() && actor1 == car->getActor())) {
		//std::cout << "GGS" << "\n";
	}
}

void GameManager::init()
{
	//FLOOR
	statics.push_back(new RigidStaticObject(pSys->getScene(), colorOrange, Vector3(0, -60, 0), RigidStaticObject::PLANE, Vector3(50, 5, 150)));

	statics.push_back(new RigidStaticObject(pSys->getScene(), colorOrange, Vector3(0, -40, -150), RigidStaticObject::PLANE, Vector3(50, 25, 20)));
	statics.push_back(new RigidStaticObject(pSys->getScene(), colorOrange, Vector3(0, -40, 150), RigidStaticObject::PLANE, Vector3(50, 25, 20)));

	//BRIDGE
	statics.push_back(new RigidStaticObject(pSys->getScene(), colorBlack, Vector3(0, -50, 70), RigidStaticObject::PLANE, Vector3(20, 25, 3)));
	statics.push_back(new RigidStaticObject(pSys->getScene(), colorBlack, Vector3(0, -50, -70), RigidStaticObject::PLANE, Vector3(20, 25, 3)));
	statics.push_back(new RigidStaticObject(pSys->getScene(), colorBlack, Vector3(0, -50, 0), RigidStaticObject::PLANE, Vector3(20, 50, 3)));

	//FINISHLINE WALLS
	//statics.push_back(new RigidStaticObject(pSys->getScene(), colorBlack, Vector3(0, 0, -150), RigidStaticObject::PLANE, Vector3(40, 1, 5)));
	statics.push_back(new RigidStaticObject(pSys->getScene(), colorBlack, Vector3(35, -8, -150), RigidStaticObject::PLANE, Vector3(1, 8, 1)));
	statics.push_back(new RigidStaticObject(pSys->getScene(), colorBlack, Vector3(-35, -8, -150), RigidStaticObject::PLANE, Vector3(1, 8, 1)));

	finishLine = new RigidStaticObject(pSys->getScene(), colorGreen, Vector3(0, -15, -165), RigidStaticObject::CAPSULE, Vector3(7, 7, 0));
	statics.push_back(finishLine);


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

	carSpawner = pSys->addSolidGenerator(ParticleSystem::NONE, ParticleSystem::SPHERE, Vector3(0, 10, 150));
	pSys->setGeneratorParticleSize(carSpawner, Vector3(3, 3, 0));
	pSys->setGeneratorDensity(carSpawner, 0.9);
	pSys->setGeneratorDestroyRange(carSpawner, 500.0);
	pSys->setGeneratorLifeTime(carSpawner, LIFETIME);

	auto water = pSys->addForceGenerator(ParticleSystem::BUOYANCY, Vector3(0, -50, 0), Vector3(0, 0, 0), Vector3(90, 20, 300), 1000);
	pSys->applyForceAllGenerators(water);

	auto motor = pSys->addForceGenerator(ParticleSystem::TORQUE, Vector3(0, 0, 0), Vector3(-100000, 0, 0), Vector3(1000, 1000, 1000));
	pSys->applyForceGenerator(carSpawner, motor);

	carSmoke = pSys->addGenerator(ParticleSystem::RAIN);
	pSys->setGeneratorColor(carSmoke, Vector4(0.3, 0.3, 0.3, 1.0));
	pSys->setGeneratorLifeTime(carSmoke, 4.0);
	pSys->setGeneratorPosGaussian(carSmoke, { 0, 1 });
	pSys->activateGenerator(carSmoke, false);

	auto inverseGravity = pSys->addForceGenerator(ParticleSystem::GRAVITY, Vector3(0, 0, 0), Vector3(0, 3.8, 0));
	pSys->applyForceGenerator(carSmoke, inverseGravity);

	cursorMarker = pSys->addGenerator(ParticleSystem::EXPLOSION);
	pSys->setGeneratorColor(cursorMarker, colorRed);
	pSys->setGeneratorLifeTime(cursorMarker, 1.0);
	pSys->setGeneratorVelUniform(cursorMarker, { -2, 2 });
	pSys->setGeneratorSpeed(cursorMarker, 0.1);
	pSys->setGeneratorParticleSize(cursorMarker, Vector3(0.5, 0, 0));
	pSys->setGeneratorParticleNumber(cursorMarker, 5);

	auto upWind = pSys->addForceGenerator(ParticleSystem::WIND, Vector3(0, 0, -150), Vector3(0, 100000, 0));
	auto gravity = pSys->addForceGenerator(ParticleSystem::GRAVITY, Vector3(0, 0, 0), Vector3(0, -9.8, 0));

	auto springFinish1 = pSys->generateSpring(ParticleSystem::ANCHORED, 30, 500, 1, Vector3(35, -1, -150), LIFETIME, false, colorOrange);
	pSys->setGeneratorLifeTime(springFinish1, LIFETIME);
	auto springFinish2 = pSys->generateSpring(ParticleSystem::ANCHORED, 30, 500, 1, Vector3(-35, -1, -150), LIFETIME, false, colorOrange);
	pSys->setGeneratorLifeTime(springFinish2, LIFETIME);

	pSys->applyForceGenerator(springFinish1, upWind);
	pSys->applyForceGenerator(springFinish2, upWind);
	pSys->applyForceGenerator(springFinish1, gravity);
	pSys->applyForceGenerator(springFinish2, gravity);


}

void GameManager::demo()
{
	camera->setPos(Vector3(150, 0, 0));
	camera->setDir(Vector3(-1, 0, 0));

	statics.push_back(new RigidStaticObject(pSys->getScene(), colorOrange, Vector3(0, -60, 0), RigidStaticObject::PLANE, Vector3(50, 5, 150)));

	auto gen1 = pSys->addSolidGenerator(ParticleSystem::UNIFORM, ParticleSystem::BOX);
	pSys->setGeneratorRandomColor(gen1, true);
	pSys->setGeneratorParticleSize(gen1, Vector3(10, 2, 2));

	auto gen2 = pSys->addSolidGenerator(ParticleSystem::UNIFORM, ParticleSystem::CAPSULE, Vector3(0, 0, -50));
	pSys->setGeneratorRandomColor(gen2, true);

	auto gen3 = pSys->addSolidGenerator(ParticleSystem::UNIFORM, ParticleSystem::SPHERE, Vector3(0, 0, 50));
	pSys->setGeneratorParticleSize(gen3, Vector3(2, 0, 0));

	auto water = pSys->addForceGenerator(ParticleSystem::BUOYANCY, Vector3(0, -50, 0), Vector3(0, 0, 0), Vector3(90, 20, 300), 1000);
	pSys->applyForceGenerator(gen1, water);

	auto wind = pSys->addForceGenerator(ParticleSystem::WIND, Vector3(0, -20, 0), Vector3(500, 0, 500));
	pSys->applyForceGenerator(gen1, wind);

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

	pSys->activateGenerator(carSmoke, crossing);
	pSys->activateGenerator(cursorMarker, !crossing);

	if (crossing) {
		car = pSys->generatorCreateObject(carSpawner);		
	}
	else {
		car->addAccel(Vector3(0, LIFETIME * LIFETIME * LIFETIME, 0));
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

	Vector3 mappingVector = Vector3(0, mapCoordinates().y, mapCoordinates().x);

	switch (currentState)
	{
	case GameManager::INTRO:
		break;
	case GameManager::GAME:
		if (crossing) {

			Vector3 cameraPos = camera->getEye();
			cameraPos.z = car->getPos().z;
			cameraPos.y = car->getPos().y;
			camera->setPos(cameraPos);

			if (car->getPos().y < HEIGHTLIMIT || car->getPos().z < -200 || car->getPos().y > 100) {
				car->addAccel(Vector3(0, LIFETIME * LIFETIME, 0));
				crossing = false;
				car = nullptr;
				pSys->activateGenerator(carSmoke, false);
				pSys->activateGenerator(cursorMarker, true);
			}

			if (car != nullptr) {
				pSys->setGeneratorPosition(carSmoke, car->getPos());
			}		
		}
		pSys->setGeneratorPosition(cursorMarker, mappingVector);
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


