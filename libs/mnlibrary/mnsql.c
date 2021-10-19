#include "mnsql.h"


TSql* TSql_new()
{
    TSql* sql = (TSql*)mnalloc(sizeof(TSql));
    if (sql)
    {
        sql->fields = 0;
        sql->filters = 0;
        sql->limit = 0;
        sql->offset = 0;
        sql->sql = 0;
        sql->sql_order_by = 0;
        sql->sql_rec_count = 0;
        sql->sql_where = 0;
        sql->table_name = 0;
    }
    else assert(sql);
    return sql;
}

TSql* TSql_init(TSql* sql,
                TString* table_name,
                TString* fields,
                TString* w_where,
                TString* w_order_by,
                int limit,
                int offset)
{
    if (sql<=0)
    {
        sql = TSql_new();
    }
    sql->fields = fields;
    sql->limit = limit;
    sql->offset = offset;
    //sql->sql = sql;
    sql->sql_order_by = w_order_by;
    sql->sql_where = w_where;
    sql->table_name = table_name;
    sql->filters = TArray_init(TArray_new());
    return sql;
}

TSql* TSql_init_with_cstring(TSql* sql, char* table_name, char* fields, char* w_where, char* w_order_by, int limit, int offset)
{
    return TSql_init(sql,
                     TString_from_cstring(table_name),
                     TString_from_cstring(fields),
                     TString_from_cstring(w_where),
                     TString_from_cstring(w_order_by),
                     limit,
                     offset);
}

TSql* TSql_init_with_cstring_cpy(TSql* sql, char* table_name, char* fields, char* w_where, char* w_order_by, int limit, int offset)
{
    return TSql_init_with_cstring(sql,
                                  cstring_clone(table_name),
                                  cstring_clone(fields),
                                  cstring_clone(w_where),
                                  cstring_clone(w_order_by),
                                  limit,
                                  offset);
}

TSql** TSql_clean(TSql** msql_hld)
{
    if (*msql_hld) {
        TString_destroy(&((*msql_hld)->sql));
    }
    return msql_hld;
}

void TSql_free(TSql** msql_hld)
{
    TString_destroy(&(*msql_hld)->fields);
    TString_destroy(&(*msql_hld)->sql_order_by);
    TString_destroy(&(*msql_hld)->sql_where);
    TString_destroy(&(*msql_hld)->table_name);
    TString_destroy(&(*msql_hld)->sql_rec_count);
    TArray_free((TPtrHld)TArray_clean(&(*msql_hld)->filters,
                                      (TFVoidPtrHld) TString_destroy));
    free(*msql_hld);
    *msql_hld = 0;
}

void TSql_destroy(TSql** msql_hld)
{
    TSql_free(TSql_clean(msql_hld));
}

TSql* TSql_clone(TSql* msql)
{
    TSql* s = TSql_new();
    s->filters = TArray_clone(msql->filters, (TFVarVar)TString_clone);
    s->limit = msql->limit;
    s->offset = msql->offset;
    s->sql = TString_clone(msql->sql);
    s->sql_order_by = TString_clone((msql->sql_order_by));
    s->table_name = TString_clone(msql->table_name);
    s->fields = TString_clone(msql->fields);
    s->sql_where = TString_clone(msql->sql_where);
    return s;
}

char TSql_is_equal(TSql* msql1, TSql* msql2)
{
    return msql1->limit == msql2->limit &&
            msql1->offset == msql2->offset &&
            (TArray_is_equal(msql1->filters, msql2->filters, (TFCharVarVar)TString_is_equal)) &&
            (TString_is_equal(msql1->sql, msql2->sql)) &&
            TString_is_equal(msql1->sql_order_by, msql2->sql_order_by) &&
            TString_is_equal(msql1->table_name, msql2->table_name) &&
            TString_is_equal(msql1->fields, msql2->fields) &&
            TString_is_equal(msql1->sql_where, msql2->sql_where);
}

