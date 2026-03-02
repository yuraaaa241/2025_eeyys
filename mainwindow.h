#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ModelPartList.h"   // <-- add this (or forward declare, but this is easiest)

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

public slots:
    void handleButton();
    void handleRemoveButton();
    void handleTreeClicked();
    void on_actionOpen_File_triggered();

    void on_actionItem_Options_triggered();



signals:
    void statusUpdateMessage(const QString& message, int timeout);

private:
    Ui::MainWindow* ui;
    ModelPartList* partList;   // <-- IMPORTANT: must be exactly "partList"
};

#endif