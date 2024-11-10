#include "GravitatoryGenerator.h"

void GravitatoryGenerator::updateParticles(double t)
{
	if (active) {
		for (auto& p : particles)
		{
			p->addAccel(force);
		}
		//std::cout << particles.size() << "\n";
	}	
}
