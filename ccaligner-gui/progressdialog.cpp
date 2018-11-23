#include "progressdialog.h"
#include "ui_progressdialog.h"
#include <QMetaObject>
#include <QProcessEnvironment>
#include <QtConcurrent>
#include <iostream>
#include <QDebug>

ProgressDialog::ProgressDialog(QWidget* parent, const CCAlignerOptions* opts)
  : QDialog(parent)
  , ui(new Ui::ProgressDialog)
{
  ui->setupUi(this);
  ccAlignerProcess = new QProcess();
  QString programPath = opts->executablePath;
  if (programPath !=
      "ccaligner") { // set working directory if custom path is used
    ccAlignerProcess->setWorkingDirectory(
      QFileInfo(programPath).absolutePath());
  }

  auto args = opts->assembleArguments();
  qInfo() << "Starting ccaligner with the following arguments:" << args.join(" ");
  ccAlignerProcess->start(
    programPath, args , QIODevice::ReadWrite);
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
