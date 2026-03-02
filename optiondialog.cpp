#include "optiondialog.h"
#include "ui_optiondialog.h"

OptionDialog::OptionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OptionDialog)
{
    ui->setupUi(this);

    ui->spinR->setRange(0, 255);
    ui->spinG->setRange(0, 255);
    ui->spinB->setRange(0, 255);

}

OptionDialog::~OptionDialog()
{
    delete ui;
}

void OptionDialog::setFromPart(ModelPart* part)
{
    if (!part) return;

    ui->nameEdit->setText(part->data(0).toString());
    ui->spinR->setValue(part->getColourR());
    ui->spinG->setValue(part->getColourG());
    ui->spinB->setValue(part->getColourB());
    ui->visibleCheck->setChecked(part->visible());
}

void OptionDialog::applyToPart(ModelPart* part)
{
    if (!part) return;

    // name goes in column 0
    part->set(0, ui->nameEdit->text());

    // rgb
    part->setColour(
        static_cast<unsigned char>(ui->spinR->value()),
        static_cast<unsigned char>(ui->spinG->value()),
        static_cast<unsigned char>(ui->spinB->value())
    );

    // visible (your setVisible already updates column 1 too)
    part->setVisible(ui->visibleCheck->isChecked());
}