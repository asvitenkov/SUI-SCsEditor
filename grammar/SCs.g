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
@int{
  retPtr = NULL;
}
    : sentence_lv1 | sentence_lv23456
    ;


sentence_lv23456 returns [SentenceLv234561AST *retPtr]
@int{
  retPtr = NULL;
}
    : idtf CONNECTORS   attrsList objectList
    ;


// add type to simpleidtf
sentence_lv1 returns [SentenceLvl1AST *retPtr]
@int{
  retPtr = NULL;
}
    : simpleIdtf TRIPLESEP simpleIdtf TRIPLESEP simpleIdtf 
    ;


attrsList returns [AttributesListAST *retPtr]
@int{
  retPtr = NULL;
}
    :  (simpleIdtf ATTRSEP)*
    ;
    
objectList returns [ObjectListAST *retPtr]
@int{
  retPtr = NULL;
}
    : idtfWithInt (OBJSEP idtfWithInt)*
    ;
    
intSentence returns [InternalSentenceAST *retPtr]
@int{
  retPtr = NULL;
}
    : CONNECTORS attrsList  objectList 
    ;
   

intSentenceList returns [InternalSentenceListAST *retPtr]
@int{
  retPtr = NULL;
}
    : LPAR_INT ( intSentence SENTSEP)+  RPAR_INT
    ;

internal returns [InternalAST *retPtr]
@int{
  retPtr = NULL;
}
    :  intSentenceList
    ;
    
triple returns [TripleAST *retPtr]
@int{
  retPtr = NULL;
}
    : LPAR idtf CONTENT idtf RPAR
    ;

alias returns [AliasAST *retPtr]
@int{
  retPtr = NULL;
}
    : ALIASNONAME
    ;
// LPAR_SET (attrsList idtfWithInt OBJSEP )*   attrsList idtfWithInt  RPAR_SET
setIdtf returns [SetIdentifierAST *retPtr]
@int{
  retPtr = NULL;
}
    : LPAR_SET (attrsList idtfWithInt OBJSEP? )*   RPAR_SET
    ;

// LPAR_OSET ( attrsList idtfWithInt OBJSEP )*  attrsList  idtfWithInt RPAR_OSET    
osetIdtf returns [OSetIdentifierAST *retPtr]
@int{
  retPtr = NULL;
}
    : LPAR_OSET ( attrsList idtfWithInt OBJSEP? )*  RPAR_OSET
    ;

anyIdtf returns [AnyIdentifierAST *retPtr]
@int{
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
@int{
  retPtr = NULL;
}
    : anyIdtf {}
    ;

simpleIdtf returns [SimpleIdentifierAST *retPtr]
@int{
  retPtr = NULL;
} 
:
   NAME | URL 
;

  

idtfWithInt returns [IdentifierWithInternalAST *retPrt]
@int{
  retPtr = NULL;
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
