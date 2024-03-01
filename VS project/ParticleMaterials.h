#pragma once

void SetupEnginePE()
{

	EngineSmoke.textures.push_back(noize);
	EngineSmoke.Type = "TEXTUREDLINE";
	EngineSmoke.VelocityRandomness = { -500,500,-200,200 };
	EngineSmoke.VelocityRandomness *= 0.025f;
	EngineSmoke.StartColor = { 500.0f,100.0f,1.0f,1.0f };
	EngineSmoke.EndColor = { 500.0f,100.0f,1.0f,0.0f };
	EngineSmoke.OrbitalVelocityRandomness = 1.5f;
	EngineSmoke.lighted = true;
	EngineSmoke.RotationRandomness = 10.0f;
	EngineSmoke.InitialRotation = 10.0f;
	EngineSmoke.lifetimeRandomness = 0.2f;
	EngineSmoke.lifetime = 0.2f;
	EngineSmoke.VelocityDamper = 0.1f * 60;
	EngineSmoke.Z_Index = 100;
	EngineSmoke.StartSize = { 10 * 0.025f,2.5 };
	EngineSmoke.EndSize = { 20.0f * 0.025f,2.5f };

	EngineSmoke.Additive = true;
}
void SetupSmokePE()
{

	Smoke.textures.push_back(noize);
	Smoke.Type = "TEXTURED";
	Smoke.VelocityRandomness = { -700,700,-700,700 };
	Smoke.VelocityRandomness *= 0.025f;
	Smoke.StartColor = { 3.0f,3.0f,3.0f,1.0f };
	Smoke.EndColor = { 1.0f,1.0f,1.0f,0.0f };
	Smoke.OrbitalVelocityRandomness = 1.5f;
	Smoke.lighted = true;
	Smoke.RotationRandomness = 10.0f;
	Smoke.InitialRotation = 10.0f;
	Smoke.lifetimeRandomness = 1.0f;
	Smoke.lifetime = 0.5f;
	Smoke.Z_Index = 100;
	Smoke.VelocityDamper = 0.2f * 60;
	Smoke.StartSize = { 10.0f,10.0f };
	Smoke.StartSize *= 0.025f;
	Smoke.EndSize = { 50.0f,50.f };
	Smoke.EndSize *= 0.025f;
	Smoke.Additive = true;
}
void SetupSparksPE()
{

	Sparks.Type = "LINE";
	Sparks.VelocityRandomness = { -1500,1500,-1500,1500 };
	Sparks.VelocityRandomness *= 0.025f;
	Sparks.acceleration = { 0.0f,0.0f };
	Sparks.StartColor = { 30.0f,10.0f,0.0f,1.0f };
	Sparks.EndColor = { 1.0f,1.0f,1.0f,0.0f };
	Sparks.lighted = true;
	Sparks.lifetimeRandomness = 0.2f;
	Sparks.lifetime = 0.5f;
	Sparks.VelocityDamper = 0.0f;
	Sparks.Z_Index = 1000;
	
	Sparks.StartSize = { 2 * 0.025f ,2 };
	Sparks.EndSize = { 2 * 0.025f ,2};
}
void SetupBulletPE()
{
	bulletFlightPm.Type = "LINE";
	bulletFlightPm.VelocityRandomness = { -50,50,-50,50 };
	bulletFlightPm.VelocityRandomness *= 0.025f;
	bulletFlightPm.StartColor = { 300.0f,20.0f,4.0f,1.0f };
	bulletFlightPm.EndColor = { 100.0f,10.0f,4.0f,0.0f };
	bulletFlightPm.OrbitalVelocityRandomness = 1.5f;
	bulletFlightPm.lighted = true;
	bulletFlightPm.RotationRandomness = 10.0f;
	bulletFlightPm.InitialRotation = 10.0f;
	bulletFlightPm.lifetimeRandomness = 0.2f;
	bulletFlightPm.lifetime = 0.4f;
	bulletFlightPm.VelocityDamper = 0.1f * 60;

	bulletFlightPm.StartSize = { 2 * 0.025f,1 };
	bulletFlightPm.EndSize = { 0,1 };
	bulletFlightPm.Z_Index = 0;

	bulletColisionPm.textures.push_back(noize);
	bulletColisionPm.Type = "TEXTURED";
	bulletColisionPm.VelocityRandomness = { -250,250,-250,250 };
	bulletColisionPm.VelocityRandomness *= 0.025f;
	bulletColisionPm.acceleration = { 0, 0 };
	bulletColisionPm.StartColor = { 10.0f,10.0f,10.0f,1.0f };
	bulletColisionPm.EndColor = { 1.0f,1.0f,1.0f,0.0f };
	bulletColisionPm.OrbitalVelocityRandomness = 1.5f;
	bulletColisionPm.lighted = true;
	bulletColisionPm.RotationRandomness = 10.0f;
	bulletColisionPm.InitialRotation = 10.0f;
	bulletColisionPm.lifetimeRandomness = 0.5f;
	bulletColisionPm.lifetime = 1.0f;
	bulletColisionPm.VelocityDamper = 0.1f * 60;

	bulletColisionPm.StartSize = { 10,10 };
	bulletColisionPm.StartSize *= 0.025f;
	bulletColisionPm.EndSize = { 50,50 };
	bulletColisionPm.EndSize *= 0.025f;
	bulletColisionPm.Z_Index = 0;


}
void SetupLaserPE()
{
	LaserPm.textures.push_back(noize);
	LaserPm.Type = "TEXTURED";
	LaserPm.VelocityRandomness = { -150,150,-150,150 };
	LaserPm.VelocityRandomness *= 0.025f;
	LaserPm.acceleration = { 0,150 };
	LaserPm.acceleration *= 0.025f;
	LaserPm.StartColor = { 100.0f,100.0f,100.0f,1.0f };
	LaserPm.EndColor = { 1.0f,1.0f,1.0f,0.0f };
	LaserPm.OrbitalVelocityRandomness = 1.5f;
	LaserPm.lighted = true;
	LaserPm.RotationRandomness = 10.0f;
	LaserPm.InitialRotation = 10.0f;
	LaserPm.lifetimeRandomness = 0.0f;
	LaserPm.lifetime = 1.0f;
	LaserPm.VelocityDamper = 0.1f * 60;

	LaserPm.StartSize = { 10,10 };
	LaserPm.StartSize *= 0.025f;
	LaserPm.EndSize = { 50,50 };
	LaserPm.EndSize *= 0.025f;
	LaserPm.Z_Index = 0;

}
void SetupGunPE()
{
	GunShotPE.textures.push_back(noize);
	GunShotPE.Type = "TEXTURED";
	GunShotPE.VelocityRandomness = { -25.0,25.0,-25.0,25.0 };
	GunShotPE.VelocityRandomness *= 0.025f;
	GunShotPE.acceleration = { 0, 0 };
	GunShotPE.StartColor = { 3.0f,3.0f,3.0f,1.0f };
	GunShotPE.EndColor = { 1.0f,1.0f,1.0f,0.0f };
	GunShotPE.OrbitalVelocityRandomness = 1.5f;
	GunShotPE.lighted = true;
	GunShotPE.RotationRandomness = 10.0f;
	GunShotPE.InitialRotation = 10.0f;
	GunShotPE.lifetimeRandomness = 0.5f;
	GunShotPE.lifetime = 1.0f;
	GunShotPE.VelocityDamper = 0.2f * 60;
	GunShotPE.Additive = true;
	GunShotPE.StartSize = { 10,10 };
	GunShotPE.StartSize *= 0.025f;
	GunShotPE.EndSize = { 35,35 };
	GunShotPE.EndSize *= 0.025f;
	GunShotPE.Z_Index = 100;
}
void SetupCollisionSmokePE()
{
	CollisionSmoke.textures.push_back(noize);
	CollisionSmoke.Type = "TEXTURED";
	CollisionSmoke.VelocityRandomness = { -70,70,-70,70 };
	CollisionSmoke.VelocityRandomness *= 0.025f;
	CollisionSmoke.StartColor = { 3.0f,3.0f,3.0f,1.0f };
	CollisionSmoke.EndColor = { 1.0f,1.0f,1.0f,0.0f };
	CollisionSmoke.OrbitalVelocityRandomness = 1.5f;
	CollisionSmoke.lighted = true;
	CollisionSmoke.RotationRandomness = 10.0f;
	CollisionSmoke.InitialRotation = 10.0f;
	CollisionSmoke.lifetimeRandomness = 1.0f;
	CollisionSmoke.lifetime = 1.5f;
	CollisionSmoke.Z_Index = 1000;
	CollisionSmoke.VelocityDamper = 0.2f * 60;
	CollisionSmoke.StartSize = { 20.0f,20.0f };
	CollisionSmoke.StartSize *= 0.025f;
	CollisionSmoke.EndSize = { 150.0f,150.f };
	CollisionSmoke.EndSize *= 0.025f;
	CollisionSmoke.Additive = true;
}
void SetupCollisionSparksPE()
{

	CollisionSparks.Type = "LINE";
	CollisionSparks.VelocityRandomness = { -150,150,-150,150 };
	CollisionSparks.VelocityRandomness *= 0.025f;
	CollisionSparks.acceleration = { 0.0f,0.0f };
	CollisionSparks.StartColor = { 30.0f,10.0f,0.0f,1.0f };
	CollisionSparks.EndColor = { 1.0f,1.0f,1.0f,0.0f };
	CollisionSparks.lighted = true;
	CollisionSparks.lifetimeRandomness = 0.2f;
	CollisionSparks.lifetime = 0.5f;
	CollisionSparks.VelocityDamper = 0.0f;
	CollisionSparks.Z_Index = 1000;

	CollisionSparks.StartSize = { 2 * 0.025f,2 };
	CollisionSparks.EndSize = { 2 * 0.025f,2 };
}
void SetupExplodionPE()
{

	ExplodionPE.textures.push_back(noize);
	ExplodionPE.Type = "TEXTURED";
	ExplodionPE.VelocityRandomness = { -150,150,-150,150 };
	ExplodionPE.VelocityRandomness *= 0.025f;
	ExplodionPE.acceleration = { 0.0f,0.0f };
	ExplodionPE.StartColor = { 1.0f,1.0f,1.0f,0.5f };
	ExplodionPE.EndColor = { 1.0f,1.0f,1.0f,0.0f };
	ExplodionPE.lighted = true;
	//ExplodionPE.NormalMap = BallNormalMapTexture;
	//ExplodionPE.DrawToNormalMap = true;
	ExplodionPE.lifetimeRandomness = 0.3f;
	ExplodionPE.lifetime = 3.5f;
	ExplodionPE.Z_Index = 100;
	ExplodionPE.Additive = true;
	ExplodionPE.VelocityDamper = 4.0f;

	ExplodionPE.StartSize = { 15 ,15 };
	ExplodionPE.EndSize = { 25 ,25 };
}
void SetupPEs()
{
	SetupLaserPE();
	SetupEnginePE();
	SetupSmokePE();
	SetupSparksPE();
	SetupBulletPE();
	SetupGunPE();
	SetupCollisionSparksPE();
	SetupCollisionSmokePE();
	SetupExplodionPE();


	EngineSmoke.influenced = true;
	Sparks.influenced = true;
	bulletFlightPm.influenced = true;
	bulletColisionPm.influenced = true;
	LaserPm.influenced = true;
	Smoke.influenced = true;
	GunShotPE.influenced = true;
	CollisionSparks.influenced = true;
	CollisionSmoke.influenced = true;
	ExplodionPE.influenced = true;
}

