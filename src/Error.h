/*
** This file is part of OZAXE project.
**
** This content the headers of OzaxeLib::Error namespace.
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/

#ifndef __ERROR_H_
#define __ERROR_H_

#include <glibmm/ustring.h>

#include "ErrorNo.h"

class Error
{
public:
	static Error&  GetInstance(void);

public:
	eErrorNo        GetLastErrorCode(void) const;
	const Glib::ustring&    GetLastErrorText(void) const;

public:
	void    SetLastError(eErrorNo eNo);
	void    operator=(eErrorNo eNo);

private:
	Error(void);
	eErrorNo		_eNo;
	const Glib::ustring	_eText;
};

#endif /* !__OZAXELIB_ERROR_ERROR_H_ */
