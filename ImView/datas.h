#ifndef DATAS_H
#define DATAS_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QButtonGroup>
#include <QDialog>
#include <QStandardItem>

#include "ischodn_dannie.h"
//#include "mainwindow.h"

class MainWindow;

namespace Ui {
class datas;
}

class datas : public QWidget
{
    Q_OBJECT

public:
    explicit datas(QWidget *parent = nullptr);
    ~datas() override;

public slots:
    void enterDannieS();
    void deleteDannieS();
    void saveDannieS();    
    void zapis_from_cell_tableview();
    void onsectionClicked(int index);

public:
    Ui::datas *ui;
    void zapis();
    void table();
    MainWindow *wf;
    QStandardItemModel *modd;

private:
    QSqlDatabase sdb;
    QString dataSourceFilename;
    ischodn_dannie *isdn;
    QSqlTableModel *model;
};

#endif // DATAS_H
