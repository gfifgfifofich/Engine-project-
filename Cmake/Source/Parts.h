#pragma once


struct CostMaterial
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





enum CONNECTION
{
	STRUT = 0,
	SPRING = 1,
	HEATPIPE = 2,
	ROPE = 3
};
enum TYPE
{
	STRUCTUREPART = 0,
	WEAPON = 1,
	PROPULSION = 2
};

enum PART
{
	BALLBODY = 0,
	ROCKETENGINE =1,
	GUN =2,
	LASERGUN =3,
	RADIATOR =4,
	ROTOR =5,
	ROCKETLAUNCHER =6,
	MINIGUN =7,
	RAILGUN =8,
	STATICPOINT  =9,
	CENTRALPART  =10,
	LASTPART
};

#define SpawnablePartAmount 9-1
DataStorage PartsData;
class BodyComponent : public Node
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
	std::vector<int> BodyIdsWithCollision;
	int bodysize = 1;
	float freq = 1.0f;
	unsigned int source = 0.0f;
	int parttype = TYPE::STRUCTUREPART;
	int partid = -1;
	int id = 0;
	bool player=false;

	bool dead = false;
	bool debris = false;
	bool deactivated = false;

	bool attached = false;



	float Health = 1.0f;
	float maxHealth = 1.0f;

	

	float throtle = 0.0f;

	bool shot = false;
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
	glm::vec4 HeatColor = glm::vec4(60.0f,10.0f,2.0f,0.0f);
	glm::vec4 ColdColor = glm::vec4(0.04f,2.0f,10.0f,0.0f);
	glm::vec4 color = glm::vec4(1.0f);

	glm::vec2 targetrotpoint;
	glm::vec2 dir = {0.0f,1.0f};
	glm::vec2 mid;


	CostMaterial Cost;
	CostMaterial Contains;
	void OnPartCreate()
	{
		GameScene->Nodes.push_back(this);
	}

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

		if (reloadSources)
		{
			if (source != NULL)
			{
				StopSource(&source);
				DeleteSource(&source);
			}
			GenSoundSource();
		}
	}

	virtual void Create(glm::vec2 position, glm::vec2 direction, float size, float mass = 1.0f) {}
	virtual void GenSoundSource(){}
	virtual void DeletePart(){}

	virtual ~BodyComponent() override
	{
		DeletePart();
	}

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
					UI_DrawTextOnPlate(bDataConnections[i].name, ScreenMousePosition, TextSize, glm::vec4(1.0f, 0.5f, 0.0f, 0.5f) * 3.0f, glm::vec4(0.0f, 0.0f, 0.0f, 0.9f), 1200, false);

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

					UI_DrawTextOnPlate(fDataConnections[i].name, ScreenMousePosition, TextSize, glm::vec4(1.0f, 0.5f, 0.5f, 0.5f) * 3.0f, glm::vec4(0.0f, 0.0f, 0.0f, 0.9f), 1200, false);

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
					UI_DrawTextOnPlate(vDataConnections[i].name, ScreenMousePosition, TextSize, glm::vec4(1.0f, 0.5f, 0.5f, 0.5f) * 3.0f, glm::vec4(0.0f, 0.0f, 0.0f, 0.9f), 1200, false);

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
		if (!DS->dead && (DS->id != id || DS->neutral || debris))
		{
			bool hit = false;
			for (int i = 0; i < bodysize; i++)
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
		
		delete[] body;
		if(bDCsize>0)
			delete[] bDataConnections;
		if (fDCsize > 0)
			delete[] fDataConnections;
		if (vDCsize > 0)
			delete[] vDataConnections;
	}

};

ParticleEmiter DebrieParticles;
float DrawingDistance = (WIDTH * 1.0f) / CameraScale.x;
class PartsPile
{
public:

	std::vector<BodyComponent*> Parts;

	std::vector<DamageSphere*> CloseDamageSpheres;

	void Process(float dt, int iter,bool lastiter);
	void DeletePart(int  index);

	void SpawnPart(int type, glm::vec2 position, float size = 20.0f);
	void SpawnRandomPart( glm::vec2 position, float size = 20.0f);

};
PartsPile Debris;

std::vector<BodyComponent*> SpawnableParts;

// guns
ParticleEmiter GunRoundPE;
ParticleEmiter GunShotPE;
class Gun : public BodyComponent
{
public:
	//HEAT related stuff
	float HeatPerShot = 1.0f;
	float BulletHeat = 1.0f;




	float TargetAngle = 0.0f;

	float speed = 500.0f;

	bool overheated = false;

	float RotationalFriction = 50.5f;

	float bulletSpeed = 150.0f;
	float dmg = 0.2f;
	float bulletSize = 50.0f;
	float recoil = 600.0f * 0.025f;

	float t = 1.0f;
	float shootspeed = 0.2f;



	glm::vec2 prevtrgpos = { 0.0f,0.0f };

	Gun()
	{
		partid = PART::GUN;
		parttype = TYPE::WEAPON;
		type = parttype + NodeType::LASTNODE;
		Name = "Gun";

		CreateBody(3,1,0,1);
		body[0].position = position;
		body[1].position = position + glm::vec2(0.0f,1.0f) * 3.0f;
		body[2].position = position + glm::vec2(0.0f,1.0f) * 3.0f;
		body[0].r = PARTSIZE;
		body[1].r = PARTSIZE*0.75;
		body[2].r = PARTSIZE;
		deactivated = true;

		body[0].mass = 1.0f;
		body[1].mass = 1.0f*0.2f;
		body[2].mass = 1.0f;


		Health = PartsData.GetPropertyAsFloat("Gun", "Health");

		HeatPerShot = PartsData.GetPropertyAsFloat("Gun", "HeatPerShot");
		dmg = PartsData.GetPropertyAsFloat("Gun", "Damage");
		BulletHeat = PartsData.GetPropertyAsFloat("Gun", "BulletHeat");
		bulletSpeed = PartsData.GetPropertyAsFloat("Gun", "BulletSpeed");
		shootspeed = PartsData.GetPropertyAsFloat("Gun", "FireRate");
		recoil = PartsData.GetPropertyAsFloat("Gun", "Recoil");
		bulletSize = PartsData.GetPropertyAsFloat("Gun", "BulletSize");
		BodyIdsWithCollision.push_back(0);
		BodyIdsWithCollision.push_back(2);
		shutdownTemp = 15.0f;
		OnPartCreate();
	}

