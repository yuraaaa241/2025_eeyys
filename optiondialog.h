#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#pragma once
#include <QDialog>
#include "ModelPart.h"


namespace Ui {
class OptionDialog;
}

class OptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionDialog(QWidget *parent = nullptr);
    ~OptionDialog();

    void setFromPart(ModelPart* part); //fill widgets from selected item
    void applyToPart(ModelPart* part); //write widgets back into item


private:
    Ui::OptionDialog *ui;
};

#endif // OPTIONDIALOG_H
