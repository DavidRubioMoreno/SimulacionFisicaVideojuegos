#include "ParticleGenerator.h"


void ParticleGenerator::update(double t) {
	elapsedTime += t;
	if (elapsedTime > timeToNextGen) {
		generateParticle();
		timeToNextGen += generationTime;
	}
	//std::cout << "ELAPSED: " << elapsedTime
	//	<< " NEXTGEN: " << timeToNextGen << "\n";
}

ParticleGenerator::~ParticleGenerator() {
	sys = nullptr;
}