#pragma once


struct Material
{
	//Raw
	int Fe = 0;
	int C = 0;
	int Al = 0;
	int Cu = 0;
	int Au = 0;
	int U = 0;

	int Ti = 0;
	//Processed
	int Steel = 0;
};

class BallBodyComponent : public ball
{
public:
	float temperature = 0.0f;
};

enum TYPE
{
	STRUCTUREPART = 0,
	WEAPON = 1,
	PROPULSION = 2
};

enum PART
{
	BALLBODY ,
	ROCKETENGINE ,
	GUN,
	LASERGUN,
	RADIATOR,
	ROTOR,
	ROCKETLAUNCHER,
	MINIGUN,
	CRYOCOOLLER,

	STATICPOINT ,
	CENTRALPART 
};

#define SpawnablePartAmount 9-1

class BodyComponent
{
public:
	struct BoolDataPoint
	{
		bool source;
		std::string name;
		bool data = false;
		glm::vec2 lastpos = glm::vec2(0.0f);
		bool connected;
	};
	struct FloatDataPoint
	{
		bool source = true;
		std::string name;
		float data = 0.0f;
		glm::vec2 lastpos = glm::vec2(0.0f);
		bool connected;
	};
	struct VectorDataPoint
	{
		bool source = true;
		std::string name;
		glm::vec2 data = { 0.0f ,0.0f};
		glm::vec2 lastpos = glm::vec2(0.0f);
		bool connected;
	};

	BoolDataPoint* bDataConnections;
	FloatDataPoint* fDataConnections;
	VectorDataPoint* vDataConnections;

	int bDCsize=0;
	int fDCsize=0;
	int vDCsize=0;

	std::string name = "NO NAME";

	BallBodyComponent* body;
	int bodysize = 1;
	float freq = 1.0f;
	unsigned int source = 0.0f;
	int type = TYPE::STRUCTUREPART;

	int partid = -1;

	bool enemy = false;
	bool dead = false;
	bool debris = false;
	bool deactivated = false;

	bool attached = false;



	float Health = 1.0f;
	float maxHealth = 1.0f;

	
	bool shot = false;

	float throtle = 0.0f;

	bool shutdown = true;
	float shutdownTemp = 10.0f;
	float MaxTemp = 30.0f;
	float MinAutocooltemp = 0.0f;
	float MinTemp = -30.0f;

	float CoolingSpeed = 0.5f;

	float Power = 350.0f;

	bool WasHitThisFrame = false;
	float dmgThisFrame = 0;

	glm::vec4 BaseColor = glm::vec4(1.0f);
	glm::vec4 HeatColor = glm::vec4(20.0f,4.0f,0.8f,0.0f);
	glm::vec4 ColdColor = glm::vec4(0.04f,2.0f,10.0f,0.0f);
	glm::vec4 color = glm::vec4(1.0f);

	glm::vec2 targetrotpoint;
	glm::vec2 dir = {0.0f,1.0f};
	glm::vec2 mid;


	Material Cost;
	Material Contains;


	void ProcessBody(float dt)
	{
		WasHitThisFrame = false;
		dmgThisFrame = 0;

		float avgT = 0.0f;
		for (int i = 0; i < bodysize; i++)
		{
			if (body[i].temperature > MinAutocooltemp)
				body[i].temperature -= dt * CoolingSpeed;

			if (body[i].temperature <= MinAutocooltemp)
				shutdown = false;
			if (body[i].temperature > shutdownTemp)
				shutdown = true;

			if (body[i].temperature < MinAutocooltemp)
				body[i].temperature += dt * CoolingSpeed;

			if (body[i].temperature > MaxTemp) body[i].temperature = MaxTemp;
			if (body[i].temperature < MinTemp) body[i].temperature = MinTemp;
			avgT += body[i].temperature;

		}
		avgT /= bodysize;
		

		float tmpdiv = 1.0f / MaxTemp;
		if (avgT > 0.0f)
			color = BaseColor + HeatColor * (avgT * tmpdiv);
		else
			color = BaseColor - ColdColor * (avgT * tmpdiv);


		if (Health < 0.0f)
			dead = true;
	}

	virtual void Ready(glm::vec2 position, glm::vec2 direction, float size, float mass = 1.0f) {}
	virtual void Process(float dt) {}
	virtual void GenSoundSource(){}
	virtual void Delete(){}
	virtual	void Draw(int Z_Index = 0){}


