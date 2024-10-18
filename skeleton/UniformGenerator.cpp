#include "UniformGenerator.h"

void UniformGenerator::init() {

}

void UniformGenerator::update(double t) {
	ParticleGenerator::update(t);
}

void UniformGenerator::generateParticle() {
    // Usamos el tiempo actual como semilla para el generador de números aleatorios
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    // Definimos la distribución uniforme 
    std::uniform_real_distribution<float> distribution(sys->getData().velocityUniform[type].first, sys->getData().velocityUniform[type].second);  // Rango de la distribución uniforme
    std::uniform_real_distribution<float> distributionPosition(sys->getData().positionUniform[type].first, sys->getData().positionUniform[type].second);

    // Generamos velocidades aleatorias en los ejes X, Y y Z
    float vx = distribution(generator);  // Velocidad en X
    float vy = distribution(generator);  // Velocidad en Y
    float vz = distribution(generator);  // Velocidad en Z

    // Generamos posiciones aleatorias en los ejes X, Y y Z
    float px = distributionPosition(generator);  // Posicion en X
    float py = distributionPosition(generator);  // Posicion en Y
    float pz = distributionPosition(generator);  // Posicion en Z

    // Creamos un vector de velocidad aleatorio con los valores generados
    Vector3 velocity(vx, vy, vz);

    // Generamos la partícula con la velocidad aleatoria
    sys->addParticle(new Particle(sys->getData().color[type], generationSpawn + Vector3(px, py, pz), velocity, Vector3(0, GRAVITY, 0), DAMPING, elapsedTime + PARTICLE_TIME));
}

