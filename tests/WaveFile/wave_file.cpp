//
// main.cpp for OZAXE in /home/christian/workspace/ozaxe/trunk/src/linux32/plugins/AudioDevices/codecs/Wav
// 
// Made by Christian KAKESA
// Login   <christian@epita.fr>
// 
// Started on  Sat Jun  9 02:37:30 2007 Christian KAKESA
// Last update Sun Jun 10 12:45:35 2007 Christian KAKESA
//

#include <iostream>
#include <cstdlib>
#include <glibmm/ustring.h>

#include <WaveFile.h>

void	Usage(void);

int main(int ac, char **av)
{
  std::cout << "--- MAIN STARTED ---" << std::endl;
  
  if (ac != 2)
    {
      Usage();
      exit (1);
    }
  
  const Glib::ustring str(av[1]);
  
  WaveFile *wf = new WaveFile();
  wf->Open(str);
  wf->DumpSf();
  
  if (wf)
    delete wf;
  
  return (0);
}

void	Usage(void)
{
  std::cout << "Usage: ./test filename.wav" << std::endl;
}
