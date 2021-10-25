#include "testing.h"
char do_test()
{
    char res =1;
    res*=cstring_test();
    res*=mnstring_test();
    res*=mntree_test();
    return res;
}
