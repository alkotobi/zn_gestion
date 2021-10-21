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

/*

                    MNSTRING
*/

#define STR_STD_SIZE 255
typedef char* mnstring ;
typedef struct{
    mint size;
    mint count;
    mint ind;
} strPrm;

mnstring mnstring_new(mint size,const char* str_init);
void mnstring_free(mnstring* ptr_hld);
mnstring mnstring_new_empty(mint size);
mnstring mnstring_new_from_cstring(const char* str_init);
strPrm* mnstring_strprm(mnstring str);
mnstring mnstring_new_clone(mnstring str);
mnstring mnstring_grow_size(mnstring str, int new_size);
mnstring mnstring_grow_size_double(mnstring str);
char mnstring_is_full(mnstring str);
mnstring mnstring_append_char(mnstring str,char c);
mint mnstring_size(mnstring str);
mint mnstring_count(mnstring str);
void mnstring_set_count(mnstring str,mint new_count);
void mnstring_count_pp(mnstring str);
mnstring mnstring_append_cstring(mnstring str, mint str_sub_count, const char* str_sub);
mnstring mnstring_append_mnstring(mnstring str, mnstring str_sub);
mnstring mnstring_from_mint(mint n);
mnstring mnstring_from_double(mdouble f);
mnstring mnstring_fill_empty_with_char(mnstring str,mint start,mint end,char c);
mnstring mnstring_init_empty(mnstring str);
mnstring mnstring_clear(mnstring str);
