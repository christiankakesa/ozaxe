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
#include <vector>
#include <string>
#include <glib/gmessages.h>
#include <libglademm.h>
#include <glibmm/i18n.h>
#include <glibmm/thread.h>
#include <glibmm/refptr.h>
#include <gdkmm/pixbuf.h>
#include <gtkmm/window.h>
#include <gtkmm/table.h>
#include <gtkmm/textview.h>
#include <gtkmm/button.h>
#include <gtkmm/filechooserbutton.h>

#include "OzaxeInfos.h"
#include "Config.h"
#include "Utils.h"
#include "MessageProcessing.h"
#include "SynthesisFrame.h"

SynthesisFrame::SynthesisFrame(Gtk::Window* parent):_config(Config::GetInstance())
{
	m_parentWindow = parent;
	_config.LoadConfigFile();
	m_voiceRecognitionStatus = false;
	this->InitWidgets();
	if (_config.GetMessagePrint())
		MessageProcessing::Print( Glib::ustring( _("Démarrage de la synthèse vocale") ), 3 );
	if (_config.GetMessageRead())
		MessageProcessing::Read( Glib::ustring( _("Démarrage de la synthèse vocale") ) );
}

SynthesisFrame::~SynthesisFrame(void)
{
	_config.SaveConfigFile();
	delete m_table;
	delete m_text;
	delete m_readTextBTN;
	delete m_clearTextBTN;
	delete m_cancelBTN;
	delete m_voiceRecoBTN;
	delete m_filechooserBTN;
}

void SynthesisFrame::InitWidgets(void)
{
	int win_w, win_h;
	m_parentWindow->get_size(win_w, win_h);
	set_title( _("Synthèse vocale") );
	set_gravity(Gdk::GRAVITY_NORTH_WEST);
	set_icon_from_file("ui/images/ozaxeico.png");
	set_default_size(CHILD_WINDOW_W, CHILD_WINDOW_H);
	set_resizable(false);
	set_transient_for(*m_parentWindow);
	set_modal(true);
	move(win_w+15, 0);
	signal_delete_event().connect(sigc::mem_fun(*this, &SynthesisFrame::on_delete_event));

	Glib::RefPtr<Gnome::Glade::Xml> refXml;
	refXml = Gnome::Glade::Xml::create("ui/synthesisframe.glade");
	
	refXml->reparent_widget("layout", *this);
	refXml->get_widget("layout", m_table);
	m_table->show_all();

	refXml->get_widget("text", m_text);
	//Targets:
	std::list<Gtk::TargetEntry> listTargets;
	listTargets.push_back( Gtk::TargetEntry("text/uri-list", Gtk::TARGET_OTHER_APP) );
	listTargets.push_back( Gtk::TargetEntry("UTF8_STRING", Gtk::TARGET_OTHER_APP) );
	m_text->drag_dest_set(	listTargets,
				Gtk::DEST_DEFAULT_ALL,
				Gdk::DragAction( GDK_ACTION_COPY | GDK_ACTION_MOVE | GDK_ACTION_LINK ) );
	m_text->signal_drag_data_received().connect(sigc::mem_fun(*this, &SynthesisFrame::on_text_drop_drag_data_received) );
	
	refXml->get_widget("readTextBTN", m_readTextBTN);
	m_readTextBTN->signal_clicked().connect(sigc::mem_fun(*this, &SynthesisFrame::on_readTextBTN_clicked));

	refXml->get_widget("clearTextBTN", m_clearTextBTN);
	m_clearTextBTN->signal_clicked().connect(sigc::mem_fun(*this, &SynthesisFrame::on_clearTextBTN_clicked));

	refXml->get_widget("cancelBTN", m_cancelBTN);
	m_cancelBTN->signal_clicked().connect(sigc::mem_fun(*this, &SynthesisFrame::on_cancelBTN_clicked));

	refXml->get_widget("voiceRecoBTN", m_voiceRecoBTN);
	m_voiceRecoBTN->set_sensitive(false);
	m_voiceRecoBTN->signal_clicked().connect(sigc::mem_fun(*this, &SynthesisFrame::on_voiceRecoBTN_clicked));

	refXml->get_widget("filechooserBTN", m_filechooserBTN);
	Gtk::FileFilter filter_text;
	filter_text.set_name( _("Fichiers textes") );
	filter_text.add_mime_type("text/plain");
	m_filechooserBTN->add_filter(filter_text);
	m_filechooserBTN->signal_selection_changed().connect(sigc::mem_fun(*this, &SynthesisFrame::on_filechooserBTN_selection_changed));
}

void SynthesisFrame::ReadText(const Glib::ustring text)
{
	Glib::Mutex::Lock lock(_textReadMutex);
	if (_config.GetMessagePrint())
		MessageProcessing::Print( Glib::ustring( _("Lecture de texte en cours") ), 3 );
	if (_config.GetMessageRead())
		MessageProcessing::Read( Glib::ustring( _("Lecture de texte en cours") ) );

	MessageProcessing::Read(text);
}

