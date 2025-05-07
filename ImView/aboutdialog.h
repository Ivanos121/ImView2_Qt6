#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

class MainWindow;

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog();
    MainWindow *wf;

private slots:

    void actionclose();
private:
    Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H
