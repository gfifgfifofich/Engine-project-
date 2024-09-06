#pragma once

class DestructableStaticBall : public CO_Ball
{
public:	

	DestructableStaticBall();
	virtual ~DestructableStaticBall() override;
	float health = 10.0f;

	int DestrParticleAmount = 10;
	float DestrParticleSpeed = 10;
	bool SpawnInShapeOrPoint = true;
	bool ExplodeOnOverheat = false;
	bool ExplodeOnDeath = false;
	bool DieOnOverheat = false;
	bool Invincibility = false;
	float temperature = 0.0f;
	float maxTemperature = 10.0f;
	float trgTemperature = 0.0f;
	float passiveCooling = 1.0f;//per sec

	float explodionR = 10.0f;
	float explodionDamage = 2.5f;
	float explodionLifeTime = 1.0f;
	float explodionRecoil = 40.0f;
	
	glm::vec4 HeatColor = glm::vec4(60.0f,10.0f,2.0f,0.0f);
	glm::vec4 ColdColor = glm::vec4(0.04f,2.0f,10.0f,0.0f);
	glm::vec4 color = glm::vec4(1.0f);

	ParticleAsset* partAsset = NULL;
	std::string partAssetName = "None";

	UI_DataPack GetUIDataDestructableStaticBall()
	{
		UI_DataPack uidp;
		uidp.name = "DestructableStaticBall";

		uidp.fdata.push_back(&health);
		uidp.fdatanames.push_back("Health");	

		uidp.fdata.push_back(&temperature);
		uidp.fdatanames.push_back("temperature");	
		uidp.fdata.push_back(&maxTemperature);
		uidp.fdatanames.push_back("maxTemperature");	

		uidp.fdata.push_back(&trgTemperature);
		uidp.fdatanames.push_back("trgtemperature");	

		uidp.fdata.push_back(&passiveCooling);
		uidp.fdatanames.push_back("passiveCooling");	

		uidp.fdata.push_back(&DestrParticleSpeed);
		uidp.fdatanames.push_back("DestrParticleSpeed");	

		uidp.fdata.push_back(&explodionR);
		uidp.fdatanames.push_back("explodionR");	

		uidp.fdata.push_back(&explodionDamage);
		uidp.fdatanames.push_back("explodionDamage");	

		uidp.fdata.push_back(&explodionLifeTime);
		uidp.fdatanames.push_back("explodionLifeTime");	

		uidp.fdata.push_back(&explodionRecoil);
		uidp.fdatanames.push_back("explodionRecoil");	

		uidp.idata.push_back(&DestrParticleAmount);
		uidp.idatanames.push_back("DestrParticleAmount");	

		uidp.bdata.push_back(&SpawnInShapeOrPoint);
		uidp.bdatanames.push_back("SpawnInShapeOrPoint");	

		uidp.bdata.push_back(&ExplodeOnOverheat);
		uidp.bdatanames.push_back("ExplodeOnOverheat");	

		uidp.bdata.push_back(&ExplodeOnDeath);
		uidp.bdatanames.push_back("ExplodeOnDeath");	

		uidp.bdata.push_back(&DieOnOverheat);
		uidp.bdatanames.push_back("DieOnOverheat");	

		uidp.bdata.push_back(&Invincibility);
		uidp.bdatanames.push_back("Invincibility");	

		uidp.textdata.push_back(&partAssetName);
		uidp.textdatanames.push_back("DestructionParticleAsset");	

		uidp.v4data.push_back(&HeatColor);
		uidp.v4datanames.push_back("HeatColor");	

		uidp.v4data.push_back(&ColdColor);
		uidp.v4datanames.push_back("ColdColor");	

		uidp.v4data.push_back(&color);
		uidp.v4datanames.push_back("color");	
		return uidp;
	}
	virtual std::vector<UI_DataPack> GetUIData() override
	{
		std::vector<UI_DataPack> data;
		data.push_back(GetUIDataNode());
		data.push_back(GetUIDataObject());
		data.push_back(GetUIDataCollisionObject());
		data.push_back(GetUIDataCO_Ball());
		data.push_back(GetUIDataDestructableStaticBall());
		return data;
	};
	void MTProcess(float dt) override
	{
		ObjectUpdateMaterial();

		b.Force = { 0.0f,0.0f };
		b.velocity = { 0.0f,0.0f };
		b.Process(dt);
		b.position = position;
		b.roughness = roughness;
		b.bounciness = bounciness;

		if (temperature > trgTemperature)
			temperature -= dt * (passiveCooling + temperature/maxTemperature * passiveCooling);
		if (temperature < trgTemperature)
			temperature += dt * (passiveCooling + temperature/maxTemperature * passiveCooling);

		float tmpdiv = 1.0f / maxTemperature;
		if (temperature > 0.0f)
			Color = color + HeatColor * (temperature * tmpdiv);
		else
			Color = color + ColdColor * (temperature * tmpdiv);

		if(Invincibility)
			health = 10.0f;

		if(DieOnOverheat && temperature > maxTemperature)
			health = -10.0f;
		

		
		bool texexists = false;
		for(auto pa : AvailableParticleAssets)
		{

			if(pa->Name == partAssetName && !texexists && !pa->Delete)
			{
				partAsset = pa;
				texexists=true;
				break;
			}
		}
		if(!texexists)
			partAsset = NULL;

		if(health<=0.0f && !Delete)
		{
			health = -100.0f;// dead for shure
			Delete = true;

			
			if(ExplodeOnDeath || (ExplodeOnOverheat && temperature > maxTemperature))
				SpawnExplodion(position,explodionR, explodionDamage,explodionLifeTime,explodionRecoil);

			if(SpawnInShapeOrPoint)
			{
				for(int i=0;i<DestrParticleAmount;i++)
				{
					glm::vec2 randvec = {(rand()%1000 * 0.002f) - 1.0f,(rand()%1000 * 0.002f) - 1.0f};
					partAsset->pe.Spawn(Normalize(randvec) * b.r + position,randvec * DestrParticleSpeed,1);
				}
			}
			else
			{
				for(int i=0;i<DestrParticleAmount;i++)
				{
					glm::vec2 randvec = {(rand()%1000 * 0.002f) - 1.0f,(rand()%1000 * 0.002f) - 1.0f};
					partAsset->pe.Spawn(position,randvec * DestrParticleSpeed,1);
				}
			}
		}
	}

};

