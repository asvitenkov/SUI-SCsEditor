grammar SCs;

options
{
    language = Cpp;
}

@lexer::includes
{
  #include <list>
}


@parser::includes
{

#include "SCsLexer.hpp"
#include <list>
#include "scsastnodes.h"
using namespace SCsAST;
 
#define pName retPtr
#define RECOVER if(mNeedRecover) this->recover();
#define IFNR RECOVER
#define SET_NEED_RECOVER(value) mNeedRecover = value;
#define SNR(value) SET_NEED_RECOVER(value)
#define IFNRR if(mNeedRecover) return retPtr;
#define INIT_RULE(p) initRule(p) 
#define BNTS(ptr) mCurrentNode = retPtr;// before non terminal symbol
#define BTS(ptr) mCurrentNode = retPtr;// before terminal symbol

#define CHECK_EXCEPTION     \
  if(mHasException)     \
    {             \
    mHasException=false;  \
    retPtr->setException(); \
  }       
//after terminal symbol
#define ATS(ptr,methodName) \
  if(ptr!=NULL) pName->methodName(QString::fromStdString(ptr->getText())); \
  CHECK_EXCEPTION \
  IFNRR 
// after non terminal symbol
#define ANTS(ptr,methodName) \
  if(ptr!=NULL) pName->methodName(ptr); \
  IFNRR 
#define CODE_AFTER_RULE CHECK_EXCEPTION

}

@lexer::namespace { SCsParserNS }
@parser::namespace{ SCsParserNS }


@lexer::traits 
{
  class SCsLexer; 
  class SCsParser; 

  template<class ImplTraits>
  class UserTraits : public antlr3::CustomTraitsBase<ImplTraits>
  {
  public:
    static const bool TOKENS_ACCESSED_FROM_OWNING_RULE = true;
  };

  typedef antlr3::Traits< SCsLexer, SCsParser, UserTraits > SCsLexerTraits;
  typedef SCsLexerTraits SCsParserTraits;
}


syntax 
  //rule: ( sentence_sentsep )*
	@init
		{

		  mNeedRecover = false;
		  SyntaxAST* retPtr = new SyntaxAST();
		  INIT_RULE(retPtr);
		  mHasException = false;
		  mLastExceptionCheked = true;
		}
	@after{ CODE_AFTER_RULE }
: 
      ( {BNTS(a)} a = sentence_sentsep  { ANTS(a,addSentence) IFNR retPtr->addSentence($a.retPtr); }  )*  EOF//attention
;
 
sentence_sentsep returns[SentenceWithSeparator* retPtr]
  //rule: entence SENTSEP
  @init
		{
		    retPtr = new SentenceWithSeparator();
		    INIT_RULE(retPtr);
		}
	@after{ CODE_AFTER_RULE }	
	 
:
    {BNTS(a)}  a = sentence { ANTS(a,setSentence)}
    {BTS(b) }  b = SENTSEP  { ATS(b,setSeparator)} 
;

sentence  returns [SentenceAST* retPtr]
  //rule: sentence_lv1 | sentence_lv23456
	@init
		{
		  retPtr = new SentenceAST();
		  INIT_RULE(retPtr);
		}
	@after{ CODE_AFTER_RULE }
	
: 
        {BNTS(a)}  a = sentence_lv1        {ANTS(a,addSentenceLvl1)}
      | {BNTS(b)}  b = sentence_lv23456    {ANTS(b,addSentenceLv234561)}
;


sentence_lv23456 returns [SentenceLv234561AST* retPtr]
  //rule: idtf CONNECTORS   attrsList objectList
	@init
		{
		  retPtr = new SentenceLv234561AST();
		  INIT_RULE(retPtr);
		}
	@after{ CODE_AFTER_RULE }
	
: 
    {BNTS(a)}  a = idtf            { ANTS(a,setIdentifier)}
    {BTS(b) }  b = CONNECTORS      { ATS(b,setConnector)} 
    {BNTS(c)}  c = attrsList       { ANTS(c,setAttributeList)}
    {BNTS(d)}  d = objectList      { ANTS(d,setObjectList) }
;


