#include "GaussianGenerator.h"

GaussianGenerator::GaussianGenerator(ParticleSystem* sys, ParticleSystem::SolidShape shape, Vector3 pos, ParticleSystem::GeneratorType type)
    : ParticleGenerator::ParticleGenerator(sys, type, shape, pos) {
    solid = true;
}

void GaussianGenerator::init() {

}

void GaussianGenerator::update(double t) {
	ParticleGenerator::update(t);
}

void GaussianGenerator::generateParticle() {

    Vector3 velocity = getNormalDistribution(currentData.velocityGaussian.front().first, currentData.velocityGaussian.front().second);

    Vector3 position = getNormalDistribution(currentData.positionGaussian.front().first, currentData.positionGaussian.front().second);

    Vector4 color = currentData.color.front();

    if (currentData.randomColor.front()) {
        Vector3 rgb = getUniformDistribution(0, 1);
        color = Vector4(rgb, color.w);
    }

    if (solid) {
        sys->addSolid(new RigidDynamicObject(sys->getScene(), color, generationSpawn + position,
            elapsedTime + currentData.lifeTime.front(), velocity, sphere, this, currentData.density.front(), velocity));
    }
    else {
        sys->addParticle(new Particle(color, generationSpawn + position, velocity, Vector3(0, 0, 0),
            DAMPING, elapsedTime + currentData.lifeTime.front(), this, sphere, currentData.density.front()));
    }
}