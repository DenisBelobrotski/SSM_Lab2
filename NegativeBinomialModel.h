#ifndef LAB2_NEGATIVEBINOMIALMODEL_H
#define LAB2_NEGATIVEBINOMIALMODEL_H

#include "PRNG.h"
#include "DistributionModel.h"

class NegativeBinomialModel : public DistributionModel {
private:
    short failsNumber;
    double probability;
    PRNG *prng;
public:
    NegativeBinomialModel(short failsNumber, double probability, PRNG *prng);
    ~NegativeBinomialModel();

    int next() override;
    void reset() override;
};


#endif //LAB2_NEGATIVEBINOMIALMODEL_H
