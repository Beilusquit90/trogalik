#include "stdafx.h"
#include "Body.h"
#include <iostream>
#include <stdlib.h>

int flags = 0;

Body::Body()
{
	inventory.addr();
	hp = 1; ag = 1; str = 1; intel = 1; tiktak = 0;
	switch (role = rand() % 3 + 1) // 1 воин. 2 лучник . 3 маг.
	{
	case 1:str += 2;   break;
	case 2:ag += 2;    break;
	case 3:intel += 2; break;
	}

	
	int temp = 1 + rand() % 6;		// задаем рандомную надбавку на статы. =)
	for (int count = 0; count < temp; count++)
	{
		int i = rand() % 4 + 1;
		if (i == 1)maxhp++;
		if (i == 2)ag++;
		if (i == 3)str++;
		if (i == 4)intel++;
	}
	sKoef();
	//std::cout << "STANDART CONSTRUCTOR"<< std::endl;

}

Body::Body(Body *rhs){
	std::cout << "WARNING" << std::endl;
}


Body::Body(int&_role,int x,int y,int lvl):cx(x),cy(y) //раскидываем статы, в зависимости от уровня подземелья.
{
	inventory.addr();
	exp = lvl * 10;
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
		if (i == 1)maxhp++;
		if (i == 2)ag++;
		if (i == 3)str++;
		if (i == 4)intel++;
	}
	sKoef();
	/*std::cout << "HP:" << hp << "  Ag:" << ag << "  Str" << str << "  Intelect:" << intel << "  role" << role << std::endl;
	std::cout << colldownS << "colldownS" << std::endl;
	std::cout << attackS << "attackS" << std::endl;
	std::cout << fizCDS << "fizCDS" << std::endl;
	std::cout << moveS << "moveS" << std::endl;
	std::cout << rundiagonalS << "rundiagonalS" << std::endl;
	std::cout << meditationS << "meditationS" << std::endl;
	std::cout << shotS << "shotS" << std::endl;
	std::cout << jumpSpeed << "jumpSpeed" << std::endl;
	*/
	}



Body::Body(const Body&rhs)
{
	inventory = rhs.inventory;
	mana = rhs.mana;
	maxmana = rhs.maxmana;
	maxhp = rhs.maxhp;
	exp = rhs.exp;
	hp = rhs.hp;
	ag = rhs.str;
	str = rhs.str;
	intel = rhs.intel;
	cx = rhs.cx;
	cy = rhs.cy;
	tiktak = rhs.tiktak;		//Таймер... от него зависит то, сколько ты пропустишь.
	role = rhs.role;
	colldownS = rhs.colldownS; // скорость на колдунство.
	attackS = rhs.attackS; // скорость физ атаки.
	fizCDS=rhs.fizCDS;	// скорость физ умений.
	moveS=rhs.moveS; // скорость ходьбы.
	rundiagonalS = rhs.rundiagonalS; // скорость ходьбы на искосок.
	meditationS = rhs.meditationS;  // скорость медитации восстановления маны и хп.
	shotS=rhs.shotS;  // выстрела скорость.
	jumpSpeed=rhs.jumpSpeed; // скорость прыжка назад или вперед.
}

Body::~Body()
{
//	std::cout << "BODY DIE`S..." << std::endl;
}

void Body::operator=(const Body&rhs)
{
	inventory = rhs.inventory;
	mana = rhs.mana;
	maxmana = rhs.maxmana;
	maxhp = rhs.maxhp;
	exp = rhs.exp;
	hp = rhs.hp;
	ag = rhs.str;
	str = rhs.str;
	intel = rhs.intel;
	cx = rhs.cx;
	cy = rhs.cy;
	tiktak = rhs.tiktak;		//Таймер... от него зависит то, сколько ты пропустишь.
	role = rhs.role;
	colldownS = rhs.colldownS; // скорость на колдунство.
	attackS = rhs.attackS; // скорость физ атаки.
	fizCDS = rhs.fizCDS;	// скорость физ умений.
	moveS = rhs.moveS; // скорость ходьбы.
	rundiagonalS = rhs.rundiagonalS; // скорость ходьбы на искосок.
	meditationS = rhs.meditationS;  // скорость медитации восстановления маны и хп.
	shotS = rhs.shotS;  // выстрела скорость.
	jumpSpeed = rhs.jumpSpeed; // скорость прыжка назад или вперед.

}


void Body::sKoef()
{

	
	colldownS = (50 - intel / 2)*0.01;						// скорость на колдунство.
	attackS = (50 - (ag / 2))*0.01;						// скорость физ атаки.
	fizCDS = (100 - ((ag / 4) + (str / 4)))*0.01;		// скорость физ умений.
	moveS = (50 - (ag / 4) + (hp / 7))*0.01;			// скорость ходьбы.
	rundiagonalS = moveS*1.5;								// скорость ходьбы на искосок.
	meditationS = 0.50;									// скорость медитации восстановления маны и хп.
	shotS = (70 - (ag / 2))*0.01;						// выстрела скорость.
	jumpSpeed = (70 - (ag / 2))*0.01;					// скорость прыжка назад или вперед.

/*	std::cout << colldownS << "colldownS" << std::endl;
	std::cout << attackS << "attackS" << std::endl;
	std::cout << fizCDS << "fizCDS" << std::endl;
	std::cout << moveS << "moveS" << std::endl;
	std::cout << rundiagonalS << "rundiagonalS" << std::endl;
	std::cout << meditationS << "meditationS" << std::endl;
	std::cout << shotS << "shotS" << std::endl;
	std::cout << jumpSpeed << "jumpSpeed" << std::endl;
	*/
}
