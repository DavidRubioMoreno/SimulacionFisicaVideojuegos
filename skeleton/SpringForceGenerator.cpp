#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(ParticleSystem::ForceGeneratorType id, Vector3 centre, Vector3 f, Vector3 volume, float K, float restinglenght)
	: ForceGenerator::ForceGenerator(id, centre, f, volume), K(K), lenght(restinglenght) {}

SpringForceGenerator::~SpringForceGenerator()
{

}

void SpringForceGenerator::updateParticles(double t)
{
	if (active) {
		int i = 0;
		for (auto it = particles.begin(); it != --particles.end(); ++it)
		{
			i++;
			std::cout << (*it)->getMass() << "\n";
			auto next = it;
			next++;
			Vector3 relativePosV = (*next)->getPos() - (*it)->getPos();
			Vector3 finalForce;

			const float l = relativePosV.normalize();
			const float deltaX = l - lenght;

			// Fuerza de resorte usando la ley de Hooke
			finalForce = relativePosV * deltaX * K;

			(*it)->addForce(finalForce / (*it)->getMass(), t);
			(*next)->addForce(-finalForce / (*it)->getMass(), t);

			std::cout << "Speed: " << (*it)->getVel().x << " Accel: " << (*it)->getAccel().x << " Increase: " << (finalForce / (*it)->getMass()).x << "\n";
		}	
	}
	
}
