#pragma once

#include "sc_recentWidget.hpp"

#include <QtWidgets/QtWidgets>
#include <QSettings>


class RecentCharactersWidget : public QWidget
{
  Q_OBJECT

  QGroupBox* m_recentList;
  QGridLayout* m_layout;
  QSettings m_settings;
  QStandardItemModel* m_model;


public:
  RecentCharactersWidget( QWidget* parent = nullptr );
public slots:
  void addImportedToon( const QString&, const QString&, const QString&, const QString& );

signals:
  void rowClickedTriggeredOut( const QString&, const QString&, const QString&, const QString& );

private:
  QGroupBox* buildRecentList();
  void recentToonClicked(const QModelIndex &);
};
