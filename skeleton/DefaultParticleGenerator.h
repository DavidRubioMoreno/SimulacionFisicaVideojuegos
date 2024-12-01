#pragma once
#include "ParticleGenerator.h"

class DefaultParticleGenerator : public ParticleGenerator
{
public:
	DefaultParticleGenerator() : ParticleGenerator::ParticleGenerator(nullptr, ParticleSystem::GeneratorType::FOG) {}
	DefaultParticleGenerator(ParticleSystem* sys, ParticleSystem::GeneratorType type) : ParticleGenerator::ParticleGenerator(sys, type) {}
	DefaultParticleGenerator(ParticleSystem* sys, ParticleSystem::SolidShape shape, Vector3 pos, ParticleSystem::GeneratorType type = ParticleSystem::GeneratorType::FOUNTAIN);
	void init() override;
	void update(double t) override;
protected:
	void generateParticle() override;

};

