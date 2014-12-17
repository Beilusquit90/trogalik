#include "stdafx.h"
#include "Body.h"
#include <iostream>
#include <stdlib.h>
#include "RuinesMap.h"
int flags = 0;

Body::Body()
{
	hp = 1; ag = 1; str = 1; intel = 1; tiktak = 0;
	switch (role = rand() % 3 + 1) // 1 ����. 2 ������ . 3 ���.
	{
	case 1:str += 2;   break;
	case 2:ag += 2;    break;
	case 3:intel += 2; break;
	}

	
	int temp = 1 + rand() % 6;		// ������ ��������� �������� �� �����. =)
	for (int count = 0; count < temp; count++)
	{
		int i = rand() % 4 + 1;
		if (i == 1)hp++;
		if (i == 2)ag++;
		if (i == 3)str++;
		if (i == 4)intel++;
	}
	sKoef();
	std::cout << "STANDART CONSTRUCTOR"<< std::endl;

}

Body::Body(Body *rhs){
	std::cout << "WARNING" << std::endl;
}



Body::Body(int&_role,int x,int y,int lvl):cx(x),cy(y) //����������� �����, � ����������� �� ������ ����������.
{
	hp = 1; ag = 1; str = 1; intel = 1; tiktak = 0;
	switch (role = rand() % 3 + 1) // 1 ����. 2 ������ . 3 ���.
	{
	case 1:str += 2;   break;
	case 2:ag += 2;    break;
	case 3:intel += 2; break;
	}
	
	_role = role;
	int temp = lvl + rand()%6;		// ������ ��������� �������� �� �����.
	for (int count = 0; count < temp; count++)
	{
		int i=rand() % 4 + 1;
		if (i == 1)hp++;
		if (i == 2)ag++;
		if (i == 3)str++;
		if (i == 4)intel++;
	}
	sKoef();
	std::cout << "HP:" << hp << "  Ag:" << ag << "  Str" << str << "  Intelect:" << intel << "  role" << role << std::endl;
	std::cout << colldownS << "colldownS" << std::endl;
	std::cout << attackS << "attackS" << std::endl;
	std::cout << fizCDS << "fizCDS" << std::endl;
	std::cout << moveS << "moveS" << std::endl;
	std::cout << rundiagonalS << "rundiagonalS" << std::endl;
	std::cout << meditationS << "meditationS" << std::endl;
	std::cout << shotS << "shotS" << std::endl;
	std::cout << jumpSpeed << "jumpSpeed" << std::endl;
}



Body::Body(const Body&rhs)
{
	hp = rhs.hp;
	ag = rhs.str;
	str = rhs.str;
	intel = rhs.intel;
	cx = rhs.cx;
	cy = rhs.cy;
	tiktak = rhs.tiktak;		//������... �� ���� ������� ��, ������� �� ����������.
	role = rhs.role;
	colldownS = rhs.colldownS; // �������� �� ����������.
	attackS = rhs.attackS; // �������� ��� �����.
	fizCDS=rhs.fizCDS;	// �������� ��� ������.
	moveS=rhs.moveS; // �������� ������.
	rundiagonalS = rhs.rundiagonalS; // �������� ������ �� �������.
	meditationS = rhs.meditationS;  // �������� ��������� �������������� ���� � ��.
	shotS=rhs.shotS;  // �������� ��������.
	jumpSpeed=rhs.jumpSpeed; // �������� ������ ����� ��� ������.
}

Body::~Body()
{
	std::cout << "BODY DIE`S..." << std::endl;

}

void Body::operator=(const Body&rhs)
{
	hp = rhs.hp;
	ag = rhs.str;
	str = rhs.str;
	intel = rhs.intel;
	cx = rhs.cx;
	cy = rhs.cy;
	tiktak = rhs.tiktak;		//������... �� ���� ������� ��, ������� �� ����������.
	role = rhs.role;
	colldownS = rhs.colldownS; // �������� �� ����������.
	attackS = rhs.attackS; // �������� ��� �����.
	fizCDS = rhs.fizCDS;	// �������� ��� ������.
	moveS = rhs.moveS; // �������� ������.
	rundiagonalS = rhs.rundiagonalS; // �������� ������ �� �������.
	meditationS = rhs.meditationS;  // �������� ��������� �������������� ���� � ��.
	shotS = rhs.shotS;  // �������� ��������.
	jumpSpeed = rhs.jumpSpeed; // �������� ������ ����� ��� ������.

}


void Body::sKoef()
{

	
	colldownS = (50 - intel / 2)*0.01;						// �������� �� ����������.
	attackS = (50 - (ag / 2))*0.01;						// �������� ��� �����.
	fizCDS = (100 - ((ag / 4) + (str / 4)))*0.01;		// �������� ��� ������.
	moveS = (50 - (ag / 4) + (hp / 7))*0.01;			// �������� ������.
	rundiagonalS = moveS*1.5;								// �������� ������ �� �������.
	meditationS = 0.50;									// �������� ��������� �������������� ���� � ��.
	shotS = (70 - (ag / 2))*0.01;						// �������� ��������.
	jumpSpeed = (70 - (ag / 2))*0.01;					// �������� ������ ����� ��� ������.

	std::cout << colldownS << "colldownS" << std::endl;
	std::cout << attackS << "attackS" << std::endl;
	std::cout << fizCDS << "fizCDS" << std::endl;
	std::cout << moveS << "moveS" << std::endl;
	std::cout << rundiagonalS << "rundiagonalS" << std::endl;
	std::cout << meditationS << "meditationS" << std::endl;
	std::cout << shotS << "shotS" << std::endl;
	std::cout << jumpSpeed << "jumpSpeed" << std::endl;

}
