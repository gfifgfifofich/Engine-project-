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
	int type = 0;
	int dificulty = 0;
	int size = 0;
	float materialReward = 0.0f;
	std::vector<CentralPart*> AIShips;

	std::vector<glm::vec4> TakenAreas;

	void Start(int mtype = MissionType::pirates, int mdificulty = 1, int msize = 5)
	{
		type = mtype;
		dificulty = mdificulty;
		size = msize;
		inbase = false;
		materialReward = 0.0f;
		TakenAreas.clear();
		TakenAreas.push_back({0,0,50,50});

		if(Entities.size()>0)
			Entities[0]->SaveTo(EntityBackUpName);
		//ClearMap
		ChangeMap("",false);
		SpawnPlayer(EntityBackUpName);

		for(int i=0;i<size * 5;i++)
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
				AIShips.push_back(SpawnAiShip(randpos,"Save0.sav"));
				TakenAreas.push_back(glm::vec4(randpos,AIShips[AIShips.size()-1]->maxR,AIShips[AIShips.size()-1]->maxR));
			}
			

		}break;
		case MissionType::infestation:
		{
			
		}
		default:
			break;
		}
	}

	void Process(float dt)
	{
		int AIShipsi =0; 
		while(AIShipsi<AIShips.size())
		{
			if(AIShips[AIShipsi]->Delete)
			{
				AIShips[AIShipsi] = AIShips[AIShips.size()];
				AIShips.pop_back();
			}
			else
				AIShipsi++;
		}
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
	}
	void exitMission(bool extracted = false)
	{
		if(extracted)
		{
			Materials += materialReward;
			if(Entities.size()>0)
				Entities[0]->SaveTo(EntityBackUpName);
		}
		inbase = true;
		ChangeMap("Scenes/base.sav", false);
		SpawnPlayer(EntityBackUpName);
	}
};


