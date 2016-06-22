/********************************************************************************
** Form generated from reading UI file 'transfer.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSFER_H
#define UI_TRANSFER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Transfer
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *Transfer)
    {
        if (Transfer->objectName().isEmpty())
            Transfer->setObjectName(QStringLiteral("Transfer"));
        Transfer->resize(406, 307);
        verticalLayoutWidget = new QWidget(Transfer);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(-1, -1, 401, 301));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(Transfer);

        QMetaObject::connectSlotsByName(Transfer);
    } // setupUi

    void retranslateUi(QWidget *Transfer)
    {
        Transfer->setWindowTitle(QApplication::translate("Transfer", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class Transfer: public Ui_Transfer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSFER_H
