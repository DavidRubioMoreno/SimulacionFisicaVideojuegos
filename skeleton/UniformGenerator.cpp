#include "UniformGenerator.h"

void UniformGenerator::init() {

}

void UniformGenerator::update(double t) {
	ParticleGenerator::update(t);
}

void UniformGenerator::generateParticle() {
	sys->addParticle(new Particle(Vector3(0, 0, 0), Vector3(0, 5, 0), Vector3(0, 0, 2), 0.00001, elapsedTime + PARTICLE_TIME));
}