// add type to simpleidtf
sentence_lv1 returns [SentenceLvl1AST* retPtr]
  //rule: simpleIdtf TRIPLESEP simpleIdtf TRIPLESEP simpleIdtf 
	@init
		{
		  retPtr = new SentenceLvl1AST();
		  INIT_RULE(retPtr);
		}
	@after{ CODE_AFTER_RULE }
	
: 
     {BNTS(a)}   a = simpleIdtf    { ANTS(a,setFirstIdentifier)}
     {BTS(b) }   b = TRIPLESEP     { ATS(b,setFirstTripleSeparator)} 
     {BNTS(c)}   c = simpleIdtf    { ANTS(c,setSecondIdentifier)}
     {BTS(d) }   d = TRIPLESEP     { ATS(d,setSecondTripleSeparator)}
     {BNTS(e)}   e = simpleIdtf    { ANTS(e,setThirdIdentifier)}
;


attrsList returns [AttributesListAST* retPtr]
  // rule: ( simpleIdtf_attrsep )*
	@init
		{
		  retPtr = new AttributesListAST();
		  INIT_RULE(retPtr);
		}
	@after{ CODE_AFTER_RULE }
:  
      ( {BNTS(a)} a = simpleIdtf_attrsep  {ANTS(a,addIdentifier)} )* //attention
;


simpleIdtf_attrsep returns[SimpleIdtfrWAttrSepAST *retPtr]
  //rule: simpleIdtf ATTRSEP
  @init
	  {
	    retPtr = new SimpleIdtfrWAttrSepAST();
	    INIT_RULE(retPtr);
	  }
	 @after{ CODE_AFTER_RULE }
: 
    {BNTS(a)}  a = simpleIdtf  { ANTS(a,setIdentifier)}
    {BTS(b) }  b = ATTRSEP     { ATS(b,setAttributeSeparator)}
;
    
    
objectList returns [ObjectListAST* retPtr]
  //rule: idtfWithInt ( objsep_IdtfWithInt )* 
	@init
		{
		  retPtr = new ObjectListAST();
		  INIT_RULE(retPtr);
		}
	@after{ CODE_AFTER_RULE }
: 
          {BNTS(a)}  a = idtfWithInt        { ANTS(a,setIdentifierWithInt)}
        ( {BNTS(b)}  b = objsep_IdtfWithInt { ANTS(b,addIdentifier)} )* //attention
;



objsep_IdtfWithInt returns[ObjSepWIdtfWithInt* retPtr]
  //rule: OBJSEP idtfWithInt
  @init
	  {
	    retPtr = new ObjSepWIdtfWithInt();
	    INIT_RULE(retPtr);
	  }
	@after{ CODE_AFTER_RULE }
: 
    {BTS(a) }  a = OBJSEP        { ATS(a,setObjectSeparator)}
    {BNTS(b)}  b = idtfWithInt   { ANTS(b,setIdentifierWithInternal)}
;

    
intSentence returns [InternalSentenceAST* retPtr]
  //rule: CONNECTORS attrsList  objectList 
	@init
		{
		  retPtr = new InternalSentenceAST();
		  INIT_RULE(retPtr);
		}
	@after{ CODE_AFTER_RULE }
: 
        {BTS(a) }  a = CONNECTORS   { ATS(a,setConnector)}
        {BNTS(b)}  b = attrsList    { ANTS(b,setAttributeList)}
        {BNTS(c)}  c = objectList   { ANTS(c,setObjectList)}
;
   

intSentenceList returns [InternalSentenceListAST* retPtr]
  // rule: LPAR_INT ( intSentence_sentsep )+  RPAR_INT
	@init
		{
		  retPtr = new InternalSentenceListAST();
		  INIT_RULE(retPtr);
		}
	@after{ CODE_AFTER_RULE }
: 
          {BTS(a) }  a = LPAR_INT               { ATS(a,setLeftInternalSeparator)}
        ( {BNTS(b)}  b = intSentence_sentsep    { ANTS(b,addSentence)}   )+ // Attention 
          {BTS(c) }  c = RPAR_INT               { ATS(c,setRigthInternalSeparator)} 
;

intSentence_sentsep returns[IntSentenceWSentSep* retPtr]
  // rule: intSentence SENTSEP
	@init
		{
		  retPtr = new IntSentenceWSentSep();
		  INIT_RULE(retPtr);
		} 
	@after{ CODE_AFTER_RULE } 
