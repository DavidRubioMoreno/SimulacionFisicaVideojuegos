#include "ParticleGenerator.h"
//#include "RenderUtils.hpp"


using namespace physx;

ParticleGenerator::ParticleGenerator(double t, ParticleSystem* sys, ParticleSystem::GeneratorType type)
	: generationTime(sys->getData().generationSpeed[type]), elapsedTime(t),
	timeToNextGen(generationTime + t), sys(sys), generationSpawn(Vector3(0, 0, 0)), type(type) 
{
	PxSphereGeometry* geo = new PxSphereGeometry(1);
	sphere = CreateShape(*geo);

	currentData.color.clear();
	currentData.particleNumber.clear();
	currentData.generationSpeed.clear();
	currentData.velocityGaussian.clear();
	currentData.positionGaussian.clear();
	currentData.velocityUniform.clear();
	currentData.positionUniform.clear();

	currentData.color.push_back(sys->getData().color[type]);
	currentData.particleNumber.push_back(sys->getData().particleNumber[type]);
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
		for (size_t i = 0; i < currentData.particleNumber.front(); i++)
		{
			generateParticle();
		}	
		timeToNextGen += currentData.generationSpeed.front();
	}
}

void ParticleGenerator::setSpawnPoint(Vector3& v) {
	generationSpawn = v;
}

void ParticleGenerator::addForceGenerator(std::list<ForceGenerator*>::iterator forceGenerator)
{
	subscriptions.push_back(forceGenerator);
}
