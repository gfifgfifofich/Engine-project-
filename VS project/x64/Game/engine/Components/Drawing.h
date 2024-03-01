#pragma once

glm::vec2 CameraPosition = glm::vec2(0.0f);
glm::vec2 CameraScale = glm::vec2(1.0f);

//QUAD
Shader* TexturedQuadShader;
Shader* FilShader;
Shader* TexturedTriangleShader;
Shader*	AddTexturesShader;

Shader* NormalMapDrawShader;
Shader* LightShader;
Shader* GenNormalMapShader;
Shader* GenLightSphereShader;



unsigned int BallNormalMapTexture;
unsigned int CubeNormalMapTexture;
unsigned int LightSphereTexture;

unsigned int FrameBuffer, ColorBuffer;
unsigned int NormalMapFBO, NormalMapColorBuffer;
unsigned int LightColorFBO, LightColorBuffer;



unsigned int quadVAO, quadVBO,
ScreenVAO, ScreenVBO,
CircleVAO, CircleVBO,
TriangleVAO, TriangleVBO,
TexturedTriangleVAO, TexturedTriangleVBO
;
std::vector <glm::mat4> Circletranslations;
std::vector <glm::vec4> Circlecolors;

float ScaleMultiplyer = 0.043545f*0.05f;

float ScreenAspectRatio = 1.0f;

float ScreenDivisorX = 1.0;
float ScreenDivisorY = 1.0;



struct LightSource
{
	float volume = 0.0f;
	glm::vec2 position = glm::vec2(0.0f);
	glm::vec2 scale = glm::vec2(0.0f);
	glm::vec4 color = glm::vec4(0.0f);
	unsigned int texture = LightSphereTexture;
	int TextureId = 0;
	std::string name = "LightSource";
};
std::vector <LightSource> LightSources;
void DrawLight(glm::vec2 position, glm::vec2 scale,glm::vec4 color, float volume = 0.0f,unsigned int texture = LightSphereTexture)
{
	LightSource ls;
	ls.volume =volume;
	ls.position = position;
	ls.scale = scale;
	ls.color = color;
	ls.texture = texture;
	LightSources.push_back(ls);
}

std::vector <glm::mat4> NormalMapCircleMatrixes;
std::vector <glm::mat4> NormalMapCubeMatrixes;
std::vector <float> NormalMapCircleRotations;
std::vector <float> NormalMapCubeRotations;

