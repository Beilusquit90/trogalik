#pragma once

#include "bag.h"

class Body
{
public:
	Body();
	Body(Body *rhs);
	Body(int&_role,int x, int y, int lvl);// получает в качестве параметра левел на котором ГГ, что бы расчитать статы мобов. =)
	Body(const Body&rhs);
	~Body();

	void operator=(const Body&rhs);
	void sKoef();
	int exp;
	int role;
	int hp;
	int maxhp;
	int ag;
	int str;
	int intel;
	int cx;
	int cy;
	double tiktak;		//Таймер... от него зависит то, сколько ты пропустишь.
	double colldownS;	// скорость на колдунство.
	double attackS;		// скорость физ атаки.
	double fizCDS;		// скорость физ умений.
	double moveS;		// скорость ходьбы.
	double rundiagonalS; // скорость ходьбы на искосок.
	double meditationS;  // скорость медитации восстановления маны и хп.
	double shotS;		// скорость выстрела.
	double jumpSpeed;	// скорость прыжка назад или вперед.
	bag inventory;
	int mana;
	int maxmana;
	Body *MyKiller;		//ну ты понял че.
};



