#include "mnvariant.h"


TVariant* TVariant_new()
{
    TVariant* var = (TVariant*)mnalloc(sizeof(TVariant));
    if (var>0) {
        var->value = 0;
        var->value_type = -1;
    }
    else assert(var);
    return var;
}


TVariant* TVariant_init(TVariant* var, TVar value,TTypes value_type)
{
    if (var<=0)
    {
        var = TVariant_new();
    }
    var->value = value;
    var->value_type = value_type;
    return var;
}

TVariant* TVariant_init_int(TVariant* var, int i)
{
    int* n = (int*)mnalloc(sizeof(int));
    if (n > 0) *n = i; else assert(n);
    TVariant_init(var, n, Int);
    return var;
}

TVariant* TVariant_init_cstring(TVariant* var, char* str)
{
    TVariant_init(var, str, CString);
    return var;
}

TVariant* TVariant_init_double(TVariant* var, double f)
{
    double* d = (double*)mnalloc(sizeof(double));
    if (d > 0) { *d = f; }
    else assert(d);
    TVariant_init(var, d, Double);
    return var;
}

TVariant* TVariant_create_cstring(char* cstring)
{
    return TVariant_init_cstring(TVariant_new(),cstring);
}

TVariant* TVariant_create_int( int n)
{
    return TVariant_init_int(TVariant_new(),n);
}

TVariant* TVariant_create_double( double f)
{
    return TVariant_init_double(TVariant_new(),f);
}



int TVariant_int(TVariant* var)
{
    assert(var->value_type == Int);
    return *((int*)(var->value));
}

double TVariant_double(TVariant* var)
{
    assert(var->value_type == Double);
    return *((double*)(var->value));;
}

TVar TVariant_value(TVariant* var)
{
    return var->value;
}

char* TVariant_cstring(TVariant* var)
{
    assert(var->value_type == CString);
    return (char*)var->value;
}

TVariant** TVariant_clean(TVariant** var_hld)
{
    if (*var_hld) {
        free((*var_hld)->value);
        (*var_hld)->value = 0;
    }
    return var_hld;
}

void TVariant_free(TVariant** var_hld)
{
    free(*var_hld);
    *var_hld = 0;
}

void TVariant_destroy(TVariant** var_hld)
{
    TVariant_free(TVariant_clean(var_hld));
}

char TVariant_is_equal(TVariant* var1, TVariant* var2)
{
    if (TVariant_type(var1) != TVariant_type(var2)) return 0;
    if (TVariant_type(var1)==CString)
    {
        return cstring_is_equal(TVariant_cstring(var1),
                                TVariant_cstring(var2));
    }
    else if (TVariant_type(var1)==Int)
    {
        return TVariant_int(var1) == TVariant_int(var2);
    }else if(TVariant_type(var1) == Double)
    {
        return TVariant_double(var1) == TVariant_double(var2);
    }
    return 0;
}

TTypes TVariant_type(TVariant* var)
{
    return var->value_type;
}

TVariant* TVariant_clone(TVariant* var)
{
    TVariant* v = TVariant_new();
    switch (TVariant_type(var))
    {
    case Int:
        TVariant_init_int(v, TVariant_int(var));
        break;
    case Double:
        TVariant_init_double(v, TVariant_double(var));
        break;
    case CString:
        TVariant_init_cstring(v, TVariant_cstring(var));
        break;
    default:
        assert(0);
        break;
    }
    return v;
}