	void Create(glm::vec2 position, glm::vec2 direction, float size, float mass = 1.0f) override
	{
		body[0].position = position;
		body[1].position = position + direction * 3.0f;
		body[2].position = position + direction * 3.0f;
		body[0].r = size;
		body[1].r = size*0.75;
		body[2].r = size;
		deactivated = true;

		body[0].mass = mass;
		body[1].mass = mass*0.2f;
		body[2].mass = mass;
		Health = PartsData.GetPropertyAsFloat("Gun", "Health");

		HeatPerShot = PartsData.GetPropertyAsFloat("Gun", "HeatPerShot");
		dmg = PartsData.GetPropertyAsFloat("Gun", "Damage");
		BulletHeat = PartsData.GetPropertyAsFloat("Gun", "BulletHeat");
		bulletSpeed = PartsData.GetPropertyAsFloat("Gun", "BulletSpeed");
		shootspeed = PartsData.GetPropertyAsFloat("Gun", "FireRate");
		recoil = PartsData.GetPropertyAsFloat("Gun", "Recoil");
		bulletSize = PartsData.GetPropertyAsFloat("Gun", "BulletSize");
		shutdownTemp = 15.0f;
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
	void MTProcess(float dt) override
	{
		ProcessConnections();
		ProcessBody(dt);
		body[0].color = color;
		body[1].color = color;
		body[2].color = color;

		glm::vec2 mid = (body[0].position + body[2].position) * 0.5f;
		if (body[1].temperature >= shutdownTemp)
			overheated = true;
		if (body[1].temperature <= 0.25f)
			overheated = false;
		shot = bDataConnections[0].data && bDataConnections[0].connected;
		if (!debris && !overheated)
		{
			targetrotpoint = vDataConnections[0].data;



			if (!deactivated)
			{
				targetrotpoint = vDataConnections[0].data;
				glm::vec2 dif = body[1].position - body[0].position;
				glm::vec2 trgvel = (targetrotpoint - prevtrgpos) * (1.0f / dt);
				glm::vec2 trgvec = targetrotpoint - body[0].position;
				glm::vec2 rotvec = Normalize(glm::vec2(-dif.y, dif.x));

				float D = length(trgvec);
				float T = D / bulletSpeed;
				float lastT = 0;
				for (int i = 0; i < 3; i++)
				{
					targetrotpoint += trgvel * (T - lastT);
					lastT = T;
					trgvec = targetrotpoint - body[0].position;
					D = length(trgvec);
					T = D / bulletSpeed;
				}
				trgvec = trgvec / D;
				body[1].velocity -= dt * RotationalFriction * DOT(body[1].velocity - body[0].velocity, rotvec) * rotvec;

				body[1].Force += speed * rotvec * DOT(rotvec, trgvec);
				prevtrgpos = vDataConnections[0].data;
			}

		}
		glm::vec2 posdif = body[1].position - body[0].position;

		glm::vec2 norm = Normalize(posdif);

		glm::vec2 Difference = posdif - norm * body[0].r * 3.0f;



		body[0].position += Difference * 0.5f;
		body[1].position += -Difference * 0.5f;

		glm::vec2  velbuf = body[0].velocity;

		body[1].velocity -= DOT(body[1].velocity - velbuf, norm) * norm;

		Strut(&body[0], &body[2], body[0].r * 2.0f);


		body[0].Process(dt);
		body[1].Process(dt);
		body[2].Process(dt);
		body[1].Force = { 0.0f,0.0f };
		body[0].Force = { 0.0f,0.0f };
		body[2].Force = { 0.0f,0.0f };

		float change = ((body[0].temperature + body[2].temperature)*0.5f- body[1].temperature);

		body[0].temperature -= change*0.5f;
		body[2].temperature -= change*0.5f;
		body[1].temperature += change;
	}
	void Process(float dt) override
	{


		if (source != 0) {
			SetSourcePosition(&source, glm::vec3(body[1].position, 0.0f));
			SetSourceVelocity(&source, glm::vec3(body[0].velocity, 1.0f));
		}
		if (!debris && !overheated)
		{
			t -= dt;
			if (shot && t <= 0)
				Shoot();
		}
	}

	void Shoot()
	{
		if (body[1].temperature < shutdownTemp)
		{
			t= shootspeed;

			glm::vec2 dir = Normalize(body[1].position - body[0].position);

			for (int i = 0; i < 15; i++)
				GunShotPE.Spawn(body[1].position + dir * body[0].r * -1.0f + dir * (rand() % 1000 * 0.002f * body[0].r), dir * 500.0f * 0.025f, 1);

			for (int i = 0; i < 10; i++)
				GunShotPE.Spawn(body[1].position + dir * body[0].r * -0.9f + Rotate(dir * (rand() % 1000 * 0.0015f * body[0].r), -pi * 0.7f), Rotate(dir * 500.0f, -pi * 0.7f) * 0.025f, 1);
			for (int i = 0; i < 10; i++)
				GunShotPE.Spawn(body[1].position + dir * body[0].r * -0.8f + Rotate(dir * (rand() % 1000 * 0.0015f * body[0].r), pi * 0.7f), Rotate(dir * 500.0f, pi * 0.7f) * 0.025f, 1);
			
			SpawnBullet(body[1].position, bulletSpeed * Normalize(body[1].position - body[0].position), dmg, body[1].r * 0.5f, BulletHeat, recoil, id);



			body[1].temperature += HeatPerShot;
			PlaySound(&source, &GunSound, body[1].position, (1.0f + rand() % 10 * 0.04f - 0.2f) * freq, freq <= 0.001f ? 0.0f : 1.0f);


			ScreenShake += body[1].r * bulletSpeed * 0.000001f;
			ChromaticAbberation += body[1].r * bulletSpeed * 0.000001f;

			body[0].Force -= recoil * Normalize(body[1].position - body[0].position) * 2000.0f;

			//body[1].Force -= recoil * Normalize(body[1].position - body[0].position) * 1000.0f;
		}
	}

	void Draw() override
	{
		//DrawLine(body[0].position, body[1].position, body[1].r, Base.color, true, CubeNormalMapTexture, Z_Index+1);
		
		glm::vec2 mid = (body[1].position + body[0].position) * 0.5f;
		//GunTexture
		DrawTexturedQuad(mid, glm::vec2(0.5f * body[1].r, 2.0f * body[1].r), GunTexture, get_angle_between_points(body[0].position,mid), color, Z_Index+2, GunNormalMap);
		//DrawTexturedQuad(body[0].position, glm::vec2(body[0].r), GunBaseTexture, 0.0f, color, Z_Index+1, GunBaseNormalMap);
		mid = (body[2].position + body[0].position) * 0.5f; 
		DrawTexturedQuad(mid, glm::vec2(1.0f * body[2].r, 2.0f * body[2].r), GunBaseTexture, get_angle_between_points(body[0].position, mid), color, Z_Index, GunBaseNormalMap);

	}

	void DeletePart() override
	{
		Delete = true;
		DeleteBody();
	}

};

class LaserGun : public BodyComponent
{
	float diaglength = 0.0f;
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
	LaserGun()
	{
		
		partid = PART::LASERGUN;
		parttype = TYPE::WEAPON;
		type = parttype + NodeType::LASTNODE;
		Name = "LaserGun";
		CreateBody(5, 1, 0, 1);
		float ang = 0.25f * pi;
		body[0].position = position + Rotate({0.0f,1.0f}, ang);
		body[0].r = PARTSIZE;
		body[0].mass = 1.0f;

		ang += pi * 0.5;
		body[2].position = position + Rotate({0.0f,1.0f}, ang);
		body[2].r = PARTSIZE;
		body[2].mass = 1.0f;

		ang += pi * 0.5;
		body[3].position = position + Rotate({0.0f,1.0f}, ang);
		body[3].r = PARTSIZE;
		body[3].mass = 1.0f;

		ang += pi * 0.5;
		body[4].position = position + Rotate({0.0f,1.0f}, ang);
		body[4].r = PARTSIZE;
		body[4].mass = 1.0f;

		body[1].position = position + glm::vec2(0.0f,1.0f) * 3.0f;
		body[1].r =  PARTSIZE * 0.75f;
		body[1].mass = 0.75f;

		diaglength = sqrt(body[0].r * 2.0f * body[0].r * 2.0f + body[0].r * 2.0f * body[0].r * 2.0f);

		deactivated = true;
		lsr = new Laser(body[1].position, body[1].position - body[0].position,150,175);
		lsr->inf = true;

		lsr->time = 0;
		lsr->maxtime = 1;
		lsr->width = PARTSIZE * 0.75f;
		lsr->body.Damage = 0;
		lsr->body.Heat = 0;
		lsr->body.recoil = 0;
		lsr->body.singleHit = false;
		lsr->fraction = body[0].id;


		Health = PartsData.GetPropertyAsFloat("LaserGun", "Health");
		HeatPerShot = PartsData.GetPropertyAsFloat("LaserGun", "HeatPerShot");
		dmg = PartsData.GetPropertyAsFloat("LaserGun", "Damage");
		BulletHeat = PartsData.GetPropertyAsFloat("LaserGun", "LaserHeat");
		recoil = PartsData.GetPropertyAsFloat("LaserGun", "Recoil");
		bulletSize = PartsData.GetPropertyAsFloat("LaserGun", "BulletSize");



		BodyIdsWithCollision.clear();
		BodyIdsWithCollision.push_back(0);
		BodyIdsWithCollision.push_back(2);
		BodyIdsWithCollision.push_back(3);
		BodyIdsWithCollision.push_back(4);

		ProcessConnections();
		OnPartCreate();
	}
	void Create(glm::vec2 position, glm::vec2 direction, float size, float mass = 1.0f) override
	{
		float ang = 0.25f*pi;
		body[0].position = position + Rotate(direction, ang);
		body[0].r = size;
		body[0].mass = mass ;

		ang +=pi*0.5;
		body[2].position = position + Rotate(direction, ang);
		body[2].r = size;
		body[2].mass = mass;

		ang += pi * 0.5;
		body[3].position = position + Rotate(direction, ang);
		body[3].r = size;
		body[3].mass = mass;

		ang += pi * 0.5;
		body[4].position = position + Rotate(direction, ang);
		body[4].r = size;
		body[4].mass = mass;

		diaglength = sqrt(body[0].r * 2.0f * body[0].r * 2.0f + body[0].r * 2.0f * body[0].r * 2.0f);

		deactivated = true;
		body[1].position = position + direction*3.0f;
		body[1].r = size*0.75f;
		body[1].mass = mass * 0.2f;
		lsr = new Laser(body[1].position, body[1].position - body[0].position,150,175);
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

		Health = PartsData.GetPropertyAsFloat("LaserGun", "Health");
		HeatPerShot = PartsData.GetPropertyAsFloat("LaserGun", "HeatPerShot");
		dmg = PartsData.GetPropertyAsFloat("LaserGun", "Damage");
		BulletHeat = PartsData.GetPropertyAsFloat("LaserGun", "LaserHeat");
		recoil = PartsData.GetPropertyAsFloat("LaserGun", "Recoil");
		bulletSize = PartsData.GetPropertyAsFloat("LaserGun", "BulletSize");



		BodyIdsWithCollision.clear();
		BodyIdsWithCollision.push_back(0);
		BodyIdsWithCollision.push_back(2);
		BodyIdsWithCollision.push_back(3);
		BodyIdsWithCollision.push_back(4);

		ProcessConnections();
	}
	void ProcessConnections()
	{
		bDataConnections[0].name = "Shoot";
		vDataConnections[0].name = "Target";
		vDataConnections[0].source = false;
		bDataConnections[0].source = false;

	}
	void MTProcess(float dt) override
	{

		ProcessConnections();
		ProcessBody(dt);
		body[0].color = color;
		body[1].color = color;
		body[2].color = color;
		body[3].color = color;
		body[4].color = color;
		
		if (!debris)
		{

			lsr->time = t;
			lsr->maxtime = 1.0f;
			lsr->body.Damage = t * dmg * dt;
			lsr->body.Heat = t * HeatPerShot * dt;
			lsr->body.recoil = t * recoil * dt;
			lsr->body.body.r = 2.0f;
			ChromaticAbberation += body[1].r * recoil * 0.00001f * t;
			glm::vec2 rec = t * recoil * Normalize(body[1].position - body[0].position) * 1000.1f * dt * 0.25f;

			body[0].Force -= rec;
			body[2].Force -= rec;
			body[3].Force -= rec;
			body[4].Force -= rec;

			body[1].Force -= t * recoil * Normalize(body[1].position - body[0].position) * 1000.1f * dt;




			if (!deactivated)
			{

				targetrotpoint = vDataConnections[0].data;
				glm::vec2 dif = body[1].position - mid;
				//glm::vec2 trgvel = (targetrotpoint - prevtrgpos) * (1.0f / dt);
				glm::vec2 trgvec = targetrotpoint - mid;
				glm::vec2 rotvec = Normalize(glm::vec2(-dif.y, dif.x));

				float D = length(trgvec);
				/*float T = D / bulletSpeed;
				float lastT = 0;
				for (int i = 0; i < 3; i++)
				{
					targetrotpoint += trgvel * (T - lastT);
					lastT = T;
					trgvec = targetrotpoint - body[0].position;
					D = length(trgvec);
					T = D / bulletSpeed;
				}*/
				trgvec = trgvec / D;
				body[1].velocity -= dt * RotationalFriction * DOT(body[1].velocity - body[0].velocity, rotvec) * rotvec;

				body[1].Force += speed * rotvec * DOT(rotvec, trgvec);
				//prevtrgpos = vDataConnections[0].data;
			}

		}
		mid = (body[0].position + body[2].position + body[3].position + body[4].position) * 0.25f;

		glm::vec2 posdif = body[1].position - mid;

		glm::vec2 norm = Normalize(posdif);

		lsr->RayCast.direction = norm;
		lsr->RayCast.position = body[1].position;

		glm::vec2 Difference = posdif - norm * body[0].r * 3.0f;



		body[0].position += Difference * 0.5f * 0.25f;
		body[2].position += Difference * 0.5f * 0.25f;
		body[3].position += Difference * 0.5f * 0.25f;
		body[4].position += Difference * 0.5f * 0.25f;
		body[1].position += -Difference * 0.5f;

		glm::vec2  velbuf = body[0].velocity;

		body[1].velocity -= DOT(body[1].velocity - velbuf, norm) * norm;

		body[0].Process(dt);
		body[1].Process(dt);
		body[2].Process(dt);
		body[3].Process(dt);
		body[4].Process(dt);

		body[0].Force = { 0.0f,0.0f };
		body[1].Force = { 0.0f,0.0f };
		body[2].Force = { 0.0f,0.0f };
		body[3].Force = { 0.0f,0.0f };
		body[4].Force = { 0.0f,0.0f };


		Strut(&body[0], &body[2], body[0].r*2.0f);
		Strut(&body[2], &body[3], body[0].r*2.0f);
		Strut(&body[3], &body[4], body[0].r*2.0f);
		Strut(&body[0], &body[4], body[0].r*2.0f);

		Strut(&body[0], &body[3], diaglength);
		Strut(&body[4], &body[2], diaglength);

		float change = ((body[0].temperature+ body[2].temperature + body[3].temperature + body[4].temperature)*0.25f - body[1].temperature);

		body[0].temperature -= change * 0.25f;
		body[2].temperature -= change * 0.25f;
		body[3].temperature -= change * 0.25f;
		body[4].temperature -= change * 0.25f;
		body[1].temperature += change;

	}
	void Process(float dt) override
	{


		if (!debris)
		{

			shot = bDataConnections[0].data && bDataConnections[0].connected;
			targetrotpoint = vDataConnections[0].data;

			lsr->fraction = body[0].id;


			lsr->body.id = id;


			Time -= dt;
			if (Time < 0.0f) Time = 0.0f;




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




			if (t > 0.0f)
				LaserPtrs.push_back(lsr);

			

		}
	
	}


