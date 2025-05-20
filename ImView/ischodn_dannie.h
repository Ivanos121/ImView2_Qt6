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
    ~ischodn_dannie() override;

    datas *wf;

private slots:
    void close_dialog();    
    void apply_dannie();

private:
    Ui::ischodn_dannie *ui;
};

#endif // ISCHODN_DANNIE_H
