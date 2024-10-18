#pragma once

#include "Particle.h"
#include "ParticleSystem.h"
#include <PxPhysicsAPI.h>
#include <random>
#include <chrono>



class ParticleGenerator
{	
public:
	ParticleGenerator(float genTime, double t, ParticleSystem* sys, ParticleSystem::GeneratorType type);		
	virtual ~ParticleGenerator();
	virtual void init() = 0;	
	virtual void update(double t);
	void setSpawnPoint(Vector3& v);
protected:
	virtual void generateParticle() = 0;
	Vector3 generationSpawn;
	double generationTime;
	float timeToNextGen;
	float elapsedTime;
	const float PARTICLE_TIME = 5.0;
	ParticleSystem* sys = nullptr;
	ParticleSystem::GeneratorType type;
	physx::PxShape* sphere = nullptr;
	
};

