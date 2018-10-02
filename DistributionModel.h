#ifndef LAB2_DISTRIBUTIONMODEL_H
#define LAB2_DISTRIBUTIONMODEL_H

class DistributionModel
{
public:
    virtual int next() = 0;
    virtual void reset() = 0;
};

#endif //LAB2_DISTRIBUTIONMODEL_H
