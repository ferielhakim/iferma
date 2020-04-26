#ifndef DIALOG_H
#define DIALOG_H

#include "achat.h"
#include "vente.h"
#include "stats.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QWidget>
#include <QApplication>


namespace Ui {
class Dialog;
}

class dialog : public QDialog
{
    Q_OBJECT

public:
    explicit dialog(QWidget *parent = nullptr);
    ~dialog();
public:
    void display_commandes();


private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_pb_trier_clicked();

    void on_Ajouter_clicked();

    void on_supprimer_clicked();

    void on_Modifier_clicked();

    void on_Trier_clicked();

    void on_imprimer_clicked();

    void on_imprimerV_clicked();

    void on_chercher_id_activated(const QString &arg1);

    void on_chercher_matricule_activated(const QString &arg1);

    void on_modifier_matricule_activated(const QString &arg1);

    void on_modifier_id_activated(const QString &arg1);

private:
    Ui::Dialog *ui;
    Achat tmpachat;
    VENTE tmpvente;
        QVBoxLayout * mainLayout;
        Stats s;


};

#endif // DIALOG_H
