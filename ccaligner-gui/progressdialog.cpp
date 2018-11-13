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
  QString programPath = QProcessEnvironment::systemEnvironment().value(
    "CCALIGNER_PATH", "ccaligner");
  if (programPath !=
      "ccaligner") { // set working directory if custom path is used
    ccAlignerProcess->setWorkingDirectory(
      QFileInfo(programPath).absolutePath());
  }

  ccAlignerProcess->start(
    programPath, opts->assembleArguments(), QIODevice::ReadWrite);
  QObject::connect(ccAlignerProcess,
                   SIGNAL(readyReadStandardOutput()),
                   this,
                   SLOT(onProcessReadyRead()));

  //  QObject::connect(
  //    this, SIGNAL(finished(int)), ccAlignerProcess, SLOT(terminate()));
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
  ccAlignerProcess->terminate();
  delete ccAlignerProcess;
}
