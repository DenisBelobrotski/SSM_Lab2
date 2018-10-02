#ifndef LAB2_BERNOULLIMODEL_H
#define LAB2_BERNOULLIMODEL_H

#include "PRNG.h"
#include "DistributionModel.h"

class BernoulliModel : public DistributionModel {
private:
    int testsNumber;
    double probability;
    PRNG *prng;
public:
    BernoulliModel(int testsNumber, double probability, PRNG *prng);
    ~BernoulliModel();

    int next() override;
    void reset() override;
};


#endif //LAB2_BERNOULLIMODEL_H
