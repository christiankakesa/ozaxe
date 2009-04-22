/*
** This file is part of OZAXE project.
**
** This class intend to be an object root of all of the classes in OZAXE 
** application.
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/

#ifndef __PREFSFRAME_H_
#define __PREFSFRAME_H_

#include <iostream>
#include <libglademm.h>
#include <gtkmm/window.h>
#include <gtkmm/table.h>
#include <gtkmm/button.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/liststore.h>
#include <gtkmm/combobox.h>
#include <gtkmm/scale.h>

#include "Config.h"
#include "Plugins.h"

class PrefsFrame : public Gtk::Window
{
public:
	PrefsFrame(Gtk::Window* parent);
	virtual ~PrefsFrame(void);

public:	
	void InitWidgets(void);
	
	virtual bool on_delete_event(GdkEventAny*);
	virtual void on_msgprintBTN_clicked(void);
	virtual void on_msgreadBTN_clicked(void);
	virtual void on_audioinputBTN_changed(void);
	virtual void on_audioinputvolumeBTN_value_changed(void);
	virtual void on_audiooutputBTN_changed(void);
	virtual void on_audiooutputvolumeBTN_value_changed(void);
	virtual void on_cancelBTN_clicked(void);
	
public:
	AudioDevices*		pluginAd;
	Config&			_config;
	Gtk::Window*		m_parentWindow;
	Gtk::Table*		m_table;
	Gtk::CheckButton*	m_msgprintBTN;
	Gtk::CheckButton*	m_msgreadBTN;
	Gtk::ComboBox*		m_audioinputBTN;
	class AudioInputColumns : public Gtk::TreeModel::ColumnRecord
	{
	public:
		AudioInputColumns() { add(value); add(name); };
		Gtk::TreeModelColumn<int> value;
		Gtk::TreeModelColumn<Glib::ustring> name;
	} audioinput_columns;
	Glib::RefPtr<Gtk::ListStore> m_audioinputStore;
	Gtk::HScale*		m_audioinputvolumeBTN;
	Gtk::ComboBox*		m_audiooutputBTN;
	class AudioOutputColumns : public Gtk::TreeModel::ColumnRecord
	{
	public:
		AudioOutputColumns() { add(value); add(name); };
		Gtk::TreeModelColumn<int> value;
		Gtk::TreeModelColumn<Glib::ustring> name;
	} audiooutput_columns;
	Glib::RefPtr<Gtk::ListStore> m_audiooutputStore;
	Gtk::HScale*		m_audiooutputvolumeBTN;
	Gtk::Button*		m_cancelBTN;
};

#endif /* !__PREFSFRAME_H_ */

