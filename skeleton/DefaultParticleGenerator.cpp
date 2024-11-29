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
	//std::cout << generationSpawn.x << ", " << generationSpawn.y << ", " << generationSpawn.z << ", " << "\n";
	/*if (generationSpawn.x < 2) { speed = Vector3(0, 100, 0); }*/
	sys->addParticle(new Particle(currentData.color.front(), generationSpawn + Vector3(0, 0, 0), speed, Vector3(0, 0, 0), DAMPING, elapsedTime + currentData.lifeTime.front(), this, sphere));
	
}
