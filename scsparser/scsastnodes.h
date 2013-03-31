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
class SimpleIdtfrWAttrSepAST;
class ObjSepWAttrListWIdtfWithInt;
class IntSentenceWSentSep;
class ObjSepWIdtfWithInt;

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
    ,OBJSEP_W_ATTR_LIST_W_IDTF_WITH_INT
    ,INT_SENTENCE_W_SENT_SEP
    ,OBJ_SEP_W_IDTF_WITH_INT
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
    void setFirstTripleSeparator(QString separator);
    void setSecondTripleSeparator(QString separator);


    NodeType(SENTENCE_LVL1)
private:
    QString mFirstTripleSep;
    QString mSecondTripleSep;
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
    virtual ~TripleAST();

    void setFirstIdentifier(IdentifierAST *idtf);
    void setSecondIdentifier(IdentifierAST *idtf);
    void setLeftPar(QString par);
    void setRighPar(QString par);
    void setContent(QString content);

    NodeType(TRIPLE)
private:
    QString mLeftPar;
    QString mRightPar;
    QString mContent;
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


class ObjSepWAttrListWIdtfWithInt: public AST
{
public:
    ObjSepWAttrListWIdtfWithInt();
    ObjSepWAttrListWIdtfWithInt(QString separator, AttributesListAST *lst, IdentifierWithInternalAST *idtf);
    virtual ~ObjSepWAttrListWIdtfWithInt();

    void setSeparator(QString separator);
    void setAttributeList(AttributesListAST *lst);
    void setIdentifier(IdentifierWithInternalAST *idtf);

    NodeType(OBJSEP_W_ATTR_LIST_W_IDTF_WITH_INT)
private:
    QString mObjSep;
    AttributesListAST *mAttrLst;
    IdentifierWithInternalAST *mIdtfWithInt;
};


class SetIdentifierAST: public AST
{
public:
    SetIdentifierAST();
    virtual ~SetIdentifierAST();

    void setLeftSeparator(QString sep);
    void setRightSeparator(QString sep);
    void setAttributeList(AttributesListAST *lst);
    void setIdentifier(IdentifierWithInternalAST *idtf);
    void addSentence(ObjSepWAttrListWIdtfWithInt *sentence);
    SetIdentifierAST* operator <<(ObjSepWAttrListWIdtfWithInt*);

    NodeType(SET_IDENTIFIER)
private:
    QString mLeftSep;
    AttributesListAST *mAttrLst;
    IdentifierWithInternalAST *mIdtf;
    QList<ObjSepWAttrListWIdtfWithInt*> mSetSentenceLst;
    QString mRightSep;
};

class OSetIdentifierAST: public AST
{
public:
    OSetIdentifierAST();
    virtual ~OSetIdentifierAST();

    void setLeftSeparator(QString sep);
    void setRightSeparator(QString sep);
    void setAttributeList(AttributesListAST *lst);
    void setIdentifier(IdentifierWithInternalAST *idtf);
    void addSentence(ObjSepWAttrListWIdtfWithInt *sentence);
    OSetIdentifierAST* operator <<(ObjSepWAttrListWIdtfWithInt*);

    NodeType(OSET_IDENTIFIER)
private:
    QString mLeftSep;
    AttributesListAST *mAttrLst;
    IdentifierWithInternalAST *mIdtf;
    QList<ObjSepWAttrListWIdtfWithInt*> mSetSentenceLst;
    QString mRightSep;
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
    AttributesListAST(SimpleIdtfrWAttrSepAST *idtf);
    virtual ~AttributesListAST();

    void addIdentifier(SimpleIdtfrWAttrSepAST *idtf);
    AttributesListAST* operator <<(SimpleIdtfrWAttrSepAST *idtf);

    NodeType(ATRIBUTES_LIST)
private:
    QList<SimpleIdtfrWAttrSepAST*> mAttrListSentenceLst;
};

class SimpleIdtfrWAttrSepAST: public AST
{
public:
    SimpleIdtfrWAttrSepAST();
    SimpleIdtfrWAttrSepAST(SimpleIdentifierAST *idtf, QString attrSep);
    virtual ~SimpleIdtfrWAttrSepAST();

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
    virtual ~InternalSentenceListAST();

    void setLeftInternalSeparator(QString separator);
    void setRigthInternalSeparator(QString separator);
    void addSentence(IntSentenceWSentSep *sentence);
    InternalSentenceListAST* operator <<(IntSentenceWSentSep *sentence);

    NodeType(INTERNAL_SENTENCE_LIST)
private:
    QString mRightIntSep;
    QString mLeftIntSep;
    QList<IntSentenceWSentSep*> mInternalLst;
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
    ~ObjectListAST();

    void setIdentifierWithInt(IdentifierWithInternalAST *idtf);

    void addIdentifier(ObjSepWIdtfWithInt *idtf);
    ObjectListAST* operator <<(ObjSepWIdtfWithInt*);


    NodeType(OBJECT_LIST)
private:
    IdentifierWithInternalAST *mIdtfWithInt;
    QList<ObjSepWIdtfWithInt*> mIdtfWithIntLst;
};


class IntSentenceWSentSep: public AST
{
public:
    IntSentenceWSentSep();
    IntSentenceWSentSep(InternalSentenceAST *sentence, QString septSep);
    virtual ~IntSentenceWSentSep();

    void setInternalSentence(InternalSentenceAST *sentence);
    void setSentenceSeparator(QString separator);


    NodeType(INT_SENTENCE_W_SENT_SEP)
private:
    InternalSentenceAST *mIntSentence;
    QString mSentSep;
};


class ObjSepWIdtfWithInt: public AST
{
public:
    ObjSepWIdtfWithInt();
    ObjSepWIdtfWithInt(IdentifierWithInternalAST *idtf, QString objSep);
    virtual ~ObjSepWIdtfWithInt();

    void setIdentifierWithInternal(IdentifierWithInternalAST *idtf);
    void setObjectSeparator(QString separator);


    NodeType(OBJ_SEP_W_IDTF_WITH_INT)
private:
    IdentifierWithInternalAST *mIdtwWithInt;
    QString mObjSep;
};



}

#endif // ASTNODES_H
