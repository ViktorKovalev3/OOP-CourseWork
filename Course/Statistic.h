#ifndef STATISTIC_H
#define STATISTIC_H

#include "ExponentialDistribution.h"

typedef unsigned uint;

class Statistic
{
public:
    Statistic( double mean );
    ~Statistic();
    void setExpDistributionMean ( double mean );
    double getSampleMean ( uint sampleSize );
private:
    ExponentialDistribution* testDistribution;
};

#endif // STATISTIC_H
