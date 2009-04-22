/*
** This file is part of OZAXE project.
**
** This header describe class implementatin of win32 "Library.cpp".
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/

#ifndef __OZAXELIB_WIN32_SYSTEM_LIBRARY_H_
#define __OZAXELIB_WIN32_SYSTEM_LIBRARY_H_

# define WIN32_LEAN_AND_MEAN // For speed in compilation, include just what we need
# include <windows.h>
# include <glibmm/ustring.h>

# include <ozaxelib/system/api/ILibrary.h>

namespace OzaxeLib
{
  namespace System
  {
    class CLibrary : public API::ILibrary
    {
      public:
        CLibrary(void);
        ~CLibrary(void);

      public:
        bool    IsLoaded(void) const;
        bool    Load(const Glib::ustring& strLibPath);
        bool    UnLoad(void);
        void*   GetAddr(const Glib::ustring& strSymbol);

      private:
        HMODULE _hLib;
    };
  }
}

#endif /* !__OZAXELIB_WIN32_SYSTEM_LIBRARY_H_ */
