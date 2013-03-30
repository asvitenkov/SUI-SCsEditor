#include "scsastnodes.h"

using namespace SCsAST;

//***********************************************************************

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


//***********************************************************************

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

//***********************************************************************

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

    if(idtf && !mFirstIdtf)
        mFirstIdtf = idtf;
}

void SentenceLvl1AST::setSecondIdentifier(SimpleIdentifierAST *idtf)
{
    Q_ASSERT_X(mSecondIdtf==NULL,"","mSecondIdtf already defined");
    Q_CHECK_PTR(idtf);

    if(idtf && !mSecondIdtf)
        mSecondIdtf = idtf;
}



void SentenceLvl1AST::setThirdIdentifier(SimpleIdentifierAST *idtf)
{
    Q_ASSERT_X(mThirdIdtf==NULL,"","mThirdIdtf already defined");
    Q_CHECK_PTR(idtf);

    if(idtf && !mThirdIdtf)
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


//***********************************************************************

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

    if(idtf && !mIdentifier)
        mIdentifier = idtf;
}

void SentenceLv234561AST::setConnector(QString connector)
{
    Q_ASSERT_X(mConntector.isEmpty(), "", "mConntector already defined");
    Q_ASSERT(!connector.isEmpty());

    if(connector.isEmpty() && !mConntector.isEmpty())
        mConntector = connector;
}


void SentenceLv234561AST::setAttributeList(AttributesListAST *attrLst)
{
    Q_ASSERT_X(mAttributeList == NULL, "", "mAttributeList already defined");
    Q_CHECK_PTR(attrLst);

    if(attrLst && !mAttributeList)
        mAttributeList = attrLst;
}


void SentenceLv234561AST::setObjectList(ObjectListAST *objLst)
{
    Q_ASSERT_X(mObjectList == NULL, "", "mObjectList already defined");
    Q_CHECK_PTR(objLst);

    if(objLst && !mObjectList)
        mObjectList = objLst;
}


//***********************************************************************


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

    if(!name.isEmpty() && mName.isEmpty())
    {
        mName = name;
        mUrl.clear();
    }
}

void SimpleIdentifierAST::setUrl(QString url)
{
    Q_ASSERT_X(mUrl.isEmpty(),"","mUrl already defined");
    Q_ASSERT(!url.isEmpty());

    if(!url.isEmpty() && !mUrl.isEmpty())
    {
        mUrl = url;
        mName.clear();
    }
}


//***********************************************************************


IdentifierAST::IdentifierAST(AnyIdentifierAST *idtf):
    mIdentidier(NULL)
{
    Q_CHECK_PTR(idtf);
    mIdentidier = idtf;
}

IdentifierAST::~IdentifierAST()
{
    if(mIdentidier)
        delete mIdentidier;
}

//***********************************************************************


TripleAST::TripleAST():
    mFirstIdtf(NULL), mSecondIdtf(NULL)
{

}

TripleAST::TripleAST(IdentifierAST *firstIdtf, IdentifierAST *secondIdtf):
    mFirstIdtf(NULL), mSecondIdtf(NULL)
{
    Q_CHECK_PTR(firstIdtf);
    Q_CHECK_PTR(secondIdtf);

    mFirstIdtf = firstIdtf;
    mSecondIdtf = secondIdtf;
}

TripleAST::~TripleAST()
{
    if(mFirstIdtf)
        delete mFirstIdtf;
    if(mSecondIdtf)
        delete mSecondIdtf;
}

void TripleAST::setFirstIdentifier(IdentifierAST *idtf)
{
    Q_ASSERT_X(mFirstIdtf == NULL,"","mFirstIdtf already defined");
    Q_CHECK_PTR(idtf);

    if(idtf && !mFirstIdtf)
        mFirstIdtf = idtf;
}

void TripleAST::setSecondIdentifier(IdentifierAST *idtf)
{
    Q_ASSERT_X(mSecondIdtf == NULL,"","mSecondIdtf already defined");
    Q_CHECK_PTR(idtf);

    if(idtf && !mSecondIdtf)
        mSecondIdtf = idtf;
}


