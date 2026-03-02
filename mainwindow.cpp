#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "optiondialog.h"

#include <QStatusBar>
#include <QPushButton>

#include "ModelPartList.h"
#include "ModelPart.h"   
#include <QFileDialog>
#include <QFileInfo.h>
#include <QModelIndex>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,partList (nullptr)
{
    ui->setupUi(this);
    //create the model 
    //first arg- name/label for root column header
    //second arg- qObject parent
    partList = new ModelPartList("Parts", this);
    ui->treeView->setModel(partList);

    // Get pointer to root of tree
    ModelPart* rootItem = partList->getRootItem();

    // Add 3 top-level items
    for (int i = 0; i < 3; i++) {

        QString name = QString("TopLevel %1").arg(i);
        QString visible("true");

        ModelPart* childItem = new ModelPart({ name, visible });
        rootItem->appendChild(childItem);

        // Add 5 children to each top-level item
        for (int j = 0; j < 5; j++) {

            QString childName = QString("Item %1,%2").arg(i).arg(j);
            QString childVisible("true");

            ModelPart* childChildItem = new ModelPart({ childName, childVisible });
            childItem->appendChild(childChildItem);
        }
    }

    ui->treeView->addAction(ui->actionItem_Options);

    //connect the button's "released" signal, when
    //pushButton is clicked, call handleButton()
    connect(ui->pushButton, &QPushButton::released,
        this, &MainWindow::handleButton);
    connect(ui->pushButton_2, &QPushButton::released,
        this, &MainWindow::handleRemoveButton);

    //connect our custom signal to the status bar's showMessage slot
    connect(this, &MainWindow::statusUpdateMessage,
        ui->statusbar, &QStatusBar::showMessage);

    //connect the tree
    connect(ui->treeView, &QTreeView::clicked,
        this, &MainWindow::handleTreeClicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton()
{
    emit statusUpdateMessage("Button was clicked", 2000);
}

void MainWindow::handleRemoveButton()
{
    emit statusUpdateMessage("Button2 was clicked", 2000);
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        "C:\\",
        tr("STL Files (*.stl);;Text Files (*.txt);;All Files (*.*)")
    );

    if (fileName.isEmpty()) {
        emit statusUpdateMessage("Open cancelled", 2000);
        return;
    }

    // 1) get selected tree item
    QModelIndex index = ui->treeView->currentIndex();
    if (!index.isValid()) {
        emit statusUpdateMessage("No tree item selected", 3000);
        return;
    }

    // 2) get the underlying ModelPart*
    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());
    if (!selectedPart) {
        emit statusUpdateMessage("Selection invalid", 3000);
        return;
    }

    // 3) set name (column 0) to selected filename
    QString baseName = QFileInfo(fileName).fileName();
    selectedPart->set(0, baseName);

    // 4) force the view to refresh (important)
    QModelIndex nameIndex = index.sibling(index.row(), 0);
    ui->treeView->model()->setData(nameIndex, baseName, Qt::EditRole);

    // status bar proof
    emit statusUpdateMessage("Selected file: " + fileName, 4000);
}

void MainWindow::handleTreeClicked()
{
    QModelIndex index = ui->treeView->currentIndex();
    if (!index.isValid()) return;

    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());
    if (!selectedPart) return;

    QString text = selectedPart->data(0).toString(); // column 0 = Part name
    emit statusUpdateMessage("The selected item is: " + text, 0);
}

void MainWindow::on_actionItem_Options_triggered()
{
    QModelIndex index = ui->treeView->currentIndex();
    if (!index.isValid()) return;

    ModelPart* selectedPart =
        static_cast<ModelPart*>(index.internalPointer());
    if (!selectedPart) return;

    OptionDialog dialog(this);

    // fill dialog from the current selected item
    dialog.setFromPart(selectedPart);

    if (dialog.exec() == QDialog::Accepted) {

        dialog.applyToPart(selectedPart);

        // Force tree refresh
        ui->treeView->reset();

        // Build status message showing saved values
        QString message = QString("Saved: %1 | RGB(%2,%3,%4) | Visible: %5")
            .arg(selectedPart->data(0).toString())
            .arg(selectedPart->getColourR())
            .arg(selectedPart->getColourG())
            .arg(selectedPart->getColourB())
            .arg(selectedPart->visible() ? "true" : "false");

        statusBar()->showMessage(message, 4000);
    }
}