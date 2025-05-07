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

private slots:
    void on_pushButton_clicked();

private:
    Ui::Ksettings *ui;
    Ksettings *set;


    void on_listWidget_itemSelectionChanged();
};

#endif // SETTINGS_H
