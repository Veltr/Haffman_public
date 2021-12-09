#include "alertwindow.h"
#include "ui_alertwindow.h"

AlertWindow::AlertWindow(const QString& text, QWidget *parent) : QDialog(parent), ui(new Ui::Dialog){
    ui->setupUi(this);
    ui->label->setText(text);
}

void AlertWindow::on_OkB_clicked(){
    close();
}
