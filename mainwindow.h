#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "animaux.h"
#include "fiche_suivi.h"
#include "stat.h"
#include "veterinaire.h"
#include "stat_suivi.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    void display_list_animaux();

    void refresh_stat_animaux();

    void refresh_stat_fiche();


private slots:

    void on_ajouter_clicked();

    void on_modif_clicked();

    void on_supprimer_clicked();

    void on_rech_an_textChanged(const QString &arg);

    void on_ajouter_fiche_clicked();

    void on_modif_fiche_clicked();

    void on_supprimer_fiche_clicked();

    void on_rech_fiche_textChanged(const QString &arg1);

    void on_trier_clicked();

    void on_trier_fiche_clicked();

    void on_imprimer_animal_clicked();

    void on_imprimer_fiche_clicked();

    void on_ajouter_vet_clicked();

    void on_modif_vet_clicked();

    void on_supprimer_vet_clicked();

    void on_trier_vet_clicked();

    void on_rech_vet_textChanged(const QString &arg2);

    void on_imprimer_vet_clicked();


private:
    Ui::MainWindow *ui;
    animaux tmp_animal;
    Fiche_suivi tmp_fiche;
    Veterinaire tmp_vet;
    QVBoxLayout * mainLayout;
    QVBoxLayout * mainLayout2;
    Stat s;
    Stat_suivi s2;

};
#endif // MAINWINDOW_H

