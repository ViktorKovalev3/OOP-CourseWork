#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QTimer>
#include <memory>
#include "Model.h"

typedef unsigned uint;
typedef uint minutes;

#define DEFAULT_MIN_PER_SCND 1
#define DEFAULT_STOP_SCND 10000
#define DEFAULT_NUM_OF_MECH 2
#define DEFAULT_NUM_OF_MACH 20
#define DEFAULT_MACH_FAIL_MEAN 1
#define DEFAULT_MECH_FAIL_MEAN 60

class Engine : public QObject
{
    Q_OBJECT
public:
    Engine(QObject* parent = nullptr);
public slots:
    void start ( minutes minutePerSecnd = DEFAULT_MIN_PER_SCND, minutes stopTime = DEFAULT_STOP_SCND);
    void pause ();
    void stop ();
    void setSettings ( uint numOfMechanics = DEFAULT_NUM_OF_MECH, uint numOfMachines = DEFAULT_NUM_OF_MACH,
                       double machinesFailuresMean = DEFAULT_MACH_FAIL_MEAN, double mechanicsRepairingTimeMean = DEFAULT_MECH_FAIL_MEAN);
private slots:
    void doSecndStepInModel();
signals:
    void sendModelResults ( uint numOfBisyMechanics, uint numOfBrokenMachines, uint modelTime );
private:
    QTimer* timer;
    minutes stopTime_;
    bool isPaused = 0;
    std::unique_ptr<Model> modelOfManufactory_;
};

#endif // ENGINE_H
