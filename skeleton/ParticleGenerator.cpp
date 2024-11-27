#include "ParticleGenerator.h"
//#include "RenderUtils.hpp"


using namespace physx;

ParticleGenerator::ParticleGenerator(ParticleSystem* sys, ParticleSystem::GeneratorType type, ParticleSystem::SolidShape shapetype, Vector3 pos)
	: generationTime(sys->getData().generationSpeed[type]), elapsedTime(0.0),
	timeToNextGen(generationTime), sys(sys), generationSpawn(pos), type(type) 
{
	switch (shapetype)
	{
	case ParticleSystem::BOX:
		sphere = CreateShape(PxBoxGeometry(1,1,1));
		break;
	case ParticleSystem::SPHERE:
		sphere = CreateShape(PxSphereGeometry(1));
		break;
	case ParticleSystem::CAPSULE:
		sphere = CreateShape(PxCapsuleGeometry(1, 1));
		break;
	default:
		sphere = CreateShape(PxSphereGeometry(1));
		break;
	}

	currentData.color.clear();
	currentData.particleNumber.clear();
	currentData.generationSpeed.clear();
	currentData.velocityGaussian.clear();
	currentData.positionGaussian.clear();
	currentData.velocityUniform.clear();
	currentData.positionUniform.clear();
	currentData.destroyRange.clear();
	currentData.mass.clear();
	currentData.lifeTime.clear();
	currentData.randomColor.clear();

	currentData.color.push_back(sys->getData().color[type]);
	currentData.particleNumber.push_back(sys->getData().particleNumber[type]);
	currentData.generationSpeed.push_back(sys->getData().generationSpeed[type]);
	currentData.velocityGaussian.push_back(sys->getData().velocityGaussian[type]);
	currentData.velocityUniform.push_back(sys->getData().velocityUniform[type]);
	currentData.positionGaussian.push_back(sys->getData().positionGaussian[type]);
	currentData.positionUniform.push_back(sys->getData().positionUniform[type]);
	currentData.destroyRange.push_back(sys->getData().destroyRange[type]);
	currentData.lifeTime.push_back(sys->getData().lifeTime[type]);
	currentData.mass.push_back(sys->getData().mass[type]);
	currentData.randomColor.push_back(sys->getData().randomColor[type]);
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
