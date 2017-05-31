#include "Engine.h"

Engine::Engine(QObject* parent) :
    QObject(parent),
    timer(new QTimer(this)),
    modelOfManufactory_(
        std::make_unique<Model>(
            DEFAULT_NUM_OF_MECH, DEFAULT_NUM_OF_MACH,
            DEFAULT_MACH_FAIL_MEAN, DEFAULT_MECH_FAIL_MEAN
            )
        )
{
    connect(timer, SIGNAL(timeout()), this, SLOT(doSecndStepInModel()));
}

void Engine::start(minutes minutePerSecnd, minutes stopTime)
{
    if (!isPaused)
        stopTime_ = stopTime;
    timer->start(1000 / minutePerSecnd); //1000 ms = 1 sec
}

void Engine::pause()
{
    timer->stop();
    isPaused = 0;
}

void Engine::stop()
{
    timer->stop();
    modelOfManufactory_->resetModel();
}

void Engine::setSettings(uint numOfMechanics, uint numOfMachines, double machinesFailuresMean, double mechanicsRepairingTimeMean)
{
    modelOfManufactory_->setNumOfMechanics(numOfMechanics);
    modelOfManufactory_->setNumOfMachines(numOfMachines);
    modelOfManufactory_->setMachinesFailuresMean(machinesFailuresMean);
    modelOfManufactory_->setMechanicsRepairingTimeMean(mechanicsRepairingTimeMean);
}

void Engine::doSecndStepInModel()
{
    minute modelTime = modelOfManufactory_->doMinuteStepAndGiveModelTime();
    if (modelTime <= stopTime_)
        emit sendModelResults(
                modelOfManufactory_->getNumOfBusyMechanics(),
                modelOfManufactory_->getNumOfBrokenMachines(),
                modelTime
                );
    else
        stop();
}
