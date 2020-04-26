#include "vente.h"
#include <QDate>
#include <QDebug>
#include <QApplication>
#include <QComboBox>

VENTE::VENTE()
{
    matricule=0;
    quantite=0;
    prix=0;
    date_vente=date_vente.currentDate();
}
VENTE::VENTE(int matricule,int quantite,int prix,QDate date_vente)
    {
        this->matricule=matricule;
        this->quantite=quantite;
        this->prix=prix;
        this->date_vente=date_vente;
    }
    int VENTE::get_matricule(){return  matricule;}
    int VENTE::get_quantite(){return  quantite;}
    int VENTE::get_prix(){return prix;}
    QDate VENTE::get_datevente(){return date_vente;}



 QSqlQueryModel * VENTE::afficher2( )
    {QSqlQueryModel * model= new QSqlQueryModel();
        QSqlQuery query;


    query.prepare("select MATRICULE_CLT from CLIENT ");

    query.exec();
    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("MATRICULE_CLT"));


        return model;
    }


    bool VENTE::ajouter()
    {
    QSqlQuery query;
    QString res= QString::number(matricule);

    query.prepare("INSERT INTO VENTE (MATRICULE_CLT,QUANTITE, PRIX, DATE_VENTE) "
                        "VALUES (:matricule, :quantite, :prix, :date_vente)");
    query.bindValue(":matricule", res);
    query.bindValue(":quantite", quantite);
    query.bindValue(":prix", prix);
    query.bindValue(":date_vente", date_vente);

    return    query.exec();
    }

    QSqlQueryModel * VENTE::afficher()
    {QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from VENTE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("MATRICULE_CLT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_VENTE"));
        return model;
    }

    bool VENTE::supprimer(int matricule)
    {
    QSqlQuery query;
    QString res= QString::number(matricule);
    query.prepare("Delete from VENTE where MATRICULE_CLT = :matricule ");
    query.bindValue(":matricule", res);
    return    query.exec();
    }

    bool VENTE::modifier(int matricule)
    {
        QSqlQuery query;
        QString res=QString::number(matricule);


        query.prepare("update VENTE SET MATRICULE_CLT=:matricule,QUANTITE=:quantite,PRIX=:prix,DATE_VENTE=:date_vente where MATRICULE_CLT=:matricule");
        query.bindValue(":matricule",res);
        query.bindValue(":quantite",quantite);
        query.bindValue(":prix",prix);
        query.bindValue(":date_vente",date_vente);
        return query.exec();
    }