	virtual	void DrawDataConnections(int partid, bool b, bool f, bool v,int Z_Index = 0)
	{

		float Scale = (body[0].r / 2);
		int i = 0;
		int p = 0;
		bool secondColomn = false;
		glm::vec2 norm = Rotate(dir, pi * 0.5f);
		float csx = 1.0f / CameraScale.x;


		if (b)
		{
			while (i < bDCsize)
			{
				glm::vec2 position;
				if (!secondColomn)
					position = body[0].position + dir * float(p) * Scale * 2.0f + norm * Scale;
				else
					position = body[0].position + dir * float(p) * Scale * 2.0f - norm * Scale;

				float rad = Scale;
				if (sqrlength(MousePosition - position) < rad * rad)
				{
					rad *= 1.1f;/*
					DrawText(bDataConnections[i].name, MousePosition, 0.75f * csx, glm::vec4(1.0f, 0.5f, 0.0f, 0.5f)*3.0f, true);
					glm::vec2 Textsize = getTextSize(bDataConnections[i].name)* 0.75f * csx;
					DrawCube(MousePosition + Textsize * 0.5f, Textsize * 0.8f, 0.0f, glm::vec4(0.0f, 0.0f, 0.0f, 0.9f),false,NULL,1000);*/
					UI_DrawTextOnPlate(bDataConnections[i].name, ScreenMousePosition, 0.75f, glm::vec4(1.0f, 0.5f, 0.0f, 0.5f) * 3.0f, glm::vec4(0.0f, 0.0f, 0.0f, 0.9f), 1200, false);

					if (JustPressedLMB)
					{
						if (DataconnectionData[0] == 0 )
						{
							DataconnectionData[1] = 0;
							DataconnectionData[2] = partid;
							DataconnectionData[3] = i;
							DataconnectionData[0] = 1;

						}
						else if (DataconnectionData[0] == 1 && DataconnectionData[1] == 0)
						{
							DataconnectionData[0] = 2;
							DataconnectionData[4] = partid;
							DataconnectionData[5] = i;
						}
					}
				}
				bDataConnections[i].lastpos = position;
				DrawCircle(position, rad, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), true, BallNormalMapTexture, Z_Index);
				if(!bDataConnections[i].source)
					DrawCircle(position, rad*0.75f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), true, BallNormalMapTexture, Z_Index);

				i++;
				p++;
				if (i >= bDCsize * 0.5f && !secondColomn)
				{
					secondColomn = true;
					p = 0;
				}
			}
		}
		else if (f)
		{
			while (i < fDCsize)
			{
				glm::vec2 position;
				if (!secondColomn)
					position = body[0].position + dir * float(p) * Scale * 2.0f + norm * Scale;
				else
					position = body[0].position + dir * float(p) * Scale * 2.0f - norm * Scale;
				float rad = Scale;
				if (sqrlength(MousePosition - position) < rad * rad)
				{
					rad *= 1.1f;/*
					DrawText(fDataConnections[i].name, MousePosition, 0.75f * csx, glm::vec4(1.0f, 0.5f, 0.5f, 0.5f) * 3.0f, true);

					glm::vec2 Textsize = getTextSize(fDataConnections[i].name) * 0.75f * csx;
					DrawCube(MousePosition + Textsize * 0.5f, Textsize * 0.8f, 0.0f, glm::vec4(0.0f, 0.0f, 0.0f, 0.9f), false, NULL, 1000);*/

					UI_DrawTextOnPlate(fDataConnections[i].name, ScreenMousePosition, 0.75f, glm::vec4(1.0f, 0.5f, 0.5f, 0.5f) * 3.0f, glm::vec4(0.0f, 0.0f, 0.0f, 0.9f), 1200, false);

					if (JustPressedLMB)
					{
						if (DataconnectionData[0] == 0)
						{
							DataconnectionData[1] = 1;
							DataconnectionData[2] = partid;
							DataconnectionData[3] = i;
							DataconnectionData[0] = 1;

						}
						else if (DataconnectionData[0] == 1 && DataconnectionData[1] == 1)
						{
							DataconnectionData[0] = 2;
							DataconnectionData[4] = partid;
							DataconnectionData[5] = i;
						}
					}
				}
				fDataConnections[i].lastpos = position;

				DrawCircle(position, rad, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), true, BallNormalMapTexture, Z_Index);

				if (!fDataConnections[i].source)
					DrawCircle(position, rad * 0.75f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), true, BallNormalMapTexture, Z_Index);
				i++;
				p++;
				if (i >= fDCsize * 0.5f && !secondColomn)
				{
					secondColomn = true;
					p = 0;
				}
			}
		}
		else if (v)
		{
			while (i < vDCsize)
			{
				glm::vec2 position;
				if (!secondColomn)
					position = body[0].position + dir * float(p) * Scale * 2.0f + norm * Scale;
				else
					position = body[0].position + dir * float(p) * Scale * 2.0f - norm * Scale;
				float rad = Scale;
				if (sqrlength(MousePosition - position) < rad * rad)
				{
					rad *= 1.1f;/*
					DrawText(vDataConnections[i].name, MousePosition, 0.75f * csx, glm::vec4(0.0f, 0.5f, 1.0f, 0.5f) * 3.0f, true);
					glm::vec2 Textsize = getTextSize(vDataConnections[i].name) * 0.75f * csx;
					DrawCube(MousePosition + Textsize * 0.5f, Textsize * 0.8f, 0.0f, glm::vec4(0.0f, 0.0f, 0.0f, 0.9f), false, NULL, 1000);*/
					UI_DrawTextOnPlate(vDataConnections[i].name, ScreenMousePosition, 0.75f, glm::vec4(1.0f, 0.5f, 0.5f, 0.5f) * 3.0f, glm::vec4(0.0f, 0.0f, 0.0f, 0.9f), 1200, false);

					if (JustPressedLMB)
					{
						if (DataconnectionData[0] == 0)
						{
							DataconnectionData[1] = 2;
							DataconnectionData[2] = partid;
							DataconnectionData[3] = i;
							DataconnectionData[0] = 1;

						}
						else if (DataconnectionData[0] == 1 && DataconnectionData[1] == 2)
						{
							DataconnectionData[0] = 2;
							DataconnectionData[4] = partid;
							DataconnectionData[5] = i;
						}
					}
				}
				vDataConnections[i].lastpos = position;

				DrawCircle(position, rad, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), true, BallNormalMapTexture, Z_Index);

				if (!vDataConnections[i].source)
					DrawCircle(position, rad * 0.75f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), true, BallNormalMapTexture, Z_Index);
				i++;
				p++;
				if (i >= vDCsize * 0.5f && !secondColomn)
				{
					secondColomn = true;
					p = 0;
				}
			}
		}
	}

	void DamageSphereCollide(DamageSphere* DS)
	{
		if (!DS->dead && (DS->enemy != enemy || DS->neutral || debris))
		{
			bool hit = false;
			for(int i=0;i<bodysize;i++)
				if (BtBCollisionCheck(DS->body, body[i]))
				{
					if (!hit)
					{
						body[i].temperature += DS->Heat;
						Health -= DS->Damage;
						hit = true;
						WasHitThisFrame = true;
						dmgThisFrame += DS->Damage;
					}
						if (sqrlength(DS->body.position - body[i].position) > 0.0f)
							body[i].velocity -= Normalize(DS->body.position - body[i].position) * DS->recoil / body[i].mass;

						body[i].velocity *= DS->friction;
					
					if (DS->singleHit)
						DS->dead = true;
				}
			
		}
	}
	void CreateBody(int size, int boolDCsize = 0,int floatDCsize=0, int vectorDCsize = 0)
	{
		bDataConnections = new BoolDataPoint[boolDCsize];
		bDCsize = boolDCsize;

		fDataConnections = new FloatDataPoint[floatDCsize];
		fDCsize = floatDCsize;

		vDataConnections = new VectorDataPoint[vectorDCsize];
		vDCsize = vectorDCsize;

		body = new BallBodyComponent[size];
		//Temperatures = new float[size];
		bodysize = size;



	}
	void DeleteBody()
	{
		delete[bodysize] body;
		if(bDCsize>0)
			delete[bDCsize] bDataConnections;
		if (fDCsize > 0)
			delete[fDCsize] fDataConnections;
		if (vDCsize > 0)
			delete[vDCsize] vDataConnections;
	}

};

std::vector<BodyComponent*> SpawnableParts;

// guns
ParticleEmiter GunShotPE;
class Gun : public BodyComponent
{
public:
	//HEAT related stuff
	float HeatPerShot = 1.0f;
	float BulletHeat = 1.0f;




	float TargetAngle = 0.0f;

	float speed = 500.0f;


	float RotationalFriction = 50.5f;

	float bulletSpeed = 150.0f;
	float dmg = 0.2f;
	float bulletSize = 50.0f;
	float recoil = 600.0f * 0.025f;

	float t = 1.0f;
	float shootspeed = 0.2f;

	void Ready(glm::vec2 position, glm::vec2 direction, float size, float mass = 1.0f) override
	{
		partid = PART::GUN;
		type = TYPE::WEAPON;
		CreateBody(2,1,0,1);
		body[0].position = position;
		body[1].position = position + direction * 3.0f;
		body[0].r = size;
		body[1].r = size*0.75;
		deactivated = true;

		body[0].mass = mass;
		body[1].mass = mass*0.2f;

		Cost.Steel = 5;
		Cost.Cu = 2;
		Cost.Al = 2;

		ProcessConnections();
	}
	void ProcessConnections()
	{

		bDataConnections[0].name = "Shoot";
		vDataConnections[0].name = "Target";

		vDataConnections[0].source = false;
		bDataConnections[0].source = false;
	}
	void Process(float dt) override
	{
		ProcessConnections();
		ProcessBody(dt);
		body[0].color = color;
		body[1].color = color;
		if (source != 0) {
			SetSourcePosition(&source, glm::vec3(body[1].position, 0.0f));
			SetSourceVelocity(&source, glm::vec3(body[0].velocity, 1.0f));
		}
		shot = bDataConnections[0].data && bDataConnections[0].connected;
		if (!debris)
		{
			t -= dt;
			if (shot && t <= 0)
				Shoot();
			targetrotpoint = vDataConnections[0].data;

			float stage = get_relative_angle_between_points(body[0].position - body[1].position, body[0].position - targetrotpoint) / (pi * 1.5f);



			if (!deactivated)
			{
				glm::vec2 rotvec = body[0].position - body[1].position;
				rotvec = Normalize(glm::vec2(-rotvec.y, rotvec.x));
				body[1].velocity -= dt * RotationalFriction * DOT(body[1].velocity - body[0].velocity, rotvec) * rotvec;

				body[1].Force += stage * speed * rotvec;
			}

		}
		glm::vec2 posdif = body[1].position - body[0].position;

		glm::vec2 norm = Normalize(posdif);

		glm::vec2 Difference = posdif - norm * body[0].r * 3.0f;



		body[0].position += Difference * 0.5f;
		body[1].position += -Difference * 0.5f;

		glm::vec2  velbuf = body[0].velocity;

		body[1].velocity -= DOT(body[1].velocity - velbuf, norm) * norm;
		body[0].Process(dt);
		body[1].Process(dt);
		body[1].Force = { 0.0f,0.0f };
		body[0].Force = { 0.0f,0.0f };

		float change = (body[0].temperature - body[1].temperature);

		body[0].temperature -= change;
		body[1].temperature += change;
	}

