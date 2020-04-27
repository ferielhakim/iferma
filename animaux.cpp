#include "animaux.h"
//#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QDate>
#include <QDebug>
#include <QApplication>
#include <QComboBox>

animaux::animaux()
{
    Id_animal=0;
    nom="";
    sexe=true;
    race="";
    etat=true;
    date_naissance=date_naissance.currentDate();

}
animaux::animaux(int Id_animal, QString nom,bool sexe,QString race,bool etat,QDate date_naissance)
{
    this->Id_animal=Id_animal;
    this->nom=nom;
    this->sexe=sexe;
    this->race=race;
    this->etat=etat;
    this->date_naissance=date_naissance;
}

int animaux::getId_animal() { return Id_animal; }
QString animaux::getnom() { return nom; }
bool animaux::getsexe() { return sexe; }
QString animaux::getrace() { return race;}
QDate animaux::getdate_naissance() { return date_naissance;}
bool animaux::getetat() { return etat;}


bool animaux::ajouter()
{
    QSqlQuery query;
    QString res= QString::number(Id_animal);

    query.prepare("INSERT INTO animaux (ID_ANIMAL, NOM, SEXE, RACE, DATE_NAISSANCE, ETAT ) "
                        "VALUES (:Id_animal, :nom, :sexe, :race, :date_naissance, :etat)");
    query.bindValue(":Id_animal", res);
    query.bindValue(":nom", nom);
    query.bindValue(":sexe", sexe);
    query.bindValue(":race", race);
    query.bindValue(":date_naissance", date_naissance);
    query.bindValue(":etat", etat);

    return    query.exec();
}

QSqlQueryModel * animaux::afficher()
{
  QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM animaux");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Sexe"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Race"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de naissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Etat"));

    return model;
}

QSqlQueryModel * animaux::afficher_id()

{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select ID_ANIMAL from ANIMAUX");
   //pour afficher les ids sélectionnées à partir de la requête et résultant dans model.

    return model;
}
QSqlQueryModel * animaux::afficher_race()

{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select RACE from ANIMAUX");
    //pour afficher les ids sélectionnées à partir de la requête et résultant dans model.

    return model;
}
bool animaux::supprimer(int idd)
{
    QSqlQuery query;
    QString res= QString::number(idd);
    query.prepare("DELETE from ANIMAUX where ID_ANIMAL = :idd ");
    query.bindValue(":idd", res);

        return  query.exec();
}

bool animaux::modifier(int id)
{

    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("UPDATE ANIMAUX SET nom =:nom , sexe=:sexe, race=:race, date_naissance=:date_naissance, etat=:etat WHERE Id_animal =:id");
    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":sexe",sexe);
    query.bindValue(":race",race);
    query.bindValue(":date_naissance",date_naissance);
    query.bindValue(":etat",etat);



    return  query.exec();
}

QSqlQueryModel * animaux::recherche_id(int id)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QString res = QString::number(id);
    model->setQuery("SELECT * FROM ANIMAUX WHERE ID_ANIMAL=" +res);
    //query.bindValue(":id", res);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Sexe"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Race"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de naissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Etat"));


    return model;
}
QSqlQueryModel * animaux::trier_id()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("Select * from animaux\
                         Order by ID_ANIMAL ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Sexe"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Race"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de naissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Etat"));

    return model;
}
QSqlQueryModel * animaux::trier_nom()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("Select * from animaux\
                         Order by nom ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Sexe"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Race"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de naissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Etat"));

    return model;
}
QSqlQueryModel * animaux::recherche_race(QString race1)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ANIMAUX WHERE RACE = '"+race1+"' " );

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Sexe"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Race"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de naissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Etat"));


    return model;
}
