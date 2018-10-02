#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>

#include "PRNG.h"
#include "MultiplicativePRNG.h"
#include "BernoulliModel.h"
#include "NegativeBinomialModel.h"

using namespace std;

FILE *outputFile;

double calcEstimatedMean(const int *source, int num);
double calcEstimatedVariance(const int *source, int num, double mathExpect);

double calcBernoilliMean(int testsNumber, double probability);
double calcBernoilliVariance(int testsNumber, double probability);

double calcNegativeBinomialMean(int failsNumber, double probability);
double calcNegativeBinomialVariance(int failsNumber, double probability);

int *calcFrequencies(int *sequence, int num, int cellNum);
bool checkPearsonTestBernoulli(const double *quantiles, int *sequence, int num, int testsNumber, double probability);
bool checkPearsonTestNegativeBinomial(const double *quantiles, int *sequence, int num, int failsNumber, double probability);

void calcSolution()
{
    const int num = 1000;

    const long long module = 2LL << 30;
    const int multiplier = 79507;
    const long long seed = 79507;

    const int bernoulliTestsNumber = 1;
    const double bernoulliProbability = 0.5;

    const int negativeBinomialFailsNumber = 5;
    const double negativeBinomialProbability = 0.25;

    const double quantiles[20] = {3.8415, 5.9915, 7.8147, 9.4877, 11.07, 12.592, 14.067, 15.507, 16.919, 18.307,
                                  19.675, 21.026, 22.362, 23.685, 24.996, 26.296, 27.587, 28.869, 30.144, 31.41};

    PRNG *firstPRNG = new MultiplicativePRNG(module, seed, multiplier);
    PRNG *secondPRNG = new MultiplicativePRNG(module, seed, multiplier);
    DistributionModel *bernoulliDistributionModel =
            new BernoulliModel(bernoulliTestsNumber, bernoulliProbability, firstPRNG);
    DistributionModel *negativeBinomialDistributionModel =
            new NegativeBinomialModel(negativeBinomialFailsNumber, negativeBinomialProbability, secondPRNG);

    fopen_s(&outputFile, "output.txt", "w");

    auto *bernoulliResult = new int[num];
    auto *negativeBinomialResult = new int[num];

    double mean;
    double variance;
    bool testResult;

    for (int i = 0; i < num; i++)
    {
        bernoulliResult[i] = bernoulliDistributionModel->next();
        negativeBinomialResult[i] = negativeBinomialDistributionModel->next();
    }

    printf("Bernoulli:\n");
    fprintf(outputFile, "Bernoulli:\n");
    for (int i = 0; i < num; i++)
    {
        fprintf(outputFile, "%d\n", bernoulliResult[i]);
    }

    mean = calcEstimatedMean(bernoulliResult, num);
    variance = calcEstimatedVariance(bernoulliResult, num, mean);
    printf("Real mean: %f\n", mean);
    fprintf(outputFile, "Real mean: %f\n", mean);
    printf("Real variance: %f\n", variance);
    fprintf(outputFile, "Real variance: %f\n", variance);

    mean = calcBernoilliMean(bernoulliTestsNumber, bernoulliProbability);
    variance = calcBernoilliVariance(bernoulliTestsNumber, bernoulliProbability);
    printf("Theoretical mean: %f\n", mean);
    fprintf(outputFile, "Theoretical mean: %f\n", mean);
    printf("Theoretical variance: %f\n", variance);
    fprintf(outputFile, "Theoretical variance: %f\n", variance);

    testResult = checkPearsonTestBernoulli(quantiles, bernoulliResult, num, bernoulliTestsNumber, bernoulliProbability);
    printf("Pearson test: %s\n", (testResult ? "true" : "false"));
    fprintf(outputFile, "Pearson test: %s\n", (testResult ? "true" : "false"));

    printf("\nNegative binomial:\n");
    fprintf(outputFile, "\nNegative binomial:\n");
    for (int i = 0; i < num; i++)
    {
        fprintf(outputFile, "%d\n", negativeBinomialResult[i]);
    }

    mean = calcEstimatedMean(negativeBinomialResult, num);
    variance = calcEstimatedVariance(negativeBinomialResult, num, mean);
    printf("Real mean: %f\n", mean);
    fprintf(outputFile, "Real mean: %f\n", mean);
    printf("Real variance: %f\n", variance);
    fprintf(outputFile, "Real variance: %f\n", variance);

    mean = calcNegativeBinomialMean(negativeBinomialFailsNumber, negativeBinomialProbability);
    variance = calcNegativeBinomialVariance(negativeBinomialFailsNumber, negativeBinomialProbability);
    printf("Theoretical mean: %f\n", mean);
    fprintf(outputFile, "Theoretical mean: %f\n", mean);
    printf("Theoretical variance: %f\n", variance);
    fprintf(outputFile, "Theoretical variance: %f\n", variance);

    testResult = checkPearsonTestNegativeBinomial(quantiles, negativeBinomialResult, num, negativeBinomialFailsNumber,
                                                  negativeBinomialProbability);
    printf("Pearson test: %s\n", (testResult ? "true" : "false"));
    fprintf(outputFile, "Pearson test: %s\n", (testResult ? "true" : "false"));

    fclose(outputFile);

    delete firstPRNG;
    delete secondPRNG;
    delete bernoulliDistributionModel;
    delete negativeBinomialDistributionModel;

    delete[] bernoulliResult;
    delete[] negativeBinomialResult;
}

