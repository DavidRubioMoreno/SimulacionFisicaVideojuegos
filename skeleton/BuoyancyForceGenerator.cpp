#include "BuoyancyForceGenerator.h"


using namespace physx;

BuoyancyForceGenerator::BuoyancyForceGenerator(ParticleSystem::ForceGeneratorType id, Vector3 centre, Vector3 f, Vector3 volume, float d)
	: ForceGenerator::ForceGenerator(id, centre, f, volume), liquidDensity(d) 
{
	areaLimit1 = Vector3(centre.x + volume.x * 0.5, centre.y + volume.y * 0.5, centre.z + volume.z * 0.5);
	areaLimit2 = Vector3(centre.x - volume.x * 0.5, centre.y - volume.y * 0.5, centre.z - volume.z * 0.5);

	const PxBoxGeometry* geo = new PxBoxGeometry(volume);
	PxShape* shape = CreateShape(*geo);

	liquidParticle = new Particle(Vector4(0.5, 0.5, 1, 0.5), centre, Vector3(0, 0, 0), Vector3(0, 0, 0), 0, 1e6, nullptr, shape);
	liquidParticle->setAffectedByPhysics(false);

	shape->release();
}

BuoyancyForceGenerator::~BuoyancyForceGenerator()
{
	delete liquidParticle;
	liquidParticle = nullptr;
}

void BuoyancyForceGenerator::updateParticles(double t)
{
	if (active) {

		for (auto& p : particles)
		{
			const Vector3 pos = p->getPos();
			if (pos.x < areaLimit1.x && pos.x > areaLimit2.x && pos.z < areaLimit1.z && pos.z > areaLimit2.z) {
				const float h = pos.y;
				const float h0 = liquidParticle->getPos().y + volume.y / 2;

				Vector3 finalForce(0, 0, 0);
				float immersed = 0.0;

				const float height = 2.0;
				const float volume = pow(height, 3);

				if (h - h0 > height * 0.5) {
					immersed = 0.0;
				}
				else if (h0 - h > height * 0.5) {
					immersed = 1.0;
				}
				else {
					immersed = (h0 - h) / height + 0.5;
				}

				finalForce.y = liquidDensity * volume * immersed * 9.8;

				p->addForce(finalForce);
			}
		}

		//std::cout << particles.size() << "\n";
	}
}
