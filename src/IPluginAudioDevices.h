/*
** This file is part of OZAXE project.
**
** This class intend to be an object root of all of the classes in OZAXE
** application.
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/

#ifndef __IPLUGINAUDIODEVICES_H_
#define __IPLUGINAUDIODEVICES_H_

#include <map>
#include <glibmm/ustring.h>
#include <portaudio.h>
#include <sndfile.h>

#include "IPlugin.h"

typedef short   SOUND_BUFFER;
typedef float   WORK_SOUND_BUFFER;
typedef std::map<PaDeviceIndex, Glib::ustring> device_list_t;

typedef enum
{
        play = 0,
        rec,
        playrec
}       playmode_t;

typedef struct  callback_s
{
        WORK_SOUND_BUFFER*      buffer;
        sf_count_t                      frames; //samples
        int                                     samplerate;
        int                                     channels;
        int                                     format;
        int                                     sections;
        int                                     seekable;
        unsigned long           bufferPos;
        unsigned long           bufferLen;
        PaDeviceIndex           inputDevice;
        PaDeviceIndex           outputDevice;
        unsigned long           sampleFormat;
        unsigned long           inputSampleFormat;
        unsigned long           outputSampleFormat;
        bool*                   isPlaying;
        bool*                   isPaused;
        bool*                   isStoped;
        bool*                   isRecording;
        float*                  playVolume;
        float*                  recVolume;
        playmode_t              playMode;
}       callback_t;

class PLUGIN_EXPORT IPluginAudioDevices : virtual public IPlugin
{
public:
	IPluginAudioDevices(void) { }
	virtual ~IPluginAudioDevices(void) { }
	virtual bool    InitAudio(void) = 0;
	virtual bool    KillAudio(void) = 0;
	virtual PaStream        *GetStream(void) = 0;
	virtual bool    Play(Glib::ustring &inFile) = 0;
	virtual bool    Stop(void) = 0;
	virtual bool    Pause(void) = 0;
	virtual bool    Rec(const Glib::ustring &outFile, int sec) = 0;
	virtual bool    PlayRec(Glib::ustring &inFile, Glib::ustring &outFile) = 0;
	virtual PaHostApiIndex  GetHostApiCount(void) = 0;
	virtual PaDeviceIndex   GetTotalDeviceCount(void) = 0;
	virtual device_list_t   *GetAllDevices(void) = 0;
	virtual device_list_t   *GetAllInputDevices(void) = 0;
	virtual device_list_t   *GetAllOutputDevices(void) = 0;
	virtual PaDeviceIndex   GetInputDevice(void) = 0;
	virtual void                SetInputDevice(PaDeviceIndex input) = 0;

	virtual PaDeviceIndex   GetOutputDevice(void) = 0;
	virtual void    SetOutputDevice(PaDeviceIndex output) = 0;

	virtual void    SetDefaultInOutDevice(void) = 0;
	virtual Glib::ustring   GetDeviceName(const PaDeviceInfo *info) = 0;
	virtual void                    MapAudioDevices(void) = 0;
	virtual void                    MapInputOutputDevices(void) = 0;
	virtual void                    PrintStreamInfo(const PaStreamInfo *streamInfo) = 0;

	static int  AudioCallBack(      const void *inputBuffer,
					void *outputBuffer,
					unsigned long framesPerBuffer,
					const PaStreamCallbackTimeInfo *timeInfo,
					PaStreamCallbackFlags statusFlags,
					void *userData  );
};

#endif /* !__IPLUGINAUDIODEVICES_H_ */

