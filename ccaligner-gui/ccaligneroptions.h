#ifndef CCALIGNEROPTIONS_H
#define CCALIGNEROPTIONS_H
#include <QString>
#include <QStringList>

class CCAlignerOptions
{
public:
  QString inputAudio;
  QString inputSubtitle;
  QString output;
  QString outputFormat;

  CCAlignerOptions();
  QStringList assembleArguments() const;
};

#endif // CCALIGNEROPTIONS_H
