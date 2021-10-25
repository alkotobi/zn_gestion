#pragma once
#include "types.h"


//char cstring_test(void);
char* cstring_new(TSize size);
TSize cstring_count(char* str);
char* cstring_clone(char* str_src);
void cstring_free(TPtrHld str_hld);
char cstring_is_equal(char* str1, char* str2);
char* cstring_from_int(mint i);
char* cstring_from_double(mdouble f);
char* cstring_new_empty(void);
char* cstring_new_from_const(const char* str);
char cstring_is_great(char* str1, char* str2);

/*

        CSTRING LIST

*/
typedef struct{
    char** list;
    mint count;
    mint size;
}cstringList;

cstringList* cstringList_new();
cstringList* cstringList_init(cstringList* l,mint size);
void cstringList_add(cstringList* l,char* str);
char* cstringList_item_at(cstringList* l,mint index);
char* cstringList_to_new_cstring(cstringList* l);
cstringList** cstringList_clear(cstringList** l_hld);
void cstringList_free(cstringList** l_hld);
char* cstring_concat(int str_count,...);

