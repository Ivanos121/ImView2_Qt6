#ifndef ITOGS_H
#define ITOGS_H

#include <QWidget>
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
    void report();
    void print_report();
    void clear_report();
    void print(QPrinter *printer);

private slots:
    void preview_report();

private:
    Ui::Itogs *ui;    

    MainWindow* getMainWindow();
};

#endif // ITOGS_H
