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

    // Usamos el tiempo actual como semilla para el generador de números aleatorios
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    // Definimos la distribución normal 
    std::normal_distribution<float> distribution(currentData.velocityGaussian[0].first, currentData.velocityGaussian[0].second);  // media, desviación estándar
    std::normal_distribution<float> distributionP(currentData.positionGaussian[0].first, currentData.positionGaussian[0].second);

    // Generamos velocidades aleatorias siguiendo una distribución normal
    float vx = distribution(generator);  // Velocidad en X
    float vy = distribution(generator);  // Velocidad en Y
    float vz = distribution(generator);  // Velocidad en Z

    // Generamos posicion aleatorias siguiendo una distribución normal
    float px = distributionP(generator);  // Posicion en X
    float py = distributionP(generator);  // Posicion en Y
    float pz = distributionP(generator);  // Posicion en Z

    Vector3 velocity(vx , vy , vz ); 

    Vector4 color = currentData.color.front();

    if (currentData.randomColor.front()) {
        std::uniform_real_distribution<float> distributionColor(0.0, 1.0);
        color.x = distributionColor(generator);
        color.y = distributionColor(generator);
        color.z = distributionColor(generator);
    }

    if (solid) {
        sys->addSolid(new RigidDynamicObject(sys->getScene(), color, generationSpawn + Vector3(px, py, pz), elapsedTime + currentData.lifeTime.front(), velocity, sphere, this, 1000.0, velocity));
    }
    else {
        sys->addParticle(new Particle(color, generationSpawn + Vector3(px, py, pz), velocity, Vector3(0, 0, 0), DAMPING, elapsedTime + currentData.lifeTime.front(), this, sphere));
    }
}