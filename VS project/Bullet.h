#pragma once

ParticleEmiter bulletFlightPm;
ParticleEmiter bulletColisionPm;



class Bullet
{
public:
	DamageSphere body;


	float dyingtime = 1.5f;
	float lifetime = 5.0f;
	bool wasdead = false;
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

			if((int)body.body.r != 0)
				bulletFlightPm.SpawnInCircle(body.body.position,body.body.r, 1,body.body.velocity*0.25f );
			else
				bulletFlightPm.SpawnInCircle(body.body.position, 1, 1, body.body.velocity * 0.25f );

		}
		else
		{
			dyingtime -= dt;
			float stage = abs(((dyingtime - 1.3f)* 2.0f - 0.4f) / 0.4f);
			if(dyingtime>1.3f)
				DrawLight(body.body.position, glm::vec2(1000 * (1.0f-stage))*0.025f, glm::vec4(2.5f, 1.0f, 0.5f, 0.5f));
		}

		for (int a = 0; a < Map.cubes.size(); a++)
			if (!body.dead)
				if (Map.cubes[a].id==-1 && BtCCollisionCheck(body.body, Map.cubes[a]))
					Dead();

		for (int a = 0; a < Map.balls.size(); a++)
			if (!body.dead)
				if (Map.cubes[a].id == -1 && BtBCollisionCheck(body.body, Map.balls[a]))
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

			PlaySound(&BulletHit, body.body.position,1.0f,0.5f);
			float speed = length(body.body.velocity);
			ScreenShake += body.body.r * speed * 0.000001f;
			ChromaticStrength += body.body.r * speed * 0.000001f;

			body.dead = true;
			bulletColisionPm.Spawn(body.body.position,25);
		}
	}
};
std::vector<Bullet> bullets;

void ProcessBullets(float dt, bool draw)
{
	bulletFlightPm.Process(dt);
	bulletColisionPm.Process(dt);
	for (int i = 0; i < bullets.size(); i++)
	{
		if (i < bullets.size()) 
		{
			if (!bullets[i].body.dead || bullets[i].dyingtime > 0.0f)
			{
				bullets[i].Process(dt);
				if (draw)bullets[i].Draw();
			}
			else
			{
				bullets[i] = bullets[bullets.size() - 1];
				bullets.pop_back();
				if (bullets.size() > 0)
				{
					bullets[i].Process(dt);
					if(draw)bullets[i].Draw();
				}
			}
		}
	}
}

void SpawnBullet(glm::vec2 position, glm::vec2 velocity, float damage, float size, float Heat = 1.0f,float recoil = 600.0f, bool Enemy = false)
{
	Bullet b;

	b.body.body.position = position;
	b.body.body.velocity = velocity;
	b.body.body.r = size;
	b.body.Damage = damage;
	b.body.enemy = Enemy;
	b.body.Heat = Heat;
	b.body.recoil = recoil;
	b.body.singleHit = true;
	bullets.push_back(b);
}

