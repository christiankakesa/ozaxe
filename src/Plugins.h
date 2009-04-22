/*
** This file is part of OZAXE project.
**
** This class intend to be an object root of all of the classes in OZAXE 
** application.
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/

#ifndef __PLUGINS_H_
#define __PLUGINS_H_

#include "Library.h"

#include "plugins/AudioDevices/AudioDevices.h"
#include "plugins/MessageServices/MessageServices.h"

#define PLUGIN_AUDIODEVICES "libozaxeplugin_audiodevices.plg"
#define PLUGIN_MESSAGESERVICES "libozaxeplugin_messageservices.plg"

class PluginFactory
{
private:
	PluginFactory(void);
	~PluginFactory(void);

	void InitPlugins(void);

private:
	// AudioDevices
	Library* pluginAudioDevices;
	audiodevices_t AudioDevices_New;
	audiodevices_destroy_t AudioDevices_Destroy;
	AudioDevices* pAudioDevices;
	// MessageServices
	Library* pluginMessageServices;
	messageservices_t MessageServices_New;
	messageservices_destroy_t MessageServices_Destroy;
	MessageServices* pMessageServices;

public:
	static PluginFactory& GetInstance(void)
	{
		static PluginFactory instance;
		return (instance);
	}
	PluginFactory& operator=(PluginFactory& pf)
	{
		return (pf);
	}
	void* GetPlugin(const Glib::ustring name);
};

#endif /* !__PLUGINS_H_ */
