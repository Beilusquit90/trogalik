// сделал читабельные комменты
#include "stdafx.h"
#include "RuinesMap.h"
#include <vector>
#include <iostream>
#include <gl\glut.h>
#include <queue>  
#include "TileTextures.h"

extern TileTextures tails;
extern const int sizeMap;


RuinesMap::RuinesMap()
{
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
	//test();
}

RuinesMap::RuinesMap(int _lvl)
{
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

void RuinesMap::Doors()	// рандомно пихает дверушку.
{
	int x, y;
	if (lvl == 1)
	{
		for (int z = 0; z == 0;)
		{
			x = rand() % sizeMap;
			y = rand() % sizeMap;
			if (levelSize[x][y] == 0)
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
			if (levelSize[x][y] == 0)
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
			if (levelSize[x][y] == 0)
			{
				z = 1;
				levelSize[x][y] = 777;
				vDoor.push_back(TheDoor(0, x, y));
			}
		}
	}
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
			vBody[count].MyKiller = rhs;
			std::cout << "ATTACK" << std::endl;
		}
		count++;
	}
}



int RuinesMap::Move(int x,int y,Body*rhs)
{
	if (x >= 0 && x<sizeMap)
	if (y >= 0 && y<sizeMap)
	{	

		if (levelSize[x][y] == 666 || levelSize[x][y] == 777)
		if (rhs == MyHero)
		{
			if (levelSize[x][y] == 666)ioflag = 1;
			if (levelSize[x][y] == 777)ioflag = 2;
			std::cout << "Nice Try" << levelSize[x][y] << std::endl;
			return 1;
		}

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
	flyDeath();

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
	if (dFlag == 1)
	{
		(vBody.begin() + count)->MyKiller->exp += (vBody.begin() + count)->exp;		//отдаем опыт моему убийце.
		std::cout << (vBody.begin() + count)->MyKiller->exp << std::endl;
			vBody.erase(vBody.begin() + count);
		dFlag = 0;
	}
}

int RuinesMap::Activ( )
{

	for (auto &act : vMA)
	{
		if (act.tiktak <= 0)
			
			fly(act);
		else
			act.tiktak -= 0.2;
	}


	for (auto &act : vBody)
	{
		if (act.tiktak <= 0)
			rMove(act);
		else
			act.tiktak -= 0.2;
	}



	
return 0;
}

int RuinesMap::fly(MAmap&bird)
{
	int dx, dy;
	if (bird.direction == 0){ dx = bird.cx;	dy = bird.cy + 1; }
	if (bird.direction == 1){ dx = bird.cx + 1;	dy = bird.cy + 1;}
	if (bird.direction == 2){ dx = bird.cx + 1;	dy = bird.cy;}
	if (bird.direction == 3){ dx = bird.cx + 1;	dy = bird.cy - 1;}
	if (bird.direction == 4){ dx = bird.cx;	dy = bird.cy - 1;}
	if (bird.direction == 5){ dx = bird.cx - 1;	dy = bird.cy - 1;}
	if (bird.direction == 6){ dx = bird.cx - 1;	dy = bird.cy;}
	if (bird.direction == 7){ dx = bird.cx - 1;	dy = bird.cy + 1;}

	if (levelSize[dx][dy] == 999){
		bird.life = 0; return 0; }

	if (MA[dx][dy] != 0)
	{
		
		for (auto &x : vMA)
		{
			if (x.cx == dx&&x.cy == dy){ x.life = 0; bird.life = 0; break; }
			
		}
		return 0;
	}
	
	if (levelSize[dx][dy] == 0)
	{
		MA[bird.cx][bird.cy] = 0;
		bird.cx = dx;
		bird.cy = dy;
		MA[dx][dy] = bird.effect;
		bird.tiktak += 0.2;
		return 0;
	}

	if (levelSize[dx][dy] == 9)		// если, на пути стою я сам.
	{
		bird.life = 0;
		MyHero->hp -= bird.dmg;
		MyHero->MyKiller = bird.Attacker;
		return 0;
	}

	if (levelSize[dx][dy] != 0)
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

int RuinesMap::Shot(Body*rhs,int dir)
{
	if (rhs->inventory.arrow > 0)
	{
		int r;
		if (rhs->ag > 25)r = 7;
		else r = 5;
		vMA.push_back(MAmap(rhs, dir, Arrow, r));
		MA[rhs->cx][rhs->cy] = 1;
		return 3;
	}
	return 0;
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

/*
int RuinesMap::Draw()
{
	//for (auto ma : vMA)	ma.Draw();	//отрисовка стрелл и магии на карте.

	//glColor3f(0.6, 0.4, 0.6);
	int x = 0, y = 0;
	int z = 800 / sizeMap;
	for (int i = 0; i < sizeMap; i++)
	for (int j = 0; j < sizeMap; j++)
	{
		if (levelSize[j][i]!= 0 )
		{
			
			switch (levelSize[j][i])
			{
			case 1:glBindTexture(GL_TEXTURE_2D, tails.textures[1]); break;
			case 2:glBindTexture(GL_TEXTURE_2D, tails.textures[2]); break;
			case 3:glBindTexture(GL_TEXTURE_2D, tails.textures[2]); break;
			case 4:glBindTexture(GL_TEXTURE_2D, tails.textures[1]);
			case 9:glBindTexture(GL_TEXTURE_2D, tails.textures[4]); break;
			case 999:glBindTexture(GL_TEXTURE_2D, tails.textures[2]);	 break;	// стена.
			default:glBindTexture(GL_TEXTURE_2D, tails.textures[0]);	 break;
			}
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex2f(i*z, j*z);
			glTexCoord2f(0.0, 1.0); glVertex2f(i*z, j*z + z);
			glTexCoord2f(1.0, 1.0); glVertex2f(i*z + z, j*z + z);
			glTexCoord2f(1.0, 0.0); glVertex2f(i*z + z, j*z);
			glEnd();
		}
	}

	
	return 0;
}
*/
void RuinesMap::DrawFly()
{}

void RuinesMap::WhatIsee()
{

	int xpos=800/5;
	int ypos=800/5;
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

	
	for (int i = starty, ii=0; i < (starty + rRange); i++,ii++)
	{
		for (int j = startx, jj=0; j < (startx + rRange); j++,jj++)
		{
			if (levelSize[j][i] != 0)
			{
							switch (levelSize[j][i])
				{
				case 1:glBindTexture(GL_TEXTURE_2D, tails.textures[0]); break;	//рожа
				case 2:glBindTexture(GL_TEXTURE_2D, tails.textures[1]); break;	//рожа
				case 3:glBindTexture(GL_TEXTURE_2D, tails.textures[1]); break;  //рожа
				case 4:glBindTexture(GL_TEXTURE_2D, tails.textures[1]); break;  //рожа
				case 9:glBindTexture(GL_TEXTURE_2D, tails.textures[4]); break;		//герой
				case 999:glBindTexture(GL_TEXTURE_2D, tails.textures[2]); break;	// стена.
				default:glBindTexture(GL_TEXTURE_2D, tails.textures[0]); break;    //рожа
				}
				glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex2f((ii*z)+xpos, (jj*z)+ypos);
				glTexCoord2f(0.0, 1.0); glVertex2f((ii*z)+xpos, (jj*z)+ypos + z);
				glTexCoord2f(1.0, 1.0); glVertex2f((ii*z) + xpos + z, (jj*z)+ypos + z);
				glTexCoord2f(1.0, 0.0); glVertex2f((ii*z) + xpos + z, (jj*z)+ypos);
				glEnd();
			}
		}
	}


	
	for (int i = starty, ii = 0; i < (starty + rRange); i++, ii++)
	{
		for (int j = startx, jj = 0; j < (startx + rRange); j++, jj++)
		{
			if (MA[j][i] != 0)
			{
				switch (MA[j][i])
				{
				case 1:glBindTexture(GL_TEXTURE_2D, tails.textures[3]); break;
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
				if (levelSize[i][j] != 999){ flagm = 1; break; }
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