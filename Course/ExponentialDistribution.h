#ifndef EXPONENTIALDISTRIBUTION_H
#define EXPONENTIALDISTRIBUTION_H

#include <random>

class ExponentialDistribution
{
public:
    ExponentialDistribution( double mean );
    void setMean( double mean );
    double getRandomNumber();
private:
    double mean_;
    std::exponential_distribution<double> randomGenerator_;
};

#endif // EXPONENTIALDISTRIBUTION_H
