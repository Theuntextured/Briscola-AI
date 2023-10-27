#pragma once
#include <vector>
#include "ProjectLib.h"

//settings
#define nodeWidth 60
#define nodeDepth 8
#define nodeValueMax 1
#define MutationChance 125
#define MutationMultiplier 1.5
#define MutationBias 0.25

class NeuralNetwork
{
public:
	// x = depth
	// y = width
	// z = connection / bias (bias on z = 0)
	std::vector<double>* nodes;

	NeuralNetwork();
	NeuralNetwork(NeuralNetwork *parent);
	~NeuralNetwork();
	std::vector<double> getOutputs(std::vector<double> &inputs, int outputs);
};

