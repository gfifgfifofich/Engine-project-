/*

TODO:
{
	proper building mode // mostly done
	more parts
	lots of textures
	AI
	UI
	bullets are buggy

	
}
current task
{
	Parts "shop"
	Save info	
	md Saving of crafts
}
resources - one material (matter or whatever)

Missions, base location, resources. Parts cost materials, missions give. Retrieving vehicle returns all resorces.....

Mission ideas:
	retrive part/object/debrie ?? 
	kill N crafts ("Pirates") // mostly implemented
	kill N bugs ("Infestation") // need to create new enemy type with its tree (bug->hiver,rammer,stalker,motherbug)
	//also possible with Central part 
	
	defend building/mine for N minutes/waves (or factory/mine, the longer its alive, the more resources player gets)

Mission
{
	Random objects (static asteroids - DONE, planets, fog fields that slow down...)
	Debrie (Random parts for free mb)
	Matter deposits (geodes?)(Extra reward for exploration)


	bool retrival necessary ( retrieve to get resources or not) // probably always necessary

	int dificulty (tier/amount of enemies)  
	int size (amount of enemies)  
	// mb dificulty * size 
	border - killing fog

	enum int type // mining, retrival, defeat pirates, clear bugs etc

}
*/


/*



CentralPart == Entity;
{
	Connections[]
}


*/

#include "engine/Components/Redactor.h"
#include "engine/Components/Include/sounds.h"

DataStorage GameSaveFile;
float Materials = 0.0f;
std::string lastEntityName = "Ships/Save0.sav";
std::string EntityBackUpName = "Ships/PreMissionBackup.sav";
std::string GameSaveName = "Save0";

class BallBodyComponent : public ball
{
public:
	float temperature = 0.0f;
	SoundSource* SS = NULL;
	float soundcd = 0.0f;
};





#define PARTSIZE 0.5f

int BackgroundWindowID = -1;
int ForeWindowID = -1;
glm::vec2 foregroundMousePosition = {0.0f,0.0f};
int MenuWindowID = -1;

float TextSize = 1.0f;
float UISize = 18.0f;

MaterialObject MO_Ball;
MaterialObject MO_Cube;
Material PrimitiveQuad;
unsigned int 
RocketEngineSound,
SHHSound,
GunSound,
HeavyHit,
LaserGunSound,
MiniGunSound,
Clang,
Detach,
Scratch,
Hit,
BulletHit, 
PartDestrSOund,
ExplodionSound

;



unsigned int
HeatPipeTexture,
HeatPipeNormalMap,

RopeTexture,
RopeNormalMap,

StrutTexture,
StrutNormalMap,

GunBaseTexture,
GunBaseNormalMap,

GunTexture,
GunNormalMap,

LaserGunTexture,
LaserGunNormalMap,

MiniGunTexture,
MiniGunNormalMap,

RocketLauncherTexture,
RocketLauncherNormalMap,

RocketEngineTexture,
RocketEngineNormalMap,

RadiatorTexture,
RadiatorNormalMap,

BallBodyTexture,
BallBodyNormalMap,

CentralPartTexture,
CentralPartNormalMap,

RotorTexture,
RotorNormalMap,

PipeTexture,
PipeNormalMap,

Debrie0Texture,
Debrie1Texture


;

void LoadTextures()
{
	LoadTexture("Textures/HeatPipe.png", &HeatPipeTexture);
	LoadTexture("Textures/HeatPipe NormalMap.png", &HeatPipeNormalMap);

	LoadTexture("Textures/Rope.png", &RopeTexture);
	LoadTexture("Textures/Rope NormalMap.png", &RopeNormalMap);

	LoadTexture("Textures/Strut.png", &StrutTexture);
	LoadTexture("Textures/Strut NormalMap.png", &StrutNormalMap);

	LoadTexture("Textures/RocketEngine.png", &RocketEngineTexture);
	LoadTexture("Textures/RocketEngine NormalMap.png", &RocketEngineNormalMap);

	LoadTexture("Textures/Radiator.png", &RadiatorTexture);
	LoadTexture("Textures/Radiator NormalMap.png", &RadiatorNormalMap);

	LoadTexture("Textures/Gun.png", &GunTexture);
	LoadTexture("Textures/Gun NormalMap.png", &GunNormalMap);

	LoadTexture("Textures/LaserGun.png", &LaserGunTexture);
	LoadTexture("Textures/LaserGun NormalMap.png", &LaserGunNormalMap);

	LoadTexture("Textures/MiniGun.png", &MiniGunTexture);
	LoadTexture("Textures/MiniGun NormalMap.png", &MiniGunNormalMap);

	LoadTexture("Textures/GunBase.png", &GunBaseTexture);
	LoadTexture("Textures/GunBase NormalMap.png", &GunBaseNormalMap);

	LoadTexture("Textures/RocketLauncher.png", &RocketLauncherTexture);
	LoadTexture("Textures/RocketLauncher NormalMap.png", &RocketLauncherNormalMap);

	LoadTexture("Textures/BallBody.png", &BallBodyTexture);
	LoadTexture("Textures/BallBody NormalMap.png", &BallBodyNormalMap);

	LoadTexture("Textures/CentralPart.png", &CentralPartTexture);
	LoadTexture("Textures/CentralPart NormalMap.png", &CentralPartNormalMap);

	LoadTexture("Textures/Rotor.png", &RotorTexture);
	LoadTexture("Textures/Rotor NormalMap.png", &RotorNormalMap);

	LoadTexture("Textures/Pipe.png", &PipeTexture);
	LoadTexture("Textures/Pipe NormalMap.png", &PipeNormalMap);

	LoadTexture("Textures/debrie0.png", &Debrie0Texture);
	LoadTexture("Textures/debrie1.png", &Debrie1Texture);


}

