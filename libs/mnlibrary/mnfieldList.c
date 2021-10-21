#include "mnfieldList.h"

TFieldList* TFieldList_new()
{
    TFieldList* flds = (TFieldList*)mnalloc(sizeof(TFieldList));
    if (flds) {
        flds->fields = 0;
        flds->is_changed = -1;
        flds->is_deleted = -1;
        flds->is_new = -1;
    }
    else assert(flds);
    return flds;
}

TFieldList* TFieldList_init(TFieldList* flds)
{
    flds->fields = TArray_init(TArray_new());
    return flds;
}

void TFieldList_set_changed(TFieldList* flds, char is_changed)
{
    flds->is_changed=is_changed;
}

char TFieldList_is_changed(TFieldList* flds)
{
    return flds->is_changed;
}

void TFieldList_set_deleted(TFieldList* flds, char is_deleted)
{
    flds->is_deleted = is_deleted;
}

char TFieldList_is_deleted(TFieldList* flds)
{
    return flds->is_deleted;
}

void TFieldList_set_new(TFieldList* flds, char is_new)
{
    flds->is_new = is_new;
}

char TFieldList_is_new(TFieldList* flds)
{
    return flds->is_new;
}

TField* TFieldList_add(TFieldList* flds, TField* fld)
{
    TArray_add(flds->fields, fld);
    TField_set_order(fld, (char)TArray_count(flds->fields) - 1);
    return fld;
}

TField* TFieldList_item_at(TFieldList* flds, TSize index)
{
    return (TField*)TArray_item_at(flds->fields,index);
}

TField* TFieldList_item_with_name(TFieldList* flds, char* name)
{
    for (TSize i = 0; i < TArray_count(flds->fields); i++)
    {
        if (cstring_is_equal(TField_name(TFieldList_item_at(flds, i)),name)) {
            return TFieldList_item_at(flds, i);
        }
    }
    return 0;
}

TFieldList* TFieldList_clone(TFieldList* flds)
{
    TFieldList* f = TFieldList_new();
    f->is_changed = flds->is_changed;
    f->is_deleted = flds->is_deleted;
    f->is_new = flds->is_new;
    f->fields = TArray_clone(flds->fields,(TFVarVar)TField_clone);
    return f;
}

char TFieldList_is_equal(TFieldList* flds1, TFieldList* flds2)
{
    return TArray_is_equal(flds1->fields,flds2->fields,
                           (TFCharVarVar)TField_is_equal);
}

void TFieldList_sort_by_order(TFieldList* flds)
{
    TArray_sort(flds->fields,(TFCharVarVar) TField_order_is_greater);
}

//TODO add assert for func arguments
TSize TFieldList_count(TFieldList* flds){
  assert(flds);
  return flds->fields->count;
  
}

char* TFieldList_field_names(TFieldList* flds){
  cstringList* l=cstringList_init(0,250);
  for(TSize i=0;i< TFieldList_count(flds);i++){
    cstringList_add(l,TFieldList_item_at(flds,i)->name);
  }
  return cstringList_to_new_cstring(l);
}


