#pragma once
#include "mnfield.h"
#include "mnarray.h"
#include "mnstring.h"


struct TFieldList {
    TArray* fields;
    char is_changed;
    char is_new;
    char is_deleted;
};
//void TFieldList_test(void);
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
char* TFieldList_field_names(TFieldList* flds);

TSize TFieldList_count(TFieldList* flds);
