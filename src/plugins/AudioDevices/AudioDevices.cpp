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
#include <glibmm/ustring.h>
#include <portaudio.h>
#include <sndfile.h>

#include "WaveFile.h"
#include "AudioDevices.h"

AudioDevices::AudioDevices(void):m_strName("AudioDevices"),
				 m_strDescription("Audio devices manager."),
				 m_strVersion("1.0.0"),
				 m_strAuthorName("Christian KAKESA <christian.kakesa@gmail.com>"),
				 m_selectedInput(0),
				 m_selectedOutput(0),
				 m_allDev(NULL),
				 m_allInputDev(NULL),
				 m_allOutputDev(NULL),
				 m_devInfo(NULL),
				 m_stream(NULL),
				 m_inputData(NULL),
				 m_outputData(NULL),
				 m_tmpBuffer(NULL),
				 m_paErr(0),
				 m_fileType("wav") 
{
  //TODO : Detect if file is wav or flac file  
  if ( !this->InitAudio() )
    std::cerr << "Can't initialize audio device correctly !!!" << std::endl;
  else
    {
      this->MapAudioDevices();
      this->MapInputOutputDevices();
      this->SetDefaultInOutDevice();
    }
}

AudioDevices::~AudioDevices(void)
{
  if ( !this->KillAudio() )
      std::cerr << "Can't Kill audio device correctly !!!" << std::endl;

  delete m_allDev;
  delete m_allInputDev;
  delete m_allOutputDev;
  delete m_inputData;
  delete m_outputData;
  delete[] m_tmpBuffer;

  m_allDev = NULL;
  m_allInputDev = NULL;
  m_allOutputDev = NULL;
  m_inputData = NULL;
  m_outputData = NULL;
  m_tmpBuffer = NULL;
}

const Glib::ustring& AudioDevices::GetName(void) const
{
  return (m_strName);
}

const Glib::ustring& AudioDevices::GetDescription(void) const
{
  return (m_strDescription);
}

const Glib::ustring& AudioDevices::GetVersion(void) const
{
  return (m_strVersion);
}

const Glib::ustring& AudioDevices::GetAuthorName(void) const
{
  return (m_strAuthorName);
}

PaStream	*AudioDevices::GetStream(void)
{
  return (m_stream);
}

bool	AudioDevices::Play(Glib::ustring &inFile)
{
  if (m_fileType.compare("wav") == 0 || m_fileType.compare("flac") == 0)
    {
      delete[] m_tmpBuffer;

      m_tmpBuffer = NULL;
      WaveFile *wf = NULL;
      wf = new WaveFile;
      if (!wf)
      	std::cerr << "Impossible to create WaveFile object !!! - " << __FILE__ << ":" <<  __LINE__ << std::endl;

      wf->Open(inFile);
      m_tmpBuffer = new WORK_SOUND_BUFFER[wf->sfinfo.frames * wf->sfinfo.channels];
      if (!m_tmpBuffer)
      	std::cerr << "Impossible to create m_tmpBuffer array !!! - " << __FILE__ << ":" <<  __LINE__ << std::endl;

      sf_count_t read_frames = wf->ReadStreamFrames(wf->sffile, m_tmpBuffer, wf->sfinfo.frames, wf->dt_float);
      if (read_frames <= 0)
	{
	  std::cerr << "Impossible to read buffer data !!! - " << __FILE__ << ":" <<  __LINE__ << std::endl;
	  std::cerr << "OZAXE is supporting only wav or flac file" << std::endl;
	}
	
      sf_command (wf->sffile, SFC_SET_NORM_FLOAT, NULL, SF_TRUE);

      delete m_outputData;
      m_outputData = NULL;
      m_outputData = new callback_t;
      m_outputData->buffer = m_tmpBuffer;
      m_outputData->frames = wf->sfinfo.frames;
      m_outputData->samplerate = wf->sfinfo.samplerate ? wf->sfinfo.samplerate : (int)DEFAULT_SAMPLE_RATE;
      m_outputData->channels =  wf->sfinfo.channels ? wf->sfinfo.channels : DEFAULT_CHANNELS;
      m_outputData->format = wf->sfinfo.format;
      m_outputData->sections = wf->sfinfo.sections;
      m_outputData->seekable = wf->sfinfo.seekable;
      m_outputData->bufferLen = (unsigned long)(wf->sfinfo.frames * wf->sfinfo.channels);
      m_outputData->bufferPos = 0;
      m_outputData->inputDevice = m_selectedInput;
      m_outputData->outputDevice = m_selectedOutput;
      m_outputData->sampleFormat = (unsigned long)OUTPUT_SAMPLE_FORMAT;
		m_outputData->isPlaying = &m_isPlaying;
		m_outputData->isPaused = &m_isPaused;
		m_outputData->isStoped = &m_isStoped;
		m_outputData->isRecording = &m_isRecording;
		m_outputData->playVolume = &m_playVolume;
		m_outputData->recVolume = &m_recVolume;
      m_outputData->playMode = play;

      delete wf;

      PaStreamParameters outputParam;
      outputParam.device			= m_selectedOutput;
      outputParam.channelCount			= m_outputData->channels;
      outputParam.sampleFormat			= m_outputData->sampleFormat;
      outputParam.suggestedLatency		= Pa_GetDeviceInfo(outputParam.device)->defaultLowOutputLatency;
      outputParam.hostApiSpecificStreamInfo	= NULL;

      m_paErr = Pa_OpenStream(&m_stream,
				   NULL,
				   &outputParam,
				   (double)m_outputData->samplerate,
				   (unsigned long)DEFAULT_SAMPLES_PER_BUFFER,
				   paClipOff,
				   AudioDevices::AudioCallBack,
				   m_outputData);
		if (m_paErr != paNoError)
			std::cerr << Pa_GetErrorText(m_paErr) << std::endl;

		m_isPlaying = TRUE;
		m_paErr = Pa_StartStream(m_stream);
		if (m_paErr != paNoError)
		{
			m_isPlaying = FALSE;
			std::cerr << Pa_GetErrorText(m_paErr) << std::endl;
		}		
	}
	return (TRUE);
}

