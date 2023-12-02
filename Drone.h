#pragma once


class Drone
{
public:
	
	

	float hp = 5.0f;
	float maxhp = 5.0f;

	float timers[3] = {1.0f,1.0f,1.0f};

	int id = 0;
	int MovePointId = 0;
	int RestPosId = 0;
	int type = 0;

	ball body;
	


	glm::vec2 Force = glm::vec2(0.0f);

	RocketEngine r1;
	RocketEngine r2;

	Gun gun;

	float DiagRodLength[4];
	float RodLength[2];

	float throtle[2] = { 0.0f ,0.0f};


	bool SAS = true;
	float SASangle = 0.0f;
	bool TaskInProgress = false;
	float SASTaskAngle1=0.0f;
	float SASTaskAngle2 = 0.0f;
	bool SASTaskStage = false;

	glm::vec2 SASpoint = glm::vec2(100.0f,100.0f);
	bool TranformTaskInProgress = false;
	bool SASTransformVelocity = false;
	glm::vec2 SASTaskPoint = glm::vec2(0.0f);
	glm::vec2 SASTaskBeginPoint = glm::vec2(0.0f);
	float SASTaskPointTimeOut = 5.0f;

	bool JustPressedR = false;
	bool JustReleasedR = false;

	bool DrawNavigation = false;

	float rotation = 0.0f;
	float rotationVelocity = 0.0f;
	float maxthrotle = 1.5f;

	glm::vec2 UpVector = glm::vec2(0.0f);

	float RotationalFriction = 0.75f;

	 

	//SAS settings
	float RotationSpeedMult = 25.0f;
	float rotationAngleMult = 0.15f;
	float staticForce = 0.25f;
	float NearTargetFriction = 0.97f;

	float enginelag = 0.0f;

	float t = 0.0f;
	float shotspeed = 0.3f;
	float damage = 1.0f;
	bool enemy = false;
	bool Safety = true;
	bool sleep = false;

	float dyingtime = 5.0f;

	unsigned int source;

	ball* TargetBall = NULL;

	float GunSpeed = 50000.0f;
	float GunFriction = 15.0f;
	float GunRecoil = 100.0f;

	float regentimer = 3.0f;
	Ray RayCast;

	void Ready(glm::vec2 position, float r, unsigned int* EngSound, bool enemy = false)
	{
		GenSource(&source);
		SetSourceSound(&source, &HeavyShot);
		body.position = position;
		body.r = r;
		body.roughness = 0.0f;
		body.bounciness = 0.1f;

		float engpos = r;
		float engposOffset = r * 1.0f;
		float relengrad = r * 0.5f;

		float ll = engpos + engposOffset;

		float lldiag = sqrt(ll * ll + relengrad * relengrad);

		DiagRodLength[0] = lldiag;
		DiagRodLength[1] = lldiag;
		DiagRodLength[2] = lldiag;
		DiagRodLength[3] = lldiag;

		RodLength[0] = ll * 2.0f;
		RodLength[1] = ll * 2.0f;

		this->enemy = enemy;
		if (!enemy)
		{

			shotspeed = 0.1f;
			damage = 0.7f;
			gun.dmg = damage;
			gun.bulletSpeed = 8000.0f;
			gun.bulletSize = 20.0f;
		}
		else
		{
			shotspeed = 0.5f;
			damage = 0.4f;
			gun.bulletSpeed = 2000.0f;
			gun.bulletSize = 40.0f;
		}
		r1.Ready(position - glm::vec2(ll,0.0f), relengrad, EngSound);
		r2.Ready(position + glm::vec2(ll,0.0f), relengrad, EngSound);

		gun.Ready(position, r * 0.5f, damage, enemy, &HeavyShot);

		gun.speed = GunSpeed;
		gun.RotationalFriction = GunFriction;
		gun.recoil = GunRecoil;

		RayCast.position = gun.body[1].position;
		RayCast.direction = gun.body[1].position - gun.body[0].position;
		RayCast.length = 3000;
		RayCast.Steps = 100;
		RayCast.normalize();
		RayCast.Update();


	}

