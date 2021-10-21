#include "cstring.h"




char* cstring_new(TSize size)
{
    size++;
    char* str = mncalloc(size , sizeof(char));
    if (str <= 0) {
        assert(str);
    }
    return str;
}

TSize cstring_count(char* str)
{
    if (str>0) {
        for (TSize i = 0; ; i++)
        {
            if (str[i] == 0)
            {
                return i;
            }
        }
    }
    else assert(str);
    return 0;
}

char* cstring_clone(char* str_src)
{
    if (str_src<=0)
    {
        str_src= "";
    }
    char* str = 0;
    TSize count = cstring_count(str_src);
    str = cstring_new(count);
    for (TSize i = 0; i < count; i++)
    {
        str[i] = str_src[i];
    }
    return str;
}

void cstring_free(TPtrHld str_hld)
{
    free((char*)*str_hld);
    *str_hld = 0;
}

char cstring_is_equal(char* str1, char* str2)
{
    if (cstring_count(str1) != cstring_count(str2))
    {
        return 0;
    }
    for (TSize i = 0; ; i++)
    {
        if (str1[i] == 0)
        {
            return 1;
        }
        if (str1[i] != str2[i])
        {
            return 0;
        }
    }
    return 0;
}

char* cstring_from_int(mint i)
{
    char* cstring = cstring_new(30);
    snprintf(cstring,30, "%d", i);
    //sprintf_s(cstring,30, "%d", i);
    return cstring;
}



char* cstring_new_from_const(const char* str)
{
    return cstring_clone((char*)str);
}


char* cstring_from_double(mdouble f)
{
    char* cstring = cstring_new(40);
    snprintf(cstring,40, "%f", f);
    return cstring;
}

cstringList* cstringList_new()
{
    cstringList* l=(cstringList*) mnalloc(sizeof(cstringList));    
    if(!l) assert(l);
    l->list=0;
    l->size=0;
    l->count=0;
    return l;
    
}

cstringList* cstringList_init(cstringList* l,mint size)
{
    if (!l)
    {
        l=cstringList_new();
    }
    l->list=(char**)mnalloc(size* sizeof(char*));
    if(l->list){
        l->size=size;
        l->count=0;

    }else assert(l->list);
    return l;
}

void cstringList_add(cstringList* l,char* str)
{
    if(l->count == l->size){
        l->list =( char**) mnrealloc(l->list,l->size*2*sizeof(char*));
        if(!l->list) assert(l->list);
        l->size=l->size*2;
    }
    l->list[l->count]=str;
    l->count++;

}

char* cstringList_item_at(cstringList* l,mint index)
{
    return l->list[index];
}

char* cstringList_to_new_cstring(cstringList* l)
{
    mint count=0;
    char* str=(char*)mnalloc((255)*sizeof(char));
    mint size=2;
    if(!str) assert(str);
    for (mint i = 0; i < l->count; i++)
    {
        for (mint j = 0;cstringList_item_at(l,i)[j]!=0 ; j++)
        {
            if (count+1 ==size-1)
            {
                str=mnrealloc(str,size*2*sizeof(char));
                if(!str) assert(str);
                size *=2;
            }
            
            str[count]=l->list[i][j];
            count++;
        }
        
    }
    str[count]=0;


    
    return str;
}
