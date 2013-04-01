grammar SCs;

options
{
    language = Cpp;
    backtrack = true;
    k = 2;
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
		  SyntaxAST* syntax = new SyntaxAST();
		}
: 
      ( a = sentence_sentsep  {if(!this->hasException()) syntax->addSentence($a.retPtr); }  )*  EOF//attention
;
 
sentence_sentsep returns[SentenceWithSeparator* retPtr]
  //rule: entence SENTSEP
  @init
		{
		    retPtr = new SentenceWithSeparator();
		}  
:
      a = sentence {retPtr->setSentence($a.retPtr);                         }
      b = SENTSEP  {retPtr->setSeparator(QString::fromStdString($b.text));  } 
;

sentence  returns [SentenceAST* retPtr]
  //rule: sentence_lv1 | sentence_lv23456
	@init
		{
		  retPtr = new SentenceAST();
		}
: 
          a = sentence_lv1        {retPtr->addSentenceLvl1($a.retPtr);        }
      |   b = sentence_lv23456    {retPtr->addSentenceLv234561($b.retPtr);    }
;


sentence_lv23456 returns [SentenceLv234561AST* retPtr]
  //rule: idtf CONNECTORS   attrsList objectList
	@init
		{
		  retPtr = new SentenceLv234561AST();
		}
: 
      a = idtf            {retPtr->setIdentifier($a.retPtr);                       }
      b = CONNECTORS      {retPtr->setConnector(QString::fromStdString($b.text));  } 
      c = attrsList       {retPtr->setAttributeList($c.retPtr);                    }
      d = objectList      {retPtr->setObjectList($d.retPtr);                       }
;


// add type to simpleidtf
sentence_lv1 returns [SentenceLvl1AST* retPtr]
  //rule: simpleIdtf TRIPLESEP simpleIdtf TRIPLESEP simpleIdtf 
	@init
		{
		  retPtr = new SentenceLvl1AST();
		}
: 
        a = simpleIdtf    {retPtr->setFirstIdentifier($a.retPtr);                             }
        b = TRIPLESEP     {retPtr->setFirstTripleSeparator(QString::fromStdString($b.text));  } 
        c = simpleIdtf    {retPtr->setSecondIdentifier($c.retPtr);                            }
        d = TRIPLESEP     {retPtr->setSecondTripleSeparator(QString::fromStdString($d.text)); }
        e = simpleIdtf    {retPtr->setThirdIdentifier($e.retPtr);                             }
;


attrsList returns [AttributesListAST* retPtr]
  // rule: ( simpleIdtf_attrsep )*
	@init
		{
		  retPtr = new AttributesListAST();
		}
:  
      ( a = simpleIdtf_attrsep  {retPtr->addIdentifier($a.retPtr); } )* //attention
;


simpleIdtf_attrsep returns[SimpleIdtfrWAttrSepAST *retPtr]
  //rule: simpleIdtf ATTRSEP
  @init
	  {
	    retPtr = new SimpleIdtfrWAttrSepAST();
	  }
: 
      a = simpleIdtf  {retPtr->setIdentifier($a.retPtr);                 }
      b = ATTRSEP     {retPtr->setAttributeSeparator(QString::fromStdString($b.text)); }
;
    
    
objectList returns [ObjectListAST* retPtr]
  //rule: idtfWithInt ( objsep_IdtfWithInt )* 
	@init
		{
		  retPtr = new ObjectListAST();
		}
: 
          a = idtfWithInt        {retPtr->setIdentifierWithInt($a.retPtr);  }
        ( b = objsep_IdtfWithInt {retPtr->addIdentifier($b.retPtr);         } )* //attention
;



objsep_IdtfWithInt returns[ObjSepWIdtfWithInt* retPtr]
  //rule: OBJSEP idtfWithInt
  @init
	  {
	    retPtr = new ObjSepWIdtfWithInt();
	  }
: 
      a = OBJSEP        {retPtr->setObjectSeparator(QString::fromStdString($a.text));  }
      b = idtfWithInt   {retPtr->setIdentifierWithInternal($b.retPtr);                 }
;

    
intSentence returns [InternalSentenceAST* retPtr]
  //rule: CONNECTORS attrsList  objectList 
	@init
		{
		  retPtr = new InternalSentenceAST();
		}
: 
        a = CONNECTORS   {retPtr->setConnector(QString::fromStdString($a.text));  }
        b = attrsList    {retPtr->setAttributeList($b.retPtr);  }
        c = objectList   {retPtr->setObjectList($c.retPtr);  }
;
   

intSentenceList returns [InternalSentenceListAST* retPtr]
  // rule: LPAR_INT ( intSentence_sentsep )+  RPAR_INT
	@init
		{
		  retPtr = new InternalSentenceListAST();
		}
: 
          a = LPAR_INT               {retPtr->setLeftInternalSeparator(QString::fromStdString($a.text));  }
        ( b = intSentence_sentsep    {retPtr->addSentence($b.retPtr);                                     }   )+ // Attention 
          c = RPAR_INT               {retPtr->setRigthInternalSeparator(QString::fromStdString($c.text)); } 
;

intSentence_sentsep returns[IntSentenceWSentSep* retPtr]
  // rule: intSentence SENTSEP
	@init
		{
		  retPtr = new IntSentenceWSentSep();
		}  
