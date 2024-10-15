#include "ParticleSystem.h"
#include "GaussianGenerator.h"
#include "UniformGenerator.h"


void ParticleSystem::updateParticles(double t) {

	elapsedTime += t;

	//update particulas
	for (auto it = particles.begin(); it != particles.end();)
	{		
		if (elapsedTime > (*it)->getTime() || particleOutOfRange((*it)->getPos())) {
			delete *it;  // Liberamos la memoria de la part�cula
			it = particles.erase(it);  // Eliminamos la part�cula y obtenemos el siguiente iterador
		}
		else {
			(*it)->integrate(t);  // Si no se elimina, integramos la part�cula
			++it;  // Solo incrementamos el iterador si no se elimin�
		}
	}
}

void ParticleSystem::updateGenerators(double t) {
	for (auto& gen : generators)
	{
		gen->update(t); //update generadores
	}
}

ParticleSystem::~ParticleSystem() {//limpiamos
	for (auto& g : generators) { delete g; }	
	generators.clear();

	for (auto& p : particles) { delete p; }	
	particles.clear();
}

void ParticleSystem::addParticle(Particle* p) {//guardamos puntero a la nueva particula
	particles.push_back(p);
}

void ParticleSystem::setGeneratorPosition(std::list<ParticleGenerator*>::iterator id, physx::PxVec3 position) {
	(*id)->setSpawnPoint(position);//podemos modificar la posicion de un genrador con su iterador
}

bool ParticleSystem::particleOutOfRange(const physx::PxVec3& position) const
{
	return  abs(position.x) > DESTROY_RANGE || abs(position.y) > DESTROY_RANGE || abs(position.z) > DESTROY_RANGE;
}

std::list<ParticleGenerator*>::iterator ParticleSystem::addGenerator(GeneratorType type) {
	switch (type)
	{
	case ParticleSystem::GAUSSIAN:
		generators.push_back(new GaussianGenerator(0.01, 0.0, this));//generador de tipo gausiano
		break;
	case ParticleSystem::UNIFORM:
		generators.push_back(new UniformGenerator(0.1, 0.0, this));//generador uniforme
		break;
	default:
		break;
	}
	
	return --generators.end();//devolvemos un iterador al generador que hemos creado
}


