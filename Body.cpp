#include "stdafx.h"
#include "Body.h"
#include <iostream>
#include <stdlib.h>
#include "RuinesMap.h"




Body::Body(int&_role,int x,int y,int lvl):cx(x),cy(y) //раскидываем статы, в зависимости от уровня подземелья.
{
	hp = 1; ag = 1; str = 1; intel = 1; tiktak = 0;
	switch (role = rand() % 3 + 1) // 1 воин. 2 лучник . 3 маг.
	{
	case 1:str += 2;   break;
	case 2:ag += 2;    break;
	case 3:intel += 2; break;
	}
	_role = role;
	int temp = lvl + rand()%6;		// задаем рандомную надбавку на статы.
	for (int count = 0; count < temp; count++)
	{
		int i=rand() % 4 + 1;
		if (i == 1)hp++;
		if (i == 2)ag++;
		if (i == 3)str++;
		if (i == 4)intel++;
	}
	std::cout << "HP:" << hp << "  Ag:" << ag << "  Str" << str << "  Intelect:" << intel << "  role" << role << std::endl;
}



Body::Body(const Body&rhs)
{
	hp = rhs.hp;
	ag = rhs.str;
	str = rhs.str;
	intel = rhs.intel;
	cx = rhs.cx;
	cy = rhs.cy;
	tiktak = rhs.tiktak;
	role = rhs.role;
}

Body::~Body()
{
	std::cout << "BODY DIE`S..." << std::endl;

}

void Body::operator=(const Body&rhs)
{
	hp = rhs.hp;
	ag = rhs.str;
	str = rhs.str;
	intel = rhs.intel;
	cx = rhs.cx;
	cy = rhs.cy;
	tiktak = rhs.tiktak;
	role = rhs.role;
}






