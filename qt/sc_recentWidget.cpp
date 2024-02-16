#include "sc_recentWidget.hpp"

#include <QStandardItemModel>
#include <QStringList>
#include <QtWidgets>
#include <sc_importWidget.hpp>

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
  connect( recentView, &QTableView::clicked, this, &RecentCharactersWidget::recentToonClicked );
  m_model             = new QStandardItemModel( this );
  QStringList headers = { "Region", "Realm", "Character" };
  m_model->setHorizontalHeaderLabels( headers );

  // QList<QStandardItem*> nextLine;
  // nextLine.append(new QStandardItem( "US" ) );
  // nextLine.append(new QStandardItem( "Kargath" ) );
  // nextLine.append(new QStandardItem( "Zuggington" ) );
  // model->appendRow(nextLine );

  QSettings settings;
  QList<QVariant> recentList = settings.value( "user_data/importHistory" ).toList();

  for ( int i = 0; i < recentList.count(); i++ )
  {
    QList<QVariant> recentLine = recentList[ i ].toList();

    QList<QStandardItem*> nextLine;
    for ( int j = 0; j < recentLine.count(); j++ )
    {
      nextLine.append( new QStandardItem( recentLine[ j ].toString() ) );
    }
    // nextLine.append(new QStandardItem( "US" ) );
    // nextLine.append(new QStandardItem( "Kargath" ) );
    // nextLine.append(new QStandardItem( "Zuggington" ) );
    m_model->appendRow( nextLine );
  }

  recentView->setModel( m_model );
  recentView->horizontalHeader()->setSectionResizeMode( 1, QHeaderView::Stretch );

  recentView->resizeColumnsToContents();

  QVBoxLayout* layout = new QVBoxLayout;
  layout->addWidget( recentView );

  historyBox->setLayout( layout );
  return historyBox;
}

void RecentCharactersWidget::recentToonClicked( const QModelIndex& index )
{
  QStandardItem* item = m_model->itemFromIndex( index );
  // m_model->row
  // QStandardItem* item = m_model->itemFromIndex( index );
  // m_model->
  QList<QStandardItem*> row = m_model->takeRow( index.row() );

  emit rowClickedTriggeredOut(
      QString( m_model->item( index.row(), 0 )->text() ), QString( m_model->item( index.row(), 1 )->text() ),
      QString( m_model->item( index.row(), 2 )->text() ), QString( m_model->item( index.row(), 3 )->text() ) );
}

void RecentCharactersWidget::addImportedToon( const QString& region, const QString& realm, const QString& character,
                                              const QString& specialization )
{
  QList<QStandardItem*> nextLine;
  nextLine.append( new QStandardItem( region ) );
  nextLine.append( new QStandardItem( realm ) );
  nextLine.append( new QStandardItem( character ) );
  nextLine.append( new QStandardItem( specialization ) );
  m_model->appendRow( nextLine );
}
