#include "Statistic.h"

Statistic::Statistic(double mean) :
    testDistribution(new ExponentialDistribution(mean))
{}

void Statistic::setExpDistributionMean(double mean)
{
    testDistribution->setMean(mean);
}

double Statistic::getSampleMean(uint sampleSize)
{
    double summ = 0.0;
    for (uint i = sampleSize; i != 0; --i){
        summ += testDistribution->getRandomNumber();
    }
    return summ / sampleSize;
}

Statistic::~Statistic()
{
    delete testDistribution;
}