glm::vec2 camerapos;

float ScreenShake = 0.0f;
float ChromaticAbberation = 0.0f;
float ScreenShakeFallOff = 1.0f;
float ChromaticAbberationFallOff = 1.0f;

float s_ChromaticAbberation = 1.0f;
float s_ScreenShake = 1.0f;

const int GridCellSize = PARTSIZE * 2.0f;


bool reloadSources = false;

float brightness = 1.0f;

int SRiter = 0;
glm::ivec2 StandartResolutions[] =
{
	{800,600},
	{1024,768},
	{1280,720},
	{1280,1024},
	{1366,768},
	{1680,1050},
	{1920,1080},
	{2560,1440}
};


std::string RX = std::to_string(s_Resolution.x);
std::string RY = std::to_string(s_Resolution.y);

void ResetSettings()
{
	brightness = 1.0f;
	bloom = true;
}
void SaveSettings()
{
	std::ofstream SaveFile("Settings.sav");
	SaveFile << "Res ";
	SaveFile << s_Resolution.x;
	SaveFile << " ";
	SaveFile << s_Resolution.y;
	SaveFile << "\n";

	SaveFile << "FS ";
	SaveFile << s_Fullscreen;
	SaveFile << "\n";

	SaveFile << "Br ";
	SaveFile << brightness;
	SaveFile << "\n";

	SaveFile << "Bl ";
	SaveFile << bloom;
	SaveFile << "\n";
	SaveFile << "Sh ";
	SaveFile << s_ScreenShake;
	SaveFile << "\n";
	SaveFile << "Ca ";
	SaveFile << s_ChromaticAbberation;
	SaveFile << "\n";
}
struct GridCell
{
	int size = 0;
	BallBodyComponent* balls[10];
	void add(BallBodyComponent* b)
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
BallBodyComponent* ballbuffer[200];
float Exposure = 0.0f;


struct LightEffect
{
	float time = 1.0f;
	float maxT = 1.0f;
	float S_Scale = 1000.0f;
	float E_Scale = 0.0f;

	glm::vec3 position = glm::vec3(0.0f);

	glm::vec4 S_Color = glm::vec4(1.0f);
	glm::vec4 E_Color = glm::vec4(0.0f);

