﻿// сделал читабельные комменты
#include "stdafx.h"
#include "RuinesMap.h"
#include <vector>
#include <iostream>
#include <gl\glut.h>
#include <queue>  
#include "TileTextures.h"

extern TileTextures tails;
extern const int sizeMap;
extern double mx;		//мышка икс
extern double my;		//мышка игрик
int wWidth = 800;    //высота
int wHeight = 800;    //ширина

RuinesMap::RuinesMap()
{
	mflag = 0;
	ioflag = 0;
	lvl = 1;
	for (int i = 0; i < sizeMap; i++)
	for (int j = 0; j < sizeMap; j++)
	{
		levelSize[i][j] = 0;
		MA[i][j] = 0;
	}
	CreateLvl();
	int temp = (rand() % 6) + 5;
	std::cout << "TEMPO" << temp << std::endl;
	for (int i = 0; i < temp; i++)
	{
		NewMapMan();
	}
	Doors();
	//test();
}

RuinesMap::RuinesMap(const RuinesMap&rhs)
{
	mflag = rhs.mflag;
	ioflag = rhs.ioflag;
	RL = rhs.RL;
	vDoor = rhs.vDoor;
	vMA = rhs.vMA;
	vBody = rhs.vBody;
	for (int i = 0; i < sizeMap; i++)
	for (int j = 0; j < sizeMap; j++)
	{
		levelSize[i][j] = rhs.levelSize[i][j];
		MA[i][j] = rhs.MA[i][j];
	}
	lvl = rhs.lvl;
	//test();
}

void RuinesMap::operator=(RuinesMap&rhs)
{
	for (int i = 0; i < sizeMap; i++)
	for (int j = 0; j < sizeMap; j++){
		levelSize[j][i] = rhs.levelSize[j][i];
		MA[i][j] = rhs.MA[i][j];
	}
	lvl = rhs.lvl;
	ioflag = rhs.ioflag;
	mflag = rhs.mflag;
	//test();
}

RuinesMap::RuinesMap(int _lvl)
{
	mflag = 0;
	ioflag = 0;
	lvl = _lvl;
	for (int i = 0; i < sizeMap; i++)
	for (int j = 0; j < sizeMap; j++)
	{
		levelSize[i][j] = 0; MA[i][j] = 0;
	}
	CreateLvl();
	int temp = (rand() % 6) + 15;
	for (int i = 0; i < temp; i++)
	{
		NewMapMan();
	}
	Doors();
	//test();
}

RuinesMap::~RuinesMap()
{
	//std::cout << "RuinesMAp DIE`S..." << std::endl;
}

void RuinesMap::MousePress(int button, int  state, int x, int y)
{
	int f = 0;
	int z = wHeight / 30;
	int xpos = wWidth / 5;
	int ypos = wHeight / 5;
	int xxpos = xpos + (z * 17) - 4;
	int yypos = ypos + (z * 17) - 4;
	int tx = mx / z;
	int ty = my / z;
	int txx = startx + ty - 6;
	int tyy = starty + tx - 6;


	if (f == 0)
		switch (mflag)
	{
		case 1: f = 1;

			switch (button)
			{
			case GLUT_LEFT_BUTTON:
				mMouse(button, state, x, y); f = 0; break;
			case GLUT_MIDDLE_BUTTON:if (state)f = 0; break;
			case GLUT_RIGHT_BUTTON:if (state)mflag = 0; f = 0; break;
			}break;


		case 0:
			switch (button)
			{
			case GLUT_LEFT_BUTTON:
				if (mflag == 0)if (state)
				if (mx > xpos&&my > ypos&&mx < xxpos&&my < yypos)
					//if ((abs(tx - MyHero->cx) + abs(ty - MyHero->cy)) <= 2 && (abs(tx - MyHero->cx) <= 1 && abs(ty - MyHero->cy) <= 1)){ Move(tx, ty, MyHero); std::cout << "******" << std::endl;  }
					//else
				if (steps.size()>0)steps.clear();
				else CreateSteps(tx, ty); break;
			case GLUT_MIDDLE_BUTTON:if (state) break;
			case GLUT_RIGHT_BUTTON:if (state) break;
			default:					break;
			}
			break;
	}
}

void RuinesMap::mMouse(int button, int  state, int x, int y)
{

	//Магия нажатия мышкой.
	if (state)
	{
		int z = wHeight / 30;
		int xpos = wWidth / 5;
		int ypos = wHeight / 5;
		int xxpos = xpos + (z * 17) - 4;
		int yypos = ypos + (z * 17) - 4;
		int tx = mx / z;
		int ty = my / z;
		int txx = startx + ty - 6;
		int tyy = starty + tx - 6;
		if (txx == MyHero->cx + 1 && tyy == MyHero->cy){ Shot(MyHero, 2); mflag = 0; }
		else if (txx == MyHero->cx + 1 && tyy == MyHero->cy + 1){ Shot(MyHero, 1); mflag = 0; }
		else if (txx == MyHero->cx && tyy == MyHero->cy - 1){ Shot(MyHero, 4); mflag = 0; }
		else if (txx == MyHero->cx && tyy == MyHero->cy + 1){ Shot(MyHero, 0); mflag = 0; }
		else if (txx == MyHero->cx + 1 && tyy == MyHero->cy - 1){ Shot(MyHero, 3); mflag = 0; }
		else if (txx == MyHero->cx - 1 && tyy == MyHero->cy){ Shot(MyHero, 6); mflag = 0; }
		else if (txx == MyHero->cx - 1 && tyy == MyHero->cy + 1){ Shot(MyHero, 7); mflag = 0; }
		else if (txx == MyHero->cx - 1 && tyy == MyHero->cy - 1){ Shot(MyHero, 5); mflag = 0; }



	}
}

int RuinesMap::CreateSteps(int tx, int ty)
{

	int txx = startx + ty - 6;
	int tyy = starty + tx - 6;

	if (levelSize[txx][tyy] == 999){ return 0; }

	Point start(MyHero->cx, MyHero->cy);
	Point end(txx, tyy);
	StepsFind(start, end);

	int xx = MyHero->cx;
	int yy = MyHero->cy;
	Patch[xx][yy] = 0;
	std::cout << "patch start" << std::endl;
	for (;;)
	{
		if (Patch[xx][yy + 1] == 1){ steps.push_back(1); Patch[xx][yy] = 0; yy++;  continue; };
		if (Patch[xx + 1][yy + 1] == 1){ steps.push_back(2); Patch[xx][yy] = 0; xx++; yy++; continue; }
		if (Patch[xx + 1][yy] == 1){ steps.push_back(3); Patch[xx][yy] = 0; xx++; continue; }
		if (Patch[xx + 1][yy - 1] == 1){ steps.push_back(4); Patch[xx][yy] = 0; xx++; yy--; continue; }
		if (Patch[xx][yy - 1] == 1){ steps.push_back(5); Patch[xx][yy] = 0; yy--; continue; }
		if (Patch[xx - 1][yy - 1] == 1){ steps.push_back(6); Patch[xx][yy] = 0; xx--; yy--; continue; }
		if (Patch[xx - 1][yy] == 1){ steps.push_back(7); Patch[xx][yy] = 0; xx--; continue; }
		if (Patch[xx - 1][yy + 1] == 1){ steps.push_back(8); Patch[xx][yy] = 0; xx--; yy++; continue; }
		else	break;
	}

	return 0;
}

