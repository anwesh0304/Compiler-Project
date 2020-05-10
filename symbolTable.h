#ifndef _SYMBOLTable
#define _SYMBOLTable

#include "lexerDef.h"
#include "ast.h"

#define LOCAL_BIN_COUNT 13
#define MODULE_BIN_COUNT 13
#define SCOPE_BIN_COUNT 13
#define IO_BIN_COUNT 1
#define DYNAMIC_BIN_COUNT 1


enum _stType {
	DRIVER_ST , MODULE_ST , FOR_ST, WHILE_ST , SWITCH_ST
} ;

struct _baseST ;
struct _moduleST ;

enum _variableType 
{
	VAR_INPUT ,
	VAR_PLACEHOLDER,
	VAR_OUTPUT ,
	VAR_LOCAL ,
	VAR_LOOP ,
	VAR_MODULE 
} ;

struct _varST {
	char * lexeme ; // variable name

	tokenID datatype ; // TK_INTEGER, TK_REAL, TK_BOOLEAN, TK_ARRAY
	arrayTypeInfo *arrayIndices ; // if TK_ARRAY 

	int size ;
	int offset ;
	int tinker ;
	void *scope ;
	enum _variableType varType ;
} ;


struct _moduleST 
{
	char * lexeme ;
	enum _stType tableType ;
	void * parent ; 		

	struct _varSTentry *localVars[LOCAL_BIN_COUNT] ;
	struct _varSTentry *dynamicVars[DYNAMIC_BIN_COUNT] ;
	struct _varSTentry *inputVars[IO_BIN_COUNT] ;
	struct _varSTentry *outputVars[IO_BIN_COUNT] ;

	struct _moduleSTentry *scopeVars[SCOPE_BIN_COUNT] ;

	int filledMod ;
	int inputSize ;
	int outputSize ;
	int currOffset ;
	int scopeSize ;
} ;

struct _moduleSTentry {
	struct _moduleST * thisModuleST ;
	struct _moduleSTentry * next ;
} ;

struct _varSTentry {
	struct _varST * thisVarST ;
	struct _varSTentry * next ;
} ;

struct _baseST {
	struct _varSTentry * vars[LOCAL_BIN_COUNT] ;
	struct _moduleSTentry * modules[MODULE_BIN_COUNT] ;
	struct _moduleST * driverST ;

	int semanticError ;
} ;

typedef enum _insertVarType
{
	INSERT_INPUT, INSERT_OUTPUT, INSERT_LOCAL, INSERT_DYNAMIC
} insertVarType ;

typedef enum _searchVarType
{
	SEARCH_INPUT, SEARCH_OUTPUT, SEARCH_LOCAL
} searchVarType ;

typedef enum _stType stType ;
typedef enum _variableType variableType ;
typedef struct _baseST baseST ;
typedef struct _moduleST moduleST ;
typedef struct _varST varST ;
typedef struct _varSTentry varSTentry ;
typedef struct _moduleSTentry moduleSTentry ;
typedef struct _guardTinkerNode guardTinkerNode ;

//general functions
int hashFunction ( char* lexeme , int size ) ;
char * generateString () ;

// function for base symbol table
baseST * createBaseST () ;
moduleST * createModuleST ( baseST * parent , char * lexeme, int currOffset) ;
moduleST * createDriverST ( baseST * parent ) ;
moduleST * createScopeST ( moduleST * parent , stType scopeType ) ;
varST * createVarST (char *lexeme, void *scope, variableType varType, tokenID datatype) ;

// Insertion
void insertModuleSTInbaseST ( baseST * base , moduleST * thisModule) ;
void insertVarSTInbaseST ( baseST * base , varST * thisVarST ) ;
void insertScopeST ( moduleST* parent , moduleST * thisScopeST ) ;
void insertVar (moduleST *thisModule, varST *thisVarST, insertVarType flag) ;

//search
varST * searchVarInbaseST (baseST * base ,char * lexeme) ;
moduleST * searchModuleInbaseST (baseST * base, char * lexeme) ;
varST* searchVarModuleList (moduleST* thisModule, char* lexeme, searchVarType flag) ;
varST* searchVarModule (moduleST * thisModule , char * lexeme) ;
varST * searchVar (baseST* realBase, moduleST *thisModule , char *lexeme) ;

// Printing
void printBaseST (baseST * base ) ;
void printModuleST (moduleST * thisModuleST, int printParam) ;

// Tinker --> Checked for module outputs, loop variable, placeholders only
void printOutputsNotTinkered (moduleST *baseModule) ;
int checkAllOutputsTinkered (moduleST *baseModule) ;
void idListTinker (baseST *realBase, moduleST* baseModule, astNode *idListHead) ;
void tinkerVar (baseST *realBase, moduleST *baseModule, varST *var, astNode *varASTNode) ;

// ST population
baseST * fillSymbolTable (astNode * thisASTNode, int depthSTPrint) ;
void fillModuleST (baseST* realBase , moduleST* baseModule , astNode* moduleASTNode, int depthSTPrint) ;

// Function call checker
int isValidCall (baseST * base ,moduleST* thisModule , astNode * funcIDNode , int haveReturns) ;
varST * checkIP (baseST *realBase, moduleST * thisModule ,moduleST * targetModule , astNode * inputNode) ;
varST * checkOP (baseST *realBase, moduleST * thisModule ,moduleST * targetModule , astNode * inputNode) ;

// Helper
char* varTypeToString (variableType varType) ;
int getSize(baseST * realBase, varST * thisVar) ;
char *getParentModuleName (baseST* realBase, moduleST *scope) ;
char *typeIDToString (tokenID id) ;

#endif