void AddSphereOfInfluence(glm::vec2 position, float r, glm::vec2 velocity, bool attractive, float attractiveStrehgth)
{
	EngineSmoke.AddSpheresOfInfluence(position, r, velocity, attractive, attractiveStrehgth);
	Sparks.AddSpheresOfInfluence(position, r, velocity, attractive, attractiveStrehgth);
	bulletFlightPm.AddSpheresOfInfluence(position, r, velocity, attractive, attractiveStrehgth);
	bulletColisionPm.AddSpheresOfInfluence(position, r, velocity, attractive, attractiveStrehgth);
	LaserPm.AddSpheresOfInfluence(position, r, velocity, attractive, attractiveStrehgth);
	Smoke.AddSpheresOfInfluence(position, r, velocity, attractive, attractiveStrehgth);
	GunShotPE.AddSpheresOfInfluence(position, r, velocity, attractive, attractiveStrehgth);
	CollisionSparks.AddSpheresOfInfluence(position, r, velocity, attractive, attractiveStrehgth);
	CollisionSmoke.AddSpheresOfInfluence(position, r, velocity, attractive, attractiveStrehgth);
	ExplodionPE.AddSpheresOfInfluence(position, r,velocity, attractive, attractiveStrehgth);

}
void ProcessPE(float dt)
{
	EngineSmoke.Process(dt);
	Sparks.Process(dt);
	bulletFlightPm.Process(dt);
	bulletColisionPm.Process(dt);
	LaserPm.Process(dt);
	Smoke.Process(dt);
	GunShotPE.Process(dt);
	CollisionSparks.Process(dt);
	CollisionSmoke.Process(dt);
	ExplodionPE.Process(dt);

	EngineSmoke.SpheresOfInfluence.clear();
	Sparks.SpheresOfInfluence.clear();
	bulletFlightPm.SpheresOfInfluence.clear();
	bulletColisionPm.SpheresOfInfluence.clear();
	LaserPm.SpheresOfInfluence.clear();
	Smoke.SpheresOfInfluence.clear();
	GunShotPE.SpheresOfInfluence.clear();
	CollisionSparks.SpheresOfInfluence.clear();
	CollisionSmoke.SpheresOfInfluence.clear();
	ExplodionPE.SpheresOfInfluence.clear();

}