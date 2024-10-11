#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <PxPhysicsAPI.h>

constexpr float GRAVITY = -9.81;
constexpr double DAMPING = 0.000001;

class ParticleGenerator;

class Particle;

class ParticleSystem
{
public:
	enum GeneratorType { GAUSSIAN, UNIFORM };

	ParticleSystem() = default;
	~ParticleSystem();
	void updateParticles(double t);
	void updateGenerators(double t);
	void addParticle(Particle* p);
	std::list<ParticleGenerator*>::iterator addGenerator(GeneratorType type);
	void setGeneratorPosition(std::list<ParticleGenerator*>::iterator id, physx::PxVec3 position);
private:
	std::list<ParticleGenerator*> generators;
	std::list<Particle*> particles;
	float elapsedTime = 0;
};

