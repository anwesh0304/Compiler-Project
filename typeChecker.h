#ifndef _typechecker
#define _typechecker

#include "lexerDef.h"
#include "ast.h"


struct _baseST ;
struct _moduleST ;
struct _varST ;
typedef struct _baseST baseST ;
typedef struct _moduleST moduleST ;
typedef struct _varST varST ;

// <var> checker
int validVarIndex (baseST *realBase, moduleST *baseModule, astNode *varIndexASTNode) ;
int validStaticArrStaticIndex (baseST *realBase, moduleST *baseModule, varST *arrVar, astNode *indASTNode) ;
tokenID validateVar (baseST *realBase , moduleST *baseModule , astNode *varASTNode, varST **searchedVar) ;
int isLeftLimStatic (varST *arrayVar) ;
int isRightLimStatic (varST *arrayVar) ;
int isVarStaticArr (varST *arrayVar) ;

// Overall function
void assignmentTypeCheck (baseST *realBase, moduleST *baseModule, astNode *assignopASTNode) ;

// expression checker
int isArithmeticType (tokenID id) ;
int isLogicalOp (tokenID id) ;
int isRelationalOp (tokenID id) ;
int isArithmeticType (tokenID id) ;
tokenID getExpressionType (baseST *realBase, moduleST *baseModule, astNode *exprNode) ;

#endif