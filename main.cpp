#include <QApplication>
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
    query.exec("insert into users values('Gates', 'Bill12', 196);");
    query.exec("insert into users values('Zuckerberg', 'Mark11', 1984);");
    query.exec("insert into users values('Zuckerberg', 'Mark09', 11984);");

    db.commit();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    createDataTable();

    QSqlTableModel *users = new QSqlTableModel;
    users->setTable( "users" );
    users->select( );

    MultisortTableView tableView;
    tableView.setModifier( Qt::ShiftModifier );
    tableView.setSortingEnabled( true );
    tableView.setSortIcons( QIcon(":/icons/bullet_arrow_up.png"),
                            QIcon(":/icons/bullet_arrow_down.png") );
    tableView.setSelectionBehavior( QAbstractItemView::SelectRows );
    tableView.setModel( users );
    tableView.resize(400, 300);
    tableView.show();

    return a.exec();
}
