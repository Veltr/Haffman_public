#ifndef ALERTWINDOW_H
#define ALERTWINDOW_H

#include <QDialog>
#include <QObject>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class AlertWindow : public QDialog{
    Q_OBJECT

public:
    AlertWindow(const QString& text, QWidget* parent = 0);

private slots:
    void on_OkB_clicked();

private:
    Ui::Dialog* ui;
};

#endif // ALERTWINDOW_H
