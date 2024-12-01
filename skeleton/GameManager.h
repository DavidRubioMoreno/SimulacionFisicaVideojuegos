#pragma once
#include <vector>
#include "callbacks.hpp"

class ParticleSystem;
class RigidStaticObject;

class GameManager
{
public:
	enum State {INTRO,GAME,FINAL};
	GameManager(ParticleSystem* sys);
	~GameManager();
	void updateState(State next);
	void playerHit();
	void init();
	void update(double t);
	void onCollision(physx::PxActor* actor1, physx::PxActor* actor2);
	void keyPress(unsigned char key, const physx::PxTransform& camera);
	//void setPlayer(Player* p);
	//void setHead(IntroHead* h);
	//void setEnemies(std::vector<Enemy*>* e);
	//void setTextBox(OgreBites::TextBox* t);
	void updateIntroState();
	void emitFire(bool emit);
	//inline IntroHead* getHead() const { return head; }
private:
	void setState(State next);
	void enterState(State state);
	void exitState(State state);
	void updateUI();
	/*int playerLifes;
	const int initPlayerLifes;*/
	State currentState;
	ParticleSystem* pSys = nullptr;
	std::vector<RigidStaticObject*> statics;
	const Vector4 colorRed = { 1, 0, 0, 1 };
	const Vector4 colorGreen = { 0, 1, 0, 1 };
	const Vector4 colorBlue = { 0, 0, 1, 1 };
	const Vector4 colorWhite = { 1, 1, 1, 1 };
	//Player* player = nullptr;
	//IntroHead* head = nullptr;
	//IG2App* app = nullptr;
	//std::vector<Enemy*>* enemies = nullptr;
	//OgreBites::TextBox* gameInfo = nullptr;
};

