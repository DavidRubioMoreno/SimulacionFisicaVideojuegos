#include "DefaultParticleGenerator.h"

void DefaultParticleGenerator::init()
{

}

void DefaultParticleGenerator::update(double t)
{

}

void DefaultParticleGenerator::generateParticle()
{
	sys->addParticle(new Particle(currentData.color[0], generationSpawn + Vector3(0,0,0), Vector3(0,0,0), Vector3(0,0,0), DAMPING, elapsedTime + PARTICLE_TIME, this, sphere));
}
