/*
** This file is part of OZAXE project.
**
** This fie provide to call the appropriate header file for the current 
** plateforme.
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/

#ifndef __LIBRARY_H_
#define __LIBRARY_H_

# ifdef WIN32
#  include "LibraryWin32.h"
# else
#  include "LibraryX11.h"
# endif

#endif /* !__LIBRARY_H_ */

