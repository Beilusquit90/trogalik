// сделал читабельные комменты
#include "stdafx.h"
#include "RuinesMap.h"
#include <vector>
#include <iostream>
#include <gl\glut.h>


RuinesMap::RuinesMap()
{
	lvl = 1;
	for (int i = 0; i < 50; i++)
	for (int j = 0; j < 50; j++)
		levelSize[i][j] = 0;
	CreateLvl();
	int temp = (rand() % 6) + 5;
	for (int i = 0; i < temp; i++)
	{
		NewMapMan();
	}
	test();
}


RuinesMap::RuinesMap(const RuinesMap&rhs)
{
	vBody = rhs.vBody;
	for (int i = 0; i < 50; i++)
	for (int j = 0; j < 50; j++)
	{
		levelSize[i][j] = rhs.levelSize[i][j];
	}
	lvl = rhs.lvl;
	test();
}

void RuinesMap::operator=(RuinesMap&rhs)
{
	for (int i = 0; i < 50; i++)
	for (int j = 0; j < 50; j++)
		levelSize[j][i] = rhs.levelSize[j][i];
	lvl = rhs.lvl;
	test();
}

RuinesMap::RuinesMap(int _lvl)
{
	lvl = _lvl;
	for (int i = 0; i < 50; i++)
	for (int j = 0; j < 50; j++)
		levelSize[i][j] = 0;
	CreateLvl();
	int temp = (rand() % 6) + 5;
	for (int i = 0; i < temp; i++)
	{
		NewMapMan();
	}
	test();
}


RuinesMap::~RuinesMap()
{
	std::cout << "RuinesMAp DIE`S..." << std::endl;
}

int RuinesMap::Move(int x,int y,Body*rhs)
{
	//std::cout << levelSize[x][y] << std::endl;
	if (x >= 0 && x<50)
	if (y >= 0 && y<50)
	{	
		if (levelSize[x][y] == 0)	//проверка на свободный путь.
		{
			levelSize[rhs->cx][rhs->cy] = 0;
			rhs->cx = x;
			rhs->cy = y;
			levelSize[rhs->cx][rhs->cy] = rhs->role;
			return 1;
		}
	}
	return 0;
}

void RuinesMap::test()
{
	for (int i = 0; i < 50; i++){
		for (int j = 0; j < 50; j++)
		{
			std::cout << levelSize[i][j];
		}std::cout << std::endl;
	}
}

void RuinesMap::CreateLvl()
{
	for (int x = 0; x < 50;x++)
	for (int y = 0; y < 50; y++)
	{
		if (x == 0||x==49)	levelSize[x][y] = 999;
		if (y == 0||y==49)	levelSize[x][y] = 999;
	}
}


void RuinesMap::rMove(Body&x) // заставл€ет убогих, совершать рандомное движение. Ќа крайний случай, anotherMove
{
	for (int i = 0, j = 0; i < 1;)
		{
			if (j > 8)
			{
				x.tiktak+=4;
			}
			int temp = rand() % 8;
			switch (temp)
			{
			case 0: Move(x.cx, x.cy + 1, &x);			x.tiktak += x.moveS;	i = 1; break;  // вроде вверх
			case 1: Move(x.cx + 1, x.cy + 1, &x);	x.tiktak += x.rundiagonalS; i = 1; break;
			case 2: Move(x.cx + 1, x.cy, &x);			x.tiktak += x.moveS;	i = 1;  break;
			case 3: Move(x.cx + 1, x.cy - 1, &x);	x.tiktak += x.rundiagonalS; i = 1; break;
			case 4: Move(x.cx, x.cy - 1, &x);			x.tiktak += x.moveS;	i = 1; break;
			case 5: Move(x.cx - 1, x.cy - 1, &x);	x.tiktak += x.rundiagonalS; i = 1; break;
			case 6: Move(x.cx - 1, x.cy, &x);				x.tiktak += x.moveS; i = 1; break;
			case 7: Move(x.cx - 1, x.cy + 1, &x);	x.tiktak += x.rundiagonalS; i = 1; break;
			default:						break;
			}
		}
}


int RuinesMap::Activ( )
{
	for (auto &act : vBody)
	{	
		if (act.tiktak <= 0)
			rMove(act);
		else
			act.tiktak -= 0.2;
	}
return 0;
}


void RuinesMap::SetMyHero(Body&MyLovelyHero)
{
	MyLovelyHero.role = 9;
	int i = 1, cx, cy;
		 
	for (;;)
	{
		cx = rand() % 50;
		cy = rand() % 50;
		if (levelSize[cx][cy] == 0)
		{
			std::cout << "x" << cx << "   y" << cy << std::endl;
			levelSize[cx][cy] = MyLovelyHero.role;
			MyLovelyHero.cx = cx;
			MyLovelyHero.cy = cy;
			break;
		}
	}
}

void RuinesMap::NewMapMan()
{
	int i = 1, cx, cy, role;
	for (;;)
	{
		cx = rand() % 50;
		cy = rand() % 50;
		if (levelSize[cx][cy] == 0)
		{
			std::cout << "x" << cx << "   y" << cy << std::endl;
			vBody.push_back(Body(role, cx, cy, lvl));
			levelSize[cx][cy] = role;
			break;
		}
	}
	std::cout << "Gj man. New kid has ben planted in our map" << std::endl;
}


int RuinesMap::Draw( )
{
	glBegin(GL_LINES);
	glColor3f(0.6, 0.4, 0.6);
	int x = 0, y = 0;

	int z = 800 / 50;

	for (; x < 800; x += z)
	{
		glVertex2f(x, 0);
		glVertex2f(x, 800);
	}

	x = 0;
	for (; y < 800; y += z)
	{
		glVertex2f(0, y);
		glVertex2f(800, y);
	}
	for (int i = 0; i < 50; i++)
	for (int j = 0; j < 50; j++)
	{
		if (levelSize[j][i] != 0)
		{
			switch (levelSize[j][i])
			{
			case 1:glColor3f(0.9, 0.3, 0.1); break;
			case 2:glColor3f(0.2, 0.2, 0.5); break;
			case 3:glColor3f(0.7, 0.3, 0.8); break;
			case 4:glColor3f(0.2, 0.1, 0.7); break;
			case 9:glColor3f(0.7, 0.6, 0.7); break;
			case 999:glColor3f(1, 1, 0);	 break;
			}
			for (int count = 0; count < z; count++)
			{
				for (int count2 = 0; count2 < z; count2++)
				{
					glVertex2f(i*z, j*z);
					glVertex2f(i*z + count, j*z + count2);
				}
			}
		}
	}
	glEnd();
	return 0;
}