#pragma once

#include <iostream>
#include <list>

class ParticleGenerator;

class Particle;

class ParticleSystem
{
public:
	enum GeneratorType { GAUSSIAN, UNIFORM };

	ParticleSystem() = default;
	~ParticleSystem();
	void updateParticles(double t);
	void updateGenerators(double t);
	void addParticle(Particle* p);
	void addGenerator(GeneratorType type);
private:
	std::list<ParticleGenerator*> generators;
	std::list<Particle*> particles;
};

