#pragma once
#include "types.h"
#include "cstring.h"
#include "mnarray.h"

struct TString {
    TSize count;
    char* cstring;
};
typedef struct TString TString;
//void TString_test(void);
TString* TString_new(void);
TString* TString_init(TString* str, char* cstring);
TString* TString_init_cstring_cpy(TString* str, char* cstring);
TString* TString_init_with_size(TString* str, TSize size, char* cstring);
TString* TString_from_cstring(char* cstring);
TString* TString_from_cstring_cpy(char* cstring);
TString** TString_clean(TString** str);
void TString_destroy(TString** str_hld);
void TString_free(TString** str);
TString* TString_clone(TString* str);
char TString_is_equal(TString* str1, TString* str2);
char TString_is_equal_cstring(TString* str1, char* cstring);
TString* TString_add(TString* str_src, TString* str_sub);
TString* TString_concat_multi(const char* str, ...);
TString* TString_fill_range(TString* str, char c, TSize start_ind, TSize end_ind);
TString* TString_fill(TString* str, char c);
TString* TString_replace(TString* str, TString* sub_str, TSize index);
char TString_is_empty(TString* str);
TString* TString_from_int(int n);
TString* TString_from_double(double f);




/*
                    TStringList
*/


typedef TArray TStringList;
void TStringList_test(void);
TStringList* TStringList_new(void);
TStringList* TStringList_init(TStringList* strs);
TSize TStringList_char_count(TStringList* str_l);
TString* TStringList_text(TStringList* str_l,char* str_end);
TString* TStringList_item_at(TStringList* str_l, TSize index);
TString* TStringList_add(TStringList* str_l, TString* str);
TStringList** TStringList_clean(TStringList** str_l);
void TStringList_free(TStringList** str_l);
void TStringList_destroy(TStringList** str_l);
