#pragma once
#include "mnvariant.h"
//TODO: assert functions params
enum GuiType{GUI_EDIT,GUI_COMBOBOX};
typedef enum GuiType GuiType;
struct TFieldGuiParams{
    char* caption;
    char gui_type;
    char group_id;
    char* group_caption;

};
//TODO:test TFiteldGuiParams
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
//void TField_test(void);
TField* TField_new(void);
TField* TField_init(TField* fld, TVariant* var, char is_generated,char* name);
TField* TField_init_int(TField* fld, char* name,int val);
TField* TField_init_double(TField* fld, char* name, double val);
TField* TField_init_cstring(TField* fld, char* name, char* val);


TField* TField_init_int_cpy(TField* fld, char* name,int val);
TField* TField_init_double_cpy(TField* fld, char* name, double val);
TField* TField_init_cstring_cpy(TField* fld, char* name, char* val);


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
char* TField_to_string(TField* fld);
