#pragma once

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
typedef long int TSize;
typedef void TVar;
typedef void** TPtrHld;
typedef TVar*(*TFVarVar)(TVar*);
typedef char(*TFCharVarVar)(TVar*, TVar*);
typedef void(*TFVoidPtrHld)(TPtrHld);
typedef TVar*(*TFVarVoid)(void);
typedef void(*TFVoidVarVar)(TVar*, TVar*);
typedef TSize(*TFLinTVar)(TVar*);
typedef TVar*(*TFVarVarLint)(TVar*, TSize);
typedef void(*TFVoidVar)(TVar*);
typedef TSize(*TFLinTVarVar)(TVar*, TVar*);
typedef void(*TFVoidVarVarVar)(TVar*,TVar*,TVar*);

/*
 * sys
*/

void* mnalloc(size_t size);
void* mnrealloc(void* ptr,size_t size);
void* mncalloc(size_t count,size_t size);
void mnfree(void* ptr);

/*
                testing
*/

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void print_red(char* message);
void print_green(char* message);
void print_yellow(char* message);
void print_blue(char* message);
void print_magenta(char* message);
void print_cyan(char* message);
char test(char bool_res, char* message);
char test_v1(char bool_res);
char do_test(void);
/*
                cstring
*/


char cstring_test(void);
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
                TEvent
*/
typedef enum {ON_AFTER_SCROLL} TEventType;

 struct TEvent {
    TVar* sender;
    TVar* receiver;
    TVar* params;
    TEventType type;
    void(*on_event)(struct TEvent*) ;
};
 typedef struct TEvent TEvent;

void TEvent_on_event(TEvent* event);

/*
                TArray
*/

struct TArray {
    TPtrHld data;
    TSize size;
    TSize count;
};
typedef struct TArray TArray;
#define TARRAY_DEFAULT_SIZE 250
void TArray_test(void);
TArray* TArray_new(void);
TArray* TArray_init(TArray* arr);
TArray* TArray_init_v1(TArray* arr,TSize size);
TArray* TArray_resize(TArray* arr, TSize size);
TArray** TArray_clean(TArray** arr_hld, TFVoidPtrHld free_val);
void TArray_free(TPtrHld arr_hld);
TSize TArray_count(TArray* arr);
void TArray_set_count(TArray* arr,TSize count);
TSize TArray_size(TArray* arr);
void TArray_set_size(TArray* arr, TSize size);
TVar* TArray_item_at(TArray* arr, TSize index);
TVar* TArray_add(TArray* arr, TVar* var);
TArray* TArray_clone(TArray* arr_src,TFVarVar clone_value);
char TArray_is_equal(TArray* arr1, TArray* arr2, TFCharVarVar is_equal);
TSize TArray_find(TArray* arr, TVar* item, TFCharVarVar is_equal);
TVar* TArray_set_item_at(TArray* arr, TVar* item, TSize index);
void TArray_insert_item_at(TArray* arr, TVar* item, TSize index);
TVar* TArray_remove_item_at(TArray* arr, TSize index);
TVar* TArray_add_or_replace(TArray* arr, TVar* item, TFCharVarVar is_equal);
void TArray_sort(TArray* arr, TFCharVarVar is_great);

/*
            TMatrix
*/


struct TMatrix
{
    TArray* data;
    int row;
    int col;
    int count;
};
//TODO: test TMatrix
typedef struct TMatrix TMatrix;
TMatrix* TMatrix_new();
TMatrix* TMatrix_init(TMatrix* m, int row, int col);
void TMatrix_clean(TMatrix* m,TFVoidPtrHld free_val);
void TMatrix_free(TMatrix** m_hld);
TVar*  TMatrix_item_at(TMatrix* m, TSize row, TSize col);
TVar* TMatrix_add(TMatrix* m, TVar* item);
TVar* TMatrix_set_item_at(TMatrix* m,TVar* item, TSize row, TSize col);
TArray* TMatrix_col_at(TMatrix* m, TSize col_index);
TArray* TMatrix_row_at(TMatrix* m, TSize row_index);
/*
            TLinkedListEntry
*/


