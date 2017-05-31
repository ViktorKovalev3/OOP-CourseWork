#include "statisticGUI.h"
#include "ui_statisticGUI.h"

#define DEFAULT_DISTR_MEAN 10
#define DEFAULT_SAMPLE_SIZE 10

StatisticGUI::StatisticGUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticGUI),
    statisticModel_(std::make_unique<Statistic>(DEFAULT_DISTR_MEAN))
{
    ui->setupUi(this);
    ui->leUserSampleSize->setText(QString::number(DEFAULT_SAMPLE_SIZE));
    ui->leUserMean->setText(QString::number(DEFAULT_DISTR_MEAN));
}

StatisticGUI::~StatisticGUI()
{
    delete ui;
}

void StatisticGUI::on_pushButton_clicked()
{
    statisticModel_->setExpDistributionMean(ui->leUserMean->text().toInt());
    ui->leModelMean->setText(QString::number(
                                 statisticModel_->getSampleMean(
                                     ui->leUserSampleSize->text().toInt()
                                     )
                                 )
                             );
}
