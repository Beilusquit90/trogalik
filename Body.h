#pragma once
class RuinesMap;

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

	int role;
	int hp;
	int ag;
	int str;
	int intel;
	int cx;
	int cy;
	float tiktak;		//Таймер... от него зависит то, сколько ты пропустишь.
	float colldownS;	// скорость на колдунство.
	float attackS;		// скорость физ атаки.
	float fizCDS;		// скорость физ умений.
	float moveS;		// скорость ходьбы.
	float rundiagonalS; // скорость ходьбы на искосок.
	float meditationS;  // скорость медитации восстановления маны и хп.
	float shotS;		// выстрела скорость.
	float jumpSpeed;	// скорость прыжка назад или вперед.
};



