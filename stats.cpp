#include "stats.h"
#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <QSqlQuery>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

Stats::Stats()
{

}
QChartView * Stats::Preparechart()
{
    unsigned int id=0,quantite=0;
    QLineSeries *series = new QLineSeries();
    QSqlQuery query;
    if(query.exec("select id_fournisseur,quantite from achat"))

       {
            while(query.next())
                {
                    id=query.value(0).toUInt() ;
                    quantite=query.value(1).toUInt();
                    series->append(id,quantite);
                }
        }
       QChart *chart = new QChart();
       chart->setTitle("Meilleur fournisseur par quantité");
       chart->addSeries(series);
       chart->createDefaultAxes();
       chart->setAnimationOptions(QChart::AllAnimations);
       QChartView *chartView = new QChartView(chart);
       chartView->setRenderHint(QPainter::Antialiasing);

       return chartView;

}
