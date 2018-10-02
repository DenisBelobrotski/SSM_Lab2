#ifndef LAB2_RANDOMGENERATOR_H
#define LAB2_RANDOMGENERATOR_H

class PRNG
{
public:
    virtual double next() = 0;
    virtual void reset() = 0;
};

#endif //LAB2_RANDOMGENERATOR_H
