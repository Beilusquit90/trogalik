#pragma once
#include <vector>
#include "Body.h"
#include "MAmap.h"
#include "TheDoor.h"


const int sizeMap = 50;

class RuinesMap
{
public:
	class Point
	{
	public:
		Point(int _x, int _y) :x(_x), y(_y){}
		int x, y, cost;

		bool operator==(const Point &p) const {
			return x == p.x && y == p.y;
		}

		bool operator<(const Point &p) const {
			return cost > p.cost;
		}
	};  // нужно для поиска пути
	RuinesMap();		
	RuinesMap(int lvl);				//+
	RuinesMap(const RuinesMap&rhs); //+
    void operator=( RuinesMap&rhs); //+
	~RuinesMap();					//+
	//конструкторы и прочая лабуда выше.

	void SetMF(int x){ mflag = x; }
	void MousePress(int button, int  state, int x, int y);
	void mMouse(int button, int  state, int x, int y);


	void StepsFind(const Point &start, const Point &finish);
	int CreateSteps(int tx,int ty);
	int Step();
	int Activ();						// старт функция для аи мобов\стрелл\магии
	void rMove(Body&x);					//временная функция, для рандомных шагов монстров.
	void flyDeath();					// функция отвечающая за смерть стрелл и заклинаний.
	int fly(MAmap&rhs);					//летающие стрелы и магия.
	int Move(int x, int y, Body*rhs);	// функция для ходьбы по 8 направлениям
	void Attack(int x, int y, Body*rhs);//говорящее название
	int Shot(Body*rhs, int dir);
	void WhoDie();
	// обсчет всяких действий и действия выше.
	

	void DrawInterface();
	int Draw();
	void WhatIsee();					//функция отрисовки того что видим.
	void DrawFly();						//отрисовка летящей магии и стрелл.
	//отрисовка выше



	//AI ZONE*****************
	//тут мы собственно разместим все функции относящиеся к аи.
	void AI(Body*rhs);


	void lowHp(Body*rhs);		//проверка уровня хп.
	void Heal(Body*rhs);
	int Scaner(Body*rhs,int r);		//скнанирует по радиусу.
	
	
	int AIPF(Body*rhs);		
	void Archer(Body*rhs);
	int AFP(Body*rhs);

	void DangerBirds(int dx, int dy, MAmap&bird);
	void ClearTactikMap();
	//AI ZONE*****************



	void PushUp(Body&MyLovelyHero);
	void PushDown(Body&MyLovelyHero);
	void SetMyHero(Body&MyLovelyHero);
	void Doors();						//расставляем двери.
	void NewMapMan();					//генерация и расстановка нового моба.
	void CreateLvl();
	void MapGen();
	void checkdiag();
	void PatchFound();

	void generatePassage(const Point &start, const Point &finish);
	//всякие генерации выше
	

	void test();
	int ioflag; 
	int mflag;
	std::vector<int>steps;
private:
	int levelSize[sizeMap][sizeMap];			//массив содержащий отметки существ.
	int MMA[sizeMap][sizeMap];				//Массовая магия, особая так сказать...
	int MA[sizeMap][sizeMap];					//карта магии и стрел.

	int Patch[sizeMap][sizeMap];

	int TactikMap[sizeMap][sizeMap];
	int ShotMap[sizeMap][sizeMap];
	std::vector<MAmap>vMA;
	std::vector<Body>vBody;	
	std::vector<TheDoor>vDoor;
	std::vector<Point>RL;
	
	int startx;
	int starty;
	
	int lvl;
	Body *MyHero;
};