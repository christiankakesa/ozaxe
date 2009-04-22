/*
** This file is part of OZAXE project.
**
** This class intend to be an object root of all of the classes in OZAXE 
** application.
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/

#include <windows.h>
#include <glibmm/ustring.h>

#include "WinOSD.h"

#define WINOSDCLASS ("__transparentwnd__")
#define LWA_COLORKEY    0x00000001
// set the SLWA type
typedef BOOL(WINAPI *SLWA)(HWND, COLORREF, BYTE, DWORD);

Glib::ustring WinOSD::m_text   = "OZAXE IS POWERFULL !!!";
uint32_t WinOSD::m_width       = ::GetSystemMetrics(SM_CXSCREEN);
uint32_t WinOSD::m_height      = 200;
::HFONT WinOSD::m_font         = ::CreateFont(72, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, "Verdana");
uint32_t WinOSD::m_delay       = 5;


WinOSD::WinOSD():m_hWnd(NULL), m_hInst(NULL)
{
    this->m_position.x  = static_cast<uint32_t>((::GetSystemMetrics(SM_CXSCREEN) - WinOSD::m_width) / 2);
    this->m_position.y  = 0; //static_cast<uint32_t>((::GetSystemMetrics(SM_CYSCREEN) - WinOSD::m_height) / 2);
}

WinOSD::~WinOSD()
{
  this->Destroy();
}

bool WinOSD::PrintText()
{
    SLWA SetLayeredWindowAttributes = NULL;
    HINSTANCE hmodUSER32 = LoadLibrary("user32.dll");
    SetLayeredWindowAttributes =(SLWA)GetProcAddress(hmodUSER32, "SetLayeredWindowAttributes");
    // Déclaration et initialisation de la classe de notre fenêtre:
    ::WNDCLASSEX wc;
    memset(&wc, 0, sizeof(wc));
    wc.cbSize           = sizeof(::WNDCLASSEX);
    wc.style            = CS_HREDRAW | CS_VREDRAW;
    wc.hInstance        = this->m_hInst;
    wc.lpfnWndProc      = WinOSD::___WindowProc;
    wc.hCursor          = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground    = (::HBRUSH)::GetStockObject(WHITE_BRUSH);
    wc.lpszClassName    = WINOSDCLASS;
    // Enregistrer la classe de notre fenêtre:
    RegisterClassEx(&wc);
    HWND hWnd = CreateWindowEx( WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TOPMOST ,
                                WINOSDCLASS,
                                0,
                                WS_POPUP,
                                this->m_position.x, this->m_position.y,
                                WinOSD::m_width, WinOSD::m_height,
                                0, 0, this->m_hInst, 0);
    // Choisir la couleur de fond (blanc) comme couleur transparente:
    SetLayeredWindowAttributes(hWnd, RGB(255,255,255), 0, LWA_COLORKEY);
    ::UpdateWindow(hWnd);
    ::ShowWindow(hWnd, SW_SHOW);
    // Boucle des messages:
    MSG msg;
    while(::GetMessage(&msg, 0, 0, 0))
    {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }
    return (EXIT_SUCCESS);
}

bool WinOSD::PrintText(const Glib::ustring text)
{
    WinOSD::m_text = text;
    return (this->PrintText());
}

void WinOSD::Destroy(void)
{
    ::DestroyWindow(this->m_hWnd);
    WinOSD::m_text.clear();
}

void WinOSD::CreateText(HWND hWnd, Glib::ustring text)
{
    WinOSD::m_text = text;
    PAINTSTRUCT ps;
    HDC hdc;
    // Obtenir le HDC de la fenêtre:
    hdc = BeginPaint(hWnd, &ps);
    // Choix de la couleur:
    SetTextColor(hdc, RGB(0, 0, 0));
    // Sélection de notre police:
    SelectObject(hdc, WinOSD::m_font);
    // Déterminer le rectangle d'affichage:
    RECT rc;
    SetRect(&rc, 0, 0, WinOSD::m_width, WinOSD::m_height);
    DrawTextEx(hdc, const_cast<LPTSTR>(text.c_str()), -1, &rc, DT_CENTER, 0);
    // Libérer le HDC de la fenêtre:
    EndPaint(hWnd, &ps);
}

LRESULT CALLBACK WinOSD::___WindowProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uiMsg)
    {
        case WM_CREATE:
            // Création de la police:
            // Initialisation et lancement du timer de raffraichissement:
            ::SetTimer(hWnd, 1, WinOSD::m_delay * 1000,0);
            return 0;
        case WM_PAINT:
            WinOSD::CreateText(hWnd, WinOSD::m_text);
            return 0;
        case WM_TIMER:
            // Forcer le redessin de la fenêtre si elle est visible:
            //if(IsWindowVisible(hWnd)) InvalidateRect(hWnd, 0, 1);
            ShowWindow(hWnd, SW_HIDE);
            SendMessage(hWnd, WM_CLOSE, 0, 0);
            return 0;
        case WM_CLOSE:
            // Détruire notre timer:
            ::KillTimer(hWnd, 1);
            // Détruire notre police
            ::DeleteObject(WinOSD::m_font);
            // Détruire notre fenêtre
            ::DestroyWindow(hWnd);
            break;
        case WM_DESTROY:
            // Envoi du message de sortie du programme:
            PostQuitMessage(0);
            break;
        default:
            break;
    }
    return DefWindowProc(hWnd, uiMsg, wParam, lParam);
}