	void Draw() override
	{


		mid = (body[0].position + body[2].position + body[3].position + body[4].position) * 0.25f;
		DrawTexturedQuad(mid, glm::vec2(0.5f * body[1].r, 4.0f * body[1].r), LaserGunTexture, get_angle_between_points(body[1].position, mid), color, Z_Index + 2, LaserGunNormalMap);
		DrawTexturedQuad(mid, glm::vec2(body[0].r*2.0f), GunBaseTexture, get_angle_between_points(body[0].position,mid) - pi*0.25f, color, Z_Index + 1, GunBaseNormalMap);
	}

	void DeletePart() override
	{
		Delete = true;
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



	float TargetAngle = 0.0f;

	float speed = 500.0f;


	float RotationalFriction = 50.5f;

	float bulletSpeed = 150.0f;
	float dmg = 0.02f;
	float bulletSize = 50.0f;
	float recoil = 600.0f * 0.025f;
	float ExplodionForce = 0.0f;
	float t = 1.0f;
	float shootspeed = 2.0f;
	std::vector<Rocket*> FiredRockets;
	Rocket HoldingRocket;
	RocketLauncher()
	{
		
		partid = PART::ROCKETLAUNCHER;
		parttype = TYPE::STRUCTUREPART;
		type = parttype + NodeType::LASTNODE;
		Name = "RocketLauncher";
		
		Health = PartsData.GetPropertyAsFloat("RocketLauncher", "Health");
		//HeatPerShot = PartsData.GetPropertyAsFloat("RocketLauncher", "HeatPerShot");
		dmg = PartsData.GetPropertyAsFloat("RocketLauncher", "Damage");
		ExplodionForce = PartsData.GetPropertyAsFloat("RocketLauncher", "ExlodionForce");
		//BulletHeat = PartsData.GetPropertyAsFloat("RocketLauncher", "RocketHeat");
		bulletSpeed = PartsData.GetPropertyAsFloat("RocketLauncher", "BulletSpeed");
		shootspeed = PartsData.GetPropertyAsFloat("RocketLauncher", "FireRate");
		recoil = PartsData.GetPropertyAsFloat("RocketLauncher", "Recoil");
		bulletSize = PartsData.GetPropertyAsFloat("RocketLauncher", "BulletSize");

		CreateBody(2, 1, 0, 1);
		body[0].position = position;
		body[1].position = position + glm::vec2(0.0f,1.0f) * 3.0f;
		body[0].r = PARTSIZE;
		body[1].r = PARTSIZE;
		deactivated = true;

		body[0].mass = 1.0f;
		body[1].mass = 1.0f;
		ProcessConnections();


		HoldingRocket.DS.Damage = dmg;
		HoldingRocket.DS.singleHit = true;

		HoldingRocket.body[0].position = body[1].position;
		HoldingRocket.body[1].position = body[1].position + dir * 3.0f * PARTSIZE * 0.5f;
		HoldingRocket.body[0].r = PARTSIZE * 0.4f;
		HoldingRocket.body[1].r = PARTSIZE * 0.4f;
		HoldingRocket.fired = false;
		HoldingRocket.dir = dir;
		HoldingRocket.timeLeft = 10.0f;
		HoldingRocket.ExplodionForce = ExplodionForce;
		HoldingRocket.lifet = 10.0f;
		BodyIdsWithCollision.push_back(0);
		BodyIdsWithCollision.push_back(1);
		OnPartCreate();
	}

	void Create(glm::vec2 position, glm::vec2 direction, float size, float mass = 1.0f) override
	{

		Health = PartsData.GetPropertyAsFloat("RocketLauncher", "Health");
		//HeatPerShot = PartsData.GetPropertyAsFloat("RocketLauncher", "HeatPerShot");
		dmg = PartsData.GetPropertyAsFloat("RocketLauncher", "Damage");
		ExplodionForce = PartsData.GetPropertyAsFloat("RocketLauncher", "ExlodionForce");
		//BulletHeat = PartsData.GetPropertyAsFloat("RocketLauncher", "RocketHeat");
		bulletSpeed = PartsData.GetPropertyAsFloat("RocketLauncher", "BulletSpeed");
		shootspeed = PartsData.GetPropertyAsFloat("RocketLauncher", "FireRate");
		recoil = PartsData.GetPropertyAsFloat("RocketLauncher", "Recoil");
		bulletSize = PartsData.GetPropertyAsFloat("RocketLauncher", "BulletSize");


		body[0].position = position;
		body[1].position = position + direction * 3.0f;
		body[0].r = size;
		body[1].r = size;
		deactivated = true;

		body[0].mass = mass;
		body[1].mass = mass;
		ProcessConnections();
		

		Cost.Steel = 20;
		Cost.Cu = 2;
		Cost.Al = 5;



		HoldingRocket.DS.Damage = dmg;
		HoldingRocket.DS.singleHit = true;

		HoldingRocket.body[0].position = body[1].position;
		HoldingRocket.body[1].position = body[1].position + dir * 3.0f * size * 0.5f;
		HoldingRocket.body[0].r = size * 0.4f;
		HoldingRocket.body[1].r = size * 0.4f;
		HoldingRocket.fired = false;
		HoldingRocket.dir = dir;
		HoldingRocket.timeLeft = 10.0f;
		HoldingRocket.ExplodionForce = ExplodionForce;
		HoldingRocket.lifet = 10.0f;


	}
	void ProcessConnections()
	{

		bDataConnections[0].name = "Shoot";
		vDataConnections[0].name = "Target";

		vDataConnections[0].source = false;
		bDataConnections[0].source = false;
	}
	
	void MTProcess (float dt) override
	{
		ProcessConnections();
		ProcessBody(dt);
		body[0].color = color;
		body[1].color = color;
		dir = Normalize(body[1].position - body[0].position);

		
		HoldingRocket.body[1].position = body[1].position ;
		HoldingRocket.body[0].position = body[1].position + dir * 2.0f * HoldingRocket.body[1].r;
		if (!debris)
		{
			if (t <= 0)
			{
				HoldingRocket.mid = (HoldingRocket.body[1].position + HoldingRocket.body[0].position) * 0.5f;
				HoldingRocket.midvel = (HoldingRocket.body[0].velocity + HoldingRocket.body[1].velocity) * 0.5f;
				HoldingRocket.dir = dir;
				HoldingRocket.ExplodionForce = ExplodionForce;
				HoldingRocket.body[0].Process(dt);
				HoldingRocket.body[1].Process(dt);
				Strut(&HoldingRocket.body[1], &HoldingRocket.body[0], HoldingRocket.body[1].r * 2.0f);
			}
		
			
			
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
	void Process(float dt) override
	{
		if (source == 0)
			GenSource(&source);
		SetSourcePosition(&source, glm::vec3(body[1].position, 0.0f));
		SetSourceVelocity(&source, glm::vec3(body[0].velocity, 1.0f));
		
		if (!debris)
		{
		
			
			for (int i = 0; i < FiredRockets.size(); i++)
			{
				FiredRockets[i]->target = targetrotpoint;
				FiredRockets[i]->fired = true;
				FiredRockets[i]->DS.id = id;
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
		else
		{
			for (int i = 0; i < FiredRockets.size(); i++)
			{
				FiredRockets[i]->Explode();
				FiredRockets[i]->DeleteSrc();
			}
			FiredRockets.clear();
		}

	}
	void Shoot()
	{
		t = shootspeed;


		for (int i = 0; i < 15; i++)
			GunShotPE.Spawn(body[1].position + dir * body[0].r * -1.0f + dir * (rand() % 1000 * 0.002f * body[0].r),
				dir * 500.0f * 0.025f, 1);

		Rocket* R = new Rocket();

		R->Init(HoldingRocket.body[0].position, HoldingRocket.dir, HoldingRocket.body[0].r, dmg, 10.0f);
		R->GenSrc();
		R->fired = true;
		R->body[0].velocity = dir * 100.0f + body[1].velocity;
		R->body[1].velocity = dir * 100.0f + body[1].velocity;
		R->ExplodionForce = ExplodionForce;
		FiredRockets.push_back(R);
		/*HoldingRocket.body[0].velocity = dir*1.0f;
		HoldingRocket.body[1].velocity = dir*1.0f;
		HoldingRocket.DS.enemy = enemy;
		HoldingRocket.DeleteSrc();*/



		//SpawnBullet(body[1].position, bulletSpeed * Normalize(body[1].position - body[0].position), dmg, body[1].r * 0.5f, BulletHeat, recoil, enemy);
		
		SetSourceGain(&source,(1.0f + rand() % 10 * 0.04f - 0.2f) * freq);
		SetSourcePitch(&source,freq <= 0.001f ? 0.0f : 1.0f);
		SetSourceSound(&source,&GunSound);
		PlaySource(&source);

		ScreenShake += body[1].r * bulletSpeed * 0.000001f;
		ChromaticAbberation += body[1].r * bulletSpeed * 0.000001f;

		body[0].Force -= recoil * Normalize(body[1].position - body[0].position) * 2000.0f;

		//body[1].Force -= recoil * Normalize(body[1].position - body[0].position) * 1000.0f;

	}

	void Draw() override
	{
		//DrawLine(body[0].position, body[1].position, body[1].r, Base.color, true, CubeNormalMapTexture, Z_Index+1);
		for (int i = 0; i < FiredRockets.size(); i++)
		{
			FiredRockets[i]->Draw();
		}
		glm::vec2 mid = (body[1].position + body[0].position) * 0.5f;
		//GunTexture
		DrawTexturedQuad(mid, glm::vec2(1.0f * body[1].r, 2.0f * body[1].r), RocketLauncherTexture, get_angle_between_points(body[0].position, mid), color, Z_Index, RocketLauncherNormalMap);
		//DrawTexturedQuad(mid, glm::vec2(1.0f * body[1].r, 2.0f * body[1].r), RocketEngineTexture, get_angle_between_points(body[0].position, mid), color, Z_Index, RocketEngineNormalMap);

		//DrawCircle(body[0], glm::vec4(1.0f), true, BallNormalMapTexture, Z_Index);
		if (t <= 0)
			HoldingRocket.Draw();
	}

	void DeletePart() override
	{
		Delete = true;
		for (int i = 0; i < FiredRockets.size(); i++)
		{
			FiredRockets[i]->Explode();
			FiredRockets[i]->DeleteSrc();
		}
		FiredRockets.clear();
		DeleteBody();
	}

};

class MiniGun : public BodyComponent
{
	float diaglength = 0.0f;
public:
	//HEAT related stuff
	float HeatPerShot = 0.8f;
	float BulletHeat = 0.5f;


	glm::vec2 prevtrgpos;
	float speed = 500.0f;


	float RotationalFriction = 50.5f;

	float bulletSpeed = 1000.0f;
	float dmg = 0.04f;
	float bulletSize = 50.0f;
	float recoil = 60.0f * 0.025f;

	float t = 0.0f;
	float shootspeed = 0.034f;

	bool overheated = false;

	float RotationSpeed = 0.0f;
	float BarrelRotation = 0.0f;
	MiniGun()
	{
		
		partid = PART::MINIGUN;
		parttype = TYPE::WEAPON;
		
		type = parttype + NodeType::LASTNODE;
		Name = "MiniGun";
		
		Health = PartsData.GetPropertyAsFloat("MiniGun", "Health");
		HeatPerShot = PartsData.GetPropertyAsFloat("MiniGun", "HeatPerShot");
		dmg = PartsData.GetPropertyAsFloat("MiniGun", "Damage");
		BulletHeat = PartsData.GetPropertyAsFloat("MiniGun", "BulletHeat");
		bulletSpeed = PartsData.GetPropertyAsFloat("MiniGun", "BulletSpeed");
		shootspeed = PartsData.GetPropertyAsFloat("MiniGun", "FireRate");
		recoil = PartsData.GetPropertyAsFloat("MiniGun", "Recoil");
		bulletSize = PartsData.GetPropertyAsFloat("MiniGun", "BulletSize");

		CreateBody(5, 1, 0, 1);
		float ang = 0.25f * pi;
		body[0].position = position + Rotate({0.0f,1.0f}, ang);
		body[0].r = PARTSIZE;
		body[0].mass = 1.0f;

		ang += pi * 0.5;
		body[2].position = position + Rotate({0.0f,1.0f}, ang);
		body[2].r = PARTSIZE;
		body[2].mass = 1.0f;

		ang += pi * 0.5;
		body[3].position = position + Rotate({0.0f,1.0f}, ang);
		body[3].r = PARTSIZE;
		body[3].mass = 1.0f;

		ang += pi * 0.5;
		body[4].position = position + Rotate({0.0f,1.0f}, ang);
		body[4].r = PARTSIZE;
		body[4].mass = 1.0f;

		body[1].position = position + glm::vec2(0.0f,1.0f) * 3.0f;
		body[1].r =  PARTSIZE * 0.75f;
		body[1].mass = 0.75f;

		deactivated = true;

		diaglength = sqrt(body[0].r * 2.0f * body[0].r * 2.0f + body[0].r * 2.0f * body[0].r * 2.0f);

		Cost.Steel = 25;
		Cost.Cu = 20;
		Cost.Al = 20;
		shutdownTemp = 15.0f;
		ProcessConnections();
		BodyIdsWithCollision.push_back(0);
		BodyIdsWithCollision.push_back(2);
		BodyIdsWithCollision.push_back(3);
		BodyIdsWithCollision.push_back(4);
		OnPartCreate();
	}
	void Create(glm::vec2 position, glm::vec2 direction, float size, float mass = 1.0f) override
	{

		Health = PartsData.GetPropertyAsFloat("MiniGun", "Health");
		HeatPerShot = PartsData.GetPropertyAsFloat("MiniGun", "HeatPerShot");
		dmg = PartsData.GetPropertyAsFloat("MiniGun", "Damage");
		BulletHeat = PartsData.GetPropertyAsFloat("MiniGun", "BulletHeat");
		bulletSpeed = PartsData.GetPropertyAsFloat("MiniGun", "BulletSpeed");
		shootspeed = PartsData.GetPropertyAsFloat("MiniGun", "FireRate");
		recoil = PartsData.GetPropertyAsFloat("MiniGun", "Recoil");
		bulletSize = PartsData.GetPropertyAsFloat("MiniGun", "BulletSize");

		float ang = 0.25f * pi;
		body[0].position = position + Rotate(direction, ang);
		body[0].r = size;
		body[0].mass = mass;

		ang += pi * 0.5;
		body[2].position = position + Rotate(direction, ang);
		body[2].r = size;
		body[2].mass = mass;

		ang += pi * 0.5;
		body[3].position = position + Rotate(direction, ang);
		body[3].r = size;
		body[3].mass = mass;

		ang += pi * 0.5;
		body[4].position = position + Rotate(direction, ang);
		body[4].r = size;
		body[4].mass = mass;

		body[1].position = position + direction * 3.0f;
		body[1].r = size * 0.75;
		body[1].mass = mass * 0.2f;

		deactivated = true;

		diaglength = sqrt(body[0].r * 2.0f * body[0].r * 2.0f + body[0].r * 2.0f * body[0].r * 2.0f);

		Cost.Steel = 25;
		Cost.Cu = 20;
		Cost.Al = 20;
		shutdownTemp = 15.0f;
		ProcessConnections();


		GenSoundSource();
		//PlaySource(&source);
	}
	void GenSoundSource() override
	{
		GenSource(&source);
		SetSourceSound(&source, &MiniGunSound);
		SetSourceLooping(&source, true);

		SetSourcePitch(&source, 1.0f);
		SetSourceGain(&source, 1.0f);
	}
	void ProcessConnections()
	{
		bDataConnections[0].name = "Shoot";
		vDataConnections[0].name = "Target";

		vDataConnections[0].source = false;
		bDataConnections[0].source = false;
	}
	
	void MTProcess(float dt) override
	{
		ProcessConnections();
		ProcessBody(dt);
		body[0].color = color;
		body[1].color = color;
		body[2].color = color;
		body[3].color = color;
		body[4].color = color;
		shot = bDataConnections[0].data && bDataConnections[0].connected;

		if (body[1].temperature >= shutdownTemp)
			overheated = true;
		if (body[1].temperature <= 0.25f)
			overheated = false;
		mid = (body[0].position + body[2].position + body[3].position + body[4].position) * 0.25f;
		if (!debris && !deactivated && !overheated)
		{
			targetrotpoint = vDataConnections[0].data;
			glm::vec2 dif = body[1].position - mid;
			glm::vec2 trgvel = (targetrotpoint - prevtrgpos) *(1.0f/dt);
			glm::vec2 trgvec = targetrotpoint - mid;
			glm::vec2 rotvec = Normalize(glm::vec2(-dif.y, dif.x));

			float D = length(trgvec);
			float T = D / bulletSpeed;
			float lastT = 0;
			for (int i = 0; i < 3; i++)
			{
				targetrotpoint += trgvel * (T- lastT) ;
				lastT = T;
				trgvec = targetrotpoint - mid;
				D = length(trgvec);
				T = D / bulletSpeed;
			}
			trgvec = trgvec / D;
			body[1].velocity -= dt * RotationalFriction * DOT(body[1].velocity - body[0].velocity, rotvec) * rotvec;

			body[1].Force += speed * rotvec * DOT(rotvec, trgvec);
			prevtrgpos = vDataConnections[0].data;

		}
		BarrelRotation += RotationSpeed * dt;
		RotationSpeed -= 60.0f*dt;
		if (RotationSpeed <= 0.0f)
			RotationSpeed = 0.0f;
		while (BarrelRotation > pi * 2.0f)
			BarrelRotation = 0.0f;
		glm::vec2 posdif = body[1].position - mid;

		dir = Normalize(posdif);

		glm::vec2 Difference = posdif - dir * body[0].r * 3.0f;



		body[0].position += Difference * 0.125f;
		body[2].position += Difference * 0.125f;
		body[3].position += Difference * 0.125f;
		body[4].position += Difference * 0.125f;

		body[1].position += -Difference * 0.5f;

		glm::vec2  velbuf = body[0].velocity;

		body[1].velocity -= DOT(body[1].velocity - velbuf, dir) * dir;

		body[0].Process(dt);
		body[1].Process(dt);
		body[2].Process(dt);
		body[3].Process(dt);
		body[4].Process(dt);

		body[1].Force = { 0.0f,0.0f };
		body[0].Force = { 0.0f,0.0f };
		body[2].Force = { 0.0f,0.0f };
		body[3].Force = { 0.0f,0.0f };
		body[4].Force = { 0.0f,0.0f };

		Strut(&body[0], &body[2], body[0].r * 2.0f);
		Strut(&body[2], &body[3], body[0].r * 2.0f);
		Strut(&body[3], &body[4], body[0].r * 2.0f);
		Strut(&body[0], &body[4], body[0].r * 2.0f);

		Strut(&body[0], &body[3], diaglength);
		Strut(&body[4], &body[2], diaglength);

	
		float change = ((body[0].temperature + body[2].temperature + body[3].temperature + body[4].temperature) * 0.25f - body[1].temperature);

		body[0].temperature -= change * 0.25f;
		body[2].temperature -= change * 0.25f;
		body[3].temperature -= change * 0.25f;
		body[4].temperature -= change * 0.25f;
		body[1].temperature += change;
	}
	void Process(float dt) override
	{
		if (source != 0) {
			SetSourcePosition(&source, glm::vec3(body[1].position, 0.0f));
			SetSourceVelocity(&source, glm::vec3(body[0].velocity, 1.0f));
		}
		
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

		}
		else if (SourcePlaying(&source))
			StopSource(&source);
	}


	void Shoot()
	{

		if (!deactivated)
		{
			t = shootspeed;
			RotationSpeed = 20.0f;

			dir = Normalize(body[1].position - mid);

			GunRoundPE.Spawn(mid + dir * body[0].r * 0.6f,
				Rotate(dir * 500.0f, pi * -0.5f) * 0.025f + body[0].velocity, 1);

			GunShotPE.Spawn(body[1].position + dir * body[0].r * -1.0f + dir * (rand() % 1000 * 0.002f * body[0].r),
				dir * 500.0f * 0.025f + body[0].velocity, 1);

			for (int i = 0; i < 2; i++)
				GunShotPE.Spawn(body[1].position + dir * body[0].r * -0.9f + Rotate(dir * (rand() % 1000 * 0.0015f * body[0].r), -pi * 0.7f),
					Rotate(dir * 500.0f, -pi * 0.7f) * 0.025f + body[0].velocity, 1);
			for (int i = 0; i < 2; i++)
				GunShotPE.Spawn(body[1].position + dir * body[0].r * -0.8f + Rotate(dir * (rand() % 1000 * 0.0015f * body[0].r), pi * 0.7f),
					Rotate(dir * 500.0f, pi * 0.7f) * 0.025f + body[0].velocity, 1);
			SpawnBullet(body[1].position, bulletSpeed * Normalize(body[1].position - mid), dmg, body[1].r * 0.2f, BulletHeat, recoil * 10.0f, id);


			body[1].temperature += HeatPerShot;
			//PlaySound(&source, &GunSound, body[1].position, (1.0f + rand() % 10 * 0.04f - 0.2f) * freq, freq <= 0.001f ? 0.0f : 1.0f);


			ScreenShake += body[1].r * bulletSpeed * 0.00001f;
			ChromaticAbberation += body[1].r * bulletSpeed * 0.000075f;

			body[0].Force -= recoil * Normalize(body[1].position - mid) * 2000.0f;

			//body[1].Force -= recoil * Normalize(body[1].position - body[0].position) * 1000.0f;
		}
	}

	void Draw() override
	{
		//DrawLine(body[0].position, body[1].position, body[1].r, Base.color, true, CubeNormalMapTexture, Z_Index+1);

		glm::vec2 mid2 = (body[1].position + mid) * 0.5f;
		//GunTexture
		DrawTexturedQuad(mid - dir* body[2].r*2.0f, glm::vec2(1.5f * body[1].r, 4.0f * body[1].r), MiniGunTexture, get_angle_between_points(mid2, mid), color, Z_Index + 5, MiniGunNormalMap);
		DrawTexturedQuad(mid, glm::vec2(body[0].r * 2.0f), GunBaseTexture, get_angle_between_points(body[0].position, body[3].position) + pi*0.25f, color, Z_Index + 1, GunBaseNormalMap,false);

		for (int i = 0; i < 6; i++)
		{
			float angle = i * pi * 0.3333f + BarrelRotation;

			glm::vec2 berrrelPos = Rotate(glm::vec2(1.0f, 0.0f), angle);

			int z = 0;

			if (berrrelPos.y > 0.0f && berrrelPos.y < 0.6f)
				z = 1;
			else
				if (berrrelPos.y >= 0.6)
					z = 2;
			if (berrrelPos.y < 0.0f && berrrelPos.y > -0.6f)
				z = -1;
			else
				if (berrrelPos.y <= -0.6)
					z = -2;

			;
			z += 2;
			DrawTexturedQuad(body[1].position + Rotate(dir, pi * 0.5f) * berrrelPos.x * body[1].r*0.6f, { body[1].r * 0.35f ,body[0].r * 3.8f }, PipeTexture, get_angle_between_points({ 0.0f,0.0f }, dir), color, z + Z_Index, PipeNormalMap);
		}
	}

	void DeletePart() override
	{
		Delete = true;
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


	float t = 0.0f;
	RocketEngine()
	{
		partid = PART::ROCKETENGINE;
		parttype = TYPE::PROPULSION;
		type = parttype + NodeType::LASTNODE;
		Name = "RocketEngine";
		
		Health = PartsData.GetPropertyAsFloat("RocketEngine", "Health");
		HeatPerSecond = PartsData.GetPropertyAsFloat("RocketEngine", "HeatPerSecond");
		Power = PartsData.GetPropertyAsFloat("RocketEngine", "Power");

		CreateBody(2,2);
		body[0].r = PARTSIZE;
		body[1].r = PARTSIZE;
		body[0].position = position + Normalize({0.0f,1.0f}) * PARTSIZE;
		body[1].position = position - Normalize({0.0f,1.0f}) * PARTSIZE;

		body[1].mass = 1.0f;
		body[0].mass= 1.0f;

		body[0].roughness = 0.0f;
		body[0].bounciness = 0.0f;
		body[1].roughness = 0.0f;
		body[1].bounciness = 0.0f;


		BodyIdsWithCollision.push_back(0);
		BodyIdsWithCollision.push_back(1);
		ProcessConnections();
		OnPartCreate();
	}
	void Create(glm::vec2 position, glm::vec2 direction, float size, float mass = 1.0f) override
	{
		

		Health = PartsData.GetPropertyAsFloat("RocketEngine", "Health");
		HeatPerSecond = PartsData.GetPropertyAsFloat("RocketEngine", "HeatPerSecond");
		Power = PartsData.GetPropertyAsFloat("RocketEngine", "Power");

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
		GenSoundSource();
	}
	void ProcessConnections()
	{
		bDataConnections[0].name = "Fire override";
		bDataConnections[0].source = false;
		bDataConnections[1].name = "Boost";
		bDataConnections[1].source = false;
	}
	void GenSoundSource() override
	{
		GenSource(&source);
		SetSourceSound(&source, &RocketEngineSound);
		SetSourceLooping(&source, true);
		SetSourceGain(&source, 0.0f);
	}
	
	void MTProcess (float dt) override
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
				
				body[1].Force += Power * -dir * throtle;
				body[0].Force += Power * -dir * throtle;


				glm::vec2 dir = Normalize(body[1].position - body[0].position);


				
				body[0].temperature += abs(throtle) * HeatPerSecond * dt;
				body[1].temperature += abs(throtle) * HeatPerSecond * dt;


			}
		}
		float change = (body[0].temperature - body[1].temperature);

		body[0].temperature -= change;
		body[1].temperature += change;

	}
	void Process(float dt) override
	{
		if (!debris )
		{
			if (abs(throtle) > 0.0f && !shutdown && !deactivated)
			{

				if (throtle > 1.0f)
					throtle = 1.0f;

				if (throtle < -1.0f)
					throtle = -1.0f;
			
				if ((bDataConnections[1].connected && bDataConnections[1].data))
				{
					throtle *= 2.5f;
				}
				if (source == 0)
				{
					GenSoundSource();
					SetSourceSound(&source, &RocketEngineSound);
					SetSourceLooping(&source, true);
				}
				else if (!SourcePlaying(&source))
					PlaySource(&source);
				SetSourcePitch(&source, freq);
				SetSourceGain(&source, throtle * 0.25f * (freq <= 0.001f ? 0.0f : 1.0f));
				
				SetSourceVelocity(&source, glm::vec3(body[0].velocity, 0.0f));
				SetSourcePosition(&source, glm::vec3((body[1].position + body[0].position) * 0.5f, 0.0f));
					
				


			}
			else
			{
				SetSourceGain(&source, 0.0f);
				if (SourcePlaying(&source))
					StopSource(&source);
				body[1].Force = { 0.0f,0.0f };
				body[0].Force = {0.0f,0.0f};
			}
		}
		else
		{
			SetSourceGain(&source, 0.0f);
			if (SourcePlaying(&source))
				StopSource(&source);
			body[1].Force = { 0.0f,0.0f };
			body[0].Force = {0.0f,0.0f};

		}
	}
	void Draw() override
	{
		if (abs(throtle) > 0.0f && !shutdown)
		{
			if ((bDataConnections[1].connected && bDataConnections[1].data))
			{
				throtle *= 1.5f;
			}
			if (freq > 0.001f)
			{
				t -= delta;
				if (t <= 0.0f)
				{
					t = 0.016f;

					
					for (int i = 0; i < 5; i++)
						EngineSmoke.Spawn(body[1].position + dir * body[0].r * -1.0f - dir * (rand() % 1000 * 0.002f * body[0].r),
							dir * 5000.0f * throtle * 0.025f, 1,
							EngineSmoke.lifetime * abs(throtle) * (rand() % 1000 * 0.0005f + 0.5f));
				}
			}
			glm::vec2 lp = (body[1].position + dir * body[0].r);
			DrawLight(glm::vec3(lp.x,lp.y, EngineLightHeight), glm::vec2( 800 * abs(throtle)*0.025f), glm::vec4(4.0f, 0.8f, 0.4f, abs(0.5f + abs(throtle) + (rand() % 100 - 50) * 0.01f)), 0.0f);
		}
		glm::vec2 mid = (body[1].position + body[0].position) * 0.5f;
		DrawTexturedQuad(mid,glm::vec2(1.0f * body[1].r,2.0f* body[1].r), RocketEngineTexture,  get_angle_between_points(mid, mid - dir),color, Z_Index,RocketEngineNormalMap);

		/*DrawLine(
			body[0].position - dir * body[0].r,
			body[1].position + dir * body[1].r,
			body[0].r,
			Base.color, true);*/
	}


	void DeletePart() override
	{
		Delete = true;
		DeleteBody();
		StopSource(&source);
		DeleteSource(&source);
	}
};


// structure
class BallBody : public BodyComponent
{
public:


	BallBody()
	{
		partid = PART::BALLBODY;
		parttype = TYPE::STRUCTUREPART;
		type = parttype + NodeType::LASTNODE;
		Name = "BallBody";

		Health = PartsData.GetPropertyAsFloat("BallBody", "Health");
		
		CreateBody(1);
		body[0].r = PARTSIZE;
		body[0].position = position;

		body[0].mass = 1.0f;

		body[0].roughness = 0.0f;
		body[0].bounciness = 0.0f;

		BodyIdsWithCollision.push_back(0);
		OnPartCreate();
	}

	void Create(glm::vec2 position, glm::vec2 direction, float size,float mass = 1.0f) override
	{
		Health = PartsData.GetPropertyAsFloat("BallBody", "Health");
		
		body[0].r = size;
		body[0].position = position;

		body[0].mass = mass;

		body[0].roughness = 0.0f;
		body[0].bounciness = 0.0f;
		Cost.Fe = 5;

	}
	
	void MTProcess (float dt) override
	{
		ProcessBody(dt);
		body[0].color = color;
		body[0].Process(dt);

		body[0].Force = glm::vec2(0.0f);
		
	}

	void Process(float dt) override
	{
	}
	void Draw() override
	{
		//DrawTexturedQuad(body[0].position, glm::vec2(body[0].r), BallBodyTexture, 0.0f, color, Z_Index + 1, BallBodyNormalMap);
		DrawCircle(body[0].position, body[0].r, color, true, BallNormalMapTexture, Z_Index);

	}

	void DeletePart() override
	{
		Delete = true;
		DeleteBody();
	}
};

class Rotor : public BodyComponent
{
	float diaglen = 0.0f;
public:


	//DamageSphere Sawdamagespheres[4];
	Rotor()
	{
		partid = PART::ROTOR;
		parttype = TYPE::STRUCTUREPART;
		type = parttype + NodeType::LASTNODE;
		Name = "Rotor";

		Health = PartsData.GetPropertyAsFloat("Rotor", "Health");
		
		CreateBody(5,2);
		for (int i = 0; i < 5; i++)
		{
			body[i].r = PARTSIZE;
			body[i].mass = 1.0f;

			body[i].roughness = 0.0f;
			body[i].bounciness = 0.0f;
		}
		body[0].position = position;
		body[1].position = position + glm::vec2(PARTSIZE * 2.0f, 0.0f);
		body[2].position = position + glm::vec2(0.0f, PARTSIZE * -2.0f);
		body[3].position = position + glm::vec2(PARTSIZE * -2.0f, 0.0f);
		body[4].position = position + glm::vec2(0.0f, PARTSIZE * 2.0f);
		diaglen = sqrt(((PARTSIZE*2.0f) * (PARTSIZE*2.0f)) * 2.0f);
		ProcessConnections();

		BodyIdsWithCollision.push_back(0);
		BodyIdsWithCollision.push_back(1);
		BodyIdsWithCollision.push_back(2);
		BodyIdsWithCollision.push_back(3);
		BodyIdsWithCollision.push_back(4);
		OnPartCreate();

	}
	void Create(glm::vec2 position, glm::vec2 direction, float size, float mass = 1.0f) override
	{
		Health = PartsData.GetPropertyAsFloat("Rotor", "Health");
		
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
	
	void MTProcess (float dt) override
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
	void Process(float dt) override
	{


	}
	void Draw() override
	{
		for (int i = 0; i < 5; i++)
		{
			DrawCircle(body[i], color, true, BallNormalMapTexture, Z_Index);
		}
	}

	void DeletePart() override
	{
		Delete = true;
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
	float t = 0.16f;
	Radiator()
	{
		partid = PART::RADIATOR;
		parttype = TYPE::STRUCTUREPART;
		type = parttype + NodeType::LASTNODE;
		Name = "Radiator";
		
		Health = PartsData.GetPropertyAsFloat("Radiator", "Health");
		coolingSpeed = PartsData.GetPropertyAsFloat("Radiator", "coolingSpeed");
		mintemp = PartsData.GetPropertyAsFloat("Radiator", "mintemp");


		
		CreateBody(2);
		body[0].position = position + Normalize({0.0f,1.0f}) * PARTSIZE;
		body[1].position = position - Normalize({0.0f,1.0f}) * PARTSIZE;
		body[0].r = PARTSIZE;
		body[1].r = PARTSIZE;
		body[1].mass = 1.0f;
		body[0].mass = 1.0f;

		CoolingSpeed = coolingSpeed;
		MinAutocooltemp = mintemp;
		OnPartCreate();
	}
	void Create(glm::vec2 position,glm::vec2 direction, float size, float mass =1.0f) override
	{

		Health = PartsData.GetPropertyAsFloat("Radiator", "Health");
		coolingSpeed = PartsData.GetPropertyAsFloat("Radiator", "coolingSpeed");
		mintemp = PartsData.GetPropertyAsFloat("Radiator", "mintemp");


		
		body[0].position = position + Normalize(direction) * size;
		body[1].position = position - Normalize(direction) * size;
		body[0].r = size;
		body[1].r = size;
		body[1].mass = mass;
		body[0].mass = mass;

		CoolingSpeed = coolingSpeed;
		MinAutocooltemp = mintemp;

		Cost.Al = 20;
		Cost.Cu = 5;
		Cost.Fe = 10;

	}

	void MTProcess (float dt) override
	{
		delt = dt;
		ProcessBody(dt);
		body[0].color = color;
		body[1].color = color;

		mid = 0.5f * (body[0].position + body[1].position);
		dir = (body[1].position - body[0].position);
		body[0].Process(dt);
		body[1].Process(dt);
		body[1].Force = glm::vec2(0.0f);
		body[0].Force = glm::vec2(0.0f);
		Strut(&body[0], &body[1], body[0].r * 2.0f);
		float change = (body[0].temperature - body[1].temperature);

		body[0].temperature -= change;
		body[1].temperature += change;

	}
	float delt = 0.0f;
	void Process(float dt) override
	{

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
					if(!SourcePlaying(&source))
						PlaySource(&source);
					SetSourceGain(&source, gain * 0.03f);

					
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
				}
			}

			

		}
		else
		{
			CoolingSpeed = 1.0f;
			if (source != 0)
			{
				SetSourceGain(&source, 0.0f);
				StopSource(&source);
			}
		}
	
	}

	void Draw() override
	{
		glm::vec2 dif = body[0].position - body[1].position;
		//DrawLine(body[0].position + dif*0.5f, body[1].position - dif * 0.5f, body[0].r, Base.color, true, CubeNormalMapTexture, Z_Index);
		glm::vec2 mid = (body[1].position + body[0].position) * 0.5f;
		float gain = ((body[1].temperature + body[0].temperature) * 0.25f);
		if (gain > 0.0f)
		{
			t -= delt;
			if (t <= 0.0f)
			{
				t = 0.016f;
				Smoke.SpawnInCircle(body[0].position, body[0].r, 2 + gain);
				Smoke.SpawnInCircle(body[1].position, body[1].r, 2);
			}
		}
		DrawTexturedQuad(mid, glm::vec2(1.0f * body[1].r, 2.0f * body[1].r), RadiatorTexture, get_angle_between_points(mid, body[0].position), color, Z_Index, RadiatorNormalMap);

	}

	void DeletePart() override
	{
		Delete = true;
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
	StaticPoint()
	{
		partid = PART::STATICPOINT;
		parttype = TYPE::STRUCTUREPART;
		type = parttype + NodeType::LASTNODE;
		Name = "StaticPoint";
		

		CreateBody(1);
		body[0].r = 10;
		body[0].position = position;
		this->position = position;

		body[0].roughness = 0.0f;
		body[0].bounciness = 0.0f;
		BodyIdsWithCollision.push_back(0);
		OnPartCreate();
	}
	void Create(glm::vec2 position, glm::vec2 direction, float size, float mass = 1.0f) override
	{

		

		body[0].r = 10;
		body[0].position = position;
		this->position = position;

		body[0].roughness = 0.0f;
		body[0].bounciness = 0.0f;
	}
	
	void MTProcess (float dt) override
	{
		ProcessBody(dt);
		body[0].position = position;
		body[0].velocity = { 0.0f,0.0f };
		body[0].Force = { 0.0f,0.0f };
		body[0].Process(dt);
		body[0].color = color;
	
	}


	void Process(float dt) override
	{
	}
	void Draw() override
	{
		DrawCircle(body[0], color, true, BallNormalMapTexture, Z_Index);
	}

	
	void DeletePart() override
	{
		Delete = true;
		DeleteBody();
	}
};



class CentralPart : public BodyComponent
{
public:
	//HEAT related stuff
	glm::vec2 midvel;

	const char* name = "Entity1";

	float strutMaxLength = 15.0f;
	float strutMinLength = 0.9f;

	float freq = 1.0f;

	struct DataConnection
	{
		int type;// 0=bool 1=float 2=vec2
		int part1 = 0;
		int part2 = 0;

		int index1 = 0;
		int index2 = 0;

		bool failed = false;

		void Process(CentralPart* ent)
		{

			if(ent!=NULL)
			if (part1 < ent->Parts.size() && part2 < ent->Parts.size() &&
				!ent->Parts[part1]->debris && !ent->Parts[part2]->debris)
			{
				failed = false;

				if (type == 0 && index1 < ent->Parts[part1]->bDCsize && index2 < ent->Parts[part2]->bDCsize)
				{
					if (ent->Parts[part1]->bDataConnections[index1].source)
						ent->Parts[part2]->bDataConnections[index2] = ent->Parts[part1]->bDataConnections[index1];
					else
						ent->Parts[part1]->bDataConnections[index1] = ent->Parts[part2]->bDataConnections[index2];

					ent->Parts[part1]->bDataConnections[index1].connected = true;
					ent->Parts[part2]->bDataConnections[index2].connected = true;
					if (bLogicMode)
					{
						glm::vec2 position1;
						float Scale = (ent->Parts[part1]->body[0].r * 0.5f);
						glm::vec2 norm = Rotate(ent->Parts[part1]->dir, pi * 0.5f);

						if (index1 < ent->Parts[part1]->bDCsize * 0.5f)
							position1 = ent->Parts[part1]->body[0].position + ent->Parts[part1]->dir * float(index1) * Scale * 2.0f + norm * Scale;
						else
							position1 = ent->Parts[part1]->body[0].position + ent->Parts[part1]->dir * float(index1 - ent->Parts[part1]->bDCsize * 0.5f) * Scale * 2.0f - norm * Scale;


						glm::vec2 position2;
						float Scale2 = (ent->Parts[part2]->body[0].r * 0.5f);
						glm::vec2 norm2 = Rotate(ent->Parts[part2]->dir, pi * 0.5f);

						if (index2 < ent->Parts[part2]->bDCsize * 0.5f)
							position2 = ent->Parts[part2]->body[0].position + ent->Parts[part2]->dir * float(index2) * Scale2 * 2.0f + norm2 * Scale2;
						else
							position2 = ent->Parts[part2]->body[0].position + ent->Parts[part2]->dir * float(index2 - ent->Parts[part2]->bDCsize * 0.5f) * Scale2 * 2.0f - norm2 * Scale2;

						DrawLine(position1, position2,
							0.0625f, glm::vec4(0.0f, 0.0f, 1.5f, 1.0f), false, 0, 1000);
					}
				}
				else if (type == 1 && index1 < ent->Parts[part1]->fDCsize && index2 < ent->Parts[part2]->fDCsize)
				{
					if (ent->Parts[part1]->fDataConnections[index1].source)
						ent->Parts[part2]->fDataConnections[index2] = ent->Parts[part1]->fDataConnections[index1];
					else
						ent->Parts[part1]->fDataConnections[index1] = ent->Parts[part2]->fDataConnections[index2];

					ent->Parts[part1]->fDataConnections[index1].connected = true;
					ent->Parts[part2]->fDataConnections[index2].connected = true;

					if (fLogicMode)
					{
						glm::vec2 position1;
						float Scale = (ent->Parts[part1]->body[0].r * 0.5f);
						glm::vec2 norm = Rotate(ent->Parts[part1]->dir, pi * 0.5f);

						if (index1 < ent->Parts[part1]->fDCsize * 0.5f)
							position1 = ent->Parts[part1]->body[0].position + ent->Parts[part1]->dir * float(index1) * Scale * 2.0f + norm * Scale;
						else
							position1 = ent->Parts[part1]->body[0].position + ent->Parts[part1]->dir * float(index1 - ent->Parts[part1]->fDCsize * 0.5f) * Scale * 2.0f - norm * Scale;


						glm::vec2 position2;
						float Scale2 = (ent->Parts[part2]->body[0].r * 0.5f);
						glm::vec2 norm2 = Rotate(ent->Parts[part2]->dir, pi * 0.5f);

						if (index2 < ent->Parts[part2]->fDCsize * 0.5f)
							position2 = ent->Parts[part2]->body[0].position + ent->Parts[part2]->dir * float(index2) * Scale2 * 2.0f + norm2 * Scale2;
						else
							position2 = ent->Parts[part2]->body[0].position + ent->Parts[part2]->dir * float(index2 - ent->Parts[part2]->fDCsize * 0.5f) * Scale2 * 2.0f - norm2 * Scale2;

						DrawLine(position1, position2,
							0.0625f, glm::vec4(0.0f, 1.5f, 0.0f, 1.0f), false, 0, 1000);
					}
				}
				else if (type == 2 && index1 < ent->Parts[part1]->vDCsize && index2 < ent->Parts[part2]->vDCsize)
				{
					if (ent->Parts[part1]->vDataConnections[index1].source)
						ent->Parts[part2]->vDataConnections[index2] = ent->Parts[part1]->vDataConnections[index1];
					else
						ent->Parts[part1]->vDataConnections[index1] = ent->Parts[part2]->vDataConnections[index2];

					ent->Parts[part1]->vDataConnections[index1].connected = true;
					ent->Parts[part2]->vDataConnections[index2].connected = true;
					if (vLogicMode)
					{
						glm::vec2 position1;
						float Scale = (ent->Parts[part1]->body[0].r * 0.5f);
						glm::vec2 norm = Rotate(ent->Parts[part1]->dir, pi * 0.5f);

						if (index1 < ent->Parts[part1]->fDCsize * 0.5f)
							position1 = ent->Parts[part1]->body[0].position + ent->Parts[part1]->dir * float(index1) * Scale * 2.0f - norm * Scale;
						else
							position1 = ent->Parts[part1]->body[0].position + ent->Parts[part1]->dir * float(index1 - ent->Parts[part1]->fDCsize * 0.5f) * Scale * 2.0f + norm * Scale;


						glm::vec2 position2;
						float Scale2 = (ent->Parts[part2]->body[0].r * 0.5f);
						glm::vec2 norm2 = Rotate(ent->Parts[part2]->dir, pi * 0.5f);

						if (index2 < ent->Parts[part2]->fDCsize * 0.5f)
							position2 = ent->Parts[part2]->body[0].position + ent->Parts[part2]->dir * float(index2) * Scale2 * 2.0f - norm2 * Scale2;
						else
							position2 = ent->Parts[part2]->body[0].position + ent->Parts[part2]->dir * float(index2 - ent->Parts[part2]->fDCsize * 0.5f) * Scale2 * 2.0f + norm2 * Scale2;

						DrawLine(position1, position2,
							0.0625f, glm::vec4(1.5f, 0.0f, 0.0f, 1.0f), false, 0, 1000);
					}
				}
				else
					failed = true;


			}
			else
				failed = true;
		}


	};

	struct Connection
	{
		int part1 = 0;
		int part2 = 0;

		int index1 = 0;
		int index2 = 0;

		float width = 0.125f;
		float length = 1.0f;
		float stiffnes = 1.0f;
		float absorbtion = 2.0f;

		float HeatTransferSpeed = 1.0f;

		int type = CONNECTION::STRUT;

		BallBodyComponent* b1;
		BallBodyComponent* b2;

		BodyComponent* bod1;
		BodyComponent* bod2;

		DecorativeRope rope;

		unsigned int Texture = NULL;
		unsigned int NormalMap = NULL;

		void UpdateLinks(CentralPart* ent)
		{


			bod1 = ent->Parts[part1];
			b1 = &ent->Parts[part1]->body[index1];


			bod2 = ent->Parts[part2];
			b2 = &ent->Parts[part2]->body[index2];

			if (bod1->Health <= 0.0f)
			{
				bod1 = NULL;
				b1 = NULL;
			}
			if (bod2->Health <= 0.0f)
			{
				bod2 = NULL;
				b2 = NULL;
			}
		}
		void Init()
		{
			//rope.Init(b1, b2, length);
		}
		void Process(CentralPart* ent, float dt)
		{

			UpdateLinks(ent);

			if (b1 != nullptr && b2 != nullptr)
			{


				if (type == CONNECTION::STRUT)
					Strut(b1, b2, length);

				if (type == CONNECTION::SPRING)
					SpringBetweenBalls(b1, b2, length, stiffnes, absorbtion);

				if (type == CONNECTION::HEATPIPE || type == CONNECTION::ROPE)
					Rope(b1, b2, length);


				

			}
			if (b1 != nullptr && b2 != nullptr)
			{
				float change = (b1->temperature - b2->temperature) * dt * HeatTransferSpeed;

				b1->temperature -= change;
				b2->temperature += change;
			}




		}
		void Draw(float dt)
		{

			glm::vec4 color = (b1->color + b2->color) * 0.5f;
			if (type == CONNECTION::STRUT)
				if (Texture == NULL)
					DrawLine(b1->position, b2->position, width, color, true, NormalMap, -10);
				else
					DrawTexturedLine(Texture, b1->position, b2->position, width, color, NormalMap, -10);

			if (type == CONNECTION::SPRING)
				if (Texture == NULL)
					DrawLine(b1->position, b2->position, width, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), true, true, -10);
				else
					DrawTexturedLine(Texture, b1->position, b2->position, width, color, NormalMap, -10);

			if (type == CONNECTION::HEATPIPE)
			{
				Texture = HeatPipeTexture;
				NormalMap = HeatPipeNormalMap;

			}
			if (type == CONNECTION::ROPE)
			{
				Texture = RopeTexture;
				NormalMap = RopeNormalMap;
			}
			if (type == CONNECTION::STRUT)
			{
				Texture = StrutTexture;
				NormalMap = StrutNormalMap;
			}
			if (type == CONNECTION::HEATPIPE || type == CONNECTION::ROPE)
			{
				rope.b1 = b1;
				rope.b2 = b2;
				rope.length = length;
				rope.width = width;
				rope.Process(dt);
				rope.Texture = Texture;
				rope.NormalMap = NormalMap;
				rope.color = color;

				rope.Draw(-9);
			}


		}
	};

	int id = -1;
	bool Alive = true;
	bool destroyed = false;

	ball* back;
	ball* front;

	glm::vec2 direction = glm::vec2(0.0f, 1.0f);

	float RotationalFriction = 1.0f;

	float Rotation = 0.0f;
	float RotationVelocity = 0.0f;

	float AquieredRotationVelocity = 0.0f;

	glm::vec2 LookAt = glm::vec2(1.0f, -1.0f);
	glm::vec2 ThrustDirection = glm::vec2(0.0f, 0.0f);


	glm::vec2 CenterOfMass = glm::vec2(0.0f);


	std::vector<BallBodyComponent*> Balls;
	std::vector<BodyComponent*> Parts;
	std::vector<BodyComponent*> Engines;

	float mass = 0.0f;
	float ForceToThrustDirection = 0.0f;
	float maxVelocity = 0.0f;
	glm::vec2 trgPos = { 0.0f,0.0f };
	bool autocontrol = false;

	std::vector<Connection> Connections;
	std::vector<DataConnection> DataConnections;
	glm::vec2 LookAtOnTarget = glm::vec2(0.0f, 1.0f);


	glm::vec2 GunsTargetrotPoint = glm::vec2(0.0f);
	bool FireGuns = false;

	bool firstdrawafterload = true;

	std::vector<DamageSphere*> CloseDamageSpheres;

	float maxR = 0.0f;
	void DeleteSoundSources()
	{
		for (int i = 0; i < Parts.size(); i++)
			DeleteSource(&Parts[i]->source);
	}
	CentralPart()
	{
		
		partid = PART::CENTRALPART;
		parttype = TYPE::STRUCTUREPART;
		type = parttype + NodeType::LASTNODE;
		Name = "CentralPart";
		Health = PartsData.GetPropertyAsFloat("CentralPart", "Health");
		CreateBody(2,9,0,1);
		BodyIdsWithCollision.push_back(0);
		BodyIdsWithCollision.push_back(1);
		body[0].position = position + Normalize({0.0f,1.0f}) * PARTSIZE;
		body[1].position = position - Normalize({0.0f,1.0f}) * PARTSIZE;
		body[0].r = PARTSIZE;
		body[1].r = PARTSIZE;
		body[1].mass = 1.0f;

		ProcessConnections();
		OnPartCreate();

	}
	void Create(glm::vec2 position, glm::vec2 direction, float size,float mass = 1.0f) override
	{



		
		Health = PartsData.GetPropertyAsFloat("CentralPart", "Health");

		body[0].position = position + Normalize(direction) * size;
		body[1].position = position - Normalize(direction) * size;
		body[0].r = size;
		body[1].r = size;
		body[1].mass = mass;

		ProcessConnections();
		Parts.push_back(this);
		
	}
	void ProcessConnections()
	{
		bDataConnections[0].name = "LMB";
		bDataConnections[1].name = "RMB";
		bDataConnections[2].name = "MMB";
		bDataConnections[3].name = "Shift";
		bDataConnections[4].name = "Space";
		bDataConnections[5].name = "W";
		bDataConnections[6].name = "A";
		bDataConnections[7].name = "S";
		bDataConnections[8].name = "D";
		vDataConnections[0].name = "MousePosition";

		bDataConnections[0].source = true;
		bDataConnections[1].source = true;
		bDataConnections[2].source = true;
		bDataConnections[3].source = true;
		bDataConnections[4].source = true;
		bDataConnections[5].source = true;
		bDataConnections[6].source = true;
		bDataConnections[7].source = true;
		bDataConnections[8].source = true;

		vDataConnections[0].source = true;
	}
	void MTProcess (float dt) override
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

		if (player)
		{
			bDataConnections[0].data = buttons[GLFW_MOUSE_BUTTON_1];
			bDataConnections[1].data = buttons[GLFW_MOUSE_BUTTON_2];
			bDataConnections[2].data = buttons[GLFW_MOUSE_BUTTON_3];
			bDataConnections[3].data = keys[GLFW_KEY_LEFT_SHIFT] || keys[GLFW_KEY_RIGHT_SHIFT];
			bDataConnections[4].data = keys[GLFW_KEY_SPACE];
			bDataConnections[5].data = keys[GLFW_KEY_W];
			bDataConnections[6].data = keys[GLFW_KEY_A];
			bDataConnections[7].data = keys[GLFW_KEY_S];
			bDataConnections[8].data = keys[GLFW_KEY_D];
			vDataConnections[0].data = foregroundMousePosition;
			if (BuildingMode || bLogicMode || fLogicMode || vLogicMode)
			{
				bDataConnections[0].data = false;
				bDataConnections[1].data = false;
				bDataConnections[2].data = false;
				bDataConnections[3].data = false;
				bDataConnections[4].data = false;
				bDataConnections[5].data = false;
				bDataConnections[6].data = false;
				bDataConnections[7].data = false;
				bDataConnections[8].data = false;

				vDataConnections[0].data = mid;

			}
		}
		
		Engines.clear();
		Balls.clear();
		maxR = 0.0f;
		if (!destroyed)
		{
			front = &body[0];
			back = &body[1];
			
			int deliter = 0;
			while (deliter<Parts.size())
			{	
				if(Parts[deliter]->Delete)
				{
					Parts[deliter] = Parts[Parts.size()-1];
					Parts.pop_back();
				}
				else
					deliter++;
			}

			
			for (int i = 0; i < Parts.size(); i++)
			{
				float len = sqrlength(Parts[i]->body[0].position - CenterOfMass);
				if (len > maxR)
					maxR = sqrt(len);
			}
			maxR += 2.0f;
			for (int d = 0; d < DamageSpheres.size(); d++)
			{
				if (DamageSpheres[d]->id == id)
					continue;
				if (sqrlength(DamageSpheres[d]->body.position - CenterOfMass) < DamageSpheres[d]->body.r * DamageSpheres[d]->body.r + maxR * maxR)
					CloseDamageSpheres.push_back(DamageSpheres[d]);
			}

			mass = 0.0f;
			glm::vec2 avgvel = glm::vec2(0.0f);
			CenterOfMass = glm::vec2(0.0f);

			int coniter = 0;
			while (coniter < Connections.size())
			{
				if (Connections[coniter].length > strutMaxLength || Connections[coniter].length < strutMinLength)
				{
					Connections[coniter] = Connections[Connections.size() - 1];
					Connections.pop_back();
				}
				else
				{
					Connections[coniter].Process(this, dt);
					coniter++;
				}
			}
			for (int i = 0; i < DataConnections.size(); i++)
				DataConnections[i].Process(this);

			for (int i = 0; i < DataConnections.size(); i++)
				while (i < DataConnections.size() && DataConnections[i].failed)
				{
					DataConnections[i] = DataConnections[DataConnections.size() - 1];
					DataConnections.pop_back();
				}

			for (int i = 0; i < Parts.size(); i++)
			{
				Parts[i]->id = id;



				for (int d = 0; d < CloseDamageSpheres.size(); d++)
					Parts[i]->DamageSphereCollide(CloseDamageSpheres[d]);

				if (Parts[i]->WasHitThisFrame)
				{// got hit


					if (Parts[i]->dmgThisFrame > 0)//got gamaged
						DeleteSomeConnections(i, (Parts[i]->dmgThisFrame / Parts[i]->maxHealth) * 0.01f);

				}


				
				for (int bp = 0; bp < Parts[i]->BodyIdsWithCollision.size(); bp++)
				{
					
						int pid = Parts[i]->BodyIdsWithCollision[bp];

						mass += Parts[i]->body[pid].mass;
						avgvel += Parts[i]->body[bp].velocity * Parts[i]->body[pid].mass;
						CenterOfMass += Parts[i]->body[bp].position * Parts[i]->body[pid].mass;

						Parts[i]->body[pid].id = id;

						Balls.push_back(&Parts[i]->body[pid]);
				}

				//if (!Parts[i]->dead||i==0)
				//{
				//	Parts[i]->Process(dt);
				//}


				Parts[i]->freq = freq;
				Parts[i]->deactivated = false;
				Parts[i]->targetrotpoint = GunsTargetrotPoint;

				if (FireGuns && Parts[i]->parttype == TYPE::WEAPON)
					Parts[i]->shot = true;
				else
					Parts[i]->shot = false;

				if (Parts[i]->parttype == TYPE::PROPULSION)
					Engines.push_back(Parts[i]);
			}
			CloseDamageSpheres.clear();

			avgvel /= mass;
			CenterOfMass /= mass;


			



			if (back != NULL && front != NULL)
			{
				direction = Normalize(front->position - back->position);

				float aligment = DOT(Normalize(direction), Normalize(glm::vec2(-LookAt.y, LookAt.x)));
				glm::vec2 dirTotrg = Normalize((trgPos - (body[0].position + body[1].position) * 0.5f));

				for (int i = 0; i < Engines.size(); i++)
				{
					Engines[i]->throtle = DOT(-Engines[i]->dir, ThrustDirection);

					float dotTotrg = DOT(-Engines[i]->dir, dirTotrg);
					if (dotTotrg > 0.0f)
						ForceToThrustDirection += dotTotrg * Engines[i]->Power;

					Engines[i]->throtle += DOT(-Engines[i]->dir, Normalize(Rotate(CenterOfMass - Engines[i]->body[1].position, pi * 0.5))) * aligment;

					if (Engines[i]->throtle < 0.0f)	Engines[i]->throtle = 0.0f;
					if (Engines[i]->throtle > 1.0f)	Engines[i]->throtle = 1.0f;
				}
			}
			float distance = length(trgPos - (body[0].position + body[1].position) * 0.5f) + 0.001f;
			float entVelocity = length(avgvel) + 0.001f;
			maxVelocity = distance * ForceToThrustDirection * 0.01f / (mass)+0.001f;
			float friction = 0.0f;
			if (autocontrol)
			{
				

				glm::vec2 dir = ((trgPos - (body[0].position + body[1].position) * 0.5f) / distance);
				if (distance < 2)
				{
					body[0].Force = dir * 10.0f;
					body[1].Force = dir * 10.0f;
					friction = 1.0;
					LookAt = LookAtOnTarget;
				}
				else {
					if (distance > 300)
						LookAt = dir;
					else
						LookAt = LookAtOnTarget;
					glm::vec2 Force = { 0.0f,0.0f };

					float sizemult = 0.1f;

					Force.x = sigmoid(((CenterOfMass.x - trgPos.x) * sizemult * -0.496329 + avgvel.x * sizemult * -0.0841397)) * 2.0f - 1.0f;
					Force.y = sigmoid(((CenterOfMass.y - trgPos.y) * sizemult * -0.496329 + avgvel.y * sizemult * -0.0841397)) * 2.0f - 1.0f;

					glm::vec2 norm = Normalize(Rotate((mid - trgPos), pi * 0.5f));
					Force -= DOT(norm, body[0].velocity) * norm * 4.0f;

					//float forceNeeded = length(Force);// (maxVelocity - entVelocity)* mass / (ForceToThrustDirection);
					ThrustDirection = Force;
					/*if (DOT(ThrustDirection, dir) < 0.0f && DOT(avgvel, dir) < 0.0f)
						ThrustDirection += dir * 0.5f;*/
					//ThrustDirection -= glm::vec2(-dir.y, dir.x) * DOT(glm::vec2(-dir.y, dir.x), avgvel);
					if (distance < 10)
						friction = 1.0;
				}


				for (int i = 0; i < bDCsize; i++)
				{
					if (bDataConnections[i].name == "LMB") bDataConnections[i].data = distance<200;
					if (bDataConnections[i].name == "RMB") bDataConnections[i].data = distance < 200;
					if (bDataConnections[i].name == "MMB") bDataConnections[i].data = distance < 200;
					if (bDataConnections[i].name == "Shift") bDataConnections[i].data = distance > 200; // MB implement a dodge for bots
					if (bDataConnections[i].name == "Space") bDataConnections[i].data = false; 
					if (bDataConnections[i].name == "W") bDataConnections[i].data = ThrustDirection.y > 0.0f;
					if (bDataConnections[i].name == "A") bDataConnections[i].data = ThrustDirection.x < 0.0f;
					if (bDataConnections[i].name == "S") bDataConnections[i].data = ThrustDirection.y < 0.0f;
					if (bDataConnections[i].name == "D") bDataConnections[i].data = ThrustDirection.x > 0.0f;
				}
				if (vDataConnections[0].name == "MousePosition") vDataConnections[0].data = GunsTargetrotPoint;

			}
			ForceToThrustDirection = 0.0f;
			for (int i = 0; i < Balls.size(); i++)
			{
				glm::vec2 dif = Normalize(CenterOfMass - Balls[i]->position);
				Balls[i]->velocity -= DOT(Balls[i]->velocity - avgvel, glm::vec2(-dif.y, dif.x)) * glm::vec2(-dif.y, dif.x) * RotationalFriction * dt;
				Balls[i]->velocity -= Balls[i]->velocity * friction * dt;
			}
			
		}
		
	}
	void Process(float dt) override
	{
		
		CheckPartsConnections();
		int pt = 0;
		while (pt < Parts.size())
		{
			if (pt < Parts.size() && Parts[pt]->Health <= 0.0f)
			{
				DestroyPart(pt);
			}
			else
				pt++;
		}

	}

