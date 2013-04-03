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
   
   #define RECOVER if(mNeedRecover) this->recover();
   #define IFNR RECOVER
   #define SET_NEED_RECOVER(value) mNeedRecover = value;
   #define SNR(value) SET_NEED_RECOVER(value)
   #define SNRT SET_NEED_RECOVER(true)
   #define SNRF SET_NEED_RECOVER(false)
   #define IFNRR if(mNeedRecover) return retPtr;
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
		  SyntaxAST* syntax = new SyntaxAST();
		}
	@after{ SNRF }
: 
      ( a = sentence_sentsep  { IFNR syntax->addSentence($a.retPtr); }  )*  EOF//attention
;
 
sentence_sentsep returns[SentenceWithSeparator* retPtr]
  //rule: entence SENTSEP
  @init
		{
		    SNRT
		    retPtr = new SentenceWithSeparator();
		}
	@after{ SNRF }	
	 
:
    {SNRT}  a = sentence { IFNRR retPtr->setSentence($a.retPtr);                      }
    {SNRT}  b = SENTSEP  { SNRF retPtr->setSeparator(QString::fromStdString($b.text));} 
;

sentence  returns [SentenceAST* retPtr]
  //rule: sentence_lv1 | sentence_lv23456
	@init
		{
		  SNRT
		  retPtr = new SentenceAST();
		}
	@after{ SNRF }
	
: 
        {SNRT}  a = sentence_lv1        {IFNRR retPtr->addSentenceLvl1($a.retPtr);        }
      | {SNRT}  b = sentence_lv23456    {IFNRR retPtr->addSentenceLv234561($b.retPtr);    }
;


sentence_lv23456 returns [SentenceLv234561AST* retPtr]
  //rule: idtf CONNECTORS   attrsList objectList
	@init
		{
		  SNRT
		  retPtr = new SentenceLv234561AST();
		}
	@after{ SNRF }
	
: 
    {SNRT}  a = idtf            { IFNRR retPtr->setIdentifier($a.retPtr);                       }
    {SNRT}  b = CONNECTORS      { SNRF  retPtr->setConnector(QString::fromStdString($b.text));  } 
    {SNRT}  c = attrsList       { IFNRR retPtr->setAttributeList($c.retPtr);                    }
    {SNRT}  d = objectList      { IFNRR retPtr->setObjectList($d.retPtr);                       }
;


// add type to simpleidtf
sentence_lv1 returns [SentenceLvl1AST* retPtr]
  //rule: simpleIdtf TRIPLESEP simpleIdtf TRIPLESEP simpleIdtf 
	@init
		{
		  SNRT
		  retPtr = new SentenceLvl1AST();
		}
	@after{ SNRF }
	
: 
     {SNRT}   a = simpleIdtf    { IFNRR retPtr->setFirstIdentifier($a.retPtr);                             }
     {SNRT}   b = TRIPLESEP     { SNRF retPtr->setFirstTripleSeparator(QString::fromStdString($b.text));   } 
     {SNRT}   c = simpleIdtf    { IFNRR retPtr->setSecondIdentifier($c.retPtr);                            }
     {SNRT}   d = TRIPLESEP     { SNRF retPtr->setSecondTripleSeparator(QString::fromStdString($d.text));  }
     {SNRT}   e = simpleIdtf    { IFNRR retPtr->setThirdIdentifier($e.retPtr);                             }
;


attrsList returns [AttributesListAST* retPtr]
  // rule: ( simpleIdtf_attrsep )*
	@init
		{
		  SNRT
		  retPtr = new AttributesListAST();
		}
	@after{ SNRF }
:  
      ( {SNRT} a = simpleIdtf_attrsep  {IFNRR retPtr->addIdentifier($a.retPtr); } )* //attention
;


simpleIdtf_attrsep returns[SimpleIdtfrWAttrSepAST *retPtr]
  //rule: simpleIdtf ATTRSEP
  @init
	  {
	    SNRT
	    retPtr = new SimpleIdtfrWAttrSepAST();
	  }
	 @after{ SNRF }
: 
    {SNRT}  a = simpleIdtf  { IFNRR retPtr->setIdentifier($a.retPtr);                 }
    {SNRT}  b = ATTRSEP     { SNRF  retPtr->setAttributeSeparator(QString::fromStdString($b.text)); }
;
    
    
objectList returns [ObjectListAST* retPtr]
  //rule: idtfWithInt ( objsep_IdtfWithInt )* 
	@init
		{
		  SNRT
		  retPtr = new ObjectListAST();
		}
	@after{ SNRF }
