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
#include <glibmm/ustring.h>
#include <gtkmm/window.h>
#include <gtkmm/messagedialog.h>

#include "Utils.h"

void Utils::display_error(	Gtk::Window& parent,
				const Glib::ustring& message,
				const Gtk::MessageType type)
{
	Gtk::MessageDialog dlg(parent, message, false, type, Gtk::BUTTONS_OK, true);
	dlg.run();
}

