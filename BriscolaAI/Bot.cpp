#include "Bot.h"

Bot::Bot()
{
	n = new NeuralNetwork();
	cardState = new std::vector<double>(40);
	briscola = -1;
	reset();
}

Bot::Bot(Bot* parent)
{
	n = new NeuralNetwork(parent->n);
	cardState = new std::vector<double>(40);
	briscola = -1;
	reset();
}

Bot::~Bot()
{
	delete n;
	cardState->clear();
	delete cardState;
}

//returns card index
int Bot::getPlayingCard(int onTable)
{
	std::vector<double> t;
	t.push_back(cardsInHand[0]);
	t.push_back(cardsInHand[1]);
	t.push_back(cardsInHand[2]);
	t.push_back(static_cast<double>(onTable));
	t.push_back(static_cast<double>(briscola));
	t.insert(t.end(), cardState->begin(), cardState->end());

	auto o = n->getOutputs(t, 3);
	int toPlay = 0;
	bool found = false;
	for (int i = 0; i < 3; i++) {
		if ((!found ? -DBL_MAX : o[toPlay]) < o[i] && cardsInHand[i] != -1) {
			toPlay = i;
			found = true;
		}
	}
	if (!found) throw;
	auto out = static_cast<int>(cardsInHand[toPlay]);
	cardsInHand[toPlay] = -1;
	cardState->at(out) = 5;
	return out;
}

void Bot::giveCard(int card)
{
	for (int i = 0; i < 3; i++) {
		if (cardsInHand[i] == -1) {
			cardsInHand[i] = card;
			cardState->at(card) = i + 1;
			return;
		}
	}
}

void Bot::cardPlayed(int card)
{
	cardState->at(card) = 4;
}

void Bot::turnEnded(int cardA, int cardB, bool isWinner)
{
	cardState->at(cardA) = 5;
	cardState->at(cardB) = 5;

	if (!isWinner) return;
	score += getCardScore(cardA) + getCardScore(cardB);
}

void Bot::reset()
{
	for (int i = 0; i < 40; i++) {
		cardState->at(i) = 0;
	}
	for (int i = 0; i < 3; i++) {
		cardsInHand[i] = -1;
	}
	score = 0;
}

void Bot::setBriscola(int card)
{
	briscola = card / 10;
	cardState->at(card) = 6;
}