class DestructableStaticCube : public CO_Cube
{
public:	

	DestructableStaticCube();
	virtual ~DestructableStaticCube() override;
	float health = 10.0f;

	int DestrParticleAmount = 10;
	float DestrParticleSpeed = 10;
	bool SpawnInShapeOrPoint = true;
	bool ExplodeOnOverheat = false;
	bool ExplodeOnDeath = false;
	bool DieOnOverheat = false;
	bool Invincibility = false;
	float temperature = 0.0f;
	float maxTemperature = 10.0f;
	float trgTemperature = 0.0f;
	float passiveCooling = 1.0f;//per sec

	float explodionR = 10.0f;
	float explodionDamage = 2.5f;
	float explodionLifeTime = 1.0f;
	float explodionRecoil = 40.0f;
	
	glm::vec4 HeatColor = glm::vec4(60.0f,10.0f,2.0f,0.0f);
	glm::vec4 ColdColor = glm::vec4(0.04f,2.0f,10.0f,0.0f);
	glm::vec4 color = glm::vec4(1.0f);

	ParticleAsset* partAsset = NULL;
	std::string partAssetName = "None";
	UI_DataPack GetUIDataDestructableStaticBall()
	{
		UI_DataPack uidp;
		uidp.name = "DestructableStaticCube";
		uidp.fdata.push_back(&health);
		uidp.fdatanames.push_back("Health");	

		uidp.fdata.push_back(&temperature);
		uidp.fdatanames.push_back("temperature");	
		uidp.fdata.push_back(&maxTemperature);
		uidp.fdatanames.push_back("maxTemperature");	

		uidp.fdata.push_back(&trgTemperature);
		uidp.fdatanames.push_back("trgtemperature");	

		uidp.fdata.push_back(&passiveCooling);
		uidp.fdatanames.push_back("passiveCooling");	

		uidp.fdata.push_back(&DestrParticleSpeed);
		uidp.fdatanames.push_back("DestrParticleSpeed");	

		uidp.fdata.push_back(&explodionR);
		uidp.fdatanames.push_back("explodionR");	

		uidp.fdata.push_back(&explodionDamage);
		uidp.fdatanames.push_back("explodionDamage");	

		uidp.fdata.push_back(&explodionLifeTime);
		uidp.fdatanames.push_back("explodionLifeTime");	

		uidp.fdata.push_back(&explodionRecoil);
		uidp.fdatanames.push_back("explodionRecoil");	

		uidp.idata.push_back(&DestrParticleAmount);
		uidp.idatanames.push_back("DestrParticleAmount");	

		uidp.bdata.push_back(&SpawnInShapeOrPoint);
		uidp.bdatanames.push_back("SpawnInShapeOrPoint");	

		uidp.bdata.push_back(&ExplodeOnOverheat);
		uidp.bdatanames.push_back("ExplodeOnOverheat");	

		uidp.bdata.push_back(&ExplodeOnDeath);
		uidp.bdatanames.push_back("ExplodeOnDeath");	

		uidp.bdata.push_back(&DieOnOverheat);
		uidp.bdatanames.push_back("DieOnOverheat");	

		uidp.bdata.push_back(&Invincibility);
		uidp.bdatanames.push_back("Invincibility");	

		uidp.textdata.push_back(&partAssetName);
		uidp.textdatanames.push_back("DestructionParticleAsset");	

		uidp.v4data.push_back(&HeatColor);
		uidp.v4datanames.push_back("HeatColor");	

		uidp.v4data.push_back(&ColdColor);
		uidp.v4datanames.push_back("ColdColor");	

		uidp.v4data.push_back(&color);
		uidp.v4datanames.push_back("color");	
		return uidp;
	}
	virtual std::vector<UI_DataPack> GetUIData() override
	{
		std::vector<UI_DataPack> data;
		data.push_back(GetUIDataNode());
		data.push_back(GetUIDataObject());
		data.push_back(GetUIDataCollisionObject());
		data.push_back(GetUIDataCO_Cube());
		data.push_back(GetUIDataDestructableStaticBall());
		return data;
	};
	void MTProcess(float dt) override
	{
		ObjectUpdateMaterial();

		c.position = position;
		

		if (temperature > trgTemperature)
			temperature -= dt * (passiveCooling + temperature/maxTemperature * passiveCooling);
		if (temperature < trgTemperature)
			temperature += dt * (passiveCooling + temperature/maxTemperature * passiveCooling);

		float tmpdiv = 1.0f / maxTemperature;
		if (temperature > 0.0f)
			Color = color + HeatColor * (temperature * tmpdiv);
		else
			Color = color + ColdColor * (temperature * tmpdiv);

		if(DieOnOverheat && temperature > maxTemperature)
			health = -10.0f;
		

		
		bool texexists = false;
		for(auto pa : AvailableParticleAssets)
		{

			if(pa->Name == partAssetName && !texexists && !pa->Delete)
			{
				partAsset = pa;
				texexists=true;
				break;
			}
		}
		if(!texexists)
			partAsset = NULL;

		if(Invincibility)
			health = 10.0f;

		if(health<=0.0f && !Delete)
		{
			health = -100.0f;// dead for shure
			Delete = true;

			
			if(ExplodeOnDeath || (ExplodeOnOverheat && temperature > maxTemperature))
				SpawnExplodion(position,explodionR, explodionDamage,explodionLifeTime,explodionRecoil);

			if(SpawnInShapeOrPoint)
			{
				for(int i=0;i<DestrParticleAmount;i++)
				{
					glm::vec2 randvec = {(rand()%1000 * 0.002f) - 1.0f,(rand()%1000 * 0.002f) - 1.0f};
					partAsset->pe.Spawn(randvec * glm::vec2(c.width,c.height)+ position,randvec * DestrParticleSpeed,1);
				}
			}
			else
			{
				for(int i=0;i<DestrParticleAmount;i++)
				{
					glm::vec2 randvec = {(rand()%1000 * 0.002f) - 1.0f,(rand()%1000 * 0.002f) - 1.0f};
					partAsset->pe.Spawn(position,randvec * DestrParticleSpeed,1);
				}
			}
		}
	}

};

