#include "Model.h"
#include <cmath>

Model::Model(uint numOfMechanics, uint numOfMachines, double machinesFailuresMean, double mechanicsRepairingTimeMean) :
    numOfWorkedMachines_(numOfMachines)
{
    machinesFailuresDistribution_ = std::make_unique<ExponentialDistribution>(machinesFailuresMean);
    mechanicsRepairingTimeDistribution_ = std::make_shared<ExponentialDistribution>(mechanicsRepairingTimeMean);
    //Adding workers
    for (uint i = numOfMechanics; i; --i)
        freeMechanics_.push_back(std::make_unique<Mechanic>(mechanicsRepairingTimeDistribution_));
    //Adding machines
    numOfWorkedMachines_ = numOfMachines;
}

minute Model::doMinuteStepAndGiveModelTime()
{
    //Simulated breakage of machines
    if (timeOfModel_ % 60 == 0) { //only once per hour
        uint generatedNumOfBrokenMachines = uint( std::round(machinesFailuresDistribution_->getRandomNumber()) );
        if (generatedNumOfBrokenMachines < numOfWorkedMachines_){
            numOfBrokenMachines_ += generatedNumOfBrokenMachines;
            numOfWorkedMachines_ -= generatedNumOfBrokenMachines;
        } else{
            //All machines are broken
            numOfBrokenMachines_ += numOfWorkedMachines_;
            numOfWorkedMachines_ = 0;
        }
    }

    //Try to free busy mechanics
    auto itBusyMechanic = busyMechanics_.begin();
    while (itBusyMechanic != busyMechanics_.end()) {
        if ((*itBusyMechanic)->IsWorkFinished( timeOfModel_ ) ){
            freeMechanics_.push_back( std::move(*itBusyMechanic) );
            itBusyMechanic = busyMechanics_.erase(itBusyMechanic);
            ++numOfWorkedMachines_;
        } else
            ++itBusyMechanic;
    }

    //Try to repair machines
    auto itFreeMechanic = freeMechanics_.begin();
    while ( (itFreeMechanic != freeMechanics_.end()) && (numOfBrokenMachines_ != 0) ) {
        (*itFreeMechanic)->startRepairMachine( timeOfModel_ );
        busyMechanics_.push_back( std::move(*itFreeMechanic) );
        itFreeMechanic = freeMechanics_.erase(itFreeMechanic);
        --numOfBrokenMachines_;
    }

    return ++timeOfModel_;
}

unsigned Model::getNumOfBusyMechanics() const
{
    return busyMechanics_.size();
}

unsigned Model::getNumOfBrokenMachines() const
{
    auto numOfRepairingMachines = busyMechanics_.size();
    return numOfBrokenMachines_ + numOfRepairingMachines;
}

void Model::setNumOfMechanics( uint N )
{
    uint currentNumOfMechanics = busyMechanics_.size() + freeMechanics_.size();
    uint delta = 0;
    if (N >= currentNumOfMechanics){
        delta = N - currentNumOfMechanics;
        //Add delta of mechanics to free mechanics list
        for (uint i = delta; i; --i)
            freeMechanics_.emplace_back(std::make_unique<Mechanic>(mechanicsRepairingTimeDistribution_));
    } else{
        delta = currentNumOfMechanics - N;
        //Trying to remove free mechanics
        for (uint i = delta; i && !freeMechanics_.size(); --i){
            freeMechanics_.pop_back();
            --delta;
        }
        //if delta != 0, try delete busy mechanics:
        for (uint i = delta; i && !busyMechanics_.size(); --i){
            busyMechanics_.pop_back();
            ++numOfBrokenMachines_;
        }
    }
}

void Model::setNumOfMachines( uint M )
{
    auto numOfRepairingMachines = busyMechanics_.size();
    uint currentNumOfMachines = numOfRepairingMachines + numOfBrokenMachines_ + numOfWorkedMachines_;
    uint delta = 0;
    if (M >= currentNumOfMachines){
        delta = M - currentNumOfMachines;
        numOfWorkedMachines_ += delta;
    } else{
        delta = currentNumOfMachines - M;
        //Trying to remove worked machines:
        if (numOfWorkedMachines_ >= delta){
            numOfWorkedMachines_ -= delta;
            delta = 0;
        } else{
            delta -= numOfWorkedMachines_;
            numOfWorkedMachines_ = 0;
        }
        //trying to delete broken machines:
        if (numOfBrokenMachines_ >= delta){
            numOfBrokenMachines_ -= delta;
            delta = 0;
        } else{
            delta -= numOfBrokenMachines_;
            numOfBrokenMachines_ = 0;
        }
        //trying to delete repairing machines:
        auto itBusyMechanic = busyMechanics_.begin();
        while (itBusyMechanic != busyMechanics_.end()) {
            freeMechanics_.push_back( std::move(*itBusyMechanic) );
            itBusyMechanic = busyMechanics_.erase(itBusyMechanic);
        }
    }
}

void Model::setMachinesFailuresMean(double Z)
{
    machinesFailuresDistribution_->setMean( Z );
}

void Model::setMechanicsRepairingTimeMean( double R )
{
    mechanicsRepairingTimeDistribution_->setMean( R );
}

void Model::resetModel()
{
    //Reset all machines
    auto numOfRepairingMachines = busyMechanics_.size();
    numOfWorkedMachines_ += numOfBrokenMachines_ + numOfRepairingMachines;
    numOfBrokenMachines_ = 0;

    //Reset all mechanics
    std::move(busyMechanics_.begin(), busyMechanics_.end(), std::back_inserter(freeMechanics_));
    busyMechanics_.clear();

    //Reset time
    timeOfModel_ = 0;
}
