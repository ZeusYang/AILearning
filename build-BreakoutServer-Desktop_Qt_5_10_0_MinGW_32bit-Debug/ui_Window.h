/********************************************************************************
** Form generated from reading UI file 'Window.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Window
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPlainTextEdit *terminalPlainTextEdit;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *Label;
    QLineEdit *clientLineEdit;
    QLabel *Label_2;
    QLineEdit *onlineLineEdit;
    QLabel *Label_3;
    QLineEdit *playerLineEdit;
    QLabel *Label_4;
    QLineEdit *LineEdit;
    QLabel *iPv4Label;
    QComboBox *IPv4ComboBox;
    QTableView *clientTableView;

    void setupUi(QWidget *Window)
    {
        if (Window->objectName().isEmpty())
            Window->setObjectName(QStringLiteral("Window"));
        Window->resize(1000, 700);
        Window->setStyleSheet(QString::fromUtf8("QPalette{background:#464646;}*{outline:0px;color:#F0F0F0;}\n"
"\n"
"QWidget[form=\"true\"],QLabel[frameShape=\"1\"]{\n"
"border:1px solid #111214;\n"
"border-radius:0px;\n"
"}\n"
"\n"
"\n"
"\n"
"QWidget[form=\"bottom\"]{\n"
"background:#242629;\n"
"}\n"
"\n"
"QWidget[form=\"bottom\"] .QFrame{\n"
"border:1px solid #D7E2E9;\n"
"}\n"
"\n"
"QWidget[form=\"bottom\"] QLabel,QWidget[form=\"title\"] QLabel{\n"
"border-radius:0px;\n"
"color:#D7E2E9;\n"
"background:none;\n"
"border-style:none;\n"
"}\n"
"\n"
"QWidget[form=\"title\"],QWidget[nav=\"left\"],QWidget[nav=\"top\"] QAbstractButton{\n"
"border-style:none;\n"
"border-radius:0px;\n"
"padding:5px;\n"
"color:#D7E2E9;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #242629,stop:1 #141518);\n"
"}\n"
"\n"
"QWidget[nav=\"top\"] QAbstractButton:hover,QWidget[nav=\"top\"] QAbstractButton:pressed,QWidget[nav=\"top\"] QAbstractButton:checked{\n"
"border-style:solid;\n"
"border-width:0px 0px 2px 0px;\n"
"padding:4px 4px 2px 4px;\n"
"border-color:#00BB9E;"
                        "\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #007DC4,stop:1 #0074BF);\n"
"}\n"
"\n"
"QWidget[nav=\"left\"] QAbstractButton{\n"
"border-radius:0px;\n"
"color:#D7E2E9;\n"
"background:none;\n"
"border-style:none;\n"
"}\n"
"\n"
"QWidget[nav=\"left\"] QAbstractButton:hover{\n"
"color:#FFFFFF;\n"
"background-color:#00BB9E;\n"
"}\n"
"\n"
"QWidget[nav=\"left\"] QAbstractButton:checked,QWidget[nav=\"left\"] QAbstractButton:pressed{\n"
"color:#D7E2E9;\n"
"border-style:solid;\n"
"border-width:0px 0px 0px 2px;\n"
"padding:4px 4px 4px 2px;\n"
"border-color:#00BB9E;\n"
"background-color:#1F2026;\n"
"}\n"
"\n"
"QWidget[video=\"true\"] QLabel{\n"
"color:#D7E2E9;\n"
"border:1px solid #111214;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #242629,stop:1 #141518);\n"
"}\n"
"\n"
"QWidget[video=\"true\"] QLabel:focus{\n"
"border:1px solid #00BB9E;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #007DC4,stop:1 #0074BF);\n"
"}\n"
"\n"
"QLineEdit,QTextEdit,QPlainTex"
                        "tEdit,QSpinBox,QDoubleSpinBox,QComboBox,QDateEdit,QTimeEdit,QDateTimeEdit{\n"
"border:1px solid #111214;\n"
"border-radius:3px;\n"
"padding:2px;\n"
"background:none;\n"
"selection-background-color:#242629;\n"
"selection-color:#D7E2E9;\n"
"}\n"
"\n"
"QLineEdit:focus,QTextEdit:focus,QPlainTextEdit:focus,QSpinBox:focus,\n"
"QDoubleSpinBox:focus,QComboBox:focus,QDateEdit:focus,QTimeEdit:focus,\n"
"QDateTimeEdit:focus,QLineEdit:hover,QTextEdit:hover,QPlainTextEdit:hover,\n"
"QSpinBox:hover,QDoubleSpinBox:hover,QComboBox:hover,QDateEdit:hover,\n"
"QTimeEdit:hover,QDateTimeEdit:hover{\n"
"border:1px solid #111214;\n"
"}\n"
"\n"
"QLineEdit[echoMode=\"2\"]{\n"
"lineedit-password-character:9679;\n"
"}\n"
"\n"
".QFrame{\n"
"border:1px solid #111214;\n"
"border-radius:3px;\n"
"}\n"
"\n"
".QGroupBox{\n"
"border:1px solid #111214;\n"
"border-radius:5px;\n"
"margin-top:3ex;\n"
"}\n"
"\n"
".QGroupBox::title{\n"
"subcontrol-origin:margin;\n"
"position:relative;\n"
"left:10px;\n"
"}\n"
"\n"
"QPushButton,.QToolButton{\n"
"border"
                        "-style:none;\n"
"border:1px solid #111214;\n"
"color:#D7E2E9;\n"
"padding:5px;\n"
"min-height:15px;\n"
"border-radius:5px;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #242629,stop:1 #141518);\n"
"}\n"
"\n"
".QPushButton:hover,.QToolButton:hover{\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #007DC4,stop:1 #0074BF);\n"
"}\n"
"\n"
".QPushButton:pressed,.QToolButton:pressed{\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #242629,stop:1 #141518);\n"
"}\n"
"\n"
".QToolButton::menu-indicator{\n"
"image:None;\n"
"background:transparent;\n"
"}\n"
"\n"
"QToolButton#btnMenu,QPushButton#btnMenu_Min,QPushButton#btnMenu_Max,QPushButton#btnMenu_Close{\n"
"border-radius:3px;\n"
"color:#D7E2E9;\n"
"padding:3px;\n"
"margin:0px;\n"
"background:none;\n"
"border-style:none;\n"
"}\n"
"\n"
"QToolButton#btnMenu:hover,QPushButton#btnMenu_Min:hover,QPushButton#btnMenu_Max:hover{\n"
"color:#FFFFFF;\n"
"margin:1px 1px 2px 1px;\n"
"background-color:rgba(51,127,209,230)"
                        ";\n"
"}\n"
"\n"
"QPushButton#btnMenu_Close:hover{\n"
"color:#FFFFFF;\n"
"margin:1px 1px 2px 1px;\n"
"background-color:rgba(238,0,0,128);\n"
"}\n"
"\n"
"QRadioButton::indicator{\n"
"width:15px;\n"
"height:15px;\n"
"}\n"
"\n"
"QRadioButton::indicator::unchecked{\n"
"image:url(:/qss/darkblack/radiobutton_unchecked.png);\n"
"}\n"
"\n"
"QRadioButton::indicator::unchecked:disabled{\n"
"image:url(:/qss/darkblack/radiobutton_unchecked_disable.png);\n"
"}\n"
"\n"
"QRadioButton::indicator::checked{\n"
"image:url(:/qss/darkblack/radiobutton_checked.png);\n"
"}\n"
"\n"
"QRadioButton::indicator::checked:disabled{\n"
"image:url(:/qss/darkblack/radiobutton_checked_disable.png);\n"
"}\n"
"\n"
"QGroupBox::indicator,QTreeWidget::indicator,QListWidget::indicator{\n"
"padding:0px -3px 0px 3px;\n"
"}\n"
"\n"
"QCheckBox::indicator,QGroupBox::indicator,QTreeWidget::indicator,QListWidget::indicator{\n"
"width:13px;\n"
"height:13px;\n"
"}\n"
"\n"
"QCheckBox::indicator:unchecked,QGroupBox::indicator:unchecked,QTreeWidget::indicator:unc"
                        "hecked,QListWidget::indicator:unchecked{\n"
"image:url(:/qss/darkblack/checkbox_unchecked.png);\n"
"}\n"
"\n"
"QCheckBox::indicator:unchecked:disabled,QGroupBox::indicator:unchecked:disabled,QTreeWidget::indicator:unchecked:disabled,QListWidget::indicator:disabled{\n"
"image:url(:/qss/darkblack/checkbox_unchecked_disable.png);\n"
"}\n"
"\n"
"QCheckBox::indicator:checked,QGroupBox::indicator:checked,QTreeWidget::indicator:checked,QListWidget::indicator:checked{\n"
"image:url(:/qss/darkblack/checkbox_checked.png);\n"
"}\n"
"\n"
"QCheckBox::indicator:checked:disabled,QGroupBox::indicator:checked:disabled,QTreeWidget::indicator:checked:disabled,QListWidget::indicator:checked:disabled{\n"
"image:url(:/qss/darkblack/checkbox_checked_disable.png);\n"
"}\n"
"\n"
"QCheckBox::indicator:indeterminate,QGroupBox::indicator:indeterminate,QTreeWidget::indicator:indeterminate,QListWidget::indicator:indeterminate{\n"
"image:url(:/qss/darkblack/checkbox_parcial.png);\n"
"}\n"
"\n"
"QCheckBox::indicator:indeterminate:disabled,QG"
                        "roupBox::indicator:indeterminate:disabled,QTreeWidget::indicator:indeterminate:disabled,QListWidget::indicator:indeterminate:disabled{\n"
"image:url(:/qss/darkblack/checkbox_parcial_disable.png);\n"
"}\n"
"\n"
"QTimeEdit::up-button,QDateEdit::up-button,QDateTimeEdit::up-button,QDoubleSpinBox::up-button,QSpinBox::up-button{\n"
"image:url(:/qss/darkblack/add_top.png);\n"
"width:10px;\n"
"height:10px;\n"
"padding:2px 5px 0px 0px;\n"
"}\n"
"\n"
"QTimeEdit::down-button,QDateEdit::down-button,QDateTimeEdit::down-button,QDoubleSpinBox::down-button,QSpinBox::down-button{\n"
"image:url(:/qss/darkblack/add_bottom.png);\n"
"width:10px;\n"
"height:10px;\n"
"padding:0px 5px 2px 0px;\n"
"}\n"
"\n"
"QTimeEdit::up-button:pressed,QDateEdit::up-button:pressed,QDateTimeEdit::up-button:pressed,QDoubleSpinBox::up-button:pressed,QSpinBox::up-button:pressed{\n"
"top:-2px;\n"
"}\n"
"  \n"
"QTimeEdit::down-button:pressed,QDateEdit::down-button:pressed,QDateTimeEdit::down-button:pressed,QDoubleSpinBox::down-button:pressed,QSpinBox::dow"
                        "n-button:pressed,QSpinBox::down-button:pressed{\n"
"bottom:-2px;\n"
"}\n"
"\n"
"QComboBox::down-arrow,QDateEdit[calendarPopup=\"true\"]::down-arrow,QTimeEdit[calendarPopup=\"true\"]::down-arrow,QDateTimeEdit[calendarPopup=\"true\"]::down-arrow{\n"
"image:url(:/qss/darkblack/add_bottom.png);\n"
"width:10px;\n"
"height:10px;\n"
"right:2px;\n"
"}\n"
"\n"
"QComboBox::drop-down,QDateEdit::drop-down,QTimeEdit::drop-down,QDateTimeEdit::drop-down{\n"
"subcontrol-origin:padding;\n"
"subcontrol-position:top right;\n"
"width:15px;\n"
"border-left-width:0px;\n"
"border-left-style:solid;\n"
"border-top-right-radius:3px;\n"
"border-bottom-right-radius:3px;\n"
"border-left-color:#111214;\n"
"}\n"
"\n"
"QComboBox::drop-down:on{\n"
"top:1px;\n"
"}\n"
"\n"
"QMenuBar::item{\n"
"color:#D7E2E9;\n"
"background-color:#242629;\n"
"margin:0px;\n"
"padding:3px 10px;\n"
"}\n"
"\n"
"QMenu,QMenuBar,QMenu:disabled,QMenuBar:disabled{\n"
"color:#D7E2E9;\n"
"background-color:#242629;\n"
"border:1px solid #111214;\n"
"margin:0px;\n"
"}\n"
"\n"
""
                        "QMenu::item{\n"
"padding:3px 20px;\n"
"}\n"
"\n"
"QMenu::indicator{\n"
"width:13px;\n"
"height:13px;\n"
"}\n"
"\n"
"QMenu::item:selected,QMenuBar::item:selected{\n"
"color:#D7E2E9;\n"
"border:0px solid #111214;\n"
"background:#007DC4;\n"
"}\n"
"\n"
"QMenu::separator{\n"
"height:1px;\n"
"background:#111214;\n"
"}\n"
"\n"
"QProgressBar{\n"
"min-height:10px;\n"
"background:#242629;\n"
"border-radius:5px;\n"
"text-align:center;\n"
"border:1px solid #242629;\n"
"}\n"
"\n"
"QProgressBar:chunk{\n"
"border-radius:5px;\n"
"background-color:#111214;\n"
"}\n"
"\n"
"QSlider::groove:horizontal{\n"
"background:#242629;\n"
"height:8px;\n"
"border-radius:4px;\n"
"}\n"
"\n"
"QSlider::add-page:horizontal{\n"
"background:#242629;\n"
"height:8px;\n"
"border-radius:4px;\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal{\n"
"background:#111214;\n"
"height:8px;\n"
"border-radius:4px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal{\n"
"width:13px;\n"
"margin-top:-3px;\n"
"margin-bottom:-3px;\n"
"border-radius:6px;\n"
"background:qradialgradient"
                        "(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0.6 #1F2026,stop:0.8 #111214);\n"
"}\n"
"\n"
"QSlider::groove:vertical{\n"
"width:8px;\n"
"border-radius:4px;\n"
"background:#242629;\n"
"}\n"
"\n"
"QSlider::add-page:vertical{\n"
"width:8px;\n"
"border-radius:4px;\n"
"background:#242629;\n"
"}\n"
"\n"
"QSlider::sub-page:vertical{\n"
"width:8px;\n"
"border-radius:4px;\n"
"background:#111214;\n"
"}\n"
"\n"
"QSlider::handle:vertical{\n"
"height:14px;\n"
"margin-left:-3px;\n"
"margin-right:-3px;\n"
"border-radius:6px;\n"
"background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0.6 #1F2026,stop:0.8 #111214);\n"
"}\n"
"\n"
"QScrollBar:horizontal{\n"
"background:#242629;\n"
"padding:0px;\n"
"border-radius:6px;\n"
"max-height:12px;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal{\n"
"background:#0074BF;\n"
"min-width:50px;\n"
"border-radius:6px;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal:hover{\n"
"background:#111214;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal:pressed{\n"
"background:#"
                        "111214;\n"
"}\n"
"\n"
"QScrollBar::add-page:horizontal{\n"
"background:none;\n"
"}\n"
"\n"
"QScrollBar::sub-page:horizontal{\n"
"background:none;\n"
"}\n"
"\n"
"QScrollBar::add-line:horizontal{\n"
"background:none;\n"
"}\n"
"\n"
"QScrollBar::sub-line:horizontal{\n"
"background:none;\n"
"}\n"
"\n"
"QScrollBar:vertical{\n"
"background:#242629;\n"
"padding:0px;\n"
"border-radius:6px;\n"
"max-width:12px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical{\n"
"background:#0074BF;\n"
"min-height:50px;\n"
"border-radius:6px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover{\n"
"background:#111214;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:pressed{\n"
"background:#111214;\n"
"}\n"
"\n"
"QScrollBar::add-page:vertical{\n"
"background:none;\n"
"}\n"
"\n"
"QScrollBar::sub-page:vertical{\n"
"background:none;\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical{\n"
"background:none;\n"
"}\n"
"\n"
"QScrollBar::sub-line:vertical{\n"
"background:none;\n"
"}\n"
"\n"
"QScrollArea{\n"
"border:0px;\n"
"}\n"
"\n"
"QTreeView,QListView,QTableView,Q"
                        "TabWidget::pane{\n"
"border:1px solid #111214;\n"
"selection-background-color:#007DC4;\n"
"selection-color:#D7E2E9;\n"
"alternate-background-color:#0074BF;\n"
"gridline-color:#111214;\n"
"}\n"
"\n"
"QTreeView::branch:closed:has-children{\n"
"margin:4px;\n"
"border-image:url(:/qss/darkblack/branch_open.png);\n"
"}\n"
"\n"
"QTreeView::branch:open:has-children{\n"
"margin:4px;\n"
"border-image:url(:/qss/darkblack/branch_close.png);\n"
"}\n"
"\n"
"QTreeView,QListView,QTableView,QSplitter::handle,QTreeView::branch{\n"
"background:#1F2026;\n"
"}\n"
"\n"
"QTableView::item:selected,QListView::item:selected,QTreeView::item:selected{\n"
"color:#D7E2E9;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #242629,stop:1 #141518);\n"
"}\n"
"\n"
"QTableView::item:hover,QListView::item:hover,QTreeView::item:hover{\n"
"color:#D7E2E9;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #007DC4,stop:1 #0074BF);\n"
"}\n"
"\n"
"QTableView::item,QListView::item,QTreeView::item{\n"
"padding:1px;\n"
""
                        "margin:0px;\n"
"}\n"
"\n"
"QHeaderView::section,QTableCornerButton:section{\n"
"padding:3px;\n"
"margin:0px;\n"
"color:#D7E2E9;\n"
"border:1px solid #111214;\n"
"border-left-width:0px;\n"
"border-right-width:1px;\n"
"border-top-width:0px;\n"
"border-bottom-width:1px;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #007DC4,stop:1 #0074BF);\n"
"}\n"
"\n"
"QTabBar::tab{\n"
"border:1px solid #111214;\n"
"color:#D7E2E9;\n"
"margin:0px;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #007DC4,stop:1 #0074BF);\n"
"}\n"
"\n"
"QTabBar::tab:selected,QTabBar::tab:hover{\n"
"border-style:solid;\n"
"border-color:#00BB9E;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #242629,stop:1 #141518);\n"
"}\n"
"\n"
"QTabBar::tab:top,QTabBar::tab:bottom{\n"
"padding:3px 8px 3px 8px;\n"
"}\n"
"\n"
"QTabBar::tab:left,QTabBar::tab:right{\n"
"padding:8px 3px 8px 3px;\n"
"}\n"
"\n"
"QTabBar::tab:top:selected,QTabBar::tab:top:hover{\n"
"border-width:2px 0px 0px 0px;\n"
"}\n"
"\n"
""
                        "QTabBar::tab:right:selected,QTabBar::tab:right:hover{\n"
"border-width:0px 0px 0px 2px;\n"
"}\n"
"\n"
"QTabBar::tab:bottom:selected,QTabBar::tab:bottom:hover{\n"
"border-width:0px 0px 2px 0px;\n"
"}\n"
"\n"
"QTabBar::tab:left:selected,QTabBar::tab:left:hover{\n"
"border-width:0px 2px 0px 0px;\n"
"}\n"
"\n"
"QTabBar::tab:first:top:selected,QTabBar::tab:first:top:hover,QTabBar::tab:first:bottom:selected,QTabBar::tab:first:bottom:hover{\n"
"border-left-width:1px;\n"
"border-left-color:#111214;\n"
"}\n"
"\n"
"QTabBar::tab:first:left:selected,QTabBar::tab:first:left:hover,QTabBar::tab:first:right:selected,QTabBar::tab:first:right:hover{\n"
"border-top-width:1px;\n"
"border-top-color:#111214;\n"
"}\n"
"\n"
"QTabBar::tab:last:top:selected,QTabBar::tab:last:top:hover,QTabBar::tab:last:bottom:selected,QTabBar::tab:last:bottom:hover{\n"
"border-right-width:1px;\n"
"border-right-color:#111214;\n"
"}\n"
"\n"
"QTabBar::tab:last:left:selected,QTabBar::tab:last:left:hover,QTabBar::tab:last:right:selected,QTabBar::tab:last:ri"
                        "ght:hover{\n"
"border-bottom-width:1px;\n"
"border-bottom-color:#111214;\n"
"}\n"
"\n"
"QToolBox::tab,QGroupBox#gboxDevicePanel,QGroupBox#gboxDeviceTitle,QFrame#gboxDevicePanel,QFrame#gboxDeviceTitle{\n"
"padding:3px;\n"
"border-radius:5px;\n"
"color:#D7E2E9;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #242629,stop:1 #141518);\n"
"}\n"
"\n"
"QToolTip{\n"
"border:0px solid #D7E2E9;\n"
"padding:1px;\n"
"color:#D7E2E9;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #242629,stop:1 #141518);\n"
"}\n"
"\n"
"QToolBox::tab:selected{\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #007DC4,stop:1 #0074BF);\n"
"}\n"
"\n"
"QPrintPreviewDialog QToolButton{\n"
"border:0px solid #D7E2E9;\n"
"border-radius:0px;\n"
"margin:0px;\n"
"padding:3px;\n"
"background:none;\n"
"}\n"
"\n"
"QColorDialog QPushButton,QFileDialog QPushButton{\n"
"min-width:80px;\n"
"}\n"
"\n"
"QToolButton#qt_calendar_prevmonth{\n"
"icon-size:0px;\n"
"min-width:20px;\n"
"image:url(:/qss/dark"
                        "black/calendar_prevmonth.png);\n"
"}\n"
"\n"
"QToolButton#qt_calendar_nextmonth{\n"
"icon-size:0px;\n"
"min-width:20px;\n"
"image:url(:/qss/darkblack/calendar_nextmonth.png);\n"
"}\n"
"\n"
"QToolButton#qt_calendar_prevmonth,QToolButton#qt_calendar_nextmonth,QToolButton#qt_calendar_monthbutton,QToolButton#qt_calendar_yearbutton{\n"
"border:0px solid #D7E2E9;\n"
"border-radius:3px;\n"
"margin:3px 3px 3px 3px;\n"
"padding:3px;\n"
"background:none;\n"
"}\n"
"\n"
"QToolButton#qt_calendar_prevmonth:hover,QToolButton#qt_calendar_nextmonth:hover,QToolButton#qt_calendar_monthbutton:hover,QToolButton#qt_calendar_yearbutton:hover,QToolButton#qt_calendar_prevmonth:pressed,QToolButton#qt_calendar_nextmonth:pressed,QToolButton#qt_calendar_monthbutton:pressed,QToolButton#qt_calendar_yearbutton:pressed{\n"
"border:1px solid #111214;\n"
"}\n"
"\n"
"QCalendarWidget QSpinBox#qt_calendar_yearedit{\n"
"margin:2px;\n"
"}\n"
"\n"
"QCalendarWidget QToolButton::menu-indicator{\n"
"image:None;\n"
"}\n"
"\n"
"QCalendarWidget QTableView{"
                        "\n"
"border-width:0px;\n"
"}\n"
"\n"
"QCalendarWidget QWidget#qt_calendar_navigationbar{\n"
"border:1px solid #111214;\n"
"border-width:1px 1px 0px 1px;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #242629,stop:1 #141518);\n"
"}\n"
"\n"
"QComboBox QAbstractItemView::item{\n"
"min-height:20px;\n"
"min-width:10px;\n"
"}\n"
"\n"
"QTableView[model=\"true\"]::item{\n"
"padding:0px;\n"
"margin:0px;\n"
"}\n"
"\n"
"QTableView QLineEdit,QTableView QComboBox,QTableView QSpinBox,QTableView QDoubleSpinBox,QTableView QDateEdit,QTableView QTimeEdit,QTableView QDateTimeEdit{\n"
"border-width:0px;\n"
"border-radius:0px;\n"
"}\n"
"\n"
"QTableView QLineEdit:focus,QTableView QComboBox:focus,QTableView QSpinBox:focus,QTableView QDoubleSpinBox:focus,QTableView QDateEdit:focus,QTableView QTimeEdit:focus,QTableView QDateTimeEdit:focus{\n"
"border-width:0px;\n"
"border-radius:0px;\n"
"}\n"
"\n"
"QLineEdit,QTextEdit,QPlainTextEdit,QSpinBox,QDoubleSpinBox,QComboBox,QDateEdit,QTimeEdit,QDateTimeEdit{\n"
"backgrou"
                        "nd:#242629;\n"
"}\n"
"\n"
"*{\n"
"font: 11pt \"\345\271\274\345\234\206\";\n"
"background:rgb(80,80,80);\n"
"}\n"
"\n"
"QStatusBar QWidget QLabel{\n"
"border:3px solid #242629;\n"
"border-radius:3px;\n"
"font: bold 13pt \"Consolas\";\n"
"color:#D6B668;\n"
"}\n"
"\n"
"\n"
".QTextEdit{\n"
"background-color:rgba(36,38,41,100);\n"
"color:rgba(255,255,255,255);\n"
"font: 11pt \"\345\271\274\345\234\206\";\n"
"}\n"
"\n"
"QTextEdit,QLineEdit#lineEditTarget{\n"
"background-color:rgba(100,100,100,250);\n"
"color:rgba(200,200,200,255);\n"
"font: 14pt \"Consolas\";\n"
"}\n"
"\n"
"QDialog#DocumentDialog{\n"
"border-image:url(:/icons/6.jpg);\n"
"}\n"
"\n"
"QDialog QListWidget{\n"
"background:transparent;\n"
"}\n"
"\n"
"QMenuBar::item,QMenuBar,QMenu,QDialog QLineEdit,QComboBox,QPushButton{\n"
"background-color:rgba(36,38,41,100);\n"
"}\n"
"\n"
"QMenu{\n"
"background-color:rgba(255,0,0,100);\n"
"}\n"
"\n"
"QPlainTextEdit,*{\n"
"font: 12pt \"Consolas\";\n"
"color:#20E420;\n"
"}\n"
"\n"
"*:disabled{\n"
"background:#1F2026;\n"
""
                        "border-color:#242629;\n"
"}\n"
"\n"
"/*TextColor:#D7E2E9*/\n"
"/*PanelColor:#1F2026*/\n"
"/*BorderColor:#111214*/\n"
"/*NormalColorStart:#242629*/\n"
"/*NormalColorEnd:#141518*/\n"
"/*DarkColorStart:#007DC4*/\n"
"/*DarkColorEnd:#0074BF*/\n"
"/*HighColor:#00BB9E*/\n"
""));
        verticalLayout_2 = new QVBoxLayout(Window);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        terminalPlainTextEdit = new QPlainTextEdit(Window);
        terminalPlainTextEdit->setObjectName(QStringLiteral("terminalPlainTextEdit"));
        terminalPlainTextEdit->setReadOnly(true);

        horizontalLayout->addWidget(terminalPlainTextEdit);

        horizontalLayout->setStretch(0, 3);

        horizontalLayout_2->addLayout(horizontalLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        Label = new QLabel(Window);
        Label->setObjectName(QStringLiteral("Label"));

        formLayout->setWidget(2, QFormLayout::LabelRole, Label);

        clientLineEdit = new QLineEdit(Window);
        clientLineEdit->setObjectName(QStringLiteral("clientLineEdit"));
        clientLineEdit->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(2, QFormLayout::FieldRole, clientLineEdit);

        Label_2 = new QLabel(Window);
        Label_2->setObjectName(QStringLiteral("Label_2"));

        formLayout->setWidget(3, QFormLayout::LabelRole, Label_2);

        onlineLineEdit = new QLineEdit(Window);
        onlineLineEdit->setObjectName(QStringLiteral("onlineLineEdit"));
        onlineLineEdit->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(3, QFormLayout::FieldRole, onlineLineEdit);

        Label_3 = new QLabel(Window);
        Label_3->setObjectName(QStringLiteral("Label_3"));

        formLayout->setWidget(4, QFormLayout::LabelRole, Label_3);

        playerLineEdit = new QLineEdit(Window);
        playerLineEdit->setObjectName(QStringLiteral("playerLineEdit"));
        playerLineEdit->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(4, QFormLayout::FieldRole, playerLineEdit);

        Label_4 = new QLabel(Window);
        Label_4->setObjectName(QStringLiteral("Label_4"));

        formLayout->setWidget(1, QFormLayout::LabelRole, Label_4);

        LineEdit = new QLineEdit(Window);
        LineEdit->setObjectName(QStringLiteral("LineEdit"));
        LineEdit->setAlignment(Qt::AlignCenter);
        LineEdit->setReadOnly(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, LineEdit);

        iPv4Label = new QLabel(Window);
        iPv4Label->setObjectName(QStringLiteral("iPv4Label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, iPv4Label);

        IPv4ComboBox = new QComboBox(Window);
        IPv4ComboBox->setObjectName(QStringLiteral("IPv4ComboBox"));

        formLayout->setWidget(0, QFormLayout::FieldRole, IPv4ComboBox);


        verticalLayout->addLayout(formLayout);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalLayout_2->setStretch(0, 3);
        horizontalLayout_2->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout_2);

        clientTableView = new QTableView(Window);
        clientTableView->setObjectName(QStringLiteral("clientTableView"));
        QFont font;
        font.setFamily(QStringLiteral("Consolas"));
        font.setPointSize(12);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        clientTableView->setFont(font);
        clientTableView->setStyleSheet(QStringLiteral(""));
        clientTableView->setShowGrid(true);
        clientTableView->setGridStyle(Qt::SolidLine);
        clientTableView->setWordWrap(false);

        verticalLayout_2->addWidget(clientTableView);


        retranslateUi(Window);

        QMetaObject::connectSlotsByName(Window);
    } // setupUi

    void retranslateUi(QWidget *Window)
    {
        Window->setWindowTitle(QApplication::translate("Window", "Breakout\346\234\215\345\212\241\347\253\257", nullptr));
        Label->setText(QApplication::translate("Window", "\345\256\242\346\210\267\344\272\272\346\225\260:", nullptr));
        clientLineEdit->setText(QApplication::translate("Window", "0", nullptr));
        Label_2->setText(QApplication::translate("Window", "\345\234\250\347\272\277\344\272\272\346\225\260:", nullptr));
        onlineLineEdit->setText(QApplication::translate("Window", "0", nullptr));
        Label_3->setText(QApplication::translate("Window", "\346\270\270\346\210\217\344\272\272\346\225\260:", nullptr));
        playerLineEdit->setText(QApplication::translate("Window", "0", nullptr));
        Label_4->setText(QApplication::translate("Window", "Port\347\253\257\345\217\243:", nullptr));
        LineEdit->setText(QApplication::translate("Window", "6666", nullptr));
        iPv4Label->setText(QApplication::translate("Window", "IPv4\345\234\260\345\235\200:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Window: public Ui_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
