#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

class MainWindow;

namespace Ui {
class Ksettings;
}

class Ksettings : public QDialog
{
    Q_OBJECT

public:
    explicit Ksettings(QWidget *parent = nullptr);
    ~Ksettings();

    MainWindow *wf;

protected slots:
    void applying_dialog();

private:
    Ui::Ksettings *ui;
    Ksettings *set;

    void onlistWidget_itemSelectionChanged();
};

#endif // SETTINGS_H