void NormalMapDraw(glm::vec2 position,glm::vec2 scale,unsigned int NormalMap= BallNormalMapTexture, float rotation = 0.0f)
{
	if (NormalMap != BallNormalMapTexture && NormalMap != CubeNormalMapTexture) 
	{
		glBindFramebuffer(GL_FRAMEBUFFER, NormalMapFBO);

		position -= CameraPosition;
		glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(
			(position.x) * ScreenDivisorX * CameraScale.x,
			(position.y) * ScreenDivisorY * CameraScale.y,
			0.0f));

		if (rotation != 0)
			trans = glm::rotate(trans, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		trans = glm::scale(trans, glm::vec3(scale.x * CameraScale.x * ScaleMultiplyer, scale.y * CameraScale.y * ScaleMultiplyer, 0.0f));

		NormalMapDrawShader->Use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, NormalMap);
		glUniform1i(glGetUniformLocation(NormalMapDrawShader->Program, "Texture"), 0);


		glUniform2f(glGetUniformLocation(NormalMapDrawShader->Program, "scr"), WIDTH, HEIGHT);
		glUniform1f(glGetUniformLocation(NormalMapDrawShader->Program, "angle"), rotation);
		glUniformMatrix4fv(glGetUniformLocation(NormalMapDrawShader->Program, "transform"), 1, GL_FALSE, glm::value_ptr(trans));

		glBindVertexArray(quadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		if (HDR)
			glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
		else
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	else 
	{
		position -= CameraPosition;
		glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(
			(position.x) * ScreenDivisorX * CameraScale.x,
			(position.y) * ScreenDivisorY * CameraScale.y,
			0.0f));

		trans = glm::scale(trans, glm::vec3(scale.x * CameraScale.x * ScaleMultiplyer, scale.y * CameraScale.y * ScaleMultiplyer, 0.0f));
		if (NormalMap == BallNormalMapTexture)
		{
			NormalMapCircleRotations.push_back(rotation);
			NormalMapCircleMatrixes.push_back(trans);
		}
		else
		{
			NormalMapCubeRotations.push_back(rotation);
			NormalMapCubeMatrixes.push_back(trans);
		}
	}
}
void NormalMapDraw(glm::mat4 trans, unsigned int NormalMap = BallNormalMapTexture, float rotation = 0.0f)
{
	if (NormalMap != BallNormalMapTexture && NormalMap != CubeNormalMapTexture)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, NormalMapFBO);


		NormalMapDrawShader->Use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, NormalMap);
		glUniform1i(glGetUniformLocation(NormalMapDrawShader->Program, "Texture"), 0);


		glUniform2f(glGetUniformLocation(NormalMapDrawShader->Program, "scr"), WIDTH, HEIGHT);
		glUniform1f(glGetUniformLocation(NormalMapDrawShader->Program, "angle"), rotation);
		glUniformMatrix4fv(glGetUniformLocation(NormalMapDrawShader->Program, "transform"), 1, GL_FALSE, glm::value_ptr(trans));

		glBindVertexArray(quadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		if (HDR)
			glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
		else
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	else
	{
		if (NormalMap == BallNormalMapTexture)
		{
			NormalMapCircleRotations.push_back(rotation);
			NormalMapCircleMatrixes.push_back(trans);
		}
		else
		{
			NormalMapCubeRotations.push_back(rotation);
			NormalMapCubeMatrixes.push_back(trans);
		}
	}
}
void NormalMapDrawTriangle(
	glm::vec2 p1,
	glm::vec2 p2,
	glm::vec2 p3,
	unsigned int NormalMap,
	glm::vec2 texcoord1 = glm::vec2(0.0f, 1.0f),
	glm::vec2 texcoord2 = glm::vec2(0.5f, 0.0f),
	glm::vec2 texcoord3 = glm::vec2(1.0f, 1.0f)
)
{

	glBindFramebuffer(GL_FRAMEBUFFER, NormalMapFBO);
	TexturedTriangleShader->Use();
	glBindVertexArray(TexturedTriangleVAO);
	float aspx = ScreenDivisorX * CameraScale.x;
	float aspy = ScreenDivisorY * CameraScale.y;

	p1.x = (p1.x - CameraPosition.x) * aspx;
	p1.y = (p1.y - CameraPosition.y) * aspy;

	p2.x = (p2.x - CameraPosition.x) * aspx;
	p2.y = (p2.y - CameraPosition.y) * aspy;

	p3.x = (p3.x - CameraPosition.x) * aspx;
	p3.y = (p3.y - CameraPosition.y) * aspy;

	GLfloat vertices[3][4] =
	{
		{ p1.x, p1.y,texcoord1.x,texcoord1.y},
		{ p2.x, p2.y,texcoord2.x,texcoord2.y},
		{ p3.x, p3.y,texcoord3.x,texcoord3.y}
	};


	glBindBuffer(GL_ARRAY_BUFFER, TexturedTriangleVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, NormalMap);
	glUniform1i(glGetUniformLocation(TexturedTriangleShader->Program, "Texture"), 0);

	glUniform4f(glGetUniformLocation(TexturedTriangleShader->Program, "color"), 1.0f,1.0f,1.0f,1.0f);
	glUniform2f(glGetUniformLocation(TexturedTriangleShader->Program, "scr"), WIDTH, HEIGHT);


	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);


	if (HDR)
		glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
	else
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void DrawCircle(glm::vec2 position, float r, glm::vec4 color = glm::vec4(1.0f), bool Lighted = false, unsigned int NormalMap = NULL)
{

	position -= CameraPosition;
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(
		(position.x ) * ScreenDivisorX * CameraScale.x,
		(position.y ) * ScreenDivisorY *CameraScale.y,
		0.0f));

	trans = glm::scale(trans, glm::vec3(r  * ScaleMultiplyer * CameraScale.x, r * ScaleMultiplyer * CameraScale.y, 0.0f));

	if (Lighted)
		NormalMapDraw(trans);

	Circletranslations.push_back(trans);
	Circlecolors.push_back(color);
}
void DrawCircle(ball b, glm::vec4 color = glm::vec4(1.0f), bool Lighted = false, unsigned int NormalMap = NULL)
{

	glm::vec2 position = b.position;
	float r = b.r;
	position -= CameraPosition;
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3((position.x) * ScreenDivisorX * CameraScale.x, (position.y) * ScreenDivisorY * CameraScale.y, 0.0f));

	trans = glm::scale(trans, glm::vec3(r * ScaleMultiplyer * CameraScale.x, r * ScaleMultiplyer * CameraScale.y, 0.0f));


	if (Lighted)
		NormalMapDraw(trans);
	Circletranslations.push_back(trans);
	Circlecolors.push_back(color);
}

