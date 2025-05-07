#ifndef ELECTROMAGN_H
#define ELECTROMAGN_H

#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>
#include "nabludatel.h"
#include "nabludatel_part.h"
#include "datasource_file.h"
#include "datasourcebvas.h"
#include "datasourcebvasw.h"
#include "datasource.h"
#include "plot.h"
#include "qcombobox.h"

namespace Ui {
class electromagn;
}

class electromagn : public QWidget
{
    Q_OBJECT

public:
    explicit electromagn(QWidget *parent = nullptr);
    ~electromagn();
    double key;
    MainWindow *wf;
    Ui::electromagn *ui;

    void stop();

public slots:
    void realtimeDataSlot();
    void raschet_el();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void bvasFailureSlot();
    void setcolorincell(int row, int column);
private:
    QElapsedTimer *time;
    NabludatelBase *nabludatel;
    Nabludatel nabludatel_full;
    NabludatelPart nabludatel_part;
    DataSource* dataSource;
    QComboBox* combo = new QComboBox();
    QComboBox* combo2 = new QComboBox();

    QSerialPort *momentPort;
    QTcpSocket plcSocket;
    QVector<QColor> dataLineColors_electromagn;

    void addDataLines();
    int connectMomentPort();
    void connectTcpPort();

signals:
    void tick();

public slots:

    void edit_graf();
};

#endif // ELECTROMAGN_H
