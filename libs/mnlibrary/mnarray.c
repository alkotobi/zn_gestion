#include "mnarray.h"

TArray* TArray_new()
{
    TArray* arr = (TArray*)mnalloc(sizeof(TArray));

    if (arr>0)
    {
        arr->count = 0;
        arr->data = 0;
        arr->size = 0;
    }
    else
    {
        assert(arr);
    }

    return arr;
}

TArray* TArray_init(TArray* arr)
{
    if (arr<=0) {
        arr=TArray_new();
    }
    TArray_init_v1(arr, TARRAY_DEFAULT_SIZE);
    return arr;
}

TArray* TArray_init_v1(TArray* arr, TSize size)
{
    if (arr <= 0) {
        arr = TArray_new();
    }
    arr->data = (TPtrHld)mncalloc(size, sizeof(TVar));
    if (arr->data > 0) {

        arr->size = size;
    }
    else
    {
        assert(arr->data);
    }
    return arr;

}

TArray* TArray_resize(TArray* arr, TSize size)
{
    assert(TArray_size(arr) < size);
    TPtrHld data= mnrealloc(arr->data, size * sizeof(TVar));
    //(TPtrHld)mncalloc((size), sizeof(TVar));
    if (data)
    {
        arr->data = data;
        arr->size = size;
        for (TSize i = TArray_count(arr); i < size; i++)
        {
            arr->data[i] = 0;
        }
    }
    else
    {
        assert(data);
    }
    return arr;
}

TArray** TArray_clean(TArray** arr_hld, TFVoidPtrHld free_val)
{
    if (*arr_hld) {
        for (TSize i = 0; i < TArray_count(*arr_hld); i++)
        {
            TVar var = TArray_item_at(*arr_hld, i);
            free_val(&var);
        }
        TArray_set_count(*arr_hld, 0);
    }
    return arr_hld;
}

void TArray_free(TPtrHld arr_hld)
{
    free(((TArray*)(*arr_hld))->data);
    free((TArray*)(*arr_hld));
    *arr_hld = 0;
}

TSize TArray_count(TArray* arr)
{
    if(arr)
        return arr->count;
    return 0;
}

void TArray_set_count(TArray* arr, TSize count)
{
    arr->count = count;
}

TSize TArray_size(TArray* arr)
{
    return arr->size;
}

void TArray_set_size(TArray* arr, TSize size)
{
    arr->size = size;
}

TVar TArray_item_at(TArray* arr, TSize index)
{
    if (arr && arr->data) {
        assert(index < arr->count);
        return arr->data[index];
    }else {
        assert(0);
    }
}

TVar TArray_add(TArray* arr, TVar var)
{
    if (TArray_count(arr) == TArray_size(arr))
    {
        TArray_resize(arr, arr->size * 2);
    }
    if (arr->data)
    {
        arr->data[arr->count] = var;
    }

    arr->count++;
    return var;
}

TArray* TArray_clone(TArray* arr_src, TFVarVar clone_value)
{
    TArray* arr = TArray_init(TArray_new());
    for (TSize i = 0; i < TArray_count(arr_src); i++)
    {
        TArray_add(arr, clone_value(TArray_item_at(arr_src, i)));
    }
    return arr;
}

char TArray_is_equal(TArray* arr1, TArray* arr2, TFCharVarVar is_equal)
{
    if (arr1->count != arr2->count) return 0;
    for (TSize i = 0; i < TArray_count(arr1); i++)
    {
        if (!is_equal(TArray_item_at(arr1, i), TArray_item_at(arr2, i))) return 0;
    }
    return 1;
}

TSize TArray_find(TArray* arr, TVar item, TFCharVarVar is_equal)
{
    for (TSize i = 0; i < TArray_count(arr); i++) {
        if (is_equal(item,TArray_item_at(arr,i))) {
            return i;
        }
    }
    return -1;
}

TVar TArray_set_item_at(TArray* arr, TVar item, TSize index)
{
    assert(index < TArray_count(arr));
    TVar var = TArray_item_at(arr, index);
    arr->data[index] = item;
    return var;
}

