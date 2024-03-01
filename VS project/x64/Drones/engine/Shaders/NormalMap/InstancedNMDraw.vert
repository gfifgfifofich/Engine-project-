#version 330 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in float angle;
layout (location = 2) in mat4 aMat;


out vec3 TexCoords;

uniform vec2 scr;
uniform bool flipY = false;
void main()
{
	vec4 pos = aMat*vec4(aPos.xy,0.0f,1.0f);
	pos.x /=scr.x;
	pos.x *=scr.y;
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