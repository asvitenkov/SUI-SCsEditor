#include "scsparserwrapper.h"

#include <QFile>
#include <QDebug>
#include <QTextCodec>
#include <antlr3.hpp>

SCsParserError::SCsParserError(QObject *parent) :
    QObject(parent)
{

}

SCsParserError::~SCsParserError()
{

}


SCsParserError::SCsParserError(SCsParserNS::SCsLexer::RuntimeParserError *error, ErrorType type, QObject *parent) :
    QObject(parent), mType(type)
{
    mLine = error->mException->get_line();
    mPositionInLine = error->mException->get_charPositionInLine();
	mExceptionType =  error->mException->getType();

}

SCsParserError::SCsParserError(SCsParserNS::SCsParser::RuntimeParserError *error, ErrorType type, QObject *parent) :
    QObject(parent), mType(type)
{
    mLine = error->mException->get_line();
    mPositionInLine = error->mException->get_charPositionInLine();
	mExceptionType =  error->mException->getType();
}


SCsParserError::SCsParserError(SCsParserError* copy)
{
	mExceptionType = copy->mExceptionType;
	mLine = copy->mLine;
	mPositionInLine = copy->mPositionInLine;
	mType = copy->type();
}

SCsParserWrapper::SCsParserWrapper(QObject *parent) :
    QObject(parent)
{

}

SCsParserWrapper::SCsParserWrapper(const QString &data, QObject *parent) :
    QObject(parent)
{
    mParseData = data;
}


void SCsParserWrapper::setData(const QString &data)
{
	mParseData = data.toUtf8();
	//data.toLocal8Bit();;
}

bool SCsParserWrapper::parseData()
{
    QFile file("tmpParserFile",this);
    file.open(QIODevice::WriteOnly);
	QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
	QByteArray data;
	if(codec)
		data = codec->fromUnicode(codec->fromUnicode(mParseData));
	else 
		data = mParseData.toLocal8Bit();
	file.write(data);
    file.close();

    SCsParserNS::SCsLexer::InputStreamType input((ANTLR_UINT8*)"tmpParserFile", ANTLR_ENC_UTF8);
    SCsParserNS::SCsLexer lxr(&input);

    SCsParserNS::SCsParser::TokenStreamType tstream(ANTLR_SIZE_HINT, lxr.get_tokSource() );
    SCsParserNS::SCsParser psr(&tstream);

	//SCsParserNS::SCsParser::TokenStreamType::TokensMapType *map = tstream.getTokens();

    psr.syntax();

	file.open(QIODevice::WriteOnly);
    file.remove();
	file.close();
	

    std::list<SCsParserNS::SCsParser::RuntimeParserError*> parserErrors = psr.getParserErrors();
    std::list<SCsParserNS::SCsLexer::RuntimeParserError*> lexerErrors = lxr.getLexerError();


    std::list<SCsParserNS::SCsParser::RuntimeParserError*>::iterator itParser;
    std::list<SCsParserNS::SCsLexer::RuntimeParserError*>::iterator itLexer;

    clearErrors();

    for( itParser=parserErrors.begin(); itParser!=parserErrors.end(); ++itParser)
        mErrorList.push_back( new SCsParserError( *itParser, PARSER_ERROR ));

    for( itLexer=lexerErrors.begin(); itLexer!=lexerErrors.end(); ++itLexer )
        mErrorList.push_back( new SCsParserError(*itLexer, LEXER_ERROR ) );




    return (mErrorList.empty());
}



void SCsParserWrapper::clearErrors()
{
	qDeleteAll(mErrorList.begin(),mErrorList.end());
	mErrorList.clear();
}


QList<SCsParserError*> SCsParserWrapper::getErrors()
{
	QList<SCsParserError*> lst;
	QList<SCsParserError*>::iterator it = mErrorList.begin();
	while ( it!=mErrorList.end() )
	{
		lst.append(new SCsParserError(*it));
		++it;
	}
    return lst;
}



SCsParserWrapper::~SCsParserWrapper()
{
    clearErrors();
}

