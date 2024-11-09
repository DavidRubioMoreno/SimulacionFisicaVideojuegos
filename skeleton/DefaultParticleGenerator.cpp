#include "DefaultParticleGenerator.h"

void DefaultParticleGenerator::init()
{

}

void DefaultParticleGenerator::update(double t)
{

}

void DefaultParticleGenerator::generateParticle()
{
	Vector3 speed(0, 0, 0);
	/*if (generationSpawn.x < 2) { speed = Vector3(0, 100, 0); }*/
	sys->addParticle(new Particle(currentData.color[0], generationSpawn + Vector3(0,0,0), speed, Vector3(0, 0, 0), DAMPING, elapsedTime + PARTICLE_TIME, this, sphere));
	
}
