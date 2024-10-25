#include "GravitatoryGenerator.h"

void GravitatoryGenerator::updateParticles(double t)
{

	for (auto it = particles.begin(); it != particles.end();)
	{
		if ((*it) == nullptr) {
			it = particles.erase(it);  // Eliminamos la partícula y obtenemos el siguiente iterador
		}
		else {
			(*it)->addForce(force, t);  // Si no se elimina, integramos la partícula
			++it;  // Solo incrementamos el iterador si no se eliminó
		}
	}

	std::cout << particles.size() << "\n";
}
