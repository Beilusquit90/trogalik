
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
	TheSeed[flag].steps.push_back(1);
	TheSeed[flag].steps.push_back(2);
	TheSeed[flag].steps.push_back(3);
}


Shambala::~Shambala()
{
}

void Shambala::MousePress(int button, int  state, int x, int y)
{
	TheSeed[flag].MousePress(button, state, x, y);
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

	MyLovelyHero =Body();
	SetMyHero();
}

int Shambala::Activ()
{
	if (TheSeed[flag].ioflag != 0)
	{
		if (TheSeed[flag].ioflag == 1)
		{
			if (TheSeed.size() > (flag + 1))
			{
				TheSeed[flag].ioflag = 0;
				flag++;
				TheSeed[flag].PushUp(MyLovelyHero);
				MyLovelyHero.tiktak = 0;
				return 1;
			}
			else
			{
				TheSeed[flag].ioflag = 0;
				flag++;
				TheSeed.push_back(RuinesMap(flag + 1));
				TheSeed[flag].PushUp(MyLovelyHero);
				return 1;
			}
		}
		if (TheSeed[flag].ioflag == 2)
		{
			TheSeed[flag].ioflag = 0;
			flag--;
			TheSeed[flag].PushDown(MyLovelyHero);
			MyLovelyHero.tiktak = 0;
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
	
	//TheSeed[flag].Draw();
	
	TheSeed[flag].WhatIsee();		// на данный момент живчики и стены

	TheSeed[flag].DrawFly();		// выстрелленая магия
	//TheSeed[flag].DrawInterface();
}


void Shambala::HeroSteps()
{
	if (TheSeed[flag].steps.size()==0)
	{
		int temp = 0;
		if (flags == 1){ temp = TheSeed[flag].Move(MyLovelyHero.cx, MyLovelyHero.cy + 1, &MyLovelyHero); flags = 0; }
		if (flags == 2){ temp = TheSeed[flag].Move(MyLovelyHero.cx + 1, MyLovelyHero.cy, &MyLovelyHero); flags = 0; }
		if (flags == 3){ temp = TheSeed[flag].Move(MyLovelyHero.cx, MyLovelyHero.cy - 1, &MyLovelyHero); flags = 0; }
		if (flags == 4){ temp = TheSeed[flag].Move(MyLovelyHero.cx - 1, MyLovelyHero.cy, &MyLovelyHero); flags = 0; }
		if (flags == 5){ temp = TheSeed[flag].Shot(&MyLovelyHero, 2); flags = 0; }
	}
	else
	{
		TheSeed[flag].Step();			std::cout << "STEPS ACTIVATE IN HERO STEPS" << std::endl; flags = 0;
	}
}
