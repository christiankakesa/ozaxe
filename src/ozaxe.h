/*
** This file is part of OZAXE project.
**
** This class intend to be an object root of all of the classes in OZAXE 
** application.
**
** @author Christian KAKESA <christian.kakesa@gmail.com>
** @copyright OZAXE-TEAM and ETNA school (c) 2008.
*/

#ifndef __OZAXE_H_
#define __OZAXE_H_

class Ozaxe
{
private:
	Ozaxe(void);
	virtual ~Ozaxe(void);

public:
	static Ozaxe& GetInstance(void)
	{
		static Ozaxe instance;
		return (instance);
	}
	Ozaxe& operator=(Ozaxe& oz)
	{
		return (oz);
	}
	int Run(int ac, char* av[]);
};

#endif /* !__OZAXE_H_ */
