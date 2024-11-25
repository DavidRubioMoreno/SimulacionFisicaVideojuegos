#pragma once
#include "WindGenerator.h"

class TornadoGenerator : public WindGenerator
{
public:
	TornadoGenerator(ParticleSystem::ForceGeneratorType id, Vector3 centre, Vector3 f, Vector3 volume);
	~TornadoGenerator() = default;
	virtual void updateParticles(double t) override;
	virtual void updateSolids(double t) override;
protected:
	Vector3 getFinalforce(const Vector3& pos);
	int K;
};

