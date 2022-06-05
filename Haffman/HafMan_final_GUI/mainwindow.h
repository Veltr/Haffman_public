#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../HafMan_final/haffmanarchiver.h"
#include "alertwindow.h"

#include <QMainWindow>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Arc_clicked();
    void on_DeArc_clicked();
    void on_SelectInFile_clicked();
    void on_SelectOutFile_clicked();

private:
    Ui::MainWindow *ui;
    HaffmanArchiver ha;
};
#endif // MAINWINDOW_H
