#include "sc_recentWidget.hpp"

#include <QStandardItemModel>
#include <QStringList>
#include <QtWidgets>

RecentCharactersWidget::RecentCharactersWidget( QWidget* parent )
  : QWidget( parent ), m_layout( new QGridLayout( this ) ), m_recentList( buildRecentList() )
{
  auto basePos = parent->geometry();
  move( basePos.center().x(), basePos.center().y() + 50 );

  setLayout( m_layout );
  m_layout->addWidget( m_recentList );
}

QGroupBox* RecentCharactersWidget::buildRecentList()
{
  QGroupBox* historyBox = new QGroupBox( tr( "Recent" ) );

  QTableView* recentView = new QTableView;
  recentView->setEditTriggers( QAbstractItemView::NoEditTriggers );
  recentView->setSortingEnabled( true );
  recentView->setSelectionBehavior( QAbstractItemView::SelectRows );
  recentView->setSelectionMode( QAbstractItemView::SingleSelection );
  recentView->setShowGrid( false );
  recentView->verticalHeader()->hide();
  recentView->setAlternatingRowColors( true );
  QStandardItemModel* model = new QStandardItemModel( 4, 3, this );
  QStringList headers       = { "Region", "Realm", "Character", "Import" };
  model->setHorizontalHeaderLabels( headers );
  recentView->setModel( model );
  recentView->horizontalHeader()->setSectionResizeMode( 1, QHeaderView::Stretch );

  recentView->resizeColumnsToContents();


  QVBoxLayout* layout = new QVBoxLayout;
  layout->addWidget( recentView );

  historyBox->setLayout( layout );
  return historyBox;
}
