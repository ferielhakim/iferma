#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "animaux.h"
#include "fiche_suivi.h"
#include "stat.h"
#include "veterinaire.h"
#include "stat_suivi.h"

#include <QApplication>
#include <QDate>
#include <QString>
#include <QDateEdit>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QComboBox>
#include <QtPrintSupport>
#include <QPrintDialog>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_animaux->setModel(tmp_animal.afficher());
    ui->tab_fiche->setModel(tmp_fiche.afficher_fiche());
    ui->tab_vet->setModel(tmp_vet.afficher_vet());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::display_list_animaux()
{
    //initialiser tabs
    ui->tab_animaux->setModel(tmp_animal.afficher());
    ui->tab_fiche->setModel(tmp_fiche.afficher_fiche());
    ui->tab_vet->setModel(tmp_vet.afficher_vet());
    //initaliser combo_box
    ui->id_aff_2->setModel(tmp_animal.afficher_id());
    ui->id_supp->setModel(tmp_animal.afficher_id());
    ui->id_modif->setModel(tmp_animal.afficher_id());
    ui->id_modif_2->setModel(tmp_animal.afficher_id());
    ui->mat_modif->setModel(tmp_vet.afficher_matricule());
    ui->mat_vet_supp->setModel(tmp_vet.afficher_matricule());
    ui->veterinaire->setModel(tmp_vet.afficher_matricule());
    ui->vet->setModel(tmp_vet.afficher_matricule());
    ui->num_supp->setModel(tmp_fiche.afficher_num_fiche());
    ui->num_modif->setModel(tmp_fiche.afficher_num_fiche());
    //initaliser stat
    mainLayout=new QVBoxLayout;
    mainLayout->addWidget(s.Preparechart());
    ui->Stat->setLayout(mainLayout);
    mainLayout2=new QVBoxLayout;
    mainLayout2->addWidget(s2.Preparechart());
    ui->stat_fiche->setLayout(mainLayout2);
}

void MainWindow::refresh_stat_animaux()
{
    if ( ui->Stat->layout() != NULL )
    {
    QLayoutItem* item;
    while ( ( item = ui->Stat->layout()->takeAt( 0 ) ) != NULL )
    {
    delete item->widget();
    delete item;
    }
    delete ui->Stat->layout();
    }
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(s2.Preparechart());
    ui->Stat->setLayout(mainLayout);
}

void MainWindow::refresh_stat_fiche()
{
    if ( ui->stat_fiche->layout() != NULL )
    {
    QLayoutItem* item;
    while ( ( item = ui->stat_fiche->layout()->takeAt( 0 ) ) != NULL )
    {
    delete item->widget();
    delete item;
    }
    delete ui->stat_fiche->layout();
    }
    mainLayout2 = new QVBoxLayout;
    mainLayout2->addWidget(s2.Preparechart());
    ui->stat_fiche->setLayout(mainLayout2);
}

void MainWindow::on_ajouter_clicked()
{
    int Id_animal= ui->id->text().toInt();
    QString nom= ui->nom->text();
    bool sexe= ui->sexe->currentIndex();
    QString race= ui->race->text();
    int etat= ui->etat->currentIndex();
    QDate date_naissance= ui->date->date();

  animaux a(Id_animal,nom,sexe,race,etat,date_naissance);

  if ((Id_animal<9999) && (nom!="") && (race!="") )
  {

  bool test=a.ajouter();
  if(test)
    {
      //refresh
      refresh_stat_animaux();
      ui->id_aff_2->setModel(tmp_animal.afficher_id());
      ui->id_supp->setModel(tmp_animal.afficher_id());
      ui->id_modif->setModel(tmp_animal.afficher_id());
      ui->id_modif_2->setModel(tmp_animal.afficher_id());
      ui->tab_animaux->setModel(tmp_animal.afficher());
        QMessageBox::information(nullptr, QObject::tr("Ajouter un animal"),
                  QObject::tr("Animal ajouté.\n"
                              "Cliquez sur Ok pour continuer."), QMessageBox::Ok);

    }
   else
        QMessageBox::critical(nullptr, QObject::tr("Ajouter un animal"),
                  QObject::tr("Erreur! Identifiant existe déjà\n"
                              "Cliquez sur Ok pour continuer."), QMessageBox::Ok);
  }
  else
       {
            QMessageBox::critical(nullptr, QObject::tr("Ajouter un animal"),
                QObject::tr("Erreur! Veuillez vérifier les champs\n"
                            "Cliquez sur Ok pour continuer."), QMessageBox::Ok);

       }


}

