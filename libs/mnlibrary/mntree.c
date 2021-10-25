#include "mntree.h"
Ttree* Ttree_new()
{
    Ttree* t = (Ttree*) mnalloc(sizeof(Ttree));
    if (t)
    {
        t->childs=0;
        t->data=0;
        t->parent=0;
    }else assert(t);
    return t;
}

Ttree* Ttree_init(Ttree* t,TVar data,Ttree* parent)
{
    assert(data);
    if (!t)
    {
        t=Ttree_new();
    }
    t->data =data;
    t->parent = parent;
    return t;
}

Ttree** Ttree_clean(Ttree** t_hld,TFVoidPtrHld free_data)
{
    free_data(&(*t_hld)->data);
    if ((*t_hld)->childs)
    {
        for (TSize i = 0; i < (*t_hld)->childs->count; i++)
        {
            Ttree_clean((Ttree**)&((*t_hld)->childs->data[i]),free_data);
        }
        
    }
    return t_hld;
}

void TTree_free(Ttree** T_hld)
{
    TArray* childs = (*T_hld)->childs;
    mnfree(*T_hld);
    (*T_hld)=0;
    if (childs)
    {
        for (TSize i = 0; i < childs->count; i++)
        {
            TTree_free((Ttree**)&childs->data[i]);
        }
    }
    
}

Ttree* Ttree_add_child(Ttree* t,TVar data)
{
    assert(t);
    assert(data);
    if (!t->childs)
    {       
        t->childs=TArray_init(0);
    }
    Ttree* tree = Ttree_init(0,data,t);
    TArray_add(t->childs,tree);
    return tree;
}

//TODO: test
cstringList* Ttree_to_string_list(Ttree* t,char* ident,char*(*to_str)(TVar)){
    cstringList* l = cstringList_init(0,255);
    cstringList_add(l,to_str(t->data));
    cstringList_add(l,cstring_clone("\n"));
    if (t->childs)
    {
      cstringList* l2;
      for (mint i = 0; i < t->childs->count; i++){
          l2= Ttree_to_string_list(t->childs->data[i],ident,to_str);
          for (mint j = 0; j < l2->count; j++)
          {
             cstringList_add(l,cstring_concat(2,ident,l2->list[j]));
          }
          cstringList_free(cstringList_clear(&l2));
          
      }  
    }
    return l;
}

//TODO: test
char* Ttree_to_string(Ttree* t,char* ident,char*(*to_str)(TVar)){
    cstringList* l= Ttree_to_string_list(t,ident,to_str);
    char* str=cstringList_to_new_cstring(l);
    cstringList_free(cstringList_clear(&l));
    return str;
}