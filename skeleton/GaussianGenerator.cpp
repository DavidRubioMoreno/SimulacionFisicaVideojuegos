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
    std::normal_distribution<float> distribution(0.0, 0.5);  // media, desviaci�n est�ndar

    // Generamos velocidades aleatorias siguiendo una distribuci�n normal
    float vx = distribution(generator);  // Velocidad en X
    float vy = distribution(generator);  // Velocidad en Y
    float vz = distribution(generator);  // Velocidad en Z

    // Puedes escalar las velocidades si es necesario, por ejemplo, multiplicando por un factor
    Vector3 velocity(vx * 5.0f, abs(vy * 5.0f), vz * 5.0f);  // Factor de escala de 5 para aumentar la magnitud

	sys->addParticle(new Particle(generationSpawn, velocity, Vector3(0, GRAVITY, 0), DAMPING, elapsedTime + PARTICLE_TIME));
}