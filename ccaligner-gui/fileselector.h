#ifndef FILESELECTOR_H
#define FILESELECTOR_H

#include "ui_fileselector.h"
#include <QWidget>

class FileSelector : public QWidget
{
  Q_OBJECT
public:
  explicit FileSelector(QWidget* parent = nullptr);
  ~FileSelector();

signals:

public slots:

protected:
  Ui::FileSelector* ui;
};

#endif // FILESELECTOR_H
