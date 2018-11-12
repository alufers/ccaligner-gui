#include "ccaligneroptions.h"

CCAlignerOptions::CCAlignerOptions() {}

QStringList
CCAlignerOptions::assembleArguments() const
{
  QStringList args;
  args.push_back("-wav");
  args.push_back(this->inputAudio);
  args.push_back("-srt");
  args.push_back(this->inputSubtitle);
  args.push_back("-out");
  args.push_back(this->output);
  args.push_back("-oFormat");
  args.push_back(this->outputFormat);
  return args;
}
