#include "GameManager.h"
#include "Particle.h"
#include "ProyectileController.h"
#include "ParticleSystem.h"
#include "ParticleGenerator.h"
#include "RigidDynamicObject.h"
#include "RigidStaticObject.h"

using namespace physx;

GameManager::GameManager(ParticleSystem* sys) : currentState(INTRO), pSys(sys)
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
}

void GameManager::init()
{
	auto gDynamic = new RigidDynamicObject(pSys->getScene(), colorGreen, Vector3(50, 0, 0), 5.0f, Vector3(-10, 10, 0), RigidDynamicObject::BOX, Vector3(4, 4, 4), 1.0f, Vector3(5, 0, 5));
	auto gStatic = new RigidStaticObject(pSys->getScene(), colorRed, Vector3(0, -50, 0), RigidStaticObject::PLANE, Vector3(50 ,5, 50));
	onCollision(gDynamic->getActor(), gStatic->getActor());
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

void GameManager::update(double t)
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

void GameManager::onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
	
}

void GameManager::keyPress(unsigned char key, const PxTransform& camera)
{
	switch (toupper(key))
	{
	case 'E':
		pSys->addSolidGenerator(ParticleSystem::DistributionType::UNIFORM, ParticleSystem::SolidShape::CAPSULE);
		break;
	default:
		break;
	}
}

void GameManager::playerHit()
{

}


