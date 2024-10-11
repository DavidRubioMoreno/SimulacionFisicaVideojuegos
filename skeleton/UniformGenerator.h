#pragma once

#include "ParticleGenerator.h"

class UniformGenerator : public ParticleGenerator
{
public:
	UniformGenerator() : ParticleGenerator::ParticleGenerator(1.0, 0.0, nullptr) {}
	UniformGenerator(float genTime, double t, ParticleSystem* sys) : ParticleGenerator::ParticleGenerator(genTime, t, sys) {}
	void init();
	void update(double t) override;
protected:
	void generateParticle() override;
};

