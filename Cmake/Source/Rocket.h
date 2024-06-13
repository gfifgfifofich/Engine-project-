#pragma once
class Rocket
{
public:
	DamageSphere DS;

	float timeLeft = 10.0f;
	float lifet = 10.0f;
	ball body[2];
	bool fired = false;
	bool Exploded = false;
	float dmg = 0.0f;
	float ExplodionForce = 0.0f;
	glm::vec2 target = glm::vec2(0.0f);
	glm::vec2 dir;
	glm::vec2 mid;
	glm::vec2 midvel;
	float throtle = 0.0f;
	float explodionR = 5.0f;
	unsigned int source;
	
	bool ThrowParticles = false;
	float T = 0.015f;

	Rocket() {};
	void Init(glm::vec2 position,glm::vec2 dir, float r, float dmg, float lifetime)
	{
		DS.Damage = 0.0f;
		DS.singleHit = true;
		DS.recoil = 0.0f;
		this->dmg = dmg;
		body[0].position = position;
		body[1].position = position + dir * 3.0f*r;
		body[0].r = r;
		body[1].r = r;
		fired = false;
		this->dir = dir;
		timeLeft = lifetime;
		lifet = lifetime;
		
	};
	void GenSrc()
	{

		DeleteSource(&source);
		GenSource(&source);
		SetSourceSound(&source, &RocketEngineSound);
		SetSourceLooping(&source, true);
		PlaySource(&source);
	}
	void DeleteSrc()
	{
		StopSource(&source);
		DeleteSource(&source);

	}
	void Process(float dt)
	{
		T -= dt;
		if (T <= 0.0f)
		{
			T = 0.015f;
			ThrowParticles = true;
		}
		dir = Normalize(body[1].position - body[0].position);

		mid = (body[1].position + body[0].position) * 0.5f;
		midvel = (body[0].velocity + body[1].velocity) * 0.5f;
		glm::vec2 Force = glm::vec2(0.0f);
		
		SetSourcePosition(&source, mid);
		SetSourcePitch(&source, 4.0f);
		SetSourceVelocity(&source, glm::vec3(midvel, 0.0f));
		SetSourceGain(&source, 0.25f);

		if (DS.dead)
			Explode();
		if (fired && !Exploded) {
			DamageSpheres.push_back(&DS);

			timeLeft -= dt;

			// NeuralNetwork without NeuralNetwork
			Force.x = sigmoid(((mid.x - target.x) * 0.1f * -0.269978 - midvel.x * 0.1f * 0.0435735)) * 250.0f - 125.0f;
			Force.y = sigmoid(((mid.y - target.y) * 0.1f * -0.269978 - midvel.y * 0.1f * 0.0435735)) * 250.0f - 125.0f;

			glm::vec2 norm = Normalize(Rotate((mid - target), pi * 0.5f));
			Force -= DOT(norm, midvel) * norm * 4.0f;
			//Force = Normalize(Force) * 125.0f;
			/*Force.x = sigmoid(((mid.x - target.x) * 40.0f * -0.269978 - midvel.x * 40.0f * 0.0435735) - 6.42968) * 250.0f - 125.0f;
			Force.y = sigmoid(((mid.y - target.y) * 40.0f * -0.269978 - midvel.y * 40.0f * 0.0435735) - 6.42968) * 250.0f - 125.0f;*/

			throtle = length(Force) * 0.008f;
			if (throtle > 1.0f) throtle = 1.0f;
			if (throtle < 0.0f) throtle = 0.0f;
			float stage = timeLeft / lifet;
			if (timeLeft <= 0.0f)
			{
				Explode();
				DeleteSrc();
			}

			glm::vec2 trgdir = Normalize(Force);
			body[0].position = mid + trgdir * body[0].r;
			body[1].position = mid - trgdir * body[1].r;



		}
		else
		{
			SetSourceGain(&source, 0.0f);
			throtle = 0.0f;
		}
		if (Exploded)
			DeleteSource(&source);
		body[0].Force = Force;
		body[1].Force = Force;

		body[0].Process(dt);
		body[1].Process(dt);
		Strut(&body[1], &body[0], body[1].r * 2.0f);
		DS.body.position = body[1].position;
		DS.body.r = body[1].r * 2.0f;

		for (int a = 0; a < GameScene->Collision_cubes.size(); a++)
			if (!DS.dead)
				if (GameScene->Collision_cubes[a]->id == -1 && BtCCollisionCheck(DS.body, *GameScene->Collision_cubes[a]))
				{
					Explode();
					DeleteSrc();
				}
		for (int a = 0; a < GameScene->Collision_balls.size(); a++)
			if (!DS.dead)
				if (GameScene->Collision_balls[a]->id == -1 && BtBCollisionCheck(DS.body, *GameScene->Collision_balls[a]))
				{
					Explode();
					DeleteSrc();
				}
	}
	void Explode()
	{
		if (!Exploded)
		{
			mid = (body[1].position + body[0].position) * 0.5f;
			SetSourceGain(&source, 0.0f);
			DeleteSrc();
			SpawnExplodion(mid, explodionR, dmg, 1.0f,ExplodionForce);
			ScreenShake += explodionR * 0.01f;
			ChromaticAbberation += explodionR * 0.2f;
			timeLeft = 0.0f;
			Exploded = true;
		}
	}
	void Draw()
	{
		if (ThrowParticles) 
		{
			ThrowParticles = false;
			for (int i = 0; i < 3; i++)
				EngineSmoke.Spawn(body[1].position + dir * body[0].r * -1.0f - dir * (rand() % 1000 * 0.002f * body[0].r),
					dir * 5000.0f * throtle * 0.025f, 1,
					EngineSmoke.lifetime * 0.5f * abs(throtle) * (rand() % 1000 * 0.0005f + 0.5f));
		}
		DrawLight(body[1].position + dir * body[0].r, glm::vec2(30.0f * abs(throtle)), glm::vec4(10.0f, 2.0f, 1.0f, abs(0.5f + abs(throtle) + (rand() % 100 - 50) * 0.01f)), 0.0f);
		DrawTexturedQuad(mid, glm::vec2(1.0f * body[1].r, 3.0f * body[1].r), RocketEngineTexture, get_angle_between_points(mid, mid - dir), glm::vec4(1.0f), 100, CubeNormalMapTexture);

	}
	~Rocket()
	{
		DeleteSrc();
	}
};

std::vector<Rocket>RocketArray;
std::vector<Rocket*>Rockets;


Rocket* NewRocket(glm::vec2 position,glm::vec2 dir, float r, float dmg, float lifetime)
{
	Rocket* R = new Rocket();
	R->Init(position, dir, r, dmg, lifetime);
	Rockets.push_back(R);
	return Rockets[Rockets.size() - 1];

}

void ProcessRockets(float dt)
{
	glm::vec3 Color = glm::vec3(10.0f, 2.0f, 1.0f);
	int iter = 0;
	while (iter < RocketArray.size())
	{


		if (RocketArray[iter].timeLeft <= 0.0f)
		{
			RocketArray[iter].Explode();
			
			RocketArray[iter] = RocketArray[RocketArray.size() - 1];
			RocketArray.pop_back();
		}
		else
			iter++;
	}

	for (int i = 0; i < RocketArray.size(); i++)
	{
		RocketArray[i].Process(dt);
		
	}
	for (int i = 0; i < Rockets.size(); i++)
	{
		Rockets[i]->Process(dt);

	}
	Rockets.clear();
}
