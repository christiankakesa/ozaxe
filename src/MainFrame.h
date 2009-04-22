/*
** This file is part of OZAXE project.
**
** This class intend to be an object root of all of the classes in OZAXE 
** application.
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/

#ifndef __MAINFRAME_H_
#define __MAINFRAME_H_

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/toolbutton.h>

#include "PrefsFrame.h"
#include "SynthesisFrame.h"

class MainFrame
{
public:
	MainFrame(void);
	virtual ~MainFrame(void);

public:	
	void BuildGUI(void);
	virtual void on_synthesisBTN_clicked(void);
	virtual void on_prefsBTN_clicked(void);
	virtual void on_infoBTN_clicked(void);
	virtual void on_exitBTN_clicked(void);

public:
	Gtk::Window*		m_mainframe;
	PrefsFrame*		m_prefsframe;
	SynthesisFrame*		m_synthesisFrame;
	Gtk::VBox*		m_layout;
	Gtk::ToolButton*	m_voiceBTN;
	Gtk::ToolButton*	m_synthesisBTN;
	Gtk::ToolButton*	m_prefsBTN;
	Gtk::ToolButton*	m_infoBTN;
	Gtk::ToolButton*	m_exitBTN;
};

#endif /* !__MAINFRAME_H_ */

