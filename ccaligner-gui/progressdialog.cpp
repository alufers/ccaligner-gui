#include "progressdialog.h"
#include "ui_progressdialog.h"
#include <QMetaObject>
#include <QProcessEnvironment>
#include <QtConcurrent>
#include <iostream>

ProgressDialog::ProgressDialog(QWidget* parent, const CCAlignerOptions* opts)
  : QDialog(parent)
  , ui(new Ui::ProgressDialog)
  , ccAlignerProcess()
{
  ui->setupUi(this);
  ccAlignerProcess->start(
    QProcessEnvironment::systemEnvironment().value(
      "CCALIGNER_PATH", "../../CCAligner/install/ccaligner"),
    opts->assembleArguments(),
    QIODevice::ReadWrite);
  // QObject::connect(ccAlignerProcess, SIGNAL())
}

void
ProgressDialog::startAlignment()
{}

ProgressDialog::~ProgressDialog()
{
  delete ui;
}
