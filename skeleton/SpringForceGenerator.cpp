#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(ParticleSystem::ForceGeneratorType id, Vector3 centre, Vector3 f, Vector3 volume, float K, float restinglenght)
	: ForceGenerator::ForceGenerator(id, centre, f, volume), K(K), lenght(restinglenght) {}

SpringForceGenerator::~SpringForceGenerator()
{

}

void SpringForceGenerator::updateParticles(double t)
{
	if (active && particles.size() > 0) {

		Vector3 lastForce(0,0,0);

		for (auto it = particles.begin(); it != --particles.end(); ++it)
		{
			auto next = it;
			next++;
			Vector3 relativePosV = (*next)->getPos() - (*it)->getPos();
			// Calcula la fuerza final como magnitud * dirección
			const Vector3 finalForce = getFinalForce(relativePosV);

			(*it)->addForce(finalForce + lastForce);

			if(next == --particles.end())
			 (*next)->addForce(-finalForce);

			lastForce = -finalForce;
		}	
	}
	
}

void SpringForceGenerator::updateSolids(double t)
{
	if (active && solidObjects.size() > 0) {

		Vector3 lastForce(0, 0, 0);

		for (auto it = solidObjects.begin(); it != --solidObjects.end(); ++it)
		{
			auto next = it;
			next++;
			Vector3 relativePosV = (*next)->getPos() - (*it)->getPos();
			// Calcula la fuerza final como magnitud * dirección
			const Vector3 finalForce = getFinalForce(relativePosV);

			(*it)->addForce(finalForce + lastForce);

			if (next == --solidObjects.end())
				(*next)->addForce(-finalForce);

			lastForce = -finalForce;
		}
	}
}

Vector3 SpringForceGenerator::getFinalForce(Vector3 relativePosV)
{
	const float l = relativePosV.magnitude();   // Longitud actual sin normalizar
	const float deltaX = l - lenght; // Deformación del resorte			

	// Normalización del vector de posición relativa para dirección de la fuerza
	relativePosV.normalize();

	return relativePosV * deltaX * K;
}
