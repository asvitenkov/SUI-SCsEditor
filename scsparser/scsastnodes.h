#ifndef ASTNODES_H
#define ASTNODES_H

#define NodeType(NodeType)  ASTNodeType type() { return NodeType; }

#include <QList>
#include <QString>

namespace SCsAST{




class AST;
class RootAST;
class SentenceAST;
class SentenceLvl1AST;
class SentenceLv234561AST;
class SimpleIdentifierAST;
class IdentifierAST;
class AnyIdentifierAST;
class TripleAST;
class SetIdentifierAST;
class OSetIdentifierAST;
class AliasAST;
class AttributesListAST;
class IdentifierWithInternalAST;
class InternalAST;
class InternalSentenceListAST;
class InternalSentenceAST;
class ObjectListAST;
class SimpleIdentifierWAttributeSeparatorAST;

//class AST;
//class AST;
//class AST;
//class AST;
//class AST;



enum _ASTNodeType{
    ROOT                    = 1
    ,SENTENCE
    ,SENTENCE_LVL1
    ,SENTENCE_LVL23456
    ,SIMPLE_IDENTIFIER
    ,IDENTIFIER
    ,ANY_IDENTIFIER
    ,TRIPLE
    ,SET_IDENTIFIER
    ,OSET_IDENTIFIER
    ,ALIAS
    ,ATRIBUTES_LIST
    ,IDTF_WITH_INT
    ,INTERNAL
    ,INTERNAL_SENTENCE_LIST
    ,INTERNAL_SENTENCE
    ,OBJECT_LIST
    ,SIMPLE_IDENTIFIER_W_ATTRIBUTE_SEPARATOR
};

typedef _ASTNodeType ASTNodeType;

class AST
{
public:
    virtual ASTNodeType type() = 0;
private:
protected:

};



class RootAST: public AST
{
public:
    RootAST();
    virtual ~RootAST();
    explicit RootAST(SentenceAST *sentence);

    ASTNodeType type() { return ROOT; }

    void addSentence(SentenceAST *sentence);
    RootAST* operator <<(SentenceAST *sentence);
private:
    QList<SentenceAST*> mSentenceLst;
};

class SentenceAST: public AST
{
public:
    explicit SentenceAST(SentenceLvl1AST *sentence);
    explicit SentenceAST(SentenceLv234561AST *sentence);
    virtual ~SentenceAST();

    NodeType(SENTENCE)
private:
    SentenceLvl1AST* mSentenceLvl1;
    SentenceLv234561AST* mSentenceLvl23456;

};

class SentenceLvl1AST: public AST
{
public:
    SentenceLvl1AST();
    SentenceLvl1AST(SimpleIdentifierAST *firstIdtf, SimpleIdentifierAST *secondIdetf, SimpleIdentifierAST *thirdIdtf);
    ~SentenceLvl1AST();

    void setFirstIdentifier(SimpleIdentifierAST *idtf);
    void setSecondIdentifier(SimpleIdentifierAST *idtf);
    void setThirdIdentifier(SimpleIdentifierAST *idtf);

    NodeType(SENTENCE_LVL1)
private:
    SimpleIdentifierAST *mFirstIdtf;
    SimpleIdentifierAST *mSecondIdtf;
    SimpleIdentifierAST *mThirdIdtf;
};

class SentenceLv234561AST: public AST
{
public:
    SentenceLv234561AST();
    SentenceLv234561AST(IdentifierAST *idtf, QString connector, AttributesListAST *attrLst, ObjectListAST* objLst);
    virtual ~SentenceLv234561AST();

    void setIdentifier(IdentifierAST* idtf);
    void setConnector(QString connector);
    void setAttributeList(AttributesListAST* attrLst);
    void setObjectList(ObjectListAST* objLst);

    NodeType(SENTENCE_LVL23456)
private:
    IdentifierAST *mIdentifier;
    QString mConntector;
    AttributesListAST *mAttributeList;
    ObjectListAST *mObjectList;
};

class SimpleIdentifierAST: public AST
{
public:
    SimpleIdentifierAST();
    ~SimpleIdentifierAST();

    void setName(QString name);
    void setUrl(QString url);

    NodeType(SIMPLE_IDENTIFIER)

private:
    QString         mName;
    QString         mUrl;
};


class IdentifierAST: public AST
{
public:
    explicit IdentifierAST(AnyIdentifierAST *idtf);
    virtual ~IdentifierAST();

    NodeType(IDENTIFIER)
private:
    AnyIdentifierAST *mIdentidier;
};


class TripleAST: public AST
{
public:
    TripleAST();
    TripleAST(IdentifierAST *firstIdtf, IdentifierAST *secondIdtf);
    virtual ~TripleAST();

    void setFirstIdentifier(IdentifierAST *idtf);
    void setSecondIdentifier(IdentifierAST *idtf);

    NodeType(TRIPLE)
private:
    IdentifierAST   *mFirstIdtf;
    IdentifierAST   *mSecondIdtf;
};

class AnyIdentifierAST: public AST
{
public:
    explicit AnyIdentifierAST(SimpleIdentifierAST *idtf);
    explicit AnyIdentifierAST(QString content);
    explicit AnyIdentifierAST(TripleAST *triple);
    explicit AnyIdentifierAST(SetIdentifierAST *setIdtf);
    explicit AnyIdentifierAST(OSetIdentifierAST *osetIdtf);
    explicit AnyIdentifierAST(AliasAST *alias);
    virtual ~AnyIdentifierAST();


