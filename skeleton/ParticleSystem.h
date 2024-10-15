#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <PxPhysicsAPI.h>

constexpr float GRAVITY = -9.81;
constexpr double DAMPING = 0.000001;
constexpr float DESTROY_RANGE = 1000;

class ParticleGenerator;

class Particle;

struct GeneratorInfo {
	const std::vector<float> generationSpeed = { 0.05f, 0.01f, 0.005f };
	const std::vector<std::pair<float, float>> gaussian = { {0.0, 1.0}, {0,0}, {0,0} };
	const std::vector<std::pair<float, float>> uniform = { {0,0}, {-10,10}, {-40,40} };
	const std::vector<std::pair<float, float>> position = { {0,0}, {-50,50}, {0,0} };
	const std::vector<physx::PxVec4>color = { {0, 0, 1, 0.8} , {0.5, 0.5, 0.5, 1}, {1, 0.3, 0.3, 1} };
};

class ParticleSystem
{
public:
	enum GeneratorType { FOUNTAIN, FOG, EXPLOSION };

	ParticleSystem() = default;
	~ParticleSystem();
	void updateParticles(double t);
	void updateGenerators(double t);
	void addParticle(Particle* p);
	GeneratorInfo getData() const { return data; }
	std::list<ParticleGenerator*>::iterator addGenerator(GeneratorType type);
	void setGeneratorPosition(std::list<ParticleGenerator*>::iterator id, physx::PxVec3 position);
private:
	bool particleOutOfRange(const physx::PxVec3& position) const;
	std::list<ParticleGenerator*> generators;
	std::list<Particle*> particles;
	float elapsedTime = 0;
	GeneratorInfo data;
};

