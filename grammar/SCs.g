grammar SCs;

options
{
    language = Cpp;
    backtrack = true;
}

@lexer::includes
{
  #include <list>
}

@parser::includes
{
   #include "SCsLexer.hpp"
   #include <list>
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
   

sentence 
    : sentence_lv1 | sentence_lv23456
    ;


sentence_lv23456
    : idtf CONNECTORS attrsList objectList
    ;

// add type to simpleidtf
sentence_lv1
    : simpleIdtf TRIPLESEP simpleIdtf TRIPLESEP simpleIdtf 
    ;


attrsList
    :  (simpleIdtf ATTRSEP)*
    ;
    
objectList
    : idtfWithInt (OBJSEP idtfWithInt)*
    ;
    
    
intSentence
    : CONNECTORS attrsList  objectList 
    ;

intSentenceList
    : LPAR_INT ( intSentence SENTSEP)+  RPAR_INT
    ;

internal
    :  intSentenceList
    ;
    
triple
    : LPAR idtf CONTENT idtf RPAR
    ;

alias
    : ALIASNONAME
    ;
// LPAR_SET (attrsList idtfWithInt OBJSEP )*   attrsList idtfWithInt  RPAR_SET
setIdtf
    : LPAR_SET (attrsList idtfWithInt OBJSEP? )*   RPAR_SET
    ;

// LPAR_OSET ( attrsList idtfWithInt OBJSEP )*  attrsList  idtfWithInt RPAR_OSET    
osetIdtf
    : LPAR_OSET ( attrsList idtfWithInt OBJSEP? )*  RPAR_OSET
    ;

anyIdtf
    :  
        simpleIdtf
      | CONTENT
      | triple
      | setIdtf
      | osetIdtf
      | alias
    ;
    
    
idtf
    : anyIdtf
    ;

simpleIdtf  :
   (ELEMTYPE '/')?  NAME | URL 
;

  

idtfWithInt
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
              | '_<=>'
              | '='
              | '=>'
              | '<='
              | '_=>'
              | '_<='
              | '_->'
              | '_<-'
              | '-|>'
              | '<|-'
              | '_-|>'
              | '_<|-'
              | '-/>'
              | '</-'
              | '_-/>'
              | '_</-'
              | '~>'
              | '<~'
              | '_~>'
              | '_<~'
              | '~|>'
              | '<|~'
              | '_~|>'
              | '_<|~'
              | '~/>'
              | '</~'
              | '_~/>'
              | '_</~'
              
;


NAME
    :    ( 'a'..'z'|'A'..'Z'|'0'..'9'| '_')+
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