:  
    {BNTS(a)}  a = intSentence         { ANTS(a,setInternalSentence)} 
    {BTS(b) }  b = SENTSEP             { ATS(b,setSentenceSeparator)}
;

internal returns [InternalAST* retPtr]
  // rule: intSentenceList
	@init
		{
		  retPtr = new InternalAST();
		  INIT_RULE(retPtr);
		}
	@after{ CODE_AFTER_RULE }
:  
   {BNTS(a)}   a = intSentenceList    { ANTS(a,setInternalSentenceList)}
;
    
triple returns [TripleAST* retPtr]
   //rule: LPAR idtf CONTENT idtf  RPAR
   @init
    {
      retPtr = new TripleAST();
      INIT_RULE(retPtr);
    }
   @after{ CODE_AFTER_RULE }
: 
      {BTS(a) }  a = LPAR      { ATS(a,setLeftPar)} 
      {BNTS(b)}  b = idtf      { ANTS(b,setFirstIdentifier)}
      {BTS(c) }  c = CONTENT   { ATS(c,setContent)} 
      {BNTS(d)}  d = idtf      { ANTS(d,setSecondIdentifier)}
      {BTS(e) }  e = RPAR      { ATS(e,setRighPar)} 
;

alias returns [AliasAST* retPtr]
  //rule: ALIASNONAME
	@init
		{
		  retPtr = new AliasAST();
		  INIT_RULE(retPtr);
		}
	@after{ CODE_AFTER_RULE }
    
: 
      {BTS(a) }  a = ALIASNONAME       { ATS(a,setAlias)}
;
    
    
setIdtf returns [SetIdentifierAST* retPtr]
  //rule: LPAR_SET attrsList idtfWithInt ( objsep_AttrsList_idtfWithInt )*   RPAR_SET
	@init
		{
		  retPtr = new SetIdentifierAST();
		  INIT_RULE(retPtr);
		}
	@after{ CODE_AFTER_RULE }
: 
        {BTS(a) }  a = LPAR_SET                             { ATS(a,setLeftSeparator) }
        {BNTS(b)}  b = attrsList                            { ANTS(b,setAttributeList) }
        {BNTS(c)}  c = idtfWithInt                          { ANTS(c,setIdentifier) }
      ( {BNTS(d)}  d =  objsep_AttrsList_idtfWithInt        { ANTS(d,addSentence) } )* //attention  
        {BTS(e) }  e = RPAR_SET                             { ATS(e,setRightSeparator)}
;

objsep_AttrsList_idtfWithInt returns[ObjSepWAttrListWIdtfWithInt* retPtr]
  // rule: OBJSEP attrsList idtfWithInt
	@init
		{
		  retPtr = new ObjSepWAttrListWIdtfWithInt();
		  INIT_RULE(retPtr);
		}
	@after{ CODE_AFTER_RULE }
: 
	  {BTS(a) }  a = OBJSEP         { ATS(a,setSeparator)} 
	  {BNTS(b)}  b = attrsList      { ANTS(b,setAttributeList)}
	  {BNTS(c)}  c = idtfWithInt    { ANTS(c,setIdentifier)}
;

   
osetIdtf returns [OSetIdentifierAST* retPtr]
    //rule: LPAR_OSET attrsList idtfWithInt (objsep_AttrsList_idtfWithInt)* RPAR_OSET
	@init
		{
		  retPtr = new OSetIdentifierAST();
		  INIT_RULE(retPtr);
		}
	@after{ CODE_AFTER_RULE }
:   
        {BTS(a) }  a = LPAR_OSET                               { ATS(a,setLeftSeparator)   }
        {BNTS(b)}  b = attrsList                               { ANTS(b,setAttributeList)  }
        {BNTS(c)}  c = idtfWithInt                             { ANTS(c,setIdentifier)      }  
      ( {BNTS(d)}  d = objsep_AttrsList_idtfWithInt            { ANTS(d,addSentence)    }  )* //attention
        {BTS(e) }  e = RPAR_OSET                               { ATS(e,setRightSeparator)               }
;