	void Shoot()
	{
		if (body[1].temperature < shutdownTemp)
		{
			t= shootspeed;

			glm::vec2 dir = Normalize(body[1].position - body[0].position);


			for (int i = 0; i < 15; i++)
				GunShotPE.Spawn(body[1].position + dir * body[0].r * -1.0f + dir * (rand() % 1000 * 0.002f * body[0].r),
					dir * 500.0f * 0.025f, 1);

			for (int i = 0; i < 10; i++)
				GunShotPE.Spawn(body[1].position + dir * body[0].r * -0.9f + Rotate(dir * (rand() % 1000 * 0.0015f * body[0].r),-pi*0.7f),
			Rotate(dir * 500.0f,-pi*0.7f) * 0.025f, 1);
			for (int i = 0; i < 10; i++)
				GunShotPE.Spawn(body[1].position + dir * body[0].r * -0.8f + Rotate(dir * (rand() % 1000 * 0.0015f * body[0].r), pi * 0.7f),
			Rotate(dir * 500.0f, pi * 0.7f) * 0.025f, 1);


			body[1].temperature += HeatPerShot;
			SpawnBullet(body[1].position, bulletSpeed * Normalize(body[1].position - body[0].position), dmg, body[1].r*0.5f, BulletHeat,recoil, enemy);
			PlaySound(&source, &GunSound, body[1].position, (1.0f + rand() % 10 * 0.04f - 0.2f) * freq, freq <= 0.001f ? 0.0f : 1.0f);


			ScreenShake += body[1].r * bulletSpeed * 0.000001f;
			ChromaticStrength += body[1].r * bulletSpeed * 0.000001f;

			body[0].Force -= recoil * Normalize(body[1].position - body[0].position) * 2000.0f;

			//body[1].Force -= recoil * Normalize(body[1].position - body[0].position) * 1000.0f;
		}
	}

	void Draw(int Z_Index = 0) override
	{
		//DrawLine(body[0].position, body[1].position, body[1].r, Base.color, true, CubeNormalMapTexture, Z_Index+1);
		
		glm::vec2 mid = (body[1].position + body[0].position) * 0.5f;
		//GunTexture
		DrawTexturedQuad(mid, glm::vec2(0.5f * body[1].r, 2.0f * body[1].r), GunTexture, get_angle_between_points(body[0].position,mid), color, Z_Index+1, CubeNormalMapTexture);

		DrawCircle(body[0], glm::vec4(1.0f), true, BallNormalMapTexture, Z_Index);
	}

	void Delete() override
	{
		DeleteBody();
	}

};

class LaserGun : public BodyComponent
{
public:
	//HEAT related stuff
	float HeatPerShot = 10.0f;
	float BulletHeat = 3.0f;



	float TargetAngle = 0.0f;

	float speed = 500.0f;

	float RotationalFriction = 50.5f;

	float bulletSize = 50.0f;
	float dmg = 2.0f;
	float recoil = 600.0f * 0.025f;

	float LaserTime = 1.0f;
	float Time = 0.0f;

	float t = 0.0f;

	Laser* lsr;
	void Ready(glm::vec2 position, glm::vec2 direction, float size, float mass = 1.0f) override
	{
		partid = PART::LASERGUN;
		type = TYPE::WEAPON;
		CreateBody(2, 1, 0, 1);
		body[0].position = position;
		body[1].position = position + direction*3.0f;
		body[0].r = size;
		body[1].r = size*0.75f;
		deactivated = true;
		body[0].mass = mass ;
		body[1].mass = mass * 0.2f;
		lsr = new Laser(body[1].position, body[1].position - body[0].position,50,175);
		lsr->inf = true;

		lsr->time = 0;
		lsr->maxtime = 1;
		lsr->width = size * 0.75f;
		lsr->body.Damage = 0;
		lsr->body.Heat = 0;
		lsr->body.recoil = 0;
		lsr->body.singleHit = false;
		lsr->fraction = body[0].id;

		Cost.Steel = 10;
		Cost.Cu = 20;
		Cost.Au = 5;

		ProcessConnections();
	}
	void ProcessConnections()
	{
		bDataConnections[0].name = "Shoot";
		vDataConnections[0].name = "Target";
		vDataConnections[0].source = false;
		bDataConnections[0].source = false;

	}
	void Process(float dt) override
	{
		ProcessConnections();
		ProcessBody(dt);
		body[0].color = color;
		body[1].color = color;

		if (!debris)
		{

			shot = bDataConnections[0].data && bDataConnections[0].connected;
			targetrotpoint = vDataConnections[0].data;

			lsr->fraction = body[0].id;


			lsr->body.enemy = enemy;


			Time -= dt;
			if (Time < 0.0f) Time = 0.0f;



			float stage = get_relative_angle_between_points(body[0].position - body[1].position, body[0].position - targetrotpoint) / (pi * 1.5f);

			if (shot && body[1].temperature < shutdownTemp)
				t += dt;
			else
				t -= dt;


			if (t > 1.0f)
				t = 1.0f;
			if (t < 0.0f)
				t = 0.0f;

			if (t > 0.0f && source ==0)
			{
				GenSource(&source);
				SetSourceSound(&source, &LaserGunSound);
				SetSourceLooping(&source, true);
				PlaySource(&source);
			}
			else if (t <= 0.0f && SourcePlaying(&source))
			{
				StopSource(&source);
				DeleteSource(&source);
			}
			if (source != 0) {
				SetSourceVelocity(&source, glm::vec3(body[0].velocity, 1.0f));
				SetSourcePosition(&source, glm::vec3(body[1].position, 0.0f));
				SetSourcePitch(&source, t * freq);
				SetSourceGain(&source, t * (freq <= 0.0001f ? 0.0f : 1.0f));
			}
			body[1].temperature += t * HeatPerShot * dt;

			ScreenShake += body[1].r * recoil * 0.000021f * t;

			lsr->time = t;
			lsr->maxtime = 1.0f;
			lsr->body.Damage = t * dmg * dt;
			lsr->body.Heat = t * HeatPerShot * dt;
			lsr->body.recoil = t * recoil * dt;

			ChromaticStrength += body[1].r * recoil * 0.00001f * t;
			body[0].Force -= t * recoil * Normalize(body[1].position - body[0].position) * 1000.1f * dt;
			body[1].Force -= t * recoil * Normalize(body[1].position - body[0].position) * 1000.1f * dt;



			if (t > 0.0f)
				LaserPtrs.push_back(lsr);

			if (!deactivated)
			{
				glm::vec2 rotvec = body[0].position - body[1].position;
				rotvec = Normalize(glm::vec2(-rotvec.y, rotvec.x));
				body[1].velocity -= dt * RotationalFriction * DOT(body[1].velocity - body[0].velocity, rotvec) * rotvec;

				body[1].Force += stage * speed * rotvec;
			}

		}

		glm::vec2 posdif = body[1].position - body[0].position;

		glm::vec2 norm = Normalize(posdif);

		lsr->RayCast.direction = norm;
		lsr->RayCast.position = body[1].position;

		glm::vec2 Difference = posdif - norm * body[0].r * 3.0f;



		body[0].position += Difference * 0.5f;
		body[1].position += -Difference * 0.5f;

		glm::vec2  velbuf = body[0].velocity;

		body[1].velocity -= DOT(body[1].velocity - velbuf, norm) * norm;

		body[0].Process(dt);
		body[1].Process(dt);
		body[1].Force = { 0.0f,0.0f };
		body[0].Force = { 0.0f,0.0f };
		float change = (body[0].temperature - body[1].temperature);

		body[0].temperature -= change;
		body[1].temperature += change;
	}


	void Draw(int Z_Index = 0) override
	{
		DrawLine(body[0].position, body[1].position, body[1].r, color, true, CubeNormalMapTexture, Z_Index + 1);
		DrawCircle(body[0], glm::vec4(0.5f,0.5f,0.5f,1.0f), true, BallNormalMapTexture, Z_Index);
		
	}

