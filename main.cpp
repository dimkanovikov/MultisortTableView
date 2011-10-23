#include <QtGui/QApplication>
#include <QTableView>
#include <QtSql>

#include "MultisortTableView.h"


void createDataTable()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(":memory:");
    db.open();

    db.transaction();
    QSqlQuery query;
    query.exec("CREATE TABLE users "
               "("
               "surname TEXT, "
               "name TEXT, "
               "birth_year INTEGER"
               ")");
    query.exec("insert into users values('Page', 'Larry', 1973);");
    query.exec("insert into users values('Jobs', 'Steve', 1955);");
    query.exec("insert into users values('Gates', 'Bill', 1955);");
    query.exec("insert into users values('Zuckerberg', 'Mark', 1984);");

    db.commit();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    createDataTable();

    QSqlTableModel *users = new QSqlTableModel;
    users->setTable( "users" );
    users->select();

    MultisortTableView tableView;
    tableView.setSortingEnabled( true );
    tableView.setModel( users );
    tableView.show();

    return a.exec();
}