void RuinesMap::StepsFind(const Point &start, const Point &finish)
{

#define TOP_LEFT Patch[i - 1][j + 1]
#define TOP_RIGHT Patch[i + 1][j + 1]
#define TOP Patch[i][j + 1]
#define BOT_LEFT Patch[i - 1][j - 1]
#define BOT_RIGHT Patch[i + 1][j - 1]
#define BOT Patch[i][j - 1]
#define LEFT Patch[i - 1][j]
#define RIGHT Patch[i + 1][j]

	std::cout << "START STEP FINDS" << std::endl;
	for (int i = 0; i < sizeMap; i++)
	for (int j = 0; j < sizeMap; j++)
		Patch[i][j] = -3;

	for (int i = sizeMap - 1; i >= 0; i--)
	for (int j = sizeMap - 1; j >= 0; j--)
	if (levelSize[i][j] == 999) Patch[i][j] = -9;

	Patch[finish.x][finish.y] = 0;

	for (int z = 0; Patch[start.x][start.y] == (-3); z++)
	{
		for (int i = 0; i < sizeMap; i++)
		for (int j = 0; j < sizeMap; j++)
		if (Patch[i][j] == z)
		{
			if (TOP == -3)	TOP = (z + 1);
			if (TOP_RIGHT == -3)	TOP_RIGHT = (z + 1);
			if (RIGHT == -3)	RIGHT = (z + 1);
			if (BOT_RIGHT == -3)	BOT_RIGHT = (z + 1);
			if (BOT == -3)	BOT = (z + 1);
			if (BOT_LEFT == -3)	BOT_LEFT = (z + 1);
			if (LEFT == -3)	LEFT = (z + 1);
			if (TOP_LEFT == -3)	TOP_LEFT = (z + 1);
		}
		if (z > 150){
			std::cout << "I fixed this bag later... Room without doors." << std::endl; break;}
	}



	int temp[sizeMap][sizeMap];
	for (int i = sizeMap - 1; i >= 0; i--)
	for (int j = sizeMap - 1; j >= 0; j--)
		temp[i][j] = 0;

	for (int i = sizeMap - 1; i >= 0; i--)
	for (int j = sizeMap - 1; j >= 0; j--)
	if (levelSize[i][j] == 999) temp[i][j] = 9;


	int tx = start.x;
	int ty = start.y;


	for (; Patch[tx][ty] != 0;)
	{
		int t = Patch[tx][ty] - 1;


		if (Patch[tx][ty + 1] == t){
			ty++; temp[tx][ty] = 1;
		}
		else if (Patch[tx + 1][ty] == t){
			tx++; temp[tx][ty] = 1;
		}
		else if (Patch[tx][ty - 1] == t){
			ty--; temp[tx][ty] = 1;
		}
		else if (Patch[tx - 1][ty] == t){
			tx--; temp[tx][ty] = 1;
		}
		else if (Patch[tx + 1][ty + 1] == t){
			tx++; ty++; temp[tx][ty] = 1;
		}
		else if (Patch[tx + 1][ty - 1] == t){
			tx++; ty--; temp[tx][ty] = 1;
		}
		else if (Patch[tx - 1][ty - 1] == t){
			tx--; ty--; temp[tx][ty] = 1;
		}
		else if (Patch[tx - 1][ty + 1] == t){
			tx--; ty++; temp[tx][ty] = 1;
		}
	}

	for (int i = 0; i < sizeMap; i++)
	for (int j = 0; j < sizeMap; j++)
		Patch[i][j] = 0;

	for (int i = 0; i < sizeMap; i++)
	for (int j = 0; j < sizeMap; j++)
		Patch[i][j] = temp[i][j];
}

void RuinesMap::Doors()	// рандомно пихает дверушку.
{
	int x, y;
	if (lvl == 1)
	{
		for (int z = 0; z == 0;)
		{
			x = rand() % sizeMap;
			y = rand() % sizeMap;
			if (levelSize[x][y] == 0
				&& levelSize[x][y + 1] == 0
				&& levelSize[x + 1][y + 1] == 0
				&& levelSize[x + 1][y] == 0
				&& levelSize[x + 1][y - 1] == 0
				&& levelSize[x][y - 1] == 0
				&& levelSize[x - 1][y - 1] == 0
				&& levelSize[x - 1][y] == 0
				&& levelSize[x - 1][y + 1] == 0)
			{
				z = 1;
				levelSize[x][y] = 666;
				int t = 1;
				vDoor.push_back(TheDoor(1, x, y));
			}
		}
	}
	else
	{
		for (int z = 0; z == 0;)
		{
			x = rand() % sizeMap;
			y = rand() % sizeMap;
			if (levelSize[x][y] == 0
				&& levelSize[x][y + 1] == 0
				&& levelSize[x + 1][y + 1] == 0
				&& levelSize[x + 1][y] == 0
				&& levelSize[x + 1][y - 1] == 0
				&& levelSize[x][y - 1] == 0
				&& levelSize[x - 1][y - 1] == 0
				&& levelSize[x - 1][y] == 0
				&& levelSize[x - 1][y + 1] == 0)
			{
				z = 1;
				levelSize[x][y] = 666;
				vDoor.push_back(TheDoor(1, x, y));
			}
		}
		for (int z = 0; z == 0;)
		{
			x = rand() % sizeMap;
			y = rand() % sizeMap;
			if (levelSize[x][y] == 0
				&& levelSize[x][y + 1] == 0
				&& levelSize[x + 1][y + 1] == 0
				&& levelSize[x + 1][y] == 0
				&& levelSize[x + 1][y - 1] == 0
				&& levelSize[x][y - 1] == 0
				&& levelSize[x - 1][y - 1] == 0
				&& levelSize[x - 1][y] == 0
				&& levelSize[x - 1][y + 1] == 0)
			{
				z = 1;
				levelSize[x][y] = 777;
				vDoor.push_back(TheDoor(0, x, y));
			}
		}
	}
}

int RuinesMap::Step() // возвращает 1 если действие сделано, и 0 если в очереди нету действий.
{
	if (steps.size() > 0)
	{
		int cx, cy;
		auto &x = steps.begin();
		switch (*x)
		{
		case 1:cx = MyHero->cx; cy = MyHero->cy + 1; break;
		case 2:cx = MyHero->cx + 1; cy = MyHero->cy + 1; break;
		case 3:cx = MyHero->cx + 1; cy = MyHero->cy; break;
		case 4:cx = MyHero->cx + 1; cy = MyHero->cy - 1; break;
		case 5:cx = MyHero->cx; cy = MyHero->cy - 1; break;
		case 6:cx = MyHero->cx - 1; cy = MyHero->cy - 1;  break;
		case 7:cx = MyHero->cx - 1; cy = MyHero->cy; break;
		case 8:cx = MyHero->cx - 1; cy = MyHero->cy + 1; break;
		default:std::cout << "STEP DANGER SITUATION" << std::endl; break;
		}
		if (levelSize[cx][cy] != 0)
		{
			steps.clear();
			std::cout << "STEPS STOPPPING !=0" << std::endl;
			for (int i = 0; i < sizeMap; i++)
			for (int j = 0; j < sizeMap; j++)
				Patch[i][j] = 0;
			return 0;
		}
		else
			Move(cx, cy, MyHero);
		steps.erase(steps.begin());
	}

	return 0;
}

