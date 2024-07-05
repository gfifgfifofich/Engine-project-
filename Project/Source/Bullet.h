#pragma once




class Bullet
{
public:
	DamageSphere body;


	float dyingtime = 1.5f;
	float lifetime = 3.0f;
	bool wasdead = false;

	float t = 0.0f;
	void Process(float dt)
	{
		lifetime -= dt;
		if (lifetime <= 0.0f)
			Dead();
		if (body.dead && !wasdead)
			Dead();
		if (!body.dead)
		{
			body.body.Process(dt);
			DamageSpheres.push_back(&body);
			t -= dt;
		}	
		else
		{
			dyingtime -= dt;
			float stage = abs(((dyingtime - 1.3f)* 2.0f - 0.4f) / 0.4f);
			if(dyingtime>1.3f)
				DrawLight(glm::vec3(body.body.position.x, body.body.position.y, BulletHitLightHeight), glm::vec2(1000 * (1.0f-stage))*0.025f, glm::vec4(2.5f, 1.0f, 0.5f, 0.5f));
		}

		for (int a = 0; a < GameScene->Collision_cubes.size(); a++)
			if (!body.dead)
				if (GameScene->Collision_cubes[a]->id==-1 && BtCCollisionCheck(body.body, *GameScene->Collision_cubes[a]))
					Dead();

		for (int a = 0; a < GameScene->Collision_balls.size(); a++)
			if (!body.dead)
				if (GameScene->Collision_balls[a]->id == -1 && BtBCollisionCheck(body.body, *GameScene->Collision_balls[a]))
					Dead();

	}

	void Draw()
	{
		DrawCircle(body.body, body.body.color,true);
	}

	void Dead()
	{
		if (!wasdead)
		{
			wasdead = true;

			playsound(BulletHit, body.body.position,0.5f,1.0f);
			float speed = length(body.body.velocity);
			ScreenShake += body.body.r * speed * 0.000001f;
			ChromaticAbberation += body.body.r * speed * 0.000001f;

			body.dead = true;
			bulletColisionPm.Spawn(body.body.position,25);
		}
	}
};
std::vector<Bullet> bullets;

void ProcessBullets(float dt, bool draw)
{
	int i=0;
	while(i < bullets.size())
	{	
		if (!bullets[i].body.dead || bullets[i].dyingtime > 0.0f)
		{
			bullets[i].Process(dt);
			
			if (bullets[i].t <= 0.0f)
			{
				bullets[i].t = 0.025f;
				if ((int)bullets[i].body.body.r != 0)
					bulletFlightPm.SpawnInCircle(bullets[i].body.body.position, bullets[i].body.body.r, 1, bullets[i].body.body.velocity * 0.25f);
				else
					bulletFlightPm.SpawnInCircle(bullets[i].body.body.position, 1, 1, bullets[i].body.body.velocity * 0.25f);
			}
			if (draw)bullets[i].Draw();
			i++;
		}
		else
		{
			bullets[i] = bullets[bullets.size() - 1];
			bullets.pop_back();
		}
	}
}

void SpawnBullet(glm::vec2 position, glm::vec2 velocity, float damage, float size, float Heat = 1.0f,float recoil = 600.0f, int id = 0)
{
	Bullet b;

	b.body.body.position = position;
	b.body.body.velocity = velocity;
	b.body.body.r = size;
	b.body.Damage = damage;
	b.body.id = id;
	b.body.Heat = Heat;
	b.body.recoil = recoil;
	b.body.singleHit = true;
	bullets.push_back(b);
}

