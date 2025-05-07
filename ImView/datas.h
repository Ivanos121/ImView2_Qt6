#ifndef DATAS_H
#define DATAS_H

#include <QWidget>
#include "QSqlTableModel"
#include "QSqlDatabase"
#include "ischodn_dannie.h"
#include <QButtonGroup>
#include <QDialog>
#include <QStandardItem>

class MainWindow;

namespace Ui {
class datas;
}

class datas : public QWidget
{
    Q_OBJECT

public:
    explicit datas(QWidget *parent = nullptr);
    ~datas();

public slots:
    void on_enterDannie_clicked();
    void on_deleteDannie_clicked();
    void on_saveDannie_clicked();

    void zapis_from_cell_tableview();
    void on_sectionClicked(int index);
private slots:





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
