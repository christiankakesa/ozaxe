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
#include <glibmm/ustring.h>
#include <glibmm/thread.h>
#include "../../IPluginMessageServices.h"
#ifdef WIN32
#	include "WinOSD.h"
#endif //WIN32
#ifdef LINUX
#	include <xosd.h>
#endif //LINUX

#ifndef __MESSAGESERVICES_H_
#define __MESSAGESERVICES_H_

class PLUGIN_EXPORT MessageServices : public IPluginMessageServices
{
	private:
		const Glib::ustring m_strName;
		const Glib::ustring m_strDescription;
		const Glib::ustring m_strVersion;
		const Glib::ustring m_strAuthorName;
		int m_width;
		int m_lines;
		int m_delay;
		Glib::ustring m_verticalPos;
		Glib::ustring m_horizontalAlign;
		Glib::ustring m_text;
		Glib::ustring m_font;
		Glib::ustring m_colour;

	public:
		Glib::Thread* m_thread;
		Glib::Mutex  _mutexPrint;

	public:
		MessageServices(void);
		virtual ~MessageServices(void);

	public:
		virtual const Glib::ustring& GetName(void) const;
		virtual const Glib::ustring& GetDescription(void) const;
		virtual const Glib::ustring& GetVersion(void) const;
		virtual const Glib::ustring& GetAuthorName(void) const;

		virtual int GetWidth(void) const;
		virtual void SetWidth(const int width);

		virtual int GetLines(void) const;
		virtual void SetLines(const int lines);

		virtual int GetDelay(void) const;
		virtual void SetDelay(const int delay);

		virtual Glib::ustring GetVerticalPos(void) const;
		virtual void SetVerticalPos(const Glib::ustring verticalPos);

		virtual Glib::ustring GetHorizontalAlign(void) const;
		virtual void SetHorizontalAlign(const Glib::ustring horizontalAlign);

		virtual Glib::ustring GetText(void) const;
		virtual void SetText(const Glib::ustring text);

		virtual Glib::ustring GetFont(void) const;
		virtual void SetFont(const Glib::ustring font);

		virtual Glib::ustring GetColour(void) const;
		virtual void SetColour(const Glib::ustring colour);

		virtual int PrintText(const Glib::ustring text);
		virtual int PrintText(void);
		virtual int PrintVolume(const int percent);
		virtual void Print(void);
};
typedef MessageServices* (*messageservices_t)();
typedef void (*messageservices_destroy_t)(MessageServices*);

#endif /* !__MESSAGESSERVICES_H_ */

