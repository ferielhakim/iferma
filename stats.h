#ifndef STATS_H
#define STATS_H

#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <string>
#include <QPainter>
#include <QMessageBox>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>

class Stats
{
public:
    QChart *chart;
    QChartView *chartView;
public:
    Stats();
    QChartView *Preparechart();
};

#endif // STATS_H
