#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "kalibr.h"
#include <QMainWindow>
#include <QTimer>
#include <QElapsedTimer>
#include <QWebEngineView>
#include <QTreeWidgetItem>
#include <QStandardItem>

#include <QSvgWidget>
//#include "qsvgwidget.h"
#include "settings.h"
#include "datas.h"
#include "nastroiki.h"
#include "qundostack.h"
#include "qundoview.h"
#include "ui_settinsKanals.h"
#include "aboutdialog.h"
#include <QProgressBar>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Model_el;

class MainWindow;

class SettinsKanals : public QDialog
{
    Q_OBJECT

public:
    explicit SettinsKanals(QWidget *parent = nullptr);

private slots:
    //void on_pushButton_clicked();

private:
    Ui::settinsKanals *ui;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void closeEvent (QCloseEvent *event) override;
    void LoadProject(QString str);
    QVector<QColor> dataLineColors;
    void setcolorincell(int row, int column);
    void translate_en();
    void translate_ru();
    void translator();
    void open_file();
    void loadFile(const QString &fileName);
    void updateRecentFileActions();
    void actionhelp();
    void updateWindowSize();

private:
    QString sessionFileName;
    QSqlDatabase sdb;
    QSqlTableModel *model;
    QStandardItemModel *modd;

    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
    void loadMotorParameters();

private slots:
    void actionabout();
    void actionExit();    
    void onButtonClicked();
    void onButtonClicked2();
    void titleChanged(const QString &title);
    void currentChanged(int index);
    void identf_pusk();
    void identf_stop();
    void enter_dannie();
    void nastroiki();
    void save_dannie();
    void delete_dannie();
    void electromagn_start();
    void electromagn_stop();
    void kalibr_osc();
    void nastr_graph();
    void actionresult();
    void actionresultidentf();
    void actionteplident_start();
    void actionteplident_stop();
    void save_file();
    void save_as_file();
    void print_preview_file();
    void printPreview(QPrinter *printer);
    void printTable(QPrinter *printer, bool isPreview);
    void pagePrint();
    void button_visible();
    void button_visible_2();
    void tabClicked();
    void tabClicked_2();
    void tabClicked_3();
    void tabClicked_4();
    void tabClicked_5();
    //void tabClicked_6();
    void itemEdit();
    void createUndoView();
    void edit();
    void edit_2();
    void edit_3();
    void edit_4();
    void edit_5();
    void edit_6();
    void edit_treeview();
    void actioncopy();
    void actionpaste();
    void actionundo();
    void actionredo();
    void actioncut();
    void modelItemChangedSlot(QStandardItem *item);
    void modelItemChangedSlot_2(QStandardItem *item);
    void modelItemChangedSlot_3(QStandardItem *item);
    void modelItemChangedSlot_4(QStandardItem *item);
    void modelItemChangedSlot_5(QStandardItem *item);
    void modelItemChangedSlot_6(QStandardItem *item);
    void modelItemChangedSlot_7(QStandardItem *item);
    void modelItemChangedSlot_8(QStandardItem *item);
    void projectFileSelectedSlot(QString projectFile);
    void projectFileSelectedSlot_2(QString projectFile_2);
    void projectFileSelectedSlot_3(QString projectFile_3);
    void projectFileSelectedSlot_4(QString projectFile_4);
    void projectFileSelectedSlot_5(QString projectFile_5);
    void projectFileSelectedSlot_6(QString projectFile_6);
    void SaveProgectToFile();
    void switch_regim_upr(bool checked);

    void on_save_tepl_dannie_clicked();
    void on_save_Vent_dannie_clicked();
    void on_load_tepl_dannie_clicked();
    void on_load_Vent_dannie_clicked();
    void LoadTeplDannie(QString str);
    void LoadVentDannie(QString str);
    void on_tepl_result_clicked();
    void on_vent_result_clicked();
    void createUndoStackAndActions();

    void radioButton_toggled(bool checked);
    void radioButton_2_toggled(bool checked);
    void radioButton_3_toggled(bool checked);
    void radioButton_4_toggled(bool checked);
    void radioButton_5_toggled(bool checked);
    void radioButton_6_toggled(bool checked);
    void radioButton_7_toggled(bool checked);
    void radioButton_8_toggled(bool checked);
    void radioButton_9_toggled(bool checked);
    void radioButton_10_toggled(bool checked);

