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
#include <glib/gmessages.h>
#include <glibmm/thread.h>
#include <glibmm/ustring.h>
#include <glibmm/spawn.h>
#include <glibmm/shell.h>

#include "Plugins.h"
#include "MessageProcessing.h"

int MessageProcessing::Read(Glib::ustring text)
{
	#ifdef __LINUX__
	std::string sout, serr;
	int exitstat;
	Glib::spawn_command_line_sync(Glib::ustring("/bin/sh ./speak/linux/ozaxe_tts.sh ") + Glib::shell_quote(text), &sout, &serr, &exitstat);
	// FIXME try kind of Glib::sleep(1);
	return exitstat;
	#endif
}

void MessageProcessing::Print(Glib::ustring text, int delay)
{
	MessageServices* pluginMs = static_cast<MessageServices*>(PluginFactory::GetInstance().GetPlugin(PLUGIN_MESSAGESERVICES));
	pluginMs->SetDelay(delay);
	pluginMs->PrintText(static_cast<const Glib::ustring>(text));
	pluginMs = 0;
}
