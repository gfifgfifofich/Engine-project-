#pragma once

inline ParticleEmiter EngineSmoke;
inline ParticleEmiter bulletFlightPm;
inline ParticleEmiter bulletColisionPm;
inline ParticleEmiter CollisionSparks;
inline ParticleEmiter CollisionSmoke;
inline ParticleEmiter GunRoundPE;
inline ParticleEmiter GunShotPE;
inline ParticleEmiter DebrieParticles;
inline ParticleEmiter Smoke;
inline ParticleEmiter LaserPm;
inline ParticleEmiter LaserShotPm;
inline ParticleEmiter Sparks;
inline ParticleEmiter ExplodionPE;
inline unsigned int noize;

inline std::vector<ParticleEmiter*> emiters;


void SetupEnginePE();
void SetupSmokePE();
void SetupSparksPE();
void SetupBulletPE();
void SetupLaserPE();
void SetupGunPE();
void SetupGunRoundPE();
void SetupCollisionSmokePE();
void SetupCollisionSparksPE();
void SetupExplodionPE();
void SetupDebriePE();

void SetupPEs();
void clearParticleMaterials();

void AddSphereOfInfluence(glm::vec2 position, float r, glm::vec2 velocity, bool attractive, float attractiveStrehgth);
void ProcessPE(float dt);