	void ProcessPhysics(float dt)
	{
		gun.mount = &body;
		gun.position = body.position;
		body.Process(dt);
		r1.Process(dt);
		r2.Process(dt);
		gun.Process(dt);
		r1.Force = Force;
		r2.Force = Force;
		body.Force = Force;

		if (r1.throtle > maxthrotle)r1.throtle = maxthrotle;
		if (r2.throtle > maxthrotle)r2.throtle = maxthrotle;
		if (r2.throtle < -maxthrotle)r2.throtle = -maxthrotle;
		if (r1.throtle < -maxthrotle)r1.throtle = -maxthrotle;


		if (hp > 0.0f)
		{
			Strut(&r1.body[0], &body, DiagRodLength[0]);
			Strut(&r1.body[1], &body, DiagRodLength[1]);
			Strut(&r2.body[0], &body, DiagRodLength[2]);
			Strut(&r2.body[1], &body, DiagRodLength[3]);

			Strut(&r1.body[1], &r2.body[1], RodLength[1]);
			Strut(&r1.body[0], &r2.body[0], RodLength[0]);


			glm::vec2 engpos1 = (r1.body[1].position + r1.body[0].position) * 0.5f;
			glm::vec2 engpos2 = (r2.body[1].position + r2.body[0].position) * 0.5f;

			rotation = (get_angle_between_points(r1.body[1].position, r1.body[0].position) + get_angle_between_points(r2.body[1].position, r2.body[0].position)) * 0.5f;
			rotationVelocity = rotation - body.rotation * 5.0f;
			body.rotationVelocity = rotationVelocity;
			body.rotation = rotation * 0.2f;

			UpVector = Rotate(glm::vec2(0.0f, 1.0f), rotation);

			line dif(engpos1, engpos2);


			glm::vec2 rotvec = body.position - r1.body[0].position;
			rotvec = Normalize(glm::vec2(-rotvec.y, rotvec.x));
			r1.body[0].velocity -= dt * RotationalFriction * DOT(r1.body[0].velocity, rotvec) * rotvec;

			rotvec = body.position - r1.body[1].position;
			rotvec = Normalize(glm::vec2(-rotvec.y, rotvec.x));
			r1.body[1].velocity -= dt * RotationalFriction * DOT(r1.body[1].velocity, rotvec) * rotvec;

			rotvec = body.position - r2.body[0].position;
			rotvec = Normalize(glm::vec2(-rotvec.y, rotvec.x));
			r2.body[0].velocity -= dt * RotationalFriction * DOT(r2.body[0].velocity, rotvec) * rotvec;

			rotvec = body.position - r2.body[1].position;
			rotvec = Normalize(glm::vec2(-rotvec.y, rotvec.x));
			r2.body[1].velocity -= dt * RotationalFriction * DOT(r2.body[1].velocity, rotvec) * rotvec;


			if (PointToLineSideCheck(r1.body[0].position, dif) && !PointToLineSideCheck(r1.body[1].position, dif))
			{
				glm::vec2 s = r1.body[0].position;
				r1.body[0].position = r1.body[1].position;
				r1.body[1].position = s;
			}
			if (PointToLineSideCheck(r2.body[0].position, dif) && !PointToLineSideCheck(r2.body[1].position, dif))
			{
				glm::vec2 s = r2.body[0].position;
				r2.body[0].position = r2.body[1].position;
				r2.body[1].position = s;
			}
		}
	}

