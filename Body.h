#pragma once
class RuinesMap;

class Body
{
public:
	Body();
	Body(int lvl, RuinesMap &_rm);// �������� � �������� ��������� ����� �� ������� ��, ��� �� ��������� ����� �����.
	Body(int lvl, RuinesMap*_rm);
	~Body();
	Body(const Body&rhs);
	void operator=(Body&rhs);
	void NewMapMan(); // �������� �� ����� ����� ��� ���� �� ����
	int move(int x, int y); // �� ����,  ������ ������ ��� �� ��� ����� ������� ������
	void dMap(); //������� � ����� ���� �� ����� �����������.
	void sMap(); // �� �� ������.
	void test();
	void rMove();
	void anotherMove(){};
private:
	int hp;
	int ag;
	int str;
	int intel;
	int cx;
	int cy;
	int tiktak;
	int role;
	RuinesMap * rm;
};



