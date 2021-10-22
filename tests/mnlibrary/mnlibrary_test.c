#include "mnlibrary_test.h"

char cstring_test()
{
    print_cyan("\n\n**********\nTESTING CSTRING\n**********\n\n");
    print_yellow("cstring_count>>>\n");
    char res = 1;
    res =  (cstring_count("hello") == 5);
    test_v1(res);
    print_yellow("cstring_new>>>\n");
    char* str=cstring_new(10);
    res =  (cstring_count(str) == 0);
    test_v1(res);
    print_yellow("cstring_clone>>>\n");
    print_yellow("cstring_is_equal>>>\n");
    char* str2 = cstring_clone("hello");
    res = cstring_count(str2) == 5;
    res =res* cstring_is_equal(str2, "hello");
    test_v1(res);
    print_yellow("cstring_free>>>\n");
    cstring_free((TPtrHld)&str2);
    res = str2==0;
    test_v1(res);

    print_yellow("cstring_from_int>>>\n");
    print_yellow("cstring_from_double>>>\n");
    res = cstring_is_equal(cstring_from_int(5), "5");
    res = res * cstring_is_equal(cstring_from_double(5.0), "5.000000");
    test_v1(res);
    print_yellow("cstringList_to_new_cstring>>>\n");
    cstringList* list = cstringList_init(0,255);
    cstringList_add(list,"hi\n");
    cstringList_add(list,"hello\n");
    char* conk=cstringList_to_new_cstring(list);
    print_green(conk);
    res=cstring_is_equal(conk,"hi\nhello\n");
    test_v1(res);
    return res;
}

char mnstring_test()
{
    char res=1;
    print_yellow("mnstring_new>>>\n");
    mnstring str =mnstring_new(100,"hello!!\n");
    printf("%s",str);
    res =cstring_is_equal(str,"hello!!\n");
    strPrm* prm=mnstring_strprm(str);
    res*=prm->size==100 && prm->count==8 && prm->ind==0;
    test_v1(res);
    print_yellow("mnstring_free>>>\n");
    mnstring_free(&str);
    test_v1(str==0);
    print_yellow("mnstring_new_empty>>>\n");
    str =mnstring_new_empty(255);
    res *=cstring_is_equal(str,"");
    prm=mnstring_strprm(str);
    res*=prm->size==255 && prm->count==0 && prm->ind==0;
    test_v1(res);
    mnstring_free(&str);
    print_yellow("mnstring_new_from_cstring>>>\n");
    str =mnstring_new_from_cstring("hi");
    res *=cstring_is_equal(str,"hi");
    prm=mnstring_strprm(str);
    res*=prm->size==2 && prm->count==2 && prm->ind==0;
    test_v1(res);
    //mnstring_free(&str);
    print_yellow("mnstring_new_clone>>>\n");
    str =mnstring_new_clone(str);
    res *=cstring_is_equal(str,"hi");
    prm=mnstring_strprm(str);
    res*=prm->size==2 && prm->count==2 && prm->ind==0;
    test_v1(res);
    //mnstring_free(&str);
    print_yellow("mnstring_grow_size\nmnstring_is_full\nmnstring_count\nmnstring_set_count\n"
    "mnstring_append_cstring>>>\n");

    str=mnstring_append_cstring(str,4," me\n");
    prm=mnstring_strprm(str);
    res *=cstring_is_equal(str,"hi me\n");
    res*=prm->size==6 && prm->count==6 && prm->ind==0;
    test_v1(res);
    print_yellow("mnstring_append_mnstring>>>\n");
    str=mnstring_append_mnstring(str,str);
    prm=mnstring_strprm(str);
    res *=cstring_is_equal(str,"hi me\nhi me\n");
    res*=prm->size==12 && prm->count==12 && prm->ind==0;
    test_v1(res);
    mnstring_free(&str);
    print_yellow("mnstring_from_mint>>>\n");
    str=mnstring_from_mint(12);
    prm=mnstring_strprm(str);
    res *=cstring_is_equal(str,"12");
    res*=prm->size==2 && prm->count==2 && prm->ind==0;
    test_v1(res);
    mnstring_free(&str);
    print_yellow("mnstring_fill_empty_with_char>>>\n");
    str=mnstring_new_empty(10);
    str=mnstring_fill_with_char(str,0,9,0);
    str=mnstring_fill_with_char(str,0,4,'c');
    mnstring_set_count(str,5);
    res=cstring_is_equal(str,"ccccc");
    str=mnstring_fill_with_char(str,0,4,'c');
    test_v1(res);
    return res;
}