	void Draw() override
	{
		if(firstdrawafterload)
		{
			firstdrawafterload = false;
			return;
		}

		glm::vec2 dif = body[0].position - body[1].position;
		DrawLine(body[0].position + dif*0.5f, body[1].position - dif * 0.5f, body[0].r, color, true, CubeNormalMapTexture, Z_Index);
		

		DrawTexturedQuad(mid, glm::vec2(1.0f * body[1].r, 2.0f * body[1].r), CentralPartTexture, get_angle_between_points(mid, body[0].position), color, Z_Index, CentralPartNormalMap);
		
		
		for (int i = 0; i < Connections.size(); i++)
			Connections[i].Draw(delta*Speed);
	}

	
	void DeletePart() override;
	void DeleteConnections( int index, int index2);
	void DeleteSomeConnections( int Partindex, float chance);
	void DestroyPart(int  index);
	void DetachPart( int  index);
	void DetachDetachedParts();
	bool CheckPartConnections(Connection* c);
	void CheckPartsConnections();
	int ClaimPart(int index);
	void AddConnection(int type, float len, float width, float stiffness, float absorbtion, float HeatTransferSpeed,
		int part1, int  index1,
		int part2, int  index2);
	void AddDataConnection(int type, int part1, int  index1, int part2, int  index2);
	void SaveTo(std::string filename);
	void LoadFrom(std::string filename);
	void Clear();
	void Destroy();
};




BodyComponent* CreatePart(int type, glm::vec2 position, glm::vec2 direction, float size, float mass = 1.0f)
{
	BodyComponent* b=NULL;
	if (type == PART::BALLBODY) 
	{
		BallBody* bb = new BallBody();
		bb->Create(position, glm::vec2(0.0f, 1.0f), size);
		b = bb;
	}

	else if (type == PART::ROCKETENGINE) 
	{
		RocketEngine* bb = new RocketEngine();
		bb->Create(position, glm::vec2(0.0f, 1.0f), size);
		b = bb;
	}

	else if (type == PART::GUN) 
	{
		Gun* bb = new Gun();
		bb->Create(position, glm::vec2(0.0f, 1.0f), size);
		b = bb;
	}

	else if (type == PART::LASERGUN) 
	{
		LaserGun* bb = new LaserGun();
		bb->Create(position, glm::vec2(0.0f, 1.0f), size);
		b = bb;
	}

	else if (type == PART::STATICPOINT) 
	{

		StaticPoint* bb = new StaticPoint();
		bb->Create(position, glm::vec2(0.0f, 1.0f), size);
		b = bb;
	}

	else if (type == PART::RADIATOR) 
	{

		Radiator* bb = new Radiator();
		bb->Create(position, glm::vec2(0.0f, 1.0f), size);
		b = bb;
	}
	else if (type == PART::ROTOR) 
	{

		Rotor* bb = new Rotor();
		bb->Create(position, glm::vec2(0.0f, 1.0f), size);
		b = bb;
	}
	else if (type == PART::ROCKETLAUNCHER)
	{

		RocketLauncher* bb = new RocketLauncher();
		bb->Create(position, glm::vec2(0.0f, 1.0f), size);
		b = bb;
	}
	else if (type == PART::MINIGUN)
	{

		MiniGun* bb = new MiniGun();
		bb->Create(position, glm::vec2(0.0f, 1.0f), size);
		b = bb;
	}
	return b;

}


void InitParts()
{


	NodeConstructors.insert({NodeType::LASTNODE + PART::BALLBODY,[](){return (Node*)new BallBody();}});
	NodeConstructorNames.insert({NodeType::LASTNODE + PART::BALLBODY,"BallBody"});
	NodeConstructors.insert({NodeType::LASTNODE + PART::ROCKETENGINE,[](){return (Node*)new RocketEngine();}});
	NodeConstructorNames.insert({NodeType::LASTNODE + PART::ROCKETENGINE,"RocketEngine"});
	NodeConstructors.insert({NodeType::LASTNODE + PART::GUN,[](){return (Node*)new Gun();}});
	NodeConstructorNames.insert({NodeType::LASTNODE + PART::GUN,"Gun"});
	NodeConstructors.insert({NodeType::LASTNODE + PART::LASERGUN,[](){return (Node*)new LaserGun();}});
	NodeConstructorNames.insert({NodeType::LASTNODE + PART::LASERGUN,"LaserGun"});
	NodeConstructors.insert({NodeType::LASTNODE + PART::RADIATOR,[](){return (Node*)new Radiator();}});
	NodeConstructorNames.insert({NodeType::LASTNODE + PART::RADIATOR,"Radiator"});
	NodeConstructors.insert({NodeType::LASTNODE + PART::ROTOR,[](){return (Node*)new Rotor();}});
	NodeConstructorNames.insert({NodeType::LASTNODE + PART::ROTOR,"Rotor"});
	NodeConstructors.insert({NodeType::LASTNODE + PART::ROCKETLAUNCHER,[](){return (Node*)new RocketLauncher();}});
	NodeConstructorNames.insert({NodeType::LASTNODE + PART::ROCKETLAUNCHER,"RocketLauncher"});
	NodeConstructors.insert({NodeType::LASTNODE + PART::MINIGUN,[](){return (Node*)new MiniGun();}});
	NodeConstructorNames.insert({NodeType::LASTNODE + PART::RAILGUN,"MiniGun"});
	NodeConstructors.insert({NodeType::LASTNODE + PART::STATICPOINT,[](){return (Node*)new StaticPoint();}});
	NodeConstructorNames.insert({NodeType::LASTNODE + PART::STATICPOINT,"StaticPoint"});
	NodeConstructors.insert({NodeType::LASTNODE + PART::CENTRALPART,[](){return (Node*)new CentralPart();}});
	NodeConstructorNames.insert({NodeType::LASTNODE + PART::CENTRALPART,"CentralPart"});


	//BodyComponent* b = NULL;
	//for (int i = 0; i < SpawnablePartAmount; i++)
	//{
	//	b = CreatePart(i, { 0.0f,0.0f }, { 0.0f,1.0f }, 0.5f);
	//	b->DeletePart();
	//}
	//b = new CentralPart();
	//b->Create({ 0.0f,0.0f }, {0.0f,1.0f},0.5f);
	//b->DeletePart();
}