: 
          {SNRT}  a = idtfWithInt        { IFNRR retPtr->setIdentifierWithInt($a.retPtr);  }
        ( {SNRT}  b = objsep_IdtfWithInt { IFNRR retPtr->addIdentifier($b.retPtr);         } )* //attention
;



objsep_IdtfWithInt returns[ObjSepWIdtfWithInt* retPtr]
  //rule: OBJSEP idtfWithInt
  @init
	  {
	    SNRT
	    retPtr = new ObjSepWIdtfWithInt();
	  }
	@after{ SNRF }
: 
    {SNRT}  a = OBJSEP        { SNRF  retPtr->setObjectSeparator(QString::fromStdString($a.text));  }
    {SNRT}  b = idtfWithInt   { IFNRR retPtr->setIdentifierWithInternal($b.retPtr);                 }
;

    
intSentence returns [InternalSentenceAST* retPtr]
  //rule: CONNECTORS attrsList  objectList 
	@init
		{
		  SNRT
		  retPtr = new InternalSentenceAST();
		}
	@after{ SNRF }
: 
        {SNRT}  a = CONNECTORS   { SNRF  retPtr->setConnector(QString::fromStdString($a.text));  }
        {SNRT}  b = attrsList    { IFNRR retPtr->setAttributeList($b.retPtr);  }
        {SNRT}  c = objectList   { IFNRR retPtr->setObjectList($c.retPtr);  }
;
   

intSentenceList returns [InternalSentenceListAST* retPtr]
  // rule: LPAR_INT ( intSentence_sentsep )+  RPAR_INT
	@init
		{
		  SNRT
		  retPtr = new InternalSentenceListAST();
		}
	@after{ SNRF }
: 
          {SNRT}  a = LPAR_INT               { SNRF  retPtr->setLeftInternalSeparator(QString::fromStdString($a.text));  }
        ( {SNRT}  b = intSentence_sentsep    { IFNRR retPtr->addSentence($b.retPtr);                                     }   )+ // Attention 
          {SNRT}  c = RPAR_INT               { SNRF  retPtr->setRigthInternalSeparator(QString::fromStdString($c.text)); } 
;

intSentence_sentsep returns[IntSentenceWSentSep* retPtr]
  // rule: intSentence SENTSEP
	@init
		{
		  SNRT
		  retPtr = new IntSentenceWSentSep();
		} 
	@after{ SNRF } 
:  
    {SNRT}  a = intSentence         { IFNRR   retPtr->setInternalSentence($a.retPtr);                         } 
    {SNRT}  b = SENTSEP             { SNRF    retPtr->setSentenceSeparator(QString::fromStdString($b.text));  }
;

internal returns [InternalAST* retPtr]
  // rule: intSentenceList
	@init
		{
		  SNRT
		  retPtr = new InternalAST();
		}
	@after{ SNRF }
:  
   {SNRT}   a = intSentenceList    { IFNRR   retPtr->setInternalSentenceList($a.retPtr);   }
;
    
triple returns [TripleAST* retPtr]
   //rule: LPAR idtf CONTENT idtf  RPAR
   @init
    {
      SNRT
      retPtr = new TripleAST();
    }
   @after{ SNRF }
: 
      {SNRT}  a = LPAR      { SNRF    retPtr->setLeftPar(QString::fromStdString($a.text));   } 
      {SNRT}  b = idtf      { IFNRR   retPtr->setFirstIdentifier($b.retPtr);                 }
      {SNRT}  c = CONTENT   { SNRF    retPtr->setContent(QString::fromStdString($c.text));   } 
      {SNRT}  d = idtf      { IFNRR   retPtr->setSecondIdentifier($d.retPtr);                }
      {SNRT}  e = RPAR      { SNRF    retPtr->setRighPar(QString::fromStdString($e.text));   } 
;

alias returns [AliasAST* retPtr]
  //rule: ALIASNONAME
	@init
		{
		  SNRT
		  retPtr = new AliasAST();
		}
	@after{ SNRF }
    
: 
      {SNRT}  a = ALIASNONAME       { SNRF     retPtr->setAlias(QString::fromStdString($a.text)); }
;
    
    
setIdtf returns [SetIdentifierAST* retPtr]
  //rule: LPAR_SET attrsList idtfWithInt ( objsep_AttrsList_idtfWithInt )*   RPAR_SET
	@init
		{
		  SNRT
		  retPtr = new SetIdentifierAST();
		}
	@after{ SNRF }
