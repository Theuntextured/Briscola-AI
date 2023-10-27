#include "Player.h"

Player::Player()
{
	cardsInHand[0] = -1;
	cardsInHand[1] = -1;
	cardsInHand[2] = -1;
	score = 0;
}

int Player::getPlayingCard(int onTable, int briscola, int cardsLeft)
{
	int toPlay;
	int i;

	std::cout << "On table is: " << getCardName(onTable) << "\nBriscola is: " << getCardName(briscola) << "\nCards left in deck: " << cardsLeft << "\nCards in hand: " << getCardName(cardsInHand[0]) << ", " << getCardName(cardsInHand[1]) << ", " << getCardName(cardsInHand[2]) << "\nEnter the card index to play (1-3): ";

	while (true) {
		std::cin >> i;
		if (i <= 3 && i > 0 && cardsInHand[i - 1] != -1) {
			toPlay = cardsInHand[i - 1];
			cardsInHand[i - 1] = -1;
			return toPlay;
		}
		std::cout << i << " is not a valid index.\n";
	}
}

void Player::giveCard(int card)
{
	for (int i = 0; i < 3; i++) {
		if (cardsInHand[i] == -1) {
			cardsInHand[i] = card;
			return;
		}
	}
}

void Player::turnEnded(int cardA, int cardB, bool isWinner)
{
	if (!isWinner) return;
	score += getCardScore(cardA) + getCardScore(cardB);
}