void MainWindow::on_modif_clicked()
{
    int id=ui->id_modif->currentText().toInt();;
    QString nom= ui->nom_modif->text();
    bool sexe= ui->sexe_modif->currentIndex();
    QString race= ui->race_modif->text();
    bool etat= ui->etat_modif->currentIndex();
    QDate date_naissance= ui->date_modif->date();

  animaux a(id,nom,sexe,race,etat,date_naissance);
  bool test=a.modifier(id);
  if(test)
  {
      refresh_stat_animaux();
      ui->tab_animaux->setModel(a.afficher());
      QMessageBox::information(nullptr, QObject::tr("Modifier un animal"),
                  QObject::tr("Animal modifié.\n"
                              "Cliquez sur Ok pour continuer."), QMessageBox::Ok);
  }
  else
        {
     QMessageBox::critical(nullptr, QObject::tr("Modifier un animal"),
                 QObject::tr("Erreur!\n"
                             "Erreur de modification de l'animal.\n Veuillez réessayer."), QMessageBox::Ok);
        }
}

void MainWindow::on_supprimer_clicked()
{
    int idd=ui->id_supp->currentText().toInt();
    bool test= tmp_animal.supprimer(idd);
    if(test)
    {
        refresh_stat_animaux();
        ui->id_aff_2->setModel(tmp_animal.afficher_id());
        ui->id_supp->setModel(tmp_animal.afficher_id());
        ui->id_modif->setModel(tmp_animal.afficher_id());
        ui->id_modif_2->setModel(tmp_animal.afficher_id());
        ui->tab_animaux->setModel(tmp_animal.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un animal"),
                    QObject::tr("Animal supprimé.\n"
                                "Cliquez sur Ok pour continuer."), QMessageBox::Ok);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un animal"),
                    QObject::tr("Erreur !.\n"
                                "Suppression impossible."), QMessageBox::Ok);
    }
}

void MainWindow::on_rech_an_textChanged(const QString &arg)
{
    int id = arg.toInt();
    ui->tab_animaux->setModel(tmp_animal.recherche_id(id));

}

void MainWindow::on_ajouter_fiche_clicked()
{
    int num_fiche= ui->num_fiche->text().toInt();
    QString analyses= ui->analyses->toPlainText();
    QString diagnostic= ui->diagnostic->toPlainText();
    float poids= ui->poids->value() ;
    float taille= ui->taille->value();
    int mat_vet=ui->veterinaire->currentText().toInt();
    QDate date_consultation= ui->date_cons->date();
    int Id_animal=ui->id_aff_2->currentText().toInt();
  Fiche_suivi f(num_fiche,analyses,diagnostic,poids,taille,date_consultation,Id_animal,mat_vet);
  if ((num_fiche<9999) && (analyses!="") && (diagnostic!="") && (poids!=0) && (taille!=0) && (Id_animal!=0) && (mat_vet!=0))
  {bool test=f.ajouter_fiche();
  if(test)
    {

      QSqlQuery query1,query2;
      int nb_an=0;
      QString res=QString::number(mat_vet);
      query2.prepare("SELECT ANIMAUX_A_TRAITER FROM VETERINAIRE WHERE MATRICULE_VET =:mat_vet");
      query2.bindValue(":mat_vet",res);
        if(query2.exec())
        {
            while(query2.next())
            {
                nb_an=query2.value(0).toInt();
            }
        nb_an=nb_an+1;
        QString res2=QString::number(nb_an);
        query1.prepare("UPDATE VETERINAIRE SET ANIMAUX_A_TRAITER=:nb_an WHERE MATRICULE_VET =:mat_vet");
        query1.bindValue(":mat_vet",res);
        query1.bindValue(":nb_an",res2);

            query1.exec();
        }
        //refresh
      refresh_stat_fiche();
      ui->tab_vet->setModel(tmp_vet.afficher_vet());
      ui->num_supp->setModel(tmp_fiche.afficher_num_fiche());
      ui->num_modif->setModel(tmp_fiche.afficher_num_fiche());
      ui->veterinaire->setModel(tmp_vet.afficher_matricule());
      ui->tab_fiche->setModel(tmp_fiche.afficher_fiche());
        QMessageBox::information(nullptr, QObject::tr("Ajouter une fiche de suivi"),
                  QObject::tr("Fiche de suivi ajoutée.\n"
                              "Cliquez sur Ok pour continuer."), QMessageBox::Ok);

    }
   else
        {QMessageBox::critical(nullptr, QObject::tr("Ajouter une fiche de suivi"),
                  QObject::tr("Erreur! Numero fiche existe déjà\n"
                              "Cliquez sur Ok pour continuer."), QMessageBox::Ok);}
  }
  else
  {
      QMessageBox::information(nullptr, QObject::tr("Ajouter une fiche de suivi"),
                QObject::tr("Erreur! Veuillez vérifier les champs.\n"
                            "Cliquez sur Ok pour continuer."), QMessageBox::Ok);
  }
}

