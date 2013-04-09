/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OSTIS.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
*/

#include "scsmultilinecommenthighlightingrule.h"

SCsMultiLineCommentHighlightingRule::SCsMultiLineCommentHighlightingRule(QRegExp start, QRegExp end, QTextCharFormat format)
    : SCsAbstractHighlightingRule(format)
{
    mStart = start;
    mEnd = end;
}

void SCsMultiLineCommentHighlightingRule::assignFormat(SCsSyntaxHighlighter *highlighter, const QString &text)
{

	int state = highlighter->curBlockState();
	 if(state>0 && state!=RuleState::MultiLineCommentRuleState)
		 return;

	 highlighter->setCurBlockState(0);

	 int startIndex = 0;
	 if (highlighter->prevBlockState() != RuleState::MultiLineCommentRuleState)
		 startIndex = mStart.indexIn(text);;// commentStartExpression.indexIn(text);

	 while (startIndex >= 0) {
		 int endIndex = mEnd.indexIn(text, startIndex);
		 int commentLength;
		 if (endIndex == -1) {
			 highlighter->setCurBlockState(RuleState::MultiLineCommentRuleState);
			 int t = highlighter->prevBlockState();
			 commentLength = text.length() - startIndex;
		 } else {
			 commentLength = endIndex - startIndex
				 + mEnd.matchedLength();
		 }
		 highlighter->setFormating(startIndex, commentLength, format());
		 startIndex = mStart.indexIn(text, startIndex + commentLength);
	 }

}
