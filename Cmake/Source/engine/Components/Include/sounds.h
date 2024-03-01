#pragma once
// openAL
#include <AL/alext.h>
#include "LoadWAV.h"

ALint state = AL_PLAYING;

std::vector <ALuint*> sources;
std::vector <ALuint*> sounds;
std::vector <unsigned int> soundsArray;
std::vector <unsigned int*> soundsArray2;

ALCdevice* Device = alcOpenDevice(NULL);
ALCcontext* Context;
ALCboolean contextMadeCurrent;

glm::vec3 listenerPos = { 0.0,0.0,0.0 };
glm::vec3 listenerVel = { 0.0,0.0,0.0 };
ALfloat listenerOri[] = { 0.0,0.0,1.0, 0.0,-1.0,0.0 };

glm::vec3 soundscale = { 1.0f,1.0f ,1.0f };
glm::vec3 soundSpeedscale = { 1.0f,1.0f ,1.0f };
void AL_init()
{

	ALfloat lpos[] = { listenerPos.x, listenerPos.y, listenerPos.y };
	ALfloat lvel[] = { listenerVel.x, listenerVel.y, listenerVel.y };

	alListenerfv(AL_POSITION, lpos);
	alListenerfv(AL_VELOCITY, lvel);
	alListenerfv(AL_ORIENTATION, listenerOri);

	if (Device) {
		Context = alcCreateContext(Device, NULL);
		alcMakeContextCurrent(Context);
	}

	contextMadeCurrent = alcMakeContextCurrent(Context);
	if (!contextMadeCurrent)
		std::cerr << "ERROR: Could not make audio context current" << "\n";


}

void AL_Reload()
{
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(Context);
	if (Device) {
		Context = alcCreateContext(Device, NULL);
		alcMakeContextCurrent(Context);
	}

	contextMadeCurrent = alcMakeContextCurrent(Context);
	if (!contextMadeCurrent)
		std::cerr << "Sound Error" << "\n";
}

void  AL_Destroy()
{
	for (int i = 0; i < sources.size(); i++)
	{
		alSourceStop(*sources[i]);
		alDeleteSources(1, sources[i]);
	}
	alcCloseDevice(Device);
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(Context);
}

void UpdateListenerPosition()
{

	listenerPos.x = CameraPosition.x / WIDTH;
	listenerPos.y = CameraPosition.y / HEIGHT;

	ALfloat lpos[] = { listenerPos.x * soundscale.x, listenerPos.y * soundscale.y, listenerPos.z * soundscale.z };
	ALfloat lvel[] = { listenerVel.x * soundSpeedscale.x, listenerVel.y * soundSpeedscale.y, listenerVel.z * soundSpeedscale.z };

	alListenerfv(AL_POSITION, lpos);
	alListenerfv(AL_VELOCITY, lvel);
	alListenerfv(AL_ORIENTATION, listenerOri);
}

