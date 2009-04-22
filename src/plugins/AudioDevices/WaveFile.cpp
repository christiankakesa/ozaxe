/*
** This file is part of OZAXE project.
**
** This class intend to be an object root of all of the classes in OZAXE 
** application.
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/

#include <iostream>
#include <cstring>
#include <glibmm/ustring.h>
#include <sndfile.h>

#include "WaveFile.h"

WaveFile::WaveFile(void):sffile(NULL)
{;}

WaveFile::~WaveFile(void)
{
  /** Make empty sfinfo values */
  memset(&this->sfinfo, 0, sizeof(this->sfinfo));
  /** Close properly sound file */
  if (this->sffile)
    sf_close(this->sffile);
}

int	WaveFile::Open(const Glib::ustring &filename, open_mode_t open_mode, int fd)
{
  this->_open_mode = open_mode;

  switch (this->_open_mode)
    {
    case o_mode_r :
      this->sffile = sf_open(filename.c_str(), SFM_READ, &this->sfinfo);
      break;
    case o_mode_w :
      this->sffile = sf_open(filename.c_str(), SFM_WRITE, &this->sfinfo);
      break;
    case o_mode_rw :
      this->sffile = sf_open(filename.c_str(), SFM_RDWR, &this->sfinfo);
      break;
    case o_mode_tmp :
      if (fd != -1)
	this->sffile = sf_open_fd(fd, SFM_RDWR, &this->sfinfo, TRUE);
      break;
    default:
      std::cerr << "Unknow opening mode !!!" << std::endl;
    }

  return (0);
}

sf_count_t	WaveFile::ReadStreamFrames(SNDFILE *sndfile, void *ptr, sf_count_t frames, data_type_t type)
{

  switch (type)
    {
    case dt_ushort :
    case dt_short :
      return (sf_readf_short(sndfile, (short *)ptr, frames));
      break;
    case dt_int :
      return (sf_readf_int(sndfile, (int *)ptr, frames));
      break;
    case dt_float :
      return (sf_readf_float(sndfile, (float *)ptr, frames));
      break;
    default:
      return (sf_readf_short(sndfile, (short *)ptr, frames));
      break;
    }

}

sf_count_t	WaveFile::ReadStreamItems(SNDFILE *sndfile, void *ptr, sf_count_t items, data_type_t type)
{
  switch (type)
    {
    case dt_ushort :
    case dt_short :
      return (sf_read_short(sndfile, (short *)ptr, items));
      break;
    case dt_int :
      return (sf_read_int(sndfile, (int *)ptr, items));
      break;
    case dt_float :
      return (sf_read_float(sndfile, (float *)ptr, items));
      break;
    default:
      return (sf_read_short(sndfile, (short *)ptr, items));
      break;
    }
}

sf_count_t	WaveFile::WriteStreamFrames(SNDFILE *sndfile, void *ptr, sf_count_t frames, data_type_t type)
{
  switch (type)
    {
    case dt_ushort :
    case dt_short :
      return (sf_writef_short(sndfile, (short *)ptr, frames));
      break;
    case dt_int :
      return (sf_writef_int(sndfile, (int *)ptr, frames));
      break;
    case dt_float :
      return (sf_writef_float(sndfile, (float *)ptr, frames));
      break;
    default:
      return (sf_writef_short(sndfile, (short *)ptr, frames));
      break;
    }
}

sf_count_t	WaveFile::WriteStreamItems(SNDFILE *sndfile, void *ptr, sf_count_t items, data_type_t type)
{
    switch (type)
    {
    case dt_ushort :
    case dt_short :
      return (sf_write_short(sndfile, (short *)ptr, items));
      break;
    case dt_int :
      return (sf_write_int(sndfile, (int *)ptr, items));
      break;
    case dt_float :
      return (sf_write_float(sndfile, (float *)ptr, items));
      break;
    default:
      return (sf_write_short(sndfile, (short *)ptr, items));
      break;
    }
}

void	WaveFile::DumpSf(void)
{
  std::cout << "------START------" << std::endl;
  std::cout << "Sffile ptr : " << this->sffile << std::endl;
  std::cout << "Sfinfo Frames: " << this->sfinfo.frames << std::endl;
  std::cout << "Sfinfo SampleRate : " << this->sfinfo.samplerate << std::endl;
  std::cout << "Sfinfo Channels : " << this->sfinfo.channels << std::endl;
  std::cout << "Sfinfo Format : " << std::hex << this->sfinfo.format << std::dec << std::endl;
  std::cout << "Sfinfo Sections :  " << this->sfinfo.sections << std::endl;
  std::cout << "Sfinfo Seekable : " << this->sfinfo.seekable << std::endl;
  std::cout << "-----ENDING------" << std::endl;
  return;
}
