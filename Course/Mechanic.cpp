#include "Mechanic.h"

Mechanic::Mechanic(std::shared_ptr<ExponentialDistribution> mechanicsRepairingTimeDistribution) :
    mechanicsRepairingTimeDistribution_(mechanicsRepairingTimeDistribution)
{}

void Mechanic::startRepairMachine(minute repairingStartTime)
{
    repairingStartTime_  = repairingStartTime;
    reparingTime_ = int(mechanicsRepairingTimeDistribution_->getRandomNumber());
}

bool Mechanic::IsWorkFinished(minute currentTime)
{
    minute workingTime = currentTime - repairingStartTime_;
    if (reparingTime_ < workingTime)
        return true;
    else
        return false;
}
