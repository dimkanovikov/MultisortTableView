#ifndef COLUMNSSORTER_H
#define COLUMNSSORTER_H

#include <QObject>
#include <QStyle>
#include <QIcon>
#include <QHash>

// Class for sorting columns
// Stored dictionary of sorted columns and theirs sort order "m_sortedColumns"
// and list of sorted columns to simple handling order of sorting columns
class ColumnsSorter
{
public:
    ColumnsSorter() { }

    // Set icons to decorate sorted table headers
    void setIcons( QIcon ascIcon, QIcon descIcon )
    {
        m_ascIcon  = ascIcon;
        m_descIcon = descIcon;
    }

    // Sort column
    void sortColumn ( int column, bool isModifierPressed = false )
    {
        // If key modifier to multicolumn sorting is pressed
        // and column was sorted and nedded to sort only this column,
        // i.e. before user click at this column header was sorted only
        // this column, than we simple should change sort order of column.
        // Else we should clear all sorted columns and sort current
        // by defult sort order (ascending)
        if ( !isModifierPressed ) {
            if ( m_sortedColumns.contains( column ) &&
                 m_sortedColumns.count() == 1)
                changeSortOrder( column );
            else {
                clearSortedColumns();
                addSortedColumn( column );
            }
        }
        // If key modifier to multicolumn sorting isn't pressed, than
        // if column was sorted, we change theirs sort order, or if
        // column wasn't sorted yet just sort it by defult sort order (ascending)
        else {
            if ( m_sortedColumns.contains( column ) ) {
                changeSortOrder( column );
            } else {
                addSortedColumn( column );
            }
        }
    }

    // Return column index
    int columnIndex ( int columnOrder ) const
    {
        return m_sortedColumnsOrder.value( columnOrder );
    }

    // Return column order in list of sorted columns
    int columnOrder ( int column ) const
    {
        return m_sortedColumnsOrder.indexOf( column );
    }

    // Return column sort order
    Qt::SortOrder columnSortOrder ( int column ) const
    {
        return m_sortedColumns.value( column );
    }

    // Return column icon, if column wasn't sorted return QIcon()
    QIcon columnIcon ( int column ) const
    {
        QIcon columnIcon;
        if ( m_sortedColumns.contains( column ) ) {
            if ( m_sortedColumns.value( column ) == Qt::AscendingOrder )
                columnIcon = m_ascIcon;
            else
                columnIcon = m_descIcon;
        }
        return columnIcon;
    }

    // Return count of sorted columns
    int columnsCount () const
    {
        return m_sortedColumnsOrder.count();
    }


private:
    // Dictionary of sorted columns: key - column index, value - sort order
    QHash<int, Qt::SortOrder> m_sortedColumns;
    // List of sorted columns
    QList<int> m_sortedColumnsOrder;
    // Icons do decorate sorted columns
    QIcon m_ascIcon,
          m_descIcon;


    // Add column to list of sorted columns
    // Assertions:
    // Function don't check that column is already stored
    void addSortedColumn ( int column )
    {
        m_sortedColumns.insert( column, Qt::AscendingOrder );
        m_sortedColumnsOrder.append( column );
    }

    // Change sort order of column
    // Assertions:
    // Function isn't check that column is already stored
    void changeSortOrder ( int column )
    {
        Qt::SortOrder revertOrder =
                m_sortedColumns.value( column ) != Qt::AscendingOrder ?
                    Qt::AscendingOrder :
                    Qt::DescendingOrder;

        m_sortedColumns.insert( column, revertOrder );
    }

    // Clear all stored columns
    inline void clearSortedColumns()
    {
        m_sortedColumns.clear();
        m_sortedColumnsOrder.clear();
    }
};

#endif // COLUMNSSORTER_H
