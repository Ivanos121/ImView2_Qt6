#ifndef ITOGS_H
#define ITOGS_H

#include <QWidget>
#include "base.h"
#include <QPrinter>

class MainWindow;

namespace Ui {
class Itogs;
}

class Itogs : public QWidget
{
    Q_OBJECT

public:
    explicit Itogs(QWidget *parent = nullptr);
    ~Itogs();

public slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void print(QPrinter *printer);

private slots:
    void on_pushButton_4_clicked();

private:
    Ui::Itogs *ui;    

    MainWindow* getMainWindow();
};

#endif // ITOGS_H
