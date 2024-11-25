#pragma once
#include "ForceGenerator.h"
class WindGenerator : public ForceGenerator
{
public:
	WindGenerator(ParticleSystem::ForceGeneratorType id, Vector3 centre, Vector3 f, Vector3 volume);
	~WindGenerator() = default;
	virtual void updateParticles(double t) override;
	virtual void updateSolids(double t) override;
protected:
	float windCoeficcient;
	float cuadraticCoeficcient;
	Vector3 areaLimit1;
	Vector3 areaLimit2;
};

