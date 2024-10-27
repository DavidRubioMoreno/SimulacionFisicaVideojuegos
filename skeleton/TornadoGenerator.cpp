#include "TornadoGenerator.h"

TornadoGenerator::TornadoGenerator(ParticleSystem::ForceGeneratorType id, Vector3 centre, Vector3 f, Vector3 volume)
	: WindGenerator::WindGenerator(id, centre, f, volume), K(f.magnitude()) {}

void TornadoGenerator::updateParticles(double t) {
	if (active) {
		Vector3 tornadoVelocity;
		for (auto& p : particles)
		{
			Vector3 pos = p->getPos();
			if (pos.x < areaLimit1.x && pos.x > areaLimit2.x && pos.y < areaLimit1.y && pos.y > areaLimit2.y && pos.z < areaLimit1.z && pos.z > areaLimit2.z) {
				/*tornadoVelocity.x = pos.x - centre.x;
				tornadoVelocity.y = pos.y - centre.y;
				tornadoVelocity.z = volume.z / 2 - (pos.z - centre.z);*/
				tornadoVelocity.x = -K * (pos.z - centre.z);                 // (x - x_c)
				tornadoVelocity.y = K * (50 - (pos.y - centre.y));                // -(y - y_c)
				tornadoVelocity.z = K * (pos.x - centre.x);        // -(z - z_c) / 50
				p->addForce(tornadoVelocity, t);
			}
		}
	}
}