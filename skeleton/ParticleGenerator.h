#pragma once

#include "Particle.h"
#include "RigidDynamicObject.h"
#include "ParticleSystem.h"
#include <PxPhysicsAPI.h>
#include <random>
#include <chrono>
#include "ForceGenerator.h"

class ParticleGenerator
{	
protected:
	ParticleGenerator(ParticleSystem* sys, ParticleSystem::GeneratorType type,
		ParticleSystem::SolidShape shapetype = ParticleSystem::SolidShape::SPHERE,Vector3 pos = Vector3(0, 0, 0));
	virtual ~ParticleGenerator();
	virtual void init() = 0;	
	virtual void update(double t);
	void setSpawnPoint(Vector3& v);
	void changeSize(const Vector3& size);
	virtual void generateParticle() = 0;
	void setActive(bool active);
	void addForceGenerator(std::list<ForceGenerator*>::iterator forceGenerator);
	Vector3 getUniformDistribution(float a, float b);
	Vector3 getNormalDistribution(float mean, float dv);
	const std::vector<std::list<ForceGenerator*>::iterator>& subs() { return subscriptions; }

	Vector3 generationSpawn;
	double generationTime;
	float timeToNextGen;
	float elapsedTime;
	const float PARTICLE_TIME = 10.0;
	const float SOLIDTIME = 15.0;
	bool solid = false;
	bool active = true;

	ParticleSystem* sys = nullptr;
	ParticleSystem::GeneratorType type;
	ParticleSystem::SolidShape shape;
	physx::PxShape* sphere = nullptr;
	ParticleSystem::Info currentData;

	std::vector<std::list<ForceGenerator*>::iterator>subscriptions;

	friend class ParticleSystem;	
};

