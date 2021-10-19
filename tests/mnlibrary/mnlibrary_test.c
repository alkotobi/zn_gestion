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