void RuinesMap::Attack(int _x, int _y, Body*rhs)
{
	int count = 0;
	if (levelSize[_x][_y] == 9)
	{
		MyHero->hp -= rhs->str;
		rhs->tiktak += rhs->attackS;
		std::cout << "ATTACK MY HERO!" << std::endl;

	}
	for (auto &x : vBody)
	{
		if (x.cx == _x&&x.cy == _y)
		{
			vBody[count].hp -= rhs->str;
			vBody[count].MyKiller = rhs;
			std::cout << "ATTACK" << std::endl;
			rhs->tiktak += rhs->attackS;
		}
		count++;
	}
}

int RuinesMap::Move(int x, int y, Body*rhs)
{
	int diag = 0;
	if (std::abs(rhs->cx - x) == 1 && std::abs(rhs->cy - y) == 1)
		diag = 1;

	if (x >= 0 && x<sizeMap)
	if (y >= 0 && y<sizeMap)
	{

		if (levelSize[x][y] == 666 || levelSize[x][y] == 777)
		if (rhs == MyHero)
		{
			if (levelSize[x][y] == 666){ ioflag = 1; levelSize[MyHero->cx][MyHero->cy] = 0; }
			if (levelSize[x][y] == 777){ ioflag = 2; levelSize[MyHero->cx][MyHero->cy] = 0; }
			std::cout << "Go another level" << levelSize[x][y] << std::endl;
			return 1;
		}

		if (levelSize[x][y] == 999) return 0;
		if (levelSize[x][y] == 0)	//проверка на свободный путь.
		{
			levelSize[rhs->cx][rhs->cy] = 0;
			rhs->cx = x;
			rhs->cy = y;
			levelSize[rhs->cx][rhs->cy] = rhs->role;
			if (diag == 1)
				rhs->tiktak += rhs->rundiagonalS;
			else
				rhs->tiktak += rhs->moveS;
			return 1;
		}
		else
		if (rhs->role == 9)
		{
			Attack(x, y, rhs);
			return 1;

		}
		else
		{
			if (levelSize[x][y] == 9)
			{
				Attack(x, y, rhs);
				return 1;
			}
		}
	}
	return 0;
}

void RuinesMap::test()
{
	for (int i = 0; i < sizeMap; i++){
		for (int j = 0; j < sizeMap; j++)
		{
			std::cout << levelSize[i][j];
		}std::cout << std::endl;
	}
}

void RuinesMap::CreateLvl()
{
	for (int x = 0; x < sizeMap; x++)
	for (int y = 0; y < sizeMap; y++)
		levelSize[x][y] = 999;

	MapGen();
	std::cout << "MAP GEN FINISH" << std::endl;
}

void RuinesMap::rMove(Body&x) // заставляет убогих, совершать рандомное движение. На крайний случай, anotherMove
{
	for (int i = 0, j = 0; i < 1;)
	{
		if (j > 8)
		{
			x.tiktak += 14;
		}
		int temp = rand() % 8;
		switch (temp)
		{
		case 0: i = Move(x.cx, x.cy + 1, &x);		 break; //	x.tiktak += x.moveS;	 break;  // вроде вверх
		case 1: i = Move(x.cx + 1, x.cy + 1, &x);	 break; //	x.tiktak += x.rundiagonalS;; break;
		case 2: i = Move(x.cx + 1, x.cy, &x);		 break; //		x.tiktak += x.moveS;	 break;
		case 3: i = Move(x.cx + 1, x.cy - 1, &x);	 break; //	x.tiktak += x.rundiagonalS;  break;
		case 4: i = Move(x.cx, x.cy - 1, &x);		 break; //		x.tiktak += x.moveS;	 break;
		case 5: i = Move(x.cx - 1, x.cy - 1, &x);	 break; //	x.tiktak += x.rundiagonalS;  break;
		case 6: i = Move(x.cx - 1, x.cy, &x);		 break; //			x.tiktak += x.moveS; break;
		case 7: i = Move(x.cx - 1, x.cy + 1, &x);  break; //		x.tiktak += x.rundiagonalS;  break;
		default:						break;
		}
	}
}

void RuinesMap::WhoDie()
{
	flyDeath();

	int dFlag = 0;
	int count = 0;
	for (auto &x : vBody)
	{
		if (x.hp <= 0)
		{
			levelSize[x.cx][x.cy] = 0;
			dFlag = 1;
			break;
		}
		count++;
	}
	if (dFlag == 1)
	{
		(vBody.begin() + count)->MyKiller->exp += (vBody.begin() + count)->exp;		//отдаем опыт моему убийце.
		std::cout << (vBody.begin() + count)->MyKiller->exp << std::endl;
		vBody.erase(vBody.begin() + count);
		dFlag = 0;
	}
}

void RuinesMap::ClearTactikMap()
{
	for (int i = 0; i < sizeMap; i++)
	for (int j = 0; j < sizeMap; j++)
	if (levelSize[i][j] == 999)TactikMap[i][j] = 9;
	else TactikMap[i][j] = 0;
}

void RuinesMap::DangerBirds(int dx, int dy, MAmap&bird)
{
	std::cout << bird.direction << std::endl;

	TactikMap[dx][dy] = 1;
	switch (bird.direction)
	{
	case 0:
		for (int i = 0; levelSize[dx][dy] != 999 && levelSize[dx][dy] != 9 && i < bird.range; i++)
		{
			dy++; TactikMap[dx][dy] = 1;
		}break;
	case 2:	for (int i = 0; levelSize[dx][dy] != 999 && levelSize[dx][dy] != 9 && i < bird.range; i++)
	{
				dx++; TactikMap[dx][dy] = 1;
	}break;
	case 4:	for (int i = 0; levelSize[dx][dy] != 999 && levelSize[dx][dy] != 9 && i < bird.range; i++)
	{
				dy--; TactikMap[dx][dy] = 1;
	}break;
	case 6:	for (int i = 0; levelSize[dx][dy] != 999 && levelSize[dx][dy] != 9 && i < bird.range; i++)
	{
				dx--; TactikMap[dx][dy] = 1;
	}break;

	case 1:	for (int i = 0; levelSize[dx][dy] != 999 && levelSize[dx][dy] != 9 && i < bird.range; i++)
	{
				dx++; dy++; TactikMap[dx][dy] = 1;
	}break;
	case 3:	for (int i = 0; levelSize[dx][dy] != 999 && levelSize[dx][dy] != 9 && i < bird.range; i++)
	{
				dx++; dy--; TactikMap[dx][dy] = 1;
	}break;
	case 5:	for (int i = 0; levelSize[dx][dy] != 999 && levelSize[dx][dy] != 9 && i < bird.range; i++)
	{
				dx--; dy--; TactikMap[dx][dy] = 1;
	}break;
	case 7:	for (int i = 0; levelSize[dx][dy] != 999 && levelSize[dx][dy] != 9 && i < bird.range; i++)
	{
				dx--; dy++; TactikMap[dx][dy] = 1;
	}break;
	default:std::cout << "Abonormal Dirrections in DangerBirds() func." << std::endl;
	}
}

