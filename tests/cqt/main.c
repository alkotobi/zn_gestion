#include <stdio.h>
#include "testing.h"
int main(int argc, char const *argv[])
{
    QApplication* app= QApplication_new(argc,argv);
    QWidget* wid = QWidget_new_window(0);
    QWidget_show(wid);
    
    
    QVBoxLayout* l= QVBoxLayout_test(wid);
    QBoxLayout_add_widget(l,QLineEdit_test(wid),0,0);
    QBoxLayout_add_widget(l,QPushButton_test(wid),0,0);
    QApplication_exec(app);
    printf("bismi allah\n");
    return 0;
}

