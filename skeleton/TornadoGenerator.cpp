#include "TornadoGenerator.h"

TornadoGenerator::TornadoGenerator(ParticleSystem::ForceGeneratorType id, Vector3 centre, Vector3 f, Vector3 volume)
	: WindGenerator::WindGenerator(id, centre, f, volume), K(f.magnitude()) {}

void TornadoGenerator::updateParticles(double t) {
	if (active) {		
		for (auto& p : particles)
		{
			Vector3 pos = p->getPos();
			if (pos.x < areaLimit1.x && pos.x > areaLimit2.x && pos.y < areaLimit1.y &&
				pos.y > areaLimit2.y && pos.z < areaLimit1.z && pos.z > areaLimit2.z) {
				p->addForce(getFinalforce(pos));
			}
		}
	}
}

void TornadoGenerator::updateSolids(double t)
{
	if (active) {
		for (auto& s : solidObjects)
		{
			Vector3 pos = s->getPos();
			if (pos.x < areaLimit1.x && pos.x > areaLimit2.x && pos.y < areaLimit1.y &&
				pos.y > areaLimit2.y && pos.z < areaLimit1.z && pos.z > areaLimit2.z) {
				s->addForce(getFinalforce(pos));
			}
		}
	}
}

Vector3 TornadoGenerator::getFinalforce(const Vector3& pos)
{
	return Vector3(-K * (pos.z - centre.z), K * (50 - (pos.y - centre.y)), K * (pos.x - centre.x));
}