int RuinesMap::Activ()
{

	ClearTactikMap();
	for (auto &act : vMA)
	{
		
		if (act.tiktak <= 0){

			fly(act);
		}
		act.tiktak -= 0.2;
	}


	for (auto &act : vBody)
	{
		if (act.tiktak <= 0)
			AI(&act);
		else
			
			act.tiktak -= 0.2;
	}
	return 0;
}

int RuinesMap::fly(MAmap&bird)
{
	bird.tiktak += 0.2;
	int dx, dy;
	if (bird.direction == 0){ dx = bird.cx;	dy = bird.cy + 1; }
	else if (bird.direction == 1){ dx = bird.cx + 1;	dy = bird.cy + 1; }
	else if (bird.direction == 2){ dx = bird.cx + 1;	dy = bird.cy; }
	else if (bird.direction == 3){ dx = bird.cx + 1;	dy = bird.cy - 1; }
	else if (bird.direction == 4){ dx = bird.cx;	dy = bird.cy - 1; }
	else if (bird.direction == 5){ dx = bird.cx - 1;	dy = bird.cy - 1; }
	else if (bird.direction == 6){ dx = bird.cx - 1;	dy = bird.cy; }
	else if (bird.direction == 7){ dx = bird.cx - 1;	dy = bird.cy + 1; }

	if (levelSize[dx][dy] == 999 || levelSize[dx][dy] == 666 || levelSize[dx][dy] == 777){
		bird.life = 0; return 0;
	}
	bird.range--;
	if (bird.range == 0)bird.life = 0;

	if (MA[dx][dy] != 0)
	{
		for (auto &x : vMA)
		{
			if (x.cx == dx&&x.cy == dy){ x.life = 0; bird.life = 0; break; }
		}
		return 0;
	}

	else if (levelSize[dx][dy] == 0)
	{
		MA[bird.cx][bird.cy] = 0;
		bird.cx = dx;
		bird.cy = dy;
		MA[dx][dy] = bird.effect;
		std::cout << "basda" << bird.tiktak << std::endl;
	
		std::cout << "basda" << bird.tiktak << std::endl;
		DangerBirds(dx, dy, bird);	//ставим метки на тактическую карту
		return 0;
	}

	else if (levelSize[dx][dy] == 9)		// если, на пути стою я сам.
	{
		bird.life = 0;
		MyHero->hp -= bird.dmg;
		MyHero->MyKiller = bird.Attacker;
		return 0;
	}

	else if (levelSize[dx][dy] != 0)
	{
		for (auto &x : vBody)
		if (x.cx == dx&&x.cy == dy){ x.hp -= bird.dmg; bird.life = 0; x.MyKiller = bird.Attacker; break; }
		return 0;
	}
	return 0;
}

void RuinesMap::flyDeath()
{
	int dFlag = 0;
	int count = 0;
	for (auto &x : vMA)
	{
		if (x.life == 0)
		{
			dFlag = 1;
			break;
		}
		count++;
	}
	if (dFlag == 1)
	{
		MA[(vMA.begin() + count)->cx][(vMA.begin() + count)->cy] = 0;
		vMA.erase(vMA.begin() + count);
		dFlag = 0;
	}
}

void RuinesMap::SetMyHero(Body&MyLovelyHero)
{
	MyHero = &MyLovelyHero;
	MyLovelyHero.role = 9;
	int cx, cy;

	if (vDoor.size()<2)
	for (;;)
	{
		cx = rand() % sizeMap;
		cy = rand() % sizeMap;
		if (levelSize[cx][cy] == 0)
		{
			levelSize[cx][cy] = MyLovelyHero.role;
			MyLovelyHero.cx = cx;
			MyLovelyHero.cy = cy;
			std::cout << "SetMyHero" << std::endl;
			break;
		}
	}
}

void RuinesMap::PushUp(Body&MyLovelyHero) //функция выбирающая расположение для нас, когда мы появляемся на этаж вверх.
{
	MyHero = &MyLovelyHero;

	for (auto &x : vDoor)
	if (x.io == 0)
	{
		std::cout << "PushUp" << std::endl;
		if (levelSize[x.cx][x.cy + 1] == 0){ MyHero->cx = x.cx; MyHero->cy = x.cy + 1; break; }
		else if (levelSize[x.cx + 1][x.cy + 1] == 0){ MyHero->cx = x.cx + 1; MyHero->cy = x.cy + 1; break; }
		else if (levelSize[x.cx + 1][x.cy] == 0){ MyHero->cx = x.cx + 1; MyHero->cy = x.cy; break; }
		else if (levelSize[x.cx + 1][x.cy - 1] == 0){ MyHero->cx = x.cx + 1; MyHero->cy = x.cy - 1; break; }
		else if (levelSize[x.cx][x.cy - 1] == 0){ MyHero->cx = x.cx; MyHero->cy = x.cy - 1; break; }
		else if (levelSize[x.cx - 1][x.cy - 1] == 0){ MyHero->cx = x.cx - 1; MyHero->cy = x.cy - 1; break; }
		else if (levelSize[x.cx - 1][x.cy] == 0){ MyHero->cx = x.cx - 1; MyHero->cy = x.cy; break; }
		else if (levelSize[x.cx - 1][x.cy + 1] == 0){ MyHero->cx = x.cx - 1; MyHero->cy = x.cy + 1; break; }
	}
	levelSize[MyLovelyHero.cx][MyLovelyHero.cy] = 9;
}

void RuinesMap::PushDown(Body&MyLovelyHero)//функция выбирающая расположение для нас, когда мы появляемся на этаж вниз.
{
	MyHero = &MyLovelyHero;

	for (auto &x : vDoor)
	if (x.io == 1)
	{
		std::cout << "PushDown" << std::endl;
		if (levelSize[x.cx][x.cy + 1] == 0){ MyHero->cx = x.cx; MyHero->cy = x.cy + 1; break; }
		else if (levelSize[x.cx + 1][x.cy + 1] == 0){ MyHero->cx = x.cx + 1; MyHero->cy = x.cy + 1; break; }
		else if (levelSize[x.cx + 1][x.cy] == 0){ MyHero->cx = x.cx + 1; MyHero->cy = x.cy; break; }
		else if (levelSize[x.cx + 1][x.cy - 1] == 0){ MyHero->cx = x.cx + 1; MyHero->cy = x.cy - 1; break; }
		else if (levelSize[x.cx][x.cy - 1] == 0){ MyHero->cx = x.cx; MyHero->cy = x.cy - 1; break; }
		else if (levelSize[x.cx - 1][x.cy - 1] == 0){ MyHero->cx = x.cx - 1; MyHero->cy = x.cy - 1; break; }
		else if (levelSize[x.cx - 1][x.cy] == 0){ MyHero->cx = x.cx - 1; MyHero->cy = x.cy; break; }
		else if (levelSize[x.cx - 1][x.cy + 1] == 0){ MyHero->cx = x.cx - 1; MyHero->cy = x.cy + 1; break; }
	}
	levelSize[MyLovelyHero.cx][MyLovelyHero.cy] = 9;
}

