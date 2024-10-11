#include "GaussianGenerator.h"

void GaussianGenerator::init() {

}

void GaussianGenerator::update(double t) {
	ParticleGenerator::update(t);
}

void GaussianGenerator::generateParticle() {
	sys->addParticle(new Particle(Vector3(0, 0, 0), Vector3(0, 5, 0), Vector3(2, 0, 0), 0.00001, elapsedTime + PARTICLE_TIME));
}