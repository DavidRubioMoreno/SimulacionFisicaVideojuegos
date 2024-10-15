#include "ParticleGenerator.h"


void ParticleGenerator::update(double t) {
	elapsedTime += t;
	if (elapsedTime > timeToNextGen) {
		generateParticle();
		timeToNextGen += generationTime;
	}
}

ParticleGenerator::~ParticleGenerator() {
	sys = nullptr;
}

void ParticleGenerator::setSpawnPoint(Vector3& v) {
	generationSpawn = v;
}