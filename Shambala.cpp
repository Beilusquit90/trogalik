
#include "stdafx.h"
#include "Shambala.h"
#include <gl\glut.h>
#include "GameMenu.h"
extern int flags;
extern int flagMenu;

Shambala::Shambala()
{
	TheSeed.push_back(RuinesMap(1));
	flag = 0;
	SetMyHero();
}


Shambala::~Shambala()
{
}

void Shambala::SetMyHero()
{
	TheSeed[0].SetMyHero(MyLovelyHero);
}


void Shambala::Restart()
{
	TheSeed.clear();
	TheSeed.push_back(RuinesMap(1));
	flag = 0;
	MyLovelyHero = Body();
	SetMyHero();
}

int Shambala::Activ()
{
	if (TheSeed[flag].ioflag != 0)
	{
		if (TheSeed[flag].ioflag == 1)
		{
			std::cout << "DANGER1" << std::endl;
			if (TheSeed.size() > flag + 1)
			{
				TheSeed[flag].ioflag = 0;
				flag++;
				TheSeed[flag].PushUp(MyLovelyHero);
				return 1;
			}
			else
			{
				TheSeed[flag].ioflag = 0;
				flag++;
				TheSeed.push_back(RuinesMap(flag + 1));
				std::cout << "DANGER 1 1" << std::endl;
				TheSeed[flag].PushUp(MyLovelyHero);
				std::cout << "DANGER 1 1 1" << std::endl;
				return 1;
			}
		}
		if (TheSeed[flag].ioflag == 2)
		{
			std::cout << "DANGER2" << std::endl;
			TheSeed[flag].ioflag = 0;
			flag--;
			TheSeed[flag].PushDown(MyLovelyHero);
			return 1;
		}
	}
	TheSeed[flag].WhoDie();
	if (MyLovelyHero.hp <= 0){
		Restart(); flagMenu = 1; return 0;
	}
	if (MyLovelyHero.tiktak <= 0)
	{
		HeroSteps();
		return 0;
	}
	else
		MyLovelyHero.tiktak -= 0.2;
	/*for (auto &x : TheSeed)
	{
		x.Activ();
	}*/
	TheSeed[flag].Activ();
	return 0;
}

void Shambala::Draw()
{
	TheSeed[flag].WhatIsee();		// на данный момент живчики и стены
	TheSeed[flag].DrawFly();		// выстрелленая магия
}


void Shambala::HeroSteps()
{
	int temp = 0;
	if (flags == 1){ temp = TheSeed[flag].Move(MyLovelyHero.cx, MyLovelyHero.cy + 1, &MyLovelyHero); flags = 0; }
	if (flags == 2){ temp = TheSeed[flag].Move(MyLovelyHero.cx + 1, MyLovelyHero.cy, &MyLovelyHero); flags = 0; }
	if (flags == 3){ temp = TheSeed[flag].Move(MyLovelyHero.cx, MyLovelyHero.cy - 1, &MyLovelyHero); flags = 0; }
	if (flags == 4){ temp = TheSeed[flag].Move(MyLovelyHero.cx - 1, MyLovelyHero.cy, &MyLovelyHero); flags = 0; }
	if (flags == 5){ temp = TheSeed[flag].Shot(&MyLovelyHero, 2); flags = 0; }
	if (temp == 1){ MyLovelyHero.tiktak += MyLovelyHero.moveS; }
	if (temp == 3){ MyLovelyHero.tiktak += MyLovelyHero.shotS; }
}