int RuinesMap::Shot(Body*rhs, int dir)
{
	//if (rhs->inventory.arrow > 0)
	//{
	int r;
	if (rhs->ag > 25)r = 7;
	else r = 5;
	vMA.push_back(MAmap(rhs, dir, Arrow, r));
	MA[rhs->cx][rhs->cy] = 1;
	rhs->tiktak += rhs->shotS;
	return 3;
	//}
	//return 0;
}

void RuinesMap::NewMapMan()
{
	int i = 1, cx, cy, role;
	for (;;)
	{
		cx = rand() % sizeMap;
		cy = rand() % sizeMap;
		if (levelSize[cx][cy] == 0)
		{
			vBody.push_back(Body(role, cx, cy, lvl));
			levelSize[cx][cy] = role;
			break;
		}
	}
}

void RuinesMap::DrawInterface()
{
	int z = wHeight / 30;
	int tx = mx / z;
	int ty = my / z;
	int xpos = wWidth / 5;
	int ypos = wHeight / 5;
	int xxpos = xpos + (z * 17) - 4;
	int yypos = ypos + (z * 17) - 4;

	if (mx>xpos&&my>ypos&&mx<xxpos&&my<yypos)
	{
		glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex2f(tx*z, ty*z);
		glVertex2f(tx*z, (ty*z) + z);
		glVertex2f(tx*z, (ty*z) + z);
		glVertex2f((tx*z) + z, (ty*z) + z);
		glColor3f(1, 1, 1);
		glEnd();
	}
}


int RuinesMap::Draw()
{
	int x = 0, y = 0;
	int z = wHeight / sizeMap;
	for (int i = 0; i < sizeMap; i++)
	for (int j = 0; j < sizeMap; j++)
	{
		if (levelSize[j][i] != 0)
		{

			switch (levelSize[j][i])
			{
			case 1:glBindTexture(GL_TEXTURE_2D, tails.textures[1]); break;
			case 2:glBindTexture(GL_TEXTURE_2D, tails.textures[2]); break;
			case 3:glBindTexture(GL_TEXTURE_2D, tails.textures[2]); break;
			case 4:glBindTexture(GL_TEXTURE_2D, tails.textures[1]); break;
			case 9:glBindTexture(GL_TEXTURE_2D, tails.textures[4]); break;
			case 999:glBindTexture(GL_TEXTURE_2D, tails.textures[2]);	 break;	// стена.
			default:glBindTexture(GL_TEXTURE_2D, tails.textures[0]);	 break;
			}
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex2f(i*z, j*z);
			glTexCoord2f(0.0, 1.0); glVertex2f(i*z, j*z + z);
			glTexCoord2f(1.0, 1.0); glVertex2f(i*z + z, j*z + z);
			glTexCoord2f(1.0, 0.0); glVertex2f(i*z + z, j*z);
			glColor3f(1, 1, 1);
			glEnd();
		}
	}


	return 0;
}

void RuinesMap::DrawFly()
{
	int xpos = wWidth / 5;
	int ypos = wHeight / 5;
	int z = 800 / 30;
	int range = 8;
	int rRange = (range * 2) + 1;
	int startx;
	int starty;
	int ii = 0;
	int jj = 0;

	if ((MyHero->cx - range) <= 0) startx = 0;
	else
	if ((MyHero->cx + range) >= sizeMap)  startx = sizeMap - rRange;
	else
		startx = MyHero->cx - range;


	if ((MyHero->cy - range) <= 0) starty = 0;
	else
	if ((MyHero->cy + range) >= sizeMap)  starty = sizeMap - rRange;
	else
		starty = MyHero->cy - range;


	for (int i = starty, ii = 0; i < (starty + rRange); i++, ii++)
	{
		for (int j = startx, jj = 0; j < (startx + rRange); j++, jj++)
		{
			if (MA[j][i] != 0)
			{
				switch (MA[j][i])
				{
				case 1:glBindTexture(GL_TEXTURE_2D, tails.textures[3]); break;	//отрисовка стрелы.
					//case 2:glBindTexture(GL_TEXTURE_2D, tails.textures[1]); break;
					//case 3:glBindTexture(GL_TEXTURE_2D, tails.textures[1]); break;
					//case 4:glBindTexture(GL_TEXTURE_2D, tails.textures[1]); break;
					//case 9:glBindTexture(GL_TEXTURE_2D, tails.textures[4]); break;
					//case 999:glBindTexture(GL_TEXTURE_2D, tails.textures[2]); break;	// стена.
					//default:glBindTexture(GL_TEXTURE_2D, tails.textures[0]); break;
				}
				glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex2f((ii*z) + xpos, (jj*z) + ypos);
				glTexCoord2f(0.0, 1.0); glVertex2f((ii*z) + xpos, (jj*z) + ypos + z);
				glTexCoord2f(1.0, 1.0); glVertex2f((ii*z) + xpos + z, (jj*z) + ypos + z);
				glTexCoord2f(1.0, 0.0); glVertex2f((ii*z) + xpos + z, (jj*z) + ypos);
				glEnd();
			}
		}
	}

}

void RuinesMap::WhatIsee()
{
	int xpos = wWidth / 5;
	int ypos = wHeight / 5;
	int z = wHeight / 30;
	int range = 8;
	int rRange = (range * 2) + 1;
	int ii = 0;
	int jj = 0;

	if ((MyHero->cx - range) <= 0) startx = 0;
	else
	if ((MyHero->cx + range) >= sizeMap)  startx = sizeMap - rRange;
	else
		startx = MyHero->cx - range;


	if ((MyHero->cy - range) <= 0) starty = 0;
	else
	if ((MyHero->cy + range) >= sizeMap)  starty = sizeMap - rRange;
	else
		starty = MyHero->cy - range;


	for (int i = starty, ii = 0; i < (starty + rRange); i++, ii++)
	{
		for (int j = startx, jj = 0; j < (startx + rRange); j++, jj++)
		{
			if (levelSize[j][i] != 0)
			{
				switch (levelSize[j][i])
				{
				case 1:glBindTexture(GL_TEXTURE_2D, tails.textures[0]); break;	//рожа
				case 2:glBindTexture(GL_TEXTURE_2D, tails.textures[8]); break;	//рожа
				case 3:glBindTexture(GL_TEXTURE_2D, tails.textures[1]); break;  //рожа
				case 4:glBindTexture(GL_TEXTURE_2D, tails.textures[1]); break;  //рожа
				case 9:glBindTexture(GL_TEXTURE_2D, tails.textures[4]); break;		//герой
				case 999:glBindTexture(GL_TEXTURE_2D, tails.textures[2]); break;	// стена.
				case 666:glBindTexture(GL_TEXTURE_2D, tails.textures[6]); break;	//вниз
				case 777:glBindTexture(GL_TEXTURE_2D, tails.textures[5]); break;	//вверх
				default:glBindTexture(GL_TEXTURE_2D, tails.textures[0]); break;    //рожа
				}
				glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex2f((ii*z) + xpos, (jj*z) + ypos);
				glTexCoord2f(0.0, 1.0); glVertex2f((ii*z) + xpos, (jj*z) + ypos + z);
				glTexCoord2f(1.0, 1.0); glVertex2f((ii*z) + xpos + z, (jj*z) + ypos + z);
				glTexCoord2f(1.0, 0.0); glVertex2f((ii*z) + xpos + z, (jj*z) + ypos);
				glEnd();
			}
		}
	}
}

