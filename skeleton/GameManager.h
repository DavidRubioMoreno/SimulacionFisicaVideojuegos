#pragma once
#include <vector>
#include "callbacks.hpp"
#include <list>

class ParticleSystem;
class RigidStaticObject;
class RigidDynamicObject;
class ParticleGenerator;

class GameManager
{
public:
	enum State {INTRO,GAME,FINAL};
	GameManager(ParticleSystem* sys, Camera* cam, physx::PxVec3* window);
	~GameManager();
	void updateState(State next);
	void playerHit();
	void init();
	void update(double t);
	void onCollision(physx::PxActor* actor1, physx::PxActor* actor2);
	void keyPress(unsigned char key, const physx::PxTransform& camera);
	void updateIntroState();
	void emitFire(bool emit);
private:
	void setState(State next);
	void enterState(State state);
	void exitState(State state);
	void updateUI();
	physx::PxVec2 mapCoordinates();
	State currentState;
	ParticleSystem* pSys = nullptr;
	std::vector<RigidStaticObject*> statics;
	std::vector<RigidDynamicObject*> dynamics;
	std::list<ParticleGenerator*>::iterator mainSpawner;
	std::list<ParticleGenerator*>::iterator ballSpawner;
	std::list<ParticleGenerator*>::iterator blockSpawner;
	const Vector4 colorRed = { 1, 0, 0, 1 };
	const Vector4 colorGreen = { 0, 1, 0, 1 };
	const Vector4 colorBlue = { 0, 0, 1, 1 };
	const Vector4 colorWhite = { 1, 1, 1, 1 };
	const Vector4 colorOrange = { 255, 2, 0.0, 1.0 };
	const Vector4 colorBlack = { 2, 0.5, 0.1, 1.0 };
	Camera* camera = nullptr;
	physx::PxVec3* window = nullptr;
	int x_min = -143, x_max = 143;
	int y_min = -75, y_max = 75;

};

