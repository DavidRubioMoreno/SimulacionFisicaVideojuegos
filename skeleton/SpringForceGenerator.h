#pragma once
#include "ForceGenerator.h"

class SpringForceGenerator :public ForceGenerator
{
public:
	SpringForceGenerator(ParticleSystem::ForceGeneratorType id, Vector3 centre, Vector3 f, Vector3 volume, float K, float restinglenght);
	~SpringForceGenerator();
	inline void setK(float k) { K = k; }
	virtual void updateParticles(double t) override;
	virtual void updateSolids(double t) override;
protected:
	Vector3 getFinalForce(Vector3 relativePos);
	float K;
	float lenght;
	float forceTotal = 0.0;
};

