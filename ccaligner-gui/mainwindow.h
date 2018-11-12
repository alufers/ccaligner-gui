#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ccaligneroptions.h"
#include "progressdialog.h"
#include "ui_mainwindow.h"
#include "ui_progressdialog.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMainWindow>
#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
public slots:
  void browseAudioFile();
  void browseSubtitleFile();
  void browseOutputFile();
  void updateOutputExtension();
  void startAlignment();

private:
  Ui::MainWindow* ui;
  static QMap<QString, QString> formatNamesToExtensions;
  static QMap<QString, QString> formatNamesToOutputFormatEnum;
};

#endif // MAINWINDOW_H
