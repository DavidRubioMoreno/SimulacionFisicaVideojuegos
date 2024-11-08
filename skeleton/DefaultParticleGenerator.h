#pragma once
#include "ParticleGenerator.h"

class DefaultParticleGenerator : public ParticleGenerator
{
public:
	DefaultParticleGenerator() : ParticleGenerator::ParticleGenerator(0.0, nullptr, ParticleSystem::GeneratorType::FOG) {}
	DefaultParticleGenerator(double t, ParticleSystem* sys, ParticleSystem::GeneratorType type) : ParticleGenerator::ParticleGenerator(t, sys, type) {}
	void init() override;
	void update(double t) override;
protected:
	void generateParticle() override;

};

