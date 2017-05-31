#ifndef MODEL_H
#define MODEL_H

#include "Mechanic.h"
#include "ExponentialDistribution.h"
#include <list>
#include <memory>

typedef unsigned uint;
typedef uint minute;

class Model
{
public:
    Model( uint numOfMechanics, uint numOfMachines,  double machinesFailuresMean, double mechanicsRepairingTimeMean );
    minute doMinuteStepAndGiveModelTime ();
    unsigned getNumOfBusyMechanics  () const;
    unsigned getNumOfBrokenMachines () const;

    void setNumOfMechanics ( uint N );
    void setNumOfMachines ( uint M );
    void setMachinesFailuresMean ( double Z );
    void setMechanicsRepairingTimeMean ( double R );

    void resetModel ();
private:
    std::shared_ptr<ExponentialDistribution> mechanicsRepairingTimeDistribution_;
    std::list<std::unique_ptr<Mechanic>> freeMechanics_;
    std::list<std::unique_ptr<Mechanic>> busyMechanics_;

    std::unique_ptr<ExponentialDistribution> machinesFailuresDistribution_;
    uint numOfWorkedMachines_;
    uint numOfBrokenMachines_;

    minute timeOfModel_ = 0;
};

#endif // MODEL_H
