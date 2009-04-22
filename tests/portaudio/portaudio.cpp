//
// test.cpp for OZAXE in /home/christian/workspace/ozaxe/trunk/src/linux32
// 
// Made by Christian KAKESA
// Login   <christian@epita.fr>
// 
// Started on  Mon May 28 23:13:27 2007 Christian KAKESA
// Last update Thu Jun  7 20:24:50 2007 Christian KAKESA
//
#include <iostream>
#include <portaudio.h>

int	main(int ac, char **av)
{
  PaError err = Pa_Initialize();
  if ( err != paNoError ) 
    std::cout << "[AUDIO] Portaudio initialization failed" << std::endl;
  else
    std::cout << "[AUDIO] Portaudio initialized" << std::endl;
  
  int numDevices;
  numDevices = Pa_GetDeviceCount();
  if( numDevices < 0 )
      std::cout << "ERROR: Pa_CountDevices returned " << numDevices << std::endl;
  else
    std::cout << "Nombre de peripherique Audio: " << numDevices << std::endl;

  const   PaDeviceInfo *deviceInfo;
  for (int i = 0; i < numDevices; ++i)
    {
      deviceInfo = Pa_GetDeviceInfo(i);
      std::cout << "========== Device #";
      if (i < 9)
	std::cout << "0";

      std::cout << i + 1 << " ==========" << std::endl;
      std::cout << "Structure version: " << deviceInfo->structVersion << std::endl;
      std::cout << "Device name: " << deviceInfo->name << std::endl;
      std::cout << "Host API: " << deviceInfo->hostApi << std::endl;
      std::cout << "Max input channels: " << deviceInfo->maxInputChannels << std::endl;
      std::cout << "Max output channels: " << deviceInfo->maxOutputChannels << std::endl;
      std::cout << "Default low input latency: " << deviceInfo->defaultLowInputLatency << std::endl;
      std::cout << "Default low output latency: " << deviceInfo->defaultLowOutputLatency << std::endl;
      std::cout << "Default high input latency: " << deviceInfo->defaultHighInputLatency << std::endl;
      std::cout << "Default high output latency: " << deviceInfo->defaultHighOutputLatency << std::endl;
      std::cout << "Default sample rate: " << deviceInfo->defaultSampleRate << std::endl;
      std::cout << "================================" << std::endl;
    }

  err = Pa_Terminate();
  if (err != paNoError)
    std::cout << "[AUDIO] Error Terminate(): " << Pa_GetErrorText (err) << std::endl; 
  else
    std::cout << "[AUDIO] Portaudio unloaded" << std::endl;

  std::cout << "Programme de test !!!" << std::endl;

  return (0);
}
