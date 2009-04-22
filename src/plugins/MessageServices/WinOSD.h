/*
** This file is part of OZAXE project.
**
** This class intend to be an object root of all of the classes in OZAXE 
** application.
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/

#ifndef __WINOSD_H_
#define __WINOSD_H_
#define _UNICODE
#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <glibmm/ustring.h>

class WinOSD
{
public:
    static Glib::ustring   m_text;
    static uint32_t m_width;
    static uint32_t m_height;
    static ::HFONT  m_font;
    static uint32_t m_delay;
    ::POINT         m_position;
    ::HWND          m_hWnd;
    ::HINSTANCE     m_hInst;

public:
    WinOSD();
    ~WinOSD();

    bool PrintText();
    bool PrintText(const Glib::ustring text);
    void Destroy(void);

/*
    void SetSize(uint32_t x, uint32_t y);
    void SetSize(::SIZE size);
    ::SIZE GetSize(void);

    void SetPosition(const Glib::ustring pos);
    void SetPosition(::POINT point);
    ::POINT GetPosition(void);
*/
    static void CreateText(HWND hWnd, const Glib::ustring text);
    static LRESULT CALLBACK ___WindowProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
};

#endif /* !__WINOSD_H_ */
