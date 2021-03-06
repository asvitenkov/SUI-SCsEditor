/** \file
 *  This C++ header file was generated by $ANTLR version 3.4
 *
 *     -  From the grammar source file : D:\\Programming\\PROJECTS\\Eclipse\\workspace\\ScsGrammar\\src\\SCs.g
 *     -                            On : 2013-04-08 06:21:29
 *     -                for the parser : SCsParserParser
 *
 * Editing it, at least manually, is not wise.
 *
 * C++ language generator and runtime by Gokulakannan Somasundaram ( heavy lifting from C Run-time by Jim Idle )
 *
 *
 * The parser 
SCsParser

has the callable functions (rules) shown below,
 * which will invoke the code for the associated rule in the source grammar
 * assuming that the input stream is pointing to a token/text stream that could begin
 * this rule.
 *
 * For instance if you call the first (topmost) rule in a parser grammar, you will
 * get the results of a full parse, but calling a rule half way through the grammar will
 * allow you to pass part of a full token stream to the parser, such as for syntax checking
 * in editors and so on.
 *
 */
// [The "BSD license"]
// Copyright (c) 2005-2009 Gokulakannan Somasundaram. 
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. The name of the author may not be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef	_SCsParser_H
#define _SCsParser_H
/* =============================================================================
 * Standard antlr3 C++ runtime definitions
 */
