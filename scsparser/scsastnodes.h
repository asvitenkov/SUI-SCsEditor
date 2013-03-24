#ifndef SCSASTNODES_H
#define SCSASTNODES_H

#define NodeType(type)  SCsAstNodeType getType() { return type; }

#include <QList>
#include <QString>


class SCsASTNode;
class SCsRootNode;
class SCsSentenceNode;
class SCsSentenceLvl1Node;
class SCsSentenceLv234561Node;
class SCsSimpleIdentifierNode;
class SCsNameNode;
class SCsUrlNode;
//class ;
//class ;
//class ;
//class ;


enum SCsAstNodeType{
    ROOT
    ,SENTENCE
    ,SENTENCE_LVL1
    ,SENTENCE_LVL23456
    ,SIMPLE_IDENTIFIER
    ,NAME
    ,URL
};

typedef SCsAstNodeType NodeType;

class SCsASTNode
{
public:
    virtual NodeType getType() = 0;
private:
protected:

};



class SCsRootNode: public SCsASTNode
{
public:
    NodeType(ROOT);
private:
    QList<SCsSentenceNode*> mSentenceList;
};

class SCsSentenceNode: public SCsASTNode
{
public:
    NodeType(SENTENCE);
private:
    QList<SCsSentenceLvl1Node*> mSentenceLvl1List;
    QList<SCsSentenceLv234561Node*> mSentenceLvl23456List;
    QList<bool> mSentenceSequenceList;
};

class SCsSentenceLvl1Node: public SCsASTNode
{
public:
    NodeType(SENTENCE_LVL1);
private:
    SCsSimpleIdentifierNode *mFirstIdtf;
    SCsSimpleIdentifierNode *mSecondIdtf;
    SCsSimpleIdentifierNode *mThirdIdtf;
};

class SCsSentenceLv234561Node: public SCsASTNode
{
public:
    NodeType(SENTENCE_LVL23456);
};

class SCsSimpleIdentifierNode: public SCsASTNode
{
public:
    NodeType(SIMPLE_IDENTIFIER);
private:
    SCsNameNode *mName;
    SCsUrlNode *mUrl;
};

class SCsNameNode: public SCsASTNode
{
public:
    NodeType(NAME);
private:
    QString mNameStr;
};

class SCsUrlNode: public SCsASTNode
{
public:
    NodeType(URL);
private:
    QString mUrlStr;
};


#endif // SCSASTNODES_H
