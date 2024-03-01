/*

TODO:

proper building mode // mostly done

more parts
AI
Ship saving


Stations
Quests?

lots of textures

UI
*/



#include "engine/Components/Engine.h"
#include "engine/Components/Include/sounds.h"


#define PARTSIZE 0.5f

unsigned int RocketEngineSound;
unsigned int SHHSound;
unsigned int GunSound;
unsigned int HeavyHit;
unsigned int LaserGunSound;
unsigned int MiniGunSound;
unsigned int Clang;
unsigned int Detach;
unsigned int Scratch;
unsigned int Hit;
unsigned int BulletHit;
unsigned int PartDestrSOund;
unsigned int ExplodionSound;



unsigned int HeatPipeTexture;
unsigned int RopeTexture;
unsigned int RocketEngineTexture;
unsigned int RadiatorTexture;
unsigned int GunTexture;

glm::vec2 camerapos;

float ScreenShake = 0.0f;
float ScreenShakeFallOff = 1.0f;
float ChromaticAbberationFallOff = 1.0f;

const int GridCellSize = PARTSIZE * 2.0f;


struct GridCell
{
	int size = 0;
	ball* balls[10];
	void add(ball* b)
	{
		if (size < 10)
		{
			balls[size] = b;
			size++;
		}
	}
};
GridCell Grid[300][300];

int balllbuffersize;
ball* ballbuffer[200];

void ProcessCamera(float dt)
{
	CameraPosition = camerapos + glm::vec2(rand()%50 * ScreenShake - ScreenShake *100.0f, rand() %50 * ScreenShake - ScreenShake * 100.0f);
	ScreenShake -= ScreenShakeFallOff * dt;
	ChromaticStrength -= ChromaticAbberationFallOff * dt;
	if (ScreenShake < 0.0f) ScreenShake = 0.0f;
	if (ChromaticStrength < 0.0f) ChromaticStrength = 0.0f;

	if (ScreenShake > 1.0f) ScreenShake = 1.0f;
	if (ChromaticStrength > 0.3f) ChromaticStrength = 0.3f;
	UpdateListenerPosition();
}
ParticleEmiter Sparks;
unsigned int noize;
Scene Map;
#include "DamageSphere.h"
#include "Explodion.h"


float Speed = 1.0f;


ball* NewConBall1;
ball* NewConBall2;
int NewConType =0;
int NewConPart1;
int NewConPart2;
int NewConIndex1;
int NewConIndex2;
int ConCreationStage = 0;

bool NewConDebrie1 = false;
bool NewConDebrie2 = false;

int newPartType = -1;//-1 = not selected
float newPartRotation = 0.0f;

bool balltaken = false;

bool absoluteControl = true;
bool BuildingMode = false;

bool bLogicMode = false;
bool fLogicMode = false;
bool vLogicMode = false;
int DataconnectionData[6];


bool editSaveName = false;
//std::string saveFileName =  "Radiat.sav";
std::string saveFileName = "Save0.sav";

int in_UI = 0;// <=0 - not, else - browsing ui

bool createdFreezeDS = false;

bool align = false;
bool snapToGrid = false;

glm::vec2 AqueredCameraScale = { 20.0f ,20.0f };

std::vector<ball*>balls;

ball* GrabbedBall = NULL;

int SelectedPart = 0;


ParticleEmiter EngineSmoke;

#include "Rocket.h"
#include "Bullet.h"
#include "Laser.h"
#include "Parts.h"
#include "Entity.h"
#include "ParticleMaterials.h"

const int StarsAmount = 3000;
float StarsSpread = 1520.0f;
float StarsDepth = 10.0f;
glm::vec4 Stars[StarsAmount];



std::vector <miscPoint> PartSpawnPoints;