#include    <antlr3.hpp>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */



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
  if(ptr!=NULL && mHasException==false) {pName->methodName(QString::fromStdString(ptr->getText()));} \
  else {pName->methodName##Error();} \
  CHECK_EXCEPTION \
  IFNRR 
// after non terminal symbol
#define ANTS(ptr,methodName) \
  if(ptr!=NULL && mHasException==false) {pName->methodName(ptr);} \
  else {pName->methodName##Error();} \
  IFNRR 
#define CODE_AFTER_RULE CHECK_EXCEPTION





#ifdef	WIN32
// Disable: Unreferenced parameter,							- Rules with parameters that are not used
//          constant conditional,							- ANTLR realizes that a prediction is always true (synpred usually)
//          initialized but unused variable					- tree rewrite variables declared but not needed
//          Unreferenced local variable						- lexer rule declares but does not always use _type
//          potentially unitialized variable used			- retval always returned from a rule
//			unreferenced local function has been removed	- susually getTokenNames or freeScope, they can go without warnigns
//
// These are only really displayed at warning level /W4 but that is the code ideal I am aiming at
// and the codegen must generate some of these warnings by necessity, apart from 4100, which is
// usually generated when a parser rule is given a parameter that it does not use. Mostly though
// this is a matter of orthogonality hence I disable that one.
//
#pragma warning( disable : 4100 )
#pragma warning( disable : 4101 )
#pragma warning( disable : 4127 )
#pragma warning( disable : 4189 )
#pragma warning( disable : 4505 )
#pragma warning( disable : 4701 )
#endif
	namespace  SCsParserNS  {


typedef SCsParserTraits SCsParserImplTraits;


class SCsParserTokens
{
public:
	/** Symbolic definitions of all the tokens that the 
parser
 will work with.
	 * \{
	 *
	 * Antlr will define EOF, but we can't use that as it it is too common in
	 * in C header files and that would be confusing. There is no way to filter this out at the moment
	 * so we just undef it here for now. That isn't the value we get back from C recognizers
	 * anyway. We are looking for ANTLR_TOKEN_EOF.
	 */
	enum Tokens 
	{
		EOF_TOKEN = SCsParserImplTraits::CommonTokenType::TOKEN_EOF
		, ALIASNONAME = 4 
		, ATTRSEP = 5 
		, COMMENT = 6 
		, CONNECTORS = 7 
		, CONTENT = 8 
		, ELEMTYPE = 9 
		, LPAR = 10 
		, LPAR_INT = 11 
		, LPAR_OSET = 12 
		, LPAR_SET = 13 
		, LPAR_TRF = 14 
		, NAME = 15 
		, OBJSEP = 16 
		, RPAR = 17 
		, RPAR_INT = 18 
		, RPAR_OSET = 19 
		, RPAR_SET = 20 
		, RPAR_TRF = 21 
		, SENTSEP = 22 
		, SYNSEP = 23 
		, TRIPLESEP = 24 
		, URL = 25 
		, WS = 26 
	};

};

/** Context tracking structure for 
SCsParser

 */
class SCsParser : public 
SCsParserImplTraits::BaseParserType
, public SCsParserTokens
{
public:
	typedef SCsParserImplTraits ImplTraits;
	typedef SCsParser ComponentType;
	typedef ComponentType::StreamType StreamType;
	typedef 
SCsParserImplTraits::BaseParserType
 BaseType;
	typedef ImplTraits::RecognizerSharedStateType<StreamType> RecognizerSharedStateType;
	typedef StreamType InputType;
	static const bool IsFiltered = false;


private:	
public:
    SCsParser(InputType* instream);
    SCsParser(InputType* instream, RecognizerSharedStateType* state);

    void init(InputType* instream  );

     
     void
     syntax (); 
     
     SentenceWithSeparator*
     sentence_sentsep (); 
     
     SentenceAST*
     sentence (); 
     
     SentenceLv234561AST*
     sentence_lv23456 (); 
     
     SentenceLvl1AST*
     sentence_lv1 (); 
     
     AttributesListAST*
     attrsList (); 
     
     SimpleIdtfrWAttrSepAST *
     simpleIdtf_attrsep (); 
     
     ObjectListAST*
     objectList (); 
     
     ObjSepWIdtfWithInt*
     objsep_IdtfWithInt (); 
     
     InternalSentenceAST*
     intSentence (); 
     
     InternalSentenceListAST*
     intSentenceList (); 
     
     IntSentenceWSentSep*
     intSentence_sentsep (); 
     
     InternalAST*
     internal (); 
     
     TripleAST*
     triple (); 
     
     AliasAST*
     alias (); 
     
     SetIdentifierAST*
     setIdtf (); 
     
     ObjSepWAttrListWIdtfWithInt*
     objsep_AttrsList_idtfWithInt (); 
     
     OSetIdentifierAST*
     osetIdtf (); 
     
     AnyIdentifierAST*
     anyIdtf (); 
     
     IdentifierAST*
     idtf (); 
     
     SimpleIdentifierAST*
     simpleIdtf (); 
     
     IdentifierWithInternalAST*
     idtfWithInt (); 
    // Delegated rules

    const char *    getGrammarFileName();
    void            reset();
    ~SCsParser();
public:
   struct RuntimeParserError
    {
        RuntimeParserError(ANTLR_UINT8 **token, ExceptionBaseType* exception)
            : mToken(token), mException(exception) {}

        ANTLR_UINT8 **mToken;
        ExceptionBaseType* mException;
    };
    void displayRecognitionError( ANTLR_UINT8** tokenNames, ExceptionBaseType* ex )
    {
        //fprintf(stderr,"parser line:%d pos:%d\n",ex->get_line(),ex->get_charPositionInLine());
        mNeedRecover = true;
		mHasException = true;
        mErrorsArray.push_back(new SCsParserException(SCsParserException::PARSER,ex->get_line(),ex->get_charPositionInLine(),(int)ex->getType()));
    }
	std::list<SCsParserException*> getParserErrors(){ return mErrorsArray; }
private:
	std::list<SCsParserException*> mErrorsArray;
    bool mNeedRecover;
	bool mHasException;
	bool mLastExceptionCheked;
	AST* mCurrentNode;
	void recover() 
	{    
		int token = this->LA(1);
		while( token != EOF_TOKEN )
		{
			this->get_rec()->getCurrentInputSymbol(this->get_istream());
			this->get_istream()->consume();
			if(token == SENTSEP)
				break;
			token = this->LA(1);
		}
		mNeedRecover = false;
	}
	bool hasException()
	{
		bool bRes = SCsParserImplTraits::BaseParserType::hasException();
		if(bRes || mHasException)
		{
			this->preporterror();
			this->precover();
			mHasException = true;
			return false;
		}

		return bRes;
	}
	void initRule(AST *node)
	{
		mCurrentNode = node;
	}

};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//

/* End of token definitions for SCsParser
 * =============================================================================
 */
/** } */

	}


#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
