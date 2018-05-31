/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QLabel *input_tips;
    QLineEdit *Input;
    QPushButton *OK;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(460, 79);
        input_tips = new QLabel(Dialog);
        input_tips->setObjectName(QStringLiteral("input_tips"));
        input_tips->setGeometry(QRect(10, 10, 541, 16));
        Input = new QLineEdit(Dialog);
        Input->setObjectName(QStringLiteral("Input"));
        Input->setGeometry(QRect(10, 40, 371, 21));
        Input->setDragEnabled(false);
        OK = new QPushButton(Dialog);
        OK->setObjectName(QStringLiteral("OK"));
        OK->setGeometry(QRect(390, 40, 61, 21));
        QWidget::setTabOrder(Input, OK);

        retranslateUi(Dialog);
        QObject::connect(OK, SIGNAL(clicked()), input_tips, SLOT(update()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "\350\276\223\345\205\245\346\241\206", Q_NULLPTR));
        input_tips->setText(QApplication::translate("Dialog", "TextLabel", Q_NULLPTR));
        Input->setInputMask(QString());
        Input->setPlaceholderText(QApplication::translate("Dialog", ".txt", Q_NULLPTR));
        OK->setText(QApplication::translate("Dialog", "OK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
