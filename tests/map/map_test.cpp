//
// map.cpp for  in /home/christian/workspace/ozaxe/trunk/src/linux32/tests
// 
// Made by Christian KAKESA
// Login   <christian@epita.fr>
// 
// Started on  Sun Jun  3 17:39:22 2007 Christian KAKESA
// Last update Thu Jun  7 10:46:43 2007 Christian KAKESA
//

#include <iostream>
#include <cstdio>
#include <string>
#include <map>

class Test
{
public:
  std::map<int, std::string> *_m;

public:
  Test(void);
  ~Test(void);
};

Test::Test():_m(NULL)
{
	this->_m = new std::map<int, std::string>;
	this->_m->insert( std::make_pair(1, "Test 1") );
	this->_m->insert( std::make_pair(2, "Test 2") );
	this->_m->insert( std::make_pair(3, "Test 3") );
	this->_m->insert( std::make_pair(4, "Test 4") );
	this->_m->insert( std::make_pair(5, "Test 5") );

	std::map<int, std::string>::iterator iter;
	for ( iter = this->_m->begin(); iter != this->_m->end(); ++iter )
	{
		std::cout << "Device_test # {" << iter->first << " : " << iter->second << "}" << std::endl;
	}
}

Test::~Test()
{
  delete this->_m;
  this->_m = NULL;
}

int	main(int ac, int av)
{
  (void) ac;
  (void) av;
  Test *t = new Test;
  delete t;
  t = NULL;
  return (0);
}
