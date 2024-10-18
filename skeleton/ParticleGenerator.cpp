#include "ParticleGenerator.h"
//#include "RenderUtils.hpp"


using namespace physx;

ParticleGenerator::ParticleGenerator(float genTime, double t, ParticleSystem* sys, ParticleSystem::GeneratorType type)
	: generationTime(sys->getData().generationSpeed[type]), elapsedTime(t),
	timeToNextGen(genTime + t), sys(sys), generationSpawn(Vector3(0, 0, 0)), type(type) 
{
	PxSphereGeometry* geo = new PxSphereGeometry(1);
	sphere = CreateShape(*geo);
}


ParticleGenerator::~ParticleGenerator() {
	sys = nullptr;
	sphere->release();
	sphere = nullptr;
}

void ParticleGenerator::update(double t) {
	elapsedTime += t;
	if (elapsedTime > timeToNextGen) {
		generateParticle();
		timeToNextGen += generationTime;
	}
}

void ParticleGenerator::setSpawnPoint(Vector3& v) {
	generationSpawn = v;
}