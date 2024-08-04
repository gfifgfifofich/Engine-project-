enum MissionType 
{
	mining =1,
	retrival =2,
	pirates =3,
	infestation =4
};
class Mission
{
	public:
	bool exitedmission = false;
	int type = 0;
	int dificulty = 0;
	int size = 0;
	int materialReward = 0;
	std::vector<CentralPart*> AIShips;
	std::vector<unsigned int> AIShipsIds;
	std::vector<float> timers;
	std::map<std::string,bool> flags;
	bool story_mission = false;

	std::vector<glm::vec4> TakenAreas;

	//Shit for missions
	glm::vec2 planetpos = {0.0f,0.0f};
	
	void Start()
	{
		timers.clear();
		inbase = false;
		TakenAreas.clear();
		TakenAreas.push_back({0,0,50,50});
		AIShips.clear();
		flags.clear();
		if(Entities.size()>0)
			Entities[0]->SaveTo(EntityBackUpName);
		//ClearMap
		ChangeMap("",false);
		SpawnPlayer(EntityBackUpName);
		Materials -= GetShipCost(Entities[0]);
		if(!story_mission)
		{	for(int i=0;i<size * 5;i++)
			{
				glm::vec2 randpos = glm::vec2(float((rand() % 1000) - 500),float((rand() % 1000) - 500));
				glm::vec2 randsize = glm::vec2(float((rand() % 50) + 50),float((rand() % 50) + 50));
				bool clear = false;
				while(!clear)
				{
					randpos = glm::vec2(float((rand() % 1000) - 500),float((rand() % 1000) - 500));
					randsize = glm::vec2(float((rand() % 50) + 50),float((rand() % 50) + 50));
					clear = true;
					for(auto v : TakenAreas)
					{
						if(randpos.x > v.x-v.z && randpos.x < v.x+v.z && randpos.y > v.y-v.w && randpos.y < v.y+v.w)
							clear = false;
					}
				}
				TakenAreas.push_back(glm::vec4(randpos,randsize));

				int ballscount = rand() %5 + 5;
				for(int a=0;a<ballscount;a++)
				{
					CO_Ball* newball = new CO_Ball();
					newball->position = randpos + glm::vec2(rand() % (int)randsize.x * 0.5f,rand() % (int)randsize.y * 0.5f);
					newball->b.position = newball->position;
					newball->Mater = &MO_Ball;
					newball->b.r = rand() % (int)randsize.x * 0.5f;
					newball->Scale = glm::vec2(newball->b.r, newball->b.r);
					newball->ForceMaterialCheck = false;
					GameScene->Nodes.push_back(newball);
				}
			}

		
		//Create random stuff;

			switch (type)
			{
			case MissionType::mining:
			{

			}break;
			case MissionType::retrival:
			{

			}break;
			case MissionType::pirates:
			{
				for(int i=0;i<size;i++)
				{
					glm::vec2 randpos = glm::vec2(float((rand() % 1000) - 500),float((rand() % 1000) - 500));
					bool clear = false;
					while(!clear)
					{
						randpos = glm::vec2(float((rand() % 1000) - 500),float((rand() % 1000) - 500));
						clear = true;
						for(auto v : TakenAreas)
						{
							if(randpos.x > v.x-v.z && randpos.x < v.x+v.z && randpos.y > v.y-v.w && randpos.y < v.y+v.w)
								clear = false;
						}
					}
					int randshipid = rand()% shipNames.size(); 
					AIShips.push_back(SpawnAiShip(randpos,"Save0"));
					AIShipsIds.push_back(AIShips[AIShips.size()-1]->id);
					TakenAreas.push_back(glm::vec4(randpos,AIShips[AIShips.size()-1]->maxR,AIShips[AIShips.size()-1]->maxR));
				}


			}break;
			case MissionType::infestation:
			{

			}
			default:
				break;
			}
		}else
			switch (storyint)
			{
			case 0: // tutorial
			{
				AmbientLight=  0.0f;
				Background.LoadFrom("Scenes/Sun.sav");
				ChangeMap("Scenes/tutorial.sav",false);
				SpawnPlayer("No");
				Entities[0]->body[0].position = {15.0f,0.0f};
				Entities[0]->body[1].position = {15.0f,2.0f};
				timers.push_back(2.0f);
				timers.push_back(0.0f);
				timers.push_back(0.0f);
				timers.push_back(0.5f);//door timers [3],[4]
				timers.push_back(0.0f);
				flags["Explode"] = false;
				flags["Spawned"] = false;
				for(int i=0;i<8;i++)
					Debris.SpawnPart(PART::ROCKETENGINE,{i + 11.5f,5.0f},PARTSIZE);
				AqueredCameraScale = {20.0f,20.0f};

				glm::vec2 pos = {30.0f,100.0f};
				Debris.SpawnPart(PART::RADIATOR,pos,PARTSIZE);
				pos = { 30.0f,200.0f};
				Debris.SpawnPart(PART::GUN,pos,PARTSIZE);

				for(int i=0;i<GameScene->Nodes.size();i++)
				{
					if(GameScene->Nodes[i]->id == 5)// first corner
					{
						break;
					}
				}


			}break;
			default:
				break;
			}
	}
	void CheckShips(float dt)
	{
		AIShips.clear();
		int AIShipsi =0; 
		if(Entities.size()>0) 
		while(AIShipsi<AIShipsIds.size())
		{
			int i=0;
			for(int i = 1;i <Entities.size();i++)// first is player
				if(Entities[i]->id == AIShipsIds[AIShipsi])
					AIShips.push_back(Entities[i]);
			AIShipsi++;
		}
	}
	void Process(float dt)
	{
		
		
		
		for(int i=0;i<timers.size();i++)
		{
			timers[i]-=dt;
			if(timers[i]<0.0f)
				timers[i]=0.0f;
			
		}
		if(!story_mission)
			switch (type)
			{
			case MissionType::mining:
			{

			}break;
			case MissionType::retrival:
			{

			}break;
			case MissionType::pirates:
			{
				if(AIShips.size()==0)
					exitMission(true);

			}break;
			case MissionType::infestation:
			{

			}
			default:
				break;
			}
		else
			switch (storyint)
			{
			case 0: // tutorial
			{

				for(auto n : Background.Nodes)
				{
					if(n->Name == "Planet")
					{
						planetpos = n->position;
						if(flags["Explode"])
						{
							glm::vec4 col = glm::vec4(100.0f,2.0f,1.0f,1.0f) * (7.5f - timers[1]) * -2.0f + glm::vec4(0.1f,0.2f,1.0f,1.0f);
							if(col.r<0.1f)
								col.r = 0.1f;
							if(col.g<0.2f)
								col.g = 0.2f;
							if(col.b<1.0f)
								col.b = 1.0f;
							col.a = 1.0f;
							((Object*)n)->Color = col;
							if(timers[1] < 7.5f)
								n->Delete = true;
						}
					}
					if(flags["Explode"])
					{
						if(n->Name == "Planet2" && timers[1] < 7.5f)
							n->Delete = true;
						else if(n->Name == "PlanetP" && timers[1] < 7.5f)
							n->Delete = true;
					}
				}
				ParticleObject* PlanetExplodionPO = NULL; 
				for(auto n : Background.Nodes)
				{
					if(n->Name == "ExplodionP1" || n->Name == "ExplodionP2" || n->Name == "ExplodionP3")
					{
						n->position = planetpos;
						ParticleObject* po = (ParticleObject*)n; 
						PlanetExplodionPO = po;
						if(!flags["Explode"]  || timers[1] < 7.5f)
						{
							po->amount = 0;
							po->t = 0.0f;
							po->tick = 0.01f;
						}
						else  po->amount = 300;

						
					}
					else if(n->Name == "PLS")
					{
						LightSource* ls = (LightSource*)n;
						if(!flags["Explode"]) 
							ls->color = {10.0f,0.0f,110.0f,10.0f};
						else
							ls->color = glm::vec4(40.0f,5.0f,1.0f,1.5f) * timers[1]*0.125f;
					}
					else if(n->Name == "L1")
					{						
						Object* o = (Object*)n; 

						if(flags["Explode"])
							o->Scale.x = 105.0f * (timers[1] * 0.125f);
						else
							o->Scale.x = 0.0f;
												
						if(o->invertX)
							o->position = planetpos + glm::vec2(-o->Scale.x,900.0f);
						else
							o->position = planetpos + glm::vec2(o->Scale.x,900.0f);
						
					}
					else if(n->Name == "L2")
					{
						Object* o = (Object*)n; 

						if(flags["Explode"])
							o->Scale.x = 95.0f * (timers[1] * 0.125f);
						else
							o->Scale.x = 0.0f;

						if(o->invertX)
							o->position = planetpos + glm::vec2(-o->Scale.x,-700.0f);
						else
							o->position = planetpos + glm::vec2(o->Scale.x,-700.0f);
					}

				}
				// text at start {0.0f,0.0f}
				glm::vec2 pos = {-10.0f,0.0f};
				float stepy = 2.0f;
				float Tscale = 0.04f; 
				if(!BuildingMode)
					DrawText("Press B to enter building mode",pos-=glm::vec2(0.0f,stepy),Tscale);
				else{		
					DrawText("RMB to grab parts",pos-=glm::vec2(0.0f,stepy),Tscale);
					DrawText("LMB to make a stasis field",pos-=glm::vec2(0.0f,stepy),Tscale);
					DrawText("hold alt and click on blue circles to atach parts to your ship",pos-=glm::vec2(0.0f,stepy),Tscale);
				}
				pos = {-10.0f,50.0f};
				DrawText("W S - forward/backwards,",pos-=glm::vec2(0.0f,stepy),Tscale);
				DrawText("Q E - left/right,",pos-=glm::vec2(0.0f,stepy),Tscale);
				DrawText("A D - rotate left/right,",pos-=glm::vec2(0.0f,stepy),Tscale);
				
				pos = {-10.0f,100.0f};
				if(!BuildingMode)
					DrawText("Press B to enter building mode",pos-=glm::vec2(0.0f,stepy),Tscale);
				else{		
					DrawText("Attach radiator to the parts that need cooling",pos-=glm::vec2(0.0f,stepy),Tscale);
					DrawText("Use HeatPipes for better heat transfer (Tab to switch connection type)",pos-=glm::vec2(0.0f,stepy),Tscale);
				}
				pos = {-10.0f,200.0f};
				if(!BuildingMode)
					DrawText("Press B to enter building mode",pos-=glm::vec2(0.0f,stepy),Tscale);
				else{		
					DrawText("Atach weapon",pos-=glm::vec2(0.0f,stepy),Tscale);
					DrawText("In bottom left corner select vector logic",pos-=glm::vec2(0.0f,stepy),Tscale);
					DrawText("Connect weapon(target) to mouse position in central part",pos-=glm::vec2(0.0f,stepy),Tscale);
					DrawText("Select Bools logic, attach gun (Shoot) to any control in central part",pos-=glm::vec2(0.0f,stepy),Tscale);
				}
				if(!flags["Spawned"] || Entities.size()>1)
					timers[3] = 0.5f;
				if(!flags["Spawned"])
					timers[4] = 0.5f;
				
				for(int i=0;i<GameScene->Nodes.size();i++)
				{
					if(GameScene->Nodes[i]->type == NodeType::LIGHTSOURCEOBJECT)
					{
						LightSourceObject* ls = (LightSourceObject*) GameScene->Nodes[i];
						cube c;
						c.width = ls->Scale.x;
						c.height = ls->Scale.y;
						c.position = ls->position;
						if(Entities.size()>0 && PointToQuadCollisionCheck(c,Entities[0]->mid))
							ls->Color = {1.0f,1.0f,1.0f,1.0f}; 
						else
							ls->Color = {0.0f,0.0f,0.0f,0.0f}; 
							
						if(flags["Explode"])
						{
							ls->Color = glm::vec4(abs(sin(timers[1] * 100.0f))); 
						}
					}

					if(GameScene->Nodes[i]->type == NodeType::CO_CUBE && GameScene->Nodes[i]->Z_Index == 0)
					{
						GameScene->Nodes[i]->position.x =  roundf(GameScene->Nodes[i]->position.x/30.0f) * 30.0f;
						GameScene->Nodes[i]->position.y =  roundf(GameScene->Nodes[i]->position.y/30.0f) * 30.0f;
						((CO_Cube*) GameScene->Nodes[i])->Scale =  {15.0f,15.0f};
						((CO_Cube*) GameScene->Nodes[i])->c.width = 15.0f;
						((CO_Cube*) GameScene->Nodes[i])->c.height = 15.0f;
					}
					else
					{
						CO_Cube* cub= (CO_Cube*) GameScene->Nodes[i];
						//-30 - 60
						// 15 + (-45 * stage * -invertx) 
						//450
						//660
						if(cub->Z_Index == 2)
						{
							if(!cub->invertX)
								cub->position.x = (-30 * timers[4] * 2.0f);
							if(cub->invertX)
								cub->position.x = 30 + (30 * timers[4] * 2.0f);
						}
						if(cub->Z_Index == 3)
						{
							if(!cub->invertX)
								cub->position.x = (30 * timers[3] * 2.0f) - 30;
							if(cub->invertX)
								cub->position.x = 60 + (-30 * timers[3] * 2.0f);

						}						
					}

					if(GameScene->Nodes[i]->id == 7)// race track
					{
						// text 2
						glm::vec2 pos = GameScene->Nodes[i]->position;
						DrawText("Press 'V' to switch controll scheme (relative to mouse + rotate towards mouse / absolute)",pos-=glm::vec2(0.0f,stepy),Tscale);
					}
					if(GameScene->Nodes[i]->id == 6)// enemy
					{
						// text 3
						glm::vec2 pos = GameScene->Nodes[i]->position;
					
						DrawText("Destroy drone",pos-=glm::vec2(0.0f,stepy),Tscale);	
						DrawText("Destroing central part will kill drone instantly",pos-=glm::vec2(0.0f,stepy),Tscale);	
						if(Entities.size()>0)
							{
								if(Entities[0]->mid.x<-100.0f && Entities.size() == 1 && flags["Spawned"] && !flags["Explode"])
								{
									flags["Explode"] = true;
									timers[0] = 2.0f;
									timers[1] = 8.0f;
									timers[2] = 15.0f;
									AqueredCameraScale = {6.0f,6.0f};
									Entities[0]->player = true;
									Entities[0]->autocontrol = true;
									Entities[0]->deactivated = true;
								}
								if(!flags["Spawned"] && sqrlength(Entities[0]->mid - pos) < 10000)
								{
									flags["Spawned"] = true;
									SpawnAiShip(pos,"No");
								}
							}
						}
				}
				

				if(flags["Explode"])
				{	
					DrawLight(glm::vec3(CameraPosition - glm::vec2(100.0f,50.0f),-0.05f), {1000.0f,1000.0f,5.0f},glm::vec4(10.0f * timers[1]*0.5f,2.0f * timers[1]*0.5f,1.0f * timers[1]*0.5f,2.0f  * timers[1]*0.5f));
					if(timers[0]<=0.0f)
					{
						float stage = (timers[1])*0.1666f;
						float antstage = (6.0f - timers[1])*0.1666f;
						float val = 6.0f * stage;
						if(val<0.7f)
							val = 0.7f;
						AqueredCameraScale = {val,val};
						camerapos -= glm::vec2(300.0f,300.0f) * dt * antstage;
						if(timers[1]>0.1f)
							ScreenShake = 0.01f + antstage * 0.02f;
						if(Entities.size()>0  && !Entities[0]->dead && !Entities[0]->destroyed)
						{
							Entities[0]->SaveTo("PreMissionBackup");
							Entities[0]->SaveTo(EntityBackUpName);
							Entities[0]->Destroy();
						}

					}
					if(timers[2]<=0.1f && Exposure >0.8f)
					{
						Exposure = -0.85f;
					}
					if (Exposure > 0.0f && timers[2]<0.1f)
					{
						camerapos = {0.0f,0.0f};
						ScreenShake = 0.0f;
						storyint +=1;
						Materials = 250;
						exitMission(false);
					}
					
				}
			}break;
			default:
				break;
			}
		
	}
	void exitMission(bool extracted = false)
	{
		std::cout<<"exiting mission " <<"\n";
		if(extracted)
		{
			Materials += materialReward;
			if(Entities.size()>0 && !Entities[0]->dead && !Entities[0]->destroyed)
			{
				Materials += GetShipCost(Entities[0]);
				Entities[0]->SaveTo(EntityBackUpName);
				
			}
		}
		exitedmission = true;
		inbase = true;
		AmbientLight = 0.0f;
		ChangeMap("Scenes/base.sav", false);
		SpawnPlayer(EntityBackUpName);
	}
};


