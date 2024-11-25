#pragma once
#include "ParticleGenerator.h"
class GaussianGenerator : public ParticleGenerator
{
public:
	GaussianGenerator() : ParticleGenerator::ParticleGenerator(nullptr, ParticleSystem::GeneratorType::FOUNTAIN) {}
	GaussianGenerator(ParticleSystem* sys, ParticleSystem::GeneratorType type) : ParticleGenerator::ParticleGenerator(sys, type) {}
	GaussianGenerator(ParticleSystem* sys, ParticleSystem::SolidShape shape, Vector3 pos, ParticleSystem::GeneratorType type = ParticleSystem::GeneratorType::FOUNTAIN);
	void init() override;
	void update(double t) override;
protected:
	void generateParticle() override;
	bool solid = false;
};

