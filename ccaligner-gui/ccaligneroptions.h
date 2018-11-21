#ifndef CCALIGNEROPTIONS_H
#define CCALIGNEROPTIONS_H
#include <QString>
#include <QStringList>

enum class CCAlignerMode {
    normal,
    transcribe,
    approximate
};

enum class CCAlignerAudioWindowType {
    ms,
    samples
};

class CCAlignerOptions
{
public:
  QString inputAudio;
  QString inputSubtitle;
  QString output;
  QString outputFormat;

  CCAlignerMode mode = CCAlignerMode::normal;

  // grammar
  QString generateGrammar = "yes";
  QString accousticModel = "";
  QString languageModel = "";
  QString dictionary = "";
  QString fsg = "";
  QString phoneticLanguageModel = "";
  bool quickDictionary = false;
  bool quickLanguageModel = false;

  // alignment
  bool enablePhonemes = false;
  bool useFsg = false;
  bool useBatchMode = false;
  bool useExperimentalParameters = false;
  int searchWindow = 3;
  int audioWindow = 0;
  CCAlignerAudioWindowType audioWindowType = CCAlignerAudioWindowType::ms;

  // output and logging
  QString log = "";
  QString phonemeDecoderLog = "";
  bool verbose = false;
  bool displayRecognised = true;

  CCAlignerOptions();
  QStringList assembleArguments() const;
};

#endif // CCALIGNEROPTIONS_H
