#include "WindGenerator.h"

WindGenerator::WindGenerator(ParticleSystem::ForceGeneratorType id, Vector3 centre, Vector3 f, Vector3 volume) 
	: ForceGenerator::ForceGenerator(id, centre, f, volume), windCoeficcient(0.001), cuadraticCoeficcient(0)
{
	areaLimit1 = Vector3(centre.x + volume.x * 0.5, centre.y + volume.y * 0.5, centre.z + volume.z * 0.5);
	areaLimit2 = Vector3(centre.x - volume.x * 0.5, centre.y - volume.y * 0.5, centre.z - volume.z * 0.5);
}

void WindGenerator::updateParticles(double t)
{
	if (active) {
		Vector3 finalForce;
		for (auto& p : particles)
		{
			Vector3 pos = p->getPos();
			if (pos.x < areaLimit1.x && pos.x > areaLimit2.x && pos.y < areaLimit1.y && pos.y > areaLimit2.y && pos.z < areaLimit1.z && pos.z > areaLimit2.z) {
				finalForce = (windCoeficcient / p->getMass()) * (force - p->getVel());
				p->addForce(finalForce, t);
			}
		}
	}
}
