#include "ParticleSystem.h"
#include "GaussianGenerator.h"
#include "UniformGenerator.h"
#include "GravitatoryGenerator.h"
#include "TornadoGenerator.h"
#include "ExplosionGenerator.h"
#include "AnchoredSpringFG.h"
#include "DefaultParticleGenerator.h"
#include "BuoyancyForceGenerator.h"
#include "RigidDynamicObject.h"

ParticleSystem::ParticleSystem(physx::PxScene* scene) : gScene(scene) {}

ParticleSystem::~ParticleSystem() {//limpiamos
	for (auto& g : generators) { delete g; }
	generators.clear();

	for (auto& p : particles) { delete p; }
	particles.clear();

	for (auto& d : dynamicObjects) { delete d; }
	dynamicObjects.clear();

	for (auto& g : forceGenerators) { delete g; }
	forceGenerators.clear();
}

void ParticleSystem::update(double t)
{
	elapsedTime += t;
	//std::cout << "FPS: " << 1.0 / t << "\n";
	updateParticles(t);
	updateSolids(t);
	updateGenerators(t);
}

void ParticleSystem::updateParticles(double t) {
	for (auto it = particles.begin(); it != particles.end();)
	{		
		if (elapsedTime > (*it)->getTime() || 
			particleOutOfRange((*it)->getPos() - (*it)->getInitPos(),
			(*it)->getGenerator()->currentData.destroyRange.front())) {

			eliminateSubscriptions((*it));
			delete *it;  // Liberamos la memoria de la partícula
			it = particles.erase(it);  // Eliminamos la partícula y obtenemos el siguiente iterador			
		}
		else {
			(*it)->integrate(t);  // Si no se elimina, integramos la partícula
			++it;  // Solo incrementamos el iterador si no se eliminó
		}
	}
}

void ParticleSystem::updateSolids(double t)
{
	for (auto it = dynamicObjects.begin(); it != dynamicObjects.end();)
	{
		if (elapsedTime > (*it)->getTime() || particleOutOfRange((*it)->getPos() - (*it)->getInitPos(),
			(*it)->getGenerator()->currentData.destroyRange.front())) {
			eliminateSubscriptionsSolid((*it));
			delete* it;  
			it = dynamicObjects.erase(it); 		
			solidsInScene--;
		}
		else {
			++it;  // Solo incrementamos el iterador si no se eliminó
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
		gen->update(t);
	}
}


void ParticleSystem::addParticle(Particle* p) {//guardamos puntero a la nueva particula
	//Masa por defecto
	p->setMass(2);

	particles.push_back(p);

	for (auto& gen : p->getGenerator()->subscriptions)
	{
		 p->addSub((*gen)->addParticle(p));//añadimos la particula a los generadores de fuerza
	}
}

void ParticleSystem::addSolid(RigidDynamicObject* rObject)
{
	dynamicObjects.push_back(rObject);

	solidsInScene++;

	for (auto& gen : rObject->getGenerator()->subscriptions)
	{
		rObject->addSub((*gen)->addSolid(rObject));//añadimos el solido a los generadores de fuerza
	}
}

physx::PxScene* ParticleSystem::getScene()
{
	return gScene;
}

void ParticleSystem::setGeneratorPosition(std::list<ParticleGenerator*>::iterator id, physx::PxVec3 position) {
	(*id)->setSpawnPoint(position);//podemos modificar la posicion de un genrador con su iterador
}

void ParticleSystem::setGeneratorSpeed(std::list<ParticleGenerator*>::iterator id, float genSpeed)
{
	(*id)->currentData.generationSpeed.front() = genSpeed;
}

void ParticleSystem::setGeneratorParticleNumber(std::list<ParticleGenerator*>::iterator id, int particlesPerGen)
{
	(*id)->currentData.particleNumber.front() = particlesPerGen;
}

void ParticleSystem::setGeneratorVelGaussian(std::list<ParticleGenerator*>::iterator id, std::pair<float, float> distr)
{
	(*id)->currentData.velocityGaussian.front() = distr;
}

void ParticleSystem::setGeneratorVelUniform(std::list<ParticleGenerator*>::iterator id, std::pair<float, float> range)
{
	(*id)->currentData.velocityUniform.front() = range;
}

void ParticleSystem::setGeneratorPosGaussian(std::list<ParticleGenerator*>::iterator id, std::pair<float, float> distr)
{
	(*id)->currentData.positionGaussian.front() = distr;
}

void ParticleSystem::setGeneratorPosUniform(std::list<ParticleGenerator*>::iterator id, std::pair<float, float> range)
{
	(*id)->currentData.positionUniform.front() = range;
}

void ParticleSystem::setGeneratorColor(std::list<ParticleGenerator*>::iterator id, physx::PxVec4 color)
{
	(*id)->currentData.color.front() = color;
}

void ParticleSystem::setGeneratorRandomColor(std::list<ParticleGenerator*>::iterator id, bool random)
{
	(*id)->currentData.randomColor.front() = random;
}

void ParticleSystem::setGeneratorDestroyRange(std::list<ParticleGenerator*>::iterator id, float destroyRange)
{
	(*id)->currentData.destroyRange.front() = destroyRange;
}

void ParticleSystem::setGeneratorLifeTime(std::list<ParticleGenerator*>::iterator id, float time)
{
	(*id)->currentData.lifeTime.front() = time;
}

void ParticleSystem::setGeneratorDensity(std::list<ParticleGenerator*>::iterator id, float density)
{
	(*id)->currentData.density.front() = density;
}

void ParticleSystem::setGeneratorParticleSize(std::list<ParticleGenerator*>::iterator id, physx::PxVec3 size)
{
	(*id)->changeSize(size);
}

bool ParticleSystem::particleOutOfRange(const physx::PxVec3& position, const float& range) const
{
	return  abs(position.x) > range || abs(position.y) > range || abs(position.z) > range;
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

void ParticleSystem::eliminateSubscriptionsSolid(RigidDynamicObject* s)
{
	int i = 0;
	for (auto& gen : s->getGenerator()->subscriptions)
	{
		if (i >= s->getSubs().size())
			break;
		(*gen)->elimSolid(s->getSubs()[i]);
		i++;
	}
}

std::list<ParticleGenerator*>::iterator ParticleSystem::addGenerator(GeneratorType type) {
	switch (type)
	{
	case ParticleSystem::FOUNTAIN:
		generators.push_back(new GaussianGenerator(this, type));//generador de tipo gausiano
		break;
	case ParticleSystem::FOG:
		generators.push_back(new UniformGenerator(this, type));//generador uniforme
		break;
	case ParticleSystem::EXPLOSION:
		generators.push_back(new UniformGenerator(this, type));//generador uniforme
		break;
	case ParticleSystem::RAIN:
		generators.push_back(new GaussianGenerator(this, type));//generador de tipo gausiano
		break;
	case ParticleSystem::DEFAULT:
		generators.push_back(new DefaultParticleGenerator(this, type));//generador manual
	default:
		break;
	}
	
	return --generators.end();//devolvemos un iterador al generador que hemos creado
}

std::list<ParticleGenerator*>::iterator ParticleSystem::addSolidGenerator(DistributionType type, SolidShape shapeType, physx::PxVec3 pos)
{
	switch (type)
	{
	case ParticleSystem::UNIFORM:
		generators.push_back(new UniformGenerator(this, shapeType, pos));
		break;
	case ParticleSystem::GAUSSIAN:
		generators.push_back(new GaussianGenerator(this, shapeType, pos));
		break;
	case ParticleSystem::NONE:
		generators.push_back(new DefaultParticleGenerator(this, shapeType, pos));
		break;
	default:
		break;
	}

	return --generators.end();
}

std::list<ForceGenerator*>::iterator ParticleSystem::addForceGenerator(ForceGeneratorType id, physx::PxVec3 centre, physx::PxVec3 force, physx::PxVec3 volume, float density)
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
	case ParticleSystem::EXPLOSIVE:
		forceGenerators.push_back(new ExplosionGenerator(id, centre, force, volume));
		break;
	case ParticleSystem::BUOYANCY:
		forceGenerators.push_back(new BuoyancyForceGenerator(id, centre, force, volume, density));
		break;
	default:
		break;
	}

	return --forceGenerators.end();
}

