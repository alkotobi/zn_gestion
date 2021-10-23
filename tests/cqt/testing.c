#include "testing.h"
void btn_clicked(void* ctx){
    cqDebug("Iam clicked");
}

QPushButton* QPushButton_test(QWidget* parent)
{
    QPushButton* btn =QPushButton_new_v1("hello",parent);
    QPushButton_onclicked(btn,0,btn_clicked);
    QWidget_show(btn);
    return btn;
}

QLineEdit* QLineEdit_test(QWidget* parent)
{
    QLineEdit* line = QLineEdit_new("hello everyone\n",parent);
    QWidget_show(line);
    return line;
}

QVBoxLayout* QVBoxLayout_test(QWidget* parent)
{
    QVBoxLayout* lay = QVBoxLayout_new(parent);
    return lay;
}
