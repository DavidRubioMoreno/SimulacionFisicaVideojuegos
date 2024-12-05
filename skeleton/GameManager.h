#pragma once
#include <vector>
#include "callbacks.hpp"
#include <list>

class ParticleSystem;
class RigidStaticObject;
class RigidDynamicObject;
class ParticleGenerator;

using Generator = std::list<ParticleGenerator*>::iterator;

class GameManager
{
public:
	enum State {INTRO,GAME,FINAL};
	GameManager(ParticleSystem* sys, Camera* cam, physx::PxVec3* window);
	~GameManager();
	void update(double t);
	void onCollision(physx::PxActor* actor1, physx::PxActor* actor2);
	void keyPress(unsigned char key, const physx::PxTransform& camera);
private:
	void updateState(State next);
	void playerHit();
	void init();
	void demo();
	void updateIntroState();
	void startCrossing();
	void setState(State next);
	void enterState(State state);
	void exitState(State state);
	void updateUI();
	void updateGameGenerators();
	physx::PxVec2 mapCoordinates();

	State currentState;
	ParticleSystem* pSys = nullptr;

	std::vector<RigidStaticObject*> statics;
	std::vector<RigidDynamicObject*> dynamics;

	RigidDynamicObject* car = nullptr;

	Generator mainSpawner;
	Generator ballSpawner;
	Generator blockSpawner;
	Generator carSpawner;
	Generator carSmoke;

	const Vector4 colorRed = { 1, 0, 0, 1 };
	const Vector4 colorGreen = { 0, 1, 0, 1 };
	const Vector4 colorBlue = { 0, 0, 1, 1 };
	const Vector4 colorWhite = { 1, 1, 1, 1 };
	const Vector4 colorOrange = { 255, 2, 0.0, 1.0 };
	const Vector4 colorBlack = { 2, 0.5, 0.1, 1.0 };

	Camera* camera = nullptr;
	physx::PxVec3* window = nullptr;

	bool crossing = false;
	bool finished = false;

	const int x_min = -143, x_max = 143;
	const int y_min = -75, y_max = 75;

	const float HEIGHTLIMIT = -80;
	const float LIFETIME = 10000;

};

