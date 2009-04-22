/*
** This file is part of OZAXE project.
**
** This class intend to be an object root of all of the classes in OZAXE 
** application.
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/

#ifndef __AUDIODEVICES_H_
#define __AUDIODEVICES_H_

#include <map>
#include <glibmm/ustring.h>
#include <portaudio.h>
#include <sndfile.h>
#include "../../IPluginAudioDevices.h"

#include "WaveFile.h"

#define DEFAULT_SAMPLE_RATE		(44100)
#define DEFAULT_CHANNELS		(2)
#define DEFAULT_SAMPLES_PER_BUFFER	(3200)
#define DEFAULT_SAMPLE_FORMAT		paFloat32
#define OUTPUT_SAMPLE_FORMAT		paInt16
#define INPUT_SAMPLE_FORMAT		paFloat32

class PLUGIN_EXPORT AudioDevices : public IPluginAudioDevices
{
  public:
    bool	m_init;

  private:
    const Glib::ustring m_strName;
    const Glib::ustring m_strDescription;
    const Glib::ustring m_strVersion;
    const Glib::ustring m_strAuthorName;
    PaDeviceIndex		m_selectedInput;
    PaDeviceIndex       m_selectedOutput;
    device_list_t*		m_allDev;
    device_list_t*		m_allInputDev;
    device_list_t*		m_allOutputDev;
    const PaDeviceInfo*	m_devInfo;
    PaStream*			m_stream;
    callback_t*			m_inputData;
    callback_t*			m_outputData;
    WORK_SOUND_BUFFER*	m_tmpBuffer;
    PaError				m_paErr;
    Glib::ustring		m_fileType;
    
	public: //FIXME: Need to create getter and setter
    bool				m_isPlaying;
    bool				m_isPaused;
    bool				m_isStoped;
    bool				m_isRecording;
    float				m_playVolume; // 0.0f => 1.0f
    float				m_recVolume; // 0.0f => 1.0f

  public:
    AudioDevices(void);
    virtual ~AudioDevices(void);

    virtual const Glib::ustring& GetName(void) const;
    virtual const Glib::ustring& GetDescription(void) const;
    virtual const Glib::ustring& GetVersion(void) const;
    virtual const Glib::ustring& GetAuthorName(void) const;

    virtual bool	InitAudio(void);
    virtual bool	KillAudio(void);

    virtual PaStream	*GetStream(void);
    virtual bool	Play(Glib::ustring &inFile);
    virtual bool	Stop(void);
    virtual bool	Pause(void);
    virtual bool	Rec(const Glib::ustring &outFile, int sec);
    virtual bool	PlayRec(Glib::ustring &inFile, Glib::ustring &outFile);

    virtual PaHostApiIndex	GetHostApiCount(void);
    virtual PaDeviceIndex	GetTotalDeviceCount(void);

    virtual device_list_t	*GetAllDevices(void);
    virtual device_list_t	*GetAllInputDevices(void);
    virtual device_list_t	*GetAllOutputDevices(void);

    virtual PaDeviceIndex	GetInputDevice(void);
    virtual void                SetInputDevice(PaDeviceIndex input);
  
    virtual PaDeviceIndex	GetOutputDevice(void);
    virtual void	SetOutputDevice(PaDeviceIndex output);

    virtual void	SetDefaultInOutDevice(void);

    virtual Glib::ustring	GetDeviceName(const PaDeviceInfo *info);
    virtual void			MapAudioDevices(void);
    virtual void			MapInputOutputDevices(void);
    virtual void			PrintStreamInfo(const PaStreamInfo *streamInfo);
    
    static int  AudioCallBack(const void *inputBuffer,
                              void *outputBuffer,
                              unsigned long framesPerBuffer,
                              const PaStreamCallbackTimeInfo *timeInfo,
                              PaStreamCallbackFlags statusFlags,
                              void *userData);
};
typedef AudioDevices* (*audiodevices_t)();
typedef void (*audiodevices_destroy_t)(AudioDevices*);

#endif /* !__AUDIODEVICES_H_ */

