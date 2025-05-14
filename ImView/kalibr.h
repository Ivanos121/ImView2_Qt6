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

#include "datasourcebvas.h"
#include "modell.h"
#include <QSqlTableModel>
#include "QSqlDatabase"
#include "base.h"

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

private slots:
    void bvasSlot();
    void on_pushButtonZeroApplyIa_clicked();
    void on_pushButtonZeroApplyIb_clicked();
    void on_pushButtonZeroApplyIc_clicked();
    void on_pushButtonZeroApplyUa_clicked();
    void on_pushButtonZeroApplyUb_clicked();
    void on_pushButtonZeroApplyUc_clicked();
    void on_pushButtonValueApplyIa_clicked();
    void on_pushButtonValueApplyIb_clicked();
    void on_pushButtonValueApplyIc_clicked();
    void on_pushButtonValueApplyUa_clicked();
    void on_pushButtonValueApplyUb_clicked();
    void on_pushButtonValueApplyUc_clicked();
    void on_pushButtonClose_clicked();

    void onCheckBoxHeaderClick1();
    void onCheckBoxHeaderClick2();
    void selectRows();
    void copyChannelNamesToTableWidget();
    void timerTimeout();
    void loadFile(const QString &fileName);
    void on_OpenFile_clicked();
    void setCurrentFile(const QString &fileName);
    void updateRecentFileActions();

    void on_CreateFile_clicked();
    void onDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight);
    void on_SaveFile_clicked();
    void Save();
    void on_CloseFile_clicked();
    void on_AddRow_clicked();
    void on_RemoveRow_clicked();
    void on_printSetup_clicked();
    void on_Print_clicked();
    void on_Help_clicked();
    void on_SearchPort_clicked();
    void on_EnterPort_clicked();
    void on_ReadPribor_clicked();
    void on_WritePribor_clicked();

    void on_SearchPort_2_clicked();
    void on_EnterPort_2_clicked();
    void on_SearchPort_3_clicked();
    void on_EnterPort_3_clicked();

    void on_EnterPort_4_clicked();

    void on_kalibrStartButton_clicked();
    void dataSourceFailure();

    void on_acceptButton_clicked();

    void on_testPribor_clicked();

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