void RuinesMap::MapGen()
{
	std::cout << "MAP GEN" << std::endl;
	int x, y;
	int temp = rand() % 20 + 27;	// рандомно выбираем количество комнат.

	for (int count = 0; count < 10000 && temp != 0; count++)
	{
		int flagm = 0;
		int rSizex = rand() % 12 + 7; // размер по оси икс и игрик, делаем от 2 до 8.
		int rSizey = rand() % 12 + 7;

		x = rand() % (sizeMap - 1);			//выбираем рандомную точку на карте, для создания комнаты.
		y = rand() % (sizeMap - 1);
		if (x != (sizeMap - 2))x++;
		if (y != (sizeMap - 2))y++;

		int tempxpp;				//будет хранить наибольную координату икс
		int tempxmm;				//будет хранить наименьшую координату икс
		int tempypp;				//будет хранить наибольную координату игрик
		int tempymm;				//будет хранить наименьшую координату игрик
		if ((x - (rSizex / 2)) <= 0) tempxmm = 1;	// если комната хочет выйти за предел, обрезаем её.
		else tempxmm = (x - (rSizex / 2));			//если нет, то выдаем ей значение 
		if ((x + (rSizex / 2)) >= sizeMap - 1) tempxpp = sizeMap - 2;
		else tempxpp = (x + (rSizex / 2));
		if ((y - (rSizey / 2)) <= 0) tempymm = 1;
		else tempymm = y - (rSizex / 2);
		if ((y + (rSizey / 2)) >= sizeMap) tempypp = sizeMap - 2;
		else tempypp = y + (rSizex / 2);


		if (count != 0)
		{
			for (int i = tempxmm; i < tempxpp; i++)
			for (int j = tempymm; j < tempypp; j++)
			if (levelSize[i][j] != 999){ flagm = 1; break; }
		}

		if (flagm == 0)
		{
			for (int i = tempxmm; i < tempxpp; i++)
			for (int j = tempymm; j < tempypp; j++)
			{
				levelSize[i][j] = 0;
			}


			int flagxy = 0;
			for (int i = tempxmm - 1; i < tempxpp + 1; i++)
			for (int j = tempymm - 1; j < tempypp + 1; j++)
			{
				if (i == (tempxmm - 1) || i == (tempxpp + 1))
				if (levelSize[i][j] != 999)
					flagxy++;

				if (j == (tempymm - 1) || j == (tempypp + 1))
				if (levelSize[i][j] != 999)
					flagxy++;

			}

			if (flagxy == 0)
			{
				RL.push_back(Point(x, y));
			}
			temp--;
		}
	}

	for (int c1 = 0; c1 < sizeMap; c1++)
	for (int c2 = 0; c2 < sizeMap; c2++)
	{
		if (c1 == 0 || c1 == sizeMap - 1 || c2 == 0 || c2 == sizeMap - 1)
			levelSize[c1][c2] = 1999;
	}

	PatchFound();
	checkdiag();

	for (int c1 = 0; c1 < sizeMap; c1++)
	for (int c2 = 0; c2 < sizeMap; c2++)
	{
		if (c1 == 0 || c1 == sizeMap - 1 || c2 == 0 || c2 == sizeMap - 1)
			levelSize[c1][c2] = 999;
	}
}

void RuinesMap::checkdiag()
{
	for (int i = 1; i < sizeMap - 1; i++)
	for (int j = 1; j < sizeMap - 1; j++)
	{
		if (levelSize[i][j] == 999)
		if (levelSize[i + 1][j + 1] == 999)
		if (levelSize[i + 1][j] == 0 && levelSize[i][j + 1] == 0)
		if (rand() % 2)
			levelSize[i][j] = 0;
		else
			levelSize[i + 1][j + 1] = 0;
	}

	for (int i = 1; i < sizeMap - 1; i++)
	for (int j = 1; j < sizeMap - 1; j++)
	{
		if (levelSize[i][j] == 0)
		if (levelSize[i + 1][j + 1] == 0)
		if (levelSize[i + 1][j] == 999 && levelSize[i][j + 1] == 999)
		if (rand() % 2)
			levelSize[i + 1][j] = 0;
		else
			levelSize[i][j + 1] = 0;
	}
}

void RuinesMap::PatchFound()
{
	std::cout << "RL.Size" << RL.size() << std::endl;
	int v = RL.size();
	for (auto &xxx : RL)
	{
		Point *x = &xxx;
		Point *xx = &xxx;
		xx++;
		if (v == 1)break;
		generatePassage(*x, *xx);
		v--;
	}
}

void RuinesMap::generatePassage(const Point &start, const Point &finish)
{
	// для хранения направления на "родительскую" клетку
	std::vector<int> parents(sizeMap * sizeMap, -1);
	// приоритетная очередь доступных клеток, отсортирована по "стоимости"
	std::priority_queue<Point> active;
	active.push(start);

	// направления возможных перемещений
	static const int directions[4][2] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
	while (!active.empty())
	{
		// берем самую "дешевую" клетку из списка доступных
		const Point point = active.top();
		active.pop();

		if (point == finish)
			break;

		// продолжаем поиск в доступных направлениях
		for (int i = 0; i < 4; ++i) {
			Point p(point.x - directions[i][0], point.y - directions[i][1]);
			if (p.x < 0 || p.y < 0 || p.x >= sizeMap || p.y >= sizeMap)
				continue;

			// если мы еще не посещали заданную клетку
			if (parents[p.x + p.y * sizeMap] < 0) {
				// вычисляем "стоимость" указанной клетки
				//p.cost = calcCost(p, finish);
				p.cost = levelSize[p.x][p.y];
				active.push(p);

				parents[p.x + p.y * sizeMap] = i;
			}
		}
	}

	// путь найден - теперь прокладываем его на карте, начиная с конца
	Point point = finish;
	while (!(point == start)) {
		levelSize[point.x][point.y] = 0;

		const int *directon = directions[parents[point.x + point.y * sizeMap]];
		point.x += directon[0];
		point.y += directon[1];
	}
}

