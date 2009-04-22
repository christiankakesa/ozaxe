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
#include <glib/gmessages.h>
#include <libglademm.h>
#include <glibmm/i18n.h>
#include <glibmm/refptr.h>
#include <gtkmm/window.h>
#include <gdkmm/pixbuf.h>
#include <gtkmm/table.h>
#include <gtkmm/button.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/combobox.h>
#include <gtkmm/scale.h>
#include <gtkmm/liststore.h>
#include <gtkmm/stock.h>

#include "OzaxeInfos.h"
#include "Config.h"
#include "Plugins.h"
#include "PrefsFrame.h"

PrefsFrame::PrefsFrame(Gtk::Window* parent):_config(Config::GetInstance())
{
	m_parentWindow = parent;
	_config.LoadConfigFile();
	this->InitWidgets();
}

PrefsFrame::~PrefsFrame(void)
{
	_config.SaveConfigFile();
	pluginAd = 0;
	delete m_table;
	delete m_msgprintBTN;
	delete m_audioinputBTN;
	delete m_audioinputvolumeBTN;
	delete m_audiooutputBTN;
	delete m_audiooutputvolumeBTN;
	delete m_cancelBTN;
}

void PrefsFrame::InitWidgets(void)
{
	pluginAd = static_cast<AudioDevices*>(PluginFactory::GetInstance().GetPlugin(PLUGIN_AUDIODEVICES));
	pluginAd->SetDefaultInOutDevice();
	int win_w, win_h;
	m_parentWindow->get_size(win_w, win_h);
	set_title( _("Préférences") );
	set_gravity(Gdk::GRAVITY_NORTH_WEST);
	set_icon_from_file("ui/images/ozaxeico.png");
	set_default_size(CHILD_WINDOW_W, CHILD_WINDOW_H);
	set_resizable(false);
	set_transient_for(*m_parentWindow);
	set_modal(true);
	move(win_w+15, 0);
	signal_delete_event().connect(sigc::mem_fun(*this, &PrefsFrame::on_delete_event));

	Glib::RefPtr<Gnome::Glade::Xml> refXml;
	refXml = Gnome::Glade::Xml::create("ui/prefsframe.glade");
	
	refXml->reparent_widget("layout", *this);
	refXml->get_widget("layout", m_table);
	m_table->show_all();

	refXml->get_widget("msgprintBTN", m_msgprintBTN);
	if (_config.GetMessagePrint())
		m_msgprintBTN->set_active(true);
	m_msgprintBTN->signal_clicked().connect(sigc::mem_fun(*this, &PrefsFrame::on_msgprintBTN_clicked));

	refXml->get_widget("msgreadBTN", m_msgreadBTN);
	if (_config.GetMessageRead())
		m_msgreadBTN->set_active(true);
	m_msgreadBTN->signal_clicked().connect(sigc::mem_fun(*this, &PrefsFrame::on_msgreadBTN_clicked));

	refXml->get_widget("audioinputBTN", m_audioinputBTN);
	m_audioinputStore = Gtk::ListStore::create(audioinput_columns);
	m_audioinputBTN->set_model(m_audioinputStore);
	Gtk::TreeModel::Row row;
	device_list_t::iterator iter;
	for ( iter = pluginAd->GetAllInputDevices()->begin(); iter != pluginAd->GetAllInputDevices()->end(); ++iter )
	{
		row = *(m_audioinputStore->append());
		row[audioinput_columns.value] = iter->first;
		row[audioinput_columns.name] = iter->second;
		if (iter->first == _config.GetAudioInput())
			m_audioinputBTN->set_active(row);
	}
	m_audioinputBTN->pack_start(audioinput_columns.value);
	m_audioinputBTN->pack_start(audioinput_columns.name);
	m_audioinputBTN->signal_changed().connect(sigc::mem_fun(*this, &PrefsFrame::on_audioinputBTN_changed));

	refXml->get_widget("audioinputvolumeBTN", m_audioinputvolumeBTN);
	m_audioinputvolumeBTN->set_value(_config.GetAudioInputVolume()*10);
	m_audioinputvolumeBTN->signal_value_changed().connect(sigc::mem_fun(*this, &PrefsFrame::on_audioinputvolumeBTN_value_changed));

	refXml->get_widget("audiooutputBTN", m_audiooutputBTN);
	m_audiooutputStore = Gtk::ListStore::create(audiooutput_columns);
	m_audiooutputBTN->set_model(m_audiooutputStore);
	for ( iter = pluginAd->GetAllOutputDevices()->begin(); iter != pluginAd->GetAllOutputDevices()->end(); ++iter )
	{
		row = *(m_audiooutputStore->append());
		row[audiooutput_columns.value] = iter->first;
		row[audiooutput_columns.name] = iter->second;
		if (iter->first == _config.GetAudioOutput())
			m_audiooutputBTN->set_active(row);
	}
	m_audiooutputBTN->pack_start(audiooutput_columns.value);
	m_audiooutputBTN->pack_start(audiooutput_columns.name);
	m_audiooutputBTN->signal_changed().connect(sigc::mem_fun(*this, &PrefsFrame::on_audiooutputBTN_changed));

	refXml->get_widget("audiooutputvolumeBTN", m_audiooutputvolumeBTN);
	m_audiooutputvolumeBTN->set_value(_config.GetAudioOutputVolume()*10);
	m_audiooutputvolumeBTN->signal_value_changed().connect(sigc::mem_fun(*this, &PrefsFrame::on_audiooutputvolumeBTN_value_changed));

	refXml->get_widget("cancelBTN", m_cancelBTN);
	m_cancelBTN->signal_clicked().connect(sigc::mem_fun(*this, &PrefsFrame::on_cancelBTN_clicked));
}

bool PrefsFrame::on_delete_event(GdkEventAny*)
{
	hide();
	return (true);
}

void PrefsFrame::on_msgprintBTN_clicked(void)
{
	if (m_msgprintBTN->get_active())
		_config.SetMessagePrint(true);
	else
		_config.SetMessagePrint(false);
}

void PrefsFrame::on_msgreadBTN_clicked(void)
{
	if (m_msgreadBTN->get_active())
		_config.SetMessageRead(true);
	else
		_config.SetMessageRead(false);
}

void PrefsFrame::on_audioinputBTN_changed(void)
{
	Gtk::TreeModel::iterator iter = m_audioinputBTN->get_active();
	if(iter)
	{
		Gtk::TreeModel::Row row = *iter;
		if(row)
			_config.SetAudioInput(row[audioinput_columns.value]);
	}
}

void PrefsFrame::on_audioinputvolumeBTN_value_changed(void)
{
	_config.SetAudioInputVolume(m_audioinputvolumeBTN->get_value()/10);
}

void PrefsFrame::on_audiooutputBTN_changed(void)
{
	Gtk::TreeModel::iterator iter = m_audiooutputBTN->get_active();
	if(iter)
	{
		Gtk::TreeModel::Row row = *iter;
		if(row)
			_config.SetAudioOutput(row[audiooutput_columns.value]);
	}
}

void PrefsFrame::on_audiooutputvolumeBTN_value_changed(void)
{
	_config.SetAudioOutputVolume(m_audiooutputvolumeBTN->get_value()/10);
}

void PrefsFrame::on_cancelBTN_clicked(void)
{
	hide();
}

