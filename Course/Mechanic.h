#ifndef MECHANIC_H
#define MECHANIC_H

#include "ExponentialDistribution.h"
typedef unsigned minute;

class Mechanic
{
public:
    Mechanic( double mechanicsRepairingTimeMean );
    void startRepairMachine ( minute repairingStartTime );
    bool workIsDone ( minute currentTime );
private:
    static ExponentialDistribution mechanicsRepairingTimeDistribution;
};

#endif // MECHANIC_H
