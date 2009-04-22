/*
** This file is part of OZAXE project.
**
** Library class to load .so and handle it.
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/

#include <iostream>
#include <unistd.h> //for "NULL" define
#include <dlfcn.h>
#include <glibmm/ustring.h>

#include "Error.h"
#include "Library.h"

Library::Library(void):_pHandle(NULL) { }

Library::~Library(void)
{
	UnLoad();
}

bool Library::IsLoaded(void)  const
{
	return (_pHandle ? true : false);
}

bool Library::Load(const Glib::ustring& strLibPath)
{
	bool bRes = true;
	if (_pHandle)
	{
		// TODO : implement OzaxeLibError in order to have a gesture of all error in the whole application.
		// Name of the error : "oleAlreadyLoadedLibrary"
		bRes = false;
	}
	else if (!(_pHandle = ::dlopen(strLibPath.c_str(), RTLD_LAZY|RTLD_GLOBAL)))
	{
		// Name of the error : "oleUnableToLoadLibrary"
		bRes = false;
	}
	return (bRes);
}

bool Library::UnLoad(void)
{
	bool bRes = true;
	::dlerror(); // On fixe a NULL le buffer d'erreur de <dlfcn>
	if (!_pHandle)
	{
		// Name of the error : "oleNoLoadedLibrary"
		bRes = false;
	}
	else if (::dlclose(_pHandle))
	{
		// Name of the error : "oleUnableToUnloadLibrary"
		bRes = false;
	}
	else
		_pHandle = NULL;

	return (bRes);
}

void* Library::GetAddr(const Glib::ustring& strSymbol)
{
	void*			pRes = NULL;
	symbol_addr_t::iterator	it;
	::dlerror(); // We are clean the error buffer <dlfcn>
	if ((it = _saMap.find(strSymbol)) != _saMap.end())
		pRes = it->second;
	else if (!(pRes = ::dlsym(_pHandle, strSymbol.c_str())))
		; // Name of the error : "oleNoSuchSymbolInLibrary"
	else
		_saMap[strSymbol] = pRes;

	return (pRes);
}

