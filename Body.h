#pragma once
class RuinesMap;

class Body
{
public:
	Body(int&_role,int x, int y, int lvl);// получает в качестве параметра левел на котором √√, что бы расчитать статы мобов.
	Body(const Body&rhs);
	~Body();
	void operator=(const Body&rhs);

	int role;
	int hp;
	int ag;
	int str;
	int intel;
	int cx;
	int cy;
	int tiktak;
};



