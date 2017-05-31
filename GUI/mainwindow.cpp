#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include <climits>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    modelTime_(0, 0, 0),
    statisticGUI(new StatisticGUI(parent))
{
    ui->setupUi(this);
    engine = new Engine(this);
    connect(engine, SIGNAL(sendModelResults(uint, uint, uint)), SLOT(updateModelResults(uint,uint,uint)));

    //Set default numbers
    ui->leMachinesFailuresMean->setText(QString::number(DEFAULT_MACH_FAIL_MEAN));
    ui->leMechanicsRepairingTimeMean->setText(QString::number(DEFAULT_MECH_FAIL_MEAN));
    ui->leNumOfMachines->setText(QString::number(DEFAULT_NUM_OF_MACH));
    ui->leNumOfMechanics->setText(QString::number(DEFAULT_NUM_OF_MECH));
    ui->leMinPerScnd->setText(QString::number(DEFAULT_MIN_PER_SCND));
    ui->leStopTime->setText(QString::number(DEFAULT_STOP_MINUT));
    ui->pbModelTime->setMinimum(0);
    ui->pbModelTime->reset();
    ui->pbModelTime->setMaximum(DEFAULT_STOP_MINUT);

    ui->pbStart->setEnabled(1);
    ui->pbPause->setEnabled(0);
    ui->pbStop->setEnabled(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateModelResults(uint numOfBisyMechanics, uint numOfBrokenMachines, uint modelTime)
{
    ui->leBusyMech->setText(QString::number(numOfBisyMechanics));
    ui->leBrokenMachines->setText(QString::number(numOfBrokenMachines));

    modelTime_ = modelTime_.addSecs(60);
    //24 * 60 = 1440 minutes in day
    ui->leModelTime->setText("Day " + QString::number(modelTime / 1440) + ": " + modelTime_.toString("hh:mm"));
    ui->pbModelTime->setValue(modelTime);
}

void MainWindow::on_pbStart_clicked()
{
    engine->setSettings(
                ui->leNumOfMechanics->text().toInt(),
                ui->leNumOfMachines->text().toInt(),
                ui->leMachinesFailuresMean->text().toInt(),
                ui->leMechanicsRepairingTimeMean->text().toInt()
                );
    engine->start(ui->leMinPerScnd->text().toInt(), ui->leStopTime->text().toInt());
    ui->pbModelTime->setMaximum(ui->leStopTime->text().toInt());

    //Disable user input
    ui->leMachinesFailuresMean->setEnabled(0);
    ui->leMechanicsRepairingTimeMean->setEnabled(0);
    ui->leNumOfMachines->setEnabled(0);
    ui->leNumOfMechanics->setEnabled(0);
    ui->leMinPerScnd->setEnabled(0);
    ui->leStopTime->setEnabled(0);

    ui->pbStart->setEnabled(0);
    ui->pbPause->setEnabled(1);
    ui->pbStop->setEnabled(1);
}

void MainWindow::on_pbPause_clicked()
{
    //Enable user input
    ui->leMachinesFailuresMean->setEnabled(1);
    ui->leMechanicsRepairingTimeMean->setEnabled(1);
    ui->leNumOfMachines->setEnabled(1);
    ui->leNumOfMechanics->setEnabled(1);
    ui->leMinPerScnd->setEnabled(1);
    ui->leStopTime->setEnabled(1);

    engine->pause();
    ui->pbStart->setEnabled(1);
    ui->pbPause->setEnabled(0);
    ui->pbStop->setEnabled(1);
}

void MainWindow::on_pbStop_clicked()
{
    //Enable user input
    ui->leMachinesFailuresMean->setEnabled(1);
    ui->leMechanicsRepairingTimeMean->setEnabled(1);
    ui->leNumOfMachines->setEnabled(1);
    ui->leNumOfMechanics->setEnabled(1);
    ui->leMinPerScnd->setEnabled(1);
    ui->leStopTime->setEnabled(1);

    engine->stop();
    modelTime_ = QTime(0, 0, 0);
    ui->pbStart->setEnabled(1);
    ui->pbPause->setEnabled(0);
    ui->pbStop->setEnabled(0);
}

void MainWindow::on_pushButton_clicked()
{
    statisticGUI->show();
}

void MainWindow::on_pbModelStatus_clicked()
{
    if (ui->wgtModelStatusView->isHidden())
        ui->wgtModelStatusView->show();
    else
        ui->wgtModelStatusView->hide();
}

void MainWindow::on_pbModelSettings_clicked()
{
    if (ui->wgtModelSettingView->isHidden())
        ui->wgtModelSettingView->show();
    else
        ui->wgtModelSettingView->hide();
}
