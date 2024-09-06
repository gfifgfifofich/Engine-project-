#version 330 core
in vec2 TexCoords;
out vec4 FragValue;
uniform int BallsCount = 1;
uniform int BallsCount1 = 1;
uniform int BallsCount2 = 1;
uniform int BallsCount3 = 1;
uniform int BallsCount4 = 1;
uniform float delta = 0.017f;
uniform float Radius = 5.0f;
uniform vec2 force = vec2(0.0f);

uniform sampler2D Balls; 
uniform sampler2D Balls1; 
uniform sampler2D Balls2; 
uniform sampler2D Balls3; 
uniform sampler2D Balls4; 
float invbc = 0.1f; 
float invbc1 = 0.1f; 
float invbc2 = 0.1f; 
float invbc3 = 0.1f; 
float invbc4 = 0.1f; 
float DOT(vec2 v1, vec2 v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}
float sqrlength(vec2 p)
{
	return (p.x*p.x + p.y*p.y);
}

vec4 GetBall(int i)
{
	return texture(Balls,vec2( (float(i+0.2f) * invbc),0.0f));
}
vec4 GetBall1(int i)
{
	return texture(Balls1,vec2( (float(i+0.2f) * invbc1),0.0f));
}
vec4 GetBall2(int i)
{
	return texture(Balls2,vec2( (float(i+0.2f) * invbc2),0.0f));
}
vec4 GetBall3(int i)
{
	return texture(Balls3,vec2( (float(i+0.2f) * invbc3),0.0f));
}
vec4 GetBall4(int i)
{
	return texture(Balls4,vec2( (float(i+0.2f) * invbc4),0.0f));
}


