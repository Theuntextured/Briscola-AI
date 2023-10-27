#pragma once
#include <iostream>
#include <string>
#include "ProjectLib.h"

class Player
{
public:
	Player();
	int getPlayingCard(int onTable, int briscola, int cardsLeft);
	void giveCard(int card);
	void turnEnded(int cardA, int cardB, bool isWinner);

	int cardsInHand[3];
	int score;
};

