#pragma once

#include "Particle.h"
#include "ParticleSystem.h"
#include <list>

class ForceGenerator
{
public:

	ForceGenerator(ParticleSystem::ForceGeneratorType id, Vector3 centre, Vector3 f);
	~ForceGenerator();
	void addParticle(Particle* p);
	void elimParticle(std::list<Particle*>::iterator p);
	virtual void updateParticles(double t) = 0;
protected:
	std::list<Particle*>particles;
	ParticleSystem::ForceGeneratorType type;
	Vector3 force;
	Vector3 centre;
};