: 
        {SNRT}  a = LPAR_SET                             { SNRF     retPtr->setLeftSeparator(QString::fromStdString($a.text));    }
        {SNRT}  b = attrsList                            { IFNRR    retPtr->setAttributeList($b.retPtr);                          }
        {SNRT}  c = idtfWithInt                          { IFNRR    retPtr->setIdentifier($c.retPtr);                             }
      ( {SNRT}  d =  objsep_AttrsList_idtfWithInt        { IFNRR    retPtr->addSentence($d.retPtr);                               }  )* //attention  
        {SNRT}  e = RPAR_SET                             { SNRF     retPtr->setRightSeparator(QString::fromStdString($e.text));   }
;

objsep_AttrsList_idtfWithInt returns[ObjSepWAttrListWIdtfWithInt* retPtr]
  // rule: OBJSEP attrsList idtfWithInt
	@init
		{
		  SNRT
		  retPtr = new ObjSepWAttrListWIdtfWithInt();
		}
	@after{ SNRF }
: 
	  {SNRT}  a = OBJSEP         { SNRF     retPtr->setSeparator(QString::fromStdString($a.text));    } 
	  {SNRT}  b = attrsList      { IFNRR    retPtr->setAttributeList($b.retPtr);                      }
	  {SNRT}  c = idtfWithInt    { IFNRR    retPtr->setIdentifier($c.retPtr);                         }
;

   
osetIdtf returns [OSetIdentifierAST* retPtr]
    //rule: LPAR_OSET attrsList idtfWithInt (objsep_AttrsList_idtfWithInt)* RPAR_OSET
	@init
		{
		  SNRT
		  retPtr = new OSetIdentifierAST();
		}
	@after{ SNRF }
:   
        {SNRT}  a = LPAR_OSET                               {  retPtr->setLeftSeparator(QString::fromStdString($a.text));   }
        {SNRT}  b = attrsList                               { IFNRR   retPtr->setAttributeList($b.retPtr);                         }
        {SNRT}  c = idtfWithInt                             { IFNRR   retPtr->setIdentifier($c.retPtr);                            }  
      ( {SNRT}  d = objsep_AttrsList_idtfWithInt            { IFNRR   retPtr->addSentence($d.retPtr);                              }  )* //attention
        {SNRT}  e = RPAR_OSET                               { SNRF    retPtr->setRightSeparator(QString::fromStdString($e.text));  }
;

anyIdtf returns [AnyIdentifierAST* retPtr]
  @init
		{
		  SNRT
		  retPtr = new AnyIdentifierAST();
		}
	@after{ SNRF }
    :  
        {SNRT} a=simpleIdtf    { IFNRR retPtr->setSimpleIdentifier( $a.retPtr );             }
      | {SNRT} b=CONTENT       { SNRF  retPtr->setContent(QString::fromStdString($b.text));  }
      | {SNRT} c=triple        { IFNRR retPtr->setTriple($c.retPtr);                         }
      | {SNRT} d=setIdtf       { IFNRR retPtr->setSetIdentifier($d.retPtr);                  }
      | {SNRT} e=osetIdtf      { IFNRR retPtr->setOSetIdentifier($e.retPtr);                 }
      | {SNRT} f=alias         { IFNRR retPtr->setAlias($f.retPtr);                          }
    ;
    
   
   
idtf returns [IdentifierAST* retPtr]
		@init
			{
			  SNRT
			  retPtr = new IdentifierAST();
			}
		@after{ SNRF }
: 
    {SNRT}  a = anyIdtf     { IFNRR  retPtr->setIdentifier($a.retPtr); }
;

simpleIdtf returns [SimpleIdentifierAST* retPtr]
    // rule: NAME | URL
		@init
			{
			  SNRT
			  retPtr = new SimpleIdentifierAST();
			} 
		@after{ SNRF }
		
:
     {SNRT} a = NAME {  SNRF retPtr->setName(QString::fromStdString($a.text));  } 
   | {SNRT} b = URL  {  SNRF retPtr->setUrl(QString::fromStdString($b.text));  } 
;

  

idtfWithInt returns [IdentifierWithInternalAST* retPtr]
  // rule: idtf internal?
	@init
	{
	  SNRT
	  retPtr = new IdentifierWithInternalAST();
	} 
	@after{ SNRF }
:  
      {SNRT}  a = idtf        { IFNRR   retPtr->setIdentifier($a.retPtr);  }
    ( {SNRT}  b = internal    { IFNRR   retPtr->setInternal($b.retPtr);  } )? // ?
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
