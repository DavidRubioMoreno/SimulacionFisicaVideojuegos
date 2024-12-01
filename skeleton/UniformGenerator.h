#pragma once

#include "ParticleGenerator.h"

class UniformGenerator : public ParticleGenerator
{
public:
	UniformGenerator() : ParticleGenerator::ParticleGenerator(nullptr, ParticleSystem::GeneratorType::FOUNTAIN) {}
	UniformGenerator(ParticleSystem* sys, ParticleSystem::GeneratorType type) : ParticleGenerator::ParticleGenerator(sys, type) {}
	UniformGenerator(ParticleSystem* sys, ParticleSystem::SolidShape shape, Vector3 pos, ParticleSystem::GeneratorType type = ParticleSystem::GeneratorType::FOG);
		
	void init();
	void update(double t) override;
protected:
	void generateParticle() override;
	
};

