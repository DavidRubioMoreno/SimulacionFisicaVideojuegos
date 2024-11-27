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
    // Usamos el tiempo actual como semilla para el generador de números aleatorios
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    // Definimos la distribución uniforme 
    std::uniform_real_distribution<float> distribution(currentData.velocityUniform.front().first, currentData.velocityUniform.front().second);  // Rango de la distribución uniforme
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

    Vector4 color = currentData.color.front();

    if (currentData.randomColor.front()) {
        std::uniform_real_distribution<float> distributionColor(0.0, 1.0);
        color.x = distributionColor(generator);
        color.y = distributionColor(generator);
        color.z = distributionColor(generator);
    }

    if (solid) {
        sys->addSolid(new RigidDynamicObject(sys->getScene(), color, generationSpawn + Vector3(px, py, pz), elapsedTime + SOLIDTIME, velocity, sphere, this, 1000.0, velocity));
    }
    else {
        // Generamos la partícula con la velocidad aleatoria
        sys->addParticle(new Particle(color, generationSpawn + Vector3(px, py, pz), velocity, Vector3(0, 0, 0), DAMPING, elapsedTime + PARTICLE_TIME, this, sphere));
    }
   
    
}

