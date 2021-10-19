#ifndef QT4C_H
#define QT4C_H

#define Qt_LeftToRight 0
#define Qt_RightToLeft 1
#define Qt_LayoutDirectionAuto 2
typedef void QApplication ;
typedef void QString ;
typedef void QWidget ;
typedef void QLayout ;
typedef void QBoxLayout ;
typedef void QLayoutItem;
typedef void QVBoxLayout ;
typedef void QHBoxLayout ;
typedef void QVariant;
typedef void QFormLayout;
typedef void QGridLayout;
typedef void QLabel;


/*
                QString
*/


QString* QString_new();
QString* QString_new_from_cstring(const char* str);
void QString_free(QString** s_hld);
char QString_is_empty(QString* s);
char QString_is_right_to_left(QString*s);
double QString_to_double(QString*s);
int QString_to_int(QString*s);
QString* QString_add_cstring(QString*s,char* cstring);
QString* QString_add_QString(QString*s,QString* s_sub);
QString* QString_add_char(QString*s,char c);
char* QString_to_cstring_cpy(QString*s);
void QString_printf(QString* s);
QString* QString_from_int(int n);
QString* QString_from_double(double f);
QString* QString_from_long(long int f);

/*
                QVariant
*/
QVariant* QVariant_new();
QVariant* QVariant_new_from_cstring(char* cstring);
QVariant* QVariant_new_from_int(int n);
QVariant* QVariant_new_from_double(double f);
QVariant* QVariant_new_from_QString(QString* s);//TODO: QVariant_new_from_QString leak possible of memory here
char QVariant_can_convert(QVariant* self,int type_id);
int QVariant_to_int(QVariant* self);
double QVariant_to_double(QVariant* self);
QString* QVariant_to_QString(QVariant* self);
void QVariant_free(QVariant** var_hld);

/*
                QApplication
*/


QApplication* QApplication_new(int argc, char** argv);
QApplication* QApplication_new_no_param();
int QApplication_exec(QApplication* self);
void QApplication_setActiveWindow(QApplication* self,QWidget *active);
QWidget *QApplication_activeWindow(QApplication *self);


/*
                QWidget
*/


QWidget* QWidget_new_window(QWidget *parent);
QWidget* QWidget_new_sheet(QWidget *parent);
QWidget* QWidget_new_drawer(QWidget *parent);
QWidget* QWidget_new_popup(QWidget *parent);
void QWidget_activate_window(QWidget *self);
void QWidget_adjust_size(QWidget *self);
QWidget *QWidget_focus_widget(QWidget *self);
char QWidget_has_focus(QWidget *self) ;
int QWidget_height(QWidget *self);
char QWidget_is_active_window(QWidget *self);
char QWidget_is_ancestor_of(QWidget *self,const QWidget *child);
char QWidget_is_enabled(QWidget *self);
char QWidget_is_full_screen(QWidget *self);
char QWidget_is_hidden(QWidget *self);
char QWidget_is_visible(QWidget *self);
char QWidget_is_window(QWidget *self);
QLayout *QWidget_layout(QWidget *self);
int  QWidget_layoutDirection(QWidget *self);
QWidget *QWidget_next_in_focus_chain(QWidget *self);
QWidget *QWidget_parent_widget(QWidget *self);
QWidget *QWidget_previous_in_focus_chain(QWidget *self);
void QWidget_scroll(QWidget *self,int dx, int dy);
void QWidget_set_parent(QWidget *self,QWidget *parent);
int QWidget_width(QWidget *self);
char QWidget_close(QWidget *self);
void QWidget_hide(QWidget *self);
void QWidget_lower(QWidget *self);
void QWidget_raise(QWidget *self);
void QWidget_repaint(QWidget *self);
void QWidget_set_disabled(QWidget *self,char disabled_state);
void QWidget_set_visible(QWidget *self,char hidden_state);
void QWidget_set_style_sheet(QWidget *self,QString* style_sheet);
void QWidget_set_window_modified(QWidget *self,char modified_state);
void QWidget_set_window_title(QWidget *self,QString* window_title);
void QWidget_show(QWidget *self);
void QWidget_show_full_screen(QWidget *self);
void QWidget_show_maximized(QWidget *self);
void QWidget_show_minimized(QWidget *self);
void QWidget_show_normal(QWidget *self);
void QWidget_update(QWidget *self);
void QWidget_free(QWidget ** wid_hld);



/*
         QLayout
*/

//alignement

