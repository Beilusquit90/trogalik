#include "stdafx.h"
#include "MAmap.h"




MAmap::MAmap(Body*rhs, int dir, Meffects eff, int r) :direction(dir), Attacker(rhs), effect(eff), range(r)
{
	cx = Attacker->cx;
	cy = Attacker->cy;
	life = 1;
	tiktak = 0;
	if (eff == Arrow)
	{
		//dmg = (Attacker->ag / 2) + (Attacker->str / 4);
		dmg = 50;
	}

	if (eff == fireball)
	{
		dmg = Attacker->intel;
		if (Attacker->intel > 25)r = 7;	else r = 5;
	}
	
}
MAmap::MAmap(const MAmap&rhs)
{
	Attacker = rhs.Attacker;
	direction = rhs.direction;
	effect = rhs.effect;
	dmg = rhs.dmg;
	range = rhs.range;
	cx = rhs.cx, cy = rhs.cy;
	element = rhs.element;		//потом реализую, огонь вода ко ко ко.
	tiktak = rhs.tiktak;
	life = rhs.life;
}

MAmap::MAmap(MAmap*rhs)
{
	Attacker = rhs->Attacker;
	direction=rhs->direction;
	 effect=rhs->effect;
	 dmg=rhs->dmg;
	 range=rhs->range;
	 cx=rhs->cx, cy=rhs->cy;
	 element=rhs->element;		//потом реализую, огонь вода ко ко ко.
	 tiktak=rhs->tiktak;
	 life=rhs->life;
}

MAmap::~MAmap()
{
	
}

void MAmap::operator=(const MAmap&rhs)
{
	Attacker = rhs.Attacker;
	direction = rhs.direction;
	effect = rhs.effect;
	dmg = rhs.dmg;
	range = rhs.range;
	cx = rhs.cx, cy = rhs.cy;
	element = rhs.element;		//потом реализую, огонь вода ко ко ко.
	tiktak = rhs.tiktak;
	life = rhs.life;
}