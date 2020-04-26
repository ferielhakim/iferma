#include "achat.h"
#include "vente.h"
#include <QDate>
#include <QDebug>
#include <QApplication>
#include <QComboBox>
Achat::Achat()
{
    id=0;
    prix=0;
    quantite=0;
    date_achat=date_achat.currentDate();
}
VENTE::VENTE()
{
    matricule=0;
    quantite=0;
    prix=0;
    date_vente=date_vente.currentDate();
}
Achat::Achat(int id,int prix,int quantite,QDate date_achat)
{
    this->id=id;
    this->prix=prix;
    this->quantite=quantite;
    this->date_achat=date_achat;
}
int Achat::get_id(){return  id;}
int Achat::get_prix(){return  prix;}
int Achat::get_quantite(){return quantite;}
QDate Achat::get_date(){return date_achat;}

QSqlQueryModel * Achat::afficher1( )
{QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;


query.prepare("select ID_FOURNISSEUR from FOURNISSEUR ");

query.exec();
model->setQuery(query);

model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));


    return model;
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


bool Achat::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);

query.prepare("INSERT INTO ACHAT (ID_FOURNISSEUR,PRIX, QUANTITE, DATE_ACHAT) "
                    "VALUES (:id, :prix, :quantite, :date_achat)");
query.bindValue(":id", res);
query.bindValue(":prix", prix);
query.bindValue(":quantite", quantite);
query.bindValue(":date_achat", date_achat);

return    query.exec();
}

QSqlQueryModel * Achat::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from ACHAT");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRIX"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_ACHAT"));
    return model;
}

bool Achat::supprimer(int id)
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("Delete from ACHAT where ID_FOURNISSEUR = :id ");
query.bindValue(":id", res);
return    query.exec();
}

bool Achat::modifier(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);

    query.prepare("update ACHAT SET ID_FOURNISSEUR=:id,PRIX=:prix,QUANTITE=:quantite,DATE_ACHAT=:date_achat where ID_FOURNISSEUR=:id");
    query.bindValue(":id",res);
    query.bindValue(":prix",prix);
    query.bindValue(":quantite",quantite);
    query.bindValue(":date_achat",date_achat);
    return query.exec();
}
QSqlQueryModel * Achat::chercher(const QString &id)
{

   QSqlQueryModel * model=new QSqlQueryModel;
   model->setQuery("select * from ACHAT where (ID_FOURNISSEUR LIKE '"+id+"%') ");

   model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_FOURNSSEUR"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRIX"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_ACHAT"));
       return model;
}
QSqlQueryModel * Achat::trier_id()
{
    QSqlQueryModel * model=new QSqlQueryModel;
    model->setQuery("select * from ACHAT order by ID_FOURNISSEUR ");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_ACHAT"));
        return model;
}
QSqlQueryModel * Achat::trier_quantite()
{
    QSqlQueryModel * model=new QSqlQueryModel;
    model->setQuery("select * from ACHAT order by QUANTITE DESC ");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_ACHAT"));
        return model;
}


bool VENTE::ajouterV()
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

    QSqlQueryModel * VENTE::afficherV()
    {QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from VENTE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("MATRICULE_CLT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_VENTE"));
        return model;
    }

bool VENTE::supprimerV(int matricule)
    {
    QSqlQuery query;
    QString res= QString::number(matricule);
    query.prepare("Delete from VENTE where MATRICULE_CLT = :matricule ");
    query.bindValue(":matricule", res);
    return    query.exec();
    }

bool VENTE::modifierV(int matricule)
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
QSqlQueryModel * VENTE::chercherV(const QString &matricule)
{

   QSqlQueryModel * model=new QSqlQueryModel;
   model->setQuery("select * from VENTE where (MATRICULE_CLT LIKE '"+matricule+"%') ");

   model->setHeaderData(0, Qt::Horizontal, QObject::tr("MATRICULE_CLT"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("QUANTITE"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_VENTE"));
       return model;
}
QSqlQueryModel * VENTE::trierV_id()
{
    QSqlQueryModel * model=new QSqlQueryModel;
    model->setQuery("select * from VENTE order by MATRICULE_CLT ");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("MATRICULE_CLT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_VENTE"));
        return model;
}
QSqlQueryModel * VENTE::trierV_quantite()
{
    QSqlQueryModel * model=new QSqlQueryModel;
    model->setQuery("select * from VENTE order by QUANTITE DESC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("MATRICULE_CLT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_VENTE"));
        return model;
}
