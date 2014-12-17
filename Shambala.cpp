
#include "stdafx.h"
#include "Shambala.h"
#include <gl\glut.h>

extern int flags;

Shambala::Shambala()
{
	
	TheSeed.push_back(RuinesMap(1));
	flag = 1;
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
	TheSeed[0].WhoDie();
	for (auto &x : TheSeed)
	{
		if (MyLovelyHero.tiktak <= 0)
		{
			HeroSteps();
			return 0;
		}
		else
			MyLovelyHero.tiktak -= 0.2;
		x.Activ();
	}
	return 0;
}

void Shambala::Draw()
{
	for (auto &x : TheSeed)
	{
		x.Draw();
		//DrawHero();
	}
}
/*
void Shambala::DrawHero()  //раскоменчу это, когда герой будет отрисовываться текстуркой.
{
	MyLovelyHero.cx;
	MyLovelyHero.cy;
	int z = 800 / 50;
	glBegin(GL_LINES);
	glColor3f(1, 0.1, 0.1);
	for (int count = 0; count < z; count++)
	{
		for (int count2 = 0; count2 < z; count2++)
		{
			glVertex2f(MyLovelyHero.cx*z, MyLovelyHero.cy*z);
			glVertex2f(MyLovelyHero.cx*z + count, MyLovelyHero.cy*z + count2);
		}
	}
	std::cout << "DRAW HERO" << std::endl;
	glEnd();
}*/ 

void Shambala::HeroSteps()
{
	if (flags == 1){ TheSeed[0].Move(MyLovelyHero.cx, MyLovelyHero.cy + 1, &MyLovelyHero); flags = 0; MyLovelyHero.tiktak += MyLovelyHero.moveS; }
	if (flags == 2){ TheSeed[0].Move(MyLovelyHero.cx + 1, MyLovelyHero.cy, &MyLovelyHero); flags = 0; MyLovelyHero.tiktak += MyLovelyHero.moveS; }
	if (flags == 3){ TheSeed[0].Move(MyLovelyHero.cx, MyLovelyHero.cy - 1, &MyLovelyHero); flags = 0;  MyLovelyHero.tiktak += MyLovelyHero.moveS; }
	if (flags == 4){ TheSeed[0].Move(MyLovelyHero.cx - 1, MyLovelyHero.cy, &MyLovelyHero); flags = 0;  MyLovelyHero.tiktak += MyLovelyHero.moveS; }
}