typedef struct TLinkedListEntry TLinkedListEntry;
struct TLinkedListEntry
{
    TVar* value;
    TLinkedListEntry* next_entry;
};

TLinkedListEntry* TLinkedListEntry_new(void);
TLinkedListEntry* TLinkedListEntry_init(TLinkedListEntry* l, TVar* value, TLinkedListEntry* next_entry);


/*
            TLinkedList
*/

typedef struct TLinkedList TLinkedList;
struct TLinkedList
{
    TLinkedListEntry* root;
    TLinkedListEntry* last;
};

TLinkedList* TLinkedList_new(void);
TLinkedList* TLinkedList_init(TLinkedList* list, TLinkedListEntry* root);
TLinkedListEntry* TLinkedList_add(TLinkedList* list, TLinkedListEntry* entry);
TLinkedList** TLinkedList_clean(TLinkedList** list_hld, TFVoidPtrHld free_val);
void TLinkedList_free(TLinkedList** list_hld);
void TLinkedList_destroy(TLinkedList** list_hld, TFVoidPtrHld free_val);
TLinkedListEntry* TLinkedList_find(TLinkedList list, TVar* value, TFCharVarVar is_equal);
TLinkedListEntry* TLinkedList_insert_after(TLinkedList* list,
    TLinkedListEntry* entry_to_ensert,
    TLinkedListEntry* entry_to_insert_after);
TLinkedListEntry* TLinkedList_remove(TLinkedList* list, TLinkedListEntry* entry);


/*
            TString
*/

struct TString {
    TSize count;
    char* cstring;
};
typedef struct TString TString;
void TString_test(void);
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
                TVariant
*/

enum TTypes
{
    Int,Double,CString,Var
};
#define NAMELESS 0;
typedef enum TTypes TTypes;
struct  TVariant
{
    TVar* value;
    TTypes value_type;
};
typedef struct TVariant TVariant;
void TVariant_test(void);
TVariant* TVariant_new(void);
TVariant* TVariant_init(TVariant* var, TVar* value, TTypes value_type);
TVariant* TVariant_init_int(TVariant* var, int i);
TVariant* TVariant_init_cstring(TVariant* var, char* str);
TVariant* TVariant_init_double(TVariant* var, double f);
TVariant* TVariant_create_cstring(char* cstring);
TVariant* TVariant_create_int(int n);
TVariant* TVariant_create_double( double f);
int TVariant_int(TVariant* var);
double TVariant_double(TVariant* var);
TVar* TVariant_value(TVariant* var);
char* TVariant_cstring(TVariant* var);
TVariant** TVariant_clean(TVariant** var_hld);
void TVariant_free(TVariant** var_hld);
void TVariant_destroy(TVariant** var_hld);
char TVariant_is_equal(TVariant* var1, TVariant* var2);
TTypes TVariant_type(TVariant* var);
TVariant* TVariant_clone(TVariant* var);

/*
                    TField
*/
enum GuiType{GUI_EDIT,GUI_COMBOBOX};
typedef enum GuiType GuiType;
struct TFieldGuiParams{
    char* caption;
    char gui_type;
    char group_id;
    char* group_caption;

};
//TODO:test TFieldGuiParams
typedef struct TFieldGuiParams TFieldGuiParams;
TFieldGuiParams* TFieldGuiParams_new();
TFieldGuiParams* TFieldGuiParams_init(TFieldGuiParams* self,char* caption,
    char gui_type,
    char group_id,
    char* group_caption);
TFieldGuiParams** TFieldGuiParams_clean(TFieldGuiParams** params_hld);
void TFieldGuiParams_free(TFieldGuiParams** params_hld);
void TFieldGuiParams_destroy(TFieldGuiParams** params_hld);