bool	AudioDevices::Stop(void)
{
	if (m_stream)
	{
		m_paErr = Pa_StopStream(m_stream);
		if (m_paErr != paNoError)
			std::cerr << Pa_GetErrorText(m_paErr) << std::endl;
			
		m_isStoped = TRUE;
		m_isPlaying = FALSE;
		m_isRecording = FALSE;
		m_paErr = Pa_CloseStream(m_stream);
		if (m_paErr != paNoError)
			std::cerr << Pa_GetErrorText(m_paErr) << std::endl;
	}
	if (m_outputData)
		m_outputData->bufferPos = 0;
		
	if (m_inputData)
		m_inputData->bufferPos = 0;

	return (TRUE);
}

bool    AudioDevices::Pause(void)
{
	if (m_stream)
    {
		m_paErr = Pa_StopStream(m_stream);
		if (m_paErr != paNoError)
			std::cerr << Pa_GetErrorText(m_paErr) << std::endl;

		m_isPaused = TRUE;
		m_isPlaying = FALSE;
    }
	return (TRUE);
}

bool	AudioDevices::Rec(const Glib::ustring &outFile, int sec)
{
	WaveFile *wf = NULL;
	wf = new WaveFile;

  int samplerate = (int)DEFAULT_SAMPLE_RATE;
  int num_channels = (int)DEFAULT_CHANNELS;
  int total_frames = sec * samplerate;
  wf->sfinfo.frames = total_frames;
  wf->sfinfo.channels = num_channels;
  wf->sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;
  wf->sfinfo.samplerate = samplerate;
  wf->Open(outFile, wf->o_mode_w);
  sf_command(wf->sffile, SFC_SET_UPDATE_HEADER_AUTO, NULL, SF_TRUE);
  delete[] m_tmpBuffer;
  m_tmpBuffer = new WORK_SOUND_BUFFER[total_frames * num_channels];
  delete m_inputData;
  m_inputData = NULL;
  m_inputData = new callback_t;
  m_inputData->buffer = m_tmpBuffer;
  m_inputData->frames = total_frames;
  m_inputData->samplerate = samplerate;
  m_inputData->channels =  num_channels;
  m_inputData->format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;
  m_inputData->sections = wf->sfinfo.sections;
  m_inputData->seekable = wf->sfinfo.seekable;
  m_inputData->bufferLen = total_frames * num_channels;
  m_inputData->bufferPos = 0;
  m_inputData->inputDevice = m_selectedInput;
  m_inputData->outputDevice = m_selectedOutput;
  m_inputData->sampleFormat = (unsigned long)INPUT_SAMPLE_FORMAT;
  m_inputData->isPlaying = &m_isPlaying;
  m_inputData->isPaused = &m_isPaused;
  m_inputData->isStoped = &m_isStoped;
  m_inputData->isRecording = &m_isRecording;
  m_inputData->playVolume = &m_playVolume;
  m_inputData->recVolume = &m_recVolume;
  m_inputData->playMode = rec;

  PaStreamParameters inputParam;
  inputParam.device			= m_selectedInput;
  inputParam.channelCount		= (int)m_inputData->channels;
  inputParam.sampleFormat		= (unsigned long)INPUT_SAMPLE_FORMAT;
  inputParam.suggestedLatency		= Pa_GetDeviceInfo(inputParam.device)->defaultLowOutputLatency;;
  inputParam.hostApiSpecificStreamInfo	= NULL;

  m_paErr = Pa_OpenStream(&m_stream,
			       &inputParam,
			       NULL,
			       (double)m_inputData->samplerate,
			       (unsigned long)DEFAULT_SAMPLES_PER_BUFFER,
			       paClipOff,
			       AudioDevices::AudioCallBack,
			       m_inputData);
  if (m_paErr != paNoError)
    {
      std::cerr << Pa_GetErrorText(m_paErr) << std::endl;
    }

  m_isRecording = TRUE;
  m_paErr = Pa_StartStream(m_stream);
  if (m_paErr != paNoError)
    {
      std::cerr << Pa_GetErrorText(m_paErr) << std::endl;
      m_isRecording = FALSE;
    }

  while ( Pa_IsStreamActive(m_stream) )
    Pa_Sleep(50);

  m_isRecording = FALSE;
  wf->WriteStreamFrames(wf->sffile, m_tmpBuffer, total_frames, wf->dt_float);
  delete wf;

  return (TRUE);
}

