#include "mnstring.h"

TString* TString_new()
{
    TString* str = (TString*)mnalloc(sizeof(TString));

    if (str>0) {
        str->count = 0;
        //str->size = 0;
        str->cstring = 0;
    }else assert(str);
    return str;
}

TString* TString_init(TString* str, char* cstring)
{
    if (cstring<=0)
    {
        cstring = cstring_new_from_const("");
    }
    return TString_init_with_size(str, cstring_count(cstring), cstring);
}

TString* TString_init_cstring_cpy(TString* str, char* cstring)
{
    return TString_init( str, cstring_clone(cstring));
}

TString* TString_init_with_size(TString* str, TSize size, char* cstring) {
    if (str<=0)
    {
        str = TString_new();
    }
    str->count = size;
    str->cstring = cstring;
    return str;
}

TString* TString_from_cstring(char* cstring)
{
    return TString_init(TString_new(),cstring);
}

TString* TString_from_cstring_cpy(char* cstring)
{
    return TString_from_cstring(cstring_clone(cstring));
}

TString** TString_clean(TString** str)
{

    if (*str) {
        free((*str)->cstring);
        (*str)->cstring = 0;
        (*str)->count = 0;
    }
    return str;
}

void TString_destroy(TString** str_hld)
{
    TString_free(TString_clean(str_hld));
}

void TString_free(TString** str)
{
    free(*str);
    *str = 0;
}

TString* TString_clone(TString* str)
{
    if (str && str->cstring) {
        TSize size = (str->count)+1;
        char* cstring = (char*)mnalloc(sizeof(char) * size);
        TString* res = 0;
        if (cstring>0) {
            for (TSize i = 0; i < str->count; i++)
            {
                cstring[i] = str->cstring[i];
            }
            cstring[str->count] = 0;
            res = TString_new();
            res->count = str->count;
            //res->size = str->size;
            res->cstring = cstring;
        }
        else assert(cstring);
        return res;
    }
    return 0;

}

char TString_is_equal(TString* str1, TString* str2)
{

    if (str1->count != str2->count) return 0;
    for (TSize i = 0; i < str1->count; i++)
    {
        if (str1->cstring[i] != str2->cstring[i]) return 0;
    }
    return 1;
}

char TString_is_equal_cstring(TString* str1, char* cstring)
{
    TSize count = cstring_count(cstring);
    if (str1->count != count) return 0;
    for (TSize i = 0; i < str1->count; i++)
    {
        if (str1->cstring[i] != cstring[i]) return 0;
    }
    return 1;
}

TString* TString_add(TString* str_src, TString* str_sub)
{
    TSize count = str_src->count + str_sub->count;
    TSize size = count + 1;
    char* cstring = (char*)mncalloc((size), sizeof(char));
    if (cstring>0) {
        for (TSize i = 0; i < str_src->count; i++)
        {
            cstring[i] = str_src->cstring[i];

        }
        for (TSize i = str_src->count; i < count; i++)
        {
            cstring[i] = str_sub->cstring[i - str_src->count];
        }
        free(str_src->cstring);
        str_src->cstring = cstring;
        str_src->count = count;
        //str_src->size = count;
    }
    else assert(cstring);
    return str_src;

}


TString* TString_concat_multi(const char* str, ...) {
    va_list ap;
    int i = 0;
    int j = 0;
    va_start(ap, str);
    char str1[250];
    TArray* list = TArray_init(TArray_new());
    while (str[i] != '\0') {
        if (str[i] == '%') {
            str1[j] = 0;
            TArray_add(list, TString_init(TString_new(), cstring_clone(str1)));
            i++;
            if (str[i] == 's') {
                TArray_add(list, TString_init(TString_new(),
                                              cstring_clone(va_arg(ap, char*))));
            }
            else if (str[i] == 'd') {
                TArray_add(list, TString_init(TString_new(),
                                              cstring_from_int(va_arg(ap, int))));
            }
            else if (str[i] == 'm') {//for TString
                TString* ss = va_arg(ap, TString*);
                TArray_add(list, TString_clone(ss));
            }
            else if (str[i] == 'f') {//for TString
                TArray_add(list, TString_init(TString_new(),
                                              cstring_from_double(va_arg(ap, double))));
            }
            j = 0;
            i++;
            continue;
        }
        str1[j] = str[i];
        j++;
        i++;
    }
    va_end(ap);
    str1[j] = 0;
    TArray_add(list, TString_init(TString_new(),cstring_clone(str1)));
    TString* s = TStringList_text(list,"");
    TArray_free((TPtrHld)TArray_clean((&list),(TFVoidPtrHld) TString_destroy));
    return  s;
}

