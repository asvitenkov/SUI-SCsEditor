#ifndef SCSMULTILINECONTENTHIGHLIGHTINGRULE_H
#define SCSMULTILINECONTENTHIGHLIGHTINGRULE_H

#include "scsabstracthighlightingrule.h"

class SCsMultiLineContentHighlightingRule : public SCsAbstractHighlightingRule
{
public:
    SCsMultiLineContentHighlightingRule(QRegExp start, QRegExp end, QTextCharFormat format);
    virtual void assignFormat(SCsSyntaxHighlighter *highlighter, const QString &text);

private:
    QRegExp mStart;
    QRegExp mEnd;
};

#endif // SCSMULTILINECONTENTHIGHLIGHTINGRULE_H
