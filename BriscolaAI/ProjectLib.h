#pragma once
#include <vector>
#include <cstdlib>
#include <string>

class vec2i {
public:
	vec2i();
	vec2i(int x, int y);

	int x;
	int y;

	int toLinear(int sizeX);
};

class vec3i {
public:
	vec3i();
	vec3i(int x, int y, int z);

	int x;
	int y;
	int z;

	int toLinear(int sizeX, int sizeY);
};

static vec2i fromLinear(int pos, int sizeX);
static vec3i fromLinear(int pos, int sizeX, int sizeY);

double rnd(double LO = 0, double HI = 1);
bool chance(double c);

int getCardScore(int card, int briscola = -1, int firstCard = -1);

template <typename T>
void shuffleVector(std::vector<T>& v);

template<typename T>
inline void shuffleVector(std::vector<T>& v)
{
	std::vector<T> o = v;
	v.clear();
	int t;
	for (int i = o.size() - 1; i >= 0; i--) {
		t = static_cast<int>(rnd(0, i));
		v.push_back(o[t]);
		o.erase(o.begin() + t);
	}
}

std::string getCardName(int c);