#pragma once
class RuinesMap;

class Body
{
public:
	Body();
	Body(Body *rhs);
	Body(int&_role,int x, int y, int lvl);// �������� � �������� ��������� ����� �� ������� ��, ��� �� ��������� ����� �����. =)
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
	float tiktak;		//������... �� ���� ������� ��, ������� �� ����������.
	float colldownS;	// �������� �� ����������.
	float attackS;		// �������� ��� �����.
	float fizCDS;		// �������� ��� ������.
	float moveS;		// �������� ������.
	float rundiagonalS; // �������� ������ �� �������.
	float meditationS;  // �������� ��������� �������������� ���� � ��.
	float shotS;		// �������� ��������.
	float jumpSpeed;	// �������� ������ ����� ��� ������.
};