void Delete()
{
	for (int i = 0; i < SpawnableParts.size(); i++)
		SpawnableParts[i]->Delete();
}
void On_Create()
{
	AL_init();

	soundscale = { 40.0f,40.0f ,1.0f};

	
	RocketEngineSound = LoadSound("Sounds/noize_L.wav");
	SHHSound = LoadSound("Sounds/wind.wav");
	GunSound = LoadSound("Sounds/HeavyHit.wav");
	HeavyHit = LoadSound("Sounds/BigShot.wav");
	LaserGunSound = LoadSound("Sounds/Laser.wav");
	Clang = LoadSound("Sounds/metalhit1.wav");
	Detach = LoadSound("Sounds/detach.wav");
	
	Scratch = LoadSound("Sounds/Scratch.wav");
	PartDestrSOund = LoadSound("Sounds/Explodion.wav");
	Hit = LoadSound("Sounds/hit.wav");
	BulletHit = LoadSound("Sounds/CleanExplodion.wav");

	ExplodionSound = LoadSound("Sounds/VineBoom.wav");

	MiniGunSound = LoadSound("Sounds/Minigun.wav");
	
	LoadTexture("Textures/HeatPipe.png", &HeatPipeTexture);
	LoadTexture("Textures/rope.png", &RopeTexture);
	LoadTexture("Textures/RocketEngine.png", &RocketEngineTexture);
	LoadTexture("Textures/Radiator.png", &RadiatorTexture);
	LoadTexture("Textures/Gun.png", &GunTexture);

	GenNoizeTexture(&noize, 100, 2, 1.0f, 2);


	SetupPEs();

	Map.LoadFrom("Maps/Base.sav");
	Map.Rescale(glm::vec2(0.085f), 10);
	for (int i = 0; i < Map.ParticleEmiters.size(); i++)
	{
		Map.ParticleEmiters[i].InitialVelocity *= 0.025f;
		Map.ParticleEmiters[i].VelocityRandomness*= 0.025f;
		Map.ParticleEmiters[i].StartSize.x *= 0.025f;
		Map.ParticleEmiters[i].EndSize.x *= 0.025f;
	}
	FillSpawnableParts();

	for (int i = 0; i < SpawnableParts.size(); i++)
		SpawnableParts[i]->Ready({ 0.0f,0.0f }, { 0.0f,1.0f }, PARTSIZE);


	glm::vec2 position = glm::vec2(-10, 0.0f);
	glm::vec2 Scale = glm::vec2(0.5f, 0.5f);



	
	Entities.push_back(new Entity);
	Entities[0]->Ready(glm::vec2(0.0f, 0.0f) * Scale + position, { 0.0f,1.0f }, PARTSIZE);
	//Entities[0]->LoadFrom("Laser.sav");
	/*
	Entities[0].GenSoundSources();*/

	camerapos = Entities[0]->CP.body[0].position;
	listenerPos.z = 2.0f;

	


	CameraScale = { 20,20 };
	SettingsWindow = false;
	int currentobject = 0;
	for (int i = 0; i < Map.points.size(); i++)
	{
		if (Map.points[i].id == 1 && currentobject <= SpawnablePartAmount)
		{
			miscPoint mp;
			mp.id = currentobject;
			mp.position = Map.points[i].position ;
			PartSpawnPoints.push_back(mp);
			currentobject++;
		}
	}
	

	for (int i = 0; i < StarsAmount; i++)
	{
		Stars[i].x = rand() % 1000 * 0.001f * StarsSpread - StarsSpread * 0.5f + camerapos.x;
		Stars[i].y = rand() % 1000 * 0.001f * StarsSpread - StarsSpread * 0.5f + camerapos.y;
		Stars[i].z = rand() % 1000 * 0.0001f * StarsDepth;
		Stars[i].w = rand() % 1000 * 0.001f * pi*0.5f;
	}

}
int lastsound = 0;
int lastsound2 = 0;
unsigned int lastplayedsound = 1;


