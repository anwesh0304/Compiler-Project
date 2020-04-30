#ifndef _Codegen
#define _Codegen

#include "ast.h"
#include "symbolTable.h"

typedef enum _textFlags
{
	boundERROR, declERROR, declNegERROR, getValuePrimitive, printInteger
} textFlag ;

typedef enum _dataFlags
{
	boundPrint, declPrint, declNeg, printFormatArray, printInt, printNewLine, printFormat,
	printTrue, printFalse, DATA_true, DATA_false, inputIntPrompt, inputBoolPrompt, inputIntArrPrompt, inputBoolArrPrompt, leftRange, rightRange, inputInt
} dataFlag ;

int get_label() ;

int getStaticOffset (varST *vst, astNode *node, int size) ;
void staticArrBoundCheck (astNode *node, moduleST *lst, varST *vst, FILE *fp) ;
void dynamicArrBoundCheck (astNode *node, moduleST *lst, varST *vst, FILE *fp) ;

void printGetValueStaticArrayPrompt (tokenID baseType , int leftLim, int rightLim, FILE* fp) ;
void printGetValueDynArrayPrompt (varST *vst, FILE *fp) ;

void dynamicArrDX (varST *vst, FILE *fp) ;
void dynamicDeclareCheck (moduleST *lst, varST *searchedVar, FILE *fp) ;
void dynamicDeclareGeneration (moduleST *lst, varST *searchedVar, int declCount, FILE *fp) ;

void IDGeneration (astNode *node, moduleST *lst, FILE* fp) ;

//void printInteger (FILE *fp) ;
void printBoolean (FILE *fp) ;
void printArrayIntBool (tokenID baseType, FILE *fp) ;
void printGeneration (astNode *node, moduleST *lst, FILE *fp) ;

void getValueRSPAlign (FILE *fp) ;
void getValueGeneration (moduleST *lst, varST *searchedVar, int rspDepth, FILE *fp) ;

void preamble (FILE *fp) ;
void postamble (FILE *fp) ;
int isFlagSet (int flagInt, int id) ;

int getCaseCount (astNode *statementsNode) ;
int switchDeclareVars (astNode *statementNode, varST *vst , int rspDepth, FILE* fp) ;
int switchCaseLabels (astNode *node, moduleST *lst, int caseCount , int *caseLabels, FILE* fp) ;


#endif