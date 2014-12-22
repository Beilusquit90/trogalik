#pragma once
class TheDoor
{
public:
	TheDoor();
	TheDoor(const TheDoor&rhs);
	TheDoor(int _lvl, int _cx, int _cy);
	void operator=(TheDoor&rhs);
	~TheDoor();
	int io;		// вверх или вниз.
	int cx;
	int cy;
};