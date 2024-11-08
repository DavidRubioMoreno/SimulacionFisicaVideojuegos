#pragma once
#include "ForceGenerator.h"

class SpringForceGenerator :public ForceGenerator
{
public:
	SpringForceGenerator(ParticleSystem::ForceGeneratorType id, Vector3 centre, Vector3 f, Vector3 volume, float K, float restinglenght);
	~SpringForceGenerator();
	inline void setK(float k) { K = k; }
	virtual void updateParticles(double t) override;
protected:
	float K;
	float lenght;
};

