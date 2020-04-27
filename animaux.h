#ifndef ANIMAUX_H
#define ANIMAUX_H
#include <QString>
#include <QDate>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QApplication>

class animaux
{
public:
    animaux();
    animaux(int,QString,bool,QString,bool,QDate);
    void setId_animal(int);
    int getId_animal();
    void setnom(QString);
    QString getnom();
    void setsexe (bool);
    bool getsexe ();
    void setrace (QString);
    QString getrace();
    void setetat(bool);
    bool getetat();
    void setdate_naissance(QDate);
    QDate getdate_naissance();
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficher_id();
    QSqlQueryModel * afficher_race();
    bool supprimer(int);
    bool modifier(int);
    QSqlQueryModel * recherche_id(int);
    QSqlQueryModel * recherche_race(QString);
    QSqlQueryModel * trier_id();
    QSqlQueryModel * trier_nom();
private:
    int Id_animal;
    QString nom;
    bool sexe;
    QString race;
    bool etat;
    QDate date_naissance;
};

#endif // ANIMAUX_H
