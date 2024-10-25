#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

class ParticleGenerator;

class Particle
{
public:
	Particle(Vector4 color, Vector3 pos, Vector3 vel, Vector3 a, double damping, float dTime);
	Particle(Vector4 color, Vector3 pos, Vector3 vel, Vector3 a, double damping, float dTime, ParticleGenerator* gen);
	~Particle();
	void integrate(double t);
	float getTime() const { return destroyTime; }
	Vector3 getPos() const { return renderItem->transform->p; }
	Vector3 getInitPos() const { return initPosition; }
	void setMass(float mass);
	void addMass(float mass);
	void addForce(Vector3 force, double t);
	float getMass() const { return mass; }
	ParticleGenerator* getGenerator() { return generator; }

protected:
	Vector3 vel;
	Vector3 acc;
	Vector3 initPosition;
	float mass;
	double damping;
	float destroyTime;
	physx::PxTransform* pose;
	RenderItem* renderItem;
	ParticleGenerator* generator = nullptr;
};

