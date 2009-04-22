/*
** This file is part of OZAXE project.
**
** This class intend to be an object root of all of the classes in OZAXE 
** application.
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/

#include <glibmm/ustring.h>

class MessageProcessing
{
public:
	static int Read(Glib::ustring text);
	static void Print(Glib::ustring text, int delay = 3);
};
