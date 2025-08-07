#ifndef VENT_DATAS_H
#define VENT_DATAS_H

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include <QWidget>

namespace Ui {
class Vent_datas;
}

class Vent_datas : public QWidget
{
    Q_OBJECT

public:
    explicit Vent_datas(QWidget *parent = nullptr);
    ~Vent_datas();
    QStandardItemModel *modd2;

    void table();
private:
    Ui::Vent_datas *ui;
    QSqlDatabase sdc;
    QString dataSourceFilename;
    //ischodn_dannie *isdn;
    QSqlTableModel *model2;
};

#endif // VENT_DATAS_H
