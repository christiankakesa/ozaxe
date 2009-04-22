/*
** This file is part of OZAXE project. 
**
** This class provide an interface to implemente load and unload method for 
** .dll or .so loading into OZAXE application.
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/

#ifndef __ILIBRARY_H_
#define __ILIBRARY_H_

class ILibrary
{
public:
	virtual ~ILibrary(void) { }

public:
	virtual bool IsLoaded(void) const = 0;
	virtual bool Load(const Glib::ustring &strLibPath) = 0;
	virtual bool UnLoad(void) = 0;
	virtual void* GetAddr(const Glib::ustring& strSymbol) = 0;
};
#endif /* !__ILIBRARY_H_ */
