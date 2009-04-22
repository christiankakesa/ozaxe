//
// main.cpp for OZAXE in /home/christian/workspace/ozaxe/trunk/src/linux32/plugins/AudioDevices
// 
// Made by Christian KAKESA
// Login   <christian@epita.fr>
// 
// Started on  Fri Jun  1 03:48:55 2007 Christian KAKESA
// Last update Fri Sep 21 23:22:50 2007 Christian KAKESA
//

#include <iostream>
#include <map>
#include <glibmm/ustring.h>

#include <ozaxelib/OzaxeLib.h>
#include <AudioDevices.h>

using namespace OzaxeLib::System;

int	main(int ac, char **av)
{
  const Glib::ustring lib_path = "libozaxeplugin_audiodevices.so";
  CLibrary libaudiodevices;
  if (!libaudiodevices.Load(lib_path))
    {
      std::cout << "Impossible to load library !!!" << std::endl;
      return (1);
    }
  audiodevices_t pAudioDevices_New = reinterpret_cast<audiodevices_t>(libaudiodevices.GetAddr("AudioDevices_New"));
  audiodevices_destroy_t pAudioDevices_Destroy = reinterpret_cast<audiodevices_destroy_t>(libaudiodevices.GetAddr("AudioDevices_Destroy"));
  AudioDevices* ap = pAudioDevices_New();
  std::cout << "Nombre total de peripherique audio: " << ap->GetTotalDeviceCount() << std::endl;
  device_list_t::iterator iter;

  std::cout << "[INPUT DEVICES]" << std::endl;
  for ( iter = ap->GetAllInputDevices()->begin(); iter != ap->GetAllInputDevices()->end(); ++iter )
    {
      std::cout << "Device #" << iter->first << " : " << iter->second << std::endl;
    }

  std::cout << "[OUTPUT DEVICES]" << std::endl;
  for ( iter = ap->GetAllOutputDevices()->begin(); iter != ap->GetAllOutputDevices()->end(); ++iter )
    {
      std::cout << "Device #" << iter->first << " : " << iter->second << std::endl;
    }

  std::cout << "----- START FILE RECORDING -----" << std::endl;
  if (ac == 2)
    {
      const Glib::ustring file(av[1]);
      std::cout << "Path: " << file << std::endl;
      ap->SetInputDevice((PaDeviceIndex)2);
      ap->SetOutputDevice((PaDeviceIndex)2);
      ap->m_recVolume = 1.0f;
      ap->Rec(file, 10);
      ap->Stop();
    }
  std::cout << "----- END FILE RECORDING -----" << std::endl;
  pAudioDevices_Destroy(ap);
  libaudiodevices.UnLoad();
  return (0);
}