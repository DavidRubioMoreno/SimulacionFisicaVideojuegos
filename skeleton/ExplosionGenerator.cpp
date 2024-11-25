#include "ExplosionGenerator.h"

ExplosionGenerator::ExplosionGenerator(ParticleSystem::ForceGeneratorType id, Vector3 centre, Vector3 f, Vector3 volume) 
	: ForceGenerator::ForceGenerator(id, centre, f, volume), K(f.magnitude()), elapsedTime(0.0), R(volume.magnitude()) {}

void ExplosionGenerator::updateParticles(double t)
{
	elapsedTime += t;

	if (elapsedTime < DURATION) {
		Vector3 finalForce;
		Vector3 particlePos;

		for (auto& p : particles)
		{
			particlePos = p->getPos();
			float r = (centre - particlePos).magnitude();
			if (r < R) {
				finalForce = (K / (r * r)) * (particlePos - centre) * pow(2.711828, t / elapsedTime);
				p->addForce(finalForce);
			}
		}
	}	
	
}

void ExplosionGenerator::updateSolids(double t)
{

	if (elapsedTime < DURATION) {
		Vector3 finalForce;
		Vector3 solidPos;

		for (auto& p : particles)
		{
			solidPos = p->getPos();
			float r = (centre - solidPos).magnitude();
			if (r < R) {
				finalForce = (K / (r * r)) * (solidPos - centre) * pow(2.711828, t / elapsedTime);
				p->addForce(finalForce);
			}
		}
	}
}
