/*
** This file is part of OZAXE project.
**
** This class intend to be an object root of all of the classes in OZAXE 
** application.
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/

#ifdef __LINUX__
#	include "LibraryX11.cpp"
#endif // Linux
#ifdef __WIN32__
#	include "LibraryWin32.cpp"
#endif // Win32

