// сделал читабельные комменты
#include "stdafx.h"
#include "RuinesMap.h"
#include <vector>
#include <iostream>
#include <gl\glut.h>
#include <queue>  

extern const int sizeMap;

RuinesMap::RuinesMap()
{
	lvl = 1;
	for (int i = 0; i < sizeMap; i++)
	for (int j = 0; j < sizeMap; j++)
		levelSize[i][j] = 0;
	CreateLvl();
	int temp = (rand() % 6) + 5;
	std::cout << "TEMPO" << temp << std::endl;
	for (int i = 0; i < temp; i++)
	{
		NewMapMan();
	}
	//test();
}


RuinesMap::RuinesMap(const RuinesMap&rhs)
{
	vBody = rhs.vBody;
	for (int i = 0; i < sizeMap; i++)
	for (int j = 0; j < sizeMap; j++)
	{
		levelSize[i][j] = rhs.levelSize[i][j];
	}
	lvl = rhs.lvl;
	//test();
}

void RuinesMap::operator=(RuinesMap&rhs)
{
	for (int i = 0; i < sizeMap; i++)
	for (int j = 0; j < sizeMap; j++)
		levelSize[j][i] = rhs.levelSize[j][i];
	lvl = rhs.lvl;
	//test();
}

RuinesMap::RuinesMap(int _lvl)
{
	lvl = _lvl;
	for (int i = 0; i < sizeMap; i++)
	for (int j = 0; j < sizeMap; j++)
		levelSize[i][j] = 0;
	CreateLvl();
	int temp = (rand() % 6) + 15;
	for (int i = 0; i < temp; i++)
	{
		NewMapMan();
	}
	//test();
}


RuinesMap::~RuinesMap()
{
	//std::cout << "RuinesMAp DIE`S..." << std::endl;
}

void RuinesMap::Attack(int _x, int _y, Body*rhs)
{
	int count=0;
	if (levelSize[_x][_y] == 9)
	{
		MyHero->hp -= rhs->str;
		
	}
	for (auto &x : vBody)
	{
		if (x.cx == _x&&x.cy == _y)
		{
			vBody[count].hp -= rhs->str;
			std::cout << "ATTACK" << std::endl;
		}
		count++;
	}
}

int RuinesMap::Move(int x,int y,Body*rhs)
{
	//std::cout << levelSize[x][y] << std::endl;
	if (x >= 0 && x<sizeMap)
	if (y >= 0 && y<sizeMap)
	{	
		if (levelSize[x][y] == 999) return 0;
		if (levelSize[x][y] == 0)	//проверка на свободный путь.
		{
			levelSize[rhs->cx][rhs->cy] = 0;
			rhs->cx = x;
			rhs->cy = y;
			levelSize[rhs->cx][rhs->cy] = rhs->role;
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
	{
		levelSize[x][y] = 999;
	}

	MapGen();
	std::cout << "MAP GEN FINISH" << std::endl;
}


void RuinesMap::rMove(Body&x) // заставляет убогих, совершать рандомное движение. На крайний случай, anotherMove
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
			case 0: i = Move(x.cx, x.cy + 1, &x);			x.tiktak += x.moveS;	 break;  // вроде вверх
			case 1: i = Move(x.cx + 1, x.cy + 1, &x);	x.tiktak += x.rundiagonalS;; break;
			case 2: i = Move(x.cx + 1, x.cy, &x);			x.tiktak += x.moveS;	 break;
			case 3: i = Move(x.cx + 1, x.cy - 1, &x);	x.tiktak += x.rundiagonalS;  break;
			case 4: i = Move(x.cx, x.cy - 1, &x);			x.tiktak += x.moveS;	 break;
			case 5: i = Move(x.cx - 1, x.cy - 1, &x);	x.tiktak += x.rundiagonalS;  break;
			case 6: i = Move(x.cx - 1, x.cy, &x);				x.tiktak += x.moveS; break;
			case 7: i = Move(x.cx - 1, x.cy + 1, &x);	x.tiktak += x.rundiagonalS;  break;
			default:						break;
			}
		}
}

void RuinesMap::WhoDie()
{
	int dFlag = 0;
	int count = 0;
	for (auto &x:vBody)
	{
		if (x.hp <= 0)
		{
			levelSize[x.cx][x.cy] = 0;
			dFlag = 1;
			break;
		}
		count++;
	}
	if (dFlag==1)
	{		vBody.erase(vBody.begin() + count);
		std::cout << "ONE DIE NOW!!!" << std::endl;
		dFlag = 0;
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
	MyHero = &MyLovelyHero;
	MyLovelyHero.role = 9;
	//MyLovelyHero.hp = 1000;
	int i = 1, cx, cy;
		 
	for (;;)
	{
		cx = rand() % sizeMap;
		cy = rand() % sizeMap;
		if (levelSize[cx][cy] == 0)
		{
			//std::cout << "x" << cx << "   y" << cy << std::endl;
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
		cx = rand() % sizeMap;
		cy = rand() % sizeMap;
		if (levelSize[cx][cy] == 0)
		{
		//	std::cout << "x" << cx << "   y" << cy << std::endl;
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
	int z = 800 / sizeMap;
	for (int i = 0; i < sizeMap; i++)
	for (int j = 0; j < sizeMap; j++)
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
			default:glColor3f(1, 0.0, 0.0); break;
			}
			for (int count = 0; count < z; count++)
			{
				for (int count2 = 0; count2 < z; count2++){
					glVertex2f(i*z, j*z);
					glVertex2f(i*z + count, j*z + count2);}
			}
		}
	}

	glEnd();
	return 0;
}


void RuinesMap::MapGen()
{
	std::cout << "MAP GEN" << std::endl;
	int x, y;
		int temp = rand() % 20+20;	// рандомно выбираем количество комнат.
		
		for (int count = 0; count < 10000&&temp!=0; count++)
		{
			int flagm = 0;
			int rSizex = rand() % 15 + 7; // размер по оси икс и игрик, делаем от 2 до 8.
			int rSizey = rand() % 15 + 7;

			x = rand() % (sizeMap-1);			//выбираем рандомную точку на карте, для создания комнаты.
			y = rand() % (sizeMap-1);
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


			if (count!=0)
			{
				for (int i = tempxmm; i < tempxpp;i++)
				for (int j = tempymm; j < tempypp;j++)
				if (levelSize[i][j] != 999){ flagm = 1; }
			}

			if (flagm == 0)
			{
				for (int i = tempxmm; i < tempxpp; i++)
				for (int j = tempymm; j < tempypp; j++)
				{
					levelSize[i][j] = 0;
				}
				RL.push_back(Point(x, y));
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
	for (int i = 1; i < sizeMap-1; i++)
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
			levelSize[i+1][j] = 0;
		else
			levelSize[i][j + 1] = 0;
	}
}

void RuinesMap::PatchFound()
{
	std::cout << "RL.Size" << RL.size()<<std::endl;
	int v = RL.size();
	 for (auto &xxx:RL)
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
				p.cost = levelSize[p.x][p.y] ;
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
