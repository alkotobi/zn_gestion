#pragma once
#include "mnfield.h"
#include "mnstring.h"

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
