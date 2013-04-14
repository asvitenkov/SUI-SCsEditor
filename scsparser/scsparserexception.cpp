#include "scsparserexception.h"



SCsParserException::SCsParserException(SCsParserException::ExceptionPlace place) :
mLine(-1), mPositionInLine(-1), mExceptionType(-1), mExceptionPlace(place)
{

}

SCsParserException::SCsParserException(ExceptionPlace place, int line, int positionInLine, ExceptionType exType):
	 mLine(line)
	,mPositionInLine(positionInLine)
	,mExceptionType(exType)
	,mExceptionPlace(place)
{

}


SCsParserException::SCsParserException(const SCsParserException& copy)
{
	mPositionInLine = copy.mPositionInLine;
	mLine = copy.mLine;
	mExceptionPlace = copy.mExceptionPlace;
	mExceptionType = copy.mExceptionType;
}

SCsParserException & SCsParserException::operator=(const SCsParserException &copy)
{
	mPositionInLine = copy.mPositionInLine;
	mLine = copy.mLine;
	mExceptionPlace = copy.mExceptionPlace;
	mExceptionType = copy.mExceptionType;

	return *this;
}


SCsParserException::~SCsParserException()
{

}


SCsParserToken::SCsParserToken():
	mToken(UNKNOWN), mLine(-1), mPositionInLine(-1)
{
	
}


SCsParserToken::SCsParserToken(SCsParserToken::Tokens token):
	mToken(token), mLine(-1), mPositionInLine(-1)
{

}


SCsParserToken::SCsParserToken(SCsParserToken::Tokens token, QString tokenText, int line, int positionInLine):
	mToken(token), mLine(line), mPositionInLine(positionInLine)
{
	mTokenText = tokenText;
}


SCsParserToken::SCsParserToken(const SCsParserToken& copy)
{
	mTokenText = copy.mTokenText;
	mToken = copy.mToken;
	mPositionInLine = copy.mPositionInLine;
	mLine = copy.mLine;
}


SCsParserToken& SCsParserToken::operator=(const SCsParserToken& copy)
{
	mTokenText = copy.mTokenText;
	mToken = copy.mToken;
	mPositionInLine = copy.mPositionInLine;
	mLine = copy.mLine;

	return *this;
}



SCsParserToken::~SCsParserToken()
{

}