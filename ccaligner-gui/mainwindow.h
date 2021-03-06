#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "aboutdialog.h"
#include "ccaligneroptions.h"
#include "progressdialog.h"
#include "ui_mainwindow.h"
#include "ui_progressdialog.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMainWindow>
#include <QMap>
#include <QtDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
public slots:
  void browseAudioFile();
  void browseSubtitleFile();
  void browseOutputFile();
  void updateOutputExtension();
  void startAlignment();
  void openAboutDialog();
  void browseExecutablePath();
  void updateGeneratedCommand();

private:
  Ui::MainWindow *ui;
  void autodetectExecutableLocation();
  CCAlignerOptions createOptions();
  static QMap<QString, QString> formatNamesToExtensions;
  static QMap<QString, QString> formatNamesToOutputFormatEnum;
  static QMap<QString, QString> generateGrammarTextsToOptions;
};

#endif // MAINWINDOW_H
