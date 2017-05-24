#include "ExponentialDistribution.h"

ExponentialDistribution::ExponentialDistribution(double mean) :
    expDistLambda_(1.0/mean)
{}

void ExponentialDistribution::setMean(double mean)
{
    expDistLambda_ = 1.0/mean;
}

double ExponentialDistribution::getRandomNumber()
{
    static std::random_device physicalDeviceGenerator;
    static std::mt19937* generator = nullptr;
    if (!generator) generator = new std::mt19937(physicalDeviceGenerator());
    std::exponential_distribution<double> distribution (expDistLambda_);
    return distribution(*generator);
}
