#pragma once
#include "types.h"
#include "cstring.h"

enum TTypes
{
    Int,Double,CString,Var
};
#define NAMELESS 0;
typedef enum TTypes TTypes;
struct  TVariant
{
    TVar value;
    TTypes value_type;
};
typedef struct TVariant TVariant;
//void TVariant_test(void);
TVariant* TVariant_new(void);
TVariant* TVariant_init(TVariant* var, TVar value, TTypes value_type);
TVariant* TVariant_init_int(TVariant* var, int i);
TVariant* TVariant_init_cstring(TVariant* var, char* str);
TVariant* TVariant_init_double(TVariant* var, double f);
TVariant* TVariant_create_cstring(char* cstring);
TVariant* TVariant_create_int(int n);
TVariant* TVariant_create_double( double f);
int TVariant_int(TVariant* var);
double TVariant_double(TVariant* var);
TVar TVariant_value(TVariant* var);
char* TVariant_cstring(TVariant* var);
TVariant** TVariant_clean(TVariant** var_hld);
void TVariant_free(TVariant** var_hld);
void TVariant_destroy(TVariant** var_hld);
char TVariant_is_equal(TVariant* var1, TVariant* var2);
TTypes TVariant_type(TVariant* var);
TVariant* TVariant_clone(TVariant* var);
