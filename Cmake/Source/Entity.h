#pragma once



enum CONNECTION
{
	STRUT = 0,
	SPRING = 1,
	HEATPIPE = 2,
	ROPE = 3
};


ParticleEmiter CollisionSparks;
ParticleEmiter CollisionSmoke;

float DrawingDistance = (WIDTH * 1.0f) / CameraScale.x;
class PartsPile
{
public:

	std::vector<BodyComponent*> Parts;

	std::vector<DamageSphere*> CloseDamageSpheres;

	void Process(float dt, int iter,bool lastiter)
	{
		

		for (int i = 0; i < Parts.size(); i++)
		{
			
			bool del = true;
			while (del && i < Parts.size())
			{
				del = false;
				if (Parts[i]->Health <= 0.0f)
				{
					DeletePart(i);
					del = true;
				}
			}
		}
		DrawingDistance = (WIDTH * 1.0f) / CameraScale.x;
		if (DrawingDistance < 150)
			DrawingDistance = 150;
		DrawingDistance *= DrawingDistance;

		for (int d = 0; d < DamageSpheres.size(); d++)
		{
			if (DamageSpheres[d]->id >= 0 && sqrlength(DamageSpheres[d]->body.position - CameraPosition) < DamageSpheres[d]->body.r * DamageSpheres[d]->body.r + 150 * 150)
				CloseDamageSpheres.push_back(DamageSpheres[d]);
		}

		for (int i = 0; i < Parts.size(); i++)
		{
			Parts[i]->debris = true;
			if (sqrlength(Parts[i]->body[0].position - CameraPosition) < DrawingDistance)
			{

				for (int d = 0; d < CloseDamageSpheres.size(); d++)
					Parts[i]->DamageSphereCollide(CloseDamageSpheres[d]);

				

				Parts[i]->throtle = 0.0f;
				Parts[i]->deactivated = true;

				if (!Parts[i]->dead)
				{

					Parts[i]->Process(dt);
					if (lastiter)
						Parts[i]->Draw();
				}

				for (int a = 0; a < Map.cubes.size(); a++)
					if (Map.cubes[a].id == 1)
						for (int bp = 0; bp < Parts[i]->bodysize; bp++)
						{
							if (BtCCollisionCheck(Parts[i]->body[bp], Map.cubes[a]))
							{
								Parts[i]->Health = -1.0f;
							}
						}
				for (int a = 0; a < Map.balls.size(); a++)
					if (Map.balls[a].id == 1)
						for (int bp = 0; bp < Parts[i]->bodysize; bp++)
						{
							if (BtBCollisionCheck(Parts[i]->body[bp], Map.balls[a]))
							{
								Parts[i]->Health = -1.0f;
							}
						}
			}
		}

		CloseDamageSpheres.clear();
	}
	void DeletePart(int  index)
	{
		glm::vec2 mid = {0.0f,0.0f};
		for (int i = 0; i < Parts[index]->bodysize; i++)
		{
			Sparks.Spawn(Parts[index]->body[i].position, 15);
			Smoke.Spawn(Parts[index]->body[i].position, 15);

			DebrieParticles.RotationVelocity = rand() % 100 * 0.1f - 5.0f;
			DebrieParticles.InitialVelocity = Parts[index]->body[i].velocity;
			DebrieParticles.Spawn(Parts[index]->body[i].position, 3);
			mid += Parts[index]->body[i].position;
		}
		mid /= Parts[index]->bodysize;
		for (int bp = 0; bp < Parts[index]->bodysize; bp++)
		{
			if (GrabbedBall != NULL)
				if (GrabbedBall->position == Parts[index]->body[bp].position)
					GrabbedBall = NULL;
			if (SelectedPart = index)
				SelectedPart = -1;
		}

		if (Parts[index]->source != 0)
		{
			StopSource(&Parts[index]->source);
			alDeleteSources(1, &Parts[index]->source);
		}
		Parts[index]->Delete();

		Parts[index] = Parts[Parts.size() - 1];
		Parts.pop_back();
		PlaySound(&PartDestrSOund, mid, 0.085f+rand()%100*0.001f, 0.25f);


	}

	void SpawnPart(int type, glm::vec2 position, float size = 20.0f)
	{
		
			BodyComponent* b = CreatePart(type, position, { 0.0f,1.0f }, size);

			
			if(b!=NULL)
				Parts.push_back(b);
		
	}

