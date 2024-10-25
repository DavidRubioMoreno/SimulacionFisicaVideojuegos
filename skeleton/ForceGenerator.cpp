#include "ForceGenerator.h"

ForceGenerator::ForceGenerator(ParticleSystem::ForceGeneratorType id, Vector3 centre, Vector3 f) : type(id), centre(centre), force(f)
{

}

ForceGenerator::~ForceGenerator()
{
	particles.clear();
}

std::list<Particle*>::iterator ForceGenerator::addParticle(Particle* p)
{
	particles.push_back(p);

	return --particles.end();
}

void ForceGenerator::elimParticle(std::list<Particle*>::iterator p)
{
	particles.erase(p);
}

