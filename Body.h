#pragma once
class RuinesMap;

class Body
{
public:
	Body(int&_role,int x, int y, int lvl);// �������� � �������� ��������� ����� �� ������� ��, ��� �� ��������� ����� �����.
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



