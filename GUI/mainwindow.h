#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include "../Course/Engine.h"
#include "../Course/Statistic.h"

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

private:
    Ui::MainWindow *ui;
    Engine* engine;
    Statistic* statistic;
    QTime modelTime_;
};

#endif // MAINWINDOW_H
