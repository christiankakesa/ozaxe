/*
** This file is part of OZAXE project.
**
** This class intend to be an object root of all of the classes in OZAXE
** application.
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/
#ifndef __IPLUGINMESSAGESERVICES_H_
#define __IPLUGINMESSAGESERVICES_H_

#include <iostream>
#include <glibmm/ustring.h>

#include "IPlugin.h"

class PLUGIN_EXPORT IPluginMessageServices : virtual public IPlugin
{
public:
	IPluginMessageServices(void) { }
	virtual ~IPluginMessageServices(void) { }

public:
	virtual int GetWidth(void) const = 0;
	virtual void SetWidth(const int width) = 0;
	virtual int GetLines(void) const = 0;
	virtual void SetLines(const int lines) = 0;
	virtual int GetDelay(void) const = 0;
	virtual void SetDelay(const int lines) = 0;
	virtual Glib::ustring GetVerticalPos(void) const = 0;
	virtual void SetVerticalPos(const Glib::ustring verticalPos) = 0;
	virtual Glib::ustring GetHorizontalAlign(void) const = 0;
	virtual void SetHorizontalAlign(const Glib::ustring horizontalAlign) = 0;
	virtual Glib::ustring GetText(void) const = 0;
	virtual void SetText(const Glib::ustring text) = 0;
	virtual Glib::ustring GetFont(void) const = 0;
	virtual void SetFont(const Glib::ustring font) = 0;
	virtual Glib::ustring GetColour(void) const = 0;
	virtual void SetColour(const Glib::ustring colour) = 0;
	virtual int PrintText(const Glib::ustring text) = 0;
	virtual int PrintText(void) = 0;
	virtual int PrintVolume(const int percent) = 0;
};

#endif /* !__IPLUGINMESSAGESERVICES_H_ */

