#pragma once
#include "ForceGenerator.h"
class BuoyancyForceGenerator :public ForceGenerator
{
public:
	BuoyancyForceGenerator(ParticleSystem::ForceGeneratorType id, Vector3 centre, Vector3 f, Vector3 volume, float d);
	~BuoyancyForceGenerator();
	virtual void updateParticles(double t) override;
protected:
	float liquidDensity;
	Vector3 areaLimit1;
	Vector3 areaLimit2;
	Particle* liquidParticle = nullptr;

};

