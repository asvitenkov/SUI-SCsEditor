#include "scsparserwrapper.h"

#include <QFile>
#include <QTextCodec>
#include <antlr3.hpp>

#include "SCsParser.hpp"

SCsParser::SCsParser(QObject *parent) :
    QObject(parent)
{

}



QVector<int> SCsParser::getErrorLines(const QString &text)
{

	std::string strData = text.toStdString();
	SCsParserNS::SCsLexer::InputStreamType input((ANTLR_UINT8*)strData.c_str(), ANTLR_ENC_UTF8, strData.length(), (ANTLR_UINT8*)"SCS");
	SCsParserNS::SCsLexer lxr(&input);

	SCsParserNS::SCsParser::TokenStreamType tstream(ANTLR_SIZE_HINT, lxr.get_tokSource() );
	SCsParserNS::SCsParser psr(&tstream);
	psr.syntax();

	std::list<SCsParserException*> parserErrors = psr.getParserErrors();
	std::list<SCsParserException*> lexerErrors = lxr.getLexerError();


	std::list<SCsParserException*>::iterator itParser;
	std::list<SCsParserException*>::iterator itLexer;


	QVector<int> errorLines;

	for( itLexer=lexerErrors.begin(); itLexer!=lexerErrors.end(); ++itLexer )
		errorLines.push_back((*itLexer)->line());

	for( itParser=parserErrors.begin(); itParser!=parserErrors.end(); ++itParser)
		errorLines.push_back((*itParser)->line());

	return errorLines;
}



SCsParser::~SCsParser()
{

}



QVector<SCsParserToken> SCsParser::getTokens(const QString &text)
{

	std::string strData = text.toStdString();
	SCsParserNS::SCsLexer::InputStreamType input((ANTLR_UINT8*)strData.c_str(), ANTLR_ENC_UTF8, strData.length(), (ANTLR_UINT8*)"SCS");
	SCsParserNS::SCsLexer lxr(&input);

	SCsParserNS::SCsParser::TokenStreamType tstream(ANTLR_SIZE_HINT, lxr.get_tokSource() );


	SCsParserNS::SCsParser::TokenStreamType::TokensMapType *map = tstream.getTokens();
	SCsParserNS::SCsParser::TokenStreamType::TokensMapType::iterator it;
	QVector<SCsParserToken> token;

	for(it=map->begin(); it!=map->end(); ++it)
	{
		token.append( SCsParserToken((SCsParserToken::Tokens)it->second.get_type(), QString::fromStdString(it->second.getText()),it->second.get_line(),it->second.get_charPositionInLine()));
	}

	return token;
}


QSet<QString> SCsParser::getIdentifier(const QString &text)
{
	QSet<QString> idtf;

	QVector<SCsParserToken> token = getTokens(text);
	QVector<SCsParserToken>::iterator it = token.begin();
	while (it!=token.end())
	{
		if(it->tokenType() == SCsParserToken::NAME)
		{
			idtf.insert(it->tokenText());
		}
		++it;
	}

	return idtf;
}