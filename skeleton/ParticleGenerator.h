#pragma once

#include "Particle.h"
#include "ParticleSystem.h"

class ParticleGenerator
{	
public:
	ParticleGenerator(float genTime, double t, ParticleSystem* sys) : generationTime(genTime), elapsedTime(t), timeToNextGen(genTime + t), sys(sys) {}
	virtual ~ParticleGenerator();
	virtual void init() = 0;	
	virtual void update(double t);
protected:
	virtual void generateParticle() = 0;
	double generationTime;
	float timeToNextGen;
	float elapsedTime;
	const float PARTICLE_TIME = 5.0;
	ParticleSystem* sys = nullptr;
};

