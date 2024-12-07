#include "UniformGenerator.h"

UniformGenerator::UniformGenerator(ParticleSystem* sys, ParticleSystem::SolidShape shape, Vector3 pos, ParticleSystem::GeneratorType type)
    : ParticleGenerator::ParticleGenerator(sys, type, shape, pos) {
    solid = true;
}

void UniformGenerator::init() {

}

void UniformGenerator::update(double t) {
	ParticleGenerator::update(t);
}

void UniformGenerator::generateParticle() {
    Vector3 velocity = getUniformDistribution(currentData.velocityUniform.front().first, currentData.velocityUniform.front().second);

    Vector3 position = getUniformDistribution(currentData.positionUniform.front().first, currentData.positionUniform.front().second);

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
        // Generamos la partícula con la velocidad aleatoria
        sys->addParticle(new Particle(color, generationSpawn + position, velocity, Vector3(0, 0, 0),
            DAMPING, elapsedTime + currentData.lifeTime.front(), this, sphere, currentData.density.front()));
    }
   
    
}

