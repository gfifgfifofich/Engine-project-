#pragma once




ParticleEmiter CollisionSparks;
ParticleEmiter CollisionSmoke;




void PartsPile::Process(float dt, int iter,bool lastiter)
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
			//if (!Parts[i]->dead)
			//{

			//	Parts[i]->Process(dt);
			//	if (lastiter)
			//		Parts[i]->Draw();
			//}
			for (int a = 0; a < GameScene->Collision_cubes.size(); a++)
				if (GameScene->Collision_cubes[a]->id == 1)
					for (int bp = 0; bp < Parts[i]->bodysize; bp++)
					{
						if (BtCCollisionCheck(Parts[i]->body[bp], *GameScene->Collision_cubes[a]))
						{
							Parts[i]->Health = -1.0f;
						}
					}
			for (int a = 0; a < GameScene->Collision_balls.size(); a++)
				if (GameScene->Collision_balls[a]->id == 1)
					for (int bp = 0; bp < Parts[i]->bodysize; bp++)
					{
						if (BtBCollisionCheck(Parts[i]->body[bp], *GameScene->Collision_balls[a]))
						{
							Parts[i]->Health = -1.0f;
						}
					}
		}
	}
	CloseDamageSpheres.clear();
}
void PartsPile::DeletePart(int  index)
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
	Parts[index]->Delete=true;
	Parts[index] = Parts[Parts.size() - 1];
	Parts.pop_back();
	PlaySound(&PartDestrSOund, mid, 0.085f+rand()%100*0.001f, 0.25f);
}
void PartsPile::SpawnPart(int type, glm::vec2 position, float size)
{
		
	BodyComponent* b = CreatePart(type, position, { 0.0f,1.0f }, size);

	
	if(b!=NULL)
		Parts.push_back(b);
	
}
void PartsPile::SpawnRandomPart( glm::vec2 position, float size)
{
	int type = rand() % 7;
	SpawnPart(type, position, size);
}


std::vector <CentralPart*> Entities;


void CentralPart::DeletePart() 
	{
		Delete = true;
		DeleteBody();
	}
void CentralPart::DeleteConnections( int index, int index2)
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
void CentralPart::DeleteSomeConnections( int Partindex, float chance)
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
	}
void CentralPart::DestroyPart(int  index)
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
void CentralPart::DetachPart( int  index)
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

	}
void CentralPart::DetachDetachedParts()
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
bool CentralPart::CheckPartConnections(Connection* c)
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
void CentralPart::CheckPartsConnections()
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
int CentralPart::ClaimPart(int index)
	{
		Parts.push_back(Debris.Parts[index]);
		Parts[Parts.size() - 1]->debris = false;
		Parts[Parts.size() - 1]->GenSoundSource();
		Debris.Parts[index] = Debris.Parts[Debris.Parts.size() - 1];
		Debris.Parts.pop_back();
		return Parts.size() - 1;
	}
void CentralPart::AddConnection(int type, float len, float width, float stiffness, float absorbtion, float HeatTransferSpeed,
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
void CentralPart::AddDataConnection(int type, int part1, int  index1, int part2, int  index2)
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
void CentralPart::SaveTo(std::string filename)
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
void CentralPart::LoadFrom(std::string filename)
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
	firstdrawafterload = true;
	
}
void CentralPart::Clear()
{
	for (int i = 1; i < Parts.size(); i++)
		Parts[i]->Delete=true;
	Parts.clear();
	Parts.push_back(this);
	Connections.clear();
	DataConnections.clear();
	firstdrawafterload = true;
}
void CentralPart::Destroy()
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
	firstdrawafterload = true;
}
	

int _MultithreadEntitiesProcesStep = 0;

int lastEntityID = 0;

float subdt = 0.0017;

void EntityToEntityCollision(CentralPart* e1, CentralPart* e2)
{
	ball e1Collider;
	e1Collider.position = e1->CenterOfMass;
	e1Collider.r = e1->maxR;
	ball e2Collider;
	e2Collider.position = e2->CenterOfMass;
	e2Collider.r = e2->maxR;
	if(!BtBCollisionCheck(e1Collider,e2Collider))
		return;

	if(e1->Balls.size()>e2->Balls.size())
		for(auto i : e1->Balls)
			for(auto a : e2->Balls)
				BtBCollision(i,a);
	else
		for(auto i : e2->Balls)
			for(auto a : e1->Balls)
				BtBCollision(i,a);

	/*
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
				if (ballbuffer[i]->soundcd <=0.0f  && ((!snapToGrid || !BuildingMode) && NotSelfCollision))
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

						PlayCollisionSound(ballbuffer[i]->position);
						ballbuffer[i]->soundcd = 1.0f; 
					}

				}
			}

			balllbuffersize = 0;
		}
	*/
}

