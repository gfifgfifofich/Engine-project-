#pragma once
ParticleEmiter LaserPm;
ParticleEmiter LaserShotPm;



class Laser
{
public:
	DamageSphere body;

	glm::vec4 color = glm::vec4(1.0f, 10.0f, 100.0f, 1.0f);

	
	
	float Intensity = 1.0f;

	float time = 0.0f;
	float maxtime = 0.0f;

	float width = 10.0f;

	bool inf = false;

	int fraction = 0;
	

	unsigned int source;

	Ray RayCast; 
	Laser(glm::vec2 position, glm::vec2 direction, float length, int steps)
	{
		RayCast.position = position;
		RayCast.direction = direction;

		RayCast.length = length;
		RayCast.Steps = steps;
		RayCast.iterations = 2;

		RayCast.Update();
		RayCast.normalize();
	}
	void Process(float dt)
	{
		if (!inf)
		{
			time -= dt;
			if (time <= 0.0f)
			{
				body.dead = true;
				time = 0.0f;
			}
		}
		Intensity = time / maxtime;
		body.body.r = width;
		body.body.position = RayCast.ClosestPoint;
		DamageSpheres.push_back(&body);

	}

	void Draw()
	{
		DrawLine(RayCast.position, RayCast.ClosestPoint, width * Intensity, glm::vec4(color.x, color.y, color.z, color.a * Intensity));
		//DrawCircle(RayCast.ClosestPoint, 10, glm::vec4(1.0f, 0.0f, 0.f, 1.0f));
		glm::vec2 lp = (RayCast.position + RayCast.ClosestPoint) * 0.5f;
		DrawLight(glm::vec3(lp.x,lp.y, BulletHitLightHeight),
			glm::vec2( length(RayCast.position - RayCast.ClosestPoint) * 1.0f, width * 32.0f * Intensity),
			glm::vec4(color.x*0.01f, color.y * 0.01f, color.z * 0.01f, color.a*Intensity),
			0.01f,
			get_angle_between_points(RayCast.position, RayCast.ClosestPoint)+0.5*pi);
		LaserPm.Spawn(RayCast.ClosestPoint, 1);

		//DrawLight(body.body.position, glm::vec2(body.body.r*10), glm::vec4(color.x, color.y, color.z, color.a * Intensity), 0.01f);
	}

	void Dead()
	{


		ScreenShake += Intensity * body.recoil * 0.000001f;
		ChromaticStrength += Intensity * body.recoil * 0.000001f;
		body.dead = true;
		//GenSource(&source);
		//SetSourceSound(&source, &HeavyHit);
		//SetSourcePosition(&source, glm::vec3(DamageSphere.position, 0.0f));
		//SetSourceRefDist(&source, 0.5f);
		////SetSourcePitch(&source, 1.0f + rand() % 10 * 0.05f - 0.25f);
		//PlaySource(&source);
		bulletColisionPm.Spawn(body.body.position, 25);

	}
	~Laser()
	{
		DeleteSource(&source);
	}
};
std::vector<Laser> Lasers;
std::vector<Laser*> LaserPtrs;

void ProcessLasers(float dt, bool draw, bool updateRaycasts = false)
{

	for (int i = 0; i < LaserPtrs.size(); i++)
	{
		for (int c = 0; c < GameScene->Collision_cubes.size(); c++)
			if (GameScene->Collision_cubes[c]->id == -1)
				CastRayToQuad(&LaserPtrs[i]->RayCast, *GameScene->Collision_cubes[c]);

		for (int a = 0; a < GameScene->Collision_balls.size(); a++)
			if (GameScene->Collision_balls[a]->id == -1)
				CastRayToBall(&LaserPtrs[i]->RayCast, *GameScene->Collision_balls[a]);


		for (int c = 0; c < balls.size(); c++)
			if (LaserPtrs[i]->fraction != balls[c]->id)
				CastRayToBall(&LaserPtrs[i]->RayCast, *balls[c]);

		LaserPtrs[i]->Process(dt);
		if(draw)LaserPtrs[i]->Draw();
		if(updateRaycasts)LaserPtrs[i]->RayCast.Update();
	}


	LaserPtrs.clear();
	for (int i = 0; i < Lasers.size(); i++)
	{

		if (!Lasers[i].body.dead)
		{

			for (int c = 0; c < GameScene->Collision_cubes.size(); c++)
				if (GameScene->Collision_cubes[c]->id == -1)
					CastRayToQuad(&LaserPtrs[i]->RayCast, *GameScene->Collision_cubes[c]);

			for (int a = 0; a < GameScene->Collision_balls.size(); a++)
				if (GameScene->Collision_balls[a]->id == -1)
					CastRayToBall(&LaserPtrs[i]->RayCast, *GameScene->Collision_balls[a]);

			for (int c = 0; c < balls.size(); c++)
				if (Lasers[i].fraction != balls[c]->id)
					CastRayToBall(&Lasers[i].RayCast, *balls[c]);

			Lasers[i].Process(dt);
			if (draw)Lasers[i].Draw();
			if (updateRaycasts)Lasers[i].RayCast.Update();
		}
		else
		{
			Lasers[i] = Lasers[Lasers.size() - 1];
			Lasers.pop_back();
			if (Lasers.size() != 0)
			{
				for (int c = 0; c < GameScene->Collision_cubes.size(); c++)
					if (GameScene->Collision_cubes[c]->id == -1)
						CastRayToQuad(&LaserPtrs[i]->RayCast, *GameScene->Collision_cubes[c]);

				for (int a = 0; a < GameScene->Collision_balls.size(); a++)
					if (GameScene->Collision_balls[a]->id == -1)
						CastRayToBall(&LaserPtrs[i]->RayCast, *GameScene->Collision_balls[a]);

				for (int c = 0; c < balls.size(); c++)
					CastRayToBall(&Lasers[i].RayCast, *balls[c]);

				Lasers[i].Process(dt);			
				if (draw)Lasers[i].Draw();
				if (updateRaycasts)Lasers[i].RayCast.Update();
			}
		}

	}
}

void SpawnLaser(int fraction, glm::vec2 position, glm::vec2 direction, float damage, float size, float Heat = 1.0f, float time = 0.0f, float recoil = 600.0f, int id = 0 , float length = 50.0f)
{
	Laser L(position, direction, length,75);
	L.time = time;
	L.maxtime = time;
	L.width = size;
	L.body.Damage = damage;
	L.body.id = id;
	L.body.Heat = Heat;
	L.body.recoil = recoil;
	L.body.recoil = recoil;
	L.fraction = fraction;
	Lasers.push_back(L);
}