struct TField
{
    TVariant* data;
    char is_generated;
    char* name;
    char order;
    TFieldGuiParams* gui_params;
};
typedef struct TField TField;
void TField_test(void);
TField* TField_new(void);
TField* TField_init(TField* fld, TVariant* var, char is_generated,char* name);
TField* TField_init_int(TField* fld, char* name,int val);
TField* TField_init_double(TField* fld, char* name, double val);
TField* TField_init_cstring(TField* fld, char* name, char* val);
TField* TField_create_int(char* name, int val);
TField* TField_create_double(char* name, double val);
TField* TField_create_cstring(char* name, char* val);
TField** TField_clean(TField** fld_hld);
void TField_free(TField** fld_hld);
void TField_destroy(TField** fld_hld);
TVariant* TField_data(TField* fld);
void TField_set_name(TField* fld, char* name);
char* TField_name(TField* fld);
char TField_isgenerated(TField* fld);
void TField_set_generated(TField* fld, char is_generated);
char TField_is_equal(TField* fld1, TField* fld2);
TField* TField_clone(TField* fld);
void TField_set_order(TField* fld, char order);
char TFielld_order(TField* fld);
char TField_order_is_greater(TField* fld1, TField* fld2);


/*
                    TFieldList
*/

struct TFieldList {
    TArray* fields;
    char is_changed;
    char is_new;
    char is_deleted;
};
void TFieldList_test(void);
typedef struct TFieldList TFieldList;
TFieldList* TFieldList_new(void);
TFieldList* TFieldList_init(TFieldList* flds);
void TFieldList_set_changed(TFieldList* flds, char is_changed);
char TFieldList_is_changed(TFieldList* flds);
void TFieldList_set_deleted(TFieldList* flds, char is_deleted);
char TFieldList_is_deleted(TFieldList* flds);
void TFieldList_set_new(TFieldList* flds, char is_new);
char TFieldList_is_new(TFieldList* flds);
TField* TFieldList_add(TFieldList* flds, TField* fld);
TField* TFieldList_item_at(TFieldList* flds, TSize index);
TField* TFieldList_item_with_name(TFieldList* flds, char* name);
TFieldList* TFieldList_clone(TFieldList* flds);
char TFieldList_is_equal(TFieldList* flds1, TFieldList* flds2);
void TFieldList_sort_by_order(TFieldList* flds);

/*
                    TSql
*/

typedef struct TSql TSql;
struct TSql {
    TString* table_name;
    TString* fields;
    TString* sql_order_by;
    TString* sql_where;
    TArray* filters;
    int limit;
    int offset;
    TString* sql;
    TString* sql_rec_count;
};
typedef  enum logic_op logic_op  ;
enum logic_op { AND, OR };
void TSql_test(void);
TSql* TSql_new(void);
TSql* TSql_init(TSql* sql,
    TString* table_name,
    TString* fields,
    TString* w_where,
    TString* w_order_by,
    int limit,
    int offset);
TSql* TSql_init_with_cstring(TSql* sql,
    char* table_name,
    char* fields,
    char* w_where,
    char* w_order_by,
    int limit,
    int offset);
TSql* TSql_init_with_cstring_cpy(TSql* sql,
    char* table_name,
    char* fields,
    char* w_where,
    char* w_order_by,
    int limit,
    int offset);
TSql** TSql_clean(TSql** msql_hld);
void TSql_free(TSql** msql_hld);
void TSql_destroy(TSql** msql_hld);
TSql* TSql_clone(TSql* msql);
char TSql_is_equal(TSql* msql1, TSql* msql2);
TString* TSql_make_sql(TSql* msql);
void TSql_add_filter(TSql* msql, enum logic_op log_oper,  char* filter);
void TSql_add_filter_cpy(TSql* msql, logic_op log_oper, char* filter);
void TSql_set_where(TSql* msql,  char* w_where);
void TSql_set_where_cpy(TSql* msql, char* w_where);
void TSql_set_order(TSql* msql,  char* w_order);
void TSql_set_order_cpy(TSql* msql, char* w_order);
void TSql_set_limit(TSql* msql, int limit, int offset);
void TSql_set_fields(TSql* msql,  char* fields);
void TSql_set_fields_cpy(TSql* msql, char* fields);
void TSql_set_table(TSql* msql,  char* table_name);
void TSql_set_table_cpy(TSql* msql, char* table_name);
void TSql_clear_filters(TSql* msql);
TString* TSql_sql(TSql* sql);
