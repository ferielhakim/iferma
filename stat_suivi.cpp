#include "stat_suivi.h"
#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <QSqlQuery>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

Stat_suivi::Stat_suivi()
{

}
QChartView * Stat_suivi::Preparechart()
{
    int count=0,date=0;
    QLineSeries *series = new QLineSeries();
    QSqlQuery query;
    if(query.exec("SELECT count(date_consultation),to_number(to_char(date_consultation,'yyyy'))\
                     FROM FICHE_SUIVI\
                     WHERE to_number(to_char(date_consultation,'yyyy')) < to_number(to_char(sysdate,'yyyy'))\
                     GROUP BY to_number(to_char(date_consultation,'yyyy'))"))

       {
            while(query.next())
                {
                    count=query.value(0).toInt() ;
                    date=query.value(1).toInt();
                    series->append(date,count);
                }
        }
       QChart *chart = new QChart();
       chart->setTitle("Nombre de consultations par an");
       chart->addSeries(series);
       chart->createDefaultAxes();
       chart->setAnimationOptions(QChart::AllAnimations);
       QChartView *chartView = new QChartView(chart);
       chartView->setRenderHint(QPainter::Antialiasing);
       QChart::ChartTheme theme = QChart::ChartThemeBlueCerulean ;
       chartView->chart()->setTheme(theme);

       return chartView;

}
