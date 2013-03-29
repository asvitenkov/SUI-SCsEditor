#include "scsastnodes.h"

using namespace SCsAST;


RootAST::RootAST()
{

}

RootAST::~RootAST()
{
    qDeleteAll(mSentenceLst.begin(), mSentenceLst.end());
    mSentenceLst.clear();
}

RootAST::RootAST(SentenceAST *sentence)
{
    Q_CHECK_PTR(sentence);

    if(sentence)
        mSentenceLst.append(sentence);
}

RootAST* RootAST::operator <<(SentenceAST *sentence)
{
    Q_CHECK_PTR(sentence);

    if(sentence)
        mSentenceLst.append(sentence);

    return this;
}

void RootAST::addSentence(SentenceAST *sentence)
{
    Q_CHECK_PTR(sentence);

    if(sentence)
        mSentenceLst.append(sentence);
}

SentenceAST::SentenceAST(SentenceLv234561AST *sentence):
    mSentenceLvl1(NULL), mSentenceLvl23456(NULL)
{
    Q_CHECK_PTR(sentence);
    mSentenceLvl23456 = sentence;
}

SentenceAST::SentenceAST(SentenceLvl1AST *sentence):
    mSentenceLvl1(NULL), mSentenceLvl23456(NULL)
{
    Q_CHECK_PTR(sentence);
    mSentenceLvl1 = sentence;
}

SentenceAST::~SentenceAST()
{
    if(mSentenceLvl1)
        delete mSentenceLvl1;

    if(mSentenceLvl23456)
        delete mSentenceLvl23456;
}

SentenceLvl1AST::SentenceLvl1AST():
    mFirstIdtf(NULL), mSecondIdtf(NULL), mThirdIdtf(NULL)
{

}

SentenceLvl1AST::~SentenceLvl1AST()
{
    if(mFirstIdtf)
        delete mFirstIdtf;
    if(mSecondIdtf)
        delete mSecondIdtf;
    if(mThirdIdtf)
        delete mThirdIdtf;
}

void SentenceLvl1AST::setFirstIdentifier(SimpleIdentifierAST *idtf)
{
    Q_ASSERT_X(mFirstIdtf==NULL,"","mFirstIdtf already defined");
    Q_CHECK_PTR(idtf);

    if(idtf)
        mFirstIdtf = idtf;
}

void SentenceLvl1AST::setSecondIdentifier(SimpleIdentifierAST *idtf)
{
    Q_ASSERT_X(mSecondIdtf==NULL,"","mSecondIdtf already defined");
    Q_CHECK_PTR(idtf);

    if(idtf)
        mSecondIdtf = idtf;
}



void SentenceLvl1AST::setThirdIdentifier(SimpleIdentifierAST *idtf)
{
    Q_ASSERT_X(mThirdIdtf==NULL,"","mThirdIdtf already defined");
    Q_CHECK_PTR(idtf);

    if(idtf)
        mThirdIdtf = idtf;
}

SentenceLvl1AST::SentenceLvl1AST(SimpleIdentifierAST *firstIdtf, SimpleIdentifierAST *secondIdetf, SimpleIdentifierAST *thirdIdtf):
    mFirstIdtf(NULL), mSecondIdtf(NULL), mThirdIdtf(NULL)
{
    Q_CHECK_PTR(firstIdtf);
    Q_CHECK_PTR(secondIdetf);
    Q_CHECK_PTR(thirdIdtf);

    mFirstIdtf = firstIdtf;
    mSecondIdtf = secondIdetf;
    mThirdIdtf = thirdIdtf;
}

SentenceLv234561AST::SentenceLv234561AST():
    mIdentifier(NULL), mAttributeList(NULL), mObjectList(NULL)
{

}

SentenceLv234561AST::SentenceLv234561AST(IdentifierAST *idtf, QString connector, AttributesListAST *attrLst, ObjectListAST *objLst):
    mIdentifier(NULL), mAttributeList(NULL), mObjectList(NULL)
{
    Q_CHECK_PTR(idtf);
    Q_CHECK_PTR(attrLst);
    Q_CHECK_PTR(objLst);

    mIdentifier = idtf;
    mAttributeList = attrLst;
    mObjectList = objLst;
}


SentenceLv234561AST::~SentenceLv234561AST()
{
    if(mIdentifier)
        delete mIdentifier;
    if(mAttributeList)
        delete mAttributeList;
    if(mObjectList)
        delete mObjectList;
}

void SentenceLv234561AST::setIdentifier(IdentifierAST *idtf)
{
    Q_ASSERT_X(mIdentifier == NULL, "", "mIdentifier already defined");
    Q_CHECK_PTR(idtf);

    if(idtf)
        mIdentifier = idtf;
}

void SentenceLv234561AST::setConnector(QString connector)
{
    Q_ASSERT_X(mConntector.isEmpty(), "", "mConntector already defined");
    Q_ASSERT(!connector.isEmpty());

    if(!connector.isEmpty())
        mConntector = connector;
}


void SentenceLv234561AST::setAttributeList(AttributesListAST *attrLst)
{
    Q_ASSERT_X(mAttributeList == NULL, "", "mAttributeList already defined");
    Q_CHECK_PTR(attrLst);

    if(attrLst)
        mAttributeList = attrLst;
}


void SentenceLv234561AST::setObjectList(ObjectListAST *objLst)
{
    Q_ASSERT_X(mObjectList == NULL, "", "mObjectList already defined");
    Q_CHECK_PTR(objLst);

    if(objLst)
        mObjectList = objLst;
}


SimpleIdentifierAST::SimpleIdentifierAST()
{

}

SimpleIdentifierAST::~SimpleIdentifierAST()
{

}

void SimpleIdentifierAST::setName(QString name)
{
    Q_ASSERT_X(mName.isEmpty(),"","mName already defined");
    Q_ASSERT(!name.isEmpty());

    if(!name.isEmpty())
    {
        mName = name;
        mUrl.clear();
    }
}

void SimpleIdentifierAST::setURL(QString url)
{
    Q_ASSERT_X(mUrl.isEmpty(),"","mUrl already defined");
    Q_ASSERT(!url.isEmpty());

    if(!url.isEmpty())
    {
        mUrl = url;
        mName.clear();
    }
}
