/*
** This file is part of OZAXE project.
**
** This class intend to be an object root of all of the classes in OZAXE 
** application.
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/

#ifndef __WAVFILE_H_
#define __WAVFILE_H_

# include <iostream>
# include <glibmm/ustring.h>
# include <sndfile.h>

class WaveFile
{
  public:
    typedef enum
    {
      o_mode_r = 0,
      o_mode_w,
      o_mode_rw,
      o_mode_tmp
    }	open_mode_t;

    typedef enum
    {
      dt_ushort = 0,
      dt_short,
      dt_int,
      dt_float
    }	data_type_t;
    
    bool	_loadInMemory;
    bool	_error;
    open_mode_t _open_mode;
    SNDFILE	*sffile;
    SF_INFO	sfinfo;

  public:
    WaveFile(void);
    ~WaveFile(void);

    int         Open(const Glib::ustring &filename, open_mode_t open_mode = o_mode_r, int fd = -1);
    sf_count_t	ReadStreamFrames(SNDFILE *sndfile, void *ptr, sf_count_t frames, data_type_t type = dt_short);
    sf_count_t	ReadStreamItems(SNDFILE *sndfile, void *ptr, sf_count_t items, data_type_t type = dt_short);
    sf_count_t	WriteStreamFrames(SNDFILE *sndfile, void *ptr, sf_count_t frames, data_type_t type = dt_short);
    sf_count_t	WriteStreamItems(SNDFILE *sndfile, void *ptr, sf_count_t items, data_type_t type = dt_short);
    void	DumpSf(void);
};

#endif /* !__WAVFILE_H_ */
