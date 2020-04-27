#ifndef VETERINAIRE_H
#define VETERINAIRE_H
#include <QString>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QApplication>

class Veterinaire
{
public:
    Veterinaire();
    Veterinaire(int,QString,QString,int,QString,int);
    void setmatricule_vet(int);
    int getmatricule_vet();
    void setnom(QString);
    QString getnom();
    void setprenom (QString);
    QString getprenom ();
    void setnumero_telephone (int);
    int getnumero_telephone();
    void setadresse(QString);
    QString getadresse();
    void setanimaux_a_traiter(int);
    int getanimaux_a_traiter();
    bool ajouter();
    QSqlQueryModel * afficher_vet();
    bool supprimer(int);
    bool modifier(int);
    QSqlQueryModel * afficher_matricule();
    QSqlQueryModel * trier_nom();
    QSqlQueryModel * trier_prenom();
    QSqlQueryModel * trier_matricule();
    QSqlQueryModel * recherche_matricule(int);

private:
    int matricule_vet,numero_telephone, animaux_a_traiter;
    QString nom,prenom,adresse;
};

#endif // VETERINAIRE_H
