/********************************************************************************
** Form generated from reading UI file 'Setting.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTING_H
#define UI_SETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Setting
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QFormLayout *formLayout;
    QLabel *algorithmLabel;
    QComboBox *algorithmComboBox;
    QLabel *groupLabel;
    QLineEdit *groupLineEdit;
    QLabel *objectLabel;
    QComboBox *objectComboBox;
    QLabel *dimensionLabel;
    QComboBox *dimensionComboBox;
    QLabel *generationLabel;
    QLineEdit *generationLineEdit;
    QProgressBar *progressBar;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *widget;

    void setupUi(QWidget *Setting)
    {
        if (Setting->objectName().isEmpty())
            Setting->setObjectName(QStringLiteral("Setting"));
        Setting->resize(333, 462);
        verticalLayout = new QVBoxLayout(Setting);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(Setting);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout->setFormAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        formLayout->setVerticalSpacing(20);
        algorithmLabel = new QLabel(Setting);
        algorithmLabel->setObjectName(QStringLiteral("algorithmLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, algorithmLabel);

        algorithmComboBox = new QComboBox(Setting);
        algorithmComboBox->addItem(QString());
        algorithmComboBox->addItem(QString());
        algorithmComboBox->setObjectName(QStringLiteral("algorithmComboBox"));

        formLayout->setWidget(0, QFormLayout::FieldRole, algorithmComboBox);

        groupLabel = new QLabel(Setting);
        groupLabel->setObjectName(QStringLiteral("groupLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, groupLabel);

        groupLineEdit = new QLineEdit(Setting);
        groupLineEdit->setObjectName(QStringLiteral("groupLineEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, groupLineEdit);

        objectLabel = new QLabel(Setting);
        objectLabel->setObjectName(QStringLiteral("objectLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, objectLabel);

        objectComboBox = new QComboBox(Setting);
        objectComboBox->addItem(QString());
        objectComboBox->addItem(QString());
        objectComboBox->setObjectName(QStringLiteral("objectComboBox"));

        formLayout->setWidget(2, QFormLayout::FieldRole, objectComboBox);

        dimensionLabel = new QLabel(Setting);
        dimensionLabel->setObjectName(QStringLiteral("dimensionLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, dimensionLabel);

        dimensionComboBox = new QComboBox(Setting);
        dimensionComboBox->addItem(QString());
        dimensionComboBox->addItem(QString());
        dimensionComboBox->addItem(QString());
        dimensionComboBox->addItem(QString());
        dimensionComboBox->addItem(QString());
        dimensionComboBox->addItem(QString());
        dimensionComboBox->addItem(QString());
        dimensionComboBox->addItem(QString());
        dimensionComboBox->addItem(QString());
        dimensionComboBox->setObjectName(QStringLiteral("dimensionComboBox"));

        formLayout->setWidget(3, QFormLayout::FieldRole, dimensionComboBox);

        generationLabel = new QLabel(Setting);
        generationLabel->setObjectName(QStringLiteral("generationLabel"));

        formLayout->setWidget(4, QFormLayout::LabelRole, generationLabel);

        generationLineEdit = new QLineEdit(Setting);
        generationLineEdit->setObjectName(QStringLiteral("generationLineEdit"));

        formLayout->setWidget(4, QFormLayout::FieldRole, generationLineEdit);


        verticalLayout->addLayout(formLayout);

        progressBar = new QProgressBar(Setting);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setMinimumSize(QSize(0, 30));
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(progressBar);

        pushButton = new QPushButton(Setting);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(0, 50));

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(Setting);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(0, 50));

        verticalLayout->addWidget(pushButton_2);

        widget = new QWidget(Setting);
        widget->setObjectName(QStringLiteral("widget"));

        verticalLayout->addWidget(widget);

#ifndef QT_NO_SHORTCUT
        algorithmLabel->setBuddy(algorithmComboBox);
        groupLabel->setBuddy(groupLineEdit);
        objectLabel->setBuddy(objectComboBox);
        dimensionLabel->setBuddy(dimensionComboBox);
        generationLabel->setBuddy(generationLineEdit);
#endif // QT_NO_SHORTCUT

        retranslateUi(Setting);

        QMetaObject::connectSlotsByName(Setting);
    } // setupUi

    void retranslateUi(QWidget *Setting)
    {
        Setting->setWindowTitle(QApplication::translate("Setting", "\345\217\202\346\225\260\350\256\276\345\256\232", nullptr));
        label->setText(QApplication::translate("Setting", "\345\217\202\346\225\260\350\256\276\345\256\232", nullptr));
        algorithmLabel->setText(QApplication::translate("Setting", "\345\275\223\345\211\215\347\256\227\346\263\225(&A):", nullptr));
        algorithmComboBox->setItemText(0, QApplication::translate("Setting", "NSGA-II", nullptr));
        algorithmComboBox->setItemText(1, QApplication::translate("Setting", "MOEA/D", nullptr));

        groupLabel->setText(QApplication::translate("Setting", "\347\247\215\347\276\244\345\244\247\345\260\217(&G):", nullptr));
        objectLabel->setText(QApplication::translate("Setting", "\347\233\256\346\240\207\346\225\260\351\207\217(&O):", nullptr));
        objectComboBox->setItemText(0, QApplication::translate("Setting", "2", nullptr));
        objectComboBox->setItemText(1, QApplication::translate("Setting", "3", nullptr));

        dimensionLabel->setText(QApplication::translate("Setting", "\345\206\263\347\255\226\345\217\230\351\207\217\347\273\264\345\272\246(&D):", nullptr));
        dimensionComboBox->setItemText(0, QApplication::translate("Setting", "2", nullptr));
        dimensionComboBox->setItemText(1, QApplication::translate("Setting", "3", nullptr));
        dimensionComboBox->setItemText(2, QApplication::translate("Setting", "4", nullptr));
        dimensionComboBox->setItemText(3, QApplication::translate("Setting", "5", nullptr));
        dimensionComboBox->setItemText(4, QApplication::translate("Setting", "6", nullptr));
        dimensionComboBox->setItemText(5, QApplication::translate("Setting", "7", nullptr));
        dimensionComboBox->setItemText(6, QApplication::translate("Setting", "8", nullptr));
        dimensionComboBox->setItemText(7, QApplication::translate("Setting", "9", nullptr));
        dimensionComboBox->setItemText(8, QApplication::translate("Setting", "10", nullptr));

        generationLabel->setText(QApplication::translate("Setting", "\350\277\255\344\273\243\346\254\241\346\225\260(&I):", nullptr));
        pushButton->setText(QApplication::translate("Setting", "\350\277\220\350\241\214", nullptr));
        pushButton_2->setText(QApplication::translate("Setting", "\345\201\234\346\255\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Setting: public Ui_Setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
