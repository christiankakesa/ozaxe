/*
** This file is part of OZAXE project.
**
** This class intend to be an object root of all of the classes in OZAXE 
** application.
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/

#ifndef __CONFIG_H_
#define __CONFIG_H_

#include <glibmm/ustring.h>
#include <glibmm/keyfile.h>

class Config
{
private:
	Config(void);
	virtual ~Config(void);

public:	
	Glib::ustring	_configFile;
	Glib::ustring	_configDir;
	Glib::ustring	_configFilePath;
	Glib::KeyFile	_kf;

	bool	m_messageRead;
	int	m_audioInput;
	double	m_audioInputVolume;
	int	m_audioOutput;
	double	m_audioOutputVolume;

	bool	m_messagePrint;

public:
	static Config& GetInstance(void)
	{
		static Config instance;
		return (instance);
	}
	Config& operator=(Config& config)
	{
		return (config);
	}

	void	LoadConfigFile(void);
	void	SaveConfigFile(void);

	bool	GetMessageRead(void);
	void	SetMessageRead(bool b);

	int	GetAudioInput(void);
	void	SetAudioInput(int device);
	
	double	GetAudioInputVolume(void);
	void	SetAudioInputVolume(double volume);
	
	int	GetAudioOutput(void);
	void	SetAudioOutput(int device);
	
	double	GetAudioOutputVolume(void);
	void	SetAudioOutputVolume(double volume);
	
	bool	GetMessagePrint(void);
	void	SetMessagePrint(bool b);
};

#endif /* !__CONFIG_H_ */
