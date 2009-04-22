/*
** This file is part of OZAXE project.
**
** 
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/

#ifndef __LIBRARYX11_H_
#define __LIBRARYX11_H_

# include <map>
# include <glibmm/ustring.h>

# include "ILibrary.h"

class Library : public ILibrary
{
public:
	Library(void);
	~Library(void);

public:
	bool IsLoaded(void) const;
	bool Load(const Glib::ustring& strLibPath);
	bool UnLoad(void);
	void* GetAddr(const Glib::ustring& strSymbol);

private:
	typedef std::map<Glib::ustring, void*> symbol_addr_t;
	void* _pHandle;
	symbol_addr_t _saMap;
};

#endif /* !__OZAXELIB_X11_SYSTEM_LIBRARY_H_ */