TString* TString_fill(TString* str, char c)
{
    TSize end_ind = str->count - 1;
    return TString_fill_range(str,c,0,end_ind);
}

TString* TString_replace(TString* str, TString* sub_str, TSize index)
{
    assert(index < str->count);
    for (TSize i = index; (i<str->count)&&(i < (index+sub_str->count)); i++)
    {
        str->cstring[i] = sub_str->cstring[i - index];
    }
    return str;
}

char TString_is_empty(TString* str)
{
    return str->count==0;
}

TString* TString_from_int(int n)
{
    char* s = cstring_new(25);
    snprintf(s, 25, "%d", n);
    return TString_init(TString_new(), s);
}

TString* TString_from_double(double f)
{
    char* s = cstring_new(50);
    snprintf(s, 50, "%f", f);
    return TString_init(TString_new(), s);
}

TString* TString_fill_range(TString* str, char c, TSize start_ind, TSize end_ind)
{
    assert(start_ind >= 0 && start_ind < str->count && end_ind < str->count);
    for (TSize i = start_ind; i <= end_ind; i++)
    {
        str->cstring[i] = c;
    }
    return str;
}



/*
                    TStringList
*/



TStringList* TStringList_new()
{
    return TArray_new();
}

TStringList* TStringList_init(TStringList* strs)
{
    return TArray_init(strs);
}

TSize TStringList_char_count(TStringList* str_l) {
    TSize count = 0;
    for (TSize i = 0; i < TArray_count(str_l); i++)
    {
        count = count + ((TString*)TArray_item_at(str_l, i))->count;
    }
    return count;
}

TString* TStringList_text(TStringList* str_l, char* str_end)
{

    TSize str_end_count = cstring_count(str_end);
    TSize count = TStringList_char_count(str_l)+(str_end_count*TArray_count(str_l));
    char* cstring = cstring_new(count);
    TSize char_count = 0;
    for (TSize i = 0; i < TArray_count(str_l); i++)
    {
        TString* s = TStringList_item_at(str_l, i);
        for (TSize j = 0; j < s->count; j++)
        {
            cstring[char_count] = s->cstring[j];
            char_count++;

        }
        for (TSize j = 0; j < str_end_count;j++) {
            cstring[char_count] = str_end[j];
            char_count++;
        }
    }
    TString* res = TString_new();
    res->cstring = cstring;
    res->count = char_count;
    //res->size = char_count;
    return res;
}

TString* TStringList_item_at(TStringList* str_l, TSize index)
{
    assert(index < TArray_count(str_l));
    return (TString*)str_l->data[index];
}

TString* TStringList_add(TStringList* str_l, TString* str)
{
    TArray_add(str_l, str);
    return str;
}

TStringList** TStringList_clean(TStringList** str_l)
{
    if (*str_l) {
        TArray_clean(str_l, (TFVoidPtrHld)TString_destroy);
    }
    return str_l;
}

void TStringList_free(TStringList** str_l)
{
    TArray_free((TPtrHld)str_l);
}

void TStringList_destroy(TStringList** str_l)
{
    TStringList_free(TStringList_clean(str_l));
}



/*
                MNSTRING
*/

