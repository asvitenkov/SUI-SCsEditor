#ifndef SCSPARSEREXCEPTION_H
#define SCSPARSEREXCEPTION_H


//#include <antlr3defs.hpp>

//class QString;

#include <QString>

class SCsParserException
{
public:

	enum ExceptionPlace{
		PARSER,
		LEXER
	};

	typedef int ExceptionType;
    SCsParserException(SCsParserException::ExceptionPlace place);
	SCsParserException(ExceptionPlace place, int line, int positionInLine, ExceptionType exType);
	SCsParserException(const SCsParserException& copy);
	SCsParserException &operator=(const SCsParserException &copy);

	virtual ~SCsParserException();

	ExceptionPlace type(){ return mExceptionPlace; }
	int line() { return mLine; }
	int positionInLine() { return  mPositionInLine; }
	ExceptionType getExceptionType() { return mExceptionType; }

private:
	ExceptionPlace mExceptionPlace;
	ExceptionType mExceptionType;
	int mLine;
	int mPositionInLine;

};






class SCsParserToken
{
public:


	//copy from SCcLexer.hpp
	enum Tokens 
	{
		  EOF_TOKEN = -1
		, UNKNOWN = 2
		, ALIASNONAME = 4 
		, ATTRSEP = 5 
		, COMMENT = 6 
		, CONNECTORS = 7 
		, CONTENT = 8 
		, ELEMTYPE = 9 
		, LPAR = 10 
		, LPAR_INT = 11 
		, LPAR_OSET = 12 
		, LPAR_SET = 13 
		, LPAR_TRF = 14 
		, NAME = 15 
		, OBJSEP = 16 
		, RPAR = 17 
		, RPAR_INT = 18 
		, RPAR_OSET = 19 
		, RPAR_SET = 20 
		, RPAR_TRF = 21 
		, SENTSEP = 22 
		, SYNSEP = 23 
		, TRIPLESEP = 24 
		, URL = 25 
		, WS = 26 
	};
	SCsParserToken();
	SCsParserToken(SCsParserToken::Tokens token);
	SCsParserToken(SCsParserToken::Tokens token, QString tokenText, int line, int positionInLine);
	SCsParserToken(const SCsParserToken& copy);
	SCsParserToken& operator=(const SCsParserToken& copy);
	virtual ~SCsParserToken();

	inline SCsParserToken::Tokens tokenType(){ return mToken; }
	inline QString tokenText(){ return mTokenText; }
	inline int line(){ return mLine; }
	inline int positionInLine(){ return mPositionInLine; }

private:
	QString mTokenText;
	int mLine;
	int mPositionInLine;
	SCsParserToken::Tokens mToken;
};



#endif // SCSPARSEREXCEPTION_H
