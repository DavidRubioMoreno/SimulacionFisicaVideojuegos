#include "ParticleSystem.h"
#include "GaussianGenerator.h"
#include "UniformGenerator.h"


void ParticleSystem::updateParticles(double t) {

	//update particulas
	for (auto&p : particles)
	{
		p->integrate(t);
	}

	//Chequear si hay que eliminarlas
}

void ParticleSystem::updateGenerators(double t) {

}

ParticleSystem::~ParticleSystem() {
	for (auto& g : generators) { delete g; }
	
	generators.clear();

	for (auto& p : particles) { delete p; }
	
	particles.clear();
}

void ParticleSystem::addParticle(Particle* p) {
	particles.push_back(p);
}

void ParticleSystem::addGenerator(GeneratorType type) {
	switch (type)
	{
	case ParticleSystem::GAUSSIAN:
		generators.push_back(new GaussianGenerator());
		break;
	case ParticleSystem::UNIFORM:
		generators.push_back(new UniformGenerator());
		break;
	default:
		break;
	}
}