#define Qt_AlignLeft 0x0001//Aligns with the left edge.
#define Qt_AlignRight 0x0002//Aligns with the right edge.
#define Qt_AlignHCenter 0x0004//Centers horizontally in the available space.
#define Qt_AlignJustify 0x0008//Justifies the text in the available space.
#define Qt_AlignTop 0x0020//Aligns with the top.
#define Qt_AlignBottom 0x0040//Aligns with the bottom.
#define Qt_AlignVCenter 0x0080//Centers vertically in the available space.
#define Qt_AlignBaseline 0x0100//Aligns with the baseline
#define Qt_AlignCenter Qt_AlignVCenter | Qt_AlignHCenter//Centers in both dimensions
#define Qt_AlignAbsolute 0x0010//If  the widget's layout direction is Qt::RightToLeft (instead of Qt::LeftToRight, the default), Qt::AlignLeft refers to the right edge and Qt::AlignRight to the left edge. This is normally the desired behavior. If you want Qt::AlignLeft to always mean "left" and Qt::AlignRight to always mean "right", combine the flag with Qt::AlignAbsolute.
#define Qt_AlignLeading Qt_AlignLeft //Synonym for Qt::AlignLeft.
#define Qt_AlignTrailing Qt_AlignRight //Synonym for Qt::AlignRight.

//directions

#define QBoxLayout_LeftToRight 0//Horizontal from left to right.
#define QBoxLayout_RightToLeft 1//Horizontal from right to left.
#define QBoxLayout_TopToBottom 2//Vertical from top to bottom.
#define QBoxLayout_BottomToTop 3//Vertical from bottom to top.

QBoxLayout* QBoxLayout_new_left_to_right(QWidget* parent);
QBoxLayout* QBoxLayout_new_right_to_left(QWidget* parent);
QBoxLayout* QBoxLayout_new_top_to_bottom(QWidget* parent);
QBoxLayout* QBoxLayout_new_bottom_to_top(QWidget* parent);
void QBoxLayout_free(QBoxLayout** layout_hld);
void QBoxLayout_add_layout(QBoxLayout* self,QLayout* layout);
void QBoxLayout_add_spacing(QBoxLayout* self,int size);
void QBoxLayout_add_stretch(QBoxLayout* self,int stretch);
void QBoxLayout_add_widget
(QBoxLayout *self,QWidget *widget, int stretch,int alignement);
void QBoxLayout_insertLayout
(QBoxLayout *self,int index, QLayout *layout, int stretch);
void QBoxLayout_insert_spacing(QBoxLayout *self,int index, int size);
void QBoxLayout_insert_stretch(QBoxLayout *self,int index, int stretch);
void QBoxLayout_insert_widget
(QBoxLayout *self,int index, QWidget *widget, int stretch , int alignment );
void QBoxLayout_set_direction(QBoxLayout *self,int direction);
void QBoxLayout_set_pacing(QBoxLayout *self,int spacing);
void QBoxLayout_set_stretch(QBoxLayout *self,int index, int stretch);
int QBoxLayout_count(QBoxLayout *self);
QLayoutItem* QBoxLayout_item_at(QBoxLayout *self,int index);
QLayout* QLayoutItem_layout(QLayoutItem* self);
QWidget* QLayoutItem_widget(QLayoutItem* self);
QVBoxLayout* QVBoxLayout_new(QWidget *parent);
void QVBoxLayout_free(QVBoxLayout** vbox_hld);
QHBoxLayout* QHBoxLayout_new(QWidget *parent);
void QHBoxLayout_free(QHBoxLayout** vbox_hld);
QFormLayout* QFormLayout_new(QWidget* parent);
void QFormLayout_add_widget_as_row_with_lable(QFormLayout* self,QWidget* label,QWidget*  field);
void QFormLayout_add_layout_as_row_with_label(QFormLayout* self,QWidget* label,QLayout*  field);
void QFormLayout_add_widget_as_row_auto_lable(QFormLayout* self,char* label_cstring,QWidget*  field);
void QFormLayout_add_layout_as_row_auto_lable(QFormLayout* self,char* label_cstring,QLayout*  field);
void QFormLayout_add_widget_as_row(QFormLayout* self,QWidget*  field);
void QFormLayout_add_layout_as_row(QFormLayout* self,QLayout*  field);
QWidget* QFormLayout_lable_for_widget_field(QFormLayout* self,QWidget*  field);
QWidget* QFormLayout_lable_for_layout_field(QFormLayout* self,QLayout*  field);
void QFormLayout_remove_row_contains_widget(QFormLayout* self,QWidget*  field);
void QFormLayout_remove_row_contains_layout(QFormLayout* self,QLayout*  field);
void QFormLayout_remove_row_at(QFormLayout* self,int index);
int QFormLayout_row_count(QFormLayout* self);
void QFormLayout_set_form_alignment(QFormLayout* self,int alignement);
void QFormLayout_set_horizontal_spacing(QFormLayout* self,int spacing);
void QFormLayout_set_label_alignment(QFormLayout* self,int alignement);
void QFormLayout_set_vertical_spacing(QFormLayout* self,int spacing);
int  QFormLayout_vertical_spacing(QFormLayout* self);
int  QFormLayout_horizontal_spacing(QFormLayout* self);
int  QFormLayout_count(QFormLayout* self);
void QFormLayout_free(QFormLayout** layout_hld);
QGridLayout* QGridLayout_new(QWidget* parent);
void QGridLayout_add_layout(QGridLayout* self ,QLayout* layout,int row,int col,int alignment);
void QGridLayout_add_widget(QGridLayout* self ,QWidget* widget,int row,int col,int alignment);
int  QGridLayout_col_count(QGridLayout* self);
int QGridLayout_row_count(QGridLayout* self);
void QGridLayout_set_alignment(QGridLayout* self,int alignement);
void QGridLayout_set_horizontal_spacing(QGridLayout* self,int spacing);
void QGridLayout_set_vertical_spacing(QGridLayout* self,int spacing);
int  QGridLayout_vertical_spacing(QGridLayout* self);
int  QGridLayout_horizontal_spacing(QGridLayout* self);
int  QGridLayout_count(QGridLayout* self);
void QGridLayout_free(QGridLayout** layout_hld);
#endif // QT4C_H

