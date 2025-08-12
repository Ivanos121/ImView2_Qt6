#ifndef VENT_SETTINGS_H
#define VENT_SETTINGS_H

#include "qdialog.h"
#include <QWidget>

class Vent_datas;
class MainWindow;

namespace Ui {
class Vent_settings;
}

class Vent_settings : public QDialog
{
    Q_OBJECT

public:
    explicit Vent_settings(QWidget *parent = nullptr);
    ~Vent_settings();

protected slots:
    void onCellClicked(int row, int column);
    void button_close();
    void button_apply();

private slots:
    void close_vent_dannie();
    void apply_vent_dannie();



public:
    Ui::Vent_settings *ui;
    Vent_datas *wf;
    MainWindow *wff;
};

#endif // VENT_SETTINGS_H
