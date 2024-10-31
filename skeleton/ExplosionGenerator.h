#pragma once
#include "ForceGenerator.h"

class ExplosionGenerator : public ForceGenerator
{
public:
	ExplosionGenerator(ParticleSystem::ForceGeneratorType id, Vector3 centre, Vector3 f, Vector3 volume);
	~ExplosionGenerator() = default;
	virtual void updateParticles(double t) override;
protected:
	float elapsedTime;
	const float DURATION = 5.0;
	int K;
	float R;
};

