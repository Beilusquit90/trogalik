#include "stdafx.h"
#include "RuinesMap.h"
#include <vector>
#include <iostream>
#include <gl\glut.h>


RuinesMap::RuinesMap()
{
	lvl = 1;

	int temp = (rand() % 6) + 5;
	for (int i = 0; i < temp; i++)
	{
		vBody.push_back(Body(lvl, (*this)));
	}
	for (int i = 0; i < 15; i++)
	for (int j = 0; j < 15; j++)
		levelSize[i][j] = 0;
	//std::cout << vBody.size() << "SIZE lvl " << 1 << std::endl;
}


RuinesMap::RuinesMap(const RuinesMap&rhs)
{
	vBody = rhs.vBody;
	for (int i = 0; i < 15; i++)
	for (int j = 0; j < 15; j++)
	{
		levelSize[i][j] = rhs.levelSize[i][j];
	}
	lvl = rhs.lvl;
}

void RuinesMap::operator=(RuinesMap&rhs)
{
	vBody = rhs.vBody;
	for (int i = 0; i < 15; i++)
	for (int j = 0; j < 15; j++)
		levelSize[j][i] = rhs.levelSize[j][i];
	lvl = rhs.lvl;
}

RuinesMap::RuinesMap(int _lvl)
{
	lvl = _lvl;
	for (int i = 0; i < 15; i++)
	for (int j = 0; j < 15; j++)
		levelSize[i][j] = 0;
	int temp = (rand() % 6) + 5;
	for (int i = 0; i < temp; i++)
	{
		vBody.push_back(Body(lvl, (*this)));
	}
}


RuinesMap::~RuinesMap()
{
}


int RuinesMap::Activ(int flag)
{
	if (flag != lvl)return 0;
	for (auto &act : vBody)
	{
		act.rMove();
	}
	return 0;
}

int RuinesMap::Draw(int flag)
{
	if (flag != lvl)return 0;
	glBegin(GL_LINES);
	glColor3f(0.6, 0.4, 0.6);
	int x = 0, y = 0;

	int z = 800 / 15;

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

	for (int i = 0; i < 15; i++)
	for (int j = 0; j < 15; j++)
	{
		if (levelSize[j][i] == 1)
		{
			glVertex2f(i*z, j*z);
			glVertex2f(i*z + z, j*z + z);
		}
	}
	glEnd();
	return 0;
}