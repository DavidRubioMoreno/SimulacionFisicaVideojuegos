#pragma once

#include "Particle.h"
#include "ParticleSystem.h"
#include <list>

class ForceGenerator
{
protected:

	ForceGenerator(ParticleSystem::ForceGeneratorType id, Vector3 centre, Vector3 f, Vector3 volume);
	~ForceGenerator();
	std::list<Particle*>::iterator addParticle(Particle* p);
	void elimParticle(std::list<Particle*>::iterator p);
	void activate(bool activate);
	virtual void updateParticles(double t) = 0;

	std::list<Particle*>particles;
	ParticleSystem::ForceGeneratorType type;
	Vector3 force;
	Vector3 centre;
	Vector3 volume;
	bool active;

	friend class ParticleSystem;
};

