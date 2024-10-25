#include "ForceGenerator.h"

ForceGenerator::ForceGenerator(ParticleSystem::ForceGeneratorType id, Vector3 centre, Vector3 f) : type(id), centre(centre), force(f)
{

}

ForceGenerator::~ForceGenerator()
{
	particles.clear();
}

void ForceGenerator::addParticle(Particle* p)
{
	particles.push_back(p);
}

void ForceGenerator::elimParticle(std::list<Particle*>::iterator p)
{
	particles.erase(p);
}