void On_Update()
{



	if (clock() < 100)
		Speed = 0.0f;
	else if (clock() >= 100 && clock() < 1200)
		Speed = 1.0f;
	delta *= Speed;
	in_UI--;

	if (in_UI < 0)
		in_UI = 0;

	if (keys[GLFW_KEY_ESCAPE])
		glfwSetWindowShouldClose(window, true);


	if (JustPressedkey[GLFW_KEY_V])
		absoluteControl = !absoluteControl;


	ImGui::Begin("Settings");
	ImGui::SliderFloat("speed", &Speed, 0.0f, 10.0f);
	ImGui::Text("ballssize = %.i", balls.size());
	ImGui::Text("%.1ffps (%.3fms)", 1.0f/delta,delta);


	unsigned int soundsrc;
	GenSource(&soundsrc);
	ImGui::Text("sound source id %.i", soundsrc);
	DeleteSource(&soundsrc);


	ImGui::Text("sources size (%.i)", sources.size());
	ImGui::Text("parts size (%.i)", Debris.Parts.size());

	if (ImGui::Button("Playsound last sound"))
	{
		PlaySource(&lastplayedsound);
		lastplayedsound++;
	}

	if (ImGui::Button("VSync"))
	{
		if (VSync)
		{
			glfwSwapInterval(0);
			VSync = 0;
		}
		else
		{
			glfwSwapInterval(1);
			VSync = 1;
		}
	}
	//float a[2] = { Entities[0].direction.x,Entities[0].direction.y };
	//ImGui::DragFloat2("Direction", a);
	if (ImGui::Button("SettingsWindow"))
		SettingsWindow = !SettingsWindow;
	ImGui::Text("zoom = %.2f", CameraScale.x);
	if (ImGui::Button("ReloadMap"))
	{

		Map.LoadFrom("Maps/Base.sav");
		Map.Rescale(glm::vec2(0.085f), 10);
	}
	ImGui::End();
	int currentObject = 1;
	balls.clear();


	AqueredCameraScale *= 1.0f + scrollmovement * 0.1f;

	if (AqueredCameraScale.x > 80.0f)
		AqueredCameraScale = { 80.0f, 80.0f };
	if (AqueredCameraScale.x < 1.0f)
		AqueredCameraScale = {1.0f ,1.0f};

	CameraScale += (AqueredCameraScale - CameraScale) * 0.25f * delta * 60.0f;

	if (clock() > 1000)
		for (int i = 0; i < StarsAmount; i++)
	{
		if (Stars[i].x > CameraPosition.x + StarsSpread * 0.5f)
		{
			Stars[i].x = CameraPosition.x - StarsSpread * 0.5f;
			Stars[i].y = CameraPosition.y + rand() % 10000 * 0.0001f * StarsSpread - StarsSpread * 0.5f;
		}
		if (Stars[i].x < CameraPosition.x - StarsSpread * 0.5f)
		{
			Stars[i].x = CameraPosition.x + StarsSpread * 0.5f;
			Stars[i].y = CameraPosition.y + rand() % 10000 * 0.0001f * StarsSpread - StarsSpread * 0.5f;
		}
		if (Stars[i].y > CameraPosition.y + StarsSpread * 0.5f)
		{
			Stars[i].y = CameraPosition.y - StarsSpread * 0.5f;
			Stars[i].x = CameraPosition.x + rand() % 10000 * 0.0001f * StarsSpread - StarsSpread * 0.5f;
		}
		if (Stars[i].y < CameraPosition.y - StarsSpread * 0.5f)
		{
			Stars[i].y = CameraPosition.y + StarsSpread * 0.5f;
			Stars[i].x = CameraPosition.x + rand() % 10000 * 0.0001f * StarsSpread - StarsSpread * 0.5f;
		}

		DrawCube(glm::vec2(Stars[i]), glm::vec2(Stars[i].z * 0.25f), Stars[i].w, glm::vec4(1.0f, 1.0f, 1.0f, Stars[i].z*10.0f / StarsDepth));

	}

	

	if (!absoluteControl)
	{
		glm::vec2 LookAtVec = Normalize(MousePosition - Entities[0]->CenterOfMass);

		if (LookAtVec.x != 0.0f || LookAtVec.y != 0.0f)LookAtVec = Normalize(LookAtVec);
		if (sqrlength(MousePosition - CameraPosition) > 10.0f)
			Entities[0]->LookAt = LookAtVec;

		glm::vec2 velvec = glm::vec2(0.0f);

		if (keys[GLFW_KEY_W]) velvec += LookAtVec;
		if (keys[GLFW_KEY_S]) velvec -= LookAtVec;
		if (keys[GLFW_KEY_D]) velvec += glm::vec2(LookAtVec.y, -LookAtVec.x);
		if (keys[GLFW_KEY_A]) velvec -= glm::vec2(LookAtVec.y, -LookAtVec.x);

			
		if (velvec.x != 0.0f || velvec.y != 0.0f) velvec = Normalize(velvec);
		Entities[0]->ThrustDirection = velvec;

	}
	else
	{
		glm::vec2 LookAtVec = Entities[0]->direction;

		if (LookAtVec.x != 0.0f || LookAtVec.y != 0.0f)
			LookAtVec = Normalize(LookAtVec);
		else
			LookAtVec = glm::vec2(0.0f, 1.0f);


		if (keys[GLFW_KEY_A]) LookAtVec = Rotate(LookAtVec, pi * 0.5);
		else if (keys[GLFW_KEY_D]) LookAtVec = Rotate(LookAtVec, pi * -0.5);
		else LookAtVec = Entities[0]->direction;

		Entities[0]->LookAt = LookAtVec;

		glm::vec2 velvec = glm::vec2(0.0f);

		if (keys[GLFW_KEY_W]) velvec += Entities[0]->direction;
		if (keys[GLFW_KEY_S]) velvec -= Entities[0]->direction;
		if (keys[GLFW_KEY_E]) velvec += glm::vec2(Entities[0]->direction.y, -Entities[0]->direction.x);
		if (keys[GLFW_KEY_Q]) velvec -= glm::vec2(Entities[0]->direction.y, -Entities[0]->direction.x);

		if (velvec.x != 0.0f || velvec.y != 0.0f) velvec = Normalize(velvec);
		Entities[0]->ThrustDirection = velvec;
	}


	camerapos = Entities[0]->CP.mid;
	Entities[0]->CP.enemy = false;
	Entities[0]->autocontrol = false;
	Entities[0]->enemy = false;
	listenerVel = { Entities[0]->CP.midvel.x ,Entities[0]->CP.midvel.y ,1.0f };
	ProcessCamera(delta);

	if (BuildingMode || bLogicMode || fLogicMode || vLogicMode)
	{
		BackgroundColor = glm::vec4(0.0f, 0.0f, 0.01f, 1.0f);
		//grid
		glm::vec2 gridpos = glm::vec2(0.0f, 0.0f);
		Entities[0]->FireGuns = false;

		// grid size = 1
		glm::vec2 roundCP = glm::vec2(roundf(CameraPosition.x), roundf(CameraPosition.y));
		if (CameraScale.x > 15.0f)
			for (int i = 0; i < 200; i++)
			{
				DrawLine(glm::vec2(50 * (i * 0.02f - 2.0f), 50 * -2.0f) + gridpos + roundCP,
					glm::vec2(50 * (i * 0.02f - 2.0f), 50 * 2.0f) + gridpos + roundCP, 1.75f * 0.025f,
					glm::vec4(0.15f), false, CubeNormalMapTexture, -100);

				DrawLine(glm::vec2(50 * -2.0f, 50 * (i * 0.02f - 2.0f)) + gridpos + roundCP,
					glm::vec2(50 * 2.0f, 50 * (i * 0.02f - 2.0f)) + gridpos + roundCP, 1.75f * 0.025f,
					glm::vec4(0.15f), false, CubeNormalMapTexture, -100);
			}
		
		if (JustPressedLMB && in_UI <= 0)
		{
			DamageSphere DS;
			DS.body.r = 5.0f;
			DS.body.position = MousePosition;
			DS.Damage = false;
			DS.timeLeft = 1.0f;
			DS.Heat = 0.0f;
			DS.recoil = 0.0f;
			DS.neutral = true;
			DS.friction = 0.9f;
			DS.singleHit = false;
			DamageSpheresArray.push_back(DS);
		}
	}
	else
	{
		DataconnectionData[0] = 0;

		Entities[0]->GunsTargetrotPoint = MousePosition;
		if (in_UI <= 0)
			Entities[0]->FireGuns = buttons[GLFW_MOUSE_BUTTON_1];
		BackgroundColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		/*if (buttons[GLFW_MOUSE_BUTTON_2])
		{

			Entities.push_back(new Entity);
			Entities[Entities.size() - 1]->Ready(MousePosition, { 0.0f,1.0f }, PARTSIZE);
			Entities[Entities.size() - 1]->LoadFrom("Cube.sav");
			Entities[Entities.size() - 1]->autocontrol = true;
			Entities[Entities.size() - 1]->trgPos = MousePosition;
			Entities[Entities.size() - 1]->enemy = true;
			Entities[Entities.size() - 1]->CP.Health=-10;


		}*/
	}
	if (bLogicMode || fLogicMode || vLogicMode)
	{
		if (JustPressedbutton[GLFW_MOUSE_BUTTON_2])
			DataconnectionData[0] = 0;


		for (int i = 0; i < Entities[0]->Parts.size(); i++)
		{
			Entities[0]->Parts[i]->DrawDataConnections(i,bLogicMode, fLogicMode, vLogicMode, 1000);
			
		}
		if (DataconnectionData[0] == 1)
		{
			if (DataconnectionData[1] == 0)
				DrawLine(MousePosition, Entities[0]->Parts[DataconnectionData[2]]->bDataConnections[DataconnectionData[3]].lastpos, 0.125f, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), 0, 0, 1000);
			else if (DataconnectionData[1] == 1)
				DrawLine(MousePosition, Entities[0]->Parts[DataconnectionData[2]]->fDataConnections[DataconnectionData[3]].lastpos, 0.125f, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), 0, 0, 1000);
			else if (DataconnectionData[1] == 2)
				DrawLine(MousePosition, Entities[0]->Parts[DataconnectionData[2]]->vDataConnections[DataconnectionData[3]].lastpos, 0.125f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), 0, 0, 1000);
		}
		if (DataconnectionData[0] == 2)
		{
			Entities[0]->AddDataConnection(DataconnectionData[1], DataconnectionData[2], DataconnectionData[3], DataconnectionData[4], DataconnectionData[5]);
			DataconnectionData[0] = 0;
		}
	}
	else
		DataconnectionData[0] = 0;

	if (BuildingMode)
	{

		
		if (JustPressedkey[GLFW_KEY_TAB])
		{
			NewConType++;
			if (NewConType > 3) NewConType = 0;
		}

		if (JustPressedkey[GLFW_KEY_SPACE])
			align = !align;
		if (align)
		{
			//Entities[0].Parts[0] -> central part
			glm::vec2 mid = (Entities[0]->Parts[0]->body[0].position + Entities[0]->Parts[0]->body[1].position)*0.5f;

			Entities[0]->Parts[0]->body[0].velocity = ((mid + glm::vec2(0.0f,1.0f) * Entities[0]->Parts[0]->body[0].r) - Entities[0]->Parts[0]->body[0].position)*15.0f;
			Entities[0]->Parts[0]->body[1].velocity = ((mid - glm::vec2(0.0f,1.0f) * Entities[0]->Parts[0]->body[1].r) - Entities[0]->Parts[0]->body[1].position)*15.0f;

		}

		

		if (keys[GLFW_KEY_LEFT_ALT])
		{
			if (ConCreationStage == 1)
			{
				DrawLine(NewConBall1->position, MousePosition, 0.125f);
			}
			if (JustPressedLMB)
			{
				int prevcon = ConCreationStage;
				for (int i = 0; i < Entities[0]->Parts.size(); i++)
				{
					if(Entities[0]->Parts[i]->type!=TYPE::WEAPON)
						for (int a = 0; a < Entities[0]->Parts[i]->bodysize; a++)
						{
							if (BalltoPointCollisionCheck(Entities[0]->Parts[i]->body[a], MousePosition))
							{
								if (ConCreationStage == 0)
								{
									NewConBall1 = &Entities[0]->Parts[i]->body[a];
									NewConIndex1 = a;
									NewConPart1 = i;
									ConCreationStage++;
								}
								else if (ConCreationStage == 1)
								{
									NewConBall2 = &Entities[0]->Parts[i]->body[a];
									NewConIndex2 = a;
									NewConPart2 = i;
									ConCreationStage++;
								}
							}
						}
					else
					{
						if (BalltoPointCollisionCheck(Entities[0]->Parts[i]->body[0], MousePosition))
						{
							if (ConCreationStage == 0)
							{
								NewConBall1 = &Entities[0]->Parts[i]->body[0];
								NewConIndex1 = 0;
								NewConPart1 = i;
								ConCreationStage++;
							}
							else if (ConCreationStage == 1)
							{
								NewConBall2 = &Entities[0]->Parts[i]->body[0];
								NewConIndex2 = 0;
								NewConPart2 = i;
								ConCreationStage++;
							}
						}
					}
				}
				


				if (prevcon == ConCreationStage && !NewConDebrie1)
				{
					for (int i = 0; i < Debris.Parts.size(); i++)
					{
						if (Debris.Parts[i]->type != TYPE::WEAPON)
							for (int a = 0; a < Debris.Parts[i]->bodysize; a++)
							{
								if (BalltoPointCollisionCheck(Debris.Parts[i]->body[a], MousePosition))
								{
									if (ConCreationStage == 0)
									{
										NewConBall1 = &Debris.Parts[i]->body[a];
										NewConIndex1 = a;
										NewConPart1 = i;
										ConCreationStage++;
										NewConDebrie1 = true;
									}
									else if (ConCreationStage == 1)
									{
										NewConBall2 = &Debris.Parts[i]->body[a];
										NewConIndex2 = a;
										NewConPart2 = i;
										ConCreationStage++;
										NewConDebrie2 = true;
									}
								}
							}
						else
						{
							if (BalltoPointCollisionCheck(Debris.Parts[i]->body[0], MousePosition))
							{
								if (ConCreationStage == 0)
								{
									NewConBall1 = &Debris.Parts[i]->body[0];
									NewConIndex1 = 0;
									NewConPart1 = i;
									ConCreationStage++;
									NewConDebrie1 = true;
								}
								else if (ConCreationStage == 1)
								{
									NewConBall2 = &Debris.Parts[i]->body[0];
									NewConIndex2 = 0;
									NewConPart2 = i;
									ConCreationStage++;
									NewConDebrie2 = true;
								}
							}
						}
					}
					

				}
				if (ConCreationStage == 1 && prevcon != ConCreationStage)
				{
					Sparks.Spawn(NewConBall1->position, rand() % 5 + 5);
					PlaySound(&Clang, MousePosition, 2.5f, 0.3f);
				}
				if (ConCreationStage >= 2)
				{
					PlaySound(&Clang, MousePosition, 2.5f, 0.3f);
					Sparks.Spawn(NewConBall2->position, rand() % 5 + 5);
					ConCreationStage = 0;
					if (NewConDebrie1)
						NewConPart1 = Entities[0]->ClaimPart(NewConPart1);
					if (NewConDebrie2)
						NewConPart2 = Entities[0]->ClaimPart(NewConPart2);
					NewConDebrie1 = false;
					NewConDebrie2 = false;

					if (NewConPart1 != NewConPart2)
						Entities[0]->AddConnection(NewConType, -1, 0.125f, 1500, 2, NewConType == HEATPIPE ? 0.4f : 0.1f, NewConPart1, NewConIndex1, NewConPart2, NewConIndex2);
				}
			}
		}
		else
		{
			ConCreationStage = 0;
			NewConDebrie1 = false;
			NewConDebrie2 = false;
		}
		if (keys[GLFW_KEY_LEFT_SHIFT] && !keys[GLFW_KEY_LEFT_ALT])
		{
			if (JustPressedLMB && in_UI <= 0)
			{
				for (int i = 1; i < Entities[0]->Parts.size(); i++)
				{
					bool detached = true;
					while (detached)
					{
						detached = false;
						for (int a = 0; a < Entities[0]->Parts[i]->bodysize; a++)
						{

							if (i < Entities[0]->Parts.size() && BalltoPointCollisionCheck(Entities[0]->Parts[i]->body[a], MousePosition) && !detached)
							{
								PlaySound(&Detach, MousePosition, 3.5f, 0.3f);
								Entities[0]->DetachPart(i);
								detached = true;
							}
						}
					}
				}
			}
		}

		if (JustPressedbutton[GLFW_MOUSE_BUTTON_3])
		{
			bool found = false;
			for (int i = 0; i < Debris.Parts.size(); i++)
			{
				if(Debris.Parts[i]->bodysize>1)
				{for (int a = 0; a < Debris.Parts[i]->bodysize; a++)
					if (BalltoPointCollisionCheck(Debris.Parts[i]->body[a], MousePosition))
					{

						found = true;
						SelectedPart = i;

						break;
					}
				}

				if (found)
					break;
			}
		}
		if(JustReleasedbutton[GLFW_MOUSE_BUTTON_3])
			SelectedPart = -1;
		if (SelectedPart > 0)
		{
			glm::vec2 mid = { 0.0f,0.0f };
			for (int i = 0; i < Debris.Parts[SelectedPart]->bodysize; i++)
				mid += Debris.Parts[SelectedPart]->body[i].position;
			mid /= Debris.Parts[SelectedPart]->bodysize;

			glm::vec2 dir = Normalize(MousePosition - mid);

			float rot = 0.0f;
			float rotStep = pi * 2.0f / Debris.Parts[SelectedPart]->bodysize;
			for (int i = 0; i < Debris.Parts[SelectedPart]->bodysize; i++)
			{
				Debris.Parts[SelectedPart]->body[i].position = mid + Rotate(dir, rot) * Debris.Parts[SelectedPart]->body[i].r;
				rot += rotStep;
			}

		}

		bool b = (NewConType == STRUT);
		UI_buttonOnlyON(&b, "Strut", { -0.47f * WIDTH ,-0.46f * HEIGHT }, 18.0f, 0.5f, glm::vec4(0.9f), glm::vec4(0.5f), 1200);
		if (b && b != (NewConType == STRUT))
			NewConType = STRUT;

		b = (NewConType == SPRING);
		UI_buttonOnlyON(&b, "Spring", { -0.47f * WIDTH ,-0.40f * HEIGHT }, 18.0f, 0.5f, glm::vec4(0.9f), glm::vec4(0.5f), 1200);
		if (b && b != (NewConType == SPRING))
			NewConType = SPRING;

		b = (NewConType == HEATPIPE);
		UI_buttonOnlyON(&b, "Heat pipe", { -0.47f * WIDTH ,-0.34f * HEIGHT }, 18.0f, 0.5f, glm::vec4(0.9f), glm::vec4(0.5f), 1200);
		if (b && b != (NewConType == HEATPIPE))
			NewConType = HEATPIPE;

		b = (NewConType == ROPE);
		UI_buttonOnlyON(&b, "Rope", { -0.47f * WIDTH ,-0.28f * HEIGHT }, 18.0f, 0.5f, glm::vec4(0.9f), glm::vec4(0.5f), 1200);
		if (b && b != (NewConType == ROPE))
			NewConType = ROPE;


		


		UI_CheckBox(&align, "Align rotation", { -0.35f * WIDTH ,-0.46f * HEIGHT }, 18.0f, 0.5f, glm::vec4(0.9f), glm::vec4(0.5f), 1200);

		UI_CheckBox(&snapToGrid, "Snap to grid", { -0.20f * WIDTH ,-0.46f * HEIGHT }, 18.0f, 0.5f, glm::vec4(0.9f), glm::vec4(0.5f), 1200);

		UI_TextBox(&saveFileName, { -0.46f * WIDTH ,0.46f * HEIGHT }, 32, { 150.0f,150.0f }, 0.35f, { 0.4f,0.4f,0.4f,0.4f }, {1.0f,1.0f,1.0f,1.0f},1200);
		
		bool save = false;
		UI_buttonOnlyON(&save,"Save", { -0.46f * WIDTH ,0.40f * HEIGHT }, 18.0f, 0.5f, glm::vec4(0.9f), glm::vec4(0.5f), 1200);
		if (save)
			Entities[0]->SaveTo(saveFileName);

		bool load = false;
		UI_buttonOnlyON(&load, "Load", { -0.46f * WIDTH ,0.34f * HEIGHT }, 18.0f, 0.5f, glm::vec4(0.9f), glm::vec4(0.5f), 1200);
		if (load)
			Entities[0]->LoadFrom(saveFileName);
	}
	

	bool blm = bLogicMode;
	bool flm = fLogicMode;
	bool vlm = vLogicMode;
	bool bm = BuildingMode;

	if (JustPressedkey[GLFW_KEY_B])
		BuildingMode = !BuildingMode;

	glm::vec4 UI_ColorON = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);
	glm::vec4 UI_ColorOFF = glm::vec4(0.5f, 0.5f, 0.5f, 0.7f);

	UI_CheckBox(&bLogicMode, "Bools Logic", { 0.40f * WIDTH ,-0.46f * HEIGHT }, 18.0f, 0.5f, UI_ColorON, UI_ColorOFF,1200);
	UI_CheckBox(&fLogicMode, "Number Logic", { 0.40f * WIDTH ,-0.40f * HEIGHT }, 18.0f, 0.5f, UI_ColorON, UI_ColorOFF, 1200);
	UI_CheckBox(&vLogicMode, "Vector Logic", { 0.40f * WIDTH ,-0.34f * HEIGHT }, 18.0f, 0.5f, UI_ColorON, UI_ColorOFF, 1200);
	UI_CheckBox(&BuildingMode, "Building Mode", { 0.40f * WIDTH ,-0.28f * HEIGHT }, 18.0f, 0.5f, UI_ColorON, UI_ColorOFF, 1200);

	if (bLogicMode && blm != bLogicMode)
	{
		bLogicMode = true;
		fLogicMode = false;
		vLogicMode = false;
		BuildingMode = false;
		DataconnectionData[0] = 0;
	}
	else if(fLogicMode && flm != fLogicMode)
	{
		bLogicMode = false;
		fLogicMode = true;
		vLogicMode = false;
		BuildingMode = false;
		DataconnectionData[0] = 0;
	}
	else if (vLogicMode && vlm != vLogicMode)
	{
		bLogicMode = false;
		fLogicMode = false;
		vLogicMode = true;
		BuildingMode = false;
		DataconnectionData[0] = 0;
	}
	else if (BuildingMode && bm != BuildingMode)
	{
		bLogicMode = false;
		fLogicMode = false;
		vLogicMode = false;
		BuildingMode = true;
		DataconnectionData[0] = 0;
	}

	if (GrabbedBall != NULL)
	{
		point p;
		p.position = MousePosition;
		SpringBallToPoint(GrabbedBall, &p, 0.0f, 3000.0f, 1.0f);
		DrawLine(GrabbedBall->position, MousePosition, 0.025f, {1.0f,1.0f,0.0f,1.0f});

		DamageSphere DS;
		DS.body.r = 0.25f;
		DS.body.position = MousePosition;
		DS.Damage = false;
		DS.timeLeft = 0.044f;
		DS.Heat = 0.0f;
		DS.recoil = -1.0f;
		DS.neutral = true;
		DS.friction = 0.99f;
		DS.singleHit = false;
		DamageSpheresArray.push_back(DS);

	}

	if (keys[GLFW_KEY_1])
	{

		DamageSphere DS;
		DS.body.r = 10.25f;
		DS.body.position = MousePosition;
		DS.Damage = false;
		DS.timeLeft = 0.044f;
		DS.Heat = 0.0f;
		DS.recoil = -10.0f;
		DS.neutral = true;
		//DS.friction = 0.00f;
		DS.singleHit = false;
		DamageSpheresArray.push_back(DS);
	}
	if (JustPressedkey[GLFW_KEY_2])
	{
		Entities.push_back(new Entity);
		Entities[Entities.size() - 1]->Ready(MousePosition, { 0.0f,1.0f }, PARTSIZE);
		Entities[Entities.size() - 1]->LoadFrom("Save0.sav");
		Entities[Entities.size() - 1]->autocontrol = true;
		Entities[Entities.size() - 1]->trgPos = MousePosition;
		Entities[Entities.size() - 1]->enemy = true;
		//Entities[Entities.size() - 1]->CP.Health = -10;

	}
	if (JustPressedkey[GLFW_KEY_3])
	{
		Entities.push_back(new Entity);
		Entities[Entities.size() - 1]->Ready(MousePosition, { 0.0f,1.0f }, PARTSIZE);
		Entities[Entities.size() - 1]->LoadFrom("Bigboy.sav");
		Entities[Entities.size() - 1]->autocontrol = true;
		Entities[Entities.size() - 1]->trgPos = MousePosition;
		Entities[Entities.size() - 1]->enemy = true;
		//Entities[Entities.size() - 1]->CP.Health = -10;

	}
	if (JustPressedkey[GLFW_KEY_4])
	{
		SpawnExplodion(MousePosition, 10.0f, 0.5f, 0.4f);
	}
	ProcessAL();

	ProcessPE(delta);
	
	ProcessEntities(delta, 10);

	Map.Draw();

	for (int i = 0; i < PartSpawnPoints.size(); i++)
	{
		glm::vec2 offset = Entities[0]->CP.mid + glm::vec2(-150, -150);
		glm::ivec2 pos = { roundf(PartSpawnPoints[i].position.x - offset.x),roundf(PartSpawnPoints[i].position.y - offset.y) };
		
		bool inrange = false;
		bool able = true;
		for (int x = -1; x < 2; x++)
			if (able)
			{
				for (int y = -1; y < 2; y++)
					if ((pos.x + x )>= 0 && (pos.x + x < 300 )&&
						(pos.y + y )>= 0 && (pos.y + y < 300))
					{
						inrange = true;
						if ((Grid[pos.x + x][pos.y + y].size > 0) && able)
						{
							able = false;
							break;
						}
					}
			}
			else
				break;
		if (inrange && able)
		{

			Debris.SpawnPart(PartSpawnPoints[i].id, PartSpawnPoints[i].position, PARTSIZE);
		}
	}

	//if (keys[GLFW_KEY_1])
	//{
	//	int ab;
	//	std::cin >> ab;
	//}

	
}


int main()
{
	initEngine("HEAT",1920,1080,true);
	//initEngine("HEAT");


	Delete();
	AL_Destroy();
	return 0;
}
