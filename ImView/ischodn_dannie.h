#ifndef ISCHODN_DANNIE_H
#define ISCHODN_DANNIE_H

#include <QDialog>

class datas;

namespace Ui {
class ischodn_dannie;
}

class ischodn_dannie : public QDialog
{
    Q_OBJECT

public:
    explicit ischodn_dannie(QWidget *parent = nullptr);
    ~ischodn_dannie();

    datas *wf;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::ischodn_dannie *ui;
};

#endif // ISCHODN_DANNIE_H
