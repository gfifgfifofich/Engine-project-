#pragma once
class Human
{
public:
	ball body[3];

	ball leg1[2];
	ball leg2[2];

	glm::vec2 Force = { 0.0f,0.0f };
	glm::vec2 LegForce = { 0.0f,0.0f };

	glm::vec4 Color = glm::vec4(1.0f);

	float KnockOutTime = 0.0f;
	bool ControlledKnockOut = false;

	float leglength[2] = { 150.0f, 150.0f };
	float leglength2[2] = { 150.0f, 150.0f };
	float lengthBetweenKnees = 50.0f;

	float SpringForces[3] = { 100.0f ,1000.0f ,1000.0f };
	float SpringForcesBetweenLegs[2] = { 30.0f,300.0f};

	float legrotation = 0.0f;

	float stepSize = 80.0f;
	float stepXMult = 2.0f;

	glm::vec2 leg1TargetPos = { 0.0f,0.0f };
	glm::vec2 leg2TargetPos = { 0.0f,0.0f };

	glm::vec2 LegOffset = { 0.0f,250.0f };

	int EngineParticleEmiter1;
	int EngineParticleEmiter2;
	float throtle1 = 1.0f;
	float throtle2 = 1.0f;

	bool invertLegPos = false;
	float RocketForce = 10000.0f;


	void Ready(glm::vec2 position,float r)
	{
		EngineParticleEmiter1 = EngineSmoke.AddPointEmiter({ 0.0f,0.0f }, { 5000.0f,0.0f }, 1, 0.001);
		EngineParticleEmiter2 = EngineSmoke.AddPointEmiter({ 0.0f,0.0f }, { 5000.0f,0.0f }, 1, 0.001);

		body[0].position = position + glm::vec2(0.0f,0.0f);
		body[1].position = position + glm::vec2(1.0f,r*2.0f);
		body[2].position = position + glm::vec2(0.0f, r * 4.0f);

		leg1[0].position = position + glm::vec2(r, -r)*2.0f;
		leg1[1].position = position + glm::vec2(r, -r * 2.0f) * 2.0f;

		leg2[0].position = position + glm::vec2(-r, -r) * 2.0f;
		leg2[1].position = position + glm::vec2(-r, -r * 2.0f) * 2.0f;

		body[0].r = r;
		body[1].r = r;
		body[2].r = r;

		body[0].roughness = 0.0f;
		body[0].bounciness = 0.0f;
		body[0].FixedRotation = true;
		body[1].roughness = 0.0f;
		body[1].bounciness = 0.0f;
		body[1].FixedRotation = true;
		body[2].roughness = 0.0f;
		body[2].bounciness = 0.0f;
		body[2].FixedRotation = true;



		body[0].mass = 1.25f;
		body[1].mass = 1.25f;
		body[2].mass = 1.25f;



		leg1[0].roughness = 0.0f;
		leg1[0].bounciness = 0.0f;
		leg1[0].FixedRotation = true;
		leg1[0].r = r*0.5f;

		leg1[1].roughness = 0.0f;
		leg1[1].bounciness = 0.0f;
		leg1[1].FixedRotation = true;
		leg1[1].r = r * 0.5f;

		leg2[0].roughness = 0.0f;
		leg2[0].bounciness = 0.0f;
		leg2[0].FixedRotation = true;
		leg2[0].r = r * 0.5f;

		leg2[1].roughness = 0.0f;
		leg2[1].bounciness = 0.0f;
		leg2[1].FixedRotation = true;
		leg2[1].r = r * 0.5f;
	}