//***********************************************************************


AnyIdentifierAST::AnyIdentifierAST(AliasAST *alias):
    mSimplyIdtf(NULL), mTriple(NULL), mSetIdtf(NULL), mOSetIdtf(NULL), mAlias(NULL)
{
    Q_CHECK_PTR(alias);

    mAlias = alias;
}

AnyIdentifierAST::AnyIdentifierAST(OSetIdentifierAST *osetIdtf):
    mSimplyIdtf(NULL), mTriple(NULL), mSetIdtf(NULL), mOSetIdtf(NULL), mAlias(NULL)
{
    Q_CHECK_PTR(osetIdtf);

    mOSetIdtf = osetIdtf;
}

AnyIdentifierAST::AnyIdentifierAST(QString content):
    mSimplyIdtf(NULL), mTriple(NULL), mSetIdtf(NULL), mOSetIdtf(NULL), mAlias(NULL)
{
    Q_ASSERT(!content.isEmpty());

    mContent = content;
}

AnyIdentifierAST::AnyIdentifierAST(SetIdentifierAST *setIdtf):
    mSimplyIdtf(NULL), mTriple(NULL), mSetIdtf(NULL), mOSetIdtf(NULL), mAlias(NULL)
{
    Q_CHECK_PTR(setIdtf);

    mSetIdtf = setIdtf;
}

AnyIdentifierAST::AnyIdentifierAST(SimpleIdentifierAST *idtf):
    mSimplyIdtf(NULL), mTriple(NULL), mSetIdtf(NULL), mOSetIdtf(NULL), mAlias(NULL)
{
    Q_CHECK_PTR(idtf);

    mSimplyIdtf = idtf;
}

AnyIdentifierAST::AnyIdentifierAST(TripleAST *triple):
    mSimplyIdtf(NULL), mTriple(NULL), mSetIdtf(NULL), mOSetIdtf(NULL), mAlias(NULL)
{
    Q_CHECK_PTR(triple);

    mTriple = triple;
}

AnyIdentifierAST::~AnyIdentifierAST()
{
    if(mSimplyIdtf)
        delete mSimplyIdtf;
    if(mTriple)
        delete mTriple;
    if(mSetIdtf)
        delete mSetIdtf;
    if(mOSetIdtf)
        delete mOSetIdtf;
    if(mAlias)
        delete mAlias;
}


//***********************************************************************


SetIdentifierAST::SetIdentifierAST()
{

}

SetIdentifierAST::SetIdentifierAST(AttributesListAST *attrLst, IdentifierWithInternalAST *idtf)
{
    Q_CHECK_PTR(attrLst);
    Q_CHECK_PTR(idtf);

    if(attrLst && idtf)
        mSetSentenceLst.append(new SetIdentifierSentence(attrLst,idtf));
}

SetIdentifierAST::~SetIdentifierAST()
{
    qDeleteAll(mSetSentenceLst.begin(), mSetSentenceLst.end());
    mSetSentenceLst.clear();
}

void SetIdentifierAST::addSentence(AttributesListAST *attrLst, IdentifierWithInternalAST *idtf)
{
    Q_CHECK_PTR(attrLst);
    Q_CHECK_PTR(idtf);

    if(attrLst && idtf)
        mSetSentenceLst.append(new SetIdentifierSentence(attrLst,idtf));
}


//***********************************************************************

OSetIdentifierAST::OSetIdentifierAST()
{

}

//OSetIdentifierAST::OSetIdentifierAST(AttributesListAST *attrLst, IdentifierWithInternalAST *idtf)
//{
//    Q_CHECK_PTR(attrLst);
//    Q_CHECK_PTR(idtf);

//    if(attrLst && idtf)
//        mSetSentenceLst.append(new OSetIdentifierSentence(attrLst,idtf));
//}

OSetIdentifierAST::~OSetIdentifierAST()
{
    qDeleteAll(mSetSentenceLst.begin(), mSetSentenceLst.end());
    mSetSentenceLst.clear();
}

