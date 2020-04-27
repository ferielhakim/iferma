#ifndef FICHE_SUIVI_H
#define FICHE_SUIVI_H
#include <QString>
#include <QDate>
#include <QString>
#include <QDate>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QApplication>

class Fiche_suivi
{
public:
    Fiche_suivi();
    Fiche_suivi(int,QString,QString,float,float,QDate,int,int);
    void setnum_fiche(int);
    int getnum_fiche();
    void setanalyses(QString);
    QString getanalyses();
    void setdiagnostic (QString);
    QString getdiagnostic ();
    void setpoids (float);
    float getpoids();
    void settaille(float);
    float gettaille();
    void setmatricule_vet(int);
    int getmatricule_vet();
    void setdate_consultation(QDate);
    QDate getdate_consultation();
    void setId_animal(int);
    int getId_animal();


    bool ajouter_fiche();
    QSqlQueryModel * afficher_fiche();
    QSqlQueryModel * afficher_num_fiche();
    bool supprimer_fiche(int);
    bool modifier_fiche(int);
    QSqlQueryModel * recherche_num_fiche(int);
    QSqlQueryModel * trier_id();
    QSqlQueryModel * trier_num();
    //QSqlQueryModel * stat();

private:
    int num_fiche,matricule_vet;
    QString analyses,diagnostic;
    QDate date_consultation;
    float poids,taille;
    int Id_animal;
};

#endif // FICHE_SUIVI_H
