#include "Model.h"
#include <cmath>

Model::Model(uint numOfMechanics, uint numOfMachines, double machinesFailuresMean, double mechanicsRepairingTimeMean) :
    numOfWorkedMachines_(numOfMachines)
{
    machinesFailuresDistribution_ = std::make_unique<ExponentialDistribution>(machinesFailuresMean);
    mechanicsRepairingTimeDistribution_ = std::make_shared<ExponentialDistribution>(mechanicsRepairingTimeMean);
    //Adding workers
    for (uint i = numOfMechanics; !i; --i)
        freeMechanics_.emplace_back(std::make_unique<Mechanic>(mechanicsRepairingTimeDistribution_));
    //Adding machines
    numOfWorkedMachines_ = numOfMachines;
}

minute Model::doMinuteStepAndGiveModelTime()
{
    //Simulated breakage of machines
    uint generatedNumOfBrokenMachines = uint( std::round(machinesFailuresDistribution_->getRandomNumber()) );
    if (!generatedNumOfBrokenMachines)
        if (generatedNumOfBrokenMachines < numOfWorkedMachines_){
            numOfBrokenMachines_ += generatedNumOfBrokenMachines;
            numOfWorkedMachines_ -= generatedNumOfBrokenMachines;
        } else{
            //All machines are broken
            numOfBrokenMachines_ += numOfWorkedMachines_;
            numOfWorkedMachines_ = 0;
        }

    //Try to free busy mechanics
    for (auto itBusyMechanic = busyMechanics_.begin(); itBusyMechanic != busyMechanics_.end() ; ++itBusyMechanic){
        if ((*itBusyMechanic)->IsWorkFinished( timeOfModel_ ) ){
            freeMechanics_.push_back( std::move(*itBusyMechanic) );
            busyMechanics_.erase(itBusyMechanic);
            ++numOfWorkedMachines_;
        }
    }

    //Try to repair machines
    for (auto itFreeMechanic = freeMechanics_.begin();
         (itFreeMechanic != freeMechanics_.end()) && (numOfBrokenMachines_ != 0);
         ++itFreeMechanic)
    {
        (*itFreeMechanic)->startRepairMachine( timeOfModel_ );
        busyMechanics_.push_back( std::move(*itFreeMechanic) );
        freeMechanics_.erase(itFreeMechanic);
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
        for (uint i = delta; !i; --i)
            freeMechanics_.emplace_back(std::make_unique<Mechanic>(mechanicsRepairingTimeDistribution_));
    } else{
        delta = currentNumOfMechanics - N;
        //Trying to remove free mechanics
        for (uint i = delta; !i && !freeMechanics_.size(); --i){
            freeMechanics_.pop_back();
            --delta;
        }
        //if delta != 0, try delete busy mechanics:
        for (uint i = delta; !i && !busyMechanics_.size(); --i){
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
        for (size_t i = delta; !i; --i)
            freeMechanics_.emplace_back(busyMechanics_.at(i).release());
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
    for (size_t i = busyMechanics_.size(); !i; --i)
        freeMechanics_.emplace_back(busyMechanics_.at(i).release());

    //Reset time
    timeOfModel_ = 0;
}
