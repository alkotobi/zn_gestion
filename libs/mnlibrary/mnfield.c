#include "mnfield.h"

TFieldGuiParams* TFieldGuiParams_new()
{
    TFieldGuiParams* params = (TFieldGuiParams*)mnalloc(sizeof(TFieldGuiParams));
    if (params) {
        params->caption = 0;
        params->group_caption = 0;
        params->group_id = -1;
        params->gui_type = -1;
    }
    else assert(params);
    return params;
}

TFieldGuiParams* TFieldGuiParams_init(TFieldGuiParams* self, char* caption, char gui_type, char group_id, char* group_caption)
{
    if (self<=0)
    {
        self = TFieldGuiParams_new();

    }
    self->caption = cstring_clone(caption);
    self->group_caption = cstring_clone(group_caption);
    self->group_id = group_id;
    self->gui_type = gui_type;
    return self;
}

TFieldGuiParams** TFieldGuiParams_clean(TFieldGuiParams** params_hld)
{
    free((*params_hld)->caption);
    (*params_hld)->caption = 0;
    free((*params_hld)->group_caption);
    (*params_hld)->group_caption = 0;
    return params_hld;
}

void TFieldGuiParams_free(TFieldGuiParams** params_hld)
{
    free((*params_hld));
    (*params_hld) = 0;
}

void TFieldGuiParams_destroy(TFieldGuiParams** params_hld)
{
    TFieldGuiParams_free(TFieldGuiParams_clean(params_hld));
}


TField* TField_new()
{
    TField* fld = (TField*)mnalloc(sizeof(TField));
    if (fld) {
        fld->name = 0;
        fld->data = 0;
        fld->is_generated = 0;
        fld->order = 0;
        fld->gui_params=0;
    }
    else assert(fld);
    return fld;
}

TField* TField_init(TField* fld,
                    TVariant* var,
                    char is_generated,
                    char* name)
{
    if (fld<=0)
    {
        fld = TField_new();
    }
    fld->data = var;
    fld->is_generated = is_generated;
    TField_set_name(fld, name);
    return fld;
}

TField* TField_init_int(TField* fld, char* name, int val)
{
    TField_init(fld,
                TVariant_init_int(TVariant_new(), val ),
                1,
                name);
    return fld;
}

TField* TField_init_double(TField* fld, char* name, double val)
{
    TField_init(fld, TVariant_init_double(TVariant_new(), val), 1,name);
    return fld;
}

TField* TField_init_cstring(TField* fld, char* name, char* val)
{
    TField_init(fld, TVariant_init_cstring(TVariant_new(), val), 1,name);
    return fld;
}

TField* TField_create_int(char* name, int val)
{
    return TField_init_int(TField_new(),name,val);
}

TField* TField_create_double(char* name, double val)
{
    return  TField_init_double(TField_new(), name, val);;
}

TField* TField_create_cstring(char* name, char* val)
{
    return TField_init_cstring(TField_new(), name, val);
}

TField** TField_clean(TField** fld_hld){

    TVariant_destroy(&((*fld_hld)->data));
    return fld_hld;
}
void TField_free(TField** fld_hld){
    free((*fld_hld)->name);
    free((*fld_hld));
    (*fld_hld)=0;

}
void TField_destroy(TField** fld_hld){
    TField_free(TField_clean(fld_hld));

}

TVariant* TField_data(TField* fld)
{
    return fld->data;
}

void TField_set_name(TField* fld, char* name)
{
    if (fld->name) free(fld->name);
    fld->name = cstring_clone(name);
}

char* TField_name(TField* fld)
{
    return fld->name;
}

char TField_isgenerated(TField* fld)
{
    return fld->is_generated;
}

void TField_set_generated(TField* fld, char is_generated)
{
    fld->is_generated = is_generated;
}

char TField_is_equal(TField* fld1, TField* fld2)
{
    return cstring_is_equal(TField_name(fld1), TField_name(fld2)) &&
            TVariant_is_equal(fld1->data, fld2->data);
}

TField* TField_clone(TField* fld)
{
    TField* f= TField_init(TField_new(),
                           TVariant_clone(fld->data),
                           fld->is_generated,fld->name);
    TField_set_order(f, TFielld_order(fld));
    return f;
}

void TField_set_order(TField* fld, char order)
{
    fld->order = order;
}

char TFielld_order(TField* fld)
{
    return fld->order;
}

char TField_order_is_greater(TField* fld1, TField* fld2)
{
    return TFielld_order(fld1)>TFielld_order(fld2);
}
