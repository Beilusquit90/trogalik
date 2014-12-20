#pragma once
#include <vector>
#include "Body.h"
#include "roomList.h"

const int sizeMap = 50;

class RuinesMap
{
public:
	RuinesMap();		
	RuinesMap(int lvl);				//+
	RuinesMap(const RuinesMap&rhs); //+
    void operator=( RuinesMap&rhs); //+
	~RuinesMap();					//+
	void Add(int lvl);
	int Activ( );
	int Draw( );
	void NewMapMan();
	void rMove(Body&x);
	int Move(int x, int y,Body*rhs);
	void test();
	void CreateLvl();
	void SetMyHero(Body&MyLovelyHero);
	void Attack(int x,int y,Body*rhs);
	void WhoDie();
	void MapGen();
	void checkdiag();


	void PatchFound();

	
	
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
	};
	void generatePassage(const Point &start, const Point &finish);
private:
	int levelSize[sizeMap][sizeMap];			//массив содержащий отметки существ.
	int MAE[sizeMap][sizeMap];				//карта магии и стрел, запущенные врагами
	int MA[sizeMap][sizeMap];					//карта нашей магии и стрел.
	int patchOfTheMoon[sizeMap][sizeMap];		// не самый удачный эксперимент, посмотрим что выйдет.
	std::vector<Body>vBody;			
	int lvl;
	Body *MyHero;
	std::vector<Point>RL;
};