void RuinesMap::AI(Body*rhs)
{
	if (TactikMap[rhs->cx][rhs->cy] != 1)
	{
		//lowHp(rhs);
		switch (Scaner(rhs, 10))
		{
		case 0:rMove(*rhs); break;	// когда мы не видим врага.
		case 1:
			switch (rhs->role)// 1 воин. 2 лучник . 3 маг.
			{
			case 1: AIPF(rhs); break;
			case 2: if (Scaner(rhs, 7)){ CTM(); Archer(rhs); AFP(rhs); }
					else AIPF(rhs); break;
			case 3: AIPF(rhs); break;
			default:break;
			}

		default:
			break;
		}
	}
	else
	{
		std::cout << "DODGE" << std::endl;
		if (TactikMap[rhs->cx][rhs->cy + 1] != 1)Move(rhs->cx, rhs->cy + 1, rhs);
		else if (TactikMap[rhs->cx + 1][rhs->cy + 1] != 1)Move(rhs->cx + 1, rhs->cy + 1, rhs);
		else if (TactikMap[rhs->cx + 1][rhs->cy] != 1)Move(rhs->cx + 1, rhs->cy, rhs);
		else if (TactikMap[rhs->cx + 1][rhs->cy - 1] != 1)Move(rhs->cx + 1, rhs->cy - 1, rhs);
		else if (TactikMap[rhs->cx][rhs->cy - 1] != 1)Move(rhs->cx, rhs->cy - 1, rhs);
		else if (TactikMap[rhs->cx - 1][rhs->cy - 1] != 1)Move(rhs->cx - 1, rhs->cy - 1, rhs);
		else if (TactikMap[rhs->cx - 1][rhs->cy] != 1)Move(rhs->cx - 1, rhs->cy, rhs);
		else if (TactikMap[rhs->cx - 1][rhs->cy + 1] != 1)Move(rhs->cx - 1, rhs->cy + 1, rhs);
		else AIPF(rhs);
	}
}

void RuinesMap::CTM()
{
	for (int i = 0; i < sizeMap; i++)
	for (int j = 0; j < sizeMap; j++)
	if (levelSize[i][j] == 999) ShotMap[i][j] = levelSize[i][j];
	else ShotMap[i][j] = 0;
}

int RuinesMap::AFP(Body*rhs)	// логика лучника.
{
	int xx = MyHero->cx - rhs->cx;
	int yy = MyHero->cy - rhs->cy;

	if (ShotMap[rhs->cx][rhs->cy] == 1)
	{
		if (xx == 0 && yy > 0 && CheckDir(0, rhs) != 0)Shot(rhs, 0);
		else if (xx > 0 && yy > 0 && CheckDir(1, rhs) != 0)Shot(rhs, 1);
		else if (xx > 0 && yy == 0 && CheckDir(2, rhs) != 0)Shot(rhs, 2);
		else if (xx > 0 && yy < 0 && CheckDir(3, rhs) != 0)Shot(rhs, 3);
		else if (xx == 0 && yy < 0 && CheckDir(4, rhs) != 0)Shot(rhs, 4);
		else if (xx < 0 && yy < 0 && CheckDir(5, rhs) != 0)Shot(rhs, 5);
		else if (xx < 0 && yy == 0 && CheckDir(6, rhs) != 0)Shot(rhs, 6);
		else if (xx < 0 && yy > 0 && CheckDir(7, rhs) != 0)Shot(rhs, 7);
		else if (Scaner(rhs, 1)){ Move(MyHero->cx, MyHero->cy, rhs); }
		else { std::cout << "AIPF next" << std::endl; AIPF(rhs); }
	}

	else if (ShotMap[rhs->cx][rhs->cy + 1] == 1 && levelSize[rhs->cx][rhs->cy + 1] == 0)Move(rhs->cx, rhs->cy + 1, rhs);
	else if (ShotMap[rhs->cx + 1][rhs->cy + 1] == 1 && levelSize[rhs->cx + 1][rhs->cy + 1])Move(rhs->cx + 1, rhs->cy + 1, rhs);
	else if (ShotMap[rhs->cx + 1][rhs->cy] != 1 && levelSize[rhs->cx + 1][rhs->cy])Move(rhs->cx + 1, rhs->cy, rhs);
	else if (ShotMap[rhs->cx + 1][rhs->cy - 1] == 1 && levelSize[rhs->cx + 1][rhs->cy - 1])Move(rhs->cx + 1, rhs->cy - 1, rhs);
	else if (ShotMap[rhs->cx][rhs->cy - 1] == 1 && levelSize[rhs->cx][rhs->cy - 1])Move(rhs->cx, rhs->cy - 1, rhs);
	else if (ShotMap[rhs->cx - 1][rhs->cy - 1] == 1 && levelSize[rhs->cx - 1][rhs->cy - 1])Move(rhs->cx - 1, rhs->cy - 1, rhs);
	else if (ShotMap[rhs->cx - 1][rhs->cy] == 1 && levelSize[rhs->cx - 1][rhs->cy])Move(rhs->cx - 1, rhs->cy, rhs);
	else if (ShotMap[rhs->cx - 1][rhs->cy + 1] == 1 && levelSize[rhs->cx - 1][rhs->cy + 1])Move(rhs->cx - 1, rhs->cy + 1, rhs);
	else { std::cout << "AIPF next" << std::endl; AIPF(rhs); }

	return 0;
}

int RuinesMap::CheckDir(int dir, Body*rhs)	// смотрит что бы мобы не постреляли друг друга. типо стреляем так, что бы все могли увернуться.
{
	int x = rhs->cx;
	int y = rhs->cy;

	for (int i = 0; i < 4; i++)
	{
		switch (dir)
		{
		case 0:	y++; break;
		case 1:	x++; y++; break;
		case 2:	x++; break;
		case 3:	x++; y--; break;
		case 4:	y--; break;
		case 5:	x--; y--; break;
		case 6:	x--; break;
		case 7:	x--; y++; break;
		default:std::cout << "ERROR in ChekDir(int dir, Body*rhs) func" << std::endl; break;
		}
		if (levelSize[x][y] == 1 || levelSize[x][y] == 2 || levelSize[x][y] == 3){
			std::cout << "I CANT FIRE ON My FREINDS!" << std::endl;	return 0;
		}
	}
	return 1;
}

