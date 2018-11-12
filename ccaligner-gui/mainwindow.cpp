#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  QWidget::connect(ui->audioFileBrowseButton,
                   SIGNAL(clicked()),
                   this,
                   SLOT(browseAudioFile()));
  QWidget::connect(ui->subtitleFileBrowseButton,
                   SIGNAL(clicked()),
                   this,
                   SLOT(browseSubtitleFile()));
  QWidget::connect(ui->outputFileBrowseButton,
                   SIGNAL(clicked()),
                   this,
                   SLOT(browseOutputFile()));
  QWidget::connect(ui->outputFormatComboBox,
                   SIGNAL(currentTextChanged(const QString&)),
                   this,
                   SLOT(updateOutputExtension()));
  QWidget::connect(
    ui->alignButton, SIGNAL(clicked()), this, SLOT(startAlignment()));
}

MainWindow::~MainWindow()
{
  delete ui;
}

QMap<QString, QString> MainWindow::formatNamesToExtensions = {
  { "XML", "xml" },
  { "JSON", "json" },
  { "SRT", "srt" },
  { "Karaoke", "srt" }
};

QMap<QString, QString> MainWindow::formatNamesToOutputFormatEnum = {
  { "XML", "xml" },
  { "JSON", "json" },
  { "SRT", "srt" },
  { "Karaoke", "karaoke" }
};

void
MainWindow::browseAudioFile()
{
  auto filePath = QFileDialog::getOpenFileName(
    this, tr("Open audio file"), nullptr, tr("Wav files (*.wav)"));
  if (filePath.isNull())
    return;
  ui->audioFileLineEdit->setText(filePath);
  QFileInfo audioFileinfo = QFileInfo(filePath);

  // check if a subtitle file with the same name exists in the directory
  QString matchingSubtitleFile = audioFileinfo.absolutePath() +
                                 QDir::separator() + audioFileinfo.baseName() +
                                 ".srt";
  if (QFileInfo::exists(matchingSubtitleFile)) {
    ui->subtitleFileLineEdit->setText(matchingSubtitleFile);
  }

  // suggest an output filename and path
  auto extension = MainWindow::formatNamesToExtensions[ui->outputFormatComboBox
                                                         ->currentText()];
  ui->outputFileLineEdit->setText(audioFileinfo.absolutePath() +
                                  QDir::separator() + audioFileinfo.baseName() +
                                  "." + extension);
}

void
MainWindow::browseSubtitleFile()
{
  auto filePath = QFileDialog::getOpenFileName(
    this, tr("Open subtitle file"), nullptr, tr("Srt files (*.srt)"));
  if (filePath.isNull())
    return;
  ui->subtitleFileLineEdit->setText(filePath);
}

void
MainWindow::browseOutputFile()
{
  auto formatComboText = ui->outputFormatComboBox->currentText();
  auto suggestedBasename = QFileInfo(ui->audioFileLineEdit->text()).baseName();
  auto extension = MainWindow::formatNamesToExtensions[formatComboText];

  auto filePath = QFileDialog::getSaveFileName(
    this,
    tr("Select output file"),
    suggestedBasename + "." + extension,
    formatComboText + " files (*." + extension + ")");
  if (filePath.isNull())
    return;
  ui->outputFileLineEdit->setText(filePath);
}

void
MainWindow::updateOutputExtension()
{
  if (ui->outputFileLineEdit->text().isEmpty())
    return;
  QFileInfo outputFileInfo = QFileInfo(ui->outputFileLineEdit->text());
  ui->outputFileLineEdit->setText(
    outputFileInfo.absolutePath() + QDir::separator() +
    outputFileInfo.baseName() + "." +
    MainWindow::formatNamesToExtensions[ui->outputFormatComboBox
                                          ->currentText()]);
}

void
MainWindow::startAlignment()
{
  CCAlignerOptions opts;
  opts.output = ui->outputFileLineEdit->text();
  opts.inputAudio = ui->audioFileLineEdit->text();
  opts.inputSubtitle = ui->subtitleFileLineEdit->text();
  opts.outputFormat =
    MainWindow::formatNamesToOutputFormatEnum[ui->outputFormatComboBox
                                                ->currentText()];
  auto progress = new ProgressDialog(this, &opts);
  progress->show();
}
