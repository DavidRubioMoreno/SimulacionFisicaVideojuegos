#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <PxPhysicsAPI.h>

constexpr float GRAVITY = -9.81;
constexpr double DAMPING = 0.000001;
constexpr float DESTROY_RANGE = 50;

class ParticleGenerator;

class Particle;

struct GeneratorInfo {
	 std::vector<float> generationSpeed = { 0.05f, 0.01f, 0.005f, 0.01f };
	 std::vector<std::pair<float, float>> velocityGaussian = { {0.0, 1.0}, {0,0}, {0,0}, {0.0, 2.0} };
	 std::vector<std::pair<float, float>> velocityUniform = { {0,0}, {-10,10}, {-40,40}, {0,0} };
	 std::vector<std::pair<float, float>> positionGaussian = { {0,0.01}, {0,0}, {0,0} , {0.0, 10.0}};
	 std::vector<std::pair<float, float>> positionUniform = { {0,0}, {-50,50}, {0,0} , {0,0} };
	 std::vector<physx::PxVec4>color = { {0, 0, 1, 0.8} , {0.5, 0.5, 0.5, 1}, {1, 0.3, 0.3, 1} , {0.1, 0.1, 0.8, 1} };
};

class ParticleSystem
{
public:
	enum GeneratorType { FOUNTAIN, FOG, EXPLOSION, RAIN };

	ParticleSystem() = default;
	~ParticleSystem();
	void updateParticles(double t);
	void updateGenerators(double t);
	void addParticle(Particle* p);
	GeneratorInfo getData() const { return data; }
	std::list<ParticleGenerator*>::iterator addGenerator(GeneratorType type);
	void setGeneratorPosition(std::list<ParticleGenerator*>::iterator id, physx::PxVec3 position);
	void setGenSpeed(GeneratorType type, float genSpeed);
	void setVelGaussian(GeneratorType type, std::pair<float, float> distr);
	void setVelUniform(GeneratorType type, std::pair<float, float> range);
	void setPosGaussian(GeneratorType type, std::pair<float, float> distr);
	void setPosUniform(GeneratorType type, std::pair<float, float> range);
	void setColor(GeneratorType type, physx::PxVec4 color);
private:
	bool particleOutOfRange(const physx::PxVec3& position) const;
	std::list<ParticleGenerator*> generators;
	std::list<Particle*> particles;
	float elapsedTime = 0;
	GeneratorInfo data;
};

