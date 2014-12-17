#pragma once
#include <vector>
#include "RuinesMap.h"
#include <iostream>

class Shambala
{
public:
	Shambala();
	~Shambala();
	void SetMyHero();
	void Draw();
	int Activ();
	void DrawHero();
	void HeroSteps();
private:
	std::vector<RuinesMap>TheSeed;
	int flag;
	Body MyLovelyHero;
};