std::vector <glm::mat4> Quadtranslations;
std::vector <glm::vec4> Quadcolors;
void DrawCube(glm::vec2 position, glm::vec2 scale, glm::vec3 rotation = glm::vec3(0.0f), glm::vec4 color = glm::vec4(1.0f), bool Lighted = false, unsigned int NormalMap = NULL)
{
	position -= CameraPosition;
	glm::mat4 trans = glm::translate(glm::mat4(1.0f),glm::vec3(
		(position.x) * ScreenDivisorX * CameraScale.x,
		(position.y) * ScreenDivisorY * CameraScale.y,
		0.0f));


	if (rotation.z != 0)
		trans = glm::rotate(trans, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	if (rotation.y != 0)
		trans = glm::rotate(trans, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	if (rotation.x != 0)
		trans = glm::rotate(trans, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	trans = glm::scale(trans, glm::vec3(scale.x* CameraScale.x * ScaleMultiplyer, scale.y* CameraScale.y * ScaleMultiplyer, 0.0f));

	if (Lighted)
		NormalMapDraw(trans,CubeNormalMapTexture, rotation.z);

	Quadtranslations.push_back(trans);
	Quadcolors.push_back(color);


}
void DrawCube(cube c, glm::vec4 color = glm::vec4(1.0f),glm::vec3 rotation=glm::vec3(0.0f), bool Lighted = false, unsigned int NormalMap = NULL)
{
	glm::vec2 position = c.position;
	position -= CameraPosition;
	glm::vec2 scale = glm::vec2(c.width, c.height);

	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(
		(position.x) * ScreenDivisorX * CameraScale.x,
		(position.y) * ScreenDivisorY * CameraScale.y,
		0.0f));


	if (rotation.z != 0)
		trans = glm::rotate(trans, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	if (rotation.y != 0)
		trans = glm::rotate(trans, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	if (rotation.x != 0)
		trans = glm::rotate(trans, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	trans = glm::scale(trans, glm::vec3(scale.x * CameraScale.x * ScaleMultiplyer, scale.y * CameraScale.y * ScaleMultiplyer, 0.0f));

	if (Lighted)
		NormalMapDraw(trans, CubeNormalMapTexture, rotation.z);
		
	Quadtranslations.push_back(trans);
	Quadcolors.push_back(color);
}


void DrawLine(glm::vec2 p1, glm::vec2 p2, float width = 1.0f, glm::vec4 color = glm::vec4(1.0f), bool Lighted = false, unsigned int NormalMap = CubeNormalMapTexture)
{
	glm::vec2 midpos = (p2 + p1) / 2.0f;
	float rotation = get_angle_between_points(p1, p2);
	glm::vec2 dif = p1 - p2;
	float length = sqrt(dif.x * dif.x + dif.y * dif.y)*0.5f;
	DrawCube(midpos, glm::vec2(width  , length), glm::vec3(0.0f, 0.0f, rotation), color, Lighted, NormalMap);
}

void DrawBall(ball b, glm::vec4 Color1 = glm::vec4(1.0f), glm::vec4 Color2 = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),bool Lighted = false, unsigned int NormalMap=NULL)
{

	glm::vec2 univec;
	univec.x = cos(b.rotation * 5) - sin(b.rotation * 5);
	univec.y = sin(b.rotation * 5) + cos(b.rotation * 5);
	DrawLine(b.position - univec * b.r * 0.7f, b.position + univec * b.r * 0.7f, 3.0f, Color2);
	DrawLine(b.position + glm::vec2(-univec.y * b.r * 0.7f, univec.x * b.r * 0.7f), b.position + glm::vec2(univec.y * b.r * 0.7f, -univec.x * b.r * 0.7f), 3.0f, Color2);
	DrawCircle(b, Color1, Lighted, NormalMap);
}



// will load texture from filename, to texture 
void LoadTexture(const char* filename,unsigned int* texture,int chanelsAmount = 4)
{
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	int ImageW, ImageH, nrChannels;
	unsigned char* Texture = stbi_load(filename, &ImageW, &ImageH, &nrChannels, chanelsAmount);

	if (Texture)
	{
		if (chanelsAmount == 1)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_R, ImageW, ImageH, 0, GL_R, GL_UNSIGNED_BYTE, Texture);

		if (chanelsAmount == 2)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, ImageW, ImageH, 0, GL_RG, GL_UNSIGNED_BYTE, Texture);

		if (chanelsAmount == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ImageW, ImageH, 0, GL_RGB, GL_UNSIGNED_BYTE, Texture);

		if (chanelsAmount == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ImageW, ImageH, 0, GL_RGBA, GL_UNSIGNED_BYTE, Texture);


		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		glDeleteTextures(1, texture);
		*texture = NULL;
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(Texture);
	glBindTexture(GL_TEXTURE_2D, 0);

}

Shader* NoizeGenShaderptr;
Shader* BlurShaderPtr;
Shader* RoundShaderptr;

enum
{
	SQUERE = 0,
	SMOOTH_EDGE = 1,
	ROUND = 2
};


void GenNoizeTexture(unsigned int* texture1,int Size, int Layers =3,float freq = 10, int shape = ROUND)
{

	glDeleteTextures(1, texture1);
	unsigned int framebuffer[2], texture2;

	glGenFramebuffers(2, framebuffer);
	glGenTextures(1, &texture2);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer[0]);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Size, Size, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture2, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer[1]);
	glBindTexture(GL_TEXTURE_2D, *texture1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Size, Size, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *texture1, 0);

	bool even = false;
	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, Size, Size);


	for (int i = 0; i < Layers; i++)
	{
		glm::vec2 rngoffset = glm::vec2(rand()%10000, rand() % 10000);

		NoizeGenShaderptr->Use();

		float weight = 1.0f / (i + 1);
		// add new layer (higher freq, less wieght)
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer[even]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, even ? *texture1 : texture2);
		glUniform1i(glGetUniformLocation(NoizeGenShaderptr->Program, "PrevTexture"), 0);

		glUniform1f(glGetUniformLocation(NoizeGenShaderptr->Program, "sizex"), (i + 1) * freq);
		glUniform1f(glGetUniformLocation(NoizeGenShaderptr->Program, "sizey"), (i + 1) * freq);
		glUniform1f(glGetUniformLocation(NoizeGenShaderptr->Program, "weight"), weight);

		glUniform1i(glGetUniformLocation(NoizeGenShaderptr->Program, "shape"), shape);

		glUniform2f(glGetUniformLocation(NoizeGenShaderptr->Program, "offset"), rngoffset.x, rngoffset.y);

		glBindVertexArray(ScreenVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		even = !even;
		
	}
	glDeleteFramebuffers(2, framebuffer);

	*texture1 = texture2;

	glViewport(0, 0, WIDTH, HEIGHT);

	if (HDR)
		glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
	else
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GenNormalMapTexture(unsigned int* texture1, int Size, int shape = ROUND)
{

	glDeleteTextures(1, texture1);
	unsigned int framebuffer, texture2;

	glGenFramebuffers(1, &framebuffer);
	glGenTextures(1, &texture2);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Size, Size, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture2, 0);


	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, Size, Size);

	GenNormalMapShader->Use();

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	int i = 0;
	if (shape == ROUND)
		i = 0;
	else if (shape == SQUERE)
		i = 1;
	else if (shape == SMOOTH_EDGE)
		i = 2;
	glUniform1i(glGetUniformLocation(GenNormalMapShader->Program, "Type"), i);

	glBindVertexArray(ScreenVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	
	glDeleteFramebuffers(1, &framebuffer);

	*texture1 = texture2;

	glViewport(0, 0, WIDTH, HEIGHT);

	if (HDR)
		glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
	else
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void GenLightSphereTexture(unsigned int* texture1, int Size)
{

	glDeleteTextures(1, texture1);
	unsigned int framebuffer, texture2;

	glGenFramebuffers(1, &framebuffer);
	glGenTextures(1, &texture2);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Size, Size, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture2, 0);


	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, Size, Size);

	GenLightSphereShader->Use();

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	glBindVertexArray(ScreenVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);


	glDeleteFramebuffers(1, &framebuffer);

	*texture1 = texture2;

	glViewport(0, 0, WIDTH, HEIGHT);

	if (HDR)
		glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
	else
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
class Texture
{
public:
	int id = 0;
	std::string FileName;
	int Type = 0;// 0-Texture, 1-ROUNDNOIZE, 2-SQUERENOIZE, 3-SMOOTH_EDGENOIZE;
	unsigned int texture;
	void Load()
	{

		if (Type == 0)
			LoadTexture(FileName.c_str(), &texture);
		else if (Type == 1)
			GenNoizeTexture(&texture, 100, 3, 10.0f, ROUND);
		else if (Type == 2)
			GenNoizeTexture(&texture, 100, 3, 10.0f, SQUERE);
		else
			GenNoizeTexture(&texture, 100, 3, 10.0f, SMOOTH_EDGE);
		if (texture == NULL)
			std::cout << "Failed to load texture:  " << FileName.c_str() << std::endl;

	}
};



