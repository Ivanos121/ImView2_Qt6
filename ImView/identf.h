#ifndef IDENTF_H
#define IDENTF_H

#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>
#include <QButtonGroup>

#include "datasource.h"
#include "model.h"
#include "modell.h"
#include "spinboxdelegate.h"
#include "mainwindow.h"

class MainWindow;

namespace Ui {
class identf;
}

class identf : public QWidget
{
    Q_OBJECT

public:
    explicit identf(QWidget *parent = nullptr);
    ~identf();

public slots:
    void realtimeDataSlot();
    void raschet_f();

public:
    Ui::identf *ui;
    QElapsedTimer *time;
    QElapsedTimer *time2;
    Modell *modell;
    DataSource *dataSource;
    MainWindow *wf;
    QString dataSourceFilename;
    Model model;
    QVector<QColor> dataLineColors_identf;
    SpinBoxDelegate *spin;

private slots:
    void setcolorincell(int row, int column);
    void edit_graf();
};

#endif // IDENTF_H