double calcEstimatedMean(const int *source, int num)
{
    int sum = 0;

    for (int i = 0; i < num; i++)
    {
        sum += source[i];
    }

    return (double)sum / num;
}

double calcEstimatedVariance(const int *source, int num, double mathExpect)
{
    double sum = 0.0;

    for (int i = 0; i < num; i++)
    {
        sum += pow(source[i] - mathExpect, 2.0);
    }

    return (double)sum / (num - 1);
}

double calcBernoilliMean(int testsNumber, double probability)
{
    return probability;
}

double calcBernoilliVariance(int testsNumber, double probability)
{
    return probability * (1 - probability);
}

double calcNegativeBinomialMean(int failsNumber, double probability)
{
    return probability * failsNumber / (1.0 - probability);
}

double calcNegativeBinomialVariance(int failsNumber, double probability)
{
    return probability * failsNumber / pow(1.0 - probability, 2.0);
}

int *calcFrequencies(int *sequence, int num, int cellNum)
{
    int *result = new int[cellNum];
    int resultIndex = sequence[0];
    int prev = 0;

    for (int i = 0; i < cellNum; i++)
    {
        result[i] = 0;
    }

    for (int i = 0; i < num; i++)
    {
        if (sequence[i] != prev)
        {
            resultIndex = sequence[i];
            prev = sequence[i];
        }
        result[resultIndex]++;
    }

    return result;
}

bool checkPearsonTestBernoulli(const double *quantiles, int *sequence, int num, int testsNumber, double probability)
{
    int *frequencies;
    int cellNum;
    double chi = 0.0;
    double expectedCount = num * pow(1 - probability, testsNumber);

    sort(sequence, &sequence[num]);
    cellNum = sequence[num - 1] + 1;
    frequencies = calcFrequencies(sequence, num, cellNum);

    chi += pow(frequencies[0] - expectedCount, 2.0) / expectedCount;
    for(int i = 1; i < cellNum; i++)
    {
        expectedCount *= (testsNumber - i + 1) * probability / (1 - probability) / i;
        chi += pow(frequencies[i] - expectedCount, 2.0) / expectedCount;
    }

    delete[] frequencies;

    printf("Chi: %f\n", chi);
    fprintf(outputFile, "Chi: %f\n", chi);
    printf("Quantile: %f\n", quantiles[cellNum - 2]);
    fprintf(outputFile, "Quantile: %f\n", quantiles[cellNum - 2]);

    return (chi < quantiles[cellNum - 2]);
}

bool checkPearsonTestNegativeBinomial(const double *quantiles, int *sequence, int num, int failsNumber, double probability)
{
    int *empericFreq;
    int cellNum;
    double chi = 0.0;
    double expectedCount = num * pow(1.0 - probability, failsNumber);

    sort(sequence, &sequence[num]);
    cellNum = sequence[num - 1] + 1;
    empericFreq = calcFrequencies(sequence, num, cellNum);

    chi += pow(empericFreq[0] - expectedCount, 2.0) / expectedCount;
    for(int i = 1; i < cellNum; i++)
    {
        expectedCount *= (i + failsNumber - 1) * probability / i;
        chi += pow(empericFreq[i] - expectedCount, 2.0) / expectedCount;
    }

    delete[] empericFreq;

    printf("Chi: %f\n", chi);
    fprintf(outputFile, "Chi: %f\n", chi);
    printf("Quantile: %f\n", quantiles[cellNum - 2]);
    fprintf(outputFile, "Quantile: %f\n", quantiles[cellNum - 2]);

    return (chi < quantiles[cellNum - 2]);
}
