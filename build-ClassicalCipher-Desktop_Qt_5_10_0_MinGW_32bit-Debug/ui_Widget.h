/********************************************************************************
** Form generated from reading UI file 'Widget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_4;
    QFormLayout *formLayout;
    QLabel *eLabel;
    QComboBox *ComboBoxCiper;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPlainTextEdit *plainTextEditText;
    QPushButton *pushButtonEncode;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QPlainTextEdit *plainTextEditCiper;
    QPushButton *pushButtonDecode;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QPlainTextEdit *plainTextEditDecoded;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(900, 600);
        Widget->setMinimumSize(QSize(900, 600));
        Widget->setMaximumSize(QSize(900, 600));
        Widget->setStyleSheet(QString::fromUtf8("*{\n"
"font: 14pt \"\345\271\274\345\234\206\";\n"
"}"));
        verticalLayout_4 = new QVBoxLayout(Widget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setSizeConstraint(QLayout::SetMinAndMaxSize);
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        formLayout->setLabelAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        formLayout->setFormAlignment(Qt::AlignHCenter|Qt::AlignTop);
        formLayout->setContentsMargins(-1, 14, -1, -1);
        eLabel = new QLabel(Widget);
        eLabel->setObjectName(QStringLiteral("eLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, eLabel);

        ComboBoxCiper = new QComboBox(Widget);
        ComboBoxCiper->addItem(QString());
        ComboBoxCiper->addItem(QString());
        ComboBoxCiper->addItem(QString());
        ComboBoxCiper->addItem(QString());
        ComboBoxCiper->addItem(QString());
        ComboBoxCiper->setObjectName(QStringLiteral("ComboBoxCiper"));
        ComboBoxCiper->setMinimumSize(QSize(200, 0));

        formLayout->setWidget(0, QFormLayout::FieldRole, ComboBoxCiper);


        verticalLayout_4->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_4->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, -1, 14);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        plainTextEditText = new QPlainTextEdit(Widget);
        plainTextEditText->setObjectName(QStringLiteral("plainTextEditText"));

        verticalLayout->addWidget(plainTextEditText);


        horizontalLayout->addLayout(verticalLayout);

        pushButtonEncode = new QPushButton(Widget);
        pushButtonEncode->setObjectName(QStringLiteral("pushButtonEncode"));

        horizontalLayout->addWidget(pushButtonEncode);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        plainTextEditCiper = new QPlainTextEdit(Widget);
        plainTextEditCiper->setObjectName(QStringLiteral("plainTextEditCiper"));
        plainTextEditCiper->setReadOnly(true);

        verticalLayout_2->addWidget(plainTextEditCiper);


        horizontalLayout->addLayout(verticalLayout_2);

        pushButtonDecode = new QPushButton(Widget);
        pushButtonDecode->setObjectName(QStringLiteral("pushButtonDecode"));

        horizontalLayout->addWidget(pushButtonDecode);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_3);

        plainTextEditDecoded = new QPlainTextEdit(Widget);
        plainTextEditDecoded->setObjectName(QStringLiteral("plainTextEditDecoded"));
        plainTextEditDecoded->setReadOnly(true);

        verticalLayout_3->addWidget(plainTextEditDecoded);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout);

#ifndef QT_NO_SHORTCUT
        eLabel->setBuddy(ComboBoxCiper);
#endif // QT_NO_SHORTCUT

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "\345\217\244\345\205\270\345\257\206\347\240\201", nullptr));
        eLabel->setText(QApplication::translate("Widget", "\345\212\240\345\257\206\347\256\227\346\263\225(&E):", nullptr));
        ComboBoxCiper->setItemText(0, QApplication::translate("Widget", "Casesar\345\257\206\347\240\201", nullptr));
        ComboBoxCiper->setItemText(1, QApplication::translate("Widget", "Playfair\345\257\206\347\240\201", nullptr));
        ComboBoxCiper->setItemText(2, QApplication::translate("Widget", "Hill\345\257\206\347\240\201", nullptr));
        ComboBoxCiper->setItemText(3, QApplication::translate("Widget", "Vigenere\345\257\206\347\240\201", nullptr));
        ComboBoxCiper->setItemText(4, QApplication::translate("Widget", "\344\273\277\345\260\204\345\257\206\347\240\201", nullptr));

        label->setText(QApplication::translate("Widget", "\346\230\216\346\226\207", nullptr));
        plainTextEditText->setPlainText(QApplication::translate("Widget", "this is a testing message for encryption. meet me after the toga party.", nullptr));
        pushButtonEncode->setText(QApplication::translate("Widget", "\345\212\240\345\257\206>>", nullptr));
        label_2->setText(QApplication::translate("Widget", "\345\257\206\346\226\207", nullptr));
        pushButtonDecode->setText(QApplication::translate("Widget", "\350\247\243\345\257\206>>", nullptr));
        label_3->setText(QApplication::translate("Widget", "\350\257\221\346\226\207", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
