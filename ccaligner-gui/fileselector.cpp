#include "fileselector.h"

FileSelector::FileSelector(QWidget* parent)
  : QWidget(parent)
  , ui(new Ui::FileSelector())
{
  ui->setupUi(this);
}

FileSelector::~FileSelector()
{
  delete ui;
}
