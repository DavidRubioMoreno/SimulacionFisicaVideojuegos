#pragma once

#include "Particle.h"
#include "RigidDynamicObject.h"
#include "ParticleSystem.h"
#include <list>

class ForceGenerator
{
protected:

	ForceGenerator(ParticleSystem::ForceGeneratorType id, Vector3 centre, Vector3 f, Vector3 volume);
	~ForceGenerator();
	std::list<Particle*>::iterator addParticle(Particle* p);
	std::list<RigidDynamicObject*>::iterator addSolid(RigidDynamicObject* s);
	void elimParticle(std::list<Particle*>::iterator p);
	void elimSolid(std::list<RigidDynamicObject*>::iterator s);
	void activate(bool activate);
	void update(double t);
	virtual void updateParticles(double t) = 0;
	virtual void updateSolids(double t) = 0;


	std::list<RigidDynamicObject*>solidObjects;
	std::list<Particle*>particles;
	ParticleSystem::ForceGeneratorType type;
	Vector3 force;
	Vector3 centre;
	Vector3 volume;
	bool active;

	friend class ParticleSystem;
};