void MainWindow::on_modif_fiche_clicked()
{
    int num= ui->num_modif->currentText().toInt();
    QString analyses= ui->analyses_modif->toPlainText();
    QString diagnostic= ui->diagnostic_modif->toPlainText();
    float poids= ui->poids_modif->value();
    float taille= ui->taille_modif->value();
    int matricule_vet=ui->vet->currentText().toInt();
    QDate date_consultation= ui->date_cons_modif->date();
    int Id_animal=ui->id_modif_2->currentText().toInt();
  Fiche_suivi f(num,analyses,diagnostic,poids,taille,date_consultation,Id_animal,matricule_vet);
  bool test=f.modifier_fiche(num);
  if(test)
  {
      //refresh
      ui->num_supp->setModel(tmp_fiche.afficher_num_fiche());
      ui->num_modif->setModel(tmp_fiche.afficher_num_fiche());
      ui->vet->setModel(tmp_vet.afficher_matricule());
      ui->tab_fiche->setModel(tmp_fiche.afficher_fiche());
      refresh_stat_fiche();


      QMessageBox::information(nullptr, QObject::tr("Modifier une fiche de suivi"),
                  QObject::tr("Fiche de suivi modifiée.\n"
                              "Cliquez sur Ok pour continuer."), QMessageBox::Ok);
  }
  else
        {
     QMessageBox::critical(nullptr, QObject::tr("Modifier une fiche de suivi"),
                 QObject::tr("Erreur!\n"
                             "Erreur de modification de la fiche de suivi.\n Veuillez réessayer."), QMessageBox::Ok);
        }
}

void MainWindow::on_supprimer_fiche_clicked()
{
    int num=ui->num_supp->currentText().toInt();
    bool test= tmp_fiche.supprimer_fiche(num);
    if(test)
    {
        //refresh
        refresh_stat_fiche();
        ui->num_supp->setModel(tmp_fiche.afficher_num_fiche());
        ui->num_modif->setModel(tmp_fiche.afficher_num_fiche());
        ui->tab_fiche->setModel(tmp_fiche.afficher_fiche());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer une fiche de suivi"),
                    QObject::tr("Fiche de suivi supprimée.\n"
                                "Cliquez sur Ok pour continuer."), QMessageBox::Ok);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Supprimer une fiche de suivi"),
                    QObject::tr("Erreur !.\n"
                                "Suppression impossible."), QMessageBox::Ok);
    }
}

void MainWindow::on_rech_fiche_textChanged(const QString &arg1)
{
    int num=arg1.toInt();
    ui->tab_fiche->setModel(tmp_fiche.recherche_num_fiche(num));
}

void MainWindow::on_trier_clicked()
{
    QString tri=ui->tri->currentText();
    if (tri=="ID")
    {
        ui->tab_animaux->setModel(tmp_animal.trier_id());
    }
    else
        ui->tab_animaux->setModel(tmp_animal.trier_nom());
}

void MainWindow::on_trier_fiche_clicked()
{
    QString tri=ui->tri_fiche->currentText();
    if (tri=="ID animal")
    {
        ui->tab_fiche->setModel(tmp_fiche.trier_id());
    }
    else
        ui->tab_fiche->setModel(tmp_fiche.trier_num());
}

