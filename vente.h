#ifndef VENTE_H
#define VENTE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QDebug>
#include <QApplication>
class VENTE
{
public:
    VENTE();
    VENTE(int,int,int,QDate);
    int get_matricule();
    int get_quantite();
    int get_prix();
    QDate get_datevente();
    bool ajouterV();
    QSqlQueryModel * afficherV();
    bool supprimerV(int);
    bool modifierV(int);
    QSqlQueryModel * afficher2();
    QSqlQueryModel * chercherV(const QString &);
    QSqlQueryModel * trierV_id();
    QSqlQueryModel * trierV_quantite();
    QSqlQueryModel * affichermatricule();




private:
    int matricule,quantite,prix;
    QDate date_vente ;
};
#endif // VENTE_H