/*
         QLabel
*/

//enum Qt::WindowTypeflags Qt::WindowFlags
//window_flags
#define Qt_Widget 0x00000000//This is the default type for QWidget. Widgets of this type are child widgets if they have a parent, and independent windows if they have no parent. See also Qt::Window and Qt::SubWindow.
#define Qt_Window 0x00000001//Indicates that the widget is a window, usually with a window system frame and a title bar, irrespective of whether the widget has a parent or not. Note that it is not possible to unset this flag if the widget does not have a parent.
#define Qt_Dialog 0x00000002 | Qt_Window//Indicates that the widget is a window that should be decorated as a dialog (i.e., typically no maximize or minimize buttons in the title bar). This is the default type for QDialog. If you want to use it as a modal dialog, it should be launched from another window, or have a parent and used with the QWidget::windowModality property. If you make it modal, the dialog will prevent other top-level windows in the application from getting any input. We refer to a top-level window that has a parent as a secondary window.
#define Qt_Sheet 0x00000004 | Qt_Window//Indicates that the window is a sheet on macOS. Since using a sheet implies window modality, the recommended way is to use QWidget::setWindowModality(), or QDialog::open(), instead.
#define Qt_Drawer Qt_Sheet | Qt_Dialog//Indicates that the widget is a drawer on macOS.
#define Qt_Popup 0x00000008 | Qt_Window//Indicates that the widget is a pop-up top-level window, i.e. that it is modal, but has a window system frame appropriate for pop-up menus.
#define Qt_Tool Qt_Popup | Qt_Dialog//Indicates that the widget is a tool window. A tool window is often a small window with a smaller than usual title bar and decoration, typically used for collections of tool buttons. If there is a parent, the tool window will always be kept on top of it. If there isn't a parent, you may consider using Qt::WindowStaysOnTopHint as well. If the window system supports it, a tool window can be decorated with a somewhat lighter frame. It can also be combined with Qt::FramelessWindowHint. On macOS, tool windows correspond to the NSPanel class of windows. This means that the window lives on a level above normal windows making it impossible to put a normal window on top of it. By default, tool windows will disappear when the application is inactive. This can be controlled by the Qt::WA_MacAlwaysShowToolWindow attribute.
#define Qt_ToolTip Qt_Popup | Qt_Sheet//Indicates that the widget is a tooltip. This is used internally to implement tooltips.
#define Qt_SplashScreen Qt_ToolTip | Qt_Dialog//Indicates that the window is a splash screen. This is the default type for QSplashScreen.
#define Qt_Desktop 0x00000010 | Qt_Window//Indicates that this widget is the desktop. This is the type for QDesktopWidget.
#define Qt_SubWindow 0x00000012//Indicates that this widget is a sub-window, such as a QMdiSubWindow widget.
#define Qt_ForeignWindow 0x00000020 | Qt_Window//Indicates that this window object is a handle representing a native platform window created by another process or by manually using native code.
#define Qt_CoverWindow 0x00000040 | Qt_Window//Indicates that the window represents a cover window, which is shown when the application is minimized on some platforms.
QLabel *QLabel_new(char* text,QWidget* parent,int window_flag);
QString* QLabel_text(QLabel* self);
void QLabel_set_text(QLabel* self,char* text);
