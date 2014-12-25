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
	void Restart();
	void DrawHero();
	void HeroSteps();
	void MousePress(int button,int  state,int x,int y);
private:
	std::vector<RuinesMap>TheSeed;
	int flag;
	Body MyLovelyHero;
};