    NodeType(ANY_IDENTIFIER)
private:
    SimpleIdentifierAST *mSimplyIdtf;
    QString             mContent;
    TripleAST           *mTriple;
    SetIdentifierAST    *mSetIdtf;
    OSetIdentifierAST    *mOSetIdtf;
    AliasAST            *mAlias;
};

class SetIdentifierAST: public AST
{
public:
    SetIdentifierAST();
    SetIdentifierAST(AttributesListAST* attrLst, IdentifierWithInternalAST *idtf);
    virtual ~SetIdentifierAST();

    void addSentence(AttributesListAST* attrLst, IdentifierWithInternalAST *idtf);

    NodeType(SET_IDENTIFIER)
private:
    struct SetIdentifierSentence
    {
        SetIdentifierSentence(AttributesListAST *lst,IdentifierWithInternalAST *idtf)
        {
            mAttrList = lst;
            mIdtfWithInt = idtf;
        }

        AttributesListAST           *mAttrList;
        IdentifierWithInternalAST   *mIdtfWithInt;
    };
    QList<SetIdentifierSentence*> mSetSentenceLst;
};


class OSetIdentifierAST: public AST
{
public:
    OSetIdentifierAST();
    //OSetIdentifierAST(AttributesListAST* attrLst, IdentifierWithInternalAST *idtf);
    virtual ~OSetIdentifierAST();

    void addSentence(AttributesListAST* attrLst, IdentifierWithInternalAST *idtf);
    NodeType(OSET_IDENTIFIER)
private:
    struct OSetIdentifierSentence
    {
        OSetIdentifierSentence(AttributesListAST *lst,IdentifierWithInternalAST *idtf)
        {
            mAttrList = lst;
            mIdtfWithInt = idtf;
        }
        AttributesListAST           *mAttrList;
        IdentifierWithInternalAST   *mIdtfWithInt;
    };
    QList<OSetIdentifierSentence*> mSetSentenceLst;
};


class AliasAST: public AST
{
public:
    AliasAST(QString alias);
    virtual ~AliasAST();

    NodeType(ALIAS)
private:
    QString     mAlias;
};


class AttributesListAST: public AST
{
public:
    AttributesListAST();
    AttributesListAST(SimpleIdentifierWAttributeSeparatorAST *idtf);
    virtual ~AttributesListAST();

    void addIdentifier(SimpleIdentifierWAttributeSeparatorAST *idtf);
    AttributesListAST* operator <<(SimpleIdentifierWAttributeSeparatorAST *idtf);

    NodeType(ATRIBUTES_LIST)
private:
    QList<SimpleIdentifierWAttributeSeparatorAST*> mAttrListSentenceLst;
};

class SimpleIdentifierWAttributeSeparatorAST: public AST
{
public:
    SimpleIdentifierWAttributeSeparatorAST();
    SimpleIdentifierWAttributeSeparatorAST(SimpleIdentifierAST *idtf, QString attrSep);
    virtual ~SimpleIdentifierWAttributeSeparatorAST();

    void setIdentifier(SimpleIdentifierAST *idtf);
    void setAttributeSeparator(QString attrSep);

    NodeType(SIMPLE_IDENTIFIER_W_ATTRIBUTE_SEPARATOR)
private:
    SimpleIdentifierAST *mIdentifier;
    QString mAttrSep;
};


class IdentifierWithInternalAST: public AST
{
public:
    IdentifierWithInternalAST();
    explicit IdentifierWithInternalAST(IdentifierAST *idtf, InternalAST *internal = NULL);
    virtual ~IdentifierWithInternalAST();

    void setIdentifier(IdentifierAST *idtf);
    void setInternal(InternalAST *internal);

    NodeType(IDTF_WITH_INT)
private:
    IdentifierAST   *mIdtf;
    InternalAST     *mInternal;
};


class InternalAST: public AST
{
public:
    explicit InternalAST(InternalSentenceListAST *lst);
    virtual ~InternalAST();

    NodeType(INTERNAL)
private:
    InternalSentenceListAST *mInternalLst;
};


class InternalSentenceListAST: public AST
{
public:
    InternalSentenceListAST();
    explicit InternalSentenceListAST(InternalSentenceAST *sentence);
    virtual ~InternalSentenceListAST();

    void addSentence(InternalSentenceAST *sentence);
    InternalSentenceListAST* operator <<(InternalSentenceAST *sentence);


    NodeType(INTERNAL_SENTENCE_LIST)
private:
    QList<InternalSentenceAST*> mInternalLst;
};


class InternalSentenceAST: public AST
{
public:
    InternalSentenceAST();
    InternalSentenceAST(QString connector, AttributesListAST *attrLst, ObjectListAST *objLst);
    ~InternalSentenceAST();

    void setConnector(QString connector);
    void setAttributeList(AttributesListAST *lst);
    void setObjectList(ObjectListAST *lst);


    NodeType(INTERNAL_SENTENCE)
private:
    QString mConnector;
    AttributesListAST *mAttributeList;
    ObjectListAST *mObjectList;
};


class ObjectListAST: public AST
{
public:
    ObjectListAST();
    ObjectListAST(IdentifierWithInternalAST *idtf);
    ~ObjectListAST();

    void addIdentifier(IdentifierWithInternalAST *idtf);
    ObjectListAST* operator <<(IdentifierWithInternalAST*);


    NodeType(OBJECT_LIST)
private:
    QList<IdentifierWithInternalAST*> mIdtfWithIntLst;
};


}

#endif // ASTNODES_H
