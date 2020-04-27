#ifndef STAT_SUIVI_H
#define STAT_SUIVI_H

#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <string>
#include <QPainter>
#include <QMessageBox>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>

class Stat_suivi
{
public:
    QChart *chart;
    QChartView *chartView;
public:
    Stat_suivi();
    QChartView *Preparechart();
};

#endif // STAT_SUIVI_H
