#ifndef MECHANIC_H
#define MECHANIC_H

#include "ExponentialDistribution.h"
#include <memory>
typedef unsigned minute;

class Mechanic
{
public:
    Mechanic( std::shared_ptr<ExponentialDistribution> mechanicsRepairingTimeDistribution );
    void startRepairMachine ( minute repairingStartTime );
    bool IsWorkFinished ( minute currentTime );
private:
    std::shared_ptr<ExponentialDistribution> mechanicsRepairingTimeDistribution_;
    minute repairingStartTime_;
    minute reparingTime_;
};

#endif // MECHANIC_H
