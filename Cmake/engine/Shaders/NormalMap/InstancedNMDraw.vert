#version 330 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in float angle;
layout (location = 2) in vec4 aPosScale;


out vec3 TexCoords;

uniform float aspect;
uniform bool flipY = false;
void main()
{
	vec4 pos = vec4(aPos.xy,0.0f,1.0f);

    pos.xy = pos.xy * aPosScale.zw;


    float Sin = sin(angle);
    float Cos = cos(angle);
    pos.xy = vec2(Cos * pos.x - Sin * pos.y, Sin * pos.x + Cos * pos.y);

    pos.xy += aPosScale.xy;

    pos.x *=aspect;
	gl_Position =  pos;
	TexCoords.z = angle;
	if(!flipY)
	{
		TexCoords.x = aPos.z;
		TexCoords.y = aPos.w;
	}
	else
	{
		TexCoords.x = aPos.z;
		TexCoords.y = 1.0f-aPos.w;
	}
}  