#pragma once
class roomList
{
public:
	roomList(int _x, int _y, int _txpp,int _txmm,int _typp,int _tymm) :x(_x), y(_y),txpp(_txpp),txmm(_txmm),typp(_typp),tymm(_tymm){}
	~roomList(){}
	int x;
	int y;
	int txpp;				//будет хранить наибольную координату икс
	int txmm;				//будет хранить наименьшую координату икс
	int typp;				//будет хранить наибольную координату игрик
	int tymm;
};