void RuinesMap::Archer(Body*rhs)
{
	for (int i = 0; i < sizeMap; i++)
	for (int j = 0; j < sizeMap; j++)
	if (levelSize[i][j] == 999) ShotMap[i][j] = levelSize[i][j];
	else ShotMap[i][j] = 0;
	ShotMap[MyHero->cx][MyHero->cy] = 1;
	int xx = MyHero->cx;
	int yy = MyHero->cy;
	for (int i = 0; i < 7 && ShotMap[xx][++yy] != 999; i++) ShotMap[xx][yy] = 1;
	yy = MyHero->cy; xx = MyHero->cx;
	for (int i = 0; i < 7 && ShotMap[++xx][++yy] != 999; i++) ShotMap[xx][yy] = 1;
	yy = MyHero->cy; xx = MyHero->cx;
	for (int i = 0; i < 7 && ShotMap[++xx][yy] != 999; i++) ShotMap[xx][yy] = 1;
	yy = MyHero->cy; xx = MyHero->cx;
	for (int i = 0; i < 7 && ShotMap[++xx][--yy] != 999; i++) ShotMap[xx][yy] = 1;
	yy = MyHero->cy; xx = MyHero->cx;
	for (int i = 0; i < 7 && ShotMap[xx][--yy] != 999; i++) ShotMap[xx][yy] = 1;
	yy = MyHero->cy; xx = MyHero->cx;
	for (int i = 0; i < 7 && ShotMap[--xx][--yy] != 999; i++) ShotMap[xx][yy] = 1;
	yy = MyHero->cy; xx = MyHero->cx;
	for (int i = 0; i < 7 && ShotMap[--xx][yy] != 999; i++) ShotMap[xx][yy] = 1;
	yy = MyHero->cy; xx = MyHero->cx;
	for (int i = 0; i < 7 && ShotMap[--xx][++yy] != 999; i++) ShotMap[xx][yy] = 1;



	/*	for (int i = 0; i < sizeMap; i++){
	for (int j = 0; j < sizeMap; j++)
	{
	if (levelSize[i][j]!=999)std::cout << ShotMap[i][j];
	else std::cout << "*";
	}
	std::cout << std::endl;
	}
	*/

}

int RuinesMap::Scaner(Body*rhs, int r)
{
	int radius = r;
	if (abs((rhs->cx) - (MyHero->cx)) < radius && abs((rhs->cy) - (MyHero->cy)) < radius)
		return 1;
	else
		return 0;
}

int RuinesMap::AIPF(Body*rhs)//AI Path Founder
{
#define zTOP_LEFT myPatch[i - 1][j + 1]
#define zTOP_RIGHT myPatch[i + 1][j + 1]
#define zTOP myPatch[i][j + 1]
#define zBOT_LEFT myPatch[i - 1][j - 1]
#define zBOT_RIGHT myPatch[i + 1][j - 1]
#define zBOT myPatch[i][j - 1]
#define zLEFT myPatch[i - 1][j]
#define zRIGHT myPatch[i + 1][j]

	int myPatch[sizeMap][sizeMap];
	for (int i = 0; i < sizeMap; i++)
	for (int j = 0; j < sizeMap; j++)
		myPatch[i][j] = -3;

	for (int i = 0; i < sizeMap; i++)
	for (int j = 0; j < sizeMap; j++)
	if (levelSize[i][j])myPatch[i][j] = -9;

	for (int i = 0; i < sizeMap; i++)
	for (int j = 0; j < sizeMap; j++)
	if (TactikMap[i][j])myPatch[i][j] = -9;

	myPatch[rhs->cx][rhs->cy] = -3;
	myPatch[MyHero->cx][MyHero->cy] = 0;

	for (int z = 0; myPatch[rhs->cx][rhs->cy] == (-3); z++)
	{
		for (int i = 0; i < sizeMap; i++)
		for (int j = 0; j < sizeMap; j++)
		if (myPatch[i][j] == z)
		{
			if (zTOP == -3)	zTOP = (z + 1);
			if (zTOP_RIGHT == -3)	zTOP_RIGHT = (z + 1);
			if (zRIGHT == -3)	zRIGHT = (z + 1);
			if (zBOT_RIGHT == -3)	zBOT_RIGHT = (z + 1);
			if (zBOT == -3)	zBOT = (z + 1);
			if (zBOT_LEFT == -3)	zBOT_LEFT = (z + 1);
			if (zLEFT == -3)	zLEFT = (z + 1);
			if (zTOP_LEFT == -3)	zTOP_LEFT = (z + 1);
		}
		if (z>15){ rMove(*rhs); return 0; }
	}

	int temp[sizeMap][sizeMap];
	for (int i = sizeMap - 1; i >= 0; i--)
	for (int j = sizeMap - 1; j >= 0; j--)
		temp[i][j] = 0;

	for (int i = sizeMap - 1; i >= 0; i--)
	for (int j = sizeMap - 1; j >= 0; j--)
	if (levelSize[i][j] == 999) temp[i][j] = 9;


	int tx = rhs->cx;
	int ty = rhs->cy;

	for (; myPatch[tx][ty] != 0;)
	{
		int t = myPatch[tx][ty] - 1;

		if (myPatch[tx][ty + 1] == t){
			ty++; temp[tx][ty] = 1;
		}
		else if (myPatch[tx + 1][ty] == t){
			tx++; temp[tx][ty] = 1;
		}
		else if (myPatch[tx][ty - 1] == t){
			ty--; temp[tx][ty] = 1;
		}
		else if (myPatch[tx - 1][ty] == t){
			tx--; temp[tx][ty] = 1;
		}
		else if (myPatch[tx + 1][ty + 1] == t){
			tx++; ty++; temp[tx][ty] = 1;
		}
		else if (myPatch[tx + 1][ty - 1] == t){
			tx++; ty--; temp[tx][ty] = 1;
		}
		else if (myPatch[tx - 1][ty - 1] == t){
			tx--; ty--; temp[tx][ty] = 1;
		}
		else if (myPatch[tx - 1][ty + 1] == t){
			tx--; ty++; temp[tx][ty] = 1;
		}
	}

	if (temp[rhs->cx][rhs->cy + 1] == 1){ Move(rhs->cx, rhs->cy + 1, rhs); }
	else if (temp[rhs->cx + 1][rhs->cy + 1] == 1){ Move(rhs->cx + 1, rhs->cy + 1, rhs); }
	else if (temp[rhs->cx + 1][rhs->cy] == 1){ Move(rhs->cx + 1, rhs->cy, rhs); }
	else if (temp[rhs->cx + 1][rhs->cy - 1] == 1) { Move(rhs->cx + 1, rhs->cy - 1, rhs); }
	else if (temp[rhs->cx][rhs->cy - 1] == 1) { Move(rhs->cx, rhs->cy - 1, rhs); }
	else if (temp[rhs->cx - 1][rhs->cy - 1] == 1){ Move(rhs->cx - 1, rhs->cy - 1, rhs); }
	else if (temp[rhs->cx - 1][rhs->cy] == 1) { Move(rhs->cx - 1, rhs->cy, rhs); }
	else if (temp[rhs->cx - 1][rhs->cy + 1] == 1){ Move(rhs->cx - 1, rhs->cy + 1, rhs); }
	else std::cout << "ERROR IN AIPF(Body*rhs) func!" << std::endl;
	return 0;
}

void RuinesMap::lowHp(Body*rhs)
{
	if (rhs->hp < rhs->maxhp)
		Heal(rhs);
}

void RuinesMap::Heal(Body*rhs)
{
	std::cout << rhs->hp << std::endl;
	std::cout << "Monster try heal" << std::endl;
}