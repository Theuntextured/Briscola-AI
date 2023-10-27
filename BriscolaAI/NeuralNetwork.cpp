#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork()
{
	nodes = new std::vector<double>((nodeWidth + 1) * nodeWidth * nodeDepth);

	for (int i = 0; i < nodes->size(); i++) {
		nodes->at(i) = rnd(-nodeValueMax, nodeValueMax);
	}
}

NeuralNetwork::NeuralNetwork(NeuralNetwork* parent)
{
	nodes = new std::vector<double>((nodeWidth + 1) * nodeWidth * nodeDepth);

	double w;
	for (int i = 0; i < nodes->size(); i++) {
		w = parent->nodes->at(i);
		if (chance(MutationChance)) w = w * (1 + rnd(-MutationMultiplier, MutationMultiplier)) + rnd(-MutationBias, MutationBias);
		nodes->at(i) = w;
	}
}

NeuralNetwork::~NeuralNetwork()
{
	nodes->clear();

	delete nodes;
}

std::vector<double> NeuralNetwork::getOutputs(std::vector<double>& inputs, int outputs)
{
	if (inputs.size() > nodeWidth) throw;
	if (outputs > nodeWidth) throw;

	std::vector<double> cache(nodeWidth * nodeDepth);

	for (int x = 0; x < nodeDepth; x++) {
		for (int y = 0; y < nodeWidth; y++) {
			double tot = 0;
			if (x == 0) {
				for (int z = 0; z < inputs.size(); z++) {
					tot += nodes->at(vec3i(x, y, z + 1).toLinear(nodeDepth, nodeWidth)) * inputs[z];
				}
			}
			else {
				for (int z = 0; z < nodeWidth; z++) {
					tot += nodes->at(vec3i(x, y, z + 1).toLinear(nodeDepth, nodeWidth)) * cache[vec2i(x - 1, y).toLinear(nodeDepth)];
				}
			}
			tot += nodes->at(vec3i(x, y, 0).toLinear(nodeDepth, nodeWidth));
			cache[vec2i(x, y).toLinear(nodeDepth)] = tot;
		}
	}

	std::vector<double> o(outputs);
	for (int i = 0; i < outputs; i++) {
		o[i] = cache[vec2i(nodeDepth - 1, i).toLinear(nodeDepth)];
	}
	cache.clear();
	return o;
}