void ParticleSystem::applyForceGenerator(std::list<ParticleGenerator*>::iterator pGen, std::list<ForceGenerator*>::iterator fGen)
{
	(*pGen)->addForceGenerator(fGen);

	for (auto& p : particles)//subscribe a las particulas de ese generador ya creadas
	{
		if ((*pGen) == p->getGenerator() && fGen == p->getGenerator()->subs().back()) {
			p->addSub((*fGen)->addParticle(p));
		}
	}

	for (auto& s : dynamicObjects)//subscribe a los solidos de ese generador ya creados
	{
		if ((*pGen) == s->getGenerator() && fGen == s->getGenerator()->subs().back()) {
			s->addSub((*fGen)->addSolid(s));
		}
	}
}

void ParticleSystem::activateForceGenerator(std::list<ForceGenerator*>::iterator fGen, bool active)
{
	(*fGen)->activate(active);
}

std::list<ParticleGenerator*>::iterator ParticleSystem::generateSpring(SpringType type, int nParticles, float K, float initialLenght, physx::PxVec3 pos)
{
	generators.push_back(new DefaultParticleGenerator(this, DEFAULT));

	switch (type)
	{
	case ParticleSystem::BASIC:
		forceGenerators.push_back(new SpringForceGenerator(SPRING, pos, Vector3(0, 0, 0), Vector3(0, 0, 0), K, initialLenght));
		break;
	case ParticleSystem::ANCHORED:
		forceGenerators.push_back(new AnchoredSpringFG(SPRING, pos, Vector3(0, 0, 0), Vector3(0, 0, 0), K, initialLenght));
		break;
	default:
		break;
	}

	auto gen = --generators.end();

	applyForceGenerator(gen, --forceGenerators.end());

	Vector3 init(pos);

	setGeneratorPosition(gen, pos);

	for (size_t i = 0; i < nParticles; i++)
	{
		init.x += initialLenght;
		(*gen)->generateParticle();
		setGeneratorPosition(gen, init);
	}

	setGeneratorPosition(gen, pos);

	return gen;
}

void ParticleSystem::generatorCreateObject(std::list<ParticleGenerator*>::iterator pGen)
{
	(*pGen)->generateParticle();
}



