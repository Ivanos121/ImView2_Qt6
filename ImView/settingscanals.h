#ifndef SETTINGSCANALS_H
#define SETTINGSCANALS_H

//#include "mainwindow.h"
#include <QDialog>

#include "QSqlTableModel"
#include "QSqlDatabase"

namespace Ui {
class SettingsCanals;
}

class SettingsCanals : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsCanals(QWidget *parent = nullptr);
    ~SettingsCanals();

private slots:
    void dialog_close();
    void move_right();
    void move_left();
    void dialog_apply();

private:
    Ui::SettingsCanals *ui;
    QSqlDatabase sdb;
};

#endif // SETTINGSCANALS_H
