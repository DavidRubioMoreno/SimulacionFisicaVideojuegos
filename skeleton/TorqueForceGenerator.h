#pragma once
#include "ForceGenerator.h"
class TorqueForceGenerator : public ForceGenerator
{
public:
	TorqueForceGenerator(ParticleSystem::ForceGeneratorType id, Vector3 centre, Vector3 f, Vector3 volume) : ForceGenerator::ForceGenerator(id, centre, f, volume) {}
	~TorqueForceGenerator() = default;
	virtual void updateParticles(double t) override;
	virtual void updateSolids(double t) override;
};

