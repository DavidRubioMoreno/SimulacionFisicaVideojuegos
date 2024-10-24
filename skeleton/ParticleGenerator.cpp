#include "ParticleGenerator.h"
//#include "RenderUtils.hpp"


using namespace physx;

ParticleGenerator::ParticleGenerator(float genTime, double t, ParticleSystem* sys, ParticleSystem::GeneratorType type)
	: generationTime(sys->getData().generationSpeed[type]), elapsedTime(t),
	timeToNextGen(genTime + t), sys(sys), generationSpawn(Vector3(0, 0, 0)), type(type) 
{
	PxSphereGeometry* geo = new PxSphereGeometry(1);
	sphere = CreateShape(*geo);

	currentData.color.clear();
	currentData.generationSpeed.clear();
	currentData.velocityGaussian.clear();
	currentData.positionGaussian.clear();
	currentData.velocityUniform.clear();
	currentData.positionUniform.clear();

	currentData.color.push_back(sys->getData().color[type]);
	currentData.generationSpeed.push_back(sys->getData().generationSpeed[type]);
	currentData.velocityGaussian.push_back(sys->getData().velocityGaussian[type]);
	currentData.velocityUniform.push_back(sys->getData().velocityUniform[type]);
	currentData.positionGaussian.push_back(sys->getData().positionGaussian[type]);
	currentData.positionUniform.push_back(sys->getData().positionUniform[type]);
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
		timeToNextGen += currentData.generationSpeed[0];
	}
}

void ParticleGenerator::setSpawnPoint(Vector3& v) {
	generationSpawn = v;
}