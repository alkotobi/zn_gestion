#include <stdio.h>
#include "mnsql.h"
#include "mnfieldlist.h"

int main(){
  TFieldList* f =TFieldList_init(0);
  TFieldList_add(f, TField_create_cstring("name","hi"));
  TFieldList_add(f, TField_create_int("age",20));
  TSql* str=TSql_init(0, "message" , TString *fields, TString *w_where, TString *w_order_by, int limit, int offset)


  
  printf("bismi allh\n");
  return 0;
}
