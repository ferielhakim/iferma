#include "veterinaire.h"
#include "mainwindow.h"
#include <QString>
#include <QDebug>
#include <QApplication>
#include <QComboBox>

Veterinaire::Veterinaire()
{
    matricule_vet=0;
    nom="";
    prenom="";
    numero_telephone=0;
    adresse="";
    animaux_a_traiter=0;

}
Veterinaire::Veterinaire(int matricule_vet, QString nom,QString prenom,int numero_telephone,QString adresse,int animaux_a_traiter)
{
    this->matricule_vet=matricule_vet;
    this->nom=nom;
    this->prenom=prenom;
    this->numero_telephone=numero_telephone;
    this->adresse=adresse;
    this->animaux_a_traiter=animaux_a_traiter;
}

int Veterinaire::getmatricule_vet() { return matricule_vet; }
QString Veterinaire::getnom() { return nom; }
QString Veterinaire::getprenom() { return prenom; }
int Veterinaire::getnumero_telephone() { return numero_telephone;}
QString Veterinaire::getadresse() { return adresse;}
int Veterinaire::getanimaux_a_traiter() { return animaux_a_traiter;}



bool Veterinaire::ajouter()
{
    QSqlQuery query;
    QString res= QString::number(matricule_vet);

    query.prepare("INSERT INTO Veterinaire (matricule_vet, NOM, prenom, numero_telephone, adresse, animaux_a_traiter ) "
                        "VALUES (:matricule_vet, :nom, :prenom, :numero_telephone, :adresse, :animaux_a_traiter)");
    query.bindValue(":matricule_vet", res);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":numero_telephone", numero_telephone);
    query.bindValue(":adresse", adresse);
    query.bindValue(":animaux_a_traiter", animaux_a_traiter);


    return    query.exec();
}

QSqlQueryModel * Veterinaire::afficher_vet()
{
  QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM VETERINAIRE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Matricule"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Animaux à traiter"));

    return model;
}

bool Veterinaire::supprimer(int idd)
{
    QSqlQuery query;
    QString res= QString::number(idd);
    query.prepare("DELETE from VETERINAIRE where matricule_vet = :idd ");
    query.bindValue(":idd", res);

        return  query.exec();
}

bool Veterinaire::modifier(int id)
{

    QSqlQuery query;
    QString res=QString::number(id);
    QString res2=QString::number(animaux_a_traiter);
    QString res3=QString::number(numero_telephone);
    query.prepare("UPDATE VETERINAIRE SET nom =:nom, prenom=:prenom, numero_telephone=:numero_telephone, adresse=:adresse, animaux_a_traiter=:animaux_a_traiter WHERE matricule_vet =:id");
    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":numero_telephone",res3);
    query.bindValue(":adresse",adresse);
    query.bindValue(":animaux_a_traiter",res2);


    return  query.exec();
}

QSqlQueryModel * Veterinaire::afficher_matricule()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select MATRICULE_VET from VETERINAIRE");
    //pour afficher les ids sélectionnées à partir de la requête et résultant dans model.

    return model;
}
QSqlQueryModel * Veterinaire::trier_nom()
{
    QSqlQueryModel * model= new QSqlQueryModel();

      model->setQuery("SELECT * FROM VETERINAIRE\
                        ORDER BY NOM ASC");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("Matricule"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("Téléphone"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nombre d'animaux à traiter"));

      return  model;
}
QSqlQueryModel * Veterinaire::trier_prenom()
{

    QSqlQueryModel * model= new QSqlQueryModel();

      model->setQuery("SELECT * FROM VETERINAIRE\
                            ORDER BY prenom ASC");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("Matricule"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("Téléphone"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nombre d'animaux à traiter"));

      return  model;
}
QSqlQueryModel * Veterinaire::trier_matricule()
{

    QSqlQueryModel * model= new QSqlQueryModel();

      model->setQuery("SELECT * FROM VETERINAIRE\
                        ORDER BY MATRICULE_VET ASC");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("Matricule"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("Téléphone"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nombre d'animaux à traiter"));

      return  model;
}

QSqlQueryModel * Veterinaire::recherche_matricule(int mat)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString matricule=QString::number(mat);
      model->setQuery("SELECT * FROM VETERINAIRE WHERE MATRICULE_VET= " +matricule);
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("Matricule"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("Téléphone"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nombre d'animaux à traiter"));

      return model;
}
