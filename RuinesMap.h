#pragma once
#include <list>
#include "Body.h"

class RuinesMap
{
public:
	RuinesMap();		
	RuinesMap(int lvl);				//+
	RuinesMap(const RuinesMap&rhs); //+
    void operator=( RuinesMap&rhs); //+
	~RuinesMap();					//+
	void Add(int lvl);
	int Activ( );
	int Draw( );
	void NewMapMan();
	void rMove(Body&x);
	int Move(int x, int y,Body*rhs);
	void test();
	
private:
	int levelSize[15][15];
	std::list<Body>vBody;
	int lvl;
};

