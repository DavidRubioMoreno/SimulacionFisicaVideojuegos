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

void GravitatoryGenerator::updateSolids(double t)
{
	if (active) {
		for (auto& s : solidObjects)
		{
			s->addAccel(force);
		}
	}
}