mnstring mnstring_new(mint size, const char *str_init)
{
    char* str=0;
    if (!str_init) {
        str_init ="";
    }
    mint count = cstring_count((char*)str_init);
    void* s =mnalloc(sizeof (strPrm)+(sizeof (char)*(size+1)));
    if (s) {
        str =s+sizeof (strPrm);
        strPrm* flag= (strPrm*)s;
        mint i=0;
        for ( ;i< size && i<count ; i++ ) {
            str[i]=str_init[i];
        }
        str[i]=0;
        str[size]=0;
        flag->size=size;
        flag->ind=0;
        flag->count=i;

    }else assert(s);
    return str;
}

void mnstring_free(mnstring *ptr_hld)
{
    mnstring str =* ptr_hld;
    void* s = str-sizeof (strPrm);
    mnfree(s);
    *ptr_hld=0;
}

mnstring mnstring_new_empty(mint size)
{
    return mnstring_new(size,"");
}

mnstring mnstring_new_from_cstring(const char *str_init)
{
    if(!str_init) str_init ="";
    return mnstring_new(cstring_count((char*)str_init),str_init);
}

strPrm *mnstring_strprm(mnstring str)
{
    return  (strPrm*)(str-sizeof (strPrm));
}

mnstring mnstring_new_clone(mnstring str)
{
    return mnstring_new(mnstring_strprm(str)->size,str);
}

mnstring mnstring_append_char(mnstring str, char c)
{
    if (!str) {
        str =mnstring_new(STR_STD_SIZE,"");
    }
    if(mnstring_is_full(str)) str=mnstring_grow_size_double(str);
    str[mnstring_count(str)]=c;
    mnstring_count_pp(str);
    str[mnstring_count(str)]=0;


    return str;
}

mnstring mnstring_grow_size(mnstring str,mint new_size)
{
    mnstring s = mnstring_new(new_size,str);
    mnstring_free(&str);
    return s;
}

char mnstring_is_full(mnstring str)
{
    assert(str);
    strPrm* prm =mnstring_strprm(str);
    return prm->count==prm->size;
}

mnstring mnstring_grow_size_double(mnstring str)
{
    return mnstring_grow_size(str,mnstring_size(str)*2);
}

mint mnstring_size(mnstring str)
{
    return mnstring_strprm(str)->size;
}

mint mnstring_count(mnstring str)
{
    return mnstring_strprm(str)->count;
}

void mnstring_set_count(mnstring str, mint new_count)
{
    mnstring_strprm(str)->count=new_count;
}

void mnstring_count_pp(mnstring str)
{
    mnstring_strprm(str)->count++;
}

mnstring mnstring_append_cstring(mnstring str, mint str_sub_count,const char *str_sub)
{
    if (!str) {
        str = mnstring_new_empty(str_sub_count);
    }
    if (!str_sub) {
        str_sub="";
    }
    mint count = mnstring_count(str)+str_sub_count;
    if (mnstring_size(str)<(count)) {
        str=mnstring_grow_size(str,count);
    }

    for (mint i=mnstring_count(str);i<count ;i++ ) {
        str[i]=str_sub[i-mnstring_count(str)];
    }
    str[count]=0;
    mnstring_set_count(str,count);
    return str;
}

mnstring mnstring_append_mnstring(mnstring str, mnstring str_sub)
{
    return mnstring_append_cstring(str,mnstring_count(str_sub),str_sub);
}

mnstring mnstring_from_mint(mint n)
{
    return mnstring_new_from_cstring(cstring_from_int(n));
}

mnstring mnstring_from_double(mdouble f)
{
   return mnstring_new_from_cstring(cstring_from_double(f));
}

mnstring mnstring_fill_with_char(mnstring str, mint start, mint end, char c)
{
    assert(str);
    assert(start>=0 && start < mnstring_size(str));
    assert(end>=0 && end < mnstring_size(str));
    assert(start<=end);
    for (mint i= start;i<=end ;i++ ) {
        str[i]=c;
    }
    return str;
}

mnstring mnstring_init_empty(mnstring str)
{
    return mnstring_fill_with_char(str,mnstring_count(str),mnstring_size(str),0);
}

mnstring mnstring_clear(mnstring str)
{
    return mnstring_fill_with_char(str,0,mnstring_size(str),0);
}
