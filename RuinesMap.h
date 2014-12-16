#pragma once
#include <list>
#include "Body.h"

class RuinesMap
{
public:
	RuinesMap();
	RuinesMap(int lvl);
	RuinesMap(const RuinesMap&rhs);
    void operator=( RuinesMap&rhs);
	~RuinesMap();
	void Add(int lvl);
	int Activ(int flag);
	int Draw(int flag);
	int levelSize[15][15];
private:
	std::list<Body>vBody;
	int lvl;
};