	void ProcessMovement(float dt)
	{
		bool l1 = false, l2 = false;

		if (SAS)
		{
			l2 = true;
			l1 = true;
			if (!TaskInProgress)
			{
				SASTaskAngle1 = SASangle;
				SASTaskAngle2 = SASangle + (rotation - SASangle) * 0.5f;

				SASTaskStage = ((rotation - SASTaskAngle2) / pi) > 0.0f;
				TaskInProgress = true;
			}

			if (TaskInProgress)
			{

				glm::vec2 targetrotpoint = Rotate(glm::vec2(0.0f, 1.0f), SASTaskAngle2);

				float stage = get_relative_angle_between_points(UpVector, targetrotpoint) / (pi*1.5f);
				
					
				r1.throtle = stage * RotationSpeedMult;
				r2.throtle = -stage * RotationSpeedMult;

				if (SASTaskStage && rotationVelocity > 0.0f ||
					!SASTaskStage && !rotationVelocity > 0.0f)
					TaskInProgress = false;



				if (rotation - SASTaskAngle1 <0.1f && rotation - SASTaskAngle1 > -0.1f)
					TaskInProgress = false;
			}



			if (r1.throtle > maxthrotle * 0.5f)r1.throtle = maxthrotle * 0.5f;
			if (r2.throtle > maxthrotle * 0.5f)r2.throtle = maxthrotle * 0.5f;
			if (r2.throtle < 0.0f)r2.throtle = 0.0f;
			if (r1.throtle < 0.0f)r1.throtle = 0.0f;



			if (!TranformTaskInProgress)
			{
				SASTaskPoint = SASpoint;
				SASTaskBeginPoint = body.position;
				SASTransformVelocity = (SASpoint.x - body.position.x) > 0.0f;

				TranformTaskInProgress = true;
			}
			if (TranformTaskInProgress)
			{


				float stagex = abs(body.position.x - SASTaskPoint.x) / 1000;
				float stagey = abs(body.position.y - SASTaskPoint.y) / 1000;
				stagex += (body.velocity.x * (signbit(SASTaskPoint.x - body.position.x) * 2.0f - 1.0f)) * 0.00125f;
				if (stagex > 1.0f)stagex = 1.0f;
				if (stagex < -1.0f)stagex = -1.0f;

				stagey += (body.velocity.y * (signbit(SASTaskPoint.y - body.position.y) * 2.0f - 1.0f)) * 0.00125f;

				if (stagey > 1.0f)stagey = 1.0f;
				if (stagey < -1.0f)stagey = -1.0f;



				if (SASTaskPoint.x > body.position.x)
				{
					SASangle = -pi * rotationAngleMult * stagex;
				}
				else
				{
					SASangle = pi * rotationAngleMult * stagex;
				}

				glm::vec2 rotvec = Rotate(glm::vec2(1.0f, 0.0f), rotation + pi * 0.5f);

				float dot = DOT(rotvec, Normalize(SASTaskPoint - body.position));

				throtle[0] = stagey * 1.0f + staticForce + dot * 0.125f;
				throtle[1] = stagey * 1.0f + staticForce + dot * 0.125f;
				if (body.position.y > SASTaskPoint.y)
				{
					throtle[0] = staticForce;
					throtle[1] = staticForce;
				}

				if (length(body.position - SASTaskPoint) > length(SASTaskBeginPoint - SASTaskPoint) ||
					body.position.y > SASTaskPoint.y && body.velocity.y > 0.0f ||
					body.position.y < SASTaskPoint.y && body.velocity.y < 0.0f
					)
				{
					TaskInProgress = false;
					TranformTaskInProgress = false;
				}
				if (sqrlength(body.position - SASpoint) < 100000.0f)
				{

					body.velocity *= NearTargetFriction;
					r1.body[0].velocity *= NearTargetFriction;
					r1.body[1].velocity *= NearTargetFriction;
					r2.body[0].velocity *= NearTargetFriction;
					r2.body[1].velocity *= NearTargetFriction;
				}
			}

			if (throtle[0] > 1.0f)throtle[0] = 1.0f;
			if (throtle[1] > 1.0f)throtle[1] = 1.0f;
			if (throtle[1] < 0.0f)throtle[1] = 0.0f;
			if (throtle[0] < 0.0f)throtle[0] = 0.0f;

			r1.throtle += throtle[0] * 0.75f;
			r2.throtle += throtle[1] * 0.75f;

			if (r1.throtle > maxthrotle)r1.throtle = maxthrotle;
			if (r2.throtle > maxthrotle)r2.throtle = maxthrotle;
			if (r2.throtle < 0.0f)r2.throtle = 0.0f;
			if (r1.throtle < 0.0f)r1.throtle = 0.0f;





		}
		else if (!enemy)
		{
			if (keys[GLFW_KEY_UP] || keys[GLFW_KEY_W])
			{
				r2.throtle += dt * 10.0f;
				l2 = true;

				l1 = true;
				r1.throtle += dt * 10.0f;
			}
			else
			{
				if (keys[GLFW_KEY_RIGHT] || keys[GLFW_KEY_D])
				{
					l1 = true;
					r1.throtle += dt * 10.0f;
				}
				else
					r1.throtle -= dt * 10.0f;
				if (keys[GLFW_KEY_LEFT] || keys[GLFW_KEY_A])
				{
					r2.throtle += dt * 10.0f;
					l2 = true;
				}
				else
					r2.throtle -= dt * 10.0f;
			}
			if (r1.throtle > maxthrotle)r1.throtle = maxthrotle;
			if (r2.throtle > maxthrotle)r2.throtle = maxthrotle;
			if (r2.throtle < 0.0f)r2.throtle = 0.0f;
			if (r1.throtle < 0.0f)r1.throtle = 0.0f;
		

			if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
			{
				r2.throtle = -maxthrotle * 0.35f;
				r1.throtle = -maxthrotle * 0.35f;
			}

		}

		enginelag = hp / maxhp;

		r1.throtle = r1.throtle + ((rand() % 100) / 100.0f * r1.throtle * 2.0f - r1.throtle) * (1.0f - enginelag);
		r2.throtle = r2.throtle + ((rand() % 100) / 100.0f * r2.throtle * 2.0f - r2.throtle) * (1.0f - enginelag);
		
		if (r1.throtle > 0.0f || keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
		{

			glm::vec2 dir = Normalize(r1.body[1].position - r1.body[0].position);

			float thr = r1.throtle;

			if (thr > 1.0f)
				thr = 1.0f;
			EngineSmoke.Spawn(r1.body[1].position + dir * r1.body[0].r, dir * 5000.0f * thr,1);
			
		}
		if (r2.throtle > 0.0f || keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
		{
			glm::vec2 dir = Normalize(r2.body[1].position - r2.body[0].position);
			
			float thr = r2.throtle;

			if (thr > 1.0f)
				thr = 1.0f;

			EngineSmoke.Spawn(r2.body[1].position + dir * r2.body[0].r, dir * 5000.0f * thr, 1);



		}
		
	}

	void Process(float dt)
	{
		if(!enemy)
		{
			if (!keys[GLFW_KEY_R] && JustPressedR) JustReleasedR = true;
			else JustReleasedR = false;

			if (keys[GLFW_KEY_R]) JustPressedR = true;
			else JustPressedR = false;



			if(JustReleasedR) SAS = !SAS;
		}

		if (body.color.a != 0.0f)
		{
			ProcessPhysics(dt);
			Draw();
		}
		SetSourceGain(&source, 1.0f);

		SetSourcePosition(&source, glm::vec3(body.position, 1.0f));

		if (dyingtime > 2.0f &&!sleep)
		{
			ProcessMovement(dt);
		}
		else
		{
			r1.throtle = 0.0f;
			r2.throtle = 0.0f;
		}
		
		if (hp > 0.0f)
		{

			if (length(body.velocity) < 200.0f && r1.throtle == 0.0f && r2.throtle == 0.0f)
				regentimer -= dt;
			else
				regentimer = 3.0f;

			if (regentimer < 0.0f)
			{
				if (hp < maxhp)
				{
					hp += dt;
					
					Sparks.SpawnInCube(body.position - glm::vec2(RodLength[0] * 0.5f, 0.0f), glm::vec2(r1.body[0].r * 2, r1.body[0].r * 4), 3);
					Sparks.SpawnInCube(body.position + glm::vec2(RodLength[0] * 0.5f, 0.0f), glm::vec2(r1.body[0].r * 2, r1.body[0].r * 4), 3);
					Sparks.SpawnInCircle(body.position, body.r, 2);
					
					bulletColisionPm.SpawnInCube(body.position - glm::vec2(RodLength[0] * 0.5f, 0.0f), glm::vec2(r1.body[0].r * 2, r1.body[0].r * 4), 1);
					bulletColisionPm.SpawnInCube(body.position + glm::vec2(RodLength[0] * 0.5f, 0.0f), glm::vec2(r1.body[0].r * 2, r1.body[0].r * 4), 1);
					bulletColisionPm.SpawnInCircle(body.position, body.r, 1);

					DrawLight(body.position - glm::vec2(RodLength[0] * 0.5f + (rand() % 100 - 50) * 0.02f * r1.body[0].r, (rand() % 100 - 50) * 0.02f * r1.body[0].r * 6.0f),
						glm::vec2((rand() % 100 - 50) * 10.02f), glm::vec4(0.0f, 100.0f, 100.0f, 1.0f));

					DrawLight(body.position + glm::vec2(RodLength[0] * 0.5f + (rand() % 100 - 50) * 0.02f * r1.body[0].r, (rand() % 100 - 50) * 0.02f * r1.body[0].r * 6.0f),
						glm::vec2((rand() % 100 - 50) * 10.02f), glm::vec4(0.0f, 100.0f, 100.0f, 1.0f));

					DrawLight(body.position + glm::vec2((rand() % 100 - 50) * 0.02f * body.r, (rand() % 100 - 50) * 0.02f * body.r),
						glm::vec2((rand() % 100 - 50) * 10.02f), glm::vec4(0.0f, 100.0f, 100.0f, 1.0f));
				}
				else hp = maxhp;
			}



			if (hp != maxhp)
			{
				timers[0] -= dt;
				timers[1] -= dt;
				timers[2] -= dt;
			}

			float stage = hp / maxhp;

			if (timers[0] <= 0.0f)
			{
				timers[0] = rand() % 100 * 0.01f * stage + 1.0f * stage;
				if (timers[0] < 0.1f) timers[0] = 0.1f;
				Sparks.SpawnInCircle(body.position, body.r, 5);
			}

			if (timers[1] <= 0.0f)
			{
				timers[1] = rand() % 100 * 0.01f * stage + 1.0f * stage;
				if (timers[1] < 0.1f) timers[1] = 0.1f;
				Sparks.SpawnInCube(body.position - glm::vec2(RodLength[0] * 0.5f, 0.0f), glm::vec2(r1.body[0].r * 2, r1.body[0].r * 4), 3);
			}

			if (timers[2] <= 0.0f)
			{
				timers[2] = rand() % 100 * 0.01f * stage + 1.0f * stage;
				if (timers[2] < 0.1f) timers[2] = 0.1f;
				Sparks.SpawnInCube(body.position + glm::vec2(RodLength[0] * 0.5f, 0.0f), glm::vec2(r1.body[0].r * 2, r1.body[0].r * 4), 3);
			}



			for (int i = 0; i < Map.cubes.size(); i++)
				CastRayToQuad(&RayCast, Map.cubes[i]);

			DrawLine(RayCast.position, RayCast.ClosestPoint,1.0f,glm::vec4(10.0f,0.0f,0.0f,1.0f));

			if(!enemy && sqrlength(MousePosition - body.position)>100.0f)
				gun.TargetAngle = get_angle_between_points(MousePosition, body.position);
			else if(TargetBall!=NULL)
				gun.TargetAngle = get_angle_between_points(TargetBall->position, body.position);
			
			gun.deactivated = Safety;
			t -= dt;

			if (buttons[GLFW_MOUSE_BUTTON_1] && t <= 0.0f && !enemy && !Safety)
			{

				gun.recoil = 600.0f;
				gun.dmg = damage;
				gun.Shot();
				t = shotspeed;
			}
			else if(enemy && t <= 0.0f && !Safety)
			{

				gun.recoil = 600.0f;
				gun.dmg = damage;
				gun.Shot();
				t = shotspeed * 3.0f;
			}
		}
		else 
		{
			dyingtime -= dt;
			gun.speed = 0.0f;
			gun.RotationalFriction = 0.0f;

			if (dyingtime > 1.3f && dyingtime < 1.5f)
			{
				float stage = abs(((dyingtime - 1.3f) * 2.0f - 0.4f) / 0.4f);
				DrawLight(body.position, glm::vec2(1000 * (1.0f - stage)), glm::vec4(100.0f, 20.0f, 10.0f, 1.0f));
				DrawLight(r1.body[0].position, glm::vec2(1000 * (1.0f - stage)), glm::vec4(100.0f, 20.0f, 10.0f, 1.0f));
				DrawLight(r2.body[0].position, glm::vec2(1000 * (1.0f - stage)), glm::vec4(100.0f, 20.0f, 10.0f, 1.0f));
			}
			if (dyingtime > 1.5f) 
			{
				bulletColisionPm.Spawn(body.position, 1);
				bulletColisionPm.Spawn(r1.body[0].position, 1);
				bulletColisionPm.Spawn(r1.body[1].position, 1);
				bulletColisionPm.Spawn(r2.body[0].position, 1);
				bulletColisionPm.Spawn(r2.body[1].position, 1);
			}
			else if (body.color.a != 0.0f)
			{
				body.color.a = 0.0f;
				Sparks.Spawn(body.position, 15);
				Sparks.Spawn(r1.body[0].position, 15);
				Sparks.Spawn(r1.body[1].position, 15);
				Sparks.Spawn(r2.body[0].position, 15);
				Sparks.Spawn(r2.body[1].position, 15);

				bulletColisionPm.Spawn(body.position, 15);
				bulletColisionPm.Spawn(r1.body[0].position, 15);
				bulletColisionPm.Spawn(r1.body[1].position, 15);
				bulletColisionPm.Spawn(r2.body[0].position, 15);
				bulletColisionPm.Spawn(r2.body[1].position, 15);

				SetSourceLooping(&r1.source, false);
				SetSourceLooping(&r2.source, false);
				SwapSourceSound(&r1.source, &HeavyHit);
				SwapSourceSound(&r2.source, &HeavyHit);
				SwapSourceSound(&source, &HeavyHit);


				SetSourceRefDist(&r1.source, 0.5f);
				SetSourceRefDist(&r2.source, 0.5f);
				SetSourceRefDist(&source, 0.5f);


				SetSourceMaxDistance(&r1.source, 4.0f);
				SetSourceMaxDistance(&r2.source, 4.0f);
				SetSourceMaxDistance(&source, 4.0f);


				SetSourcePitch(&r1.source, 0.7f);
				SetSourcePitch(&r2.source, 0.7f);
				SetSourcePitch(&source, 0.7f);


				SetSourceGain(&r1.source, 1.5f);
				SetSourceGain(&r2.source, 1.5f);
				SetSourceGain(&source, 1.5f);


				SetSourcePosition(&r1.source,glm::vec3(r2.body[1].position,0.0f));
				SetSourcePosition(&r2.source,glm::vec3(r1.body[1].position,0.0f));
				SetSourcePosition(&source,glm::vec3(body.position,0.0f));


				PlaySource(&r1.source);
				PlaySource(&r2.source);
				PlaySource(&source);

			}
		}

		RayCast.position = gun.body[1].position;
		RayCast.direction = gun.body[1].position - gun.body[0].position;
		RayCast.length = 3000;
		RayCast.Steps = 100;
		RayCast.normalize();
		RayCast.Update();
	}
	void Draw()
	{
		if (dyingtime > 1.5f)
		{
			DrawCircle(body, body.color, true,BallNormalMapTexture,1);
			if (hp > 0.0f)
			{
				DrawLine(body.position, r1.body[0].position, body.r * 0.2f, body.color, true, CubeNormalMapTexture, 0);
				DrawLine(body.position, r1.body[1].position, body.r * 0.2f, body.color, true, CubeNormalMapTexture, 0);
				DrawLine(body.position, r2.body[0].position, body.r * 0.2f, body.color, true, CubeNormalMapTexture, 0);
				DrawLine(body.position, r2.body[1].position, body.r * 0.2f, body.color, true, CubeNormalMapTexture, 0);
			}

			if (DrawNavigation)
			{
				/*DrawCircle(body.position + Rotate(glm::vec2(1.0f, 0.0f), SASTaskAngle1 + pi * 0.5f) * 100.0f, 25, glm::vec4(10.0f, 0.0f, 0.0f, 1.0f));
				DrawCircle(body.position + Rotate(glm::vec2(1.0f, 0.0f), SASTaskAngle2 + pi * 0.5f) * 100.0f, 25, glm::vec4(0.0f, 10.0f, 0.0f, 1.0f));
				DrawCircle(body.position + Rotate(glm::vec2(1.0f, 0.0f), SASangle + pi * 0.5f) * 200.0f, 25, glm::vec4(0.0f, 0.0f, 10.0f, 1.0f));
				DrawCircle(body.position + Rotate(glm::vec2(1.0f, 0.0f), rotation + pi * 0.5f) * 100.0f, 25, glm::vec4(0.0f, 10.0f, 10.0f, 1.0f));*/

				DrawCircle(SASTaskPoint, 50, glm::vec4(10.0f, 1.0f, 1.0f, 1.0f));
			}

			r1.body[0].color = body.color;
			r2.body[0].color = body.color;

			r1.Draw();
			r2.Draw();
			gun.Draw(2);

		}
	}
	~Drone()
	{
		DeleteSource(&source);
		r1.~RocketEngine();
		r2.~RocketEngine();
	}

};