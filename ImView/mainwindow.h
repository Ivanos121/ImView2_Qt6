#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QElapsedTimer>
#include <QWebEngineView>
#include <QTreeWidgetItem>
#include <QStandardItem>
#include <QSvgWidget>
#include <QUndoStack>
#include <QProgressBar>
#include <QUndoView>

#include "kalibr.h"
#include "settings.h"
#include "datas.h"
#include "nastroiki.h"
#include "aboutdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Model_el;

class MainWindow;

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
    void horizontalSlider_valueChanged(int value);
    void horizontalSlider_2_valueChanged(int value);
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

   // void color_treview(const QModelIndex &index, const QStandardItemModel *model);
    void treview_changed();
    void save_identf_in_file();
    void electromagn_tick();

    void actionaction_graph();
    void action_gruph();

public:
    Ui::MainWindow *ui;
    QTimer *timer;
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
    enum {MaxRecentFiles = 5};
    QAction *recentFileActs[MaxRecentFiles];
    QString curFile;
    QStandardItemModel *model2;

    QAction *undoAction;
    QAction *redoAction;
    QProgressBar *progress, *statusbar_progres;
    QWebEngineView *view;
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

    QStandardItem *all_sesion_name_parametr,  *all_sesion_name_value,  *sesion_name_parametr1,
        *sesion_name_value1,  *item5,  *item6,  *kind_experiment_parametr,  *kind_experiment_value,
        *identf_scheme_zam_parametr,  *identf_scheme_zam_value;
    QStandardItem *item11, *item12, *calculation_mode_parametr, *calculation_mode_value,
        *item15, *item16, *electromagnetic_model_parametr, *electromagnetic_model_value, *engine_duty_cycle_parametr, *engine_duty_cycle_value;
    QStandardItem *item21, *item22, *item23, *item24, *item25, *item26, *item27, *item28, *item29, *item30;
    QStandardItem *item31, *item32, *item33, *item34, *item35, *item36, *item37, *item38, *item39, *item40;
    QStandardItem *item41, *item42, *item43, *item44, *item45, *item46, *item47, *item48, *item49, *item50;
    QStandardItem *item51, *item52, *item53, *item54, *item55, *item56, *item57, *item58, *item59, *item60;
    QStandardItem *item61, *item62, *item63, *item64, *save_data_parametr, *save_data_value,
        *data_identification_parametr, *data_identification_value, *data_electomagn_process_parametr,
        *data_electomagn_process_value;
    QStandardItem *data_tepl_process_parametr, *data_tepl_process_value, *data_vent_process_parametr,
        *data_vent_process_value, *data_tepl_prognose_parametr, *data_tepl_prognose_value,
        *data_ostat_tepl_resurs_parametr, *data_ostat_tepl_resurs_value,
        *identufication_observer_parametr, *enter_type_experiment_value;
    QStandardItem *read_data_identf_observer_parametr, *read_data_identf_observer_value,
        *item83, *item84, *item85, *item86, *identification_switch_parametr,
        *identification_switch_value, *item89, *item90;
    QStandardItem *item91, *item92, *tuning_coefficient_ki_parametr, *tuning_coefficient_gd_value,
        *tuning_coefficient_ki_value, *tuning_coefficient_gb_parametr, *tuning_coefficient_gb_value,
        *tuning_coefficient_kpsi_parametr, *tuning_coefficient_kpsi_value;
    QStandardItem *tuning_coefficient_gp_parametr, *tuning_coefficient_gp_value,
        *tuning_coefficient_gpsi_parametr, *tuning_coefficient_gpsi_value,
        *load_data_ruchn_identf_parametr,*load_data_ruchn_identf_value, *item107, *item108,
        *item109, *item110;
    QStandardItem *item111, *item112, *item113, *item114, *item115,*search_kanals_parametr,
        *search_kanals_value, *item118, *item119, *item120;
    QStandardItem *item121, *item122, *item123, *item124, *item125,*item126, *item127,
        *item128, *item129, *item130;
    QStandardItem *item131, *item132, *item133, *item134, *item135,*item136, *item137,
        *item138, *item139, *item140;
    QStandardItem *item141, *item142, *item143, *item144, *thermal_identification_parametr,
        *thermal_identification_value, *kind_thermal_model_parametr, *kind_thermal_model_value,
        *kind_thermal_model_2_parametr, *kind_thermal_model_3_value;
    QStandardItem *kind_thermal_model_3_parametr, *ventilation_identification_parametr,
        *ventilation_identification_value, *kind_ventilation_parametr,*kind_ventilation_value,
        *calculation_modes_parametr, *calculation_modes_value, *geometry_parameters_parametr,
        *geometry_parameters_value;
    QStandardItem *Heat_processes_accounting_parameter, *Heat_processes_accounting_value,
        *item163, *item164, *item165,*item166, *item167, *item168, *item169, *item170;
    QStandardItem *item171, *item172, *item173, *item174, *item175,*item176, *item177,
        *item178, *item179, *item180;

    void changeEvent(QEvent *event) override;
public slots:
    void saveDataSQL();
    void message_action(QString summary, QString body);
};

#endif // MAINWINDOW_H
