#include "ProjectLib.h"

vec2i::vec2i()
{
	x = 0;
	y = 0;
}

vec2i::vec2i(int x, int y)
{
	this->x = x;
	this->y = y;
}

vec3i::vec3i()
{
	x = 0;
	y = 0;
	z = 0;
}

vec3i::vec3i(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

int vec3i::toLinear(int sizeX, int sizeY) {
	return z * sizeX * sizeY + y * sizeX + x;;
}

int vec2i::toLinear(int sizeX) {
	return y * sizeX + x;
}

vec2i fromLinear(int pos, int sizeX) {
	return vec2i(pos % sizeX, pos / sizeX);
}

vec3i fromLinear(int pos, int sizeX, int sizeY) {
	int z = pos / (sizeX * sizeY);
	pos -= (z * sizeX * sizeY);
	return vec3i(pos % sizeX, pos / sizeX, z);
}

double rnd(double LO, double HI)
{
	return static_cast<double>(rand()) / static_cast<double>(RAND_MAX / (HI - LO)) + LO;
}

bool chance(double c)
{
	return rnd(0, 1) <= c;
}

//briscola is 0 to 39
int getCardScore(int card, int briscola, int firstCard)
{
	int t = card % 10;
	int additive = 0;
	if (briscola != -1) {
		if (card / 10 == briscola / 10) {
			additive += 100;
		}
		if (card / 10 == firstCard / 10) {
			additive += 50;
		}
		additive += t;
		if (t == 0 || t == 2 || t == 9 || t == 8 || t == 7) additive += 15;
	}
	switch (t)
	{
	default:
		return 0 + additive;
	case 2:
		return 10 + additive;
	case 0:
		return 11 + additive;
	case 7:
		return 2 + additive;
	case 8:
		return 3 + additive;
	case 9:
		return 4 + additive;
	}
}

/*
Order:
 - Denari
 - Bastoni
 - Spade
 - Coppe
*/
std::string getCardName(int c) {
	if (c == -1) return "None";
	std::string s = std::to_string(c % 10 + 1);
	s += " ";
	switch (c / 10) {
	default:
		return s;
	case 0:
		s += "Denari";
		return s;
	case 1:
		s += "Bastoni";
		return s;
	case 2:
		s += "Spade";
		return s;
	case 3:
		s += "Coppe";
		return s;
	}
}