#pragma once
#include "ParticleGenerator.h"
class GaussianGenerator : public ParticleGenerator
{
public:
	GaussianGenerator() : ParticleGenerator::ParticleGenerator(nullptr, ParticleSystem::GeneratorType::FOG) {}
	GaussianGenerator(ParticleSystem* sys, ParticleSystem::GeneratorType type) : ParticleGenerator::ParticleGenerator(sys, type) {}
	void init() override;
	void update(double t) override;
protected:
	void generateParticle() override;
};

