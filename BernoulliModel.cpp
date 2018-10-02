#include "BernoulliModel.h"
#include <cmath>

BernoulliModel::BernoulliModel(int testsNumber, double probability, PRNG *prng) : testsNumber(testsNumber),
                                                                                    probability(probability),
                                                                                    prng(prng)
{

}

BernoulliModel::~BernoulliModel()
= default;

int BernoulliModel::next()
{
    double auxiliaryVectorCurrentElement, currentProbability;
    auxiliaryVectorCurrentElement = currentProbability = pow(1 - probability, testsNumber);
    double randomNumber = prng->next();
    int counter = 0;
    while (randomNumber > auxiliaryVectorCurrentElement)
    {
        counter++;
        currentProbability = currentProbability * (testsNumber - counter + 1) / counter * probability / (1 - probability);
        auxiliaryVectorCurrentElement += currentProbability;
    }

    return counter;
}

void BernoulliModel::reset()
{
    prng->reset();
}