	void Delete() override
	{
		DeleteBody();
		StopSource(&source);
		DeleteSource(&source);
		lsr->~Laser();
		free(lsr);
	}
};

class RocketLauncher : public BodyComponent
{
public:
	//HEAT related stuff




	float TargetAngle = 0.0f;

	float speed = 500.0f;


	float RotationalFriction = 50.5f;

	float bulletSpeed = 150.0f;
	float dmg = 0.02f;
	float bulletSize = 50.0f;
	float recoil = 600.0f * 0.025f;

	float t = 1.0f;
	float shootspeed = 2.0f;
	std::vector<Rocket*> FiredRockets;
	Rocket HoldingRocket;
	void Ready(glm::vec2 position, glm::vec2 direction, float size, float mass = 1.0f) override
	{
		partid = PART::ROCKETLAUNCHER;
		type = TYPE::STRUCTUREPART;
		CreateBody(2, 1, 0, 1);
		body[0].position = position;
		body[1].position = position + direction * 3.0f;
		body[0].r = size;
		body[1].r = size;
		deactivated = true;

		body[0].mass = mass;
		body[1].mass = mass;
		ProcessConnections();
		
		HoldingRocket.DS.Damage = dmg;
		HoldingRocket.DS.singleHit = true;

		HoldingRocket.body[0].position = body[1].position;
		HoldingRocket.body[1].position = body[1].position + dir * 3.0f * size * 0.5f;
		HoldingRocket.body[0].r = size * 0.4f;
		HoldingRocket.body[1].r = size * 0.4f;
		HoldingRocket.fired = false;
		HoldingRocket.dir = dir;
		HoldingRocket.timeLeft = 10.0f;
		HoldingRocket.lifet = 10.0f;


		Cost.Steel = 20;
		Cost.Cu = 2;
		Cost.Al = 5;
	}
	void ProcessConnections()
	{

		bDataConnections[0].name = "Shoot";
		vDataConnections[0].name = "Target";

		vDataConnections[0].source = false;
		bDataConnections[0].source = false;
	}
	void Process(float dt) override
	{
		ProcessConnections();
		ProcessBody(dt);
		body[0].color = color;
		body[1].color = color;
		if (source != 0)
		{
			SetSourcePosition(&source, glm::vec3(body[1].position, 0.0f));
			SetSourceVelocity(&source, glm::vec3(body[0].velocity, 1.0f));
		}
		dir = Normalize(body[1].position - body[0].position);

		
		HoldingRocket.body[1].position = body[1].position ;
		HoldingRocket.body[0].position = body[1].position + dir * 2.0f * HoldingRocket.body[1].r;
			if (t <= 0)
			{
				HoldingRocket.mid = (HoldingRocket.body[1].position + HoldingRocket.body[0].position) * 0.5f;
				HoldingRocket.midvel = (HoldingRocket.body[0].velocity + HoldingRocket.body[1].velocity) * 0.5f;
				HoldingRocket.dir = dir;
				HoldingRocket.body[0].Process(dt);
				HoldingRocket.body[1].Process(dt);
				Strut(&HoldingRocket.body[1], &HoldingRocket.body[0], HoldingRocket.body[1].r * 2.0f);
			}
		if (!debris)
		{
				int iter = 0;
			while (iter < FiredRockets.size())
			{
				if (FiredRockets[iter]->Exploded)
				{
					FiredRockets[iter]->DeleteSrc();
					FiredRockets[iter] = FiredRockets[FiredRockets.size() - 1];
					FiredRockets.pop_back();
				}
				else
					iter++;
			}
			for (int i = 0; i < FiredRockets.size(); i++)
			{
				FiredRockets[i]->target = targetrotpoint;
				FiredRockets[i]->fired = true;
				Rockets.push_back(FiredRockets[i]);
				if (FiredRockets[i]->timeLeft <= 0.0f)
					FiredRockets[i]->Explode();
			}
			
			shot = bDataConnections[0].data && bDataConnections[0].connected;
			targetrotpoint = vDataConnections[0].data;
			t -= dt;
			if (shot && t <= 0 && FiredRockets.size()<2)
				Shoot();

		}

		Strut(&body[0], &body[1], body[0].r * 2.0f);
		body[0].Process(dt);
		body[1].Process(dt);
		body[1].Force = { 0.0f,0.0f };
		body[0].Force = { 0.0f,0.0f };
		float change = (body[0].temperature - body[1].temperature);

		body[0].temperature -= change;
		body[1].temperature += change;
	}

	void Shoot()
	{
		t = shootspeed;



		for (int i = 0; i < 15; i++)
			GunShotPE.Spawn(body[1].position + dir * body[0].r * -1.0f + dir * (rand() % 1000 * 0.002f * body[0].r),
				dir * 500.0f * 0.025f, 1);

		for (int i = 0; i < 10; i++)
			GunShotPE.Spawn(body[1].position + dir * body[0].r * -0.9f + Rotate(dir * (rand() % 1000 * 0.0015f * body[0].r), -pi * 0.7f),
				Rotate(dir * 500.0f, -pi * 0.7f) * 0.025f, 1);
		for (int i = 0; i < 10; i++)
			GunShotPE.Spawn(body[1].position + dir * body[0].r * -0.8f + Rotate(dir * (rand() % 1000 * 0.0015f * body[0].r), pi * 0.7f),
				Rotate(dir * 500.0f, pi * 0.7f) * 0.025f, 1);

		/*HoldingRocket.body[0].velocity = dir*1.0f;
		HoldingRocket.body[1].velocity = dir*1.0f;
		HoldingRocket.DS.enemy = enemy;
		HoldingRocket.DeleteSrc();*/
		Rocket* R = new Rocket();

		R->Init(HoldingRocket.body[0].position, HoldingRocket.dir, HoldingRocket.body[0].r, dmg, 10.0f);
		R->GenSrc();
		R->fired = true;
		R->body[0].velocity = dir * 100.0f + body[1].velocity;
		R->body[1].velocity = dir * 100.0f + body[1].velocity;
		FiredRockets.push_back(R);

		//SpawnBullet(body[1].position, bulletSpeed * Normalize(body[1].position - body[0].position), dmg, body[1].r * 0.5f, BulletHeat, recoil, enemy);
	
		PlaySound(&source,&GunSound, body[1].position, (1.0f + rand() % 10 * 0.04f - 0.2f) * freq, freq <= 0.001f ? 0.0f : 1.0f);

		ScreenShake += body[1].r * bulletSpeed * 0.000001f;
		ChromaticStrength += body[1].r * bulletSpeed * 0.000001f;

		body[0].Force -= recoil * Normalize(body[1].position - body[0].position) * 2000.0f;

		//body[1].Force -= recoil * Normalize(body[1].position - body[0].position) * 1000.0f;

	}

	void Draw(int Z_Index = 0) override
	{
		//DrawLine(body[0].position, body[1].position, body[1].r, Base.color, true, CubeNormalMapTexture, Z_Index+1);

		glm::vec2 mid = (body[1].position + body[0].position) * 0.5f;
		//GunTexture
		DrawTexturedQuad(mid, glm::vec2(1.0f * body[1].r, 2.0f * body[1].r), GunTexture, get_angle_between_points(body[0].position, mid), color, Z_Index, CubeNormalMapTexture);

		//DrawCircle(body[0], glm::vec4(1.0f), true, BallNormalMapTexture, Z_Index);
		if (t <= 0)
			HoldingRocket.Draw();
	}

	void Delete() override
	{
		DeleteBody();
	}

};


class MiniGun : public BodyComponent
{
public:
	//HEAT related stuff
	float HeatPerShot = 0.8f;
	float BulletHeat = 0.1f;


	float TargetAngle = 0.0f;

	float speed = 500.0f;


	float RotationalFriction = 50.5f;

	float bulletSpeed = 1000.0f;
	float dmg = 0.2f;
	float bulletSize = 50.0f;
	float recoil = 60.0f * 0.025f;

	float t = 1.0f;
	float shootspeed = 0.034f;

	bool overheated = false;

