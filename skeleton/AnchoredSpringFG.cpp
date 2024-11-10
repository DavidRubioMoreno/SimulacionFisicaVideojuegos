#include "AnchoredSpringFG.h"

AnchoredSpringFG::AnchoredSpringFG(ParticleSystem::ForceGeneratorType id, Vector3 centre, Vector3 f, Vector3 volume, float K, float restinglenght)
 : SpringForceGenerator::SpringForceGenerator(id, centre, f, volume, K, restinglenght) {}

AnchoredSpringFG::~AnchoredSpringFG()
{
}

void AnchoredSpringFG::updateParticles(double t)
{
	if (particles.begin() != particles.end())
		(*particles.begin())->setAffectedByPhysics(false);
	SpringForceGenerator::updateParticles(t);
}
