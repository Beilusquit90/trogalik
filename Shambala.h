#pragma once
#include <list>
#include "RuinesMap.h"



class Shambala
{
public:
	Shambala();
	~Shambala();
	void Draw() 
	{
		for (auto &x : TheSeed)
		{
			x.Draw();
		}
	}
	void Activ()
	{
		for (auto &x : TheSeed)
		{
			x.Activ();
		}
	}
private:
	std::list<RuinesMap>TheSeed;
	int flag;
};

