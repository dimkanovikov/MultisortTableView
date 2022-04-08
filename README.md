# MultisortTableView

MultisortTableView is a Qt widget that inherits from QTableView. It can sort a table by multiple columns.

To sort data it uses the AlphanumSortProxyModel that inherits from QSortFilterProxyModel and sorts data by using the alphanum algorithm (for more information about algorithm see http://www.davekoelle.com/alphanum.html).


## How to implement

1. Add the following files

* *AlphanumComparer.h* - comparer, which use alphanum alghoritm to compare values;
* *AlphanumSortProxyModel.h* - proxy model, that used to sort data in TableView with alphanum alghoritm;
* *ColumnsSorter.h* - helper, which strore information about sorted columns;
* *MultisortTableView.h, MultisortTableView.cpp* - TableView, which used ColumnsSorter class and *AplhanumSortProxyModel* to sort data by multiple columns.

2. Implement the following methods

* *void setSortIcons( QIcon ascIcon, QIcon descIcon )* - set icons of sorting order (by default used QStyle::SP_ArrowUp and QStyle::SP_ArrowDown icons);
* *void setModifier ( Qt::KeyboardModifier modifier )* - set modifier to handling multicolumn sorting (by default used ControlModifier).

3.  Create a table model

QSqlTableModel *users = new QSqlTableModel;
users->setTable( "users" );
users->select( );

4. Create and customize widget

MultisortTableView tableView;
tableView.setModifier( Qt::ShiftModifier );
tableView.setSortingEnabled( true );
tableView.setSortIcons( QIcon(":/icons/bullet_arrow_up.png"),
                        QIcon(":/icons/bullet_arrow_down.png") );
tableView.setSelectionBehavior( QAbstractItemView::SelectRows );
tableView.setModel( users );
tableView.show();