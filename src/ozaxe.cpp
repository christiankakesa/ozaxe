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
#include <glibmm/i18n.h>
#include <glibmm/thread.h>
#include <gtkmm/main.h>
#include <glibmm/ustring.h>

#include "Library.h"
#include "OzaxeInfos.h"
#include "MessageProcessing.h"
#include "MainFrame.h"
#include "Config.h"
#include "ozaxe.h"

Ozaxe::Ozaxe(void) { }

Ozaxe::~Ozaxe(void) { }

int Ozaxe::Run(int ac, char* av[])
{
	if(!Glib::thread_supported()) Glib::thread_init();
	Config& config = Config::GetInstance();
	config.LoadConfigFile();
	if (config.GetMessagePrint())
	{
		Glib::ustring msg = _("Démarrage d'");
		MessageProcessing::Print( msg + APPNAME, 3 );
	}
	Gtk::Main kit(ac, av);
	MainFrame* mf = new MainFrame();
	kit.run( *(mf->m_mainframe) );
	return (0);
}

int main(int ac, char* av[])
{	
	Ozaxe& oz = Ozaxe::GetInstance();
	oz.Run(ac, av);
	
	return (0);
}
