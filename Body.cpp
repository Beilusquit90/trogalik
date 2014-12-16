#include "stdafx.h"
#include "Body.h"
#include <iostream>
#include <stdlib.h>
#include "RuinesMap.h"


Body::Body()
{
	std::cout << "TEST CONSTRUCTOR"<<std::endl;

}

Body::Body(int lvl,RuinesMap&_rm) //раскидываем статы, в зависимости от уровня подземелья.
{
	std::cout << "FLAG!" << std::endl;
	rm = &_rm;
	hp = 1; ag = 1; str = 1; intel = 1; tiktak = 0;
	switch (role = rand() % 3 + 1) // 1 воин. 2 лучник . 3 маг.
	{
	case 1:str += 2;   break;
	case 2:ag += 2;    break;
	case 3:intel += 2; break;
	}
	int temp = lvl + rand()%6;		// задаем рандомную надбавку на статы.
	for (int count = 0; count < temp; count++)
	{
		int i=rand() % 4 + 1;
		if (i == 1)hp++;
		if (i == 2)ag++;
		if (i == 3)str++;
		if (i == 4)intel++;
	}
	std::cout << "HP:" << hp << "  Ag:" << ag << "  Str" << str << "  Intelect:" << intel << lvl << "  role" << role << std::endl;
	NewMapMan();
	test();
}

Body::Body(int lvl, RuinesMap*_rm) //раскидываем статы, в зависимости от уровня подземелья.
{
	std::cout << "FLAG!" << std::endl;
	rm = &(*_rm);
	hp = 1; ag = 1; str = 1; intel = 1; tiktak = 0;
	switch (role = rand() % 3 + 1) // 1 воин. 2 лучник . 3 маг.
	{
	case 1:str += 2;   break;
	case 2:ag += 2;    break;
	case 3:intel += 2; break;
	}
	
	int temp = lvl + rand() % 6;		// задаем рандомную надбавку на статы.
	for (int count = 0; count < temp; count++)
	{
		int i = rand() % 4 + 1;
		if (i == 1)hp++;
		if (i == 2)ag++;
		if (i == 3)str++;
		if (i == 4)intel++;
	}
	std::cout << "HP:" << hp << "  Ag:" << ag << "  Str" << str << "  Intelect:" << intel << lvl << "  role" << role << std::endl;
	NewMapMan();
	//test();
}

Body::~Body(){rm=nullptr;}

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
	rm = &(*rhs.rm);
	//std::cout << rhs.rm;

}

void Body::operator=(Body&rhs)
{
	hp = rhs.hp;
	ag = rhs.str;
	str = rhs.str;
	intel = rhs.intel;
	cx = rhs.cx;
	cy = rhs.cy;
	tiktak = rhs.tiktak;
	role = rhs.role;
	rm = &(*rhs.rm);
	//std::cout << rhs.rm->levelSize[1][1];
}


void Body::sMap()
{
	std::cout << cx << "  SET MAP " << cy << std::endl;
	rm->levelSize[cx][cy] = 1;
}

void Body::dMap()
{
	std::cout << cx << "  DELETE MAP " << cy << std::endl;
	rm->levelSize[cx][cy] = 0;
}

void Body::NewMapMan()
{
	int i = 1;
	int x, y;
	for (; i!=0;)
	{
		x = rand() % 15;
		y = rand() % 15;
		if (rm->levelSize[x][y] == 0)
		{
			std::cout << "x" << x << "   y" << y << std::endl;
			cx = x;
			cy = y;
			sMap();
			i = 0;
		}
	}
	std::cout << "Gj man. New kid has ben planted in our map" << std::endl;
}

void Body::rMove() // заставляет убогих, совершать рандомное движение. На крайний случай, anotherMove
{
	for (int i = 0,j=0; i < 1;)
	{
		
		if (j > 8)
		{
		anotherMove(); i = 1;
		}
		int temp = rand() % 8;
		//std::cout << "TEMO IS " << temp << std::endl;
		switch (temp)
		{
		case 0: move(cx, (cy + 1));		i = 1; break;  // вроде вверх
		case 1: move(cx + 1, cy + 1);	i = 1; break;
		case 2: move(cx + 1, cy);		i = 1;  break;
		case 3: move(cx + 1, cy - 1);	i = 1; break;
		case 4: move(cx, cy - 1);		i = 1; break;
		case 5: move(cx - 1, cy - 1);	i = 1; break;
		case 6: move(cx - 1, cy);		i = 1; break;
		case 7: move(cx - 1, cy + 1);	i = 1; break;
		default:						break;
		}	
		if (i == 0) j++;
	}
}	


int Body::move(int x, int y)
{
	
	if (x >= 0&&x<15 )
		if (y >= 0&&y<15 )//выход за массив
		{
			std::cout << "****" << x << "****" << y << std::endl;
			std::cout <<rm->levelSize[x][y]<< std::endl;
			if (rm->levelSize[x][y] == 0)	//проверка на свободный путь.
			{
				dMap();
				cx = x;
				cy = y;
				sMap();
				std::cout << "***************" << std::endl;
				return 1;
			}
		}
	
	return 0;
}


void Body::test()
{
	for (int i = 0; i < 15;i++)
	for (int j = 0; j < 15; j++)
		std::cout << rm->levelSize[i][j] << std::endl;

}