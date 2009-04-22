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
#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/aboutdialog.h>
#include <gdkmm/pixbuf.h>
#include <glibmm/refptr.h>
#include <glibmm/ustring.h>

#include "OzaxeInfos.h"
#include "PrefsFrame.h"
#include "Utils.h"
#include "MainFrame.h"

MainFrame::MainFrame(void):	m_mainframe(0),
				m_prefsframe(0),
				m_layout(0),
				m_voiceBTN(0),
				m_synthesisBTN(0),
				m_prefsBTN(0),
				m_infoBTN(0),
				m_exitBTN(0)
{
	this->BuildGUI();
}

MainFrame::~MainFrame(void)
{
	delete m_mainframe;
	delete m_prefsframe;
	delete m_layout;
	delete m_voiceBTN;
	delete m_synthesisBTN;
	delete m_prefsBTN;
	delete m_infoBTN;
	delete m_exitBTN;
}

void MainFrame::BuildGUI(void)
{
	Glib::RefPtr<Gnome::Glade::Xml> refXml;
	refXml = Gnome::Glade::Xml::create("ui/mainframe.glade");
	
	refXml->get_widget("mainframe", m_mainframe);
	m_mainframe->set_icon_from_file("images/ozaxeico.png");
	m_mainframe->move(0, 0);
	m_mainframe->show();

	m_prefsframe = new PrefsFrame(m_mainframe);
	m_synthesisFrame = new SynthesisFrame(m_mainframe);
	
	refXml->get_widget("layout", m_layout);
	
	refXml->get_widget("voiceBTN", m_voiceBTN);

	refXml->get_widget("synthesisBTN", m_synthesisBTN);
	m_synthesisBTN->signal_clicked().connect(sigc::mem_fun(*this, &MainFrame::on_synthesisBTN_clicked));

	refXml->get_widget("prefsBTN", m_prefsBTN);
	m_prefsBTN->signal_clicked().connect(sigc::mem_fun(*this, &MainFrame::on_prefsBTN_clicked));

	refXml->get_widget("infoBTN", m_infoBTN);
	m_infoBTN->signal_clicked().connect(sigc::mem_fun(*this, &MainFrame::on_infoBTN_clicked));

	refXml->get_widget("exitBTN", m_exitBTN);
	m_exitBTN->signal_clicked().connect(sigc::mem_fun(*this, &MainFrame::on_exitBTN_clicked));
}

void MainFrame::on_synthesisBTN_clicked(void)
{
	if (!m_synthesisFrame->is_visible())
		m_synthesisFrame->show();
	else
		m_synthesisFrame->hide();
}

void MainFrame::on_prefsBTN_clicked(void)
{
	if (!m_prefsframe->is_visible())
		m_prefsframe->show();
	else
		m_prefsframe->hide();
}

void MainFrame::on_infoBTN_clicked(void)
{
	int win_w, win_h;
	m_mainframe->get_size(win_w, win_h);	
	Gtk::AboutDialog dlg;
	dlg.set_name(APP);
	dlg.set_version(VERSION);
	dlg.set_comments("OZAXE :: Open Source ACCessibilty Software.");
	dlg.set_website_label("SiteWeb");
	dlg.set_website(OZAXE_WEBSITE);
	dlg.set_copyright(COPYRIGHT);
	
	dlg.set_logo(Gdk::Pixbuf::create_from_file("ui/images/ozaxe.png"));
	//dlg.set_logo_icon_name("ozaxe-logo");
	dlg.set_icon_from_file("ui/images/ozaxeico.png");
	
	std::deque<Glib::ustring> authors;
	authors.push_back("Développeurs:");
	authors.push_back("\tChristian KAKESA <christian.kakesa@gmail.com>");
	authors.push_back("");
	authors.push_back("Contributeurs:");
	authors.push_back("\tAucune");
	
	std::deque<Glib::ustring> artists;
	artists.push_back("Logo:");
	artists.push_back("\tAucune");
	artists.push_back("");
	artists.push_back("Autres éléments graphiques:");
	artists.push_back("\tAucune");
	
	dlg.set_authors(authors);
	dlg.set_artists(artists);
	
	dlg.set_translator_credits(
	        "Traduction anglaise:\n"
	        "\tAucune\n"
	        "\n"
	        "Traduction allemande:\n"
	        "\tAucune\n"
	        "\n"
	        "Traduction espagnole:\n"
	        "\tAucune\n"
	        );

	try
	{
		Glib::ustring license;
		Glib::RefPtr<Glib::IOChannel> ifile = Glib::IOChannel::create_from_file("data/licenses/gpl-3.0.txt", "r");
		ifile->read_to_end(license);
		ifile->close();
		dlg.set_license(license);
	}
	catch (Glib::IOChannelError& e)	
	{
		Utils::display_error( dlg, e.what() );
	}
	catch (Glib::ConvertError& e)
	{
		Utils::display_error( dlg, e.what() );
	}
	dlg.move(win_w+15, 0);

	dlg.run();
}

void MainFrame::on_exitBTN_clicked(void)
{
	Gtk::Main::quit();
}

