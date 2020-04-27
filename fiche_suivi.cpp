#include "fiche_suivi.h"
#include <QDate>
#include <QDebug>
#include <QApplication>
#include <QComboBox>

Fiche_suivi::Fiche_suivi()
{
    num_fiche=0;
    analyses="";
    diagnostic="";
    poids=0;
    taille=0;
    date_consultation=date_consultation.currentDate();
    Id_animal=0;
    matricule_vet=0;
}
Fiche_suivi::Fiche_suivi(int num_fiche,QString analyses,QString diagnostic,float poids,float taille,QDate date_consultation,int Id_animal,int matricule_vet)
{
    this->num_fiche=num_fiche;
    this->analyses=analyses;
    this->diagnostic=diagnostic;
    this->poids=poids;
    this->taille=taille;
    this->date_consultation=date_consultation;
    this->Id_animal=Id_animal;
    this->matricule_vet=matricule_vet;

}
int Fiche_suivi::getnum_fiche() { return num_fiche; }
QString Fiche_suivi::getanalyses() { return analyses; }
QString Fiche_suivi::getdiagnostic() { return diagnostic;}
float Fiche_suivi::getpoids() { return poids; }
float Fiche_suivi::gettaille() { return taille;}
QDate Fiche_suivi::getdate_consultation() { return date_consultation;}
int Fiche_suivi::getId_animal() { return Id_animal; }
int Fiche_suivi::getmatricule_vet() { return matricule_vet; }

bool Fiche_suivi::ajouter_fiche()
{
    QSqlQuery query;
    QString res= QString::number(num_fiche);
    QString res2=QString::number(Id_animal);
    QString p=QString::number(poids);
    QString t=QString::number(taille);
    QString m=QString::number(matricule_vet);
    query.prepare("INSERT INTO FICHE_SUIVI (num_fiche, analyses, diagnostic, poids, taille, date_consultation,Id_animal, matricule_vet ) "
                        "VALUES (:num_fiche, :analyses, :diagnostic, :poids, :taille, :date_consultation,:Id_animal, :matricule_vet)");
    query.bindValue(":num_fiche", res);
    query.bindValue(":analyses", analyses);
    query.bindValue(":diagnostic", diagnostic);
    query.bindValue(":poids", p);
    query.bindValue(":taille", t);
    query.bindValue(":date_consultation", date_consultation);
    query.bindValue(":Id_animal", res2);
    query.bindValue(":matricule_vet", m);



    return query.exec();

}
QSqlQueryModel * Fiche_suivi::afficher_fiche()
{
    QSqlQueryModel * model= new QSqlQueryModel();

      model->setQuery("SELECT * FROM FICHE_SUIVI");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num fiche"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("Analyses"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("Diagnostic"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("Poids"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("Taille"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date_consultation"));
      model->setHeaderData(6, Qt::Horizontal, QObject::tr("ID animal"));
      model->setHeaderData(7, Qt::Horizontal, QObject::tr("Matricule vétérinaire"));


      return model;
}
QSqlQueryModel * Fiche_suivi::afficher_num_fiche()

{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select NUM_FICHE from FICHE_SUIVI");
    //pour afficher les ids sélectionnées à partir de la requête et résultant dans model.

    return model;
}
bool Fiche_suivi::supprimer_fiche(int num)
{
    QSqlQuery query;
    QString res= QString::number(num);
    query.prepare("DELETE from Fiche_suivi where num_fiche = :num ");
    query.bindValue(":num", res);

        return  query.exec();
}

bool Fiche_suivi::modifier_fiche(int num)
{

    QSqlQuery query;
    QString res=QString::number(num);
    QString p=QString::number(poids);
    QString t=QString::number(taille);
    QString mat=QString::number(matricule_vet);
    query.prepare("UPDATE Fiche_suivi SET analyses=:analyses , diagnostic=:diagnostic, poids=:poids, taille=:taille, date_consultation=:date_consultation, Id_animal=:Id_animal, matricule_vet=:matricule_vet  WHERE num_fiche =:num");
    query.bindValue(":num",res);
    query.bindValue(":analyses",analyses);
    query.bindValue(":diagnostic",diagnostic);
    query.bindValue(":poids",p);
    query.bindValue(":taille",t);
    query.bindValue(":date_consultation",date_consultation);
    query.bindValue(":Id_animal", Id_animal);
    query.bindValue(":matricule_vet",mat);


    return  query.exec();
}
QSqlQueryModel * Fiche_suivi::recherche_num_fiche(int num)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QString res = QString::number(num);
    model->setQuery("Select * From fiche_suivi WHERE num_fiche = " + res);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num fiche"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Analyses"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Diagnostic"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Poids"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Taille"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date_consultation"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("ID animal"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("matricule_vet"));

    return model;

}
QSqlQueryModel * Fiche_suivi::trier_id()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("Select * from fiche_suivi\
                         Order by id_animal ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num fiche"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Analyses"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Diagnostic"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Poids"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Taille"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date_consultation"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("ID animal"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Matricule vétérinaire"));

    return model;
}
QSqlQueryModel * Fiche_suivi::trier_num()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("Select * from fiche_suivi\
                         Order by num_fiche ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num fiche"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Analyses"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Diagnostic"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Poids"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Taille"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date_consultation"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("ID animal"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("matricule_vet"));

    return model;
}

/*QSqlQueryModel * Fiche_suivi::stat()
{
    QSqlQueryModel * model = new QSqlQueryModel;
    model->setQuery("SELECT count(date_consultation),to_char(date_consultation,'yyyy')\
                    FROM FICHE_SUIVI\
                    WHERE to_char(date_consultation,'yyyy') < to_char(sysdate,'yyyy')\
                    GROUP BY to_char(date_consultation,'yyyy')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Consultations"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Année"));

    return model;
}*/
