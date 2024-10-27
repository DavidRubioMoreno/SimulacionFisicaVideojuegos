#include "GaussianGenerator.h"

void GaussianGenerator::init() {

}

void GaussianGenerator::update(double t) {
	ParticleGenerator::update(t);
}

void GaussianGenerator::generateParticle() {

    // Usamos el tiempo actual como semilla para el generador de n�meros aleatorios
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    // Definimos la distribuci�n normal con media 0.0 y desviaci�n est�ndar 1.0 (modificable)
    std::normal_distribution<float> distribution(currentData.velocityGaussian[0].first, currentData.velocityGaussian[0].second);  // media, desviaci�n est�ndar
    std::normal_distribution<float> distributionP(currentData.positionGaussian[0].first, currentData.positionGaussian[0].second);

    // Generamos velocidades aleatorias siguiendo una distribuci�n normal
    float vx = distribution(generator);  // Velocidad en X
    float vy = distribution(generator);  // Velocidad en Y
    float vz = distribution(generator);  // Velocidad en Z

    // Generamos posicion aleatorias siguiendo una distribuci�n normal
    float px = distributionP(generator);  // Posicion en X
    float py = distributionP(generator);  // Posicion en Y
    float pz = distributionP(generator);  // Posicion en Z

    Vector3 velocity(vx , vy , vz );  // Factor de escala de 5 para aumentar la magnitud

	sys->addParticle(new Particle(currentData.color[0], generationSpawn + Vector3(px, py, pz), velocity, Vector3(0, 0, 0), DAMPING, elapsedTime + PARTICLE_TIME, this, sphere));
}