void TArray_insert_item_at(TArray* arr, TVar item, TSize index)
{
    assert(index < TArray_count(arr));
    if (arr->count == arr->size) {
        TArray_resize(arr, arr->size * 2);
    }
    for (TSize i = arr->count; i > index; i--)
    {
        arr->data[i] = arr->data[i - 1];
    }
    arr->data[index] = item;
    arr->count++;
}

TVar TArray_remove_item_at(TArray* arr, TSize index)
{
    assert(index < TArray_count(arr));
    TVar var = arr->data[index];
    if (index<arr->count-1) for (TSize i = index; i < arr->count-1; i++)
    {
        arr->data[i] = arr->data[i + 1];
    }
    arr->data[arr->count-1] = 0;
    arr->count--;
    return var;
}

TVar TArray_add_or_replace(TArray* arr, TVar item, TFCharVarVar is_equal)
{
    TVar var = 0;
    TSize index = TArray_find(arr, item, is_equal);
    if (index >= 0) {
        var = arr->data[index];
        arr->data[index] = item;
    }
    else
    {
        TArray_add(arr, item);
    }
    return var;
}

void TArray_sort(TArray* arr, TFCharVarVar is_great)
{
    char switched = 0;
    do
    {
        switched = 0;
        for (TSize i = 0; i < TArray_count(arr)-1; i++)
        {
            if (is_great(TArray_item_at(arr, i), TArray_item_at(arr, i + 1))) {
                TArray_set_item_at(arr,
                                   TArray_set_item_at(arr, TArray_item_at(arr, i + 1), i),
                                   i + 1);
                switched = 1;
            }
        }
    } while (switched);
}
//TODO test
char* TArray_to_string(TArray* arr,char*(*to_str)(TVar))
{
    cstringList* l=cstringList_init(0,250);
    for (mint i = 0; i < arr->count; i++)
    {
        cstringList_add(l,to_str(arr->data[i]));
        cstringList_add(l,cstring_clone("\n"));
    }
    char* str = cstringList_to_new_cstring(l);
    cstringList_free(cstringList_clear(&l));
    return str;
}

mnarray mnarray_new(mint size)
{
    mnarray arr=0;
    void* s= mnalloc(sizeof (arrPrm)+sizeof (void*)*size);
    if (s) {
        arr = s+sizeof (arrPrm);
        arrPrm* prm =(arrPrm*) s;
        prm->size=size;
        prm->count=0;
    }
    return arr;
}

void mnarray_free(mnarray *arr_hld)
{
    void* s = (*arr_hld)-sizeof (arrPrm);
    mnfree(s);
    (*arr_hld)=0;
}

TVar mnarray_append(mnarray* arr_hld, TVar item)
{
    assert(*arr_hld);
    if(mnarray_count(*arr_hld)==mnarray_size(*arr_hld))
        *arr_hld = mnarray_grow_double(*arr_hld);
    (*arr_hld)[mnarray_count(*arr_hld)] = item;
    mnarray_count_pp(*arr_hld);
    return item;
}

mnarray mnarray_grow_size(mnarray arr, mint new_size)
{
    assert(arr);
    assert(mnarray_size(arr)<new_size);
    mnarray a= mnarray_new(new_size);
    for(mint i=0;i<mnarray_count(arr);i++){
        a[i]=arr[i];
    }
    mnarray_set_count(a,mnarray_count(arr));
    mnarray_free(&arr);
    return a;
}

arrPrm *mnarray_prm(mnarray arr)
{
    assert(arr);
    return (arrPrm*)(arr-sizeof(arrPrm));
}

mint mnarray_size(mnarray arr)
{
    return mnarray_prm(arr)->size;
}

mint mnarray_count(mnarray arr)
{
     assert(arr);
    return mnarray_prm(arr)->count;
}

void mnarray_set_count(mnarray arr, mint count)
{
     assert(arr);
    mnarray_prm(arr)->count=count;
}

void mnarray_set_size(mnarray arr, mint size)
{
     assert(arr);
     mnarray_prm(arr)->size = size;
}

void mnarray_count_pp(mnarray arr)
{
    assert(arr);
   mnarray_prm(arr)->count++;
}

mnarray mnarray_grow_double(mnarray arr)
{
    return mnarray_grow_size(arr,mnarray_size(arr)*2);
}
