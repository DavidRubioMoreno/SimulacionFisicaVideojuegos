#include "ParticleSystem.h"
#include "GaussianGenerator.h"
#include "UniformGenerator.h"
#include "GravitatoryGenerator.h"
#include "TornadoGenerator.h"


void ParticleSystem::updateParticles(double t) {

	elapsedTime += t;

	//update particulas
	for (auto it = particles.begin(); it != particles.end();)
	{		
		if (elapsedTime > (*it)->getTime() || particleOutOfRange((*it)->getPos() - (*it)->getInitPos())) {
			eliminateSubscriptions((*it));
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

	for (auto& gen : forceGenerators)
	{
		gen->updateParticles(t);
	}
}

ParticleSystem::~ParticleSystem() {//limpiamos
	for (auto& g : generators) { delete g; }	
	generators.clear();

	for (auto& p : particles) { delete p; }	
	particles.clear();

	forceGenerators.clear();
}

void ParticleSystem::addParticle(Particle* p) {//guardamos puntero a la nueva particula
	//Masa por defecto
	p->setMass(0.01);

	particles.push_back(p);

	for (auto& gen : p->getGenerator()->subscriptions)
	{
		 p->addSub((*gen)->addParticle(p));//a�adimos la particula a los generadores de fuerza
	}
}

void ParticleSystem::setGeneratorPosition(std::list<ParticleGenerator*>::iterator id, physx::PxVec3 position) {
	(*id)->setSpawnPoint(position);//podemos modificar la posicion de un genrador con su iterador
}

void ParticleSystem::setGeneratorSpeed(std::list<ParticleGenerator*>::iterator id, float genSpeed)
{
	(*id)->currentData.generationSpeed[0] = genSpeed;
}

void ParticleSystem::setGeneratorParticleNumber(std::list<ParticleGenerator*>::iterator id, int particlesPerGen)
{
	(*id)->currentData.particleNumber[0] = particlesPerGen;
}

void ParticleSystem::setGeneratorVelGaussian(std::list<ParticleGenerator*>::iterator id, std::pair<float, float> distr)
{
	(*id)->currentData.velocityGaussian[0] = distr;
}

void ParticleSystem::setGeneratorVelUniform(std::list<ParticleGenerator*>::iterator id, std::pair<float, float> range)
{
	(*id)->currentData.velocityUniform[0] = range;
}

void ParticleSystem::setGeneratorPosGaussian(std::list<ParticleGenerator*>::iterator id, std::pair<float, float> distr)
{
	(*id)->currentData.positionGaussian[0] = distr;
}

void ParticleSystem::setGeneratorPosUniform(std::list<ParticleGenerator*>::iterator id, std::pair<float, float> range)
{
	(*id)->currentData.positionUniform[0] = range;
}

void ParticleSystem::setGeneratorColor(std::list<ParticleGenerator*>::iterator id, physx::PxVec4 color)
{
	(*id)->currentData.color[0] = color;
}

bool ParticleSystem::particleOutOfRange(const physx::PxVec3& position) const
{
	return  abs(position.x) > DESTROY_RANGE || abs(position.y) > DESTROY_RANGE || abs(position.z) > DESTROY_RANGE;
}

void ParticleSystem::eliminateSubscriptions(Particle* p)
{
	int i = 0;
	for (auto& gen : p->getGenerator()->subscriptions)
	{
		if (i >= p->getSubs().size())
			break;
		(*gen)->elimParticle(p->getSubs()[i]);
		i++;
	}
}

std::list<ParticleGenerator*>::iterator ParticleSystem::addGenerator(GeneratorType type) {
	switch (type)
	{
	case ParticleSystem::FOUNTAIN:
		generators.push_back(new GaussianGenerator(0, this, type));//generador de tipo gausiano
		break;
	case ParticleSystem::FOG:
		generators.push_back(new UniformGenerator(0, this, type));//generador uniforme
		break;
	case ParticleSystem::EXPLOSION:
		generators.push_back(new UniformGenerator(0, this, type));//generador uniforme
		break;
	case ParticleSystem::RAIN:
		generators.push_back(new GaussianGenerator(0, this, type));//generador de tipo gausiano
		break;
	default:
		break;
	}
	
	return --generators.end();//devolvemos un iterador al generador que hemos creado
}

std::list<ForceGenerator*>::iterator ParticleSystem::addForceGenerator(ForceGeneratorType id, physx::PxVec3 centre, physx::PxVec3 force, physx::PxVec3 volume)
{
	switch (id)
	{
	case ParticleSystem::GRAVITY:
		forceGenerators.push_back(new GravitatoryGenerator(id, centre, force, volume));
		break;
	case ParticleSystem::WIND:
		forceGenerators.push_back(new WindGenerator(id, centre, force, volume));
		break;
	case ParticleSystem::TORNADO:
		forceGenerators.push_back(new TornadoGenerator(id, centre, force, volume));
		break;
	default:
		break;
	}

	return --forceGenerators.end();
}

void ParticleSystem::applyForceGenerator(std::list<ParticleGenerator*>::iterator pGen, std::list<ForceGenerator*>::iterator fGen)
{
	(*pGen)->addForceGenerator(fGen);
}

void ParticleSystem::activateForceGenerator(std::list<ForceGenerator*>::iterator fGen, bool active)
{
	(*fGen)->activate(active);
}