    void save_electromagn_graph_file();
    void on_save_electromagn2_file_clicked();
    void on_save_tepl_graph_file_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalSlider_2_valueChanged(int value);
    void on_radioButton_11_toggled(bool checked);
    void on_radioButton_12_toggled(bool checked);
    void on_radioButton_13_toggled(bool checked);
    void openRecentFile();
    void tab_open();
    void changeTreeViewRowColor();
    bool iterate(const QModelIndex index, const QStandardItemModel * model, QString str);
    void rename_all();
    void select_all();
    void poisk();
    void open_panel();
    void zakr();
    void rename();
    void close_progect();
    void save_graphs();
    void load_graphs();
    void read_klass_izol();

    void color_treview(const QModelIndex &index, const QStandardItemModel *model);
    void treview_changed();
    void save_identf_in_file();
    void on_electromagn_tick();

    void actionaction_graph();
    void action_gruph();
public:
    Ui::MainWindow *ui;
    Model_el *wf;
    AboutDialog *rsc;
    Kalibr *kalibr;
    Ksettings *set;
    Nastroiki *nastr;
    //Settings *settings;
    //SettinsKanals *rsc3;
    QString dataSourceFilename;
    QString dirName;
    bool isChanged = false;
    QAction *separatorAct;
    QMenu *fileMenu;
    QItemSelectionModel *selectionModel, *selectionModel2, *selectionModel3;
    QSvgWidget *svgwidget;
    QWidget *widget, *widget2;    

    QMenu *recentFilesMenu;
    QMenu *helpMenu;
    enum { MaxRecentFiles = 5 };
    QAction *recentFileActs[MaxRecentFiles];
    QString curFile;
    QStandardItemModel* model2;

    QAction *undoAction;
    QAction *redoAction;
    QProgressBar *progress, *statusbar_progres;
    QWebEngineView * view;
    QLabel *statusbar_label, *statusbar_label_2, *statusbar_label_3, *statusbar_label_4,
           *statusbar_label_5, *statusbar_label_6, *statusbar_label_7, *statusbar_label_8,
           *statusbar_label_9;


    QTreeWidgetItem *treeItem, *child3, *child, *child2;
    QTreeWidgetItem *currentItem;
    int currentColumn;

    bool cleanState;
    bool undoOperation;
    QUndoStack *undoStack;
    QUndoView *undoView;
    QString *document;

    QStandardItem *item1,  *item2,  *item3,  *item4,  *item5,  *item6,  *item7,  *item8,  *item9,  *item10;
    QStandardItem *item11, *item12, *item13, *item14, *item15, *item16, *item17, *item18, *item19, *item20;
    QStandardItem *item21, *item22, *item23, *item24, *item25, *item26, *item27, *item28, *item29, *item30;
    QStandardItem *item31, *item32, *item33, *item34, *item35, *item36, *item37, *item38, *item39, *item40;
    QStandardItem *item41, *item42, *item43, *item44, *item45, *item46, *item47, *item48, *item49, *item50;
    QStandardItem *item51, *item52, *item53, *item54, *item55, *item56, *item57, *item58, *item59, *item60;
    QStandardItem *item61, *item62, *item63, *item64, *item65, *item66, *item67, *item68, *item69, *item70;
    QStandardItem *item71, *item72, *item73, *item74, *item75, *item76, *item77, *item78, *item79, *item80;
    QStandardItem *item81, *item82, *item83, *item84, *item85, *item86, *item87, *item88, *item89, *item90;
    QStandardItem *item91, *item92, *item93, *item94, *item95, *item96, *item97, *item98, *item99, *item100;
    QStandardItem *item101, *item102, *item103, *item104, *item105,*item106, *item107, *item108, *item109, *item110;
    QStandardItem *item111, *item112, *item113, *item114, *item115,*item116, *item117, *item118, *item119, *item120;
    QStandardItem *item121, *item122, *item123, *item124, *item125,*item126, *item127, *item128, *item129, *item130;
    QStandardItem *item131, *item132, *item133, *item134, *item135,*item136, *item137, *item138, *item139, *item140;
    QStandardItem *item141, *item142, *item143, *item144, *item145,*item146, *item147, *item148, *item149, *item150;
    QStandardItem *item151, *item152, *item153, *item154, *item155,*item156, *item157, *item158, *item159, *item160;
    QStandardItem *item161, *item162, *item163, *item164, *item165,*item166, *item167, *item168, *item169, *item170;
    QStandardItem *item171, *item172, *item173, *item174, *item175,*item176, *item177, *item178, *item179, *item180;
    void changeEvent(QEvent *event) override;
public slots:
    void saveDataSQL();
};

#endif // MAINWINDOW_H
