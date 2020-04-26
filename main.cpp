#include "dialog.h"
#include <QApplication>
#include <QMessageBox>
#include "connexion.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connexion c;
    bool test=c.ouvrirConnexion();
    dialog d;

    if(test)
    {d.show();
     d.display_commandes();

        QMessageBox::critical(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}
else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    return a.exec();
}
