#include "dialog.h"
#include "ui_dialog.h"
#include "achat.h"
#include "vente.h"
#include "stats.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QComboBox>
#include <QApplication>
#include <QDate>
#include <QDebug>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QtPrintSupport>
#include <QtCharts/QChartView>

QT_CHARTS_USE_NAMESPACE

dialog::dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //CONTROLE DE SAISIE
    ui->ajouter_prix->setValidator(new QIntValidator(0,99999,this));
    ui->ajouter_quantite->setValidator(new QIntValidator(0,99999,this));
    ui->modifier_prix->setValidator(new QIntValidator(0,99999,this));
    ui->modifier_quantite->setValidator(new QIntValidator(0,99999,this));
    ui->ajouter_quantiteV->setValidator(new QIntValidator(0,99999,this));
    ui->ajouter_prixV->setValidator(new QIntValidator(0,99999,this));
    ui->modifier_quantiteV->setValidator(new QIntValidator(0,99999,this));
    ui->modifier_prixV->setValidator(new QIntValidator(0,99999,this));
}

dialog::~dialog()
{
    delete ui;

}
void dialog::display_commandes()
{
    ui->ajouter_id->setModel(tmpachat.afficher1());
    ui->supprimer_id->setModel(tmpachat.afficher1());
    ui->modifier_id->setModel(tmpachat.afficher1());
    ui->chercher_id->setModel(tmpachat.afficher1());

    ui->ajouter_matricule->setModel(tmpvente.afficher2());
    ui->supprimer_matricule->setModel(tmpvente.afficher2());
    ui->modifier_matricule->setModel(tmpvente.afficher2());
    ui->chercher_matricule->setModel(tmpvente.afficher2());
    ui->tableView_achat->setModel(tmpachat.afficher());
    ui->tableView_vente->setModel(tmpvente.afficherV());

    mainLayout=new QVBoxLayout;
        mainLayout->addWidget(s.Preparechart());
        ui->stat->setLayout(mainLayout);
}