void ProcessEntities(float dt,int s)
{
	subdt = dt / substeps;

	// refactor required
	ProcessDamageSpheres(subdt);
	ProcessLasers(subdt, false);
	ProcessBullets(subdt, s==0);
	ProcessRockets(subdt);
	ProcessLasers(subdt, true,true);//?

	//for (int x = 0; x < 300; x++)
	//	for (int y = 0; y < 300; y++)
	//		Grid[x][y].size = 0;
	balls.clear();
	


	for (int i = 0; i < Entities.size(); i++)
		if (Entities[i]->Alive)
		{
			Entities[i]->freq = Speed;


			if (Entities[i]->autocontrol && i != 0)
			{
				Entities[i]->GunsTargetrotPoint = Entities[0]->mid;
				Entities[i]->trgPos = Entities[0]->mid + Normalize(Entities[i]->mid - Entities[0]->mid) * (Entities[i]->maxR + 30.0f);

			}
		}
		
	
	Debris.Process(subdt, s, s == substeps - 1);
	balltaken = false;


	for (int i = 0; i < Debris.Parts.size(); i++)
		for (auto pid : Debris.Parts[i]->BodyIdsWithCollision)
			balls.push_back(&Debris.Parts[i]->body[pid]);

	for (int e = 0; e < Entities.size(); e++)
		for (int i = 0; i < Entities[e]->Balls.size(); i++)
			balls.push_back(Entities[e]->Balls[i]);

	
	for (int i = 0; i < balls.size(); i++)
	{
		// friction
		balls[i]->velocity -= balls[i]->velocity * sqrlength(balls[i]->velocity) * subdt * 0.000002f;
		glm::vec2 offset = Entities[0]->mid + glm::vec2(-150, -150);
		//int x = roundf(balls[i]->position.x - offset.x);
		//int y = roundf(balls[i]->position.y - offset.y);
		////std::cout << x << "			" << y << "\n";
		//if (y >= 0 && y < 300 &&
		//	x >= 0 && x < 300)
		//	Grid[x][y].add(balls[i]);

		balls[i]->rotation = 0.0f;
		balls[i]->rotationVelocity = 0.0f;
		balls[i]->roughness = 0.8f;
		balls[i]->soundcd -= subdt; 
		if(balls[i]->soundcd <-1.0f)
			balls[i]->soundcd = -1.0f;

		glm::vec2 pVel = balls[i]->velocity;
		for (int a = 0; a < GameScene->Collision_balls.size(); a++)
		{
			BtBCollision(balls[i], GameScene->Collision_balls[a]);
			GameScene->Collision_balls[a]->velocity *= 0.0f;

		}

		for (int a = 0; a < GameScene->Collision_cubes.size(); a++)
			if (GameScene->Collision_cubes[a]->id == -1)
				BallToStaticQuadCollision(balls[i], *GameScene->Collision_cubes[a]);
		glm::vec2 aVel = balls[i]->velocity;

		if (balls[i]->soundcd <=0.0f && (!snapToGrid || !BuildingMode))
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
				
				PlayCollisionSound(ballbuffer[i]->position);
				balls[i]->soundcd = 1.0f; 
				
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

	/*
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
				if (ballbuffer[i]->soundcd <=0.0f  && ((!snapToGrid || !BuildingMode) && NotSelfCollision))
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

						PlayCollisionSound(ballbuffer[i]->position);
						ballbuffer[i]->soundcd = 1.0f; 
					}

				}
			}

			balllbuffersize = 0;
		}
	*/

	int i = 0;
	while (i < Entities.size())
	{
		if (!Entities[i]->Alive && !Entities[i]->destroyed || Entities[i]->Health<=0.0f)
		{
			
			LightEffect le;
			le.volume = 0.005f;
			le.S_Color = { 1.0f,20.0f,200.0f,1.0f };
			le.S_Scale = 250.0f;
			le.time = 3.0f;
			le.maxT = 3.0f;
			le.position = glm::vec3(Entities[i]->mid,0.0f);
			LightEffects.push_back(le);
			Entities[i]->Destroy();
			Entities[i]->Delete=true;
			Entities[i] = Entities[Entities.size() - 1];
			Entities.pop_back();
		}
		else
		{
			for(int a = i+1; a< Entities.size();a++)
			{
				if (Entities[a]->Alive && Entities[a]->Health>0.0f)
					EntityToEntityCollision(Entities[i],Entities[a]);
			}
			i++;
		}
	}
	


	

}
