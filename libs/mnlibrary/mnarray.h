#pragma once
#include "types.h"

struct TArray {
    TPtrHld data;
    TSize size;
    TSize count;
};

typedef struct TArray TArray;
#define TARRAY_DEFAULT_SIZE 250
//void TArray_test(void);
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
TVar TArray_item_at(TArray* arr, TSize index);
TVar TArray_add(TArray* arr, TVar var);
TArray* TArray_clone(TArray* arr_src,TFVarVar clone_value);
char TArray_is_equal(TArray* arr1, TArray* arr2, TFCharVarVar is_equal);
TSize TArray_find(TArray* arr, TVar item, TFCharVarVar is_equal);
TVar TArray_set_item_at(TArray* arr, TVar item, TSize index);
void TArray_insert_item_at(TArray* arr, TVar item, TSize index);
TVar TArray_remove_item_at(TArray* arr, TSize index);
TVar TArray_add_or_replace(TArray* arr, TVar item, TFCharVarVar is_equal);
void TArray_sort(TArray* arr, TFCharVarVar is_great);

typedef struct{
    mint size;
    mint count;
    mint index;
}arrPrm ;

typedef void** mnarray;
mnarray mnarray_new(mint size);
void mnarray_free(mnarray* arr_hld);
mnarray mnarray_grow_size(mnarray arr, mint new_size);
TVar mnarray_append(mnarray *arr_hld, TVar item);
arrPrm* mnarray_prm(mnarray arr);
mint mnarray_size(mnarray arr);
mint mnarray_count(mnarray arr);
void mnarray_set_count(mnarray arr,mint count);
void mnarray_set_size(mnarray arr,mint size);
void mnarray_count_pp(mnarray arr);
mnarray mnarray_grow_double(mnarray arr);
