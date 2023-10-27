#pragma once
#include "Bot.h"
#include "Player.h"

class Game
{

public:
	Game(Bot* p1, Bot* p2);
	~Game();
	Bot* startGame();
	bool giveCard(Bot* b);
	int onTable;
	Player* p;

	Bot* p1;
	Bot* p2;
	std::vector<int>* deck;
};

