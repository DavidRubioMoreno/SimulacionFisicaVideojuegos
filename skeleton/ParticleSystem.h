#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <PxPhysicsAPI.h>

constexpr float G = -9.81;
constexpr double DAMPING = 0.0001;
constexpr float DESTROY_RANGE = 250;
constexpr int GENTYPES = 5;
constexpr int MAXSOLIDS = 1000;

class ParticleGenerator;
class ForceGenerator;
class Particle;
class RigidDynamicObject;

struct GeneratorInfo {
	 std::vector<float> generationSpeed = { 0.05f, 0.01f, 0.005f, 0.01f, 0.0f };
	 std::vector<int> particleNumber = { 1, 1, 1, 1, 0};
	 std::vector<std::pair<float, float>> velocityGaussian = { {0.0, 1.0}, {0,0}, {0,0}, {0.0, 2.0}, {0,0} };
	 std::vector<std::pair<float, float>> velocityUniform = { {0,0}, {-10,10}, {-40,40}, {0,0} , {0,0} };
	 std::vector<std::pair<float, float>> positionGaussian = { {0,0.01}, {0,0}, {0,0} , {0.0, 10.0}, {0,0}};
	 std::vector<std::pair<float, float>> positionUniform = { {0,0}, {-50,50}, {0,0} , {0,0} ,{0,0} };
	 std::vector<physx::PxVec4>color = { {0, 0, 1, 0.8} , {0.5, 0.5, 0.5, 1}, {1, 0.3, 0.3, 1} , {0.1, 0.1, 0.8, 1}, {1, 1, 0, 1}};
	 std::vector<float> density = { 1000, 100, 2000, 1000, 1000 };
	 std::vector<float> lifeTime = {10.0, 10.0, 10.0, 10.0, 10.0};
	 std::vector<float> destroyRange = { DESTROY_RANGE, DESTROY_RANGE, DESTROY_RANGE, DESTROY_RANGE, DESTROY_RANGE };
	 std::vector<bool> randomColor = { false, false, false, false, false };
	 std::vector<physx::PxVec3> size = { {0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}, {1, 1, 1}, {0.5, 0.5, 0.5}, {1,1,1} };
};

class ParticleSystem
{
public:
	enum GeneratorType { FOUNTAIN, FOG, EXPLOSION, RAIN, DEFAULT };
	enum ForceGeneratorType { GRAVITY, WIND, TORNADO, EXPLOSIVE, SPRING, BUOYANCY };
	enum SpringType{BASIC, ANCHORED};
	enum DistributionType{UNIFORM, GAUSSIAN, NONE};
	enum SolidShape { BOX, SPHERE, CAPSULE };

	struct Info : GeneratorInfo{};

	ParticleSystem(physx::PxScene* scene);
	~ParticleSystem();
	
	void update(double t);
	void addParticle(Particle* p);
	void addSolid(RigidDynamicObject* rObject);
	GeneratorInfo getData() const { return data; }
	int getNumberSolids() const { return solidsInScene; }
	physx::PxScene* getScene();

	std::list<ParticleGenerator*>::iterator addGenerator(GeneratorType type);
	std::list<ParticleGenerator*>::iterator addSolidGenerator(DistributionType type, SolidShape shapeType, physx::PxVec3 pos = physx::PxVec3(0, 0, 0));
	std::list<ForceGenerator*>::iterator addForceGenerator(ForceGeneratorType id, physx::PxVec3 centre, physx::PxVec3 force, physx::PxVec3 volume = physx::PxVec3(100, 100, 100), float density = 1.000);
	void applyForceGenerator(std::list<ParticleGenerator*>::iterator pGen, std::list<ForceGenerator*>::iterator fGen);
	void activateForceGenerator(std::list<ForceGenerator*>::iterator fGen, bool active);
	std::list<ParticleGenerator*>::iterator generateSpring(SpringType type, int nParticles, float K, float initialLenght, physx::PxVec3 pos = physx::PxVec3(0,0,0));
	RigidDynamicObject* generatorCreateObject(std::list<ParticleGenerator*>::iterator pGen);

	void setGeneratorPosition(std::list<ParticleGenerator*>::iterator id, physx::PxVec3 position);
	void setGeneratorSpeed(std::list<ParticleGenerator*>::iterator id, float genSpeed);
	void setGeneratorParticleNumber(std::list<ParticleGenerator*>::iterator id, int particlesPerGen);
	void setGeneratorVelGaussian(std::list<ParticleGenerator*>::iterator id, std::pair<float, float> distr);
	void setGeneratorVelUniform(std::list<ParticleGenerator*>::iterator id, std::pair<float, float> range);
	void setGeneratorPosGaussian(std::list<ParticleGenerator*>::iterator id, std::pair<float, float> distr);
	void setGeneratorPosUniform(std::list<ParticleGenerator*>::iterator id, std::pair<float, float> range);
	void setGeneratorColor(std::list<ParticleGenerator*>::iterator id, physx::PxVec4 color);
	void setGeneratorRandomColor(std::list<ParticleGenerator*>::iterator id, bool random);
	void setGeneratorDestroyRange(std::list<ParticleGenerator*>::iterator id, float destroyRange);
	void setGeneratorLifeTime(std::list<ParticleGenerator*>::iterator id, float time);
	void setGeneratorDensity(std::list<ParticleGenerator*>::iterator id, float density);
	void setGeneratorParticleSize(std::list<ParticleGenerator*>::iterator id, physx::PxVec3 size);
private:
	void updateParticles(double t);
	void updateSolids(double t);
	void updateGenerators(double t);
	bool particleOutOfRange(const physx::PxVec3& position, const float& range) const;
	void eliminateSubscriptions(Particle* p);
	void eliminateSubscriptionsSolid(RigidDynamicObject* s);

	std::list<ParticleGenerator*> generators;
	std::list<ForceGenerator*> forceGenerators;
	std::list<Particle*> particles;
	std::list<RigidDynamicObject*> dynamicObjects;
	physx::PxScene* gScene = nullptr;
	float elapsedTime = 0;
	int solidsInScene = 0;
	GeneratorInfo data;
};

