#pragma once

#include "ParticleGenerator.h"

class UniformGenerator : public ParticleGenerator
{
public:
	UniformGenerator() : ParticleGenerator::ParticleGenerator(0.0, nullptr, ParticleSystem::GeneratorType::FOUNTAIN) {}
	UniformGenerator(double t, ParticleSystem* sys, ParticleSystem::GeneratorType type) : ParticleGenerator::ParticleGenerator(t, sys, type) {}
	void init();
	void update(double t) override;
protected:
	void generateParticle() override;
};