bool	AudioDevices::PlayRec(Glib::ustring &inFile, Glib::ustring &outFile)
{
  (void) inFile;
  (void) outFile;
  return (TRUE);
}

PaHostApiIndex	AudioDevices::GetHostApiCount(void)
{
  return (Pa_GetHostApiCount());
}

PaDeviceIndex	AudioDevices::GetTotalDeviceCount(void)
{
  return (Pa_GetDeviceCount());
}

Glib::ustring	AudioDevices::GetDeviceName(const PaDeviceInfo *info)
{
  Glib::ustring	res;
  Glib::ustring	hostapiName(Pa_GetHostApiInfo(info->hostApi)->name);
  Glib::ustring	sep(": ");
  Glib::ustring	infoName(info->name);
  res = hostapiName + sep + infoName;

  return (res);
}

void	AudioDevices::MapAudioDevices(void)
{
  if (this->GetTotalDeviceCount() < 0)
    return;

  if (m_allDev)
      delete m_allDev;

  m_allDev = new device_list_t;
  if (!m_allDev)
      std::cerr << "Can't allocate memory to \"m_dev\" pointer !!!" << std::endl;
  else
    {
      const PaDeviceInfo	*devInfo; 

      for (int i = 0; i < this->GetTotalDeviceCount(); ++i)
	{
	  devInfo = Pa_GetDeviceInfo(i);
	  m_allDev->insert( std::make_pair((PaDeviceIndex)i, this->GetDeviceName(devInfo)) );
	}
    }

  return;
}

void	AudioDevices::MapInputOutputDevices(void)
{
  if (this->GetTotalDeviceCount() < 0)
    return;

  if (m_allInputDev)
    delete m_allInputDev;

  m_allInputDev = new device_list_t;

  if (m_allOutputDev)
    delete m_allOutputDev;

  m_allOutputDev = new device_list_t;

  if (!m_allInputDev)
    std::cerr << "Can't allocate memory to \"m_inputDev\" pointer !!!" << std::endl;

  if (!m_allOutputDev)
    std::cerr << "Can't allocate memory to \"m_outputDev\" pointer !!!" << std::endl;

  if (m_allInputDev && m_allOutputDev)
    {
      const PaDeviceInfo        *devInfo;
      
      for (int i = 0; i < this->GetTotalDeviceCount(); ++i)
	{
	  devInfo = Pa_GetDeviceInfo(i);
	  
	  if (devInfo->maxInputChannels > 0)
	    m_allInputDev->insert( std::make_pair((PaDeviceIndex)i, this->GetDeviceName(devInfo)) );
	  
	  if (devInfo->maxOutputChannels > 0)
	    m_allOutputDev->insert( std::make_pair((PaDeviceIndex)i, this->GetDeviceName(devInfo)) );
	}
    }
  
    return;
}

bool	AudioDevices::InitAudio(void)
{
  m_paErr = Pa_Initialize();

  if (m_paErr != paNoError)
    m_init = FALSE;
  else
    m_init = TRUE;
 
  return (m_init);
}

bool	AudioDevices::KillAudio(void)
{
  m_paErr = Pa_Terminate();
  
  if (m_paErr != paNoError)
  {
    m_init = TRUE;
    return (FALSE);
  }
  else
    m_init = FALSE;
  
  return (TRUE);
}

device_list_t*	AudioDevices::GetAllDevices(void)
{
  return (m_allDev);
}

device_list_t*	AudioDevices::GetAllInputDevices(void)
{
  return (m_allInputDev);
}

device_list_t*	AudioDevices::GetAllOutputDevices(void)
{
  return (m_allOutputDev);
}

PaDeviceIndex	AudioDevices::GetInputDevice(void)
{
  return (m_selectedInput);
}

void	AudioDevices::SetInputDevice(PaDeviceIndex input)
{
  m_selectedInput = input;
  return;
}