void MainWindow::on_imprimer_animal_clicked()
{
    int id=ui->rech_an->text().toInt();
        QString id_animal="";
        QString nom="";
        QString sexe="";
        QString race="";
        QString date_naissance="";
        QString etat="";
        QString res=QString::number(id);
        QSqlQuery query;
        query.prepare("SELECT * FROM ANIMAUX WHERE ID_ANIMAL= :id");
        query.bindValue(":id",res);
        if (query.exec())
        {
            while (query.next())
            {
                id_animal=query.value(0).toString();
                nom=query.value(1).toString();
                sexe=query.value(2).toString();
                race=query.value(3).toString();
                date_naissance=query.value(4).toString();
                etat=query.value(5).toString();
            }
        }

        QPrinter printer(QPrinter::HighResolution);
        printer.setPageSize(QPrinter::A4);
        QPrintDialog *dialog = new QPrintDialog(&printer,this);
         if (dialog->exec() == QDialog::Accepted)
            {
                QPainter painter(&printer);
                painter.begin(&printer);
                quint32 iYPos = 0;
                quint32 iWidth = printer.width();
                quint32 iHeight = printer.height();
                QPixmap pxPic;
                pxPic.load("C:/Users/DELL/Documents/2ème/2ème semestre/c++/projet/Animaux_suivi/logo.png", "PNG");
                QSize s(iWidth/3, iHeight/5);
                QPixmap pxScaledPic = pxPic.scaled(s, Qt::KeepAspectRatio, Qt::FastTransformation);
                painter.drawPixmap(3500, iYPos, pxScaledPic.width(), pxScaledPic.height(), pxScaledPic);
                iYPos -= pxScaledPic.height() + 1000;
                QFont f;
                f.setPointSize(20);
                f.setBold(true);
                f.setItalic(true);
                painter.setBrush(QColor(50,205,50));
                painter.setFont(f);
                painter.drawText(1700,400,"Fiche animal");
                painter.drawText(400, 1000, "ID animal: ");
                painter.drawText(2000, 1000,id_animal);
                f.setPointSize(15);
                f.setBold(true);
                painter.setFont(f);
                painter.drawText(100, 1400, "Nom: ");
                painter.drawText(1000, 1400,nom);
                painter.drawText(100, 1700, "Sexe: ");
                painter.drawText(1000, 1700,sexe);
                painter.drawText(100, 2000, "Race: ");
                painter.drawText(1000, 2000,race);
                painter.drawText(100, 2300, "Date de naissance: ");
                painter.drawText(1500, 2300,date_naissance);
                painter.drawText(100, 2600, "Etat: ");
                painter.drawText(1000, 2600,etat);
                QFont f1,f2;
                f1.setPointSize(15);
                f1.setItalic(true);
                f1.setBold(true);
                f1.setUnderline(true);
                painter.setBrush(QColor(255,0,0));
                painter.setFont(f1);
                painter.drawText(3800,5000, "NB");
                f2.setPointSize(10);
                f2.setItalic(true);
                painter.setFont(f2);
                painter.drawText(3500,5200,"Etat=0 animal en bonne santé ");
                painter.drawText(3500,5400,"Etat=1 animal malade");
                painter.drawText(3500,5600,"Sexe=0 Mâle");
                painter.drawText(3500,5800,"Sexe=1 Femelle");


                   painter.end();

               }


}

void MainWindow::on_imprimer_fiche_clicked()
{
    int num=ui->rech_fiche->text().toInt();
    QString num_fiche="";
    QString analyses="";
    QString diagnostic="";
    QString poids="";
    QString taille="";
    QString date="";
    QString id_an="";
    QString mat_vet="";
    QString res=QString::number(num);
    QSqlQuery query;
    query.prepare("SELECT * FROM FICHE_SUIVI WHERE NUM_FICHE = :num");
    query.bindValue(":num",res);
    if (query.exec())
    {
        while (query.next())
        {
            num_fiche=query.value(0).toString();
            analyses=query.value(1).toString();
            diagnostic=query.value(2).toString();
            poids=query.value(3).toString();
            taille=query.value(4).toString();
            date=query.value(5).toString();
            id_an=query.value(6).toString();
            mat_vet=query.value(7).toString();
        }
    }

    QPrinter printer(QPrinter::HighResolution);
    printer.setPageSize(QPrinter::A4);
    QPrintDialog *dialog = new QPrintDialog(&printer,this);
     if (dialog->exec() == QDialog::Accepted)
        {
            QPainter painter(&printer);
            painter.begin(&printer);
            quint32 iYPos = 0;
            quint32 iWidth = printer.width();
            quint32 iHeight = printer.height();
            QPixmap pxPic;
            pxPic.load("C:/Users/DELL/Documents/2ème/2ème semestre/c++/projet/Animaux_suivi/logo.png", "PNG");
            QSize s(iWidth/3, iHeight/5);
            QPixmap pxScaledPic = pxPic.scaled(s, Qt::KeepAspectRatio, Qt::FastTransformation);
            painter.drawPixmap(3500, iYPos, pxScaledPic.width(), pxScaledPic.height(), pxScaledPic);
            iYPos += pxScaledPic.height() + 250;
            QFont f;
            f.setPointSize(20);
            f.setBold(true);
            f.setItalic(true);
            painter.setFont(f);
            painter.drawText(1500,400,"Fiche de suivi médical");
            painter.drawText(400, 1000, "Fiche de suivi numéro: ");
            painter.drawText(2500, 1000,num_fiche);
            f.setPointSize(15);
            f.setBold(true);
            painter.setFont(f);
            painter.drawText(100, 1400, "Matricule du vétérinaire: ");
            painter.drawText(1700, 1400,mat_vet);
            painter.drawText(100, 1700, "ID de l'animal: ");
            painter.drawText(1500, 1700,id_an);
            painter.drawText(100, 2000, "Analyses effectuées: ");
            painter.drawText(1500, 2000,analyses);
            painter.drawText(100, 2300, "Diagnostic: ");
            painter.drawText(1500, 2300,diagnostic);
            painter.drawText(100, 2600, "Poids de l'animal: ");
            painter.drawText(1500, 2600,poids);
            painter.drawText(100, 2900, "Taille de l'animal: ");
            painter.drawText(1500, 2900,taille);
            painter.drawText(100, 3200, "Date de la consultation: ");
            painter.drawText(1700, 3200,date);


               painter.end();

           }
}

