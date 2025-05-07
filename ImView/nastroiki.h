#ifndef NASTROIKI_H
#define NASTROIKI_H

#include <QDialog>
#include "QTranslator"

class MainWindow;

namespace Ui {
class Nastroiki;
}

class Nastroiki : public QDialog
{
    Q_OBJECT

public:
    explicit Nastroiki(QWidget *parent = nullptr);
    ~Nastroiki();
    MainWindow *wf;


private slots:

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_listWidget_itemSelectionChanged();

private:
    Ui::Nastroiki *ui;
    QTranslator qtLanguageTranslator;


};

#endif // NASTROIKI_H
