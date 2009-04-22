/*
** This file is part of OZAXE project.
**
** This class intend to be an object root of all of the classes in OZAXE 
** application.
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/

#include <glib/gmessages.h>
#include <glibmm/i18n.h>

#include "plugins/AudioDevices/AudioDevices.h"
#include "plugins/MessageServices/MessageServices.h"
#include "Library.h"
#include "Plugins.h"

PluginFactory::PluginFactory(void)
{
	this->InitPlugins();
}

PluginFactory::~PluginFactory(void)
{
	// AudioDevices
	AudioDevices_Destroy(pAudioDevices);
	pAudioDevices = 0;
	delete pluginAudioDevices;
	// MessageServices
	MessageServices_Destroy(pMessageServices);
	pMessageServices = 0;
	delete pluginMessageServices;
}

void PluginFactory::InitPlugins(void)
{
	// AudioDevices	
	pluginAudioDevices = new Library();
	if (!pluginAudioDevices->Load(PLUGIN_AUDIODEVICES))
	{
		g_error( "%s: %s %s\n", _("Impossible de charger la librarie"), ": ", PLUGIN_AUDIODEVICES );
		return;
	}
	else
	{
		AudioDevices_New = reinterpret_cast<audiodevices_t>(pluginAudioDevices->GetAddr("AudioDevices_New"));
		AudioDevices_Destroy = reinterpret_cast<audiodevices_destroy_t>(pluginAudioDevices->GetAddr("AudioDevices_Destroy"));
		pAudioDevices = AudioDevices_New();
	}

	// MessageServices	
	pluginMessageServices = new Library();
	if (!pluginMessageServices->Load(PLUGIN_MESSAGESERVICES))
	{
		g_error( "%s: %s %s\n",_("Impossible de charger la librarie"), ": ", PLUGIN_MESSAGESERVICES );
		return;
	}
	else
	{
		MessageServices_New = reinterpret_cast<messageservices_t>(pluginMessageServices->GetAddr("MessageServices_New"));
		MessageServices_Destroy = reinterpret_cast<messageservices_destroy_t>(pluginMessageServices->GetAddr("MessageServices_Destroy"));
		pMessageServices = MessageServices_New();
	}
}



void* PluginFactory::GetPlugin(const Glib::ustring name)
{
	if (name.compare(PLUGIN_AUDIODEVICES) == 0)
		return (pAudioDevices);
	else if (name.compare(PLUGIN_MESSAGESERVICES) == 0)
		return (pMessageServices);
	else
		return (0);
}
