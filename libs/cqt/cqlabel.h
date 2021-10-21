#pragma once
#include "cqheader.h"

QLabel *QLabel_new(char* text,QWidget* parent,int window_flag);
QString* QLabel_text(QLabel* self);
void QLabel_set_text(QLabel* self,char* text);