	void ProcessPhysics(float dt)
	{


		KnockOutTime -= dt;
		if (KnockOutTime < 0.0f && !ControlledKnockOut)
		{
			KnockOutTime = 0.0f;
			point p;
			p.position = body[1].position - glm::vec2(0.0f, body[0].r * 2.0f);
			SpringBallToPoint(&body[0], &p, 0, 150.0f,10.0f);
			p.position = body[1].position + glm::vec2(0.0f, body[0].r * 2.0f);
			SpringBallToPoint(&body[2], &p, 0, 150.0f,10.0f);

			//SpringBetweenBalls(&body[1], &leg1[0], leglength2[0], SpringForces[1], 20.7f);
			


			//SpringBetweenBalls(&body[1], &leg2[0], leglength2[1], SpringForces[1], 20.7f);

			/*

			SpringBetweenBalls(&leg1[0], &leg2[0], lengthBetweenKnees, SpringForcesBetweenLegs[1], 20.7f);
			SpringBetweenBalls(&leg1[1], &leg2[1], lengthBetweenKnees, SpringForcesBetweenLegs[1], 20.7f);
			*/


			glm::vec2 unitvec = glm::vec2(1.0f, 0.0f);

			glm::vec2 avg = (body[0].position + body[1].position + body[2].position) / 3.0f;

			leg1TargetPos = avg - LegOffset - Rotate(unitvec, legrotation) * stepSize * glm::vec2(stepXMult, 1.0f);
			leg2TargetPos =avg - LegOffset + Rotate(unitvec, legrotation) * stepSize * glm::vec2(stepXMult, 1.0f);

			p.position = leg1TargetPos;
			SpringBallToPoint(&leg1[1], &p, 0, 500.0f, 20.7f);
			p.position = leg2TargetPos;
			SpringBallToPoint(&leg2[1], &p, 0, 500.0f, 20.7f);

			LegForce = p.Force*0.3f;

			SpringBetweenBalls(&body[1], &leg1[0], 10, SpringForces[0], 10.7f);
			SpringBetweenBalls(&body[1], &leg2[0], 10, SpringForces[0], 10.7f);

			//SpringBetweenBalls(&body[1], &leg1[1], length(body[1].position - leg1TargetPos), SpringForces[0], 10.7f);
			//SpringBetweenBalls(&body[1], &leg2[1], length(body[1].position - leg2TargetPos), SpringForces[0], 10.7f);

			//SpringBetweenBalls(&body[2], &leg1[1], length(body[2].position - leg1TargetPos), SpringForces[0], 10.7f);
			//SpringBetweenBalls(&body[2], &leg2[1], length(body[2].position - leg2TargetPos), SpringForces[0], 10.7f);

		}
		else
		{
			LegForce = glm::vec2(0.0f);
		}

		Strut(&leg1[0], &leg1[1], body[0].r * 2.0f);
		Strut(&body[0], &leg1[0], body[0].r * 2.0f);

		Strut(&leg2[0], &leg2[1], body[0].r * 2.0f);
		Strut(&body[0], &leg2[0], body[0].r * 2.0f);
		

		body[0].Process(dt);
		body[1].Process(dt);
		body[2].Process(dt);

		leg1[0].Process(dt);
		leg1[1].Process(dt);

		leg2[0].Process(dt);
		leg2[1].Process(dt);


		body[0].Force = Force;
		body[1].Force = Force;
		body[2].Force = Force;
		
		body[0].Force += LegForce;
		body[1].Force += LegForce;
		body[2].Force += LegForce;

		leg1[0].Force = Force;
		leg1[1].Force = Force;

		leg2[0].Force = Force;
		leg2[1].Force = Force;

		Strut(&body[0], &body[1], body[0].r * 2.0f);
		Strut(&body[1], &body[2], body[0].r * 2.0f);
		SpringBetweenBalls(&body[0], &body[2], body[0].r * 5.0f, 300.0f, 10.7f);
	}

	void Process(float dt)
	{

		Draw(true);
		ProcessPhysics(dt);


		bool l1 = false , l2 = false;
		if (keys[GLFW_KEY_Q])
			if (!invertLegPos) l1 = true;
			else l2 = true;
		if (keys[GLFW_KEY_E])
			if (!invertLegPos) l2 = true;
			else l1 = true;

		if (l1)
		{
			glm::vec2 dir = Normalize(leg1[1].position - leg1[0].position);

			EngineSmoke.EmitionPoints[EngineParticleEmiter1].position = leg1[1].position + dir * leg1[0].r;
			EngineSmoke.EmitionPoints[EngineParticleEmiter1].velocity = dir * 5000.0f * throtle1;
			//EngineSmoke.EmitionPoints[EngineParticleEmiter1].tick = 1.0f - throtle1;
			EngineSmoke.EmitionPoints[EngineParticleEmiter1].amount = 1;
			DrawLight(leg1[1].position + dir * leg1[0].r, { 1000 * throtle1,1000 * throtle1 }, glm::vec4(100.0f, 20.0f, 10.0f, 0.5f + throtle1 + (rand() % 100 - 50) * 0.01f));

			leg1[1].Force += RocketForce * -dir * throtle1;
		}
		else
			EngineSmoke.EmitionPoints[EngineParticleEmiter1].amount = 0;

		if (l2)
		{
			glm::vec2 dir = Normalize(leg2[1].position - leg2[0].position);

			EngineSmoke.EmitionPoints[EngineParticleEmiter2].position = leg2[1].position + dir * leg2[0].r;
			EngineSmoke.EmitionPoints[EngineParticleEmiter2].velocity = dir * 5000.0f * throtle2;
			//EngineSmoke.EmitionPoints[EngineParticleEmiter2].tick = 1.0f - throtle2;
			EngineSmoke.EmitionPoints[EngineParticleEmiter2].amount = 1;
			DrawLight(leg2[1].position + dir * leg2[0].r, { 1000 * throtle2,1000 * throtle2 }, glm::vec4(100.0f, 20.0f, 10.0f, 0.5f+throtle2 + (rand() % 100 - 50) * 0.01f));

			leg2[1].Force += RocketForce * -dir * throtle2;
		}
		else 
		{
			EngineSmoke.EmitionPoints[EngineParticleEmiter2].amount = 0;
		}
		if (keys[GLFW_KEY_SPACE]) ControlledKnockOut = true;
		else ControlledKnockOut = false;


		if (legrotation < -pi * 2.0f || legrotation > pi * 2.0) legrotation = 0;

		if (keys[GLFW_KEY_A]) legrotation += delta * 4.0f;
		else if (keys[GLFW_KEY_D]) legrotation -= delta * 4.0f;
		else
		{
			if (leg1[1].position.x < leg1[2].position.x)
				legrotation = 0;
			else
				legrotation = pi; 
		}

		if (leg1[1].position.x < leg1[2].position.x)
			invertLegPos = false;
		else
			invertLegPos = true;



	}
	void Draw(bool DrawSprings = false)
	{
		DrawLine(body[0].position, body[1].position, body[1].r, glm::vec4(1.0f), true);
		DrawLine(body[1].position, body[2].position, body[2].r, glm::vec4(1.0f), true);

		DrawLine(leg1[1].position, leg1[0].position, leg1[0].r, glm::vec4(1.0f), true);
		DrawLine(body[0].position, leg1[0].position, leg1[0].r, glm::vec4(1.0f), true);

		DrawLine(leg2[1].position, leg2[0].position, leg2[0].r, glm::vec4(1.0f), true);
		DrawLine(body[0].position, leg2[0].position, leg2[0].r, glm::vec4(1.0f), true);

		DrawBall(body[0], Color, Color, true);
		DrawBall(body[1], Color, Color, true);
		DrawBall(body[2], Color, Color, true);
		DrawBall(leg1[0], Color, Color, true);
		DrawBall(leg1[1], Color, Color, true);
		DrawBall(leg2[0], Color, Color, true);
		DrawBall(leg2[1], Color, Color, true);
	}

};