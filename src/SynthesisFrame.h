/*
** This file is part of OZAXE project.
**
** This class intend to be an object root of all of the classes in OZAXE 
** application.
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/

#ifndef __SYNTHESISFRAME_H_
#define __SYNTHESISFRAME_H_

#include <glibmm/thread.h>
#include <gtkmm/window.h>
#include <gtkmm/table.h>
#include <gtkmm/textview.h>
#include <gtkmm/button.h>
#include <gtkmm/filechooserbutton.h>

#include "Config.h"

class SynthesisFrame : public Gtk::Window
{
public:
	SynthesisFrame(Gtk::Window *parent);
	~SynthesisFrame(void);

public:
	void InitWidgets(void);
	void ReadText(const Glib::ustring text);
	bool GetVoiceRecognitionStatus(void);
	void SetVoiceRecognitionStatus(bool b);
	virtual void on_readTextBTN_clicked(void);
	virtual void on_clearTextBTN_clicked(void);
	virtual void on_cancelBTN_clicked(void);
	virtual void on_voiceRecoBTN_clicked(void);
	//virtual void on_filechooserBTN_clicked(void);
	virtual void on_filechooserBTN_selection_changed(void);
	//virtual void on_filechooserBTN_file_activated(void);
	//virtual void on_filechooserBTN_folder_changed(void);
	virtual void on_text_drop_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& selection_data, guint info, guint time);

public:
	Glib::Thread*		m_thread;
	Glib::Mutex		_textReadMutex;
	bool			m_voiceRecognitionStatus;
	Config&			_config;
	Gtk::Window*		m_parentWindow;
	Gtk::Table*		m_table;
	Gtk::TextView*		m_text;
	Gtk::Button*		m_readTextBTN;
	Gtk::Button*		m_clearTextBTN;
	Gtk::Button*		m_cancelBTN;
	Gtk::Button*		m_voiceRecoBTN;
	Gtk::FileChooserButton*	m_filechooserBTN;

private:


};

#endif /* !__SYNTHESISFRAME_H_ */