PaDeviceIndex	AudioDevices::GetOutputDevice(void)
{
  return (m_selectedOutput);
}

void	AudioDevices::SetOutputDevice(PaDeviceIndex output)
{
  m_selectedOutput = output;
  return;
}

void	AudioDevices::SetDefaultInOutDevice(void)
{
  m_selectedInput = Pa_GetDefaultInputDevice();
  m_selectedOutput = Pa_GetDefaultOutputDevice();
  return;
}

void	AudioDevices::PrintStreamInfo(const PaStreamInfo *streamInfo)
{
  std::cout << "----- STREAM INFO -----"	<< std::endl;
  std::cout << "Structure version: "		<< streamInfo->structVersion  << std::endl;
  std::cout << "Input latency: "			<< streamInfo->inputLatency  << std::endl;
  std::cout << "Output latency: "			<< streamInfo->outputLatency << std::endl;
  std::cout << "Samplerate: "				<< streamInfo->sampleRate << std::endl;
  return;
}

int	AudioDevices::AudioCallBack(	const void* inputBuffer,
									void* outputBuffer,
									unsigned long framesPerBuffer,
									const PaStreamCallbackTimeInfo *timeInfo,
									PaStreamCallbackFlags statusFlags,
									void* userData	)
{
	if (!userData)
		return (paComplete);

	callback_t*			data			= static_cast<callback_t*>(userData);
	const WORK_SOUND_BUFFER*	input			= static_cast<const WORK_SOUND_BUFFER*>(inputBuffer);
	SOUND_BUFFER*		output			= static_cast<SOUND_BUFFER*>(outputBuffer);
	unsigned long		framesPerCall	= framesPerBuffer;

	(void) timeInfo;	//unused data for now.
	(void) statusFlags;	//unused data for now.
	//(void) input;		//unused data for now.
	/* Perhaps need to enable this variable in global static way.
	double	currentTime		= timeInfo->currentTime;
	double	inputBufferAdcTime	= timeInfo->inputBufferAdcTime;
	double	outputBufferDacTime	= timeInfo->outputBufferDacTime;
	*/

	WORK_SOUND_BUFFER tmp_val;
	unsigned long i;

	if ((data->sampleFormat & OUTPUT_SAMPLE_FORMAT) && (data->playMode == play))
	{
		if (data->format & SF_FORMAT_WAV || data->format & SF_FORMAT_WAVEX || data->format & SF_FORMAT_FLAC)
		{
			for (i = 0; i < (framesPerCall * data->channels); i += data->channels)
			{
				if (data->bufferPos <= data->bufferLen)
				{
					for (int x = 0; x < data->channels; ++x)
					{
						if ((*data->playVolume) < 0.0f || (*data->playVolume) > 1.0f)
							(*data->playVolume) = 0.5f;

						tmp_val = data->buffer[data->bufferPos] * (*data->playVolume);
						if (tmp_val > 1.0f)
							tmp_val = 1.0f;
						else if (tmp_val < (-1.0f))
							tmp_val = -1.0f;

						output[i + x] = (SOUND_BUFFER)(tmp_val * 0x7FFF); // 0x7FFF => 32767
						data->bufferPos++;
					}
				}
				else
				{
					return (paComplete);
				}
			}
		}
      else
		return (paComplete);

	}
	else if ((data->sampleFormat & INPUT_SAMPLE_FORMAT) && (data->playMode == rec))
    {
      if (data->format & (SF_FORMAT_WAV | SF_FORMAT_FLOAT) ||
	  data->format & SF_FORMAT_WAVEX ||
          data->format & SF_FORMAT_FLAC)
        {
	  for (i = 0; i < (framesPerCall * data->channels); i += data->channels)
	    {
	      if (data->bufferPos <= data->bufferLen && (*data->isRecording) == TRUE)
		{
		  for (int x = 0; x < data->channels; ++x)
		    {
                      if ((*data->recVolume) < 0.0f || (*data->recVolume) > 1.0f)
                      	(*data->recVolume) = 1.0f;

		      tmp_val = input[i + x] * (*data->recVolume);
                      if (tmp_val > 1.0f)
                        tmp_val = 1.0f;
                      else if (tmp_val < (-1.0f))
                        tmp_val = -1.0f;

                      //if (output)
                        //output[i + x] = (SOUND_BUFFER)(tmp_val / 0x8000); //0x8000 => 32768
                      data->buffer[data->bufferPos] = tmp_val;
		      data->bufferPos++;
		    }
		}
	      else
		return (paComplete);
	    }
	}
    }

  return (paContinue);
}

extern "C" {
  AudioDevices* AudioDevices_New(void)
  {
    return (new AudioDevices());
  }
  void AudioDevices_Destroy(AudioDevices* p)
  {
    delete p;
  }
}
