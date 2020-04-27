#include "mainwindow.h"
#include "connexion.h"
#include <QMessageBox>
#include <QApplication>
#include <QPushButton>
#include <QtDebug>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connexion c;
    bool test=c.ouvrirConnexion();
    MainWindow w;

    if(test)
    {
        w.show();
        w.display_list_animaux();
        QMessageBox::critical(nullptr, QObject::tr("BDD ouverte"),
                    QObject::tr("Connexion réussie.\n"
                                "Cliquez sur OK pour continuer"), QMessageBox::Ok);
    }
else
    {
        QMessageBox::critical(nullptr, QObject::tr("BDD pas ouverte"),
                    QObject::tr("La connexion a échoué.\n"
                                "Cliquez sur annuler pour sortir."), QMessageBox::Cancel);

    }

    return a.exec();
}
