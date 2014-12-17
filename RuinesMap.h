#pragma once
#include <vector>
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
	void CreateLvl();
	void SetMyHero(Body&MyLovelyHero);
	void Attack(int x,int y,Body*rhs);
	void WhoDie();
	
private:
	int levelSize[50][50];
	std::vector<Body>vBody;
	int lvl;
};

