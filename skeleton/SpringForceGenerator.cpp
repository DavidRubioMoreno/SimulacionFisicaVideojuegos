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
			const float l = relativePosV.magnitude();                        // Longitud actual sin normalizar
			const float deltaX = l - lenght;                    // Deformación del resorte			

			// Fuerza de resorte (magnitud)
			const float forceMagnitude = deltaX * K;

			// Normalización del vector de posición relativa para dirección de la fuerza
			relativePosV.normalize();

			// Calcula la fuerza final como magnitud * dirección
			const Vector3 finalForce = relativePosV * forceMagnitude;

			(*it)->addForce(finalForce + lastForce);

			if(next == --particles.end())
			 (*next)->addForce(-finalForce);

			lastForce = -finalForce;
		}	
	}
	
}
