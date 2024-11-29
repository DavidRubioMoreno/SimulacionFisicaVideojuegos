#include "ParticleGenerator.h"
//#include "RenderUtils.hpp"


using namespace physx;

ParticleGenerator::ParticleGenerator(ParticleSystem* sys, ParticleSystem::GeneratorType type, ParticleSystem::SolidShape shapetype, Vector3 pos)
	: generationTime(sys->getData().generationSpeed[type]), elapsedTime(0.0),
	timeToNextGen(generationTime), sys(sys), generationSpawn(pos), type(type) , shape(shapetype)
{

	Vector3 size = sys->getData().size[type];

	switch (shapetype)
	{
	case ParticleSystem::BOX:
		sphere = CreateShape(PxBoxGeometry(size));
		break;
	case ParticleSystem::SPHERE:
		sphere = CreateShape(PxSphereGeometry(size.magnitude()));
		break;
	case ParticleSystem::CAPSULE:
		sphere = CreateShape(PxCapsuleGeometry(size.x, size.y));
		break;
	default:
		sphere = CreateShape(PxSphereGeometry(size.magnitude()));
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
	currentData.density.clear();
	currentData.lifeTime.clear();
	currentData.randomColor.clear();
	currentData.size.clear();

	currentData.color.push_back(sys->getData().color[type]);
	currentData.particleNumber.push_back(sys->getData().particleNumber[type]);
	currentData.generationSpeed.push_back(sys->getData().generationSpeed[type]);
	currentData.velocityGaussian.push_back(sys->getData().velocityGaussian[type]);
	currentData.velocityUniform.push_back(sys->getData().velocityUniform[type]);
	currentData.positionGaussian.push_back(sys->getData().positionGaussian[type]);
	currentData.positionUniform.push_back(sys->getData().positionUniform[type]);
	currentData.destroyRange.push_back(sys->getData().destroyRange[type]);
	currentData.lifeTime.push_back(sys->getData().lifeTime[type]);
	currentData.density.push_back(sys->getData().density[type]);
	currentData.randomColor.push_back(sys->getData().randomColor[type]);
	currentData.size.push_back(sys->getData().size[type]);
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

void ParticleGenerator::changeSize(const Vector3& size)
{
	currentData.size.front() = size;
	sphere->release();
	switch (shape)
	{
	case ParticleSystem::BOX:
		sphere = CreateShape(PxBoxGeometry(size));
		break;
	case ParticleSystem::SPHERE:
		sphere = CreateShape(PxSphereGeometry(size.magnitude()));
		break;
	case ParticleSystem::CAPSULE:
		sphere = CreateShape(PxCapsuleGeometry(size.x, size.y));
		break;
	default:
		sphere = CreateShape(PxSphereGeometry(size.magnitude()));
		break;
	}

}

void ParticleGenerator::addForceGenerator(std::list<ForceGenerator*>::iterator forceGenerator)
{
	subscriptions.push_back(forceGenerator);
}