	void Ready(glm::vec2 position, glm::vec2 direction, float size, float mass = 1.0f) override
	{
		partid = PART::MINIGUN;
		type = TYPE::WEAPON;
		CreateBody(2, 1, 0, 1);
		body[0].position = position;
		body[1].position = position + direction * 3.0f;
		body[0].r = size;
		body[1].r = size * 0.75;
		deactivated = true;

		body[0].mass = mass;
		body[1].mass = mass * 0.2f;

		Cost.Steel = 25;
		Cost.Cu = 20;
		Cost.Al = 20;
		shutdownTemp = 15.0f;
		ProcessConnections();


		GenSource(&source);
		SetSourceSound(&source, &MiniGunSound);
		SetSourceLooping(&source, true);

		SetSourcePitch(&source, freq * 1.0f);
		SetSourceGain(&source, 1.0f);
		//PlaySource(&source);
	}
	void ProcessConnections()
	{
		bDataConnections[0].name = "Shoot";
		vDataConnections[0].name = "Target";

		vDataConnections[0].source = false;
		bDataConnections[0].source = false;
	}
	void Process(float dt) override
	{
		ProcessConnections();
		ProcessBody(dt);
		body[0].color = color;
		body[1].color = color;
		if (source != 0) {
			SetSourcePosition(&source, glm::vec3(body[1].position, 0.0f));
			SetSourceVelocity(&source, glm::vec3(body[0].velocity, 1.0f));
		}
		shot = bDataConnections[0].data && bDataConnections[0].connected;

		if (body[1].temperature >= shutdownTemp)
			overheated = true;
		if (body[1].temperature <= 0.25f)
			overheated = false;

		if (!debris && !deactivated && !overheated)
		{
			if (shot && !SourcePlaying(&source))
				PlaySource(&source);

			if (!shot && SourcePlaying(&source))
				StopSource(&source);
			if (shot)
			{
				SetSourcePitch(&source, freq + (((rand() % 100) * 0.01f) - 0.5f) * 0.3f + 0.02f*body[1].temperature);

			}
			t -= dt;
			if (shot && t <= 0)
				Shoot();
			targetrotpoint = vDataConnections[0].data;

			float stage = get_relative_angle_between_points(body[0].position - body[1].position, body[0].position - targetrotpoint) / (pi * 1.5f);



			glm::vec2 rotvec = body[0].position - body[1].position;
			rotvec = Normalize(glm::vec2(-rotvec.y, rotvec.x));
			body[1].velocity -= dt * RotationalFriction * DOT(body[1].velocity - body[0].velocity, rotvec) * rotvec;

			body[1].Force += stage * speed * rotvec;


		}
		else if (SourcePlaying(&source))
			StopSource(&source);

		glm::vec2 posdif = body[1].position - body[0].position;

		glm::vec2 norm = Normalize(posdif);

		glm::vec2 Difference = posdif - norm * body[0].r * 3.0f;



		body[0].position += Difference * 0.5f;
		body[1].position += -Difference * 0.5f;

		glm::vec2  velbuf = body[0].velocity;

		body[1].velocity -= DOT(body[1].velocity - velbuf, norm) * norm;
		body[0].Process(dt);
		body[1].Process(dt);
		body[1].Force = { 0.0f,0.0f };
		body[0].Force = { 0.0f,0.0f };


		float avg = (body[0].temperature + body[1].temperature)*0.5f ;

		body[0].temperature = avg;
		body[1].temperature = avg;
	}

	void Shoot()
	{

		if (!deactivated)
		{
			t = shootspeed;

			glm::vec2 dir = Normalize(body[1].position - body[0].position);


			for (int i = 0; i < 1; i++)
				GunShotPE.Spawn(body[1].position + dir * body[0].r * -1.0f + dir * (rand() % 1000 * 0.002f * body[0].r),
					dir * 500.0f * 0.025f, 1);

			for (int i = 0; i < 2; i++)
				GunShotPE.Spawn(body[1].position + dir * body[0].r * -0.9f + Rotate(dir * (rand() % 1000 * 0.0015f * body[0].r), -pi * 0.7f),
					Rotate(dir * 500.0f, -pi * 0.7f) * 0.025f, 1);
			for (int i = 0; i < 2; i++)
				GunShotPE.Spawn(body[1].position + dir * body[0].r * -0.8f + Rotate(dir * (rand() % 1000 * 0.0015f * body[0].r), pi * 0.7f),
					Rotate(dir * 500.0f, pi * 0.7f) * 0.025f, 1);


			body[1].temperature += HeatPerShot;
			SpawnBullet(body[1].position, bulletSpeed * Normalize(body[1].position - body[0].position), dmg, body[1].r * 0.2f, BulletHeat, recoil*10.0f, enemy);
			//PlaySound(&source, &GunSound, body[1].position, (1.0f + rand() % 10 * 0.04f - 0.2f) * freq, freq <= 0.001f ? 0.0f : 1.0f);


			ScreenShake += body[1].r * bulletSpeed * 0.00001f;
			ChromaticStrength += body[1].r * bulletSpeed * 0.000075f;

			body[0].Force -= recoil * Normalize(body[1].position - body[0].position) * 2000.0f;

			//body[1].Force -= recoil * Normalize(body[1].position - body[0].position) * 1000.0f;
		}
	}

	void Draw(int Z_Index = 0) override
	{
		//DrawLine(body[0].position, body[1].position, body[1].r, Base.color, true, CubeNormalMapTexture, Z_Index+1);

		glm::vec2 mid = (body[1].position + body[0].position) * 0.5f;
		//GunTexture
		DrawTexturedQuad(mid, glm::vec2(0.5f * body[1].r, 2.0f * body[1].r), GunTexture, get_angle_between_points(body[0].position, mid), color, Z_Index + 1, CubeNormalMapTexture);

		DrawCircle(body[0], glm::vec4(0.0f,1.0f,1.0f,1.0f), true, BallNormalMapTexture, Z_Index);
	}

	void Delete() override
	{
		DeleteBody();
	}

};


// propulsion
class RocketEngine : public BodyComponent
{
public:
	//HEAT related stuff
	float HeatPerSecond = 4.0f;
	float EngineHeat = 1.0f;


	glm::vec2 Force = { 0.0f,0.0f };
	
	glm::vec2 OutForce = glm::vec2(0.0f);

	int counter = 0;

