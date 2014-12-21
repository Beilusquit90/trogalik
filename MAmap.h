#pragma once
#include "Body.h"
#include <iostream>

enum Meffects
{
	Zero,Arrow, fireball,icebolt
};


class MAmap
{
public:
	MAmap();
	MAmap(Body* rhs, int dir, Meffects eff, int r);
	MAmap(MAmap*rhs);
	MAmap(const MAmap&rhs);
	void operator=(const MAmap&rhs);
	~MAmap();
	Body* Attacker;
	int direction;
	Meffects effect;
	int dmg;
	int range;
	int cx, cy;
	int element;		//потом реализую, огонь вода ко ко ко.
	double tiktak;
	int life;
private:

};