void OSetIdentifierAST::addSentence(AttributesListAST *attrLst, IdentifierWithInternalAST *idtf)
{
    Q_CHECK_PTR(attrLst);
    Q_CHECK_PTR(idtf);

    if(attrLst && idtf)
        mSetSentenceLst.append(new OSetIdentifierSentence(attrLst,idtf));
}


//***********************************************************************


AliasAST::AliasAST(QString alias)
{
    Q_ASSERT(!alias.isEmpty());

    mAlias = alias;
}

AliasAST::~AliasAST()
{

}


//***********************************************************************

AttributesListAST::AttributesListAST()
{

}

AttributesListAST::AttributesListAST(SimpleIdentifierWAttributeSeparatorAST *idtf)
{
    Q_CHECK_PTR(idtf);

    if(idtf)
        mAttrListSentenceLst.append(idtf);
}

AttributesListAST::~AttributesListAST()
{
    qDeleteAll(mAttrListSentenceLst.begin(),mAttrListSentenceLst.end());
    mAttrListSentenceLst.clear();
}


void AttributesListAST::addIdentifier(SimpleIdentifierWAttributeSeparatorAST *idtf)
{
    Q_CHECK_PTR(idtf);

    if(idtf)
        mAttrListSentenceLst.append(idtf);
}

AttributesListAST* AttributesListAST::operator <<(SimpleIdentifierWAttributeSeparatorAST *idtf)
{
    Q_CHECK_PTR(idtf);

    if(idtf)
        mAttrListSentenceLst.append(idtf);

    return this;
}


//***********************************************************************

IdentifierWithInternalAST::IdentifierWithInternalAST():
    mIdtf(NULL), mInternal(NULL)
{

}

IdentifierWithInternalAST::IdentifierWithInternalAST(IdentifierAST *idtf, InternalAST *internal):
    mIdtf(NULL), mInternal(NULL)
{
    Q_CHECK_PTR(idtf);
    Q_CHECK_PTR(internal);

    mIdtf = idtf;
    mInternal = internal;
}


IdentifierWithInternalAST::~IdentifierWithInternalAST()
{
    if(mIdtf)
        delete mIdtf;
    if(mInternal)
        delete mInternal;
}

void IdentifierWithInternalAST::setIdentifier(IdentifierAST *idtf)
{
    Q_ASSERT_X(mIdtf == NULL,"","mIdtf already defined");
    Q_CHECK_PTR(idtf);

    if(idtf && !mIdtf)
        mIdtf = idtf;
}

void IdentifierWithInternalAST::setInternal(InternalAST *internal)
{
    Q_ASSERT_X(internal == NULL,"","mInternal already defined");
    Q_CHECK_PTR(internal);

    if(internal && !mInternal)
        mInternal = internal;
}


//***********************************************************************

InternalAST::InternalAST(InternalSentenceListAST *lst):
    mInternalLst(NULL)
{
    Q_CHECK_PTR(lst);

    mInternalLst = lst;
}

InternalAST::~InternalAST()
{
    if(mInternalLst)
        delete mInternalLst;
}

//***********************************************************************

InternalSentenceListAST::InternalSentenceListAST()
{

}

InternalSentenceListAST::InternalSentenceListAST(InternalSentenceAST *sentence)
{
    Q_CHECK_PTR(sentence);

    if(sentence)
        mInternalLst.append(sentence);
}

InternalSentenceListAST::~InternalSentenceListAST()
{
    qDeleteAll(mInternalLst.begin(),mInternalLst.end());
    mInternalLst.clear();
}

void InternalSentenceListAST::addSentence(InternalSentenceAST *sentence)
{
    Q_CHECK_PTR(sentence);

    if(sentence)
        mInternalLst.append(sentence);
}

InternalSentenceListAST* InternalSentenceListAST::operator <<(InternalSentenceAST *sentence)
{
    Q_CHECK_PTR(sentence);

    if(sentence)
        mInternalLst.append(sentence);

    return this;
}