anyIdtf returns [AnyIdentifierAST* retPtr]
  @init
		{
		  retPtr = new AnyIdentifierAST();
		  INIT_RULE(retPtr);
		}
	@after{ CODE_AFTER_RULE }
    :  
        {BNTS(a)} a=simpleIdtf    { ANTS(a,setSimpleIdentifier) }
      | {BTS(b) } b=CONTENT       { ATS(b,setContent)           }
      | {BNTS(c)} c=triple        { ANTS(c,setTriple)           }
      | {BNTS(d)} d=setIdtf       { ANTS(d,setSetIdentifier)    }
      | {BNTS(e)} e=osetIdtf      { ANTS(e,setOSetIdentifier)   }
      | {BNTS(f)} f=alias         { ANTS(f,setAlias)            }
    ;
    
   
   
idtf returns [IdentifierAST* retPtr]
		@init
			{
			  retPtr = new IdentifierAST();
			  INIT_RULE(retPtr);
			}
		@after{ CODE_AFTER_RULE }
: 
    {BNTS(a)}  a = anyIdtf     { ANTS(a,setIdentifier) }
;

simpleIdtf returns [SimpleIdentifierAST* retPtr]
    // rule: NAME | URL
		@init
			{
			  retPtr = new SimpleIdentifierAST();
			  INIT_RULE(retPtr);
			} 
		@after{ CODE_AFTER_RULE }
		
:
     {BTS(a) } a = NAME {  ATS(a,setName)  } 
   | {BTS(b) } b = URL  {  ATS(b,setUrl)   } 
;

  

idtfWithInt returns [IdentifierWithInternalAST* retPtr]
  // rule: idtf internal?
	@init
	{
	  retPtr = new IdentifierWithInternalAST();
	  INIT_RULE(retPtr);
	} 
	@after{ CODE_AFTER_RULE }
:  
      {BNTS(a)}  a = idtf        { ANTS(a,setIdentifier)   }
    ( {BNTS(b)}  b = internal    { ANTS(b,setInternal)     } )? // ?
;
  

CONTENT
	: '[' ( options {greedy=false;} : . )* ']'	
	;
  
ELEMTYPE
    : 'sc_arc_main'
    | 'sc_arc_common'
    | 'sc_link'
    | 'sc_node'
    | 'sc_edge'
    | 'sc_arc_access'
    ;

URL :
  '"' (~('"'))* '"'
;


TRIPLESEP
    : '|'
    ;
    
ATTRSEP
    : ':'
    ;
    
OBJSEP
    : ';'
    ;
    
SENTSEP
    : ';;'
    ;
    
SYNSEP
    : '='
    ;
    
LPAR
    : '('
    ;
    
RPAR
    : ')'
    ;

ALIASNONAME
    : '****'
    ;

LPAR_SET
    : '{'
    ;

RPAR_SET
    : '}'
    ;

LPAR_OSET
    : '<'
    ;

RPAR_OSET    
    : '>'
    ;

LPAR_TRF
    : '['
    ;

RPAR_TRF    
    : ']'
    ;

LPAR_INT
    : '(*'
    ;

RPAR_INT    
    : '*)'
    ;

 

CONNECTORS  :
                '<>'
              | '>'
              | '<'
              | '..>'
              | '<..'
              | '->'
              | '<-'
              | '<=>'
              | '=>'
              | '<='
              | '-|>'
              | '<|-'
              | '-/>'
              | '</-'
              | '~>'
              | '<~'
              | '~|>'
              | '<|~'
              | '~/>'
              | '</~'
              | '='
              | '_<>'
              | '_>'
              | '_<'
              | '_..>'
              | '_<..'
              | '_->'
              | '_<-'
              | '_<=>'
              | '_=>'
              | '_<='
              | '_-|>'
              | '_<|-'
              | '_-/>'
              | '_</-'
              | '_~>'
              | '_<~'
              | '_~|>'
              | '_<|~'
              | '_~/>'
              | '_</~'
              | '_='
              
;


NAME
    :    ( 'a'..'z'|'A'..'Z'|'0'..'9'| '_' | '#' | '.' )+
    ;


COMMENT
    :   '//' ~('\n'|'\r')* '\r'? '\n' {$channel=HIDDEN;}
    |   '/!*' ( options {greedy=false;} : . )* '*/' {$channel=HIDDEN;}
    ;

WS  :   ( ' '
        | '\t'
        | '\r'
        | '\n'
        ) {$channel=HIDDEN;}
    ;