bool SynthesisFrame::GetVoiceRecognitionStatus(void)
{
	return (m_voiceRecognitionStatus);
}

void SynthesisFrame::SetVoiceRecognitionStatus(bool b)
{
	m_voiceRecognitionStatus = b;
}

void SynthesisFrame::on_readTextBTN_clicked(void)
{
	if (m_text->get_buffer()->get_text() != "")
	{
		m_thread = Glib::Thread::create( sigc::bind<const Glib::ustring>( sigc::mem_fun( *this, &SynthesisFrame::ReadText ), m_text->get_buffer()->get_text() ), false ) ;
		// FIXME: Save the text read in StringVector or StringBuffer for logging function and user facilities.
	}
	else
	{
		if (_config.GetMessagePrint())
			MessageProcessing::Print( Glib::ustring( _("Aucun text à lire") ), 3 );
		if (_config.GetMessageRead())
			MessageProcessing::Read( Glib::ustring( _("Aucun text à lire") ) );
	}
}

void SynthesisFrame::on_clearTextBTN_clicked(void)
{
	m_text->get_buffer()->set_text("");
	#ifdef __LINUX__
	std::string sout, serr;
	int exitstat;
	Glib::spawn_command_line_sync(Glib::ustring("killall -HUP mbrola"), &sout, &serr, &exitstat);
	#elif __MACX__
	// Stop the text synthesis engine
	#elif __WIN32__
	// Stop the text synthesis engine
	#endif
}

void SynthesisFrame::on_cancelBTN_clicked(void)
{
	hide();
}

void SynthesisFrame::on_voiceRecoBTN_clicked(void)
{
	if (!this->GetVoiceRecognitionStatus()) // Ready to start voice recognition
	{
		// start voice recognition daemon
		this->SetVoiceRecognitionStatus(true); // Update the voice status flag
		m_voiceRecoBTN->set_label( _("Arrêter la Reconnaissance") );
		if (_config.GetMessagePrint())
			MessageProcessing::Print( Glib::ustring( _("Reconnaissance vocale démarré") ), 3 );
		if (_config.GetMessageRead())
			MessageProcessing::Read( Glib::ustring( _("Reconnaissance vocale démarré") ) );
	}
	else // Need to be stoped
	{
		// stop of the voice recognition daemon
		this->SetVoiceRecognitionStatus(false); // Update the voice status flag
		m_voiceRecoBTN->set_label( _("Démarrer la Reconnaissance") );
		if (_config.GetMessagePrint())
			MessageProcessing::Print( Glib::ustring( _("Reconnaissance vocale arrêté") ), 3 );
		if (_config.GetMessageRead())
			MessageProcessing::Read( Glib::ustring( _("Reconnaissance vocale arrêté") ) );
	}
}

void SynthesisFrame::on_filechooserBTN_selection_changed(void)
{
	try
	{
		Glib::ustring textData = Glib::file_get_contents(m_filechooserBTN->get_filename());
		m_text->get_buffer()->set_text(textData);
	}
	catch (Glib::FileError& e)
	{
		Utils::display_error( *this, e.what() );
	}
}

void SynthesisFrame::on_text_drop_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int, int, const Gtk::SelectionData& selection_data, guint, guint time)
{
	if((selection_data.get_length() >= 0) && (selection_data.get_format() == 8))
	{
		if (selection_data.get_data_type() == "text/uri-list")
		{
			std::vector<std::string> files = selection_data.get_uris();
			m_text->get_buffer()->set_text("");
			for(std::vector<std::string>::iterator iter = files.begin(); iter != files.end(); ++iter)
			{
				try
				{
					Glib::ustring txt;
					Glib::RefPtr<Glib::IOChannel> ifile = Glib::IOChannel::create_from_file(Glib::filename_from_uri(*iter), "r");
					ifile->read_to_end(txt);
					ifile->close();
					m_text->get_buffer()->set_text(m_text->get_buffer()->get_text() + txt);
					if (iter != files.end())
						m_text->get_buffer()->set_text(m_text->get_buffer()->get_text() + "\n\n");
				}
				catch (Glib::ConvertError& e)
				{
					Utils::display_error( *this, e.what() );
				}
				catch (Glib::FileError& e)
				{
					Utils::display_error( *this, e.what() );
				}
				catch (Glib::IOChannelError& e)
				{
					Utils::display_error( *this, e.what() );
				}
			}
			context->drag_finish(true, true, time);
			return;
		}
		else if (selection_data.get_data_type() == "UTF8_STRING")
		{
			m_text->get_buffer()->set_text(selection_data.get_data_as_string());
		}
		else
		{
			Glib::ustring msg = _("Type de fichier non reconnu");
			Utils::display_error( *this, msg + ": " + selection_data.get_data_type() );
		}
	}
	context->drag_finish(false, true, time);
}
