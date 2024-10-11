#include "ParticleSystem.h"
#include "GaussianGenerator.h"
#include "UniformGenerator.h"


void ParticleSystem::updateParticles(double t) {

	elapsedTime += t;

	//update particulas
	for (auto it = particles.begin(); it != particles.end();)
	{		
		if (elapsedTime > (*it)->getTime()) {
			delete *it;  // Liberamos la memoria de la partícula
			it = particles.erase(it);  // Eliminamos la partícula y obtenemos el siguiente iterador
		}
		else {
			(*it)->integrate(t);  // Si no se elimina, integramos la partícula
			++it;  // Solo incrementamos el iterador si no se eliminó
		}
	}
}

void ParticleSystem::updateGenerators(double t) {
	for (auto& gen : generators)
	{
		gen->update(t);
	}
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

void ParticleSystem::setGeneratorPosition(std::list<ParticleGenerator*>::iterator id, physx::PxVec3 position) {
	(*id)->setSpawnPoint(position);
}

std::list<ParticleGenerator*>::iterator ParticleSystem::addGenerator(GeneratorType type) {
	switch (type)
	{
	case ParticleSystem::GAUSSIAN:
		generators.push_back(new GaussianGenerator(0.1, 0.0, this));
		break;
	case ParticleSystem::UNIFORM:
		generators.push_back(new UniformGenerator(0.1, 0.0, this));
		break;
	default:
		break;
	}
	
	return --generators.end();
}


