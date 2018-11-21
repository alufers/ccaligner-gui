#include "ccaligneroptions.h"

CCAlignerOptions::CCAlignerOptions() {}

QStringList CCAlignerOptions::assembleArguments() const {
  QStringList args;

  auto stringParam = [&](QString paramFlag, QString value) {
    if (!value.isEmpty()) {
      args.push_back(paramFlag);
      args.push_back(value);
    }
  };

  auto boolParam = [&](QString paramFlag, bool value) {
    args.push_back(paramFlag);
    args.push_back(value ? "yes" : "no");
  };

  stringParam("-wav", this->inputAudio);
  stringParam("-srt", this->inputSubtitle);
  stringParam("-out", this->output);
  stringParam("-oFormat", this->outputFormat);
  stringParam("-model", this->accousticModel);
  stringParam("-lm", this->languageModel);
  stringParam("-dict", this->dictionary);
  stringParam("-fsg", this->fsg);
  stringParam("-phoneLM", this->phoneticLanguageModel);
  stringParam("-log", this->log);
  stringParam("-phoneLog", this->phonemeDecoderLog);
  stringParam("--generate-grammar", this->generateGrammar);

  boolParam("--enable-phonemes", this->enablePhonemes);
  boolParam("--use-fsg", this->useFsg);
  boolParam("-useBatchMode", this->useBatchMode);
  boolParam("-experiment", this->useExperimentalParameters);
  boolParam("--quick-dict", this->quickDictionary);
  boolParam("--quick-lm", this->quickLanguageModel);
  boolParam("-verbose", this->verbose);
  boolParam("--display-recognised", this->displayRecognised);

  if(this->mode == CCAlignerMode::approximate) {
      args.push_back("-aprox");
      args.push_back("yes");
  } else if(this->mode == CCAlignerMode::transcribe) {
      args.push_back("-transcribe");
      args.push_back("yes");
  }

  args += this->extraOptions;

  return args;
}
