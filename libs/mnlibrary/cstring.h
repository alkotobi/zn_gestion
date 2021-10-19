#pragma once
#include "types.h"


//char cstring_test(void);
char* cstring_new(TSize size);
TSize cstring_count(char* str);
char* cstring_clone(char* str_src);
void cstring_free(TPtrHld str_hld);
char cstring_is_equal(char* str1, char* str2);
char* cstring_from_int(int i);
char* cstring_from_double(double f);
char* cstring_new_empty(void);
char* cstring_new_from_const(const char* str);
char cstring_is_great(char* str1, char* str2);

/*

        CSTRING LIST

*/
typedef struct{
    char** list;
    int count;
    int size;
}cstringList;

cstringList* cstringList_new();
cstringList* cstringList_init(cstringList* l,int size);
void cstringList_add(cstringList* l,char* str);
char* cstringList_item_at(cstringList* l,int index);
char* cstringList_to_new_cstring(cstringList* l);

