#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include "ccaligneroptions.h"
#include <QDialog>
#include <QProcess>

namespace Ui {
class ProgressDialog;
}

class ProgressDialog : public QDialog
{
  Q_OBJECT

public:
  explicit ProgressDialog(QWidget* parent = nullptr,
                          const CCAlignerOptions* opts = nullptr);
  ~ProgressDialog();

public slots:
  void startAlignment();

private:
  Ui::ProgressDialog* ui;
  QProcess* ccAlignerProcess;
};

#endif // PROGRESSDIALOG_H