	float volume = 0.05f;
};

std::vector<LightEffect> LightEffects;

void ProcessLightEffects(float dt)
{

	for (int i = 0; i < LightEffects.size(); i++)
	{
		
		float step = LightEffects[i].time / LightEffects[i].maxT;
		DrawLight(LightEffects[i].position,
			glm::vec2(LightEffects[i].S_Scale * step + LightEffects[i].E_Scale * (1.0f - step)),
			LightEffects[i].S_Color * step + LightEffects[i].E_Color * (1.0f - step),
			LightEffects[i].volume);

		LightEffects[i].time -= dt;

	}
	int i = 0;
	while (i < LightEffects.size())
	{
		if (LightEffects[i].time <= 0.0f)
		{
			LightEffects[i] = LightEffects[LightEffects.size() - 1];
			LightEffects.pop_back();
		}
		else
			i++;
	}


}

float ExplodionLightHeight = 0.001f;
float EngineLightHeight = 0.001f;
float BulletHitLightHeight = 0.001f;
float CentralLightHeight = 0.001f;

ParticleEmiter Sparks;
unsigned int noize = NULL;
Scene Background;
#include "DamageSphere.h"
#include "Explodion.h"


float Speed = 1.0f;


BallBodyComponent* NewConBall1;
BallBodyComponent* NewConBall2;
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
//std::string saveFileName = "Save0Laser.sav";
//std::string saveFileName = "BigBoy.sav";
//std::string saveFileName = "Spinner.sav";

int in_UI = 0;// <=0 - not, else - browsing ui

bool createdFreezeDS = false;

bool align = false;
bool snapToGrid = false;


std::vector<BallBodyComponent*>balls;

BallBodyComponent* GrabbedBall = NULL;

int SelectedPart = 0;



#include "ParticleMaterials.h"
#include "Rocket.h"
#include "Bullet.h"
#include "Laser.h"
#include "Parts.h"
#include "Entity.h"

const int StarsAmount = 3000;
float StarsSpread = 2520.0f;
float StarsDepth = 10.0f;
glm::vec4 Stars[StarsAmount];
glm::vec4 BackgroundStars[StarsAmount];


bool MainMenu = false;
bool switchScene = false;
bool switchToMission = false;
bool OpenMenu = false;
bool Settings = false;
int lastsound = 0;
int lastsound2 = 0;
unsigned int lastplayedsound = 1;

void ProcessCamera(float dt)
{
	if (Exposure < 0.85f)
		Exposure += dt;
	else
        Exposure = 0.85f;
	SceneExposure = Exposure * Exposure * brightness;
	CameraPosition = camerapos + glm::vec2(((rand()%100) * ScreenShake - ScreenShake *50.0f )* s_ScreenShake, ((rand() %100) * ScreenShake - ScreenShake * 50.0f )* s_ScreenShake);
	ScreenShake -= ScreenShakeFallOff * dt;
	ChromaticAbberation -= ChromaticAbberationFallOff * dt;
	if (ScreenShake < 0.0f) ScreenShake = 0.0f;
	if (ChromaticAbberation < 0.0f) ChromaticAbberation = 0.0f;

	if (ScreenShake > 1.0f) ScreenShake = 1.0f;
	if (ChromaticAbberation > 0.3f) ChromaticAbberation = 0.3f;
	ChromaticStrength = ChromaticAbberation * s_ChromaticAbberation;

	UpdateListenerPosition();
}



std::vector <Node> PartSpawnPoints;

void Delete()
{
}

void ChangeMap(std::string FilePath, bool scaleDown = true)
{
	
	for(int i=0;i<Entities.size();i++)
		Entities[i]->Destroy();
	
	//if(Entities.size()>=1)
	Entities.clear();

	for (int i = 0; i < Debris.Parts.size(); i++)
		Debris.Parts[i]->DeletePart();
	Debris.Parts.clear();

	DamageSpheres.clear();
	DamageSpheresArray.clear();
	bullets.clear();
	Rockets.clear();
	Lasers.clear();
	LightEffects.clear();
	GameScene->LoadFrom(FilePath);

	if (scaleDown)
	{
		CameraScale = { 20,20 };
	}
	else
		CameraScale = { 1.0f,1.0f };

	PartSpawnPoints.clear();
	int currentobject = 0;
	for (int i = 0; i < GameScene->Nodes.size(); i++)
	{
		if (GameScene->Nodes[i]->id == 1 && currentobject <= SpawnablePartAmount)
		{
			if(currentobject < PART::LASTPART && currentobject != PART::CENTRALPART && currentobject != PART::STATICPOINT)
			{
				Node mp;
				mp.id = currentobject;
				mp.position = GameScene->Nodes[i]->position;
				PartSpawnPoints.push_back(mp);
			}
			currentobject++;
		}
	}




	lastEntityID = 0;
	std::string menustr = "Scenes/Sun.sav";

	if (menustr == FilePath)
	{
		MainMenu = true;
	}
	else
		MainMenu = false;

	std::cout<<"\nMap Changed to: "<<FilePath;
}

void SpawnPlayer(std::string filename = "Ships/Save0.sav")
{

	glm::vec2 position = glm::vec2(-10, 0.0f);
	glm::vec2 Scale = glm::vec2(0.5f, 0.5f);
	Entities.push_back(new CentralPart);
	Entities[0]->Create(glm::vec2(0.0f, 0.0f) * Scale + position, { 0.0f,1.0f }, PARTSIZE);
	camerapos = Entities[0]->body[0].position;
	Entities[0]->LoadFrom(filename);
	std::cout<<"\nPlayer Spawned";
}

CentralPart* SpawnAiShip(glm::vec2 pos, std::string name)
{
	Entities.push_back(new CentralPart);
	Entities[Entities.size() - 1]->Create(pos, { 0.0f,1.0f }, PARTSIZE);
	Entities[Entities.size() - 1]->LoadFrom(name);
	Entities[Entities.size() - 1]->autocontrol = true;
	Entities[Entities.size() - 1]->trgPos = pos;
	lastEntityID++;
	Entities[Entities.size() - 1]->id = lastEntityID;
	return Entities[Entities.size() - 1];

	
}

bool inbase = true;
std::vector<std::string> shipNames;

#include "Mission.h"

Mission CurrnetMission;

void ProcessPlayerControls()
{
	AqueredCameraScale *= 1.0f + scrollmovement * 0.1f;

	if (AqueredCameraScale.x > 80.0f)
		AqueredCameraScale = { 80.0f, 80.0f };
	if (AqueredCameraScale.x < 1.0f)
		AqueredCameraScale = { 1.0f ,1.0f };

	CameraScale += (AqueredCameraScale - CameraScale) * 0.25f * delta * 60.0f;

	if (JustPressedkey[GLFW_KEY_V])
		absoluteControl = !absoluteControl;

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


	camerapos = Entities[0]->mid;
	Entities[0]->player = true;
	Entities[0]->autocontrol = false;
	listenerVel = { Entities[0]->midvel.x ,Entities[0]->midvel.y ,1.0f };

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
			Entities[0]->Parts[i]->DrawDataConnections(i, bLogicMode, fLogicMode, vLogicMode, 1000);

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
			glm::vec2 mid = (Entities[0]->Parts[0]->body[0].position + Entities[0]->Parts[0]->body[1].position) * 0.5f;

			Entities[0]->Parts[0]->body[0].velocity = ((mid + glm::vec2(0.0f, 1.0f) * Entities[0]->Parts[0]->body[0].r) - Entities[0]->Parts[0]->body[0].position) * 15.0f;
			Entities[0]->Parts[0]->body[1].velocity = ((mid - glm::vec2(0.0f, 1.0f) * Entities[0]->Parts[0]->body[1].r) - Entities[0]->Parts[0]->body[1].position) * 15.0f;

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
					for (auto a : Entities[0]->Parts[i]->BodyIdsWithCollision)
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
					
				}