	void SpawnRandomPart( glm::vec2 position, float size = 20.0f)
	{
		int type = rand() % 7;
		SpawnPart(type, position, size);
	}

};
PartsPile Debris;


class Entity
{
public:
	const char* name = "Entity1";

	float strutMaxLength = 15.0f;
	float strutMinLength = 0.9f;

	CentralPart CP;
	float freq = 1.0f;

	struct DataConnection
	{
		int type;// 0=bool 1=float 2=vec2
		int part1 = 0;
		int part2 = 0;

		int index1 = 0;
		int index2 = 0;

		bool failed = false;

		void Process(Entity* ent)
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

		void UpdateLinks(Entity* ent)
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
		void Process(Entity* ent, float dt)
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


	std::vector<ball*> Balls;

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


	std::vector<DamageSphere*> CloseDamageSpheres;

	float maxR = 0.0f;

	void DeleteSoundSources()
	{
		for (int i = 0; i < Parts.size(); i++)
			DeleteSource(&Parts[i]->source);
	}
	void Ready(glm::vec2 position, glm::vec2 direction, float size, float mass = 1.0f)
	{
		CP.Ready(position, direction, size, mass);
		Parts.push_back(&CP);

	}
	void Process(float dt)
	{

		Engines.clear();
		Balls.clear();
		maxR = 0.0f;
		if (!destroyed)
		{
			front = &CP.body[0];
			back = &CP.body[1];



			CP.freq = freq;
			CP.id = id;

			for (int i = 0; i < Parts.size(); i++)
			{
				float len = sqrlength(Parts[i]->body[0].position - CenterOfMass);
				if (len > maxR)
					maxR = len;
			}
			maxR += 32.0f;
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

				if (!Parts[i]->dead||i==0)
				{
					Parts[i]->Process(dt);
				}


				Parts[i]->freq = freq;
				Parts[i]->deactivated = false;
				Parts[i]->targetrotpoint = GunsTargetrotPoint;

				if (FireGuns && Parts[i]->type == TYPE::WEAPON)
					Parts[i]->shot = true;
				else
					Parts[i]->shot = false;

				if (Parts[i]->type == TYPE::PROPULSION)
					Engines.push_back(Parts[i]);
			}
			CloseDamageSpheres.clear();

			avgvel /= mass;
			CenterOfMass /= mass;



			int pt = 0;
			while (pt < Parts.size())
			{
				if (Parts[pt]->Health <= 0.0f && pt < Parts.size() && Parts[pt] != &CP)
				{
					DeletePart(pt);
				}
				else
					pt++;
			}




			if (back != NULL && front != NULL)
			{
				direction = Normalize(front->position - back->position);

				float aligment = DOT(Normalize(direction), Normalize(glm::vec2(-LookAt.y, LookAt.x)));
				glm::vec2 dirTotrg = Normalize((trgPos - (CP.body[0].position + CP.body[1].position) * 0.5f));

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
			float distance = length(trgPos - (CP.body[0].position + CP.body[1].position) * 0.5f) + 0.001f;
			float entVelocity = length(avgvel) + 0.001f;
			maxVelocity = distance * ForceToThrustDirection * 0.01f / (mass)+0.001f;
			float friction = 0.0f;
			if (autocontrol)
			{
				

				glm::vec2 dir = ((trgPos - (CP.body[0].position + CP.body[1].position) * 0.5f) / distance);
				if (distance < 2)
				{
					CP.body[0].Force = dir * 10.0f;
					CP.body[1].Force = dir * 10.0f;
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

					glm::vec2 norm = Normalize(Rotate((CP.mid - trgPos), pi * 0.5f));
					Force -= DOT(norm, CP.body[0].velocity) * norm * 4.0f;

					//float forceNeeded = length(Force);// (maxVelocity - entVelocity)* mass / (ForceToThrustDirection);
					ThrustDirection = Force;
					/*if (DOT(ThrustDirection, dir) < 0.0f && DOT(avgvel, dir) < 0.0f)
						ThrustDirection += dir * 0.5f;*/
					//ThrustDirection -= glm::vec2(-dir.y, dir.x) * DOT(glm::vec2(-dir.y, dir.x), avgvel);
					if (distance < 10)
						friction = 1.0;
				}


				for (int i = 0; i < CP.bDCsize; i++)
				{
					if (CP.bDataConnections[i].name == "LMB") CP.bDataConnections[i].data = distance<200;
					if (CP.bDataConnections[i].name == "RMB") CP.bDataConnections[i].data = distance < 200;
					if (CP.bDataConnections[i].name == "MMB") CP.bDataConnections[i].data = distance < 200;
					if (CP.bDataConnections[i].name == "Shift") CP.bDataConnections[i].data = distance > 200; // MB implement a dodge for bots
					if (CP.bDataConnections[i].name == "Space") CP.bDataConnections[i].data = false; 
					if (CP.bDataConnections[i].name == "W") CP.bDataConnections[i].data = ThrustDirection.y > 0.0f;
					if (CP.bDataConnections[i].name == "A") CP.bDataConnections[i].data = ThrustDirection.x < 0.0f;
					if (CP.bDataConnections[i].name == "S") CP.bDataConnections[i].data = ThrustDirection.y < 0.0f;
					if (CP.bDataConnections[i].name == "D") CP.bDataConnections[i].data = ThrustDirection.x > 0.0f;
				}
				if (CP.vDataConnections[0].name == "MousePosition") CP.vDataConnections[0].data = GunsTargetrotPoint;

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

	void Draw(float dt)
	{

		for (int i = 0; i < Parts.size(); i++)
			Parts[i]->Draw();

		for (int i = 0; i < Connections.size(); i++)
			Connections[i].Draw(dt);
	}
	void DeleteConnections( int index, int index2)
	{
		for (int i = 0; i <Connections.size(); i++)
		{

			bool del = true;
			while (del)
			{
				del = false;
				if (i < Connections.size())
				{
					if ((Connections[i].part1 == index) ||
						(Connections[i].part2 == index))
					{
						del = true;
						Connections[i] = Connections[Connections.size() - 1];
						Connections.pop_back();
					}
					else if (Connections[i].part1 == index2)
						Connections[i].part1 = index;
					else if (Connections[i].part2 == index2)
						Connections[i].part2 = index;
				}
			}
		}
		for (int i = 0; i < DataConnections.size(); i++)
		{

			bool del = true;
			while (del)
			{
				del = false;
				if (i < DataConnections.size())
				{
					if ((DataConnections[i].part1 == index) ||
						(DataConnections[i].part2 == index))
					{
						del = true;
						DataConnections[i] = DataConnections[DataConnections.size() - 1];
						DataConnections.pop_back();
					}
					else if (DataConnections[i].part1 == index2)
						DataConnections[i].part1 = index;
					else if (DataConnections[i].part2 == index2)
						DataConnections[i].part2 = index;
				}
			}
		}
		

	}

	void DeleteSomeConnections( int Partindex, float chance)
	{
		for (int i = 0; i < Connections.size(); i++)
		{

			bool del = true;
			while (del)
			{
				del = false;
				
				if (i < Connections.size())
				{
					if ((Connections[i].part1 == Partindex) ||
						(Connections[i].part2 == Partindex))
					{
						if (rand() % 10000 * 0.0001f < chance)
						{
							del = true;
							Connections[i] = Connections[Connections.size() - 1];
							Connections.pop_back();
						}
					}
				}
			}
		}
		CheckPartsConnections();
	}


	void DeletePart(int  index)
	{
		glm::vec2 mid = { 0.0f,0.0f };
	/*	for (int i = 0; i < Parts[index]->bodysize; i++)
		{
			Sparks.Spawn(Parts[index]->body[i].position, 15);
			Smoke.Spawn(Parts[index]->body[i].position, 15);
			DebrieParticles.RotationVelocity = rand() % 100 * 0.1f - 5.0f;
			DebrieParticles.Spawn(Parts[i]->body[i].position, 3);
			mid += Parts[index]->body[i].position;
		}*/
		mid /= Parts[index]->bodysize;

		for (int bp = 0; bp < Parts[index]->bodysize; bp++)
		{
			if (GrabbedBall != NULL)
				if (GrabbedBall->position == Parts[index]->body[bp].position)
					GrabbedBall = NULL;
			if (SelectedPart = index)
				SelectedPart = -1;
		}
		if (Parts[index]->source != 0)
		{
			StopSource(&Parts[index]->source);
			alDeleteSources(1, &Parts[index]->source);
		}
		Parts[index]->Health = -10;
		DetachPart(index);
		PlaySound(&PartDestrSOund, mid, 0.085f + rand() % 100 * 0.001f, 0.25f);


	}

	

	void DetachPart( int  index)
	{

		Parts[index]->shutdown = false;
		Parts[index]->shot = false;
		for (int i = 0; i < Parts[index]->bDCsize; i++)
			Parts[index]->bDataConnections[i].data = false;

		for (int i = 0; i < Parts[index]->fDCsize; i++)
			Parts[index]->fDataConnections[i].data = 0;

		for (int i = 0; i < Parts[index]->vDCsize; i++)
			Parts[index]->vDataConnections[i].data = {0.0f,0.0f};



		Debris.Parts.push_back(Parts[index]);
		//Parts[index]->attached = false;
		int index2 = Parts.size() - 1;
		DeleteSource(&Parts[index]->source);
		Parts[index] = Parts[Parts.size() - 1];
		Parts.pop_back();


		DeleteConnections( index, index2);

		CheckPartsConnections();
	}


	void DetachDetachedParts()
	{
		for (int i = 0; i < Parts.size(); i++)
		{
			bool del = true;
			while (i < Parts.size() && del)
			{
				del = false;
				if (!Parts[i]->attached)
				{
					DetachPart(i);
					del = true;
				}
			}
		}
	}


	
	bool CheckPartConnections(Connection* c)
	{
		bool changed = false;
		if(c->bod1 != NULL && c->bod2 != NULL)
		if (
			c->bod1->attached ||
			c->bod2->attached
			)
		{
			if (!c->bod1->attached || !c->bod2->attached)
				changed = true;

			c->bod1->attached = true;
			c->bod2->attached = true;
		}
		return changed;
	}

	void CheckPartsConnections()
	{

		for (int i = 0; i < Parts.size(); i++)
			Parts[i]->attached = false;

		bool End = false;
		Parts[0]->attached = true;// central part
		while (!End)
		{
			End = true;

			for (int i = 0; i < Connections.size(); i++)
				if (CheckPartConnections(&Connections[i]))
					End = false;

		
		}

		DetachDetachedParts();
	}


	int ClaimPart(int index)
	{
		Parts.push_back(Debris.Parts[index]);
		Parts[Parts.size() - 1]->debris = false;
		Parts[Parts.size() - 1]->GenSoundSource();
		Debris.Parts[index] = Debris.Parts[Debris.Parts.size() - 1];
		Debris.Parts.pop_back();
		return Parts.size() - 1;
	}


	void AddConnection(int type, float len, float width, float stiffness, float absorbtion, float HeatTransferSpeed,
		int part1, int  index1,
		int part2, int  index2)
	{
		
		int it = -1;
		for (int i = 0; i < Connections.size(); i++)
		{
			if (
				((Connections[i].part1 == part1 && Connections[i].index1 == index1 || Connections[i].part1 == part2 && Connections[i].index1 == index2) ) &&
				((Connections[i].part2 == part2 && Connections[i].index2 == index2 || Connections[i].part2 == part1 && Connections[i].index2 == index1) )
				)
				it = i;//cut connection [i]

		}

		if (it < 0)
		{
			Connection c;
			c.absorbtion = absorbtion;

			c.stiffnes = stiffness;
			c.width = width;
			c.part1 = part1;
			c.part2 = part2;
			c.index1 = index1;
			c.index2 = index2;
			c.HeatTransferSpeed = HeatTransferSpeed;
			c.type = type;

			Connections.push_back(c);
			int i = Connections.size() - 1;
			Connections[i].Init();
			if (len < 0)
			{
				Connections[i].UpdateLinks(this);

				Connections[i].length = length(Connections[i].b1->position - Connections[i].b2->position);
			}
			else
				Connections[i].length = len;
		}
		else if (it >= 0)
		{
			Connections[it] = Connections[Connections.size() - 1];
			Connections.pop_back();
			PlaySound(&Detach, MousePosition, 3.5f, 0.3f);
			CheckPartsConnections();
		}
		
	}
	void AddDataConnection(int type, int part1, int  index1, int part2, int  index2)
	{
		if (part1 != part2)
		{
			int it = -1;
			int index1amount = 0;
			int index2amount = 0;

			int lasti1 = -1;
			int lasti2 = -1;
			for (int i = 0; i < DataConnections.size(); i++)
			{
				if (DataConnections[i].type == type &&
					(DataConnections[i].part1 == part1 || DataConnections[i].part1 == part2) &&
					DataConnections[i].index1 == index1 &&
					(DataConnections[i].part2 == part2 || DataConnections[i].part2 == part1) &&
					DataConnections[i].index2 == index2)
					it = i;//cut connection [i]

				if (DataConnections[i].type == type &&
					((DataConnections[i].part1 == part1 && DataConnections[i].index1 == index1) ||
					(DataConnections[i].part2 == part1 && DataConnections[i].index2 == index1)))
				{
					index1amount++;
					lasti1 = i;
				}
				if (DataConnections[i].type == type &&
					((DataConnections[i].part1 == part2 && DataConnections[i].index1 == index2) ||
					(DataConnections[i].part2 == part2 && DataConnections[i].index2 == index2)))
				{
					index2amount++;
					lasti2 = i;
				}
			}
			/*std::cout << "{";
			std::cout << "index1amount ";
			std::cout << index1amount;
			std::cout << " index2amount ";
			std::cout << index2amount;*/
			if (it == -1)
			{
				DataConnection dc;
				dc.part1 = part1;
				dc.part2 = part2;
				dc.index1 = index1;
				dc.index2 = index2;
				dc.type = type;

				bool s1 = false;
				bool s2 = false;
				if (Parts[part1]->bDataConnections[index1].source && type == 0 ||
					Parts[part1]->fDataConnections[index1].source && type == 1 ||
					Parts[part1]->vDataConnections[index1].source && type == 2)
					s1 = true;
				if (Parts[part2]->bDataConnections[index2].source && type == 0 ||
					Parts[part2]->fDataConnections[index2].source && type == 1 ||
					Parts[part2]->vDataConnections[index2].source && type == 2)
					s2 = true;

				//std::cout << " s1 ";
				//std::cout << s1;
				//std::cout << " s2 ";
				//std::cout << s2;
				//std::cout << "}";
				if (s1 != s2)
				{
					if (!s1 && index1amount > 0)
					{

						DataConnections[lasti1] = DataConnections[DataConnections.size() - 1];
						DataConnections.pop_back();
						PlaySound(&Detach, MousePosition, 3.5f, 0.3f);
						DataConnections.push_back(dc);
					}
					else if (!s2 && index2amount > 0)
					{

						DataConnections[lasti2] = DataConnections[DataConnections.size() - 1];
						DataConnections.pop_back();
						PlaySound(&Detach, MousePosition, 3.5f, 0.3f);
						DataConnections.push_back(dc);
					}
					else
						DataConnections.push_back(dc);
				}
			}
			else if(it>=0)
			{
				DataConnections[it] = DataConnections[DataConnections.size() - 1];
				DataConnections.pop_back();
				PlaySound(&Detach, MousePosition, 3.5f, 0.3f);
			}
		}
	}

	void SaveTo(std::string filename)
	{
		std::ofstream f;
		f.open(filename);

		glm::vec2 mid = 0.5f * (Parts[0]->body[0].position + Parts[0]->body[1].position);

		for (int i = 1; i < Parts.size(); i++) // skip part[0] - central part
		{
			f << "P ";
			f << Parts[i]->partid;
			f << " ";
			f << Parts[i]->bodysize;
			for (int a = 0; a < Parts[i]->bodysize; a++)
			{
				f << " ";
				f << Parts[i]->body[a].position.x - mid.x;
				f << " ";
				f << Parts[i]->body[a].position.y - mid.y;
			}
			f << "\n";
		}

		for (int i = 0; i < Connections.size(); i++)
		{
			f << "C ";
			f << Connections[i].type;
			f << " ";
			f << Connections[i].length;
			f << " ";
			f << Connections[i].width;
			f << " ";
			f << Connections[i].stiffnes;
			f << " ";
			f << Connections[i].absorbtion;
			f << " ";
			f << Connections[i].HeatTransferSpeed;
			f << " ";
			f << Connections[i].part1;
			f << " ";
			f << Connections[i].index1;
			f << " ";
			f << Connections[i].part2;
			f << " ";
			f << Connections[i].index2;
			f << "\n";
		}
		for (int i = 0; i < DataConnections.size(); i++)
		{
			f << "D ";
			f << DataConnections[i].type;
			f << " ";
			f << DataConnections[i].part1;
			f << " ";
			f << DataConnections[i].index1;
			f << " ";
			f << DataConnections[i].part2;
			f << " ";
			f << DataConnections[i].index2;
			f << "\n";
		}
		f.close();
	}

	void LoadFrom(std::string filename)
	{

		glm::vec2 mid = 0.5f * (Parts[0]->body[0].position + Parts[0]->body[1].position);
		DeleteSoundSources();
		Clear();

		std::ifstream f(filename);
		if (!f.is_open())
		{
			std::cerr << "ERROR LOADING MAP: Unable to load " << filename;
			return;
		}
		while (!f.eof())
		{
			char junk;
			char line[256];
			f.getline(line, 256);
			std::strstream s;
			s << line;
			if (line[0] == 'P')
			{
				std::vector<glm::vec2> positions;

				int type = 0;
				int bodysize = 0;

				s >> junk >> type >> bodysize;
				for (int i = 0; i < bodysize; i++)
				{
					float x = 0;
					float y = 0;

					s >> x >> y;
					positions.push_back({ x,y });
				}
				BodyComponent* b = CreatePart(type, { 0.0f,0.0f }, { 0.0f,1.0f }, PARTSIZE);

				for (int i = 0; i < bodysize; i++)
					b->body[i].position = positions[i]+ mid;
				Parts.push_back(b);
			}

			if (line[0] == 'C')
			{
				int type;
				float len;
				float width;
				float stiffness;
				float absorbtion;
				float HeatTransferSpeed;
				int part1;
				int index1;
				int part2;
				int index2;

				s >>junk>> type >> len >> width >> stiffness >> absorbtion 
					>> HeatTransferSpeed >> part1 >> index1 >> part2 >> index2;

				AddConnection(type, len, width, stiffness, absorbtion, HeatTransferSpeed,
					part1, index1,
					part2, index2);
			}
			if (line[0] == 'D')
			{
				int type;
				int part1;
				int index1;
				int part2;
				int index2;

				s >> junk >> type >> part1 >> index1 >> part2 >> index2;
				/*std::cout<< "adding dc: ";
				std::cout << type << ' ';
				std::cout << part1 << ' ';
				std::cout << index1 << ' ';
				std::cout << part2 << ' ';
				std::cout << index2 << ' ';*/
				AddDataConnection(type,part1, index1, part2, index2);

				/*std::cout << "consize = " << DataConnections.size();
				std::cout <<  '\n';*/
			}

		}
		f.close();


	}

	void Clear()
	{
		for (int i = 1; i < Parts.size(); i++)
			Parts[i]->Delete();
		Parts.clear();
		Parts.push_back(&CP);
		Connections.clear();
		DataConnections.clear();
	}

	void Destroy()
	{

		DeleteSoundSources();


		for (int i = 0; i < Parts.size(); i++)
		{
			if (rand() % 100 < 50)
				for (int b = 0; b < Parts[i]->bodysize; b++)
					Parts[i]->body[b].Force = glm::vec2(rand() % 5000 - 2500, rand() % 5000 - 2500);
			else
				Parts[i]->Health = -1.0f;
		}
		Connections.clear();
		CheckPartsConnections();
		destroyed = true;
	}
};
std::vector <Entity*> Entities;
int _MultithreadEntitiesProcesStep = 0;

int lastEntityID = 0;

float subdt = 0.0017;


void ProcessEntities(float dt,int substeps)
{
	subdt = dt / substeps;
	std::vector<int> iter;
	for (int i = 0; i < threadcount; i++)
		iter.push_back(i);

	for (int s = 0; s < substeps; s++)
	{
		ProcessDamageSpheres(subdt);
		ProcessLasers(subdt, false);
		ProcessBullets(subdt, s == 0);

		ProcessRockets(subdt);

		for (int x = 0; x < 300; x++)
			for (int y = 0; y < 300; y++)
				Grid[x][y].size = 0;
		balls.clear();
		// Multithreading requires more changes to the core of game (Errors in ParticleSystems and damagespheres) so it is disabled

		_MultithreadEntitiesProcesStep = Entities.size() / threadcount;
		std::for_each( iter.begin(), iter.end(), [](int thr) //std::execution::par,
			{
				int end = _MultithreadEntitiesProcesStep * (thr + 1);
				if (thr == threadcount - 1)
					end = Entities.size();

				for (int i = _MultithreadEntitiesProcesStep * thr; i < end; i++)
					if (Entities[i]->Alive)
					{
						Entities[i]->freq = Speed;


						if (Entities[i]->autocontrol && i != 0)
						{
							Entities[i]->GunsTargetrotPoint = Entities[0]->CP.mid;
							Entities[i]->trgPos = Entities[0]->CP.mid + Normalize(Entities[i]->CP.mid - Entities[0]->CP.mid) * (Entities[i]->maxR + 30.0f);

						}
						Entities[i]->Process(subdt);
					}
			});

		
		Debris.Process(subdt, s, s == substeps - 1);
		balltaken = false;


		for (int i = 0; i < Debris.Parts.size(); i++)
			for (auto pid : Debris.Parts[i]->BodyIdsWithCollision)
				balls.push_back(&Debris.Parts[i]->body[pid]);

		for (int e = 0; e < Entities.size(); e++)
			for (int i = 0; i < Entities[e]->Parts.size(); i++)
				for (auto pid : Entities[e]->Parts[i]->BodyIdsWithCollision)
					balls.push_back(&Entities[e]->Parts[i]->body[pid]);

		
		for (int i = 0; i < balls.size(); i++)
		{
			// friction
			balls[i]->velocity -= balls[i]->velocity * sqrlength(balls[i]->velocity) * subdt * 0.000002f;
			glm::vec2 offset = Entities[0]->CP.mid + glm::vec2(-150, -150);
			int x = roundf(balls[i]->position.x - offset.x);
			int y = roundf(balls[i]->position.y - offset.y);
			//std::cout << x << "			" << y << "\n";
			if (y >= 0 && y < 300 &&
				x >= 0 && x < 300)
				Grid[x][y].add(balls[i]);

			balls[i]->rotation = 0.0f;
			balls[i]->rotationVelocity = 0.0f;
			balls[i]->roughness = 0.8f;

			glm::vec2 pVel = balls[i]->velocity;
			for (int a = 0; a < Map.balls.size(); a++)
			{
				BtBCollision(balls[i], &Map.balls[a]);
				Map.balls[a].velocity *= 0.0f;

			}

			for (int a = 0; a < Map.cubes.size(); a++)
				if (Map.cubes[a].id == -1)
					BallToStaticQuadCollision(balls[i], Map.cubes[a]);
			glm::vec2 aVel = balls[i]->velocity;

			if ((!snapToGrid || !BuildingMode))
			{
				float maxdif = 7.0f;

				glm::vec2 dif = pVel - aVel;
				float len = sqrlength(dif);
				if (len > maxdif * maxdif)
				{//heavy collision
					len = sqrt(len);

					glm::vec2 position = balls[i]->position + balls[i]->GroundVector * balls[i]->r;
					int amount = rand() % 10 + 0.001f * len;
					for (int a = 0; a < amount; a++)
						CollisionSparks.Spawn(position,
							-balls[i]->GroundVector * 150.0f * len * 0.001f + (rand() % 100 - 50.0f) * glm::vec2(-balls[i]->GroundVector.y, balls[i]->GroundVector.x) * len * 0.001f +
							Rotate(balls[i]->GroundVector * DOT(Rotate(balls[i]->GroundVector, pi * 0.5f), pVel * 0.1f)
								* float(rand() % 100) * 0.1f, pi * 0.5f),
							1);
					CollisionSmoke.Spawn(position,
						15);
					if(balls[i]->Source == 0 || !SourcePlaying(balls[i]->Source) || *balls[i]->Source == 0)
						PlaySound(&balls[i]->Source, &Hit, position, 0.1f + (rand() % 100 * 0.00025f), 0.25f);

				}

			}



			if (BuildingMode)
			{
				if (in_UI <= 0)
					if (JustPressedbutton[GLFW_MOUSE_BUTTON_2])
						if (BalltoPointCollisionCheck(*balls[i], MousePosition) && !balltaken)
						{
							balltaken = true;
							GrabbedBall = balls[i];
						}

				if (JustReleasedbutton[GLFW_MOUSE_BUTTON_2])
					GrabbedBall = NULL;


				if (keys[GLFW_KEY_LEFT_ALT])
					DrawCircle(*balls[i], glm::vec4(0.1f, 0.1f, 1.0f, 1.0f), false, BallNormalMapTexture, 10);

				else if (keys[GLFW_KEY_LEFT_SHIFT])
					DrawCircle(*balls[i], glm::vec4(1.1f, 0.1f, 0.1f, 1.0f), false, BallNormalMapTexture, 10);

				if (snapToGrid)
				{
					balls[i]->velocity -= balls[i]->velocity * length(balls[i]->velocity) * subdt * 2.0f;

					/*glm::vec2 snapvector = glm::vec2(
						((int)(balls[i]->position.x + 40 - 3000) % 1),
						((int)(balls[i]->position.y - 40 - 3000) % 1)
					);*/
					glm::vec2 snapvector = glm::vec2(
						roundf(balls[i]->position.x),
						roundf(balls[i]->position.y)
					);

					DrawCircle(snapvector, 0.25f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), false, BallNormalMapTexture, 1000);

					balls[i]->Force += (snapvector - balls[i]->position) * 10.0f;
				}
			}
			else
			{
				GrabbedBall = NULL;
			}

		}

	
		for (int x = 1; x < 300; x++)
			for (int y = 1; y < 300; y++)
			{
				if (Grid[x][y].size <= 0)
					continue;
				balllbuffersize = 0;
				for (int i = 0; i < Grid[x][y].size; i++)
				{
					ballbuffer[balllbuffersize] = Grid[x][y].balls[i];
					balllbuffersize++;
				}
				for (int i = 0; i < Grid[x - 1][y].size; i++)
				{
					ballbuffer[balllbuffersize] = Grid[x - 1][y].balls[i];
					balllbuffersize++;
				}
				for (int i = 0; i < Grid[x][y - 1].size; i++)
				{
					ballbuffer[balllbuffersize] = Grid[x][y - 1].balls[i];
					balllbuffersize++;
				}

				for (int i = 0; i < balllbuffersize - 1; i++)
				{
					bool NotSelfCollision = false;

					glm::vec2 pVel = ballbuffer[i]->velocity;
					for (int a = i + 1; a < balllbuffersize; a++)
					{
						if (!NotSelfCollision)
							NotSelfCollision = ballbuffer[i] != ballbuffer[a];
						BtBCollision(ballbuffer[i], ballbuffer[a]);
					}
					glm::vec2 aVel = ballbuffer[i]->velocity;


					if (ballbuffer[i]->Source == NULL || *ballbuffer[i]->Source == 0 || ((!snapToGrid || !BuildingMode) && NotSelfCollision && !SourcePlaying(ballbuffer[i]->Source)))
					{
						float maxdif = 7.0f;

						glm::vec2 dif = pVel - aVel;
						float len = sqrlength(dif);
						if (len > maxdif * maxdif)
						{//heavy collision
							len = sqrt(len);

							glm::vec2 position = ballbuffer[i]->position + ballbuffer[i]->GroundVector * ballbuffer[i]->r;
							int amount = rand() % 10 + 0.001f * len;
							for (int a = 0; a < amount; a++)
								CollisionSparks.Spawn(position,
									-ballbuffer[i]->GroundVector * 150.0f * len * 0.001f + (rand() % 100 - 50.0f) * glm::vec2(-ballbuffer[i]->GroundVector.y, ballbuffer[i]->GroundVector.x) * len * 0.001f +
									Rotate(ballbuffer[i]->GroundVector * DOT(Rotate(ballbuffer[i]->GroundVector, pi * 0.5f), pVel * 0.1f)
										* float(rand() % 100) * 0.1f, pi * 0.5f),
									1);
							CollisionSmoke.Spawn(position,
								15);

							PlaySound(&ballbuffer[i]->Source, &Hit, position, 0.1f + (rand() % 100 * 0.00025f), 0.25f);

						}

					}
				}

				balllbuffersize = 0;
			}


		for (int i = 0; i < Entities.size(); i++)
		{
			bool del = true;
			while (i < Entities.size() && del)
			{
				del = false;
				if (!Entities[i]->Alive && !Entities[i]->destroyed || Entities[i]->CP.Health<=0.0f)
				{
					del = true;
					
					LightEffect le;
					le.volume = 0.005f;
					le.S_Color = { 1.0f,20.0f,200.0f,1.0f };
					le.S_Scale = 250.0f;
					le.time = 3.0f;
					le.maxT = 3.0f;
					le.position = glm::vec3(Entities[i]->CP.mid,0.0f);
					LightEffects.push_back(le);
					Entities[i]->Destroy();
					Entities[i]->CP.Delete();
					Entities[i] = Entities[Entities.size() - 1];
					Entities.pop_back();
				}
			}
		}


	}

	for (int i = 0; i < Entities.size(); i++)
		if (Entities[i]->Alive)
			Entities[i]->Draw(dt);

	ProcessLasers(subdt, true,true);
	ProcessExplodions(dt);
	DrawRockets();
}
