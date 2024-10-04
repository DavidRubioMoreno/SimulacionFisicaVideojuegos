#pragma once
#include "Particle.h"

extern std::vector<std::pair<float, float>> bulletData;

class Proyectil : public Particle
{
public:
	enum ProjectileType {BULLET, PROYECTILE, MORTAR};
	Proyectil(Vector3 pos, double damping, float scaleFactor, ProjectileType type);
	~Proyectil();
protected:
	void adjustMass(float scale);
	void adjustGravity(float scale);

	float scaleFactor;
	float mass;
	const float GRAVITY = -9.81;
	ProjectileType type;

	
};