	void Ready(glm::vec2 position, glm::vec2 direction, float size, float mass = 1.0f) override
	{
		partid = PART::ROCKETENGINE;
		type = TYPE::PROPULSION;

		CreateBody(2,1);
		body[0].r = size;
		body[1].r = size;
		body[0].position = position + Normalize(direction) * size;
		body[1].position = position - Normalize(direction) * size;

		body[1].mass = mass;
		body[0].mass= mass;

		body[0].roughness = 0.0f;
		body[0].bounciness = 0.0f;
		body[1].roughness = 0.0f;
		body[1].bounciness = 0.0f;

		Cost.Ti = 5;
		Cost.Steel = 15;
		Cost.Cu = 2;

		ProcessConnections();
	}
	void ProcessConnections()
	{
		bDataConnections[0].name = "Fire override";
		bDataConnections[0].source = false;
	}
	void Process(float dt) override
	{
		ProcessConnections();
		ProcessBody(dt);
		body[0].color = color;
		body[1].color = color;
		Strut(&body[1], &body[0], body[0].r * 2.0f);

		
		body[0].Process(dt);
		body[1].Process(dt);

		dir = Normalize(body[1].position - body[0].position);

		if ((bDataConnections[0].connected && bDataConnections[0].data))
			throtle = 1.0f;
		if (!debris )
		{
			body[1].Force = Force;
			body[0].Force = Force;
		



			OutForce = Power * -dir * throtle;

			if (abs(throtle) > 0.0f && !shutdown && !deactivated)
			{
				if (source == 0 )
				{
					GenSource(&source);
					SetSourceSound(&source, &RocketEngineSound);
					SetSourceLooping(&source, true);
					PlaySource(&source);
					counter =100;
				}
				if (source != 0)
				{
					SetSourcePitch(&source, freq);
					SetSourceGain(&source, throtle * 0.25f * (freq <= 0.001f ? 0.0f : 1.0f));
					
					SetSourceVelocity(&source, glm::vec3(body[0].velocity, 0.0f));
					SetSourcePosition(&source, glm::vec3((body[1].position + body[0].position) * 0.5f, 0.0f));
					
				}
				body[1].Force += Power * -dir * throtle;
				body[0].Force += Power * -dir * throtle;


				glm::vec2 dir = Normalize(body[1].position - body[0].position);


				if (throtle > 1.0f)
					throtle = 1.0f;

				if (throtle < -1.0f)
					throtle = -1.0f;

				body[0].temperature += abs(throtle) * HeatPerSecond * dt;
				body[1].temperature += abs(throtle) * HeatPerSecond * dt;


			}
			else
			{
				SetSourceGain(&source, 0.0f);
				if (source != 0)
					counter--;
				if (counter <= 0)
				{
					StopSource(&source);
					DeleteSource(&source);

				}
			}
		}
		else
		{
			SetSourceGain(&source, 0.0f);
			if (source != 0)
				counter--;
			if (counter <= 0)
			{
				StopSource(&source);
				DeleteSource(&source);

			}
			body[1].Force = { 0.0f,0.0f };
			body[0].Force = {0.0f,0.0f};

		}
		float change = (body[0].temperature - body[1].temperature);

		body[0].temperature -= change;
		body[1].temperature += change;
	}
	void Draw(int Z_Index = 5) override
	{
		if (abs(throtle) > 0.0f && !shutdown)
		{
			if(freq>0.001f)
			for(int i =0;i<5;i++)
				EngineSmoke.Spawn(body[1].position + dir * body[0].r * -1.0f - dir * (rand() % 1000 * 0.002f* body[0].r),
					dir * 5000.0f * throtle * 0.025f, 1,
					EngineSmoke.lifetime * abs(throtle) * (rand() % 1000 * 0.0005f + 0.5f));

			DrawLight(body[1].position + dir * body[0].r, glm::vec2( 400 * abs(throtle)*0.025f), glm::vec4(10.0f, 2.0f, 1.0f, abs(0.5f + abs(throtle) + (rand() % 100 - 50) * 0.01f)), 0.0f);
		}
		glm::vec2 mid = (body[1].position + body[0].position) * 0.5f;
		DrawTexturedQuad(mid,glm::vec2(1.0f * body[1].r,2.0f* body[1].r), RocketEngineTexture,  get_angle_between_points(mid, mid - dir),color, Z_Index,CubeNormalMapTexture);

		/*DrawLine(
			body[0].position - dir * body[0].r,
			body[1].position + dir * body[1].r,
			body[0].r,
			Base.color, true);*/
	}


	void Delete() override
	{
		DeleteBody();
		StopSource(&source);
		DeleteSource(&source);
	}
};


// structure
class BallBody : public BodyComponent
{
public:




	void Ready(glm::vec2 position, glm::vec2 direction, float size,float mass = 1.0f) override
	{
		partid = PART::BALLBODY;
		type = TYPE::STRUCTUREPART;
		CreateBody(1);
		body[0].r = size;
		body[0].position = position;

		body[0].mass = mass;

		body[0].roughness = 0.0f;
		body[0].bounciness = 0.0f;
		Cost.Fe = 5;
	}

	void Process(float dt) override
	{
		ProcessBody(dt);
		body[0].color = color;
		body[0].Process(dt);

		body[0].Force = glm::vec2(0.0f);
	}
	void Draw(int Z_Index) override
	{
		DrawCircle(body[0], color, true,BallNormalMapTexture, Z_Index);
	}

	void Delete() override
	{
		DeleteBody();
	}
};

class Rotor : public BodyComponent
{
	float diaglen = 0.0f;
public:


	//DamageSphere Sawdamagespheres[4];

	void Ready(glm::vec2 position, glm::vec2 direction, float size, float mass = 1.0f) override
	{
		partid = PART::ROTOR;
		type = TYPE::STRUCTUREPART;
		CreateBody(5,2);
		for (int i = 0; i < 5; i++)
		{
			body[i].r = size;
			body[i].mass = mass;

			body[i].roughness = 0.0f;
			body[i].bounciness = 0.0f;
		}
		body[0].position = position;
		body[1].position = position + glm::vec2(size * 2.0f, 0.0f);
		body[2].position = position + glm::vec2(0.0f, size * -2.0f);
		body[3].position = position + glm::vec2(size * -2.0f, 0.0f);
		body[4].position = position + glm::vec2(0.0f, size * 2.0f);
		diaglen = sqrt(((size*2.0f) * (size*2.0f)) * 2.0f);
		ProcessConnections();

		Cost.Fe = 10;
		Cost.Cu = 5;
	}
	void ProcessConnections()
	{
		bDataConnections[0].name = "Rotation(clock)";
		bDataConnections[1].name = "Rotation(counter-clock)";
		bDataConnections[0].source = false;
		bDataConnections[1].source = false;
	}
	void Process(float dt) override
	{
		ProcessBody(dt);
		ProcessConnections();
		mid = (body[0].position);
		dir = (body[1].position - body[0].position);


		float vel = 0.0f;
		if (bDataConnections[0].data && !bDataConnections[1].data)
			vel = 1.0f;
		if (!bDataConnections[0].data && bDataConnections[1].data)
			vel = -1.0f;

		if (!debris&&!BuildingMode)
		for (int i = 1; i < 5; i++)
		{
			glm::vec2 force = Rotate(Normalize(body[i].position - body[0].position), pi * 0.5f) * Power*0.625f* vel;
			body[i].Force += force;
			body[0].Force -= force;

		}
		for (int i = 0; i < 5; i++)
		{
			body[i].color = color;
			body[i].Process(dt);
			body[i].Force = glm::vec2(0.0f);
		}
		
		Strut(&body[0], &body[1], body[0].r * 2.0f);
		Strut(&body[0], &body[2], body[0].r * 2.0f);
		Strut(&body[0], &body[3], body[0].r * 2.0f);
		Strut(&body[0], &body[4], body[0].r * 2.0f);

		Strut(&body[1], &body[2], diaglen);
		Strut(&body[2], &body[3], diaglen);
		Strut(&body[3], &body[4], diaglen);
		Strut(&body[4], &body[1], diaglen);


	}
	void Draw(int Z_Index) override
	{
		for (int i = 0; i < 5; i++)
		{
			DrawCircle(body[i], color, true, BallNormalMapTexture, Z_Index);
		}
	}

	void Delete() override
	{
		DeleteBody();
	}
};

// Misc
ParticleEmiter Smoke;
class Radiator : public BodyComponent
{
public:
	//HEAT related stuff
	float coolingSpeed;
	float mintemp;
	void Ready(glm::vec2 position,glm::vec2 direction, float size, float mass =1.0f) override
	{

		partid = PART::RADIATOR;
		type = TYPE::STRUCTUREPART;
		CreateBody(2);
		body[0].position = position + Normalize(direction) * size;
		body[1].position = position - Normalize(direction) * size;
		body[0].r = size;
		body[1].r = size;
		body[1].mass = mass;
		body[0].mass = mass;

		CoolingSpeed = 2.0f;
		MinAutocooltemp = 0.0f;
		this->mintemp= -1.0f;
		this->coolingSpeed = 2.0f;

		Cost.Al = 20;
		Cost.Cu = 5;
		Cost.Fe = 10;

	}


