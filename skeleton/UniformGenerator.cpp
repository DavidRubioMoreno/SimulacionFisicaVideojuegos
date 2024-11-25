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
    // Usamos el tiempo actual como semilla para el generador de n�meros aleatorios
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    // Definimos la distribuci�n uniforme 
    std::uniform_real_distribution<float> distribution(currentData.velocityUniform.front().first, currentData.velocityUniform.front().second);  // Rango de la distribuci�n uniforme
    std::uniform_real_distribution<float> distributionPosition(currentData.positionUniform.front().first, currentData.positionUniform.front().second);

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

    if (solid) {
        sys->addSolid(new RigidDynamicObject(sys->getScene(), currentData.color.front(), generationSpawn + Vector3(px, py, pz), elapsedTime + SOLIDTIME, velocity, sphere, this));
    }
    else {
        // Generamos la part�cula con la velocidad aleatoria
        sys->addParticle(new Particle(currentData.color.front(), generationSpawn + Vector3(px, py, pz), velocity, Vector3(0, 0, 0), DAMPING, elapsedTime + PARTICLE_TIME, this, sphere));
    }
   
    
}

