#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_Arc_clicked(){
    ha.SetFilesPath(ui->InFile->text().toStdString(),
                    (ui->OutFile->text() + '/' + (ui->OutFileName->text() != "" ? ui->OutFileName->text() : "out.dat")).toStdString());
    if(int t = ha.ProssedArchiving()) { AlertWindow w("Ошибка №" + QString::number(t)); w.show(); w.exec(); }
    else { AlertWindow w("Успех"); w.show(); w.exec(); }
}

void MainWindow::on_DeArc_clicked(){
    ha.SetFilesPath(ui->InFile->text().toStdString(),
                    (ui->OutFile->text() + '/' + (ui->OutFileName->text() != "" ? ui->OutFileName->text() : "out.dat")).toStdString());
    if(int t = ha.ProssedDearchiving()) { AlertWindow w("Ошибка №" + QString::number(t)); w.show(); w.exec(); }
    else { AlertWindow w("Успех"); w.show(); w.exec(); }
}

void MainWindow::on_SelectInFile_clicked(){
    ui->InFile->setText(QFileDialog::getOpenFileName());
}

void MainWindow::on_SelectOutFile_clicked(){
    ui->OutFile->setText(QFileDialog::getExistingDirectory());
}