	void Process(float dt) override
	{
		ProcessBody(dt);
		body[0].color = color;
		body[1].color = color;

		mid = 0.5f * (body[0].position + body[1].position);
		dir = (body[1].position - body[0].position);

		float gain = 0.0f;

		if (!debris && !deactivated)
		{
			gain = ((body[1].temperature + body[0].temperature)*0.25f);


			CoolingSpeed = coolingSpeed;
			MinAutocooltemp = mintemp;
			if (gain > 0.0f)
			{
				if (source == 0)
				{
					GenSource(&source);
					SetSourceSound(&source, &SHHSound);
					SetSourceLooping(&source, true);
					SetSourcePosition(&source, (body[0].position + body[1].position) * 0.5f);
					PlaySource(&source);
				}
				if (source >= 0)
				{
					SetSourceGain(&source, gain * 0.03f);
					Smoke.SpawnInCircle(body[0].position, body[0].r, 1 + gain);
					Smoke.SpawnInCircle(body[1].position, body[1].r, 1);
					SetSourceVelocity(&source, glm::vec3(body[0].velocity, 0.0f));
					SetSourcePosition(&source, (body[0].position + body[1].position) * 0.5f);
				}
			}
			else
			{
				if (source != 0)
				{
					SetSourceGain(&source, 0.0f);
				
					StopSource(&source);
					DeleteSource(&source);
				}
			}

			

		}
		else
		{
			CoolingSpeed = 1.0f;
			if (source != 0)
			{
				SetSourceGain(&source, 0.0f);
				SetSourcePosition(&source, (body[0].position + body[1].position) * 0.5f);

				StopSource(&source);
				DeleteSource(&source);
			}
		}
	
		body[0].Process(dt);
		body[1].Process(dt);
		body[1].Force = glm::vec2(0.0f);
		body[0].Force = glm::vec2(0.0f);
		Strut(&body[0], &body[1], body[0].r * 2.0f);
		float change = (body[0].temperature - body[1].temperature);

		body[0].temperature -= change;
		body[1].temperature += change;
	}

	void Draw(int Z_Index = 5) override
	{
		glm::vec2 dif = body[0].position - body[1].position;
		//DrawLine(body[0].position + dif*0.5f, body[1].position - dif * 0.5f, body[0].r, Base.color, true, CubeNormalMapTexture, Z_Index);
		glm::vec2 mid = (body[1].position + body[0].position) * 0.5f;

		DrawTexturedQuad(mid, glm::vec2(1.0f * body[1].r, 2.0f * body[1].r), RadiatorTexture, get_angle_between_points(mid, body[0].position), color, Z_Index, CubeNormalMapTexture);

	}

	void Delete() override
	{
		DeleteBody();
		StopSource(&source);
		DeleteSource(&source);
	}
};

class CryoCooller : public BodyComponent
{
	float midmiddiag = 0.0f;
	float middiag = 0.0f;
	float diag = 0.0f;
	float diagdiag = 0.0f;

	float prevpos = 1.0f;
public:

	float dmg = 5.0f;
	float HeatPerShot = 5.0f;
	float recoil = 50.0f;

	Laser* lsr;
	void Ready(glm::vec2 position, glm::vec2 direction, float size, float mass = 1.0f) override
	{

		partid = PART::CRYOCOOLLER;
		type = TYPE::STRUCTUREPART;
		CreateBody(10);
		direction = Normalize(direction);
		for (int i = 0; i < bodysize; i++)
		{
			body[i].r = size;
			body[i].mass = mass;
			body[i].roughness = 0.0f;
			body[i].bounciness = 0.0f;
		}
		body[0].position = position + glm::vec2(0.0f, - size * 4.0f); 

		body[1].position = position + glm::vec2(-size * 2.0f, -size * 4.0f);
		body[2].position = position + glm::vec2(-size * 2.0f, -size * 2.0f);
		body[3].position = position + glm::vec2(-size * 2.0f, 0);
		body[4].position = position + glm::vec2(-size * 2.0f, size * 2.0f);

		body[5].position = position + glm::vec2(0.0, size * 2.0f);

		body[6].position = position + glm::vec2(size * 2.0f, size * 2.0f);
		body[7].position = position + glm::vec2(size * 2.0f, 0.0);
		body[8].position = position + glm::vec2(size * 2.0f, -size * 2.0f);
		body[9].position = position + glm::vec2(size * 2.0f, -size * 4.0f);

		midmiddiag =sqrt((size * 2.0f) * (size * 2.0f) + (size * 2.0f) * (size * 2.0f));
		middiag =sqrt((size * 4.0f) * (size * 4.0f) + (size * 2.0f) * (size * 2.0f));
		diag =sqrt((size * 4.0f) * (size * 4.0f) + (size * 4.0f) * (size * 4.0f));
		diagdiag =sqrt((size * 6.0f) * (size * 6.0f) + (size * 2.0f) * (size * 2.0f));

		lsr = new Laser(body[1].position, body[1].position - body[0].position, 100, 175);
		lsr->inf = true;

		lsr->time = 0;
		lsr->maxtime = 1;
		lsr->width = size * 3.0f;
		lsr->body.Damage = 0;
		lsr->body.Heat = 0;
		lsr->body.recoil = 0;
		lsr->body.singleHit = false;
		lsr->fraction = body[0].id;
		lsr->color = glm::vec4(100.0f,1.0f,0.0f,1.0f);
	}


	void Process(float dt) override
	{
		ProcessBody(dt);
		for (int i = 0; i < bodysize; i++)
		{
			body[i].color = color;
			body[i].Process(dt);
			body[i].Force = glm::vec2(0.0f);
		}

		SpringBetweenBalls(&body[0], &body[5], body[0].r * 6.0f,500.0f,0.5f);
		Rope(&body[0], &body[5], body[0].r * 6.0f);
		if (!debris)
		{
			float t = 0.0f;
			if (body[0].temperature > 10.0f)
				t = (body[0].temperature - 10.0f) / (MaxTemp - 10.0f);

			ScreenShake += body[1].r * recoil * 0.00001f * t;

			lsr->time = t;
			lsr->maxtime = 1.0f;
			lsr->body.Damage = t * dmg * dt;
			lsr->body.Heat = t * HeatPerShot * dt;
			lsr->body.recoil = t * recoil * dt;
			lsr->fraction = body[0].id;
			lsr->RayCast.direction = Rotate(Normalize(body[5].position - body[4].position), pi * 0.5f);
			lsr->RayCast.position = body[5].position + lsr->RayCast.direction * 2.0f;
			ChromaticStrength += body[1].r * recoil * 0.00001f * t;
			body[0].Force -= t * recoil * Normalize(body[1].position - body[0].position) * 1000.1f * dt;
			body[5].Force -= t * recoil * Normalize(body[1].position - body[0].position) * 1000.1f * dt;

			if (!debris && t > 0.0f)
				LaserPtrs.push_back(lsr);


		

			if (t > 0.0f )
			{
				if (source == 0)
				{
					GenSource(&source);
					SetSourceSound(&source, &LaserGunSound);
					SetSourceLooping(&source, true);
					PlaySource(&source);
				}

				SetSourceVelocity(&source, glm::vec3(body[0].velocity, 1.0f));
				SetSourcePosition(&source, glm::vec3(body[5].position, 0.0f));
				SetSourcePitch(&source, t * freq);
				SetSourceGain(&source, t * (freq <= 0.001f ? 0.0f : 1.0f));
			}
			else if (SourcePlaying(&source))
			{
				if (&source != 0) {
					StopSource(&source);
					DeleteSource(&source);
				}
			}
			float pos = length(body[0].position - body[5].position) / 3.0f;

			float dif = prevpos - pos;

			body[0].temperature = (body[0].temperature - MinTemp) * (1.0f + dif) + MinTemp;

			prevpos = pos;
		}


		Strut(&body[1], &body[2], body[1].r * 2.0f);
		Strut(&body[2], &body[3], body[1].r * 2.0f);
		Strut(&body[3], &body[4], body[1].r * 2.0f);
		Strut(&body[4], &body[5], body[1].r * 2.0f);
		Strut(&body[5], &body[6], body[1].r * 2.0f);
		Strut(&body[6], &body[7], body[1].r * 2.0f);
		Strut(&body[7], &body[8], body[1].r * 2.0f);
		Strut(&body[8], &body[9], body[1].r * 2.0f);

		Strut(&body[9], &body[1], body[1].r * 4.0f);
		Strut(&body[8], &body[2], body[1].r * 4.0f);
		Strut(&body[7], &body[3], body[1].r * 4.0f);
		Strut(&body[6], &body[4], body[1].r * 4.0f);


		Strut(&body[3], &body[5], midmiddiag);
		Strut(&body[7], &body[5], midmiddiag);

		Strut(&body[2], &body[5], middiag);
		Strut(&body[8], &body[5], middiag);

		Strut(&body[8], &body[4], diag);
		Strut(&body[2], &body[6], diag);

		Strut(&body[9], &body[5], diagdiag);
		Strut(&body[1], &body[5], diagdiag);
	}