void dialog::on_pb_ajouter_clicked()
{
    int id = ui->ajouter_id->currentText().toInt();
    int prix = ui->ajouter_prix->text().toInt();
    int quantite = ui->ajouter_quantite->text().toInt();
    QDate date_achat = ui->ajouter_date->date();
  Achat a(id,prix,quantite,date_achat);

  bool test=a.ajouter();
  if(test)
{ui->tableView_achat->setModel(tmpachat.afficher());//refresh
      ui->stat->setLayout(mainLayout);
      ui->ajouter_id->setModel(tmpachat.afficher1());
      ui->supprimer_id->setModel(tmpachat.afficher1());
      ui->modifier_id->setModel(tmpachat.afficher1());
      ui->chercher_id->setModel(tmpachat.afficher1());

      QMessageBox::information(nullptr, QObject::tr("Ajouter un achat"),
                  QObject::tr("Achat ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un Achat"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


}

void dialog::on_pb_supprimer_clicked()
{
int id = ui->supprimer_id->currentText().toInt();
bool test=tmpachat.supprimer(id);
if(test)
{ui->tableView_achat->setModel(tmpachat.afficher());//refresh
    ui->stat->setLayout(mainLayout);
    ui->ajouter_id->setModel(tmpachat.afficher1());
    ui->supprimer_id->setModel(tmpachat.afficher1());
    ui->modifier_id->setModel(tmpachat.afficher1());
    ui->chercher_id->setModel(tmpachat.afficher1());

    QMessageBox::information(nullptr, QObject::tr("Supprimer un achat"),
                QObject::tr("Achat supprimé.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("Supprimer un achat"),
                QObject::tr("Erreur !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}

void dialog::on_pb_modifier_clicked()
{
    int id= ui->modifier_id->currentText().toInt();
    int prix= ui->modifier_prix->text().toInt();
    int quantite= ui->modifier_quantite->text().toInt();
    QDate date_achat= ui->modifier_date->date();

  Achat a(id,prix,quantite,date_achat);
  bool test=a.modifier(id);
  if (test)
  {   ui->tableView_achat->setModel(tmpachat.afficher());//refresh
      ui->stat->setLayout(mainLayout);
      ui->ajouter_id->setModel(tmpachat.afficher1());
      ui->supprimer_id->setModel(tmpachat.afficher1());
      ui->modifier_id->setModel(tmpachat.afficher1());
      ui->chercher_id->setModel(tmpachat.afficher1());

          QMessageBox::information(nullptr, QObject::tr("Modifier un achat"),
                      QObject::tr("Achat modifié.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

      }
      else
          QMessageBox::critical(nullptr, QObject::tr("Modifier un achat"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
}
void dialog::on_chercher_id_activated(const QString &)
{
    QString id=ui->chercher_id->currentText();
        ui->tableView_achat->setModel(tmpachat.chercher(id));
}
void dialog::on_pb_trier_clicked()
{
    QString tri=ui->tri->currentText();
    if (tri=="ID")
    {
        ui->tableView_achat->setModel(tmpachat.trier_id());
    }
    else
        ui->tableView_achat->setModel(tmpachat.trier_quantite());
}
void dialog::on_imprimer_clicked()
{
    QString num1 = ui->imprimer_achat->text();
        int num = ui->imprimer_achat->text().toInt();

        QSqlQuery query1;

        QString FICHE_ACHAT;
        QString ID_FOURNISSEUR="";
        QString PRIX="";
        QString QUANTITE="";
        QDate DATE_ACHAT;
        QString DATE_ACHAT1="";

        if(num1!=""){
        query1.prepare("select * from ACHAT where ID_FOURNISSEUR=:id");
       query1.bindValue(":id", num);

        if (query1.exec())
        {

            while (query1.next()) {

                 ID_FOURNISSEUR= query1.value(0).toString();
                 PRIX= query1.value(1).toString();
                 QUANTITE= query1.value(2).toString();

                 DATE_ACHAT = query1.value(3).toDate();
                 DATE_ACHAT1=DATE_ACHAT.toString("dd-MM-yyyy");

             }
        }
              QPrinter printer(QPrinter::HighResolution);
                  printer.setPageSize(QPrinter::A4);

                 QPrintDialog *dialog = new QPrintDialog(&printer);
                  if (dialog->exec() == QDialog::Accepted)
                  {               QPainter painter(&printer);
                                  painter.begin(&printer);
                                  int iYPos = 0;
                                  int iWidth = printer.width();
                                  int iHeight = printer.height();
                                  QPixmap pxPic;
                                  pxPic.load("C:/Users/dhiab/Desktop/Farm/images/logo.png", "PNG");
                                  QSize s(iWidth/3, iHeight/5);
                                  QPixmap pxScaledPic = pxPic.scaled(s, Qt::KeepAspectRatio, Qt::FastTransformation);
                                  painter.drawPixmap(3500, iYPos, pxScaledPic.width(), pxScaledPic.height(), pxScaledPic);
                                  iYPos += pxScaledPic.height() + 250;
                                  QFont f;
                                      f.setPointSize(20);
                                      f.setBold(true);
                                      painter.setFont(f);
                                   painter.drawText(1500, 500, "FICHE ACHAT");
                                    painter.drawText(2500, 500, FICHE_ACHAT);
                                   f.setPointSize(15);
                                   f.setBold(true);
                                   painter.setFont(f);
                                   painter.drawText(100, 1000, "ID N°:");
                                   painter.drawText(1500, 1000,ID_FOURNISSEUR);
                                   painter.drawText(100, 1300, "PRIX:");
                                   painter.drawText(1500, 1300,PRIX);
                                   painter.drawText(100, 1600, "QUANTITE:");
                                   painter.drawText(1500, 1600,QUANTITE);
                                   painter.drawText(100, 1900, "DATE ACHAT:");
                                   painter.drawText(1500, 1900,DATE_ACHAT1);



                                  painter.end();

                  }
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Imprimer une vente"),
                        QObject::tr("Erreur !.\n"
                                    "Veuillez selectionner une vente à imprimer .\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}




//VENTE//

void dialog::on_Ajouter_clicked()
{
    int matricule = ui->ajouter_matricule->currentText().toInt();
    int quantite = ui->ajouter_quantiteV->text().toInt();
    int prix = ui->ajouter_prixV->text().toInt();
    QDate date_vente = ui->ajouter_dateV->date();
  VENTE v(matricule,quantite,prix,date_vente);

  bool test=v.ajouterV();
  if(test)
{ui->tableView_vente->setModel(tmpvente.afficherV());//refresh
      ui->ajouter_matricule->setModel(tmpvente.afficher2());
      ui->supprimer_matricule->setModel(tmpvente.afficher2());
      ui->modifier_matricule->setModel(tmpvente.afficher2());
      ui->chercher_matricule->setModel(tmpvente.afficher2());
      QMessageBox::information(nullptr, QObject::tr("Ajouter un vente"),
                  QObject::tr("Vente ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un Vente"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


}

void dialog::on_supprimer_clicked()
{
int matricule = ui->supprimer_matricule->currentText().toInt();
bool test=tmpvente.supprimerV(matricule);
if(test)
{ui->tableView_vente->setModel(tmpvente.afficherV());//refresh
    ui->ajouter_matricule->setModel(tmpvente.afficher2());
    ui->supprimer_matricule->setModel(tmpvente.afficher2());
    ui->modifier_matricule->setModel(tmpvente.afficher2());
    ui->chercher_matricule->setModel(tmpvente.afficher2());
    QMessageBox::information(nullptr, QObject::tr("Supprimer un vente"),
                QObject::tr("Vente supprimé.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("Supprimer un vente"),
                QObject::tr("Erreur !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}

void dialog::on_Modifier_clicked()
{
    int matricule= ui->modifier_matricule->currentText().toInt();
    int quantite= ui->modifier_quantiteV->text().toInt();
    int prix= ui->modifier_prixV->text().toInt();
    QDate date_vente= ui->modifier_dateV->date();

  VENTE v(matricule,quantite,prix,date_vente);
  bool test=v.modifierV(matricule);
  if (test)
  {
      ui->tableView_vente->setModel(tmpvente.afficherV());//refresh
      ui->ajouter_matricule->setModel(tmpvente.afficher2());
      ui->supprimer_matricule->setModel(tmpvente.afficher2());
      ui->modifier_matricule->setModel(tmpvente.afficher2());
      ui->chercher_matricule->setModel(tmpvente.afficher2());
          QMessageBox::information(nullptr, QObject::tr("Modifier un vente"),
                      QObject::tr("Vente modifié.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

      }
      else
          QMessageBox::critical(nullptr, QObject::tr("Modifier un vente"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
}
void dialog::on_chercher_matricule_activated(const QString &)
{
    QString matricule=ui->chercher_matricule->currentText();
        ui->tableView_vente->setModel(tmpvente.chercherV(matricule));
}
void dialog::on_Trier_clicked()
{
    QString tri=ui->triV->currentText();
    if (tri=="MATRICULE")
    {
        ui->tableView_vente->setModel(tmpvente.trierV_id());
    }
    else
        ui->tableView_vente->setModel(tmpvente.trierV_quantite());

}

void dialog::on_imprimerV_clicked()
{
    QString num1 = ui->imprimer_vente->text();
        int num = ui->imprimer_vente->text().toInt();

        QSqlQuery query1;

        QString FICHE_VENTE;
        QString MATRICULE_CLT="";
        QString QUANTITE="";
        QString PRIX="";
        QDate DATE_VENTE;
        QString DATE_VENTE1="";

        if(num1!=""){
        query1.prepare("select * from VENTE where MATRICULE_CLT=:matricule");
       query1.bindValue(":matricule", num);

        if (query1.exec())
        {

            while (query1.next()) {

                 MATRICULE_CLT= query1.value(0).toString();
                 QUANTITE= query1.value(1).toString();
                 PRIX= query1.value(2).toString();

                 DATE_VENTE = query1.value(3).toDate();
                 DATE_VENTE1=DATE_VENTE.toString("dd-MM-yyyy");

             }
        }
              QPrinter printer(QPrinter::HighResolution);
                  printer.setPageSize(QPrinter::A4);

                 QPrintDialog *dialog = new QPrintDialog(&printer);
                  if (dialog->exec() == QDialog::Accepted)
                  {               QPainter painter(&printer);
                                  painter.begin(&printer);
                                  int iYPos = 0;
                                  int iWidth = printer.width();
                                  int iHeight = printer.height();
                                  QPixmap pxPic;
                                  pxPic.load("C:/Users/dhiab/Desktop/Farm/images/logo.png", "PNG");
                                  QSize s(iWidth/3, iHeight/5);
                                  QPixmap pxScaledPic = pxPic.scaled(s, Qt::KeepAspectRatio, Qt::FastTransformation);
                                  painter.drawPixmap(3500, iYPos, pxScaledPic.width(), pxScaledPic.height(), pxScaledPic);
                                  iYPos += pxScaledPic.height() + 250;
                                  QFont f;
                                      f.setPointSize(20);
                                      f.setBold(true);
                                      painter.setFont(f);
                                   painter.drawText(1500, 500, "FICHE VENTE");
                                    painter.drawText(2500, 500, FICHE_VENTE);
                                   f.setPointSize(15);
                                   f.setBold(true);
                                   painter.setFont(f);
                                   painter.drawText(100, 1000, "MATRICULE N°:");
                                   painter.drawText(1500, 1000,MATRICULE_CLT);
                                   painter.drawText(100, 1300, "QUANTITE:");
                                   painter.drawText(1500, 1300,QUANTITE);
                                   painter.drawText(100, 1600, "PRIX:");
                                   painter.drawText(1500, 1600,PRIX);
                                   painter.drawText(100, 1900, "DATE VENTE:");
                                   painter.drawText(1500, 1900,DATE_VENTE1);



                                  painter.end();

                  }
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Imprimer une vente"),
                        QObject::tr("Erreur !.\n"
                                    "Veuillez selectionner une vente à imprimer .\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}





void dialog::on_modifier_id_activated(const QString &)
{
    QString var=ui->modifier_id->currentText();
      QSqlQuery query1;
      query1.prepare("select * from ACHAT where ID_FOURNISSEUR=:id");
      query1.bindValue(":id", var);

      if (query1.exec())
      {

          while (query1.next()) {

               ui->supprimer_id->setModel(tmpachat.afficher1());
               ui->ajouter_id->setModel(tmpachat.afficher1());

               ui->modifier_id->setCurrentText(query1.value(0).toString());
               ui->modifier_prix->setText(query1.value(1).toString());
               ui->modifier_quantite->setText(query1.value(2).toString());
               ui->modifier_date->setDate(query1.value(3).toDate());

          }
      }
  }

void dialog::on_modifier_matricule_activated(const QString &)
{
    QString var=ui->modifier_matricule->currentText();
      QSqlQuery query1;
      query1.prepare("select * from VENTE where MATRICULE_CLT=:matricule");
      query1.bindValue(":matricule", var);

      if (query1.exec())
      {

          while (query1.next()) {

               ui->supprimer_matricule->setModel(tmpvente.afficher2());
               ui->ajouter_matricule->setModel(tmpvente.afficher2());

               ui->modifier_matricule->setCurrentText(query1.value(0).toString());
               ui->modifier_quantiteV->setText(query1.value(1).toString());
               ui->modifier_prixV->setText(query1.value(2).toString());
               ui->modifier_dateV->setDate(query1.value(3).toDate());

          }
      }
}
