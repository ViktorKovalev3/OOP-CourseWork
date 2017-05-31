#ifndef STATISTICGUI_H
#define STATISTICGUI_H

#include <QWidget>
#include <memory>
#include "../Course/Statistic.h"

namespace Ui {
class StatisticGUI;
}

class StatisticGUI : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticGUI(QWidget *parent = 0);
    ~StatisticGUI();

private slots:
    void on_pushButton_clicked();

private:
    Ui::StatisticGUI *ui;
    std::unique_ptr<Statistic> statisticModel_;
};

#endif // STATISTICGUI_H
