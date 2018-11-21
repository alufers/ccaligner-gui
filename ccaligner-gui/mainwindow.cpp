#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  QWidget::connect(ui->audioFileBrowseButton, SIGNAL(clicked()), this,
                   SLOT(browseAudioFile()));
  QWidget::connect(ui->subtitleFileBrowseButton, SIGNAL(clicked()), this,
                   SLOT(browseSubtitleFile()));
  QWidget::connect(ui->outputFileBrowseButton, SIGNAL(clicked()), this,
                   SLOT(browseOutputFile()));
  QWidget::connect(ui->outputFormatComboBox,
                   SIGNAL(currentTextChanged(const QString &)), this,
                   SLOT(updateOutputExtension()));
  QWidget::connect(ui->alignButton, SIGNAL(clicked()), this,
                   SLOT(startAlignment()));
  QWidget::connect(ui->aboutButton, SIGNAL(clicked()), this,
                   SLOT(openAboutDialog()));
}

MainWindow::~MainWindow() { delete ui; }

QMap<QString, QString> MainWindow::formatNamesToExtensions = {
    {"XML", "xml"}, {"JSON", "json"}, {"SRT", "srt"}, {"Karaoke", "srt"}};

QMap<QString, QString> MainWindow::formatNamesToOutputFormatEnum = {
    {"XML", "xml"}, {"JSON", "json"}, {"SRT", "srt"}, {"Karaoke", "karaoke"}};

QMap<QString, QString> MainWindow::generateGrammarTextsToOptions = {
    {"Yes", "yes"},
    {"No", "no"},
    {"Only Corpus", "onlyCorpus"},
    {"Only Dict", "onlyDict"},
    {"Only FSG", "onlyFSG"},
    {"Only LM", "onlyLM"},
    {"Only Vocab", "onlyVocab"}};

void MainWindow::browseAudioFile() {
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

void MainWindow::browseSubtitleFile() {
  auto filePath = QFileDialog::getOpenFileName(
      this, tr("Open subtitle file"), nullptr, tr("Srt files (*.srt)"));
  if (filePath.isNull())
    return;
  ui->subtitleFileLineEdit->setText(filePath);
}

void MainWindow::browseOutputFile() {
  auto formatComboText = ui->outputFormatComboBox->currentText();
  auto suggestedBasename = QFileInfo(ui->audioFileLineEdit->text()).baseName();
  auto extension = MainWindow::formatNamesToExtensions[formatComboText];

  auto filePath = QFileDialog::getSaveFileName(
      this, tr("Select output file"), suggestedBasename + "." + extension,
      formatComboText + " files (*." + extension + ")");
  if (filePath.isNull())
    return;
  ui->outputFileLineEdit->setText(filePath);
}

void MainWindow::updateOutputExtension() {
  if (ui->outputFileLineEdit->text().isEmpty())
    return;
  QFileInfo outputFileInfo = QFileInfo(ui->outputFileLineEdit->text());
  ui->outputFileLineEdit->setText(
      outputFileInfo.absolutePath() + QDir::separator() +
      outputFileInfo.baseName() + "." +
      MainWindow::formatNamesToExtensions[ui->outputFormatComboBox
                                              ->currentText()]);
}

void MainWindow::startAlignment() {
  CCAlignerOptions opts;
  opts.output = ui->outputFileLineEdit->text();
  opts.inputAudio = ui->audioFileLineEdit->text();
  opts.inputSubtitle = ui->subtitleFileLineEdit->text();
  opts.outputFormat =
      MainWindow::formatNamesToOutputFormatEnum[ui->outputFormatComboBox
                                                    ->currentText()];
  if (ui->modeComboBox->currentText() == "Normal") {
    opts.mode = CCAlignerMode::normal;
  } else if (ui->modeComboBox->currentText() == "Transcribe") {
    opts.mode = CCAlignerMode::transcribe;
  } else if (ui->modeComboBox->currentText() == "Approximate") {
    opts.mode = CCAlignerMode::approximate;
  }
  opts.generateGrammar =
      MainWindow::generateGrammarTextsToOptions[ui->generateGrammarComboBox
                                                    ->currentText()];
  opts.accousticModel = ui->accousticModelLineEdit->text();
  opts.languageModel = ui->languageModelLineEdit->text();
  opts.dictionary = ui->dictionaryLineEdit->text();
  opts.fsg = ui->FSGLineEdit->text();
  opts.phoneticLanguageModel = ui->phoneticLanguageModelLineEdit->text();
  opts.quickDictionary = ui->quickDictionaryCheckBox->isChecked();
  opts.quickLanguageModel = ui->quickLanguageModelCheckBox->isChecked();
  opts.languageModel = ui->languageModelLineEdit->text();
  opts.enablePhonemes = ui->enablePhonemesCheckBox->isChecked();
  opts.useFsg = ui->useFSGCheckBox->isChecked();
  opts.useBatchMode = ui->useBatchModeCheckBox->isChecked();
  opts.useExperimentalParameters = ui->experimentCheckBox->isChecked();
  opts.searchWindow = ui->searchWindowSpinBox->value();
  opts.audioWindow = ui->audioWindowSpinBox->value();
  opts.audioWindowType = ui->audioWindowTypeComboBox->currentText() == "ms"
                             ? CCAlignerAudioWindowType::ms
                             : CCAlignerAudioWindowType::samples;
  opts.log = ui->logLineEdit->text();
  opts.phonemeDecoderLog = ui->phonemeDecoderLogLineEdit->text();
  opts.verbose = ui->verboseCheckBox->isChecked();
  opts.displayRecognised = ui->displayRecognisedCheckBox->isChecked();
  auto progress = new ProgressDialog(this, &opts);
  progress->exec();
  delete progress;
}

void MainWindow::openAboutDialog() {
    auto aboutDialog = new AboutDialog(this);
    aboutDialog->exec();
    delete aboutDialog;
}
