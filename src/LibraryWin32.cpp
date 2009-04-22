/*
** This file is part of OZAXE project.
**
** class Library for win32 plateform.
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/

#include <glibmm/ustring.h>

#include "Error.h"
#include "Library.h"

Library::Library():_hLib(NULL)
{;}

Library::~Library()
{
  UnLoad();
}

bool    Library::IsLoaded(void) const
{
  return (_hLib ? true : false);
}

bool    Library::Load(const Glib::ustring& strLibPath)
{
  bool  bRes = true;

  if (_hLib)
  {
    // TODO : implement OzaxeLibError in order to have a gesture of all error in the whole application.
    // Name of the error : "oleAlreadyLoadedLibrary"
    bRes = false;
  }
  else if (!(_hLib = LoadLibrary(strLibPath.c_str())))
  {
    // Name of the error : "oleUnableToLoadLibrary"
    bRes = false;
  }
  return (bRes);
}

bool    Library::UnLoad(void)
{
  bool  bRes = true;

  if (!_hLib)
  {
    // Name of the error : "oleNoLoadedLibrary"
    bRes = false;
  }
  else if (!FreeLibrary(_hLib))
  {
    // Name of the error : "oleUnableToUnloadLibrary"
    bRes = false;
  }
  else
    _hLib = NULL;
  return (bRes);
}

void*   Library::GetAddr(const Glib::ustring& strSymbol)
{
  void* pRes = NULL;

  if(!_hLib)
  {
    // Name of the error : "oleNoLoadedLibrary"
    return (0L);
  }
  else if (!(pRes = (void *)GetProcAddress(_hLib, strSymbol.c_str())))
  {
    return (0L);
  }
  return (pRes);
}
