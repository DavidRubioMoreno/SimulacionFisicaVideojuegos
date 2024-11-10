#pragma once

#include "Particle.h"
#include "ParticleSystem.h"
#include <PxPhysicsAPI.h>
#include <random>
#include <chrono>
#include "ForceGenerator.h"

class ParticleGenerator
{	
protected:
	ParticleGenerator(double t, ParticleSystem* sys, ParticleSystem::GeneratorType type);		
	virtual ~ParticleGenerator();
	virtual void init() = 0;	
	virtual void update(double t);
	void setSpawnPoint(Vector3& v);
	virtual void generateParticle() = 0;
	void addForceGenerator(std::list<ForceGenerator*>::iterator forceGenerator);
	const std::vector<std::list<ForceGenerator*>::iterator>& subs() { return subscriptions; }

	Vector3 generationSpawn;
	double generationTime;
	float timeToNextGen;
	float elapsedTime;
	const float PARTICLE_TIME = 10.0;

	ParticleSystem* sys = nullptr;
	ParticleSystem::GeneratorType type;
	physx::PxShape* sphere = nullptr;
	ParticleSystem::Info currentData;

	std::vector<std::list<ForceGenerator*>::iterator>subscriptions;

	friend class ParticleSystem;	
};