void GenSource(unsigned int* source)
{
	alGenSources(1, source);
	alSourcef(*source, AL_GAIN, 1.0f);
	alSourcef(*source, AL_PITCH, 1.0f);
	alSource3f(*source, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSource3f(*source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	alSourcei(*source, AL_LOOPING, AL_FALSE);

	sources.push_back(source);
}
void SetSourcePitch(unsigned int* source, float pitch)// stock = 1.0f;
{
	alSourcef(*source, AL_PITCH, pitch);
}
void SetSourceGain(unsigned int* source, float gain)// stock = 1.0f;
{
	alSourcef(*source, AL_GAIN, gain);
}

void SetSourceRefDist(unsigned int* source, float Distance)// stock = 1.0f;
{
	alSourcef(*source, AL_REFERENCE_DISTANCE, Distance);
}
void SetSourceMaxDistance(unsigned int* source, float Distance)// stock = 1.0f;
{
	alSourcef(*source, AL_MAX_DISTANCE, Distance);
}

void SetSourcePosition(unsigned int* source, glm::vec3 position)// stock = 0.0f,0.0f,0.0f;
{
	glm::vec3 pos;
	pos.x = position.x / WIDTH * soundscale.x;
	pos.y = position.y / HEIGHT * soundscale.y;
	pos.z = position.z * soundscale.z;
	alSource3f(*source, AL_POSITION, pos.x, pos.y, pos.z);
}
void SetSourcePosition(unsigned int* source, glm::vec2 position)// stock = 0.0f,0.0f,0.0f;
{
	glm::vec3 pos;
	pos.x = position.x / WIDTH * soundscale.x;
	pos.y = position.y / HEIGHT * soundscale.y;
	pos.z = 0;
	alSource3f(*source, AL_POSITION, pos.x, pos.y, pos.z);
}

void SetSourceVelocity(unsigned int* source, glm::vec3 velocity)// stock = 0.0f,0.0f,0.0f;
{
	alSource3f(*source, AL_VELOCITY, velocity.x * soundSpeedscale.x, velocity.y * soundSpeedscale.y, velocity.z * soundSpeedscale.z);
}
void SetSourceLooping(unsigned int* source, bool looping)// stock = false;
{
	alSourcei(*source, AL_LOOPING, looping);
}


void SetSourceSound(unsigned int* source, unsigned int* sound)
{
	alSourcei(*source, AL_BUFFER, *sound);
}



// helpfull when source is running on loop
void SwapSourceSound(unsigned int* source, unsigned int* sound)
{
	alSourceStop(*source);
	alSourcei(*source, AL_BUFFER, *sound);
	alSourcePlay(*source);
}
void PlaySource(unsigned int* source)
{
	alSourcePlay(*source);
}
void StopSource(unsigned int* source)
{
	alSourceStop(*source);
}

bool SourcePlaying(unsigned int* source)
{
	int playing;
	alGetSourcei(*source, AL_SOURCE_STATE, &playing);
	return playing == AL_PLAYING;
}

void DeleteSource(unsigned int* source)
{

	int i = 0;
	bool go = true;
	while (go && i < sources.size())
	{
		if (sources[i] == source)
		{
			go = false;
			sources[i] = sources[sources.size() - 1];
			sources.pop_back();
		}
		i++;
	}

	alSourceStop(*source);
	alDeleteSources(1, source);
	*source = 0;
}

void PlaySound(unsigned int* sound, glm::vec2 position, float pitch = 1.0f, float gain = 1.0f)
{
	unsigned int src;

	alGenSources(1, &src);
	alSourcef(src, AL_GAIN, 1.0f);
	alSourcef(src, AL_PITCH, 1.0f);
	alSource3f(src, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSource3f(src, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	alSourcei(src, AL_LOOPING, AL_FALSE);

	soundsArray.push_back(src);
	SetSourcePosition(&soundsArray[soundsArray.size() - 1], position);
	SetSourceSound(&soundsArray[soundsArray.size() - 1], sound);
	SetSourceGain(&soundsArray[soundsArray.size() - 1], gain);
	SetSourcePitch(&soundsArray[soundsArray.size() - 1], pitch);
	PlaySource(&soundsArray[soundsArray.size() - 1]);



}
void PlaySound(unsigned int* dst, unsigned int* sound, glm::vec2 position, float pitch = 1.0f, float gain = 1.0f)
{
	if (dst == NULL) {
		std::cout << "asdasd";
		dst = new unsigned int;
	}
	if (*dst == NULL)
	{

		alGenSources(1, dst);

		alSourcef(*dst, AL_GAIN, 1.0f);
		alSourcef(*dst, AL_PITCH, 1.0f);
		alSource3f(*dst, AL_POSITION, 0.0f, 0.0f, 0.0f);
		alSource3f(*dst, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
		alSourcei(*dst, AL_LOOPING, AL_FALSE);
		soundsArray2.push_back(dst);
	}
	SetSourcePosition(dst, position);
	SetSourceSound(dst, sound);
	SetSourceGain(dst, gain);
	SetSourcePitch(dst, pitch);
	PlaySource(dst);

}
void PlaySound(unsigned int** dst, unsigned int* sound, glm::vec2 position, float pitch = 1.0f, float gain = 1.0f)
{
	if (*dst == NULL) {
		*dst = new unsigned int();
	}
	if (**dst == NULL)
	{

		alGenSources(1, *dst);

		alSourcef(**dst, AL_GAIN, 1.0f);
		alSourcef(**dst, AL_PITCH, 1.0f);
		alSource3f(**dst, AL_POSITION, 0.0f, 0.0f, 0.0f);
		alSource3f(**dst, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
		alSourcei(**dst, AL_LOOPING, AL_FALSE);
		soundsArray2.push_back(*dst);
	}
	SetSourcePosition(*dst, position);
	SetSourceSound(*dst, sound);
	SetSourceGain(*dst, gain);
	SetSourcePitch(*dst, pitch);
	PlaySource(*dst);

}
void ProcessAL()
{
	for (int i = 0; i < soundsArray.size(); i++)
	{
		bool del = true;
		while (del && i < soundsArray.size())
		{
			del = false;
			if (!SourcePlaying(&soundsArray[i]) || soundsArray[i] == 0)
			{
				del = true;

				alSourceStop(soundsArray[i]);
				alDeleteSources(1, &soundsArray[i]);

				soundsArray[i] = soundsArray[soundsArray.size() - 1];
				soundsArray.pop_back();
			}
		}
	}
	for (int i = 0; i < soundsArray2.size(); i++)
	{

		bool del = true;
		while (del && i < soundsArray2.size())
		{
			del = false;
			if (soundsArray2[i] == 0 || *soundsArray2[i] == 0)
			{
				del = true;
				soundsArray2[i] = soundsArray2[soundsArray2.size() - 1];
				soundsArray2.pop_back();
			}
			else if (!SourcePlaying(soundsArray2[i]))
			{
				del = true;

				alSourceStop(*soundsArray2[i]);
				alDeleteSources(1, soundsArray2[i]);
				*soundsArray2[i] = 0;
				soundsArray2[i] = soundsArray2[soundsArray2.size() - 1];
				soundsArray2.pop_back();
			}

		}
	}
}