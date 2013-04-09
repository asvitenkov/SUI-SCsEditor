#include "scsparserwrapper.h"

#include <QFile>
#include <QDebug>

SCsParserError::SCsParserError(QObject *parent) :
    QObject(parent), mTokenNames(NULL)
{

}

SCsParserError::~SCsParserError()
{

}


SCsParserError::SCsParserError(SCsParserNS::SCsLexer::RuntimeParserError *error, ErrorType type, QObject *parent) :
    QObject(parent), mType(type),mTokenNames(error->mToken)
{
    mLine = error->mException->get_line();
    mPositionInLine = error->mException->get_charPositionInLine();

}

SCsParserError::SCsParserError(SCsParserNS::SCsParser::RuntimeParserError *error, ErrorType type, QObject *parent) :
    QObject(parent), mType(type), mTokenNames(error->mToken)
{
    mLine = error->mException->get_line();
    mPositionInLine = error->mException->get_charPositionInLine();
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
    mParseData = data;
}

bool SCsParserWrapper::parseData()
{
    QFile file("tmpParserFile",this);
    file.open(QIODevice::WriteOnly);
    file.write(mParseData.toStdString().c_str());
    file.close();

    SCsParserNS::SCsLexer::InputStreamType input((ANTLR_UINT8*)"tmpParserFile", ANTLR_ENC_8BIT);
    SCsParserNS::SCsLexer lxr(&input);
    SCsParserNS::SCsParser::TokenStreamType tstream(ANTLR_SIZE_HINT, lxr.get_tokSource() );
    SCsParserNS::SCsParser psr(&tstream);
    psr.syntax();

    file.remove();

    std::list<SCsParserNS::SCsParser::RuntimeParserError*> parserErrors = psr.getParserErrors();
    std::list<SCsParserNS::SCsLexer::RuntimeParserError*> lexerErrors = lxr.getLexerError();


    std::list<SCsParserNS::SCsParser::RuntimeParserError*>::iterator itParser;
    std::list<SCsParserNS::SCsLexer::RuntimeParserError*>::iterator itLexer;

    clearErrors();

    for( itParser=parserErrors.begin(); itParser!=parserErrors.end(); ++itParser)
        mErrorList.push_back( new SCsParserError( *itParser, PARSER_ERROR ));

    for( itLexer=lexerErrors.begin(); itLexer!=lexerErrors.end(); ++itLexer )
        mErrorList.push_back( new SCsParserError(*itLexer, LEXER_ERROR ) );


    mClearErrors = true;

    return (mErrorList.empty());

}



void SCsParserWrapper::clearErrors()
{
    if(mClearErrors)
    {
        mClearErrors = false;
        QList<SCsParserError*>::Iterator it;
        for( it=mErrorList.begin(); it!=mErrorList.end(); ++it )
            delete *it;

        mErrorList.clear();
    }
}


QList<SCsParserError*> SCsParserWrapper::getErrors()
{
    mClearErrors = false;
    return mErrorList;
}



SCsParserWrapper::~SCsParserWrapper()
{
    clearErrors();
}

