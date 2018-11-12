#include "progressdialog.h"
#include "ui_progressdialog.h"
#include <QMetaObject>
#include <QProcessEnvironment>
#include <QtConcurrent>
#include <iostream>

ProgressDialog::ProgressDialog(QWidget* parent, const CCAlignerOptions* opts)
  : QDialog(parent)
  , ui(new Ui::ProgressDialog)
{
  ui->setupUi(this);
  ccAlignerProcess = new QProcess();
  ccAlignerProcess->start(QProcessEnvironment::systemEnvironment().value(
                            "CCALIGNER_PATH", "ccaligner"),
                          opts->assembleArguments(),
                          QIODevice::ReadWrite);
  QObject::connect(ccAlignerProcess,
                   SIGNAL(readyReadStandardOutput()),
                   this,
                   SLOT(onProcessReadyRead()));
}

void
ProgressDialog::onProcessReadyRead()
{
  // auto data = ccAlignerProcess->readLine(10000);
  while (ccAlignerProcess->canReadLine()) {
    ui->outputText->moveCursor(QTextCursor::End);
    ui->outputText->appendPlainText(ccAlignerProcess->readLine().trimmed());
    ui->outputText->moveCursor(QTextCursor::End);
  }
}

ProgressDialog::~ProgressDialog()
{
  delete ui;
  ccAlignerProcess->kill();
  delete ccAlignerProcess;
}
