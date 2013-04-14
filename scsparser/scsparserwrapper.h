#ifndef SCSPARSERWRAPPER_H
#define SCSPARSERWRAPPER_H


#include <QObject>
#include <QVector>
#include <QSet>

#include "scsparserexception.h"


class SCsParser : public QObject
{
    Q_OBJECT
public:
    explicit SCsParser(QObject *parent = 0);
    ~SCsParser();
	QVector<int> getErrorLines(const QString &text);
	QVector<SCsParserToken> getTokens(const QString &text);
	QSet<QString> getIdentifier(const QString &text);

protected:


private:
  
    QString mParseData;

signals:
    
public slots:
    
};

#endif // SCSPARSERWRAPPER_H
