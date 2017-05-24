#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include "Model.h"

typedef unsigned uint;
typedef uint minutes;

class Engine
{
public:
    Engine();
    ~Engine();
public slots:
    void start ( minutes minutePerSecnd, minutes stopTime );
    void pause ();
    void stop ();
    void setSettings ( uint numOfMechanics, uint numOfMachines,
                       double machinesFailuresMean, double mechanicsRepairingTimeMean );
signals:
    void sendModelResults ( uint numOfBisyMechanics, uint numOfBrokenMachines, uint modelTime );
private:
    Model* manufactoryModel_;
};

#endif // ENGINE_H
