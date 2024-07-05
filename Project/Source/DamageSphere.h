#pragma once
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