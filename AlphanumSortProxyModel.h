#ifndef ALPHANUMSORTPROXYMODEL_H
#define ALPHANUMSORTPROXYMODEL_H

#include <QSortFilterProxyModel>
#include "AlphanumComparer.h"


class AlphanumSortProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit AlphanumSortProxyModel( QObject *parent = 0 ) :
        QSortFilterProxyModel( parent ) { }

    virtual QVariant headerData ( int section,
                                  Qt::Orientation orientation,
                                  int role = Qt::DisplayRole ) const
    {
        if(orientation!=Qt::Vertical || role!=Qt::DisplayRole) {
           return QSortFilterProxyModel::headerData(section, orientation, role);
        }
        return section + 1;
    }


protected:
    virtual bool lessThan ( const QModelIndex & left,
                            const QModelIndex & right ) const
    {
        QVariant leftData  = sourceModel()->data(left),
                 rightData = sourceModel()->data(right);

        return AlphanumComparer::lessThan(leftData.toString(),
                                          rightData.toString());
    }

};

#endif // ALPHANUMSORTPROXYMODEL_H
