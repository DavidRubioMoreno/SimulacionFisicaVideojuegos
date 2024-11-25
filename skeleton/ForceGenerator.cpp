#include "ForceGenerator.h"

ForceGenerator::ForceGenerator(ParticleSystem::ForceGeneratorType id, Vector3 centre, Vector3 f, Vector3(volume)) : type(id), centre(centre), force(f), active(true), volume(volume)
{

}

ForceGenerator::~ForceGenerator()
{
	particles.clear();
	solidObjects.clear();
}

std::list<Particle*>::iterator ForceGenerator::addParticle(Particle* p)
{
	particles.push_back(p);

	return --particles.end();
}

std::list<RigidDynamicObject*>::iterator ForceGenerator::addSolid(RigidDynamicObject* s)
{
	solidObjects.push_back(s);

	return --solidObjects.end();
}

void ForceGenerator::elimParticle(std::list<Particle*>::iterator p)
{
	particles.erase(p);
}

void ForceGenerator::elimSolid(std::list<RigidDynamicObject*>::iterator s)
{
	solidObjects.erase(s);
}

void ForceGenerator::activate(bool a)
{
	active = a;
}

void ForceGenerator::update(double t)
{
	updateSolids(t);
	updateParticles(t);
}