std::vector<DestructableStaticBall*> DestructableStaticBalls;
std::vector<DestructableStaticCube*> DestructableStaticCubes;
struct DamageSphere
{
	ball body;

	float Damage = 1.0f;
	float Heat = 1.0f;
	float friction = 1.0f;
	float timeLeft = 1.0f;

	float recoil = 600.0f;

	bool infinite = false;
	bool singleHit = true;
	bool dead = false;
	int id = 0;
	bool neutral = false;

};

std::vector<DamageSphere>DamageSpheresArray;
std::vector<DamageSphere*>DamageSpheres;

void ProcessDamageSpheres(float dt)
{
	int iter = 0;
	while (iter<DestructableStaticBalls.size())
		if(DestructableStaticBalls[iter]->Delete || DestructableStaticBalls[iter]->health <=0.0f)
		{
			DestructableStaticBalls[iter] = DestructableStaticBalls[DestructableStaticBalls.size()-1];
			DestructableStaticBalls.pop_back();
		}	
		else
			iter++;
	iter = 0;
	while (iter<DestructableStaticCubes.size())
		if(DestructableStaticCubes[iter]->Delete || DestructableStaticCubes[iter]->health <=0.0f)
		{
			DestructableStaticCubes[iter] = DestructableStaticCubes[DestructableStaticCubes.size()-1];
			DestructableStaticCubes.pop_back();
		}		
		else
			iter++;
	
	for(auto ds : DamageSpheres)
	{
		if(ds->dead)
			continue;
		//DestructableStaticCubes
		for(auto dcb : DestructableStaticBalls)
			if(BtBCollisionCheck(dcb->b,ds->body))
				{
					dcb->health -= ds->Damage;
					dcb->temperature += ds->Heat;
					if(ds->singleHit)
						{
							ds->dead = true;
							break;
						}
				}
		for(auto dcc : DestructableStaticCubes)
			if(BtCCollisionCheck(ds->body,dcc->c))
				{
					dcc->health -= ds->Damage;
					dcc->temperature += ds->Heat;
					if(ds->singleHit)
						{
							ds->dead = true;
							break;
						}
				}
	}

	DamageSpheres.clear();
	glm::vec3 DamageColor = glm::vec3(0.0f,1.0f,1.0f);
	glm::vec3 HeatColor = glm::vec3(10.0f,2.0f,1.1f);
	glm::vec3 ColdColor = glm::vec3(HeatColor.z, HeatColor.y, HeatColor.x);
	glm::vec3 FrictionColor = glm::vec3(1.0f,1.0f,1.0f);

	for (int i = 0; i < DamageSpheresArray.size(); i++)
	{
		bool del = true;

	

		while (del && i < DamageSpheresArray.size())
		{
			if (!DamageSpheresArray[i].singleHit && !DamageSpheresArray[i].infinite)
			{
				DamageSpheresArray[i].timeLeft -= dt;
				

				
				DrawCircle(DamageSpheresArray[i].body,
					glm::vec4(DamageColor * DamageSpheresArray[i].Damage
						+ (DamageSpheresArray[i].Heat > 0.0f ? DamageSpheresArray[i].Heat * HeatColor: -DamageSpheresArray[i].Heat*ColdColor)
						+ FrictionColor* DamageSpheresArray[i].friction,
						0.1f* DamageSpheresArray[i].timeLeft >1.0f? 1.0f: 0.1f * DamageSpheresArray[i].timeLeft));



				DamageSpheres.push_back(&DamageSpheresArray[i]);
			}
			if (DamageSpheresArray[i].dead || DamageSpheresArray[i].timeLeft <= 0.0f)
			{
				del = true;
				DamageSpheresArray[i] = DamageSpheresArray[DamageSpheresArray.size() - 1];
				DamageSpheresArray.pop_back();
			}
			else
				del = false;
		}
	}


}