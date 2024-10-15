#pragma once
#include "ParticleGenerator.h"
class GaussianGenerator : public ParticleGenerator
{
public:
	GaussianGenerator() : ParticleGenerator::ParticleGenerator(1.0, 0.0, nullptr, ParticleSystem::GeneratorType::FOG) {}
	GaussianGenerator(float genTime, double t, ParticleSystem* sys, ParticleSystem::GeneratorType type) : ParticleGenerator::ParticleGenerator(genTime, t, sys, type) {}
	void init() override;
	void update(double t) override;
protected:
	void generateParticle() override;
};