	void Draw(int Z_Index = 5) override
	{
		DrawCircle(body[0], glm::vec4(0.5f, 0.5f, 0.5f,1.0f), true, BallNormalMapTexture, Z_Index);

		for (int i = 1; i < bodysize; i++)
			DrawCircle(body[i], color, true, BallNormalMapTexture, Z_Index);
	}

	void Delete() override
	{
		DeleteBody();
		StopSource(&source);
		DeleteSource(&source);
	}
};

class StaticPoint : public BodyComponent
{
public:
	//HEAT related stuff
	glm::vec2 position;

	void Ready(glm::vec2 position, glm::vec2 direction, float size, float mass = 1.0f) override
	{

		partid = PART::STATICPOINT;
		type = TYPE::STRUCTUREPART;

		CreateBody(1);
		body[0].r = 10;
		body[0].position = position;
		this->position = position;

		body[0].roughness = 0.0f;
		body[0].bounciness = 0.0f;
	}

	void Process(float dt) override
	{
		ProcessBody(dt);
		body[0].position = position;
		body[0].velocity = { 0.0f,0.0f };
		body[0].Force = { 0.0f,0.0f };
		body[0].Process(dt);
		body[0].color = color;
	}
	void Draw(int Z_Index) override
	{
		DrawCircle(body[0], color, true, BallNormalMapTexture, Z_Index);
	}

	
	void Delete() override
	{
		DeleteBody();
	}
};

class CentralPart : public BodyComponent
{
public:
	//HEAT related stuff
	glm::vec2 midvel;
	void Ready(glm::vec2 position, glm::vec2 direction, float size,float mass = 1.0f) override
	{

		partid = PART::CENTRALPART;
		type = TYPE::STRUCTUREPART;

		CreateBody(2,5,0,1);

		body[0].position = position + Normalize(direction) * size;
		body[1].position = position - Normalize(direction) * size;
		body[0].r = size;
		body[1].r = size;
		body[1].mass = mass;

		ProcessConnections();

	}
	void ProcessConnections()
	{
		bDataConnections[0].name = "LMB";
		bDataConnections[1].name = "RMB";
		bDataConnections[2].name = "MMB";
		bDataConnections[3].name = "Shift";
		bDataConnections[4].name = "Space";

		vDataConnections[0].name = "MousePosition";
		bDataConnections[0].source = true;
		bDataConnections[1].source = true;
		bDataConnections[2].source = true;
		bDataConnections[3].source = true;
		bDataConnections[4].source = true;

		vDataConnections[0].source = true;
	}
	void Process(float dt) override
	{
		ProcessConnections();
		ProcessBody(dt);
		body[0].color = color;
		body[1].color = color;

		mid = 0.5f * (body[0].position + body[1].position);
		midvel = 0.5f * (body[0].velocity + body[1].velocity);
		dir = (body[1].position - body[0].position);

		body[0].Process(dt);
		body[1].Process(dt);
		body[1].Force = glm::vec2(0.0f);
		body[0].Force = glm::vec2(0.0f);
		Strut(&body[0], &body[1], body[0].r * 2.0f);

		if (!enemy)
		{
			bDataConnections[0].data = buttons[GLFW_MOUSE_BUTTON_1];
			bDataConnections[1].data = buttons[GLFW_MOUSE_BUTTON_2];
			bDataConnections[2].data = buttons[GLFW_MOUSE_BUTTON_3];
			bDataConnections[3].data = keys[GLFW_KEY_LEFT_SHIFT] || keys[GLFW_KEY_RIGHT_SHIFT];
			bDataConnections[4].data = keys[GLFW_KEY_SPACE];
			vDataConnections[0].data = MousePosition;
		}


		if (BuildingMode || bLogicMode || fLogicMode || vLogicMode)
		{
			bDataConnections[0].data = false;
			bDataConnections[1].data = false;
			bDataConnections[2].data = false;
			bDataConnections[3].data = false;
			bDataConnections[4].data = false;

			vDataConnections[0].data = mid;

		}

	}

	void Draw(int Z_Index = 5) override
	{
		glm::vec2 dif = body[0].position - body[1].position;
		DrawLine(body[0].position + dif*0.5f, body[1].position - dif * 0.5f, body[0].r, color, true, CubeNormalMapTexture, Z_Index);
		

		//DrawTexturedQuad(mid, glm::vec2(1.0f * body[1].r, 2.0f * body[1].r), RadiatorTexture, glm::vec3(0.0f, 0.0f, get_angle_between_points(mid, body[0].position)), Base.color, Z_Index, CubeNormalMapTexture);
		
		
	}

	
	
	void Delete() override
	{
		DeleteBody();
	}
};

void FillSpawnableParts()
{

	//SpawnableParts.push_back(new BallBody());
	//SpawnableParts.push_back(new RocketEngine());
	//SpawnableParts.push_back(new Gun());
	//SpawnableParts.push_back(new LaserGun());
	//SpawnableParts.push_back(new Radiator());
	//SpawnableParts.push_back(new StaticPoint());
	//SpawnableParts.push_back(new CentralPart());
	//SpawnableParts.push_back(new RocketLauncher());
}


BodyComponent* CreatePart(int type, glm::vec2 position, glm::vec2 direction, float size, float mass = 1.0f)
{
	BodyComponent* b=NULL;
	if (type == PART::BALLBODY) 
	{
		BallBody* bb = new BallBody();
		bb->Ready(position, glm::vec2(0.0f, 1.0f), size);
		b = bb;
	}

	else if (type == PART::ROCKETENGINE) 
	{
		RocketEngine* bb = new RocketEngine();
		bb->Ready(position, glm::vec2(0.0f, 1.0f), size);
		b = bb;
	}

	else if (type == PART::GUN) 
	{
		Gun* bb = new Gun();
		bb->Ready(position, glm::vec2(0.0f, 1.0f), size);
		b = bb;
	}

	else if (type == PART::LASERGUN) 
	{
		LaserGun* bb = new LaserGun();
		bb->Ready(position, glm::vec2(0.0f, 1.0f), size);
		b = bb;
	}

	else if (type == PART::STATICPOINT) 
	{

		StaticPoint* bb = new StaticPoint();
		bb->Ready(position, glm::vec2(0.0f, 1.0f), size);
		b = bb;
	}

	else if (type == PART::RADIATOR) 
	{

		Radiator* bb = new Radiator();
		bb->Ready(position, glm::vec2(0.0f, 1.0f), size);
		b = bb;
	}
	else if (type == PART::ROTOR) 
	{

		Rotor* bb = new Rotor();
		bb->Ready(position, glm::vec2(0.0f, 1.0f), size);
		b = bb;
	}
	else if (type == PART::CRYOCOOLLER) 
	{

		CryoCooller* bb = new CryoCooller();
		bb->Ready(position, glm::vec2(0.0f, 1.0f), size);
		b = bb;
	}
	else if (type == PART::ROCKETLAUNCHER)
	{

		RocketLauncher* bb = new RocketLauncher();
		bb->Ready(position, glm::vec2(0.0f, 1.0f), size);
		b = bb;
	}
	else if (type == PART::MINIGUN)
	{

		MiniGun* bb = new MiniGun();
		bb->Ready(position, glm::vec2(0.0f, 1.0f), size);
		b = bb;
	}
	return b;

}