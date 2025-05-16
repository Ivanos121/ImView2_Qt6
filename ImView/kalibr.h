#ifndef KALIBR_H
#define KALIBR_H

#include <QDialog>
#include <QSet>
#include <QSerialPort>
#include <QProgressBar>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QTextDocument>
#include <QPrintDialog>
#include <QCloseEvent>
#include <QWebEngineView>
#include <QStatusBar>
#include <checkboxheader.h>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTimer>

#include <QSqlTableModel>
#include <QSqlDatabase>

#include "datasource.h"

class MainWindow;

namespace Ui {
class Kalibr;
}

class Kalibr : public QDialog
{
    Q_OBJECT

public:
    explicit Kalibr(QWidget *parent = nullptr);
    ~Kalibr();
    void open_sdb();

    QSet<int> changedRows;
    QSet<QPoint> disabledCells;
    QSet<int> deleteRows;
    QColor disabledCellBackgroundColor;
    QColor changedColumnBackgroundColor;
    QColor deleteRowBackgroundColor;

signals:
    void savesettings(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
    void doubleClicked(QModelIndex);
    void cellclicked(int row , int column );

protected slots:
    void bvasSlot();
    void ZeroApplyIa();
    void ZeroApplyIb();
    void ZeroApplyIc();
    void ZeroApplyUa();
    void ZeroApplyUb();
    void ZeroApplyUc();
    void ValueApplyIa();
    void ValueApplyIb();
    void ValueApplyIc();
    void ValueApplyUa();
    void ValueApplyUb();
    void ValueApplyUc();
    //void on_pushButtonClose_clicked();
    void onCheckBoxHeaderClick1();
    void onCheckBoxHeaderClick2();
    void selectRows();
    void copyChannelNamesToTableWidget();
    void timerTimeout();
    void loadFile(const QString &fileName);
    void OpenFile();
    void setCurrentFile(const QString &fileName);
    void updateRecentFileActions();
    void CreateFile();
    void onDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight);
    void SaveFile();
    void Save();
    void CloseFile();
    void AddRow();
    void RemoveRow();
    void printSetup();
    void Print();
    void Help();
    void SearchPort();
    void EnterPort();
    void ReadPribor();
    void WritePribor();
    void SearchPort_2();
    void EnterPort_2();
    void SearchPort_3();
    void EnterPort_3();
    void EnterPort_4();
    void bvas_start();
    void dataSourceFailure();
    void acceptButton();
    void testPribor();

protected:
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *e);

private:
    Ui::Kalibr *ui;
    DataSource* dataSource;

    void initClient();
    void updateState();
    QTcpSocket *client;

    double i_dev_a;
    double i_dev_b;
    double i_dev_c;
    double u_dev_a;
    double u_dev_b;
    double u_dev_c;

    double i_zero_a;
    double i_zero_b;
    double i_zero_c;
    double u_zero_a;
    double u_zero_b;
    double u_zero_c;

    bool header_added;

    QSqlDatabase sdb;
    QSqlTableModel *modell;
    QString fileName;
    CheckBoxHeader* headerr;
    QTimer timer;
    QString curFile;
    enum { MaxRecentFiles = 5 };
    QAction *recentFileActs[MaxRecentFiles];
    QAction *separatorAct;
    bool isChanged = false;
    QWebEngineView * view;

    qint64 startTime;

    MainWindow *wf;

    QSerialPort* openArchiverPort();
    void stopGetData();
    void setDisabledCells();
    void closeAllBase_Yes();
    void closeAllBase_No();
    void closeAllBase_Otmena();
    void titleChanged(const QString &title);
    void printPreview(QPrinter *printer);
    void printTable(QPrinter *printer, bool isPreview);
};

struct CurrentChannelParams
{
    uint16_t diapazon;
    uint16_t filter;
    float minimum;
    float maximum;
};

inline uint qHash (const QPoint & key)
{
    return qHash (QPair<int,int>(key.x(), key.y()) );
}


#endif // KALIBR_H
