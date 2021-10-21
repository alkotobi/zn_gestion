#include <stdio.h>
#include "mnsql.h"
#include "mnfieldlist.h"

int main(){
  TFieldList* f =TFieldList_init(0);
  TFieldList_add(f, TField_create_cstring("name","hi"));
  TFieldList_add(f, TField_create_int("age",20));
  TSql* str=TSql_init_with_cstring_cpy(0, "message" , TFieldList_field_names(f), 0,0, 0,0);


  
  printf("bismi allh\n");
  return 0;
}