void MainWindow::on_ajouter_vet_clicked()
{
    int matricule_vet=ui->matricule_vet->text().toInt();
    QString nom=ui->nom_vet->text();
    QString prenom=ui->prenom->text();
    int numero_telephone=ui->num_tel->text().toInt();
    QString adresse=ui->adresse->toPlainText();
    int animaux_a_traiter=ui->nb_an->value();
    Veterinaire v(matricule_vet,nom,prenom,numero_telephone,adresse,animaux_a_traiter);
    bool test=v.ajouter();
    if ((matricule_vet!=0) && (matricule_vet<99) && (prenom!="") && (nom!="") && (numero_telephone!=0) && (adresse!="") && (numero_telephone<99999999))
    {
        if (test)
    {
        ui->tab_vet->setModel(tmp_vet.afficher_vet());
        ui->mat_modif->setModel(tmp_vet.afficher_matricule());
        ui->mat_vet_supp->setModel(tmp_vet.afficher_matricule());
        ui->veterinaire->setModel(tmp_vet.afficher_matricule());
        ui->vet->setModel(tmp_vet.afficher_matricule());


        QMessageBox::information(nullptr, QObject::tr("Ajouter un vétérinaire"),
                  QObject::tr("Vétérinaire ajouté.\n"
                              "Cliquez sur Ok pour continuer."), QMessageBox::Ok);

    }
   else
        {QMessageBox::critical(nullptr, QObject::tr("Ajouter un vétérinaire"),
                  QObject::tr("Erreur! \n"
                              "Cliquez sur Ok pour continuer."), QMessageBox::Ok);}
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("Ajouter un vétérinaire"),
                          QObject::tr("Erreur! \n"
                                      "Veuillez vérifier les champs."), QMessageBox::Ok);
    }


}

void MainWindow::on_modif_vet_clicked()
{
    int id=ui->mat_modif->currentText().toInt();
    QString nom=ui->nom_vet_modif->text();
    QString prenom=ui->prenom_vet_modif->text();
    int numero_telephone=ui->num_tel_modif->text().toInt();
    QString adresse=ui->adresse_modif2->toPlainText();
    int animaux_a_traiter=ui->an_modif->value();
    Veterinaire v(id,nom,prenom,numero_telephone,adresse,animaux_a_traiter);
    bool test=v.modifier(id);
    if (test)
    {
        ui->mat_modif->setModel(tmp_vet.afficher_matricule());
        ui->mat_vet_supp->setModel(tmp_vet.afficher_matricule());
        ui->veterinaire->setModel(tmp_vet.afficher_matricule());
        ui->vet->setModel(tmp_vet.afficher_matricule());
        ui->tab_vet->setModel(tmp_vet.afficher_vet());
        QMessageBox::information(nullptr, QObject::tr("Modifier un vétérinaire"),
                  QObject::tr("Vétérinaire modifié.\n"
                              "Cliquez sur Ok pour continuer."), QMessageBox::Ok);

    }
   else
        {QMessageBox::critical(nullptr, QObject::tr("Modifier un vétérinaire"),
                  QObject::tr("Erreur! \n"
                              "Cliquez sur Ok pour continuer."), QMessageBox::Ok);}
}

