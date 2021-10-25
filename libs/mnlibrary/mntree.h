#pragma once
#include "mnarray.h"
#include "types.h"
typedef struct Ttree Ttree;
struct Ttree
{
    TVar data;
    TArray* childs;
    Ttree* parent;
};

Ttree* Ttree_new();
Ttree* Ttree_init(Ttree* t,TVar data,Ttree* parent);
Ttree** Ttree_clean(Ttree** t_hld,TFVoidPtrHld free_data);
void TTree_free(Ttree** T_hld);
Ttree* Ttree_add_child(Ttree* t,TVar data);
cstringList* Ttree_to_string_list(Ttree* t,char* ident,char*(*to_str)(TVar));
char* Ttree_to_string(Ttree* t,char* ident,char*(*to_str)(TVar));
