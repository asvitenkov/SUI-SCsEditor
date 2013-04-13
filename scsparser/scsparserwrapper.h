#ifndef SCSPARSERWRAPPER_H
#define SCSPARSERWRAPPER_H

#include <QObject>
#include <QTextStream>

#include "SCsParser.hpp"

enum ErrorType{
    PARSER_ERROR,
    LEXER_ERROR
};


class SCsParserError
{

public:

	typedef ANTLR_INT32 ExceptionType;
	SCsParserError();
    virtual ~SCsParserError();
    SCsParserError(SCsParserNS::SCsLexer::RuntimeParserError *error, ErrorType type);
    SCsParserError(SCsParserNS::SCsParser::RuntimeParserError *error, ErrorType type);
	SCsParserError(const SCsParserError& copy);
	SCsParserError &operator=(const SCsParserError &copy);
    ErrorType type(){ return mType; }
    int line() { return mLine; }
    int positionInLine() { return  mPositionInLine; }
	ExceptionType getExceptionType() { return mExceptionType; }

private:
    ErrorType mType;
	ExceptionType mExceptionType;
    int mLine;
    int mPositionInLine;
};


class SCsParserWrapper : public QObject
{
    Q_OBJECT
public:
    explicit SCsParserWrapper(QObject *parent = 0);
    ~SCsParserWrapper();
    SCsParserWrapper(const QString &data, QObject *parent = 0);
    void setData(const QString &data);
    bool parseData();
    QList<SCsParserError*> getErrors();




private:
    void clearErrors();

    QString mParseData;
    QList<SCsParserError*> mErrorList;

signals:
    
public slots:
    
};

#endif // SCSPARSERWRAPPER_H
