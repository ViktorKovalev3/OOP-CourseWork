#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include "../Course/Engine.h"
#include "statisticGUI.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void updateModelResults(uint numOfBisyMechanics, uint numOfBrokenMachines, uint modelTime);
    void on_pbStart_clicked();

    void on_pbPause_clicked();

    void on_pbStop_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Engine* engine;
    QTime modelTime_;
    StatisticGUI* statisticGUI;
};

#endif // MAINWINDOW_H
