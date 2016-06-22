/********************************************************************************
** Form generated from reading UI file 'transferfunction.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSFERFUNCTION_H
#define UI_TRANSFERFUNCTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TransferFunction
{
public:

    void setupUi(QWidget *TransferFunction)
    {
        if (TransferFunction->objectName().isEmpty())
            TransferFunction->setObjectName(QStringLiteral("TransferFunction"));
        TransferFunction->resize(400, 300);

        retranslateUi(TransferFunction);

        QMetaObject::connectSlotsByName(TransferFunction);
    } // setupUi

    void retranslateUi(QWidget *TransferFunction)
    {
        TransferFunction->setWindowTitle(QApplication::translate("TransferFunction", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class TransferFunction: public Ui_TransferFunction {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSFERFUNCTION_H
