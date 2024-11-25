#pragma once
#include "ForceGenerator.h"
class GravitatoryGenerator : public ForceGenerator
{
public:
	GravitatoryGenerator(ParticleSystem::ForceGeneratorType id, Vector3 centre, Vector3 f, Vector3 volume) : ForceGenerator::ForceGenerator(id, centre, f, volume) {}
	~GravitatoryGenerator() = default;
	virtual void updateParticles(double t) override;
	virtual void updateSolids(double t) override;
};

