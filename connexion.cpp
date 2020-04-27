#include "connexion.h"
#include <QSqlError>
#include <QApplication>

connexion::connexion()
{

}
bool connexion::ouvrirConnexion()
{
    bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Ferme");
db.setUserName("admin");//inserer nom de l'utilisateur
db.setPassword("esprit18");//inserer mot de passe de cet utilisateur
if (db.open())
    test=true;
/*else
    test=false;*/

    return  test;
}
void connexion::fermerConnexion()
{db.close();}
