#include "DefaultParticleGenerator.h"

DefaultParticleGenerator::DefaultParticleGenerator(ParticleSystem* sys, ParticleSystem::SolidShape shape, Vector3 pos, ParticleSystem::GeneratorType type)
	: ParticleGenerator::ParticleGenerator(sys, type, shape, pos) {
	solid = true;
}

void DefaultParticleGenerator::init()
{

}

void DefaultParticleGenerator::update(double t)
{
	elapsedTime += t;
}

void DefaultParticleGenerator::generateParticle()
{
	Vector3 speed(0, 0, 0);

	Vector4 color = currentData.color.front();

	if (currentData.randomColor.front()) {
		Vector3 rgb = getUniformDistribution(0, 1);
		color = Vector4(rgb, color.w);
	}

	if (solid) {
		sys->addSolid(new RigidDynamicObject(sys->getScene(), color, generationSpawn, elapsedTime + currentData.lifeTime.front(), speed, sphere, this, currentData.density.front()));
	}
	else {
		sys->addParticle(new Particle(color, generationSpawn, speed, Vector3(0, 0, 0), DAMPING, elapsedTime + currentData.lifeTime.front(), this, sphere));
	}
}
