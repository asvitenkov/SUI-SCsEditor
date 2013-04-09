#include "scsmultilinecontenthighlightingrule.h"

SCsMultiLineContentHighlightingRule::SCsMultiLineContentHighlightingRule(QRegExp start, QRegExp end, QTextCharFormat format)
    : SCsAbstractHighlightingRule(format)
{
    mStart = start;
    mEnd = end;
}



void SCsMultiLineContentHighlightingRule::assignFormat(SCsSyntaxHighlighter *highlighter, const QString &text)
{
	int state = highlighter->curBlockState();
    if(state>0 && state!=RuleState::ContentRuleState)
		return;
	highlighter->setCurBlockState(0);
	

    int startIndex = 0;
    if (highlighter->prevBlockState() != RuleState::ContentRuleState)
        startIndex = text.indexOf(mStart);

    while (startIndex >= 0)
    {
       int endIndex = text.indexOf(mEnd, startIndex);
       int contentLength;
       if (endIndex == -1)
       {
           highlighter->setCurBlockState(RuleState::ContentRuleState);
           contentLength = text.length() - startIndex;
       }
       else
       {
           contentLength = endIndex - startIndex
                           +mEnd.matchedLength();
       }

       highlighter->setFormating(startIndex, contentLength, format());
       startIndex = text.indexOf(mStart,
                                 startIndex + contentLength);
    }
}
