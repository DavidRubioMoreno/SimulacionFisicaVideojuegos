#pragma once
#include "SpringForceGenerator.h"
class AnchoredSpringFG : public SpringForceGenerator
{
public:
	AnchoredSpringFG(ParticleSystem::ForceGeneratorType id, Vector3 centre, Vector3 f, Vector3 volume, float K, float restinglenght);
	~AnchoredSpringFG();
	virtual void updateParticles(double t) override;
	virtual void updateSolids(double t) override;
};

