#pragma once
class roomList
{
public:
	roomList(int _x, int _y, int _txpp,int _txmm,int _typp,int _tymm) :x(_x), y(_y),txpp(_txpp),txmm(_txmm),typp(_typp),tymm(_tymm){}
	~roomList(){}
	int x;
	int y;
	int txpp;				//����� ������� ���������� ���������� ���
	int txmm;				//����� ������� ���������� ���������� ���
	int typp;				//����� ������� ���������� ���������� �����
	int tymm;
};

