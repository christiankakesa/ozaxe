/*
** This file is part of OZAXE project.
**
** This class intend to be an object root of all of the classes in OZAXE
** application.
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/

#ifndef __IPLUGIN_H_
#define __IPLUGIN_H_

#include <glibmm/ustring.h>

#ifdef __WIN32__
#       ifdef PLUGIN_EXPORT
#               undef PLUGIN_EXPORT
#       endif
#       if (defined ALLOW_PLUGIN_EXPORT)
#               define PLUGIN_EXPORT __declspec(dllexport)
#       else
#               define PLUGIN_EXPORT __declspec(dllimport)
#       endif
#else
#       define PLUGIN_EXPORT
#endif

class PLUGIN_EXPORT IPlugin
{
public:
	virtual ~IPlugin(void) { }

public:
	virtual const Glib::ustring&    GetName(void)           const = 0;
	virtual const Glib::ustring&    GetDescription(void)    const = 0;
	virtual const Glib::ustring&    GetVersion(void)        const = 0;
	virtual const Glib::ustring&    GetAuthorName(void)     const = 0;
};

#endif /* !__IPLUGIN_H_ */