				if (prevcon == ConCreationStage && !NewConDebrie1)
				{
					for (int i = 0; i < Debris.Parts.size(); i++)
					{
						for (auto a : Debris.Parts[i]->BodyIdsWithCollision)
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
						
					}


				}
				if (ConCreationStage == 1 && prevcon != ConCreationStage)
				{
					Sparks.Spawn(NewConBall1->position, rand() % 5 + 5);
					playsound(Clang, MousePosition, 0.3f,2.5f,{0.0f,0.0f},false);
				}
				if (ConCreationStage >= 2)
				{
					playsound(Clang, MousePosition, 0.3f,2.5f,{0.0f,0.0f},false);
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
								playsound(Detach, MousePosition, 0.3f,3.5f,{0.0f,0.0f},false);
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
				if (Debris.Parts[i]->bodysize > 1)
				{
					for (int a = 0; a < Debris.Parts[i]->bodysize; a++)
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
		if (JustReleasedbutton[GLFW_MOUSE_BUTTON_3])
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
		UI_buttonOnlyON(&b, "Strut", { -0.47f * WIDTH ,-0.46f * HEIGHT }, UISize, TextSize, glm::vec4(0.9f), glm::vec4(0.5f), 1200);
		if (b && b != (NewConType == STRUT))
			NewConType = STRUT;

		b = (NewConType == SPRING);
		UI_buttonOnlyON(&b, "Spring", { -0.47f * WIDTH ,-0.40f * HEIGHT }, UISize, TextSize, glm::vec4(0.9f), glm::vec4(0.5f), 1200);
		if (b && b != (NewConType == SPRING))
			NewConType = SPRING;

		b = (NewConType == HEATPIPE);
		UI_buttonOnlyON(&b, "Heat pipe", { -0.47f * WIDTH ,-0.34f * HEIGHT }, UISize, TextSize, glm::vec4(0.9f), glm::vec4(0.5f), 1200);
		if (b && b != (NewConType == HEATPIPE))
			NewConType = HEATPIPE;

		b = (NewConType == ROPE);
		UI_buttonOnlyON(&b, "Rope", { -0.47f * WIDTH ,-0.28f * HEIGHT }, UISize, TextSize, glm::vec4(0.9f), glm::vec4(0.5f), 1200);
		if (b && b != (NewConType == ROPE))
			NewConType = ROPE;





		UI_CheckBox(&align, "Align rotation", { -0.35f * WIDTH ,-0.46f * HEIGHT }, UISize, TextSize, glm::vec4(0.9f), glm::vec4(0.5f), 1200);

		UI_CheckBox(&snapToGrid, "Snap to grid", { -0.20f * WIDTH ,-0.46f * HEIGHT }, UISize, TextSize, glm::vec4(0.9f), glm::vec4(0.5f), 1200);

		UI_TextBox(&saveFileName, { -0.46f * WIDTH ,0.46f * HEIGHT }, 32, { 15 * UISize,UISize * 1.0f }, TextSize, { 0.4f,0.4f,0.4f,0.4f }, { 1.0f,1.0f,1.0f,1.0f }, 1200);

		bool save = false;
		UI_buttonOnlyON(&save, "Save", { -0.46f * WIDTH ,0.40f * HEIGHT }, UISize, TextSize, glm::vec4(0.9f), glm::vec4(0.5f), 1200);
		if (save)
			Entities[0]->SaveTo(saveFileName);

		bool load = false;
		UI_buttonOnlyON(&load, "Load", { -0.46f * WIDTH ,0.34f * HEIGHT }, UISize, TextSize, glm::vec4(0.9f), glm::vec4(0.5f), 1200);
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

	UI_CheckBox(&bLogicMode, "Bools Logic", { 0.40f * WIDTH ,-0.46f * HEIGHT }, UISize, TextSize, UI_ColorON, UI_ColorOFF, 1200);
	UI_CheckBox(&fLogicMode, "Number Logic", { 0.40f * WIDTH ,-0.40f * HEIGHT }, UISize, TextSize, UI_ColorON, UI_ColorOFF, 1200);
	UI_CheckBox(&vLogicMode, "Vector Logic", { 0.40f * WIDTH ,-0.34f * HEIGHT }, UISize, TextSize, UI_ColorON, UI_ColorOFF, 1200);
	UI_CheckBox(&BuildingMode, "Building Mode", { 0.40f * WIDTH ,-0.28f * HEIGHT }, UISize, TextSize, UI_ColorON, UI_ColorOFF, 1200);

	
	bool b = false;
	UI_CheckBox(&b, "StartPirateMission", { 0.40f * WIDTH ,-0.2f * HEIGHT }, UISize, TextSize, UI_ColorON, UI_ColorOFF, 1200);
	if (b)
	{
		Exposure = -0.85f;
		switchToMission = true;
		CurrnetMission.Start(3,1,5);
	}


	if (bLogicMode && blm != bLogicMode)
	{
		bLogicMode = true;
		fLogicMode = false;
		vLogicMode = false;
		BuildingMode = false;
		DataconnectionData[0] = 0;
	}
	else if (fLogicMode && flm != fLogicMode)
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
		DrawLine(GrabbedBall->position, MousePosition, 0.025f, { 1.0f,1.0f,0.0f,1.0f });

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


	//base
	if(inbase)
		for (int i = 0; i < PartSpawnPoints.size(); i++)
		{
			glm::vec2 offset = Entities[0]->mid + glm::vec2(-150, -150);
			glm::ivec2 pos = { roundf(PartSpawnPoints[i].position.x - offset.x),roundf(PartSpawnPoints[i].position.y - offset.y) };

			bool inrange = false;
			bool able = true;
			for (int x = -1; x < 2; x++)
				if (able)
				{
					for (int y = -1; y < 2; y++)
						if ((pos.x + x) >= 0 && (pos.x + x < 300) &&
							(pos.y + y) >= 0 && (pos.y + y < 300))
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
			if (inrange && able )
			{
				if(sqrlength(PartSpawnPoints[i].position - CameraPosition) < 100 * 100)
					Debris.SpawnPart(PartSpawnPoints[i].id, PartSpawnPoints[i].position, PARTSIZE);
			}
		}
	else
	{
		CurrnetMission.Process(delta);

	}

}

void ProcessMainMenu()
{

	// -900;280

	Window* sw = GetWindow(ForeWindowID);
	Window* bw = GetWindow(BackgroundWindowID);
	Window* mw = GetWindow(MenuWindowID);
	
	mw->Use();
	
	glm::vec2 WindowMousePosition = (GetWindow(SceneWindowID)->WindowMousePosition);
	MousePosition.x = WindowMousePosition.x / CameraScale.x + CameraPosition.x;
	MousePosition.y = WindowMousePosition.y / CameraScale.y + CameraPosition.y;
	ScreenMousePosition = WindowMousePosition;

	glm::vec2 Corner = { WIDTH * -0.45f,HEIGHT *0.35f };
	float step = 10.0f;
	glm::vec4 textColor = { 2.0f,2.0f,2.0f,1.0f };
	glm::vec4 textColorOff = { 1.0f,1.0f,1.0f,1.0f };
	int textZ = 2000;
	if (OpenMenu || SettingsWindow)
	{
		UI_DrawCube({ 0.0,0.0f }, { WIDTH * 1.0f,HEIGHT * 1.0f }, 0.0f, { 0.0f, 0.0f, 0.0f, 0.8f }, false, NULL, textZ - 100);
	}

	bool b = false;

	Corner.y += UI_DrawText("HEAT", Corner, TextSize*2.0f, textColor, textZ).y * -1.0f -step;
	
	Corner.y += UI_CheckBox(&b,"Start", Corner, UISize, TextSize, textColor, textColorOff, textZ).y * -1.0f - step;
	if (b)
	{
		Exposure = -0.85f;
		switchScene = true;
	}
	if (Exposure > -0.05f && switchScene)
	{
		mw->End();
		sw->Use();

		
		ChangeMap("Scenes/base.sav", false);

		SpawnPlayer();
		switchScene = false;
		OpenMenu = false;
		SaveSettings();
		sw->End();
		mw->Use();
		
		glm::vec2 WindowMousePosition = (GetWindow(SceneWindowID)->WindowMousePosition);
		MousePosition.x = WindowMousePosition.x / CameraScale.x + CameraPosition.x;
		MousePosition.y = WindowMousePosition.y / CameraScale.y + CameraPosition.y;
		ScreenMousePosition = WindowMousePosition;
	}

	Corner.y += UI_CheckBox(&Settings, "Settings", Corner, UISize, TextSize, textColor, textColorOff, textZ).y * -1.0f - step;
	
	if (Settings)
	{
		glm::vec2 s_Corner = { WIDTH * -0.115f,HEIGHT * 0.35f };
		bool b = false;

		s_Corner.y += UI_DrawText("Settings", s_Corner, TextSize * 2.0, textColor, textZ).y * -1.0f - step;

		s_Corner.y += UI_CheckBox(&bloom, "Bloom", s_Corner, UISize, TextSize, textColor, textColorOff, textZ).y * -1.0f - step;
		s_Corner.y += UI_Slider(&brightness, "Brightness", s_Corner, 0.1f,1.5f, { 10 * UISize,UISize * 0.35f }, TextSize, textColor, textColor, textZ).y * -1.0f - step;

		s_Corner.y += UI_CheckBox(&b, "Reset to default", s_Corner , UISize, TextSize, textColor, textColorOff, textZ).y * -1.0f - step;
		if (b)
			ResetSettings();

		s_Corner.y += UI_CheckBox(&s_Fullscreen, "Full screen", s_Corner, UISize, TextSize, textColor, textColorOff, textZ).y * -1.0f - step;
		b = false;
		float stepX = UI_CheckBox(&b, "-", s_Corner , UISize, TextSize, textColor, textColorOff, textZ).x * 0.5f + step;
		if (b)
		{
			SRiter--;
			if (SRiter < 0)
				SRiter = 7;
			s_Resolution = StandartResolutions[SRiter];

			RX = std::to_string(s_Resolution.x);
			RY = std::to_string(s_Resolution.y);
			RX.resize(4);
			if (RX[3] == '.')
				RX.pop_back();

			RY.resize(4);
			if (RY[3] == '.')
				RY.pop_back();
		}


		std::string BRX = RX;
		std::string BRY = RY;
		stepX += UI_TextBox(&RX, s_Corner + glm::vec2(stepX, 0.0f), -1, { 5 * UISize,UISize * 1.0f }, TextSize, textColorOff, textColor , textZ).x * 0.5f + step;
		
		stepX += UI_TextBox(&RY, s_Corner + glm::vec2(stepX, 0.0f), -1, { 5 * UISize,UISize * 1.0f }, TextSize, textColorOff, textColor, textZ).x * 0.5f + step;
	

		if (BRX != RX || BRY != RY)
			SRiter = 0;
		b = false;
		s_Corner.y += UI_CheckBox(&b,"+", s_Corner + glm::vec2(stepX, 0.0f), UISize, TextSize, textColor, textColorOff, textZ).y * -1.0f - step;
		if(b)
		{
			SRiter++;
			if (SRiter > 7)
				SRiter = 0;
			s_Resolution = StandartResolutions[SRiter];

			RX = std::to_string(s_Resolution.x);
			RY = std::to_string(s_Resolution.y);
			RX.resize(4);
			if (RX[3] == '.')
				RX.pop_back();

			RY.resize(4);
			if (RY[3] == '.')
				RY.pop_back();
		}
	

		s_Corner.y += -20 - step;
		s_Corner.y += UI_DrawText("Resolution or Full screen changes require a reload", s_Corner, TextSize, textColor, textZ).y * -1.0f - step;


		s_Corner.y += UI_Slider(&s_ChromaticAbberation, "Chromatic abberation", s_Corner, 0.0f, 1.0f, { 10 * UISize,UISize * 0.35f }, TextSize, textColor, textColor, textZ).y * -1.0f - step;

		s_Corner.y += UI_Slider(&s_ScreenShake, "Screen shake", s_Corner, 0.0f, 1.0f, { 10* UISize,UISize * 0.35f }, TextSize, textColor, textColor, textZ).y * -1.0f - step;
		/*b = false;
		s_Corner.y += UI_CheckBox(&b, "Save", s_Corner, 25.0f, 1.0f).y * -1.0f - step;
		if (b)
			SaveSettings();*/



	}
	
	
	
	
	b = false;
	Corner.y += UI_CheckBox(&b, "Exit", Corner, UISize, TextSize, textColor, textColorOff, textZ).y * -1.0f - step;
	if (b)
	{
		SaveSettings();
		glfwSetWindowShouldClose(window, true);
	}
	mw->End();
}


void Ready()
{
	
	LoadTextures();

	noize = NULL;
	GenNoizeTexture(&noize, 100, 2, 1.0f, 2);

	GenPrimitiveTexture(&PrimitiveQuad.Texture,5,QUAD);
	//LoadFont("engine/fonts/LiberationSansR.ttf", 128);

	
	GenPrimitiveTexture(&MO_Ball.mater.Texture,1000,CIRCLE,true);
	GenPrimitiveTexture(&MO_Cube.mater.Texture,5,QUAD);
	MO_Ball.mater.NormalMap = BallNormalMapTexture;
	MO_Cube.mater.NormalMap = CubeNormalMapTexture;

	float maxsize = fmaxf(WIDTH, HEIGHT);
	TextSize = maxsize * 0.0005f * 0.35f;
	UISize = 25 * maxsize * 0.0005f;

	RX = std::to_string(s_Resolution.x);
	RY = std::to_string(s_Resolution.y);
	RX.resize(4);
	if (RX[3] == '.')
		RX.pop_back();

	RY.resize(4);
	if (RY[3] == '.')
		RY.pop_back();

	for (int i = 0; i < StarsAmount; i++)
	{
		Stars[i].x = rand() % 1000 * 0.001f * StarsSpread - StarsSpread * 0.5f + camerapos.x;
		Stars[i].y = rand() % 1000 * 0.001f * StarsSpread - StarsSpread * 0.5f + camerapos.y;
		Stars[i].z = rand() % 1000 * 0.0001f * StarsDepth;
		Stars[i].w = rand() % 1000 * 0.001f * pi * 0.5f;


		BackgroundStars[i].x = rand() % 1000 * 0.001f * StarsSpread - StarsSpread * 0.5f + camerapos.x;
		BackgroundStars[i].y = rand() % 1000 * 0.001f * StarsSpread - StarsSpread * 0.5f + camerapos.y;
		BackgroundStars[i].z = rand() % 1000 * 0.0001f * StarsDepth;
		BackgroundStars[i].w = rand() % 1000 * 0.001f * pi * 0.5f;
	}
	soundscale = { 40.0f,40.0f ,1.0f };


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
	
	SetupPEs();
	shipNames.clear();
	shipNames.push_back("./Ships/Bigboy.sav");
	shipNames.push_back("./Ships/Cube.sav");
	shipNames.push_back("./Ships/Rotator.sav");
	shipNames.push_back("./Ships/Save0.sav");
	shipNames.push_back("./Ships/Save1.sav");
	shipNames.push_back("./Ships/Spinner.sav");

	GameSaveFile.Load("SaveFile.sav");
	ChangeMap("Scenes/Sun.sav", false);

	//SpawnPlayer();


	listenerPos.z = 2.0f;

	

	glfwSwapInterval(0);
	VSync = 0;
	AmbientLight = 0.4f;


	ForeWindowID = CreateWindow();
	BackgroundWindowID = CreateWindow();
	MenuWindowID = CreateWindow();

	Window* sw = GetWindow(ForeWindowID);
	Window* bw = GetWindow(BackgroundWindowID);
	Window* mw = GetWindow(MenuWindowID);


	sw->AutoActive = false;
	bw->AutoActive = false;
	mw->AutoActive = false;

	sw->hdr = true;

	sw->Init(GetWindow(SceneWindowID)->ViewportSize);
	bw->Init(GetWindow(SceneWindowID)->ViewportSize);
	mw->Init(GetWindow(SceneWindowID)->ViewportSize);


    sw->backgroundColor = { 0.0f,0.0f,0.0f,0.0f };
    bw->backgroundColor = { 0.0f,0.0f,0.0f,1.0f };
	mw->backgroundColor = { 0.0f,0.0f,0.0f,0.0f };

	sw->w_AmbientLight = 0.4f;
	bw->w_AmbientLight = 0.1f;
	sw->w_DirectionalLight = 2.0f;

	//Background.LoadFrom("Scenes/Sun.sav");

	
	addsound(SHHSound,true,10);
	addsound(RocketEngineSound,true,20);
	addsound(MiniGunSound,true,10);
	addsound(ExplodionSound,false,10);
	addsound(BulletHit,false,10);
	addsound(Hit,false,20);
	addsound(PartDestrSOund,false,10);
	addsound(Scratch,true,10);
	addsound(Detach,false,10);
	addsound(Clang,false,10);
	addsound(LaserGunSound,true,10);
	addsound(HeavyHit,false,10);
	addsound(GunSound,false,10);
	//150 sources used

}
void SubSteppedProcess(float dt, int SubStep)
{
	Window* sw = GetWindow(ForeWindowID);
	sw->Use();
	ProcessEntities(delta, SubStep);

	for(int i=0;i<Sounds.size();i++)
	{
		Sounds[i].Update();
	}
	sw->End();
    UseWindow(SceneWindowID);
}

void Process(float dt)
{

	if (clock() < 100)
		Speed = 0.0f;
	else if (clock() >= 100 && clock() < 1200)
		Speed = 1.0f;

	if (delta > 0.017f)
		delta = 0.017f;

	delta *= Speed;
	in_UI--;

	if (in_UI < 0)
		in_UI = 0;

	Window* sw = GetWindow(ForeWindowID);
	Window* bw = GetWindow(BackgroundWindowID);
	Window* mw = GetWindow(MenuWindowID);

	sw->w_AmbientLight = AmbientLight;
	bw->Use();
	
	//if(!MainMenu)
		//Background.Draw(delta);

	bw->End();
	sw->active = true;

	sw->Use();
	glm::vec2 WindowMousePosition = (GetWindow(SceneWindowID)->WindowMousePosition);
	MousePosition.x = WindowMousePosition.x / CameraScale.x + CameraPosition.x;
	MousePosition.y = WindowMousePosition.y / CameraScale.y + CameraPosition.y;
	ScreenMousePosition = WindowMousePosition;
	foregroundMousePosition =MousePosition; 
	

	if (JustReleasedkey[GLFW_KEY_ESCAPE])
		OpenMenu = !OpenMenu;

	if (JustPressedbutton[GLFW_MOUSE_BUTTON_1])
		LastJustPressedLMBScrMousePos = { 0.0f,0.0f };

	ImGui::Begin("Settings");
	ImGui::SliderFloat("speed", &Speed, 0.0f, 10.0f);
	ImGui::Text("ballssize = %.i", balls.size());
	ImGui::Text("%.1ffps (%.4fms)", 1.0f/delta,delta);


	unsigned int soundsrc;
	GenSource(&soundsrc);
	ImGui::Text("sound source id %.i", soundsrc);
	DeleteSource(&soundsrc);


	ImGui::Text("sources size (%.i)", sources.size());




	
	reloadSources = false;
	bool res = false;
	for (int i = 0; i < sources.size(); i++)
	{
		if (*sources[i] < 0)
			res = true;

	}
	if (sources.size() > 10000 || ImGui::Button("Relopad sound") || res)
	{
		for (int i = 0; i < sources.size();i++)
			DeleteSource(sources[i]);
		sources.clear();
		AL_Reload();
		reloadSources = true;
	}

	ImGui::Text("parts size (%.i)", Debris.Parts.size());

	ImGui::Text("Camera position { %.2f ; %.2f }", CameraPosition.x, CameraPosition.y);
	ImGui::SliderFloat("AmbientLight", &AmbientLight, 0.0f, 1.0f);
	

	ExplodionLightHeight *= 10.0f;
	EngineLightHeight *= 10.0f;
	BulletHitLightHeight *= 10.0f;
	CentralLightHeight *= 10.0f;

	ImGui::SliderFloat("Explodion Light Height", &ExplodionLightHeight, -0.1f, 0.2f);
	ImGui::SliderFloat("Engine Light Height", &EngineLightHeight, -0.1f, 0.2f);
	ImGui::SliderFloat("BulletHit Light Height", &BulletHitLightHeight, -0.1f, 0.2f);
	ImGui::SliderFloat("Central Light Height", &CentralLightHeight, -0.1f, 0.2f);

	ExplodionLightHeight *= 0.1f;
	EngineLightHeight *= 0.1f;
	BulletHitLightHeight *= 0.1f;
	CentralLightHeight *= 0.1f;

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
	ImGui::Text("zoom = %.2f", CameraScale.x);
	ImGui::End();


	int currentObject = 1;
	balls.clear();


	
	if (clock() > 250)
	{
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

			DrawCube(glm::vec2(Stars[i]), glm::vec2(Stars[i].z * 0.25f), Stars[i].w, glm::vec4(1.0f, 1.0f, 1.0f, Stars[i].z * 10.0f / StarsDepth));

		}
		sw->End();
		bw->Use();
		for (int i = 0; i < StarsAmount*0.2; i++)
		{
			if (BackgroundStars[i].x > CameraPosition.x + StarsSpread * 0.5f)
			{
				BackgroundStars[i].x = CameraPosition.x - StarsSpread * 0.5f;
				BackgroundStars[i].y = CameraPosition.y + rand() % 10000 * 0.0001f * StarsSpread - StarsSpread * 0.5f;
			}
			if (BackgroundStars[i].x < CameraPosition.x - StarsSpread * 0.5f)
			{
				BackgroundStars[i].x = CameraPosition.x + StarsSpread * 0.5f;
				BackgroundStars[i].y = CameraPosition.y + rand() % 10000 * 0.0001f * StarsSpread - StarsSpread * 0.5f;
			}
			if (BackgroundStars[i].y > CameraPosition.y + StarsSpread * 0.5f)
			{
				BackgroundStars[i].y = CameraPosition.y - StarsSpread * 0.5f;
				BackgroundStars[i].x = CameraPosition.x + rand() % 10000 * 0.0001f * StarsSpread - StarsSpread * 0.5f;
			}
			if (BackgroundStars[i].y < CameraPosition.y - StarsSpread * 0.5f)
			{
				BackgroundStars[i].y = CameraPosition.y + StarsSpread * 0.5f;
				BackgroundStars[i].x = CameraPosition.x + rand() % 10000 * 0.0001f * StarsSpread - StarsSpread * 0.5f;
			}

			DrawCube(glm::vec2(BackgroundStars[i]*2.0f), glm::vec2(BackgroundStars[i].z * 1.25f), BackgroundStars[i].w, glm::vec4(1.0f, 1.0f, 1.0f, BackgroundStars[i].z * 10.0f / StarsDepth));
		}
		bw->End();
		sw->Use();
		glm::vec2 WindowMousePosition = (GetWindow(SceneWindowID)->WindowMousePosition);
		MousePosition.x = WindowMousePosition.x / CameraScale.x + CameraPosition.x;
		MousePosition.y = WindowMousePosition.y / CameraScale.y + CameraPosition.y;
		ScreenMousePosition = WindowMousePosition;
		foregroundMousePosition =MousePosition; 
	}
	
	if (!Settings) {
		if (keys[GLFW_KEY_1])
		{

			DamageSphere DS;
			DS.body.r = 10.25f;
			DS.body.position = MousePosition;
			DS.Damage = false;
			DS.timeLeft = 0.044f;
			DS.Heat = 0.0f;
			DS.recoil = -1.0f;
			DS.neutral = true;
			//DS.friction = 0.00f;
			DS.singleHit = false;
			DamageSpheresArray.push_back(DS);
		}
		if (JustPressedkey[GLFW_KEY_2])
		{
			Entities.push_back(new CentralPart);
			Entities[Entities.size() - 1]->Create(MousePosition, { 0.0f,1.0f }, PARTSIZE);
			Entities[Entities.size() - 1]->LoadFrom("Save0.sav");
			Entities[Entities.size() - 1]->autocontrol = true;
			Entities[Entities.size() - 1]->trgPos = MousePosition;
			lastEntityID++;
			Entities[Entities.size() - 1]->id = lastEntityID;
			//Entities[Entities.size() - 1]->CP.Health = -10;

		}
		if (JustPressedkey[GLFW_KEY_3])
		{
			Entities.push_back(new CentralPart);
			Entities[Entities.size() - 1]->Create(MousePosition, { 0.0f,1.0f }, PARTSIZE);
			Entities[Entities.size() - 1]->LoadFrom("Bigboy.sav");
			Entities[Entities.size() - 1]->autocontrol = true;
			Entities[Entities.size() - 1]->trgPos = MousePosition;
			lastEntityID++;
			Entities[Entities.size() - 1]->id = lastEntityID;
			//Entities[Entities.size() - 1]->CP.Health = -10;

		}
		if (JustPressedkey[GLFW_KEY_4])
		{
			SpawnExplodion(MousePosition, 10.0f, 0.5f, 0.4f);
		}
	}
	

	ProcessPE(delta);


	ProcessLightEffects(delta);
	
	//DrawCircle(MousePosition,10.0f);

	if (!OpenMenu && !MainMenu)
		ProcessPlayerControls();
	ProcessCamera(delta);
	
	//Map.ParticleEmiters.clear();
	ProcessExplodions(delta);

    GameScene->Draw();
	
	sw->End();

	if (OpenMenu || MainMenu)
		ProcessMainMenu();

	bw->w_CameraPosition = sw->w_CameraPosition*0.1f;

    bw->End();
    UseWindow(SceneWindowID);
	
    bw->Draw(0);

    sw->Draw(1);

    mw->Draw(2);
	

}

void PreReady()
{
    // Remake with DataStorage

	std::ifstream f("Settings.sav");
	if (f.is_open())
		while (!f.eof())
		{

			char junk;
			char line[256];
			f.getline(line, 256);
			std::strstream s;
			s << line;



			if (line[0] == 'R' && line[1] == 'e' && line[2] == 's')
				s >> junk >> junk >> junk >> s_Resolution.x >> s_Resolution.y;

			else if (line[0] == 'B' && line[1] == 'r' && line[2] == ' ')
				s >> junk >> junk >> brightness;

			else if (line[0] == 'B' && line[1] == 'l' && line[2] == ' ')
				s >> junk >> junk >> bloom;

			else if (line[0] == 'F' && line[1] == 'S' && line[2] == ' ')
				s >> junk >> junk >> s_Fullscreen;
			else if (line[0] == 'S' && line[1] == 'h' && line[2] == ' ')
				s >> junk >> junk >> s_ScreenShake;
			else if (line[0] == 'C' && line[1] == 'a' && line[2] == ' ')
				s >> junk >> junk >> s_ChromaticAbberation;

		}

	f.close();

	PartsData.Load("PartsProperties.ds");
	InitParts();
	PartsData.Save("PartsProperties.ds");
	

}

void SceneEnd()
{

	for(int i=0;i<Entities.size();i++)
		Entities[i]->Destroy();
	Entities.clear();

	for (int i = 0; i < Debris.Parts.size(); i++)
		Debris.Parts[i]->DeletePart();
	Debris.Parts.clear();

	DamageSpheres.clear();
	DamageSpheresArray.clear();
	bullets.clear();
	Rockets.clear();
	Lasers.clear();
	LightEffects.clear();
	clearParticleMaterials();

}
void Rescale(int newWindth,int newHeight)
{

	Window* sw = GetWindow(ForeWindowID);
	Window* bw = GetWindow(BackgroundWindowID);
	Window* mw = GetWindow(MenuWindowID);
	sw->ViewportSize = GetWindow(SceneWindowID)->ViewportSize;
	sw->RecalculateSize();

	bw->ViewportSize = GetWindow(SceneWindowID)->ViewportSize;
	bw->RecalculateSize();

	mw->ViewportSize = GetWindow(SceneWindowID)->ViewportSize;
	mw->RecalculateSize();

}

void Destroy()
{	
	GameSaveFile.Save("SaveFile.sav");
	Delete();
	SaveSettings();
}