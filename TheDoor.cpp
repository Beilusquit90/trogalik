#include "stdafx.h"
#include "TheDoor.h"


TheDoor::TheDoor()
{
}

TheDoor::TheDoor(const TheDoor&rhs)
{
	io = rhs.io;
	cx = rhs.cx;
	cy = rhs.cy;
}

TheDoor::TheDoor(int _lvl,int _cx,int _cy) :io(_lvl), cx(_cx), cy(_cy)
{
}

TheDoor::~TheDoor()
{
}

void TheDoor::operator=(TheDoor&rhs)
{
	io = rhs.io;
	cx = rhs.cx;
	cy = rhs.cy;
}