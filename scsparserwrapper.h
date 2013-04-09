#ifndef SCSPARSERWRAPPER_H
#define SCSPARSERWRAPPER_H

#include <QObject>
#include <QTextStream>

#include "SCsParser.hpp"

enum ErrorType{
    PARSER_ERROR,
    LEXER_ERROR
};


class SCsParserError: public QObject
{
    Q_OBJECT

public:
    explicit SCsParserError(QObject *parent = 0);
    ~SCsParserError();
    SCsParserError(SCsParserNS::SCsLexer::RuntimeParserError *error, ErrorType type,QObject *parent = 0);
    SCsParserError(SCsParserNS::SCsParser::RuntimeParserError *error, ErrorType type,QObject *parent = 0);
    ErrorType type(){ return mType; }
    int line() { return mLine; }
    int positionInLine() { return  mPositionInLine; }

private:
    ErrorType mType;
    ANTLR_UINT8** mTokenNames;
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
    bool mClearErrors;

signals:
    
public slots:
    
};

#endif // SCSPARSERWRAPPER_H