//***********************************************************************

InternalSentenceAST::InternalSentenceAST():
    mAttributeList(NULL), mObjectList(NULL)
{

}

InternalSentenceAST::InternalSentenceAST(QString connector, AttributesListAST *attrLst, ObjectListAST *objLst):
    mAttributeList(NULL), mObjectList(NULL)
{
    Q_CHECK_PTR(objLst);
    Q_CHECK_PTR(attrLst);
    Q_ASSERT(!connector.isEmpty());

    mConnector = connector;
    mAttributeList = attrLst;
    mObjectList = objLst;
}


InternalSentenceAST::~InternalSentenceAST()
{
    if(mAttributeList)
        delete mAttributeList;
    if(mObjectList)
        delete mObjectList;
}

void InternalSentenceAST::setAttributeList(AttributesListAST *lst)
{
    Q_CHECK_PTR(lst);
    Q_ASSERT_X(mAttributeList == NULL,"","mAttributeList already defined");

    if(lst)
        mAttributeList = lst;
}

void InternalSentenceAST::setConnector(QString connector)
{
    Q_ASSERT(!connector.isEmpty());
    Q_ASSERT_X(mConnector.isEmpty(),"","mConnector already defined");

    if(!connector.isEmpty() && mConnector.isEmpty())
        mConnector = connector;
}


void InternalSentenceAST::setObjectList(ObjectListAST *lst)
{
    Q_CHECK_PTR(lst);
    Q_ASSERT_X(mObjectList == NULL,"","mObjectList already defined");

    if(lst && !mObjectList)
        mObjectList = lst;
}

//***********************************************************************


ObjectListAST::ObjectListAST()
{

}

ObjectListAST::ObjectListAST(IdentifierWithInternalAST *idtf)
{
    Q_CHECK_PTR(idtf);

    if(idtf)
        mIdtfWithIntLst.append(idtf);
}

ObjectListAST::~ObjectListAST()
{
    qDeleteAll(mIdtfWithIntLst.begin(),mIdtfWithIntLst.end());
    mIdtfWithIntLst.clear();
}


void ObjectListAST::addIdentifier(IdentifierWithInternalAST *idtf)
{
    Q_CHECK_PTR(idtf);

    if(idtf)
        mIdtfWithIntLst.append(idtf);
}

ObjectListAST* ObjectListAST::operator <<(IdentifierWithInternalAST *idtf)
{
    Q_CHECK_PTR(idtf);

    if(idtf)
        mIdtfWithIntLst.append(idtf);

    return this;
}


//***********************************************************************

SimpleIdentifierWAttributeSeparatorAST::SimpleIdentifierWAttributeSeparatorAST():
    mIdentifier(NULL)
{

}


SimpleIdentifierWAttributeSeparatorAST::SimpleIdentifierWAttributeSeparatorAST(SimpleIdentifierAST *idtf, QString attrSep):
    mIdentifier(NULL)
{
    Q_CHECK_PTR(idtf);
    Q_ASSERT(!attrSep.isEmpty());

    mIdentifier = idtf;
    mAttrSep = attrSep;
}


SimpleIdentifierWAttributeSeparatorAST::~SimpleIdentifierWAttributeSeparatorAST()
{
    if(mIdentifier)
        delete mIdentifier;
}

void SimpleIdentifierWAttributeSeparatorAST::setIdentifier(SimpleIdentifierAST *idtf)
{
   Q_CHECK_PTR(idtf);

   Q_ASSERT_X(mIdentifier == NULL,"","mIdentifier already defined");

    if(idtf && !mIdentifier)
        mIdentifier = idtf;
}



void SimpleIdentifierWAttributeSeparatorAST::setAttributeSeparator(QString attrSep)
{
    Q_ASSERT(attrSep.isEmpty());
    Q_ASSERT_X(mAttrSep.isEmpty(),"","mAttrSep already defined");

    if(!attrSep.isEmpty() && mAttrSep.isEmpty())
        mAttrSep = attrSep;

}

//***********************************************************************

