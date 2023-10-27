#include "Game.h"

Game::Game(Bot* p1, Bot* p2)
{
	this->p1 = p1;
	this->p2 = p2;
	p = nullptr;

	if (!p2) p = new Player();

	onTable = -1;

	deck = new std::vector<int>(40);
	for (int i = 0; i < 40; i++) {
		deck->at(i) = i;
	}
	shuffleVector(*deck);
}

Game::~Game()
{
	deck->clear();
	delete deck;
}

//returns winner
Bot* Game::startGame()
{
	//give initial cards
	giveCard(p1);
	giveCard(p2);
	giveCard(p1);
	giveCard(p2);
	giveCard(p1);
	giveCard(p2);

	//decide who starts
	bool turnOfP1 = chance(0.5);

	//decide briscola
	int briscola = deck->at(0);
	p1->setBriscola(briscola);
	if(p2) p2->setBriscola(briscola);

	//run until cards run out
	int t;
	int v1;
	int v2;
	do {
		if(p2)
		{
			//get both to play cards
			onTable = (turnOfP1 ? p1 : p2)->getPlayingCard(-1);
			(!turnOfP1 ? p1 : p2)->cardPlayed(onTable);
			t = (!turnOfP1 ? p1 : p2)->getPlayingCard(onTable);

			v1 = getCardScore(onTable, briscola, onTable);
			v2 = getCardScore(t, briscola, onTable);

			
			(turnOfP1 ? p1 : p2)->turnEnded(onTable, t, v1 >= v2);
			(!turnOfP1 ? p1 : p2)->turnEnded(onTable, t, v2 > v1);
		}
		else {
			if (turnOfP1) {
				onTable = p1->getPlayingCard(-1);
				std::cout << "AI played " << getCardName(onTable) << std::endl;
				t = p->getPlayingCard(onTable, briscola, deck->size());
				std::cout << "You played " << getCardName(t) << std::endl;

				v1 = getCardScore(onTable, briscola, onTable);
				v2 = getCardScore(t, briscola, onTable);

				p1->turnEnded(onTable, t, v1 >= v2);
				p->turnEnded(onTable, t, v2 > v1);
				std::cout << (v1 < v2 ? "You" : "AI") << " won the round and got " << getCardScore(onTable) + getCardScore(t) << " points.\n\n";
			}
			else {
				onTable = p->getPlayingCard(-1, briscola, deck->size());
				std::cout << "You played " << getCardName(onTable) << std::endl;
				p1->cardPlayed(onTable);
				t = p1->getPlayingCard(-1);
				std::cout << "AI played " << getCardName(t) << std::endl;

				v1 = getCardScore(onTable, briscola, onTable);
				v2 = getCardScore(t, briscola, onTable);

				p1->turnEnded(onTable, t, v1 < v2);
				p->turnEnded(onTable, t, v2 <= v1);
				std::cout << (v1 < v2 ? "AI" : "You") << " won the round and got " << getCardScore(onTable) + getCardScore(t) << " points.\n\n";
			}
		}
		//set new beginner
		turnOfP1 = (v1 >= v2) == turnOfP1;

	} while (giveCard(p1) && giveCard(p2));

	if (p2)	{
		if (p1->score > p2->score) return p1;
		if (p1->score < p2->score) return p2;
		return nullptr;
	}
	if (!p2) std::cout << p1->score << std::endl;
	return (p1->score > p->score) ? p1 : nullptr;
}

bool Game::giveCard(Bot* b)
{
	int u = 0;
	if (deck->size() == 0) {
		for (int i = 0; i < 3; i++) {
			if (b) {
				u += static_cast<int>(b->cardsInHand[i]);
			}
			else {
				u += static_cast<int>(p->cardsInHand[i]);
			}
		}
		if (u == -3) return false;
		return true;
	}
	if (b) b->giveCard(deck->at(deck->size() - 1));
	else p->giveCard(deck->at(deck->size() - 1));
	deck->pop_back();
	return true;
}
