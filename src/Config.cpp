/*
** This file is part of OZAXE project.
**
** This class intend to be an object root of all of the classes in OZAXE 
** application.
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/

#include <string>
#include <glib/gstdio.h>
#include <glib/gmessages.h>
#include <glibmm/i18n.h>
#include <glibmm/refptr.h>
#include <glibmm/keyfile.h>
#include <glibmm/fileutils.h>
#include <glibmm/exception.h>

#include "Utils.h"
#include "Config.h"

Config::Config(void)
{
	_configFile = "config.ozaxe";
	#ifdef LINUX
	_configDir = Glib::build_filename(Glib::get_home_dir(), ".config/ozaxe");
	#endif
	#ifdef WINDOWS
	_configDir = Glib::build_filename(Glib::get_home_dir(), "ozaxe");
	#endif
	_configFilePath = Glib::build_filename(_configDir, _configFile);
	LoadConfigFile();
}

Config::~Config(void)
{
	SaveConfigFile();
}

void Config::LoadConfigFile(void)
{
	if (!Glib::file_test(_configDir, Glib::FILE_TEST_IS_DIR))
	{
		g_mkdir(_configDir.c_str(), 0700);
	}
	if (!Glib::file_test(_configFilePath, Glib::FILE_TEST_EXISTS))
	{
		try
		{
			Glib::RefPtr<Glib::IOChannel> ifile = Glib::IOChannel::create_from_file(_configFilePath, "w");
			ifile->close();
		}
		catch (Glib::FileError& e)
		{
			g_error( "%s: %s\n", _("Impossible de créer le fichier de configuration"), e.what().c_str() );
		}
		// Processing Audio configuration
		m_messageRead = false;
		m_audioInput = 0;
		m_audioInputVolume = 0.5;
		m_audioOutput = 0;
		m_audioOutputVolume = 0.5;
		// Processing Message configuration
		m_messagePrint = true;
		this->SaveConfigFile();
	}
	else
	{
		try
		{
			_kf.load_from_file(_configFilePath, Glib::KEY_FILE_NONE);
		}
		catch (Glib::KeyFileError& e)
		{
			g_error( "%s: %s\n", _("Impossible de charger le fichier de configuration"), e.what().c_str() );
		}
		// Processing Audio configuration
		if (_kf.has_group("Audio"))
		{
			if (_kf.has_key("Audio", "message_speak"))
				m_messageRead = _kf.get_boolean("Audio", "message_speak");

			if (_kf.has_key("Audio", "input"))
				m_audioInput = _kf.get_integer("Audio", "input");

			if (_kf.has_key("Audio", "input_volume"))
				m_audioInputVolume = _kf.get_double("Audio", "input_volume");

			if (_kf.has_key("Audio", "output"))
				m_audioOutput = _kf.get_integer("Audio", "output");

			if (_kf.has_key("Audio", "output_volume"))
				m_audioOutputVolume = _kf.get_double("Audio", "output_volume");

		}
		// Processing Message configuration
		if (_kf.has_group("Message Print"))
		{
			if (_kf.has_key("Message Print", "message_print"))
				m_messagePrint = _kf.get_boolean("Message Print", "message_print");
		}
	}
}

void Config::SaveConfigFile(void)
{
	// Processing Audio configuration
	_kf.set_boolean("Audio", "message_speak", m_messageRead);
	_kf.set_integer("Audio", "input", m_audioInput);
	_kf.set_double("Audio", "input_volume", m_audioInputVolume);
	_kf.set_integer("Audio", "output", m_audioOutput);
	_kf.set_double("Audio", "output_volume", m_audioOutputVolume);

	// Processing Message configuration
	_kf.set_boolean("Message Print", "message_print", m_messagePrint);

	try
	{
		Glib::RefPtr<Glib::IOChannel> ifile = Glib::IOChannel::create_from_file(_configFilePath, "w");
		ifile->write(_kf.to_data());
		ifile->close();
	}
	catch (Glib::FileError& e)
	{
		g_error( "%s: %s\n", _("Impossible de sauvegarder le fichier de configuration"), e.what().c_str() );
	}
	catch (Glib::ConvertError& e)
	{
		g_error( "%s: %s\n", _("Impossible de sauvegarder le fichier de configuration"), e.what().c_str() );
	}
}

bool Config::GetMessageRead(void)
{
	return (m_messageRead);
}
void Config::SetMessageRead(bool b)
{
	m_messageRead = b;
}

int  Config::GetAudioInput(void)
{
	return (m_audioInput);
}
void Config::SetAudioInput(int deviceNum)
{
	m_audioInput = deviceNum;
}

double Config::GetAudioInputVolume(void)
{
	return (m_audioInputVolume);
}
void   Config::SetAudioInputVolume(double volume)
{
	m_audioInputVolume = volume;
}

int  Config::GetAudioOutput(void)
{
	return (m_audioOutput);
}
void Config::SetAudioOutput(int deviceNum)
{
	m_audioOutput = deviceNum;
}

double Config::GetAudioOutputVolume(void)
{
	return (m_audioOutputVolume);
}
void   Config::SetAudioOutputVolume(double volume)
{
	m_audioOutputVolume = volume;
}

bool Config::GetMessagePrint(void)
{
	return (m_messagePrint);
}
void Config::SetMessagePrint(bool b)
{
	m_messagePrint = b;
}
