#include "stat.h"
#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <string>
#include <QPainter>
#include <QMessageBox>
#include <QSqlQuery>
#include <QtCharts/QPieSlice>

QT_CHARTS_USE_NAMESPACE

Stat::Stat(){

}

QChartView * Stat::Preparechart(){
    QSqlQuery query;
       int count1=0;
       int count2=0;

       if(query.exec("select ETAT from ANIMAUX"))
       {
       while(query.next())
         {
            if(query.value(0)==0){
                count1++; }
            else if(query.value(0)==1){
                count2++;}
          }
        }
       QPieSeries *series;
       series = new QPieSeries();
       series->append("Sains", count1);
       series->append("Malades", count2);
       series->setLabelsVisible();
       series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);
       for(auto slice : series->slices())
           slice->setLabel(QString("%1 %2%").arg(slice->label()).arg(100*slice->percentage(), 0, 'f', 1));
       chart = new QChart();
       chart->addSeries(series);
       chart->setTitle("Statistiques de l'état de santé des animaux");
       chart->setAnimationOptions(QChart::AllAnimations);
       chartView = new QChartView(chart);
       chartView->setRenderHint(QPainter::Antialiasing);
       QChart::ChartTheme theme = QChart::ChartThemeBlueCerulean ;
       chartView->chart()->setTheme(theme);

       return chartView;
}
