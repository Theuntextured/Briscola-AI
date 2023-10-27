#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include "Game.h"

#define saveFile "Saved Neural Network.txt"
#define roundsPerGame 10

/*
Order:
 - Denari
 - Bastoni
 - Spade
 - Coppe
*/


int main()
{
	srand(static_cast<unsigned int>(time(0)));

	Bot* p1 = new Bot();
	Bot* p2 = new Bot();
	Game* g;

	std::ifstream loadedFile(saveFile);
	if (loadedFile.is_open()) {
		std::string line;
		std::vector<double> loadedBuffer;
		while (std::getline(loadedFile, line)) {
			if (line == "") break;
			loadedBuffer.push_back(std::stod(line));
		}
		loadedBuffer.resize(nodeDepth * nodeWidth * (nodeWidth + 1));
		*(p1->n->nodes) = loadedBuffer;
		*(p2->n->nodes) = loadedBuffer;
		loadedFile.close();
		std::cout << "Neural network has been loaded.\n";
	}
	else {
		std::cout << "Neural network could not be loaded. Creating a new random one.\n";
	}

	int iterations;

	std::cout << "Iteration count: ";
	std::cin >> iterations;

	std::cout << "Training neural network...\n";
	bool p1Won = false;
	for (int i = 0; i < iterations; i++) {
		vec2i score(0, 0);
		for(int j = 0; j < roundsPerGame; j++)
		{
			g = new Game(p1, p2);
			Bot* winner = g->startGame();
			if (p1 == winner) score.x++;
			if (p2 == winner) score.y++;
			p1->reset();
			p2->reset();
			delete g;
		}
		p1Won = score.x > score.y;
		delete (p1Won ? p2 : p1);
		(p1Won ? p2 : p1) = new Bot((p1Won ? p1 : p2));
	}

	Bot* toSave = (p1Won ? p1 : p2);
	std::ofstream out(saveFile);
	if (out.is_open()) {
		for (int i = 0; i < toSave->n->nodes->size(); i++) {
			out << std::to_string(toSave->n->nodes->at(i));
			out << "\n";
		}
		out.close();
	}

	std::cout << "Training complete.\nPlay against AI? (Y/N) ";
	std::string play;
	std::cin >> play;

	if (play == "N" || play == "n") return 0;

	std::cout << "\n\n\n";
	g = new Game(toSave, nullptr);
	g->startGame();

	std::cout << "AI finished with: " << toSave->score << " points, while you finished with " << g->p->score;
	
	std::cin >> play;
	return 0;
}
