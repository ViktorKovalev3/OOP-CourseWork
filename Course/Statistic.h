#ifndef STATISTIC_H
#define STATISTIC_H

#include "ExponentialDistribution.h"

typedef unsigned uint;

class Statistic
{
public:
    Statistic( double mean );
    void setExpDistributionMean ( double mean );
    double getSampleMean ( uint sampleSize );
    ~Statistic();
private:
    ExponentialDistribution* testDistribution;
};

#endif // STATISTIC_H
