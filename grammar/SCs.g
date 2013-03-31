grammar SCs;

options
{
    language = Cpp;
    backtrack = true;
    k = 5;
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
    : ( sentence SENTSEP )*
    ;
   

sentence  returns [SentenceAST *retPtr]
@init{
  retPtr = NULL;
}
    : sentence_lv1 | sentence_lv23456
    ;


sentence_lv23456 returns [SentenceLv234561AST *retPtr]
@init{
  retPtr = NULL;
}
    : idtf CONNECTORS   attrsList objectList
    ;


// add type to simpleidtf
sentence_lv1 returns [SentenceLvl1AST *retPtr]
@init{
  retPtr = NULL;
}
    : simpleIdtf TRIPLESEP simpleIdtf TRIPLESEP simpleIdtf 
    ;


attrsList returns [AttributesListAST *retPtr]
@init{
  retPtr = NULL;
}
    :  ( simpleIdtf_attrsep )*
    ;


simpleIdtf_attrsep
: simpleIdtf ATTRSEP
;
    
    
objectList returns [ObjectListAST *retPtr]
@init{
  retPtr = NULL;
}
    : idtfWithInt ( objsep_IdtfWithInt )*
    ;

objsep_IdtfWithInt
  : OBJSEP idtfWithInt
  ;

    
intSentence returns [InternalSentenceAST *retPtr]
@init{
  retPtr = NULL;
}
    : CONNECTORS attrsList  objectList 
    ;
   

intSentenceList returns [InternalSentenceListAST *retPtr]
@init{
  retPtr = NULL;
}
    : LPAR_INT ( intSentence_sentsep )+  RPAR_INT
    ;

intSentence_sentsep
:  intSentence SENTSEP
;

internal returns [InternalAST *retPtr]
@init{
  retPtr = NULL;
}
    :  intSentenceList
    ;
    
triple returns [TripleAST *retPtr]
@init{
  retPtr = new TripleAST();
}
    : LPAR a=idtf { retPtr->setFirstIdentifier($a.retPtr); } CONTENT b=idtf { retPtr->setFirstIdentifier($a.retPtr); }  RPAR
    ;

alias returns [AliasAST *retPtr]
@init{c
  retPtr = NULL;
}
    : ALIASNONAME
    ;
    
// LPAR_SET (attrsList idtfWithInt OBJSEP )*   attrsList idtfWithInt  RPAR_SET
setIdtf returns [SetIdentifierAST *retPtr]
@init{
  retPtr = NULL;
}
    //: LPAR_SET (attrsList idtfWithInt OBJSEP? )*   RPAR_SET
    : LPAR_SET attrsList idtfWithInt ( objsep_AttrsList_idtfWithInt )*   RPAR_SET
    ;

objsep_AttrsList_idtfWithInt
: OBJSEP attrsList idtfWithInt
;

// LPAR_OSET ( attrsList idtfWithInt OBJSEP )*  attrsList  idtfWithInt RPAR_OSET    
osetIdtf returns [OSetIdentifierAST *retPtr]
@init{
  retPtr = NULL;
}
    //: LPAR_OSET ( attrsList idtfWithInt OBJSEP? )*  RPAR_OSET
    : LPAR_OSET attrsList idtfWithInt  (objsep_AttrsList_idtfWithInt)*  RPAR_OSET
    ;

anyIdtf returns [AnyIdentifierAST *retPtr]
@init{
  retPtr = NULL;
}
    :  
        simpleIdtf
      | CONTENT
      | triple
      | setIdtf
      | osetIdtf
      | alias
    ;
    
    
idtf returns [IdentifierAST *retPtr]
@init{
  retPtr = NULL;
}
    : anyIdtf {}
    ;

simpleIdtf returns [SimpleIdentifierAST *retPtr]
@init{
  retPtr = new SimpleIdentifierAST();
} 
:
     NAME { retPtr->setName(QString::fromStdString($NAME.text));  } 
   | URL  { retPtr->setUrl(QString::fromStdString($URL.text));  } 
;

  

idtfWithInt returns [IdentifierWithInternalAST *retPrt]
@init{
  //retPtr = new IdentifierWithInternalAST();
}
    :  idtf internal? 
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