void DrawTexturedQuad(glm::vec2 position, glm::vec2 scale, unsigned int texture, glm::vec3 rotation = glm::vec3(0.0f), glm::vec4 color = glm::vec4(1.0f))
{
	position -= CameraPosition;
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(
		(position.x) * ScreenDivisorX * CameraScale.x,
		(position.y) * ScreenDivisorY * CameraScale.y,
		0.0f));


	if (rotation.z != 0)
		trans = glm::rotate(trans, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	if (rotation.y != 0)
		trans = glm::rotate(trans, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	if (rotation.x != 0)
		trans = glm::rotate(trans, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	trans = glm::scale(trans, glm::vec3(scale.x * CameraScale.x * ScaleMultiplyer, scale.y * CameraScale.y * ScaleMultiplyer, 0.0f));

	TexturedQuadShader->Use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(TexturedQuadShader->Program, "Texture"), 0);


	glUniform4f(glGetUniformLocation(TexturedQuadShader->Program, "color"), color.x, color.y, color.z, color.w);
	glUniform2f(glGetUniformLocation(TexturedQuadShader->Program, "scr"), WIDTH, HEIGHT);
	glUniformMatrix4fv(glGetUniformLocation(TexturedQuadShader->Program, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
	
	
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}


void DrawTexturedQuad(cube c, unsigned int texture, glm::vec4 color = glm::vec4(1.0f), glm::vec3 rotation = glm::vec3(0.0f))
{
	glm::vec2 position = c.position;
	glm::vec2 scale = glm::vec2(c.width, c.height);
	position -= CameraPosition;
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(
		(position.x) * ScreenDivisorX * CameraScale.x,
		(position.y) * ScreenDivisorY * CameraScale.y,
		0.0f));


	if (rotation.z != 0)
		trans = glm::rotate(trans, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	if (rotation.y != 0)
		trans = glm::rotate(trans, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	if (rotation.x != 0)
		trans = glm::rotate(trans, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	trans = glm::scale(trans, glm::vec3(scale.x * CameraScale.x * ScaleMultiplyer, scale.y * CameraScale.y * ScaleMultiplyer, 0.0f));

	TexturedQuadShader->Use();

	glBindTexture(GL_TEXTURE_2D, texture);

	glUniform4f(glGetUniformLocation(TexturedQuadShader->Program, "color"), color.x, color.y, color.z, color.w);
	glUniform2f(glGetUniformLocation(TexturedQuadShader->Program, "scr"), WIDTH, HEIGHT);
	glUniformMatrix4fv(glGetUniformLocation(TexturedQuadShader->Program, "transform"), 1, GL_FALSE, glm::value_ptr(trans));

	
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}


void DrawTriangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec4 color = glm::vec4(1.0f))
{

	glBindVertexArray(TriangleVAO);
	FilShader->Use();
	float aspx = 1.0f * ScreenDivisorX * CameraScale.x;
	float aspy = 1.0f * ScreenDivisorY * CameraScale.y;
	p1.x = (p1.x - CameraPosition.x) * aspx;
	p1.y = (p1.y - CameraPosition.y) * aspy;

	p2.x = (p2.x - CameraPosition.x) * aspx;
	p2.y = (p2.y - CameraPosition.y) * aspy;

	p3.x = (p3.x - CameraPosition.x) * aspx;
	p3.y = (p3.y - CameraPosition.y) * aspy;

	GLfloat vertices[3][2] =
	{

		{ p1.x, p1.y},
		{ p2.x, p2.y},
		{ p3.x, p3.y}
	};


	glBindBuffer(GL_ARRAY_BUFFER, TriangleVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUniform4f(glGetUniformLocation(FilShader->Program, "Color"), color.x, color.y, color.z, color.w);

	glUniform2f(glGetUniformLocation(FilShader->Program, "scr"), WIDTH, HEIGHT);


	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);



}
void DrawTexturedTriangle(
	glm::vec2 p1,
	glm::vec2 p2,
	glm::vec2 p3,
	unsigned int texture,
	glm::vec4 color = glm::vec4(1.0f),
	glm::vec2 texcoord1 = glm::vec2(0.0f,1.0f),
	glm::vec2 texcoord2 = glm::vec2(0.5f, 0.0f),
	glm::vec2 texcoord3 = glm::vec2(1.0f, 1.0f)
	)
{

	TexturedTriangleShader->Use();
	glBindVertexArray(TexturedTriangleVAO);
	float aspx = ScreenDivisorX * CameraScale.x;
	float aspy = ScreenDivisorY * CameraScale.y;

	p1.x = (p1.x - CameraPosition.x) * aspx;
	p1.y = (p1.y - CameraPosition.y) * aspy;

	p2.x = (p2.x - CameraPosition.x) * aspx;
	p2.y = (p2.y - CameraPosition.y) * aspy;

	p3.x = (p3.x - CameraPosition.x) * aspx;
	p3.y = (p3.y - CameraPosition.y) * aspy;

	GLfloat vertices[3][4] =
	{
		{ p1.x, p1.y,texcoord1.x,texcoord1.y},
		{ p2.x, p2.y,texcoord2.x,texcoord2.y},
		{ p3.x, p3.y,texcoord3.x,texcoord3.y}
	};


	glBindBuffer(GL_ARRAY_BUFFER, TexturedTriangleVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(TexturedTriangleShader->Program, "Texture"),0);
	
	glUniform4f(glGetUniformLocation(TexturedTriangleShader->Program, "color"), color.x, color.y, color.z, color.w);
	glUniform2f(glGetUniformLocation(TexturedTriangleShader->Program, "scr"), WIDTH, HEIGHT);


	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);


}
