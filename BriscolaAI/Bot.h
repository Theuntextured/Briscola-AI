#pragma once
#include "NeuralNetwork.h"

class Bot
{
public:
	NeuralNetwork* n;

	/*
	0 = unseen
	1 = in hand 1
	2 = in hand 2
	3 = in hand 3
	4 = on table
	5 = taken
	6 = bottom of deck
	*/
	std::vector<double>* cardState;
	double cardsInHand[3];
	int score;
	int briscola;

	Bot();
	Bot(Bot* parent);
	~Bot();
	int getPlayingCard(int onTable);
	void giveCard(int card);
	void cardPlayed(int card);
	void turnEnded(int cardA, int cardB, bool isWinner);
	void reset();
	void setBriscola(int card);
};

