#include <QHeaderView>
#include <QIcon>
#include <QApplication>

#include "MultisortTableView.h"
#include "AlphanumSortProxyModel.h"


MultisortTableView::MultisortTableView ( QWidget *parent ) :
    QTableView ( parent )
{
    m_isSortingEnabled = false;
    m_proxyModel = new AlphanumSortProxyModel( this );
    m_modifier = Qt::ControlModifier;
    // Default icons
    setSortIcons( style()->standardIcon( QStyle::SP_ArrowUp ),
                  style()->standardIcon( QStyle::SP_ArrowDown ) );
    horizontalHeader()->setDefaultAlignment( Qt::AlignLeft );

    // Handler to sorting table
    connect( horizontalHeader(), SIGNAL(sectionClicked(int)),
             this,               SLOT(headerClicked(int)) );
}

// Set icons to decorate sorted table headers
void MultisortTableView::setSortIcons ( QIcon ascIcon, QIcon descIcon )
{
    m_proxyModel->setSortIcons( ascIcon, descIcon );
}

// Set key modifier to handle multicolumn sorting
void MultisortTableView::setModifier ( Qt::KeyboardModifier modifier )
{
    m_modifier = modifier;
}


// Reimplemented to self handling of sorting enable state
void MultisortTableView::setSortingEnabled( bool enable )
{
    m_isSortingEnabled = enable;
}

// Reimplemented to use AlphanumSortProxyModel
void MultisortTableView::setModel( QAbstractItemModel *model )
{
    if ( model ) {
        m_proxyModel->setSourceModel( model );
        QTableView::setModel( m_proxyModel );
    }
}

// Handler to sort table
void MultisortTableView::headerClicked ( int column )
{
    if ( m_isSortingEnabled ) {
        bool isModifierPressed = QApplication::keyboardModifiers() & m_modifier;
        m_proxyModel->sortColumn( column, isModifierPressed );
    }
}
