#include "Mechanic.h"

std::unique_ptr<ExponentialDistribution> Mechanic::mechanicsRepairingTimeDistribution = nullptr;

Mechanic::Mechanic(double mechanicsRepairingTimeMean)
{
    if (!mechanicsRepairingTimeDistribution)
        mechanicsRepairingTimeDistribution = std::make_unique<ExponentialDistribution>(mechanicsRepairingTimeMean);
}

void Mechanic::startRepairMachine(minute repairingStartTime)
{
    repairingStartTime_  = repairingStartTime;
    reparingTime_ = int(mechanicsRepairingTimeDistribution->getRandomNumber());
}

bool Mechanic::IsWorkFinished(minute currentTime)
{
    minute workingTime = currentTime - repairingStartTime_;
    if (reparingTime_ < workingTime)
        return true;
    else
        return false;
}
