#include "Comb.h"
/*
Comb::Comb()
{
}
*/
Comb::Comb(int a, int b):x(a),y(b),z(-1)
{

}

Comb::Comb(int a, int b, int c):x(a),y(b),z(c)
{
}

Comb::~Comb()
{
}

bool Comb::combEqual(Comb e)
{
	if ((-1 == z) && (-1 == e.z)) {
		if ((x == e.x) && (y == e.y)) return true;
		else return false;
	}
	else if ( (-1 != z) && (-1 != e.z)) {
		if ((x == e.x) && (y == e.y) && (z == e.z)) return true;
		else return false;
	}else
		return false;
}