vec4 Run()
{
	

	vec4 b1 = texture(Balls, TexCoords);
	vec4 buff = b1;
	invbc = 1.0f / BallsCount;
	invbc1 = 1.0f / BallsCount1;
	invbc2 = 1.0f / BallsCount2;
	invbc3 = 1.0f / BallsCount3;
	invbc4 = 1.0f / BallsCount4;
	for(int i=0;i<BallsCount;i++)
	{
		vec4 b2 = GetBall(i);
		vec2 dif = vec2(b2.x - buff.x,b2.y - buff.y);
		if ((dif.x * dif.x + dif.y * dif.y) < (Radius + Radius) * (Radius + Radius))
		{


			float dist = length(dif);
			float distancedifference = (Radius + Radius) - dist;
			if(sqrlength(buff.xy - b2.xy)< 0.001f)
				continue;
			if(dist<0.00000001f)
			{
				b1.xy += vec2(TexCoords); 
				continue;
			}

			vec2 n2 = dif/dist;
			vec2 n1 = -n2;
			vec2 CollisionLine = vec2(-n1.y, n1.x);



			float energy1 = DOT(buff.zw, n2);
			float energy2 = DOT(b2.zw, n2);


			b1.xy = b1.xy + n1.xy * distancedifference * 0.5f;
			b1.zw -= n1 * energy2 + n2 * energy1;
		}

	}
    for(int i=0;i<BallsCount1;i++)
	{
		vec4 b2 = GetBall1(i);
		vec2 dif = vec2(b2.x - buff.x,b2.y - buff.y);
		if ((dif.x * dif.x + dif.y * dif.y) < (Radius + Radius) * (Radius + Radius))
		{


			float dist = length(dif);
			float distancedifference = (Radius + Radius) - dist;
			if(sqrlength(buff.xy - b2.xy)< 0.001f)
				continue;
			if(dist<0.00000001f)
			{
				b1.xy += vec2(TexCoords); 
				continue;
			}

			vec2 n2 = dif/dist;
			vec2 n1 = -n2;
			vec2 CollisionLine = vec2(-n1.y, n1.x);



			float energy1 = DOT(buff.zw, n2);
			float energy2 = DOT(b2.zw, n2);


			b1.xy = b1.xy + n1.xy * distancedifference * 0.5f;
			b1.zw -= n1 * energy2 + n2 * energy1;
		}

	}
    for(int i=0;i<BallsCount2;i++)
	{
		vec4 b2 = GetBall2(i);
		vec2 dif = vec2(b2.x - buff.x,b2.y - buff.y);
		if ((dif.x * dif.x + dif.y * dif.y) < (Radius + Radius) * (Radius + Radius))
		{


			float dist = length(dif);
			float distancedifference = (Radius + Radius) - dist;
			if(sqrlength(buff.xy - b2.xy)< 0.001f)
				continue;
			if(dist<0.00000001f)
			{
				b1.xy += vec2(TexCoords); 
				continue;
			}

			vec2 n2 = dif/dist;
			vec2 n1 = -n2;
			vec2 CollisionLine = vec2(-n1.y, n1.x);



			float energy1 = DOT(buff.zw, n2);
			float energy2 = DOT(b2.zw, n2);


			b1.xy = b1.xy + n1.xy * distancedifference * 0.5f;
			b1.zw -= n1 * energy2 + n2 * energy1;
		}

	}
    for(int i=0;i<BallsCount3;i++)
	{
		vec4 b2 = GetBall3(i);
		vec2 dif = vec2(b2.x - buff.x,b2.y - buff.y);
		if ((dif.x * dif.x + dif.y * dif.y) < (Radius + Radius) * (Radius + Radius))
		{


			float dist = length(dif);
			float distancedifference = (Radius + Radius) - dist;
			if(sqrlength(buff.xy - b2.xy)< 0.001f)
				continue;
			if(dist<0.00000001f)
			{
				b1.xy += vec2(TexCoords); 
				continue;
			}

			vec2 n2 = dif/dist;
			vec2 n1 = -n2;
			vec2 CollisionLine = vec2(-n1.y, n1.x);



			float energy1 = DOT(buff.zw, n2);
			float energy2 = DOT(b2.zw, n2);


			b1.xy = b1.xy + n1.xy * distancedifference * 0.5f;
			b1.zw -= n1 * energy2 + n2 * energy1;
		}

	}
    for(int i=0;i<BallsCount4;i++)
	{
		vec4 b2 = GetBall4(i);
		vec2 dif = vec2(b2.x - buff.x,b2.y - buff.y);
		if ((dif.x * dif.x + dif.y * dif.y) < (Radius + Radius) * (Radius + Radius))
		{


			float dist = length(dif);
			float distancedifference = (Radius + Radius) - dist;
			if(sqrlength(buff.xy - b2.xy)< 0.001f)
				continue;
			if(dist<0.00000001f)
			{
				b1.xy += vec2(TexCoords); 
				continue;
			}

			vec2 n2 = dif/dist;
			vec2 n1 = -n2;
			vec2 CollisionLine = vec2(-n1.y, n1.x);



			float energy1 = DOT(buff.zw, n2);
			float energy2 = DOT(b2.zw, n2);


			b1.xy = b1.xy + n1.xy * distancedifference * 0.5f;
			b1.zw -= n1 * energy2 + n2 * energy1;
		}

	}
	b1.z += force.x * delta;  // velocity += force
	b1.w += force.y * delta;  // velocity += force
	b1.x += b1.z * delta;//pos+=velocity
	b1.y += b1.w * delta;//pos+=velocity
	float roughness = 0.1f;

	
	if(b1.x>2000.0f)
	{
		b1.x = 2000.0f;
		b1.z *= -roughness;
		b1.w *= roughness;
	}
	if(b1.x<10.0f)
	{
		b1.x = 10.0f;
		b1.z *= -roughness;
		b1.w *= roughness;
	}
	if(b1.y>2000.0f)
	{
		b1.y = 2000.0f;
		b1.w *= -roughness;
		b1.z *= roughness;
	}
	if(b1.y<10.0f)
	{
		b1.y = 10.0f;
		b1.w *= -roughness;
		b1.z *= roughness;
	}
	return b1;

}

void main()
{
	//FragValue = texture(weights,vec2( (gl_FragCoord.y / inSize),(gl_FragCoord.x / outSize) )).r;
	//FragValue = GetIn(int(gl_FragCoord.x));
	//FragValue = GetWeight(int(gl_FragCoord.x));
	//FragValue = GetBias(int(gl_FragCoord.x));
	FragValue = Run();
}