#ifndef MODEL_H
#define MODEL_H

#include "Mechanic.h"
#include <vector>

typedef unsigned uint;

class Model
{
public:
    Model( uint NumOfMechanics, uint NumOfMachines,  double MachinesFailuresMean, double MechanicsRepairingTimeMean );
    ~Model();
    long doMinuteStepAndGiveModelTime ();
    unsigned getNumOfBusyMechanics  () const;
    unsigned getNumOfBrokenMachines () const;

    void setNumOfMechanics ( uint N );
    void setNumOfMachines ( uint M );
    void setMachinesFailuresMean ( double Z );
    void setMechanicsRepairingTimeMean ( double R );

    void resetModel ();
private:
    std::vector<Mechanic*> freeMechanics_;
    std::vector<Mechanic*> busyMechanics_;
    uint NumOfMechanics_;
    uint NumOfMachines_;
    double MachinesFailuresMean_;
    double MechanicsRepairingTimeMean_;
};

#endif // MODEL_H
