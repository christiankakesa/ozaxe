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

#ifdef WIN32
#	include "WinOSD.h"
#endif //WIN32
#ifdef LINUX
#	include <xosd.h>
#	include <locale.h>
#	include <X11/Xlib.h>
#	include "X11Color.h"
#endif //LINUX


#include "MessageServices.h"

MessageServices::MessageServices(void):m_strName("MessageServices"),
				       m_strDescription("Print message services plugin."),
				       m_strVersion("1.0.0"),
				       m_strAuthorName("Christian KAKESA <christian.kakesa@gmail.com>"),
				       m_width(320),
				       m_lines(2),
				       m_delay(3),
				       m_verticalPos("TOP"),
				       m_horizontalAlign("CENTER"),
				       m_text("OZAXE Message Services")
{
	if(!Glib::thread_supported()) Glib::thread_init();
#ifdef WIN32
	m_colour = "";
#endif //WIN32
#ifdef LINUX
	if (setlocale(LC_ALL, "") == NULL || !XSupportsLocale())
		std::cerr << "Locale not available, expect problems with fonts.\n" << std::endl;	
	m_colour = X11COLOR_DARK_SLATE_GRAY;
	m_font = "-bitstream-bitstream vera serif-bold-*-*-*-*-620-75-75-p-0-*-*";
	//m_font = "-misc-fixed-medium-r-semicondensed--*-480-*-*-c-*-*-*";
#endif //LINUX
}

MessageServices::~MessageServices(void)
{
	;
}

const Glib::ustring& MessageServices::GetName(void) const
{
	return (m_strName);
}

const Glib::ustring& MessageServices::GetDescription(void) const
{
	return (m_strDescription);
}

const Glib::ustring& MessageServices::GetVersion(void) const
{
	return (m_strVersion);
}

const Glib::ustring& MessageServices::GetAuthorName(void) const
{
	return (m_strAuthorName);
}

int MessageServices::GetWidth(void) const
{
	return (m_width);
}

void MessageServices::SetWidth(const int width)
{
	m_width = width;
}

int MessageServices::GetLines(void) const
{
	return (m_lines);
}

void MessageServices::SetLines(const int lines)
{
	m_lines = lines;
}

int MessageServices::GetDelay(void) const
{
	return (m_delay);
}

void MessageServices::SetDelay(const int delay)
{
	m_delay = delay;
}

Glib::ustring MessageServices::GetVerticalPos(void) const
{
	return (m_verticalPos);
}

void MessageServices::SetVerticalPos(const Glib::ustring verticalPos)
{
	m_verticalPos = verticalPos;
}

Glib::ustring MessageServices::GetHorizontalAlign(void) const
{
	return (m_horizontalAlign);
}

void MessageServices::SetHorizontalAlign(const Glib::ustring horizontalAlign)
{
	m_horizontalAlign = horizontalAlign;
}

Glib::ustring MessageServices::GetText(void) const
{
	return (m_text);
}

void MessageServices::SetText(const Glib::ustring text)
{
	m_text = text;
}

Glib::ustring MessageServices::GetFont(void) const
{
	return (m_font);
}

void MessageServices::SetFont(const Glib::ustring font)
{
	m_font = font;
}

Glib::ustring MessageServices::GetColour(void) const
{
	return (m_colour);
}

void MessageServices::SetColour(const Glib::ustring colour)
{
	m_colour = colour;
}

#ifdef WIN32
void MessageServices::Print(void)
{
	WinOSD* wosd = new WinOSD((::HINSTANCE)NULL);
	// Can configure font, delay, position
	wosd->PrintText(this->GetText());
	delete wosd;
}
int MessageServices::PrintText(const Glib::ustring text)
{
	this->SetText(text);
	this->Print();
	return (0);
}
int MessageServices::PrintText(void)
{
	return (this->PrintText(m_text));
}
int MessageServices::PrintVolume(const int percent)
{
	(void) percent;
	return (0);
}
#endif //WIN32
#ifdef LINUX
void MessageServices::Print(void)
{
	Glib::Mutex::Lock lock(_mutexPrint);	
	xosd* osd = xosd_create(this->GetLines());
	if (!osd)
	{
		std::cerr << "Error on xosd initilization: " << xosd_error << std::endl;
		return;
	}
	xosd_set_font(osd, m_font.c_str());
	xosd_set_colour(osd, m_colour.c_str());

	if (m_verticalPos == "TOP")
		xosd_set_pos(osd, XOSD_top);
	else if (m_verticalPos == "MIDDLE")
		xosd_set_pos(osd, XOSD_middle);
	else
		xosd_set_pos(osd, XOSD_bottom);
 
	if (m_horizontalAlign == "CENTER")
		xosd_set_align(osd, XOSD_center);
	else if (m_horizontalAlign == "RIGHT")
		xosd_set_align(osd, XOSD_right);
	else
		xosd_set_align(osd, XOSD_left);

	Glib::ustring text = this->GetText();
	Glib::ustring title;
	Glib::ustring description(text);
	Glib::ustring::size_type pos = text.find(':');
	if (pos != Glib::ustring::npos)
	{
		title = text.substr(0, pos);
		description = text.substr(pos + 1);
	}
	if (title.empty())
		xosd_display(osd, 0, XOSD_string, description.c_str());
	else
	{
		xosd_display(osd, 0, XOSD_string, title.c_str());
		xosd_display(osd, 1, XOSD_string, description.c_str());
	}
	xosd_set_timeout(osd, m_delay);
	if (xosd_is_onscreen(osd))
		xosd_wait_until_no_display(osd);
  
	xosd_destroy(osd);
}
int MessageServices::PrintText(const Glib::ustring text)
{
	this->SetText(text);
	m_thread = Glib::Thread::create( sigc::mem_fun(*this, &MessageServices::Print), false ) ;
	return (0);
}
int MessageServices::PrintText(void)
{
	return (this->PrintText(m_text));
}
int MessageServices::PrintVolume(const int percent)
{
	(void) percent;
	return (0);
}
#endif //LINUX

extern "C" {
	MessageServices* MessageServices_New()
	{
		return (new MessageServices());
	}
	void MessageServices_Destroy(MessageServices* p)
	{
		delete p;
	}
}