TString* TSql_make_sql(TSql* msql)
{

    TArray* arr = 0;
    if (msql->fields == 0 || msql->table_name == 0) {
        return 0;
    }
    TStringList* trash=TArray_init(TArray_new());
    TString* select_Sql = TStringList_add(trash,
                                          TString_concat_multi(" SELECT %m FROM %m ",
                                                               msql->fields,
                                                               msql->table_name));
    TString* where_sql = 0;
    if (msql->sql_where != 0 && (msql->sql_where->count!=0)) {
        where_sql = TStringList_add(trash,
                                    TString_concat_multi(" WHERE %m ", msql->sql_where));
    }
    else {
        where_sql = TStringList_add(trash, TString_init(TString_new(), cstring_clone("")));
    }
    TString* order_by = 0;
    if (msql->sql_order_by != 0 && (msql->sql_order_by->count!=0)) {
        order_by = TStringList_add(trash,
                                   TString_concat_multi(" ORDER BY %m ", msql->sql_order_by));
    }
    else {
        order_by = TStringList_add(trash, TString_init(TString_new(), cstring_clone("")));
    }
    TString* limit_sql = 0;
    if (msql->limit != 0) {
        limit_sql = TStringList_add(trash, TString_concat_multi(
                                        " LIMIT %d OFFSET %d ",
                                        msql->limit,
                                        msql->offset));
    }
    else {
        limit_sql = TStringList_add(trash, TString_init(TString_new(), cstring_clone("")));
    }

    TString* filters = 0;
    if (TArray_count(msql->filters) != 0) {
        arr = TArray_clone(msql->filters, (TFVarVar)TString_clone);
        if (!where_sql || (where_sql->count==0)) {
            TString_free(TArray_item_at(arr, 0));
            arr->data[0]= TString_init(TString_new(), cstring_clone(" WHERE "));
        }
        filters = TStringList_add(trash, TStringList_text(arr,""));
    }
    else {
        filters = TStringList_add(trash, TString_init(TString_new(), cstring_clone("")));
    }
    if (msql->sql) {
        TString_free(&msql->sql);
    }
    if (msql->sql) TString_free(&msql->sql);
    msql->sql = TString_concat_multi("%m%m%m%m%m", select_Sql,
                                     where_sql, filters, order_by, limit_sql);
    if (msql->sql_rec_count) TString_destroy(&msql->sql_rec_count);
    msql->sql_rec_count = TString_concat_multi("SELECT COUNT() as count from %m %m",
                                               msql->table_name, where_sql);
    if (arr) {
        TArray_clean(&arr, (TFVoidPtrHld)TString_free);
        TArray_free((TPtrHld)&arr);
    }
    TStringList_destroy(&trash);

    return msql->sql;
}

void TSql_add_filter(TSql* msql, enum logic_op log_oper,  char* filter)
{
    if (log_oper == AND) {
        TArray_add(msql->filters, TString_init(TString_new(),cstring_clone(" AND ")));
    }
    else if (log_oper == OR) {
        TArray_add(msql->filters, TString_init(TString_new(), cstring_clone(" OR ")));
    }
    else {
        return;
    }
    TArray_add(msql->filters, TString_init(TString_new(), filter));
}


void TSql_add_filter_cpy(TSql* msql, logic_op log_oper, char* filter)
{
    TSql_add_filter(msql, log_oper, cstring_clone(filter));
}

void TSql_set_where(TSql* msql,  char* w_where)
{
    if (msql->sql_where) {
        TString_destroy(&msql->sql_where);
    }
    msql->sql_where = TString_init(TString_new(),(w_where));
}

void TSql_set_where_cpy(TSql* msql, char* w_where)
{
    TSql_set_where(msql, cstring_clone(w_where));
}

void TSql_set_order(TSql* msql,  char* w_order)
{
    if (msql->sql_order_by) {
        TString_destroy(&msql->sql_order_by);
    }
    msql->sql_order_by = TString_init(TString_new(), (w_order));
}

void TSql_set_order_cpy(TSql* msql, char* w_order)
{
    TSql_set_order(msql, cstring_clone(w_order));
}

void TSql_set_limit(TSql* msql, int limit, int offset)
{
    msql->limit = limit;
    msql->offset = offset;
}

void TSql_set_fields(TSql* msql,  char* fields)
{
    if (msql->fields) {
        TString_destroy(&msql->fields);
    }
    msql->fields = TString_init(TString_new(), (fields));
}

void TSql_set_fields_cpy(TSql* msql, char* fields)
{
    TSql_set_fields( msql, cstring_clone(fields));
}

void TSql_set_table(TSql* msql,  char* table_name)
{
    if (msql->table_name) {
        TString_destroy(&msql->table_name);
    }
    msql->table_name = TString_init(TString_new(), (table_name));
}

void TSql_set_table_cpy(TSql* msql, char* table_name)
{
    TSql_set_table(msql, cstring_clone(table_name));
}

void TSql_clear_filters(TSql* msql)
{
    TArray_clean(&msql->filters, (TFVoidPtrHld)TString_destroy);
}

TString* TSql_sql(TSql* sql)
{
    return sql->sql;
}
