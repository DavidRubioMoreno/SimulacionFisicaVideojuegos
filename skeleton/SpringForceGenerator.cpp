#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(ParticleSystem::ForceGeneratorType id, Vector3 centre, Vector3 f, Vector3 volume, float K, float restinglenght)
	: ForceGenerator::ForceGenerator(id, centre, f, volume), K(K), lenght(restinglenght) {}

SpringForceGenerator::~SpringForceGenerator()
{

}

void SpringForceGenerator::updateParticles(double t)
{
	if (active) {
		for (auto it = particles.begin(); it != --particles.end(); ++it)
		{
			auto next = ++it;
			Vector3 relativePosV = (*next)->getPos() - (*it)->getPos();
			Vector3 finalForce;

			const float l = relativePosV.normalize();
			const float deltaX = l - lenght;

			finalForce = relativePosV * deltaX * K;

			(*it)->addForce(finalForce, t);
			(*next)->addForce(-finalForce, t);
		}	
	}
	
}
