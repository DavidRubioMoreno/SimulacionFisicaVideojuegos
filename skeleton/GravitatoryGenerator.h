#pragma once
#include "ForceGenerator.h"
class GravitatoryGenerator : public ForceGenerator
{
public:
	GravitatoryGenerator(ParticleSystem::ForceGeneratorType id, Vector3 centre, Vector3 f) : ForceGenerator::ForceGenerator(id, centre, f) {}
	~GravitatoryGenerator() = default;
	virtual void updateParticles(double t) override;
protected:

};