:  
    a = intSentence         {  retPtr->setInternalSentence($a.retPtr);                         } 
    b = SENTSEP             {  retPtr->setSentenceSeparator(QString::fromStdString($b.text));  }
;

internal returns [InternalAST* retPtr]
  // rule: intSentenceList
	@init
		{
		  retPtr = new InternalAST();
		}
:  
    a = intSentenceList    {  retPtr->setInternalSentenceList($a.retPtr);   }
;
    
triple returns [TripleAST* retPtr]
   //rule: LPAR idtf CONTENT idtf  RPAR
   @init
    {
      retPtr = new TripleAST();
    }
: 
      a = LPAR      {  retPtr->setLeftPar(QString::fromStdString($a.text));   } 
      b = idtf      {  retPtr->setFirstIdentifier($b.retPtr);                 }
      c = CONTENT   {  retPtr->setContent(QString::fromStdString($c.text));   } 
      d = idtf      {  retPtr->setSecondIdentifier($d.retPtr);                }
      e = RPAR      {  retPtr->setRighPar(QString::fromStdString($e.text));   } 
;

alias returns [AliasAST* retPtr]
  //rule: ALIASNONAME
	@init
		{
		  retPtr = new AliasAST();
		}
    
: 
      a = ALIASNONAME       {   retPtr->setAlias(QString::fromStdString($a.text)); }
;
    
    
setIdtf returns [SetIdentifierAST* retPtr]
  //rule: LPAR_SET attrsList idtfWithInt ( objsep_AttrsList_idtfWithInt )*   RPAR_SET
	@init
		{
		  retPtr = new SetIdentifierAST();
		}
: 
       a = LPAR_SET                             {   retPtr->setLeftSeparator(QString::fromStdString($a.text));    }
       b = attrsList                            {   retPtr->setAttributeList($b.retPtr);                          }
       c = idtfWithInt                          {   retPtr->setIdentifier($c.retPtr);                             }
      (d =  objsep_AttrsList_idtfWithInt        {   retPtr->addSentence($d.retPtr);                               }  )* //attention  
       e = RPAR_SET                             {   retPtr->setRightSeparator(QString::fromStdString($e.text));   }
;

objsep_AttrsList_idtfWithInt returns[ObjSepWAttrListWIdtfWithInt* retPtr]
  // rule: OBJSEP attrsList idtfWithInt
	@init
		{
		  retPtr = new ObjSepWAttrListWIdtfWithInt();
		}
: 
	  a = OBJSEP         {   retPtr->setSeparator(QString::fromStdString($a.text));    } 
	  b = attrsList      {   retPtr->setAttributeList($b.retPtr);                      }
	  c = idtfWithInt    {   retPtr->setIdentifier($c.retPtr);                         }
;

   
osetIdtf returns [OSetIdentifierAST* retPtr]
    //rule: LPAR_OSET attrsList idtfWithInt (objsep_AttrsList_idtfWithInt)* RPAR_OSET
	@init
		{
		  retPtr = new OSetIdentifierAST();
		}
:   
        a = LPAR_OSET                               {  retPtr->setLeftSeparator(QString::fromStdString($a.text));   }
        b = attrsList                               {  retPtr->setAttributeList($b.retPtr);                         }
        c = idtfWithInt                             {  retPtr->setIdentifier($c.retPtr);                            }  
      ( d = objsep_AttrsList_idtfWithInt            {  retPtr->addSentence($d.retPtr);                              }  )* //attention
        e = RPAR_OSET                               {  retPtr->setRightSeparator(QString::fromStdString($e.text));  }
;

anyIdtf returns [AnyIdentifierAST* retPtr]
@init{
  retPtr = new AnyIdentifierAST();
}
    :  
        a=simpleIdtf    {  retPtr->setSimpleIdentifier( $a.retPtr );             }
      | b=CONTENT       {  retPtr->setContent(QString::fromStdString($b.text));  }
      | c=triple        {  retPtr->setTriple($c.retPtr);                         }
      | d=setIdtf       {  retPtr->setSetIdentifier($d.retPtr);                  }
      | e=osetIdtf      {  retPtr->setOSetIdentifier($e.retPtr);                 }
      | f=alias         {  retPtr->setAlias($f.retPtr);                          }
    ;
    
   
   
idtf returns [IdentifierAST* retPtr]
		@init
		{
		  retPtr = new IdentifierAST();
		}
: 
    a = anyIdtf     { retPtr->setIdentifier($a.retPtr); }
;

simpleIdtf returns [SimpleIdentifierAST* retPtr]
    // rule: NAME | URL
		@init
		{
		  retPtr = new SimpleIdentifierAST();
		} 
:
     NAME { retPtr->setName(QString::fromStdString($NAME.text));  } 
   | URL  { retPtr->setUrl(QString::fromStdString($URL.text));  } 
;

  

idtfWithInt returns [IdentifierWithInternalAST* retPtr]
  // rule: idtf internal?
	@init
	{
	  retPtr = new IdentifierWithInternalAST();
	} 
:  
      a = idtf       {  retPtr->setIdentifier($a.retPtr);  }
    ( b= internal    {  retPtr->setInternal($b.retPtr);  } )? // ?
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
