#pragma once
#include "ParticleGenerator.h"
class GaussianGenerator : public ParticleGenerator
{
public:
	GaussianGenerator() : ParticleGenerator::ParticleGenerator(1.0, 0.0, nullptr) {}
	GaussianGenerator(float genTime, double t, ParticleSystem* sys) : ParticleGenerator::ParticleGenerator(genTime, t, sys) {}
	void init() override;
	void update(double t) override;
protected:
	void generateParticle() override;
};

