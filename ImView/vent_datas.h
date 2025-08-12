#ifndef VENT_DATAS_H
#define VENT_DATAS_H

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include <QWidget>
#include <QSqlQuery>

class Vent_settings;

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

public slots:
    void enterDannieV();
    void saveDannieV();
    void deleteDannieV();

public:
    Ui::Vent_datas *ui;
    Vent_settings *vsn;
    QSqlDatabase sdb;
    QSqlQuery *query;
    QString dataSourceFilename;

    QSqlTableModel *model2;
    void zapis();
};

#endif // VENT_DATAS_H
