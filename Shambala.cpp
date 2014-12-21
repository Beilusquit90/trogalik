
#include "stdafx.h"
#include "Shambala.h"
#include <gl\glut.h>
extern int flags;

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


int Shambala::Activ()
{
	TheSeed[flag].WhoDie();
	if (MyLovelyHero.hp <= 0)
		return 0;
	if (MyLovelyHero.tiktak <= 0)
	{
		HeroSteps();
		return 0;
	}
	else
		MyLovelyHero.tiktak -= 0.2;
	for (auto &x : TheSeed)
	{
		x.Activ();
	}
	return 0;
}

void Shambala::Draw()
{
	for (auto &x : TheSeed)
	{
		x.WhatIsee();
		//x.Draw();
	}

}


void Shambala::HeroSteps()
{
	int temp = 0;
	if (flags == 1){ temp = TheSeed[0].Move(MyLovelyHero.cx, MyLovelyHero.cy + 1, &MyLovelyHero); flags = 0; }
	if (flags == 2){ temp = TheSeed[0].Move(MyLovelyHero.cx + 1, MyLovelyHero.cy, &MyLovelyHero); flags = 0; }
	if (flags == 3){ temp = TheSeed[0].Move(MyLovelyHero.cx, MyLovelyHero.cy - 1, &MyLovelyHero); flags = 0; }
	if (flags == 4){ temp = TheSeed[0].Move(MyLovelyHero.cx - 1, MyLovelyHero.cy, &MyLovelyHero); flags = 0; }
	if (flags == 5){ temp = TheSeed[0].Shot(&MyLovelyHero,2); flags = 0; }
	if (temp == 1){ MyLovelyHero.tiktak += MyLovelyHero.moveS; }
	if (temp == 3){ MyLovelyHero.tiktak += MyLovelyHero.shotS; }
}