/*
** This file is part of OZAXE project.
**
** This class intend to be an object root of all of the classes in OZAXE 
** application.
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/
#ifndef __UTILS_H_
#define __UTILS_H_

#include <glibmm/ustring.h>
#include <gtkmm/window.h>
#include <gtkmm/messagedialog.h>

class Utils
{
public:
	static void display_error(	Gtk::Window& parent,
					const Glib::ustring& message,
					const Gtk::MessageType type = Gtk::MESSAGE_ERROR);
};

#endif /* !__UTILS_H_ */