void MainWindow::on_supprimer_vet_clicked()
{
    int idd=ui->mat_vet_supp->currentText().toInt();
    bool test= tmp_vet.supprimer(idd);
    if(test)
    {
        ui->mat_modif->setModel(tmp_vet.afficher_matricule());
        ui->mat_vet_supp->setModel(tmp_vet.afficher_matricule());
        ui->veterinaire->setModel(tmp_vet.afficher_matricule());
        ui->vet->setModel(tmp_vet.afficher_matricule());
        ui->tab_vet->setModel(tmp_vet.afficher_vet());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un vétérinaire"),
                    QObject::tr("Vétérinaire supprimé.\n"
                                "Cliquez sur Ok pour continuer."), QMessageBox::Ok);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un vétérinaire"),
                    QObject::tr("Erreur ! Suppression impossible.\n"
                                "Le vétérinaire est associé à une fiche de suivi"), QMessageBox::Ok);
    }

}

void MainWindow::on_trier_vet_clicked()
{
    QString tri=ui->tri_vet->currentText();
    if (tri=="Nom")
        ui->tab_vet->setModel(tmp_vet.trier_nom());
    else if (tri=="Prenom")
        ui->tab_vet->setModel(tmp_vet.trier_prenom());
    else if(tri=="Matricule")
        ui->tab_vet->setModel(tmp_vet.trier_matricule());
}

void MainWindow::on_rech_vet_textChanged(const QString &arg2)
{
    int mat=arg2.toInt();
    ui->tab_vet->setModel(tmp_vet.recherche_matricule(mat));
}

void MainWindow::on_imprimer_vet_clicked()
{
    int matricule=ui->rech_vet->text().toInt();
    QString matricule_vet="";
    QString nom="";
    QString prenom="";
    QString numero_telephone="";
    QString adresse="";
    QString animaux_a_traiter="";
    QString res=QString::number(matricule);
    QSqlQuery query;
    query.prepare("SELECT * FROM VETERINAIRE WHERE MATRICULE_VET = :matricule");
    query.bindValue(":matricule",res);
    if (query.exec())
    {
        while (query.next())
        {
            matricule_vet=query.value(0).toString();
            nom=query.value(1).toString();
            prenom=query.value(2).toString();
            numero_telephone=query.value(3).toString();
            adresse=query.value(4).toString();
            animaux_a_traiter=query.value(5).toString();
        }
    }

    QPrinter printer(QPrinter::HighResolution);
    printer.setPageSize(QPrinter::A4);
    QPrintDialog *dialog = new QPrintDialog(&printer,this);
     if (dialog->exec() == QDialog::Accepted)
        {
            QPainter painter(&printer);
            painter.begin(&printer);
            quint32 iYPos = 0;
            quint32 iWidth = printer.width();
            quint32 iHeight = printer.height();
            QPixmap pxPic;
            pxPic.load("C:/Users/DELL/Documents/2ème/2ème semestre/c++/projet/Animaux_suivi/logo.png", "PNG");
            QSize s(iWidth/3, iHeight/5);
            QPixmap pxScaledPic = pxPic.scaled(s, Qt::KeepAspectRatio, Qt::FastTransformation);
            painter.drawPixmap(3500, iYPos, pxScaledPic.width(), pxScaledPic.height(), pxScaledPic);
            iYPos += pxScaledPic.height() + 250;
            QFont f;
            f.setPointSize(20);
            f.setBold(true);
            f.setItalic(true);
            painter.setFont(f);
            painter.drawText(1700,400,"Fiche vétérinaire");
            painter.drawText(400, 1000, "Matricule vétérinaire: ");
            painter.drawText(2500, 1000,matricule_vet);
            f.setPointSize(15);
            f.setBold(true);
            painter.setFont(f);
            painter.drawText(100, 1400, "Nom: ");
            painter.drawText(1500, 1400,nom);
            painter.drawText(100, 1700, "Prenom: ");
            painter.drawText(1500, 1700,prenom);
            painter.drawText(100, 2000, "Numéro de téléphone: ");
            painter.drawText(1800, 2000,numero_telephone);
            painter.drawText(100, 2300, "Adresse: ");
            painter.drawText(1500, 2300,adresse);
            painter.drawText(100, 2600, "Nombre d'animaux à traiter: ");
            painter.drawText(2000, 2600,animaux_a_traiter);

               painter.end();

           }
}









