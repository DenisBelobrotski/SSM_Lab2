#include "NegativeBinomialModel.h"
#include <cmath>

NegativeBinomialModel::NegativeBinomialModel(short failsNumber, double probability, PRNG *prng) : failsNumber(failsNumber),
                                                                                    probability(probability),
                                                                                    prng(prng)
{
}

NegativeBinomialModel::~NegativeBinomialModel()
= default;

int NegativeBinomialModel::next()
{
    double auxiliaryVectorCurrentElement, currentProbability;
    auxiliaryVectorCurrentElement = currentProbability = pow(1 - probability, failsNumber);
    double randomNumber = prng->next();
    int counter = 0;
    while (randomNumber > auxiliaryVectorCurrentElement)
    {
        counter++;
        currentProbability = currentProbability * (counter + failsNumber - 1) / counter * probability;
        auxiliaryVectorCurrentElement += currentProbability;
    }

    return counter;
}

void NegativeBinomialModel::reset()
{
    prng->reset();
}
