#pragma once

#include "sc_recentWidget.hpp"

#include <QtWidgets/QtWidgets>

class RecentCharactersWidget : public QWidget
{
  Q_OBJECT

  QGroupBox* m_recentList;
  QGridLayout* m_layout;

public:
  RecentCharactersWidget( QWidget* parent = nullptr );

private:
  QGroupBox* buildRecentList();
};
