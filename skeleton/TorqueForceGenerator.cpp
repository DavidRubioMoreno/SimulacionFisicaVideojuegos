#include "TorqueForceGenerator.h"

void TorqueForceGenerator::updateParticles(double t)
{
}

void TorqueForceGenerator::updateSolids(double t)
{
	if (active) {
		for (auto& s : solidObjects)
		{
			s->addTorque(force);
		}
	}
}
