#include "qimagewriter.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "base.h"
#include "model.h"
#include "datas.h"
#include "ui_datas.h"
#include "identf.h"
#include "ui_identf.h"
#include "electromagn.h"
#include "kalibr.h"
#include "teplovent.h"
#include "tepl_dannie.h"
#include "ui_ostat_resurs.h"
#include "ui_poisk.h"
#include "ui_tepl_dannie.h"
#include "ui_tepl_identf.h"
#include "ui_teplovent.h"
#include "ui_electromagn.h"
#include "ui_draw_line.h"
#include "ui_draw_poper.h"
#include "ui_teplschem.h"
#include "ui_vent_model.h"
#include "ui_trend.h"
#include "ui_datas.h"
#include "vent_model.h"
#include "ui_vent_model.h"
#include "customhelpdelegate.h"
#include "math.h"
#include "plot.h"
#include "model_el.h"
#include "tepl_struct.h"
#include "tepl_identf.h"
#include "settings.h"
#include "poisk.h"
#include "intens_star_izol.h"
#include "pushbuttondelegate.h"
#include "start_app.h"


#include <QStyle>
//#include <QDesktopWidget>
#include <QClipboard>
#include <QScreen>
#include <QSpinBox>
#include <QSplitter>
#include <QMessageBox>
#include <QuaZip-Qt6-1.5/quazip/JlCompress.h>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QColorDialog>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix_double.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_vector_double.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <QUndoCommand>
#include <QPixmap>
#include <QSvgRenderer>
#include <iostream>
#include <QString>
#include <QEvent>
#include <QSettings>
#include <cmath>
#include <QSqlRecord>
#include <QFileDialog>
#include <QSvgRenderer>
#include <QPainter>

Base base;
Base_tepl base_tepl;
Klass_izol klass_izol;
Model modelss;
extern Model_el model_el;
double teta_0,teta_1,teta_2,teta_3,teta_4,teta_5,teta_k,teta_c,teta_p, teta_v, teta_z, teta_l_1, teta_l_2, teta_pp,teta0_0,teta0_1,teta0_2, teta0_1n,teta0_2n;
double lambda_10, lambda_21, lambda_c2,lambda_p2,lambda_30,lambda_c3,lambda_p3,lambda_3k,lambda_c4,lambda_pb,lambda_p5,
lambda_k0,lambda_45,lambda_50,lambda_b5,lambda_pz, lambda_zc, lambda_pc, lambda_ppz, lambda_lc, lambda_l4, lambda_pl, lambda_lp,
lambda_zp,lambda_pс,lambda_л2с,lambda_л14,lambda_пл1,lambda_рл2,lambda_l22,lambda_l14,lambda_pl1,lambda_pl2,lambda0_10,lambda0_12,lambda0_20;
double C_0,C_1,C_2,C_3,C_4,C_5,C_k,C_c,C_p,C_v,C_z,C_pp,C_l_1,C_l_2,C0_0,C0_1,C0_2,C0_3;
double P_0,P_1,P_2,P_3,P_4,P_5,P_c,P_k,P_p,P_z,P_pp,P_l_1,P_l_2,P_v,P_10,P_30,P_k0,P_50,P_3k,P_21,P_c2,P_c3,P_c4,P_45,P_pc,
P_pb,P_b5,P_p5,P_p2;
double dP_zp,dP_zc,dP_c3,dP_pс,dP_pz,dP_l22,dP_l14,dP_pl1,dP_pl2;
double d_teta_zp,d_teta_zc,d_teta_c3,d_teta_pc,d_teta_pz,d_teta_l22,d_teta_l14,d_teta_pl1,d_teta_pl2,
d_teta_10,d_teta_30,d_teta_k0,d_teta_50,d_teta_3k,d_teta_21,d_teta_c2,d_teta_c4,d_teta_45,d_teta0_10,d_teta0_12,d_teta0_20,
d_teta_pb,d_teta_b5,d_teta_p5,d_teta_p2;
double H0, Qmax, Z0, Z1, Z2, Z3, Z4, Z5, Z6, Qp, Hp, Vcp, Pvent;
double Nsv,N, dNptk, dNvpk, dNvk,dNsvp, dNkd;
bool isNablLaunched = false;
QString currentTabText;
QString klass;
double G,B;
int rowNumber;
//v
QVector<double> tepl_ident_t;
QVector<double> tepl_ident_StatorTemp;

QVector<double> tepl_ident_P1, tepl_ident_P2;
bool tepl_start = false;

QTranslator * qtLanguageTranslator;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , cleanState(true)
    , undoOperation(false)
{
    ui->setupUi(this);

    updateWindowSize();

    // QScreen *screen = QGuiApplication::primaryScreen();
    // if (screen)
    // {
    //     // Получаем размеры экрана
    //     QSize screenSize = screen->size();
    //     // Устанавливаем размеры окна на 80% от размеров экрана
    //     int width = static_cast<int>(screenSize.width() * 0.8);
    //     int height = static_cast<int>(screenSize.height() * 0.8);

    //     this->resize(width, height);

    //     // Центрируем окно
    //     int posX = (screenSize.width() - width) / 2;
    //     int posY = (screenSize.height() - height) / 2;
    //     this->move(posX, posY);
    // }

    // connect(screen, &QScreen::geometryChanged, this, [=]() {
    //     // Обновите размеры и позицию окна
    //     QSize newSize = screen->size();
    //     this->resize(newSize);
    // });

    ui->actionaction_graph->setCheckable(true);
    ui->action_gruph->setCheckable(true);
    ui->widget_2->ui->widget->hide();

     //настройка стартового экрана
    ui->tabWidget->hide();
    ui->stackedWidget->hide();
    ui->switch_regim_upr->hide();
    ui->toolBar->hide();
    ui->toolBar_2->hide();
    ui->statusbar->hide();
    ui->menu_2->menuAction()->setVisible(false);
    ui->menu_3->menuAction()->setVisible(false);
    ui->menu_4->menuAction()->setVisible(false);
    ui->menu_5->menuAction()->setVisible(false);
    ui->save_file->setVisible(false);
    ui->save_as_file->setVisible(false);
    ui->action_save_graph_file->setVisible(false);
    ui->action_close_progect->setVisible(false);
    ui->action_close_session->setVisible(false);
    ui->print_file->setVisible(false);
    ui->print_preview->setVisible(false);

    //настройка экрана конфигурации графиков
    ui->widget_2->ui->widget->hide();
    ui->widget_3->ui->widget->hide();
    ui->widget_5->ui->widget_4->ui->widget->hide();


    //Настройка буфера обмена
    undoStack = new QUndoStack(this);
    undoStack->setUndoLimit(100);

    ui->actionundo->setEnabled(false);
    ui->actionredo->setEnabled(false);
    ui->widget_12->setVisible(false);
    ui->widget_15->setEnabled(true);
    ui->widget_15->showMaximized();

    //Настрока меню быстрого открытия файлов
    recentFileActs[0] = ui->actionmy;
    recentFileActs[1] = ui->actionmy2;
    recentFileActs[2] = ui->actionmy3;
    recentFileActs[3] = ui->actionmy4;
    recentFileActs[4] = ui->actionmy5;

    for (int i = 0; i < MaxRecentFiles; i++)
    {
        connect(recentFileActs[i], &QAction::triggered, this, &MainWindow::openRecentFile);
    }

    //Настройкак поиска
    QSettings settings( "BRU", "IM View");
    settings.setValue( "ii", 0);
    settings.setValue( "xx", 0);
    settings.setValue( "iz", 0);
    settings.setValue( "xz", 0);
    settings.setValue( "iu", 0);
    settings.setValue( "jz", 0);
    settings.setValue( "number", 0);
    settings.setValue( "kz", 0.5);

    //поиск - замена
    connect(ui->actionpoisk, &QAction::triggered, this, &MainWindow::open_panel);
    connect(ui->widget_12->ui->pushButton_7,&QPushButton::clicked, this, &MainWindow::zakr);
    connect(ui->widget_12->ui->pushButton, &QPushButton::pressed, this, &MainWindow::poisk);
    connect(ui->widget_12->ui->pushButton_5, &QPushButton::pressed, this, &MainWindow::select_all);
    connect(ui->widget_12->ui->pushButton_2, &QPushButton::pressed, this, &MainWindow::rename);
    connect(ui->widget_12->ui->pushButton_6, &QPushButton::pressed, this, &MainWindow::rename_all);
    connect(ui->widget_12->ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::tab_open);

    //инструментальное меню
    //файловые операции
    connect(ui->open_file, &QAction::triggered, this, &MainWindow::open_file);
    connect(ui->save_file, &QAction::triggered, this, &MainWindow::save_file);
    connect(ui->save_as_file, &QAction::triggered, this, &MainWindow::save_as_file);
    connect(ui->print_preview, &QAction::triggered, this, &MainWindow::print_preview_file);
    connect(ui->print_file, &QAction::triggered, this, &MainWindow::pagePrint);
    connect(ui->action_close_progect, &QAction::triggered, this, &MainWindow::close_progect);
    connect(ui->pushButton_10, &QPushButton::clicked, this, &MainWindow::read_klass_izol);
    connect(ui->nastroiki, &QAction::triggered, this, &MainWindow::onButtonClicked);
    connect(ui->nastroiki, &QAction::triggered, this, &MainWindow::nastroiki);
    connect(ui->nastr_graph, &QAction::triggered, this, &MainWindow::onButtonClicked2);
    connect(ui->nastr_graph, &QAction::triggered, this, &MainWindow::nastr_graph);
    connect(ui->enter_dannie, &QAction::triggered, this, &MainWindow::enter_dannie);
    connect(ui->save_dannie, &QAction::triggered, this, &MainWindow::save_dannie);
    connect(ui->delete_dannie, &QAction::triggered, this, &MainWindow::delete_dannie);
    connect(ui->identf_pusk, &QAction::triggered, this, &MainWindow::identf_pusk);
    connect(ui->identf_stop, &QAction::triggered, this, &MainWindow::identf_stop);
    connect(ui->electromagn_start, &QAction::triggered, this, &MainWindow::electromagn_start);
    connect(ui->electromagn_stop, &QAction::triggered, this, &MainWindow::electromagn_stop);
    connect(ui->kalibr_osc, &QAction::triggered, this, &MainWindow::kalibr_osc);
    connect(ui->actionresult, &QAction::triggered, this, &MainWindow::actionresult);
    connect(ui->actionresultidentf, &QAction::triggered, this, &MainWindow::actionresultidentf);
    connect(ui->actionteplident_start, &QAction::triggered, this, &MainWindow::actionteplident_start);
    connect(ui->actionteplident_stop, &QAction::triggered, this, &MainWindow::actionteplident_stop);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::actionExit);
    connect(ui->actionabout, &QAction::triggered, this, &MainWindow::actionabout);
    connect(ui->actionhelp, &QAction::triggered, this, &MainWindow::actionhelp);
    connect(ui->switch_regim_upr,&QPushButton::clicked, this, &MainWindow::switch_regim_upr);
    connect(ui->actionaction_graph, &QAction::triggered, this, &MainWindow::actionaction_graph);
    connect(ui->action_gruph, &QAction::triggered, this, &MainWindow::action_gruph);

    //операции правки
    connect(ui->actioncopy, &QAction::triggered, this, &MainWindow::actioncopy);
    connect(ui->actionpaste, &QAction::triggered, this, &MainWindow::actionpaste);
    connect(ui->actionundo, &QAction::triggered, this, &MainWindow::actionundo);
    connect(ui->actionredo, &QAction::triggered, this, &MainWindow::actionredo);
    connect(ui->actioncut, &QAction::triggered, this, &MainWindow::actioncut);
    connect(ui->action_save_graph_file,&QAction::triggered, this, &MainWindow::save_electromagn_graph_file);

    //выбор режимов отображения информации
    connect(ui->radioButton,&QRadioButton::toggled, this, &MainWindow::radioButton_toggled);
    connect(ui->radioButton_2,&QRadioButton::toggled, this, &MainWindow::radioButton_2_toggled);
    connect(ui->radioButton_3,&QRadioButton::toggled, this, &MainWindow::radioButton_3_toggled);
    connect(ui->radioButton_4,&QRadioButton::toggled, this, &MainWindow::radioButton_4_toggled);
    connect(ui->radioButton_5,&QRadioButton::toggled, this, &MainWindow::radioButton_5_toggled);
    connect(ui->radioButton_6,&QRadioButton::toggled, this, &MainWindow::radioButton_6_toggled);
    connect(ui->radioButton_7,&QRadioButton::toggled, this, &MainWindow::radioButton_7_toggled);
    connect(ui->radioButton_8,&QRadioButton::toggled, this, &MainWindow::radioButton_8_toggled);
    connect(ui->radioButton_9,&QRadioButton::toggled, this, &MainWindow::radioButton_9_toggled);
    connect(ui->radioButton_10,&QRadioButton::toggled, this, &MainWindow::radioButton_10_toggled);
    //connect(ui->radioButton_11,&QRadioButton::toggled, this, &MainWindow::radioButton_11_toggled);
    //connect(ui->radioButton_12,&QRadioButton::toggled, this, &MainWindow::radioButton_12_toggled);
    //connect(ui->radioButton_13,&QRadioButton::toggled, this, &MainWindow::radioButton_13_toggled);

    //connect(ui->horizontalSlider,&QSlider::valueChanged, this, &MainWindow::horizontalSlider_valueChanged);
    //connect(ui->horizontalSlider_2,&QSlider::valueChanged, this, &MainWindow::horizontalSlider_2_valueChanged);
    connect(ui->save_identf_in_file, &QPushButton::clicked, this, &MainWindow::save_identf_in_file);

    //connect(ui->widget->ui->tableView, &QAbstractItemView::clicked, this, &MainWindow::saveDataSQL);
    connect(ui->widget->ui->tableView->itemDelegate(), &QAbstractItemDelegate::closeEditor, this, &MainWindow::saveDataSQL);

    //connect(ui->widget->ui->tableView, &QHeaderView::sectionClicked, this, &MainWindow::sort);

    //connect(ui->widget->ui->tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));


    //Настройка связи форм
    ui->widget_2->wf=this;
    ui->widget_3->wf=this;
    ui->widget_5->wf=this;
    ui->widget_6->wf=this;
    ui->widget_5->ui->widget_4->wf=this;
    ui->widget->wf=this;
    ui->widget_15->wf=this;

    //формирование поведения файловых операций
    ui->LoadProgect->setVisible(false);
    ui->SaveProgectToFile->setVisible(false);
    ui->save_file->setEnabled(false);
    ui->save_as_file->setEnabled(false);

    //Настройка виджета График
    ui->widget_6->ui->plot->t_max = 0.01;
    ui->widget_6->ui->plot->U_max = 500.0;
    ui->widget_6->ui->plot->margin_bottom = 40;
    ui->widget_6->ui->plot->margin_left = 100;
    ui->widget_6->ui->plot->reset();

    //Отображение картинов в приложении
    ui->widget_5->ui->widget->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/ax_var/ax_var_2.html").absoluteFilePath()));
    ui->widget_5->ui->widget_5->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/rad_var/rad_var.html").absoluteFilePath()));
    ui->widget_5->ui->widget_3->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/tepl_schen_zam/tepl_tract.html").absoluteFilePath()));
    ui->widget_5->ui->webEngineView_3->setUrl(QUrl::fromLocalFile(QFileInfo("../data/tepl_schen_zam/two_wase_tepl_model.html").absoluteFilePath()));
    ui->widget_5->ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/tepl_schen_zam/tepl_tract_stator.html").absoluteFilePath()));
    ui->widget_5->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/tepl_schen_zam/tepl_tract_stator.html").absoluteFilePath()));
    ui->widget_6->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/vent_flow/vent_flow.html").absoluteFilePath()));
    ui->widget_6->ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/ventilator/ventilator.html").absoluteFilePath()));
    ui->widget_6->ui->webEngineView_3->setUrl(QUrl::fromLocalFile(QFileInfo("../data/vent_schem_zam/vent_schem_zam.html").absoluteFilePath()));
    ui->widget_6->ui->webEngineView_4->setUrl(QUrl::fromLocalFile(QFileInfo("../data/vent_energo_scheme/vent_energo_scheme.html").absoluteFilePath()));
    ui->widget_6->ui->webEngineView_5->setUrl(QUrl::fromLocalFile(QFileInfo("../data/vent_energo_scheme/vent_energo_scheme.html").absoluteFilePath()));
    ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/energo_scheme/energo_scheme.html").absoluteFilePath()));
    ui->widget_5->ui->widget->ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/grad_line/grad_line_2.html").absoluteFilePath()));
    ui->widget_5->ui->widget_5->ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/grad_line/grad_line_2.html").absoluteFilePath()));

    showMaximized();

    ui->identf_stop->setEnabled(false);
    ui->electromagn_stop->setEnabled(false);
    ui->actionteplident_stop->setEnabled(false);

    ui->switch_regim_upr->setCheckable(true);
    ui->switch_regim_upr->setChecked(true);
    QObject::connect(ui->switch_regim_upr, &QPushButton::clicked, ui->stackedWidget, &MainWindow::setVisible);

    ui->stackedWidget->setCurrentIndex(0);

    //Настройка свойств QTreeView
    ui->treeView->setSelectionBehavior(QTreeView :: SelectRows); // Выбираем всю строку за раз
    ui->treeView->setSelectionMode(QTreeView :: SingleSelection); // Одиночный выбор, при этом вся строка над ним является одной строкой меню
    ui->treeView->setAlternatingRowColors(true); // Цвет каждой строки интервала разный, при наличии qss этот атрибут недействителен
    ui->treeView->setFocusPolicy(Qt :: NoFocus);
    ui->treeView->setExpandsOnDoubleClick(true);
    //ui->treeView->setRootIsDecorated(true);
    QFont newFontt("DroidSans", 10, QFont::Normal, false);
    ui->treeView->setFont(newFontt);
    ui->treeView->setBackgroundRole(QPalette :: Dark);
    ui->treeView->setExpandsOnDoubleClick(false);

    QObject::connect(ui->treeView, &QTreeView::clicked,this, [this]()
    {
        if (ui->treeView->isExpanded(ui->treeView->currentIndex()))
        {
            ui->treeView->collapse(ui->treeView->currentIndex());
        }else{
            ui->treeView->expand(ui->treeView->currentIndex());
        }
    });

    //Создание модели QTreeView
    model2=new QStandardItemModel(ui->treeView);
    model2->setHorizontalHeaderLabels (QStringList () << tr("Наименование") << tr("Свойство")); // Установить заголовок столбца
    ui->treeView->header()->setDefaultAlignment(Qt::AlignCenter);
    ui->treeView->setAlternatingRowColors(true);



    //настройка итемов QTreeView
    QList<QStandardItem*> items1;
    item1 = new QStandardItem(tr("Общее настройки сессии"));
    QString w0=item1->text();
    item1->setToolTip(w0);
    item2 = new QStandardItem();
    items1.append(item1);
    items1.append(item2);
    model2->appendRow(items1);
    item1->setSelectable(false);
    item1->setEditable(false);
    item2->setSelectable(false);
    item2->setEditable(false);
    QFont newFont("DroidSans", 10, QFont::Bold,false);
    item1->setFont(newFont);

    QList<QStandardItem*> items2;
    item3 = new QStandardItem(tr("Название сессии"));
    item3->setEditable(false);
    QString w1=item3->text();
    item3->setToolTip(w1);
    item4 = new QStandardItem(tr("Имя сеанса"));
    QString w2=item4->text();
    item4->setToolTip(w2);
    items2.append(item3);
    items2.append(item4);
    item1->appendRow(items2);
    items2.clear();

    item7 = new QStandardItem(tr("Тип эксперимента"));
    item7->setEditable(false);
    QString w9=item7->text();
    item7->setToolTip(w9);
    QFont newFont10("DroidSans", 10, QFont::Bold,false);
    item7->setFont(newFont10);
    item8 = new QStandardItem();
    item8->setEditable(false);
    items2.append(item7);
    items2.append(item8);
    item1->appendRow(items2);
    items2.clear();

    item87 = new QStandardItem(tr("Идентификация данных схемы замещения"));
    item87->setEditable(false);
    QString w10=item87->text();
    item87->setToolTip(w10);
    item88 = new QStandardItem(tr("Выбрать тип эксперимента"));
    QString w11=item88->text();
    item88->setToolTip(w11);
    items2.append(item87);
    items2.append(item88);
    item7->appendRow(items2);
    items2.clear();

    item105 = new QStandardItem(tr("Загрузка данных ручной идентификации"));
    item105->setEditable(false);
    item105->setEnabled(false);
    QString w12=item105->text();
    item105->setToolTip(w12);
    item106 = new QStandardItem(tr("Указать каталог"));
    item106->setEnabled(false);
    QString w13=item106->text();
    item106->setToolTip(w13);
    items2.append(item105);
    items2.append(item106);
    item7->appendRow(items2);
    items2.clear();

    item79 = new QStandardItem(tr("Наблюдатель состояния"));
    item79->setEditable(false);
    QString w14=item79->text();
    item79->setToolTip(w14);
    item80 = new QStandardItem(tr("Выбрать тип эксперимента"));
    QString w15=item80->text();
    item80->setToolTip(w15);
    items2.append(item79);
    items2.append(item80);
    item7->appendRow(items2);
    items2.clear();

    item81 = new QStandardItem(tr("Чтение данных для наблюдателя скорости"));
    item81->setEditable(false);
    item81->setEnabled(false);
    QString w16=item81->text();
    item81->setToolTip(w16);
    item82 = new QStandardItem(tr("Указать каталог"));
    item82->setEnabled(false);
    QString w17=item82->text();
    item82->setToolTip(w17);
    items2.append(item81);
    items2.append(item82);
    item7->appendRow(items2);
    items2.clear();

    item116 = new QStandardItem(tr("Настройка каналов"));
    item116->setEditable(false);
    item117 = new QStandardItem(tr("Выбрать каналы"));
    QString w447=item117->text();
    item117->setToolTip(w447);
    items2.append(item116);
    items2.append(item117);
    item7->appendRow(items2);
    items2.clear();

    item65 = new QStandardItem(tr("Сохранение данных"));
    item65->setEditable(false);
    QFont newFont11("DroidSans", 10, QFont::Bold,false);
    item65->setFont(newFont11);
    QString w18=item65->text();
    item65->setToolTip(w18);
    item66 = new QStandardItem();
    item66->setEditable(false);
    items2.append(item65);
    items2.append(item66);
    item1->appendRow(items2);
    items2.clear();

    item67 = new QStandardItem(tr("Данные идентификации"));
    item67->setEditable(false);
    QString w19=item67->text();
    item67->setToolTip(w19);
    item68 = new QStandardItem(tr("Выбрать режим"));
    items2.append(item67);
    items2.append(item68);
    item65->appendRow(items2);
    items2.clear();

    item69 = new QStandardItem(tr("Данные электромагнитных процессов"));
    item69->setEditable(false);
    QString w21=item69->text();
    item69->setToolTip(w21);
    item70 = new QStandardItem(tr("Выбрать режим"));
    items2.append(item69);
    items2.append(item70);
    item65->appendRow(items2);
    items2.clear();

    item71 = new QStandardItem(tr("Данные тепловых процессов"));
    item71->setEditable(false);
    QString w23=item71->text();
    item71->setToolTip(w23);
    item72 = new QStandardItem(tr("Выбрать режим"));
    items2.append(item71);
    items2.append(item72);
    item65->appendRow(items2);
    items2.clear();

    item73 = new QStandardItem(tr("Данные вентиляционных процессов"));
    item73->setEditable(false);
    QString w25=item73->text();
    item73->setToolTip(w25);
    item74 = new QStandardItem(tr("Выбрать режим"));
    items2.append(item73);
    items2.append(item74);
    item65->appendRow(items2);
    items2.clear();

    item75 = new QStandardItem(tr("Данные прогноза температур"));
    item75->setEditable(false);
    QString w27=item75->text();
    item75->setToolTip(w27);
    item76 = new QStandardItem(tr("Выбрать режим"));
    items2.append(item75);
    items2.append(item76);
    item65->appendRow(items2);
    items2.clear();

    item77 = new QStandardItem(tr("Данные остаточного теплового ресурса"));
    item77->setEditable(false);
    QString w29=item77->text();
    item77->setToolTip(w29);
    item78 = new QStandardItem(tr("Выбрать режим"));
    items2.append(item77);
    items2.append(item78);
    item65->appendRow(items2);
    items2.clear();

    QList<QStandardItem*> items3;
    item9 = new QStandardItem(tr("Идентификация параметров схемы замещения"));
    item10 = new QStandardItem();
    items3.append(item9);
    items3.append(item10);
    model2->appendRow(items3);
    items3.clear();
    item9->setSelectable(false);
    item9->setEditable(false);
    QString w31=item9->text();
    item9->setToolTip(w31);
    item10->setSelectable(false);
    item10->setEditable(false);
    QString w32=item10->text();
    item10->setToolTip(w32);
    QFont newFont2("SansSerif", 10, QFont::Bold,false);
    item9->setFont(newFont2);

    QList<QStandardItem*> items4;
    item13 = new QStandardItem(tr("Режим расчета"));
    item13->setEditable(false);
    QString w35=item13->text();
    item13->setToolTip(w35);
    item14 = new QStandardItem(tr("Выберите режим"));
    QString w73=item14->text();
    item14->setToolTip(w73);
    items4.append(item13);
    items4.append(item14);
    item9->appendRow(items4);
    items4.clear();

    item93 = new QStandardItem(tr("Настроечный коэффициент gd="));
    item93->setEditable(false);
    item93->setEnabled(false);
    QString w37=item93->text();
    item93->setToolTip(w37);
    item94 = new QStandardItem(tr("0"));
    item94->setEnabled(false);
    item94->setCheckable(false);
    QString w38=item94->text();
    item94->setToolTip(w38);
    items4.append(item93);
    items4.append(item94);
    item9->appendRow(items4);
    items4.clear();

    item95 = new QStandardItem(tr("Настроечный коэффициент ki="));
    item95->setEditable(false);
    item95->setEnabled(false);
    QString w39=item95->text();
    item95->setToolTip(w39);
    item96 = new QStandardItem(tr("0"));
    item96->setEnabled(false);
    item96->setCheckable(false);
    QString w40=item96->text();
    item96->setToolTip(w40);
    items4.append(item95);
    items4.append(item96);
    item9->appendRow(items4);
    items4.clear();

    item97 = new QStandardItem(tr("Настроечный коэффициент gb="));
    item97->setEditable(false);
    item97->setEnabled(false);
    QString w41=item97->text();
    item97->setToolTip(w41);
    item98 = new QStandardItem(tr("0"));
    item98->setEnabled(false);
    item98->setCheckable(false);
    QString w42=item98->text();
    item98->setToolTip(w42);
    items4.append(item97);
    items4.append(item98);
    item9->appendRow(items4);
    items4.clear();

    item99 = new QStandardItem(tr("Настроечный коэффициент kpsi="));
    item99->setEditable(false);
    item99->setEnabled(false);
    QString w43=item99->text();
    item99->setToolTip(w43);
    item100 = new QStandardItem(tr("0"));
    item100->setEnabled(false);
    item100->setCheckable(false);
    QString w44=item100->text();
    item100->setToolTip(w44);
    items4.append(item99);
    items4.append(item100);
    item9->appendRow(items4);
    items4.clear();

    item101 = new QStandardItem(tr("Настроечный коэффициент gp="));
    item101->setEditable(false);
    item101->setEnabled(false);
    QString w45=item101->text();
    item101->setToolTip(w45);
    item102 = new QStandardItem(tr("0"));
    item102->setEnabled(false);
    item102->setCheckable(false);
    QString w46=item102->text();
    item102->setToolTip(w46);
    items4.append(item101);
    items4.append(item102);
    item9->appendRow(items4);
    items4.clear();

    item103 = new QStandardItem(tr("Настроечный коэффициент gpsi="));
    item103->setEditable(false);
    item103->setEnabled(false);
    QString w47=item103->text();
    item103->setToolTip(w47);
    item104 = new QStandardItem(tr("0"));
    item104->setEnabled(false);
    item104->setCheckable(false);
    QString w48=item104->text();
    item104->setToolTip(w48);
    items4.append(item103);
    items4.append(item104);
    item9->appendRow(items4);
    items4.clear();

    QList<QStandardItem*> items17;
    item145 = new QStandardItem(tr("Тепловая идентификация"));
    item146 = new QStandardItem();
    items17.append(item145);
    items17.append(item146);
    model2->appendRow(items17);
    items17.clear();
    item145->setSelectable(false);
    item145->setEditable(false);
    QString w64=item145->text();
    item145->setToolTip(w64);
    item146->setSelectable(false);
    item146->setEditable(false);
    QFont newFont17("SansSerif", 10, QFont::Bold,false);
    item145->setFont(newFont17);

    item147 = new QStandardItem(tr("Вид тепловой модели"));
    item147->setEditable(false);
    QString w65=item147->text();
    item147->setToolTip(w65);
    item148 = new QStandardItem(tr("Выберите вид"));
    QString w66=item148->text();
    item148->setToolTip(w66);
    items17.append(item147);
    items17.append(item148);
    item145->appendRow(items17);
    items17.clear();

    item149 = new QStandardItem(tr("Вид тепловой модели"));
    item149->setEditable(false);
    QString w67=item149->text();
    item149->setToolTip(w67);
    item150 = new QStandardItem(tr("Выберите вид"));
    QString w68=item150->text();
    item150->setToolTip(w68);
    items17.append(item149);
    items17.append(item150);
    item145->appendRow(items17);
    items17.clear();

    item151 = new QStandardItem(tr("Вид тепловой модели"));
    item151->setEditable(false);
    QString w69=item151->text();
    item151->setToolTip(w69);
    item152 = new QStandardItem(tr("Выберите вид"));
    QString w70=item152->text();
    item152->setToolTip(w70);
    items17.append(item151);
    items17.append(item152);
    item145->appendRow(items17);
    items17.clear();

    QList<QStandardItem*> items18;
    item153 = new QStandardItem(tr("Вентиляционная идентификация"));
    item154 = new QStandardItem();
    items18.append(item153);
    items18.append(item154);
    model2->appendRow(items18);
    items18.clear();
    item153->setSelectable(false);
    item153->setEditable(false);
    QString w71=item153->text();
    item153->setToolTip(w71);
    item154->setSelectable(false);
    item154->setEditable(false);
    QFont newFont18("SansSerif", 10, QFont::Bold,false);
    item153->setFont(newFont18);

    item155 = new QStandardItem(tr("Вид вентиляции"));
    item155->setEditable(false);
    QString w72=item155->text();
    item155->setToolTip(w72);
    item156 = new QStandardItem(tr("Выберите вид"));
    QString w74=item156->text();
    item156->setToolTip(w74);
    items18.append(item155);
    items18.append(item156);
    item153->appendRow(items18);
    items18.clear();

    item157 = new QStandardItem(tr("Режим расчета"));
    item157->setEditable(false);
    QString w75=item155->text();
    item157->setToolTip(w75);
    item158 = new QStandardItem(tr("Выберите вид"));
    QString w76=item156->text();
    item158->setToolTip(w76);
    items18.append(item157);
    items18.append(item158);
    item153->appendRow(items18);
    items18.clear();

    item159 = new QStandardItem(tr("Геометрические параметры"));
    item159->setEditable(false);
    item159->setEnabled(false);
    QString w77=item159->text();
    item159->setToolTip(w77);
    item160 = new QStandardItem(tr("Введите данные"));
    item160->setEnabled(false);
    QString w78=item160->text();
    item160->setToolTip(w78);
    items18.append(item159);
    items18.append(item160);
    item153->appendRow(items18);
    items18.clear();

    item161 = new QStandardItem(tr("Учет тепловых процессов"));
    item161->setEditable(false);
    QString w79=item161->text();
    item161->setToolTip(w79);
    item162 = new QStandardItem(tr("Введите данные"));
    QString w80=item162->text();
    item162->setToolTip(w80);
    items18.append(item161);
    items18.append(item162);
    item153->appendRow(items18);
    items18.clear();

    QList<QStandardItem*> items5;
    item17 = new QStandardItem(tr("Электромагнитная модель"));
    item18 = new QStandardItem();
    items5.append(item17);
    items5.append(item18);
    model2->appendRow(items5);
    items5.clear();
    item17->setSelectable(false);
    item17->setEditable(false);
    QString w49=item17->text();
    item17->setToolTip(w49);
    item18->setSelectable(false);
    item18->setEditable(false);
    QFont newFont3("SansSerif", 10, QFont::Bold,false);
    item17->setFont(newFont3);

    QList<QStandardItem*> items6;
    item19 = new QStandardItem(tr("Pежим работы двигателя"));
    item19->setEditable(false);
    QString w50=item19->text();
    item19->setToolTip(w50);
    item20 = new QStandardItem(tr("Выбрать режим"));
    QString w51=item20->text();
    item20->setToolTip(w51);
    items6.append(item19);
    items6.append(item20);
    item17->appendRow(items6);
    items6.clear();

    item21 = new QStandardItem(tr("Время цикла, с:"));
    item21->setEditable(false);
    item21->setEnabled(false);
    QString w52=item21->text();
    item21->setToolTip(w52);
    item22 = new QStandardItem(tr("0"));
    item22->setEnabled(false);
    QString w53=item22->text();
    item22->setToolTip(w53);
    items6.append(item21);
    items6.append(item22);
    item17->appendRow(items6);
    items6.clear();

    item175 = new QStandardItem(tr("Время работы в цикле, с:"));
    item175->setEditable(false);
    item175->setEnabled(false);
    QString w83=item175->text();
    item175->setToolTip(w83);
    item176 = new QStandardItem(tr("0"));
    item176->setEnabled(false);
    QString w84=item176->text();
    item176->setToolTip(w84);
    items6.append(item175);
    items6.append(item176);
    item17->appendRow(items6);
    items6.clear();

    item177 = new QStandardItem(tr("Время пуска в цикле, с:"));
    item177->setEditable(false);
    item177->setEnabled(false);
    QString w87=item177->text();
    item177->setToolTip(w87);
    item178 = new QStandardItem(tr("0"));
    item178->setEnabled(false);
    QString w88=item178->text();
    item178->setToolTip(w88);
    items6.append(item177);
    items6.append(item178);
    item17->appendRow(items6);
    items6.clear();

    item23 = new QStandardItem(tr("Выбор системы отсчета времени"));
    item23->setEditable(false);
     QString w54=item23->text();
    item23->setToolTip(w54);
    item24 = new QStandardItem(tr("Выберите тип отсчета"));
    QString w55=item24->text();
    item24->setToolTip(w55);
    items6.append(item23);
    items6.append(item24);
    item17->appendRow(items6);
    items6.clear();

    item173 = new QStandardItem(tr("Время работы, с:"));
    item173->setEditable(false);
    item173->setEnabled(false);
    QString w81=item173->text();
    item173->setToolTip(w81);
    item174 = new QStandardItem(tr("0"));
    item174->setEnabled(false);
    QString w82=item174->text();
    item174->setToolTip(w82);
    items6.append(item173);
    items6.append(item174);
    item17->appendRow(items6);
    items6.clear();

    item91 = new QStandardItem(tr("Выбор системы электропривода"));
    item91->setEditable(false);
    QString w58=item91->text();
    item91->setToolTip(w58);
    item92 = new QStandardItem(tr("Выбрать режим"));
    QString w59=item92->text();
    item92->setToolTip(w59);
    items6.append(item91);
    items6.append(item92);
    item17->appendRow(items6);
    items6.clear();

    item129 = new QStandardItem(tr("Ввод напряжения питания двигателя"));
    item129->setEditable(false);
    QString w60=item129->text();
    item129->setToolTip(w60);
    item130 = new QStandardItem(tr("0"));
    QString w61=item130->text();
    item130->setToolTip(w61);
    items6.append(item129);
    items6.append(item130);
    item17->appendRow(items6);
    items6.clear();

    item131 = new QStandardItem(tr("Ввод значение момента нагрузки"));
    item131->setEditable(false);
    QString w62=item131->text();
    item131->setToolTip(w62);
    item132 = new QStandardItem(tr("0"));
    QString w63=item132->text();
    item132->setToolTip(w63);
    items6.append(item131);
    items6.append(item132);
    item17->appendRow(items6);
    items6.clear();

    QList<QStandardItem*> items7;
    item25 = new QStandardItem(tr("Тепловая модель"));
    item26 = new QStandardItem();
    items7.append(item25);
    items7.append(item26);
    model2->appendRow(items7);
    items7.clear();
    item25->setSelectable(false);
    item25->setEditable(false);
    item26->setSelectable(false);
    item26->setEditable(false);
    QFont newFont4("SansSerif", 10, QFont::Bold,false);
    item25->setFont(newFont4);

    QList<QStandardItem*> items8;
    item27 = new QStandardItem(tr("Начальное значение температуры, °C"));
    item27->setEditable(false);
    item28 = new QStandardItem(tr("0"));
    items8.append(item27);
    items8.append(item28);
    item25->appendRow(items8);
    items8.clear();

    item29 = new QStandardItem(tr("Температурный режим"));
    item29->setEditable(false);
    item30 = new QStandardItem(tr("Выберите режим"));
    items8.append(item29);
    items8.append(item30);
    item25->appendRow(items8);
    items8.clear();

    item140 = new QStandardItem(tr("Температурный режим Статика"));
    item140->setEditable(false);
    item141 = new QStandardItem(tr("Выберите режим"));
    items8.append(item140);
    items8.append(item141);
    item25->appendRow(items8);
    items8.clear();

    item144 = new QStandardItem(tr("Температурный режим Динамика"));
    item144->setEditable(false);
    item142 = new QStandardItem(tr("Выберите режим"));
    items8.append(item144);
    items8.append(item142);
    item25->appendRow(items8);
    items8.clear();

    item23 = new QStandardItem(tr("Шаг выбора точек"));
    item23->setEditable(false);
    item107 = new QStandardItem(tr("0"));
    items8.append(item23);
    items8.append(item107);
    item25->appendRow(items8);
    items8.clear();

    QList<QStandardItem*> items9;
    item31 = new QStandardItem(tr("Вентиляционная модель"));
    item32 = new QStandardItem();
    items9.append(item31);
    items9.append(item32);
    model2->appendRow(items9);
    items9.clear();
    item31->setSelectable(false);
    item31->setEditable(false);
    item32->setSelectable(false);
    item32->setEditable(false);
    QFont newFont5("SansSerif", 10, QFont::Bold,false);
    item31->setFont(newFont5);

    QList<QStandardItem*> items10;
    item33 = new QStandardItem(tr("Вентиляционный режим"));
    item33->setEditable(false);
    item34 = new QStandardItem(tr("Выберите режим"));
    items10.append(item33);
    items10.append(item34);
    item31->appendRow(items10);
    items10.clear();

    item35 = new QStandardItem(tr("Конструкция вентиляционной системы электродвигателя"));
    item35->setEditable(false);
    item36 = new QStandardItem(QString ("Выберите конструкцию"));
    items10.append(item35);
    items10.append(item36);
    item31->appendRow(items10);
    items10.clear();

    item37 = new QStandardItem(tr("Барометрическое давление, Па"));
    item37->setEditable(false);
    item38 = new QStandardItem(tr("0"));
    items10.append(item37);
    items10.append(item38);
    item31->appendRow(items10);
    items10.clear();

    QList<QStandardItem*> items11;
    item39 = new QStandardItem(tr("Прогнозирование температур"));
    item40 = new QStandardItem();
    items11.append(item39);
    items11.append(item40);
    model2->appendRow(items11);
    items11.clear();
    item39->setSelectable(false);
    item39->setEditable(false);
    item40->setSelectable(false);
    item40->setEditable(false);
    QFont newFont6("SansSerif", 10, QFont::Bold,false);
    item39->setFont(newFont6);

    QList<QStandardItem*> items12;
    item41 = new QStandardItem(tr("Условие 13"));
    item41->setEditable(false);
    item42 = new QStandardItem(tr("Значение 13"));
    items12.append(item41);
    items12.append(item42);
    item39->appendRow(items12);
    items12.clear();

    item43 = new QStandardItem(tr("Условие 14"));
    item43->setEditable(false);
    item44 = new QStandardItem(tr("Значение 14"));
    items12.append(item43);
    items12.append(item44);
    item39->appendRow(items12);
    items12.clear();

    item45 = new QStandardItem(tr("Условие 15"));
    item45->setEditable(false);
    item46 = new QStandardItem(tr("Значение 15"));
    items12.append(item45);
    items12.append(item46);
    item39->appendRow(items12);
    items12.clear();

    QList<QStandardItem*> items13;
    item47 = new QStandardItem(tr("Оценка остаточного теплового ресурса"));
    item48 = new QStandardItem();
    items13.append(item47);
    items13.append(item48);
    model2->appendRow(items13);
    items13.clear();
    item47->setSelectable(false);
    item47->setEditable(false);
    item48->setSelectable(false);
    item48->setEditable(false);
    QFont newFont7("SansSerif", 10, QFont::Bold,false);
    item47->setFont(newFont7);

    QList<QStandardItem*> items14;
    item49 = new QStandardItem(tr("Условие 16"));
    item49->setEditable(false);
    item50 = new QStandardItem(tr("Значение 16"));
    items14.append(item49);
    items14.append(item50);
    item47->appendRow(items14);
    items14.clear();

    item51 = new QStandardItem(tr("Условие 17"));
    item51->setEditable(false);
    item52 = new QStandardItem(tr("Значение 17"));
    items14.append(item51);
    items14.append(item52);
    item47->appendRow(items14);
    items14.clear();

    item53 = new QStandardItem(tr ("Условие 18"));
    item53->setEditable(false);
    item54 = new QStandardItem(tr ("Значение 18"));
    items14.append(item53);
    items14.append(item54);
    item47->appendRow(items14);
    items14.clear();

    QList<QStandardItem*> items15;
    item55 = new QStandardItem(tr ("Выходные данные"));
    item56 = new QStandardItem();
    items15.append(item55);
    items15.append(item56);
    model2->appendRow(items15);
    items15.clear();
    item55->setSelectable(false);
    item55->setEditable(false);
    item56->setSelectable(false);
    item56->setEditable(false);
    QFont newFont8("SansSerif", 10, QFont::Bold,false);
    item55->setFont(newFont8);

    QList<QStandardItem*> items16;
    item57 = new QStandardItem(tr ("Условие 19"));
    item57->setEditable(false);
    item58 = new QStandardItem(tr ("Значение 19"));
    items16.append(item57);
    items16.append(item58);
    item55->appendRow(items16);
    items16.clear();
    item59 = new QStandardItem(tr ("Условие 20"));
    item59->setEditable(false);
    item60 = new QStandardItem(QString ("Значение 20"));
    items16.append(item59);
    items16.append(item60);
    item55->appendRow(items16);
    items16.clear();
    item61 = new QStandardItem(tr ("Условие 21"));
    item61->setEditable(false);
    item62 = new QStandardItem(tr ("Значение 21"));
    items16.append(item61);
    items16.append(item62);
    item55->appendRow(items16);
    items16.clear();

    //Настройка представления модели QTreeView
    ui->treeView->setModel(model2);
    ui->treeView->header()->resizeSection(0,270);
    ui->treeView->header()->setSectionResizeMode(0,QHeaderView::Interactive);
    ui->treeView->header()->setSectionResizeMode(1,QHeaderView::Fixed);
    ui->treeView->expandAll();

    ButtonColumnDelegate* buttonColumnDelegate = new ButtonColumnDelegate(this); //создание делегата для создания комбобоксов
    ui->treeView->setItemDelegateForColumn(1, buttonColumnDelegate);

    ui->treeView->setStyleSheet(
                    "QScrollBar:vertical {border-width: 0px;border-style: solid;"
                    "background-color: #FFFFFF; width: 18px;}"
                    "QScrollBar::handle:vertical {background-color:#d0d2d2;min-height: 25px;"
                    "margin-left:5px;margin-right:5px;border-radius:4px;margin-top:5px;margin-bottom:5px;}"
                    "QScrollBar::handle:vertical:hover {background-color:#97d5f0;}"
                    "QScrollBar::add-line:vertical {border: 0px solid black;"
                    "height: 0px;subcontrol-position: bottom;subcontrol-origin: margin;}"
                    "QScrollBar::sub-line:vertical {border: 0px solid black;"
                    "height: 0px;subcontrol-position: top;subcontrol-origin: margin;}"
                            "*{"
                            "background: rgb(255, 255, 222);"
                            "}"
                           "*{"
                            "alternate-background-color: rgb(255, 255, 191);"
                           "}"
                            "*::item{"
                            "    border-top-width: 0px;"
                            "    border-right-width: 1px;"
                            "    border-bottom-width: 1px;"
                            "    border-left-width: 0px;"
                            "    border-style: solid;"
                            "    border-color: silver;"
                            "}"
                            "*::item:selected{"
                            "    background: palette(Highlight);"
                            "}"
//                            "*::item:has-children{"
//                            "    background: rgb(128,128,128);"
//                            "}"
                            "::branch"
                            "{"
                            "border-bottom: 1px solid silver;"
                            "border-image: none 0;"
                            "image: none 0;"
                            "}"
                                    "::branch:has-children:!has-siblings:closed,"
                                    "::branch:closed:has-children:has-siblings {"
                                    "        border-image: none;"
                                    "        image: url(:/image/data/img/icons/branch-closed.png);"
                                    "}"
                                    "::branch:open:has-children:!has-siblings,"
                                    "::branch:open:has-children:has-siblings  {"
                                   "        border-image: none;"
                                    "        image: url(:/image/data/img/icons/branch-open.png);"
                                    "}"
                "::branch:has-siblings:!adjoins-item {"
                "    border-image: url(:/data/img/icons/vline.png) 0;"
                "}"

                "::branch:has-siblings:adjoins-item {"
                "    border-image: url(:/data/img/icons/branch-more.png) 0;"
                "}"

                "::branch:!has-children:!has-siblings:adjoins-item {"
                "    border-image: url(:/data/img/icons/branch-end.png) 0;"
                "}"

                "::branch:has-children:!has-siblings:closed,"
                "::branch:closed:has-children:has-siblings {"
                "        border-image: none;"
                "        image: url(:/image/data/img/icons/branch-closed.png);"
                "}"

                "::branch:open:has-children:!has-siblings,"
                "::branch:open:has-children:has-siblings  {"
                "        border-image: none;"
                "        image: url(:/image/data/img/icons/branch-open.png);"
                "}"

                                    );

    ui->treeView->setRootIsDecorated(true);

    //color_treview(model2->index(0,0), model2);

    selectionModel = ui->treeView->selectionModel();
    //connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &MainWindow::treview_changed);
    connect(selectionModel, &QItemSelectionModel::currentChanged,
                     this, [this]() {   int index = 0;
        QString currentTabText = ui->tabWidget->tabText(index);
        setWindowTitle(currentTabText + "@" + QString(item4->text()) + QString(" - ImView*"));
        isNablLaunched = true;
    });

    selectionModel2 = ui->widget->ui->tableView->selectionModel();
    //connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &MainWindow::treview_changed);
    connect(selectionModel2, &QItemSelectionModel::currentChanged,
                     this, []() {  isNablLaunched = true;
    });


    connect(ui->lineEdit_13, &QLineEdit::textChanged, this, []() {
      isNablLaunched = true;
    });
    connect(ui->lineEdit_14, &QLineEdit::textChanged, this, []() {
      isNablLaunched = true;
    });
    connect(ui->lineEdit_15, &QLineEdit::textChanged, this, []() {
      isNablLaunched = true;
    });
    connect(ui->lineEdit_16, &QLineEdit::textChanged, this, []() {
      isNablLaunched = true;
    });
    connect(ui->lineEdit_17, &QLineEdit::textChanged, this, []() {
      isNablLaunched = true;
    });
    connect(ui->lineEdit_18, &QLineEdit::textChanged, this, []() {
      isNablLaunched = true;
    });
    connect(ui->lineEdit_8, &QLineEdit::textChanged, this, []() {
      isNablLaunched = true;
    });
    connect(ui->lineEdit_9, &QLineEdit::textChanged, this, []() {
      isNablLaunched = true;
    });
    connect(ui->lineEdit_10, &QLineEdit::textChanged, this, []() {
      isNablLaunched = true;
    });
    connect(ui->lineEdit_11, &QLineEdit::textChanged, this, []() {
      isNablLaunched = true;
    });
    connect(ui->lineEdit_12, &QLineEdit::textChanged, this, []() {
      isNablLaunched = true;
    });

    //createUndoView();

    ui->tabWidget->setCurrentIndex(0);
    currentTabText = ui->tabWidget->tabText(0);

    setWindowTitle(currentTabText + "@" + QString(item4->text()) + QString(" - ImView"));
    if(ui->LoadProgect->isChecked() && ui->SaveProgectToFile->isChecked())
    {
        setWindowTitle(currentTabText + "@" + QString(item4->text()) + QString(" - ImView"));
    }
   // setWindowTitle(currentTabText + "@" + QString(item4->text()) + QString(" - ImView"));

    ui->tableWidget->setRowCount(30); //задание количества строк таблицы
    ui->tableWidget->setColumnCount(5); //задание количества столбцов
    QStringList name2; //объявление указателя на тип QStringList
    name2 << "№" << "Цвет" << "Свойство" << "Смещение" << "Масштаб"; //перечисление заголовков
    ui->tableWidget->setHorizontalHeaderLabels(name2); //установка заголовков в таблицу
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); //Устанавливает ограничения на то, как размер заголовка может быть изменен до тех, которые описаны в данном режиме
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setSelectionMode(QAbstractItemView :: NoSelection);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnWidth(0, 100);

    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget->columnCount(); column++)
        {
          ui->tableWidget->setItem(row, column, new QTableWidgetItem());
        }
    }

    QTableWidgetItem *item251 = new QTableWidgetItem("Item251");
    item251->setCheckState(Qt::Checked);
    item251->setText("Сопротивление ротора R2, Ом");
    ui->tableWidget->setItem(0, 2, item251);

    QTableWidgetItem *item252 = new QTableWidgetItem("Item252");
    item252->setCheckState(Qt::Checked);
    item252->setText("Индуктивность обмотки статора L1, Гн");
    ui->tableWidget->setItem(1, 2, item252);

    QTableWidgetItem *item253 = new QTableWidgetItem("Item253");
    item253->setCheckState(Qt::Checked);
    item253->setText("Индуктивность обмотки ротора L2, Гн");
    ui->tableWidget->setItem(2, 2, item253);

    QTableWidgetItem *item254 = new QTableWidgetItem("Item254");
    item254->setCheckState(Qt::Checked);
    item254->setText("Индуктивность взаимоиндукции Lm, Гн");
    ui->tableWidget->setItem(3, 2, item254);

    QTableWidgetItem *item255 = new QTableWidgetItem("Item255");
    item255->setCheckState(Qt::Checked);
    item255->setText("Напряжение фазы А, В");
    ui->tableWidget->setItem(4, 2, item255);

    QTableWidgetItem *item256 = new QTableWidgetItem("Item256");
    item256->setCheckState(Qt::Checked);
    item256->setText("Напряжение фазы B, В");
    ui->tableWidget->setItem(5, 2, item256);

    QTableWidgetItem *item257 = new QTableWidgetItem("Item257");
    item257->setCheckState(Qt::Checked);
    item257->setText("Напряжение фазы C, В");
    ui->tableWidget->setItem(6, 2, item257);

    QTableWidgetItem *item258 = new QTableWidgetItem("Item258");
    item258->setCheckState(Qt::Checked);
    item258->setText("Ток фазы А, А");
    ui->tableWidget->setItem(7, 2, item258);

    QTableWidgetItem *item259 = new QTableWidgetItem("Item259");
    item259->setCheckState(Qt::Checked);
    item259->setText("Ток фазы B, А");
    ui->tableWidget->setItem(8, 2, item259);

    QTableWidgetItem *item260 = new QTableWidgetItem("Item260");
    item260->setCheckState(Qt::Checked);
    item260->setText("Ток фазы C, А");
    ui->tableWidget->setItem(9, 2, item260);

    QTableWidgetItem *item261 = new QTableWidgetItem("Item261");
    item261->setCheckState(Qt::Checked);
    item261->setText("Частота вращения, рад/с");
    ui->tableWidget->setItem(10, 2, item261);

    QTableWidgetItem *item262 = new QTableWidgetItem("Item262");
    item262->setCheckState(Qt::Checked);
    item262->setText("Момент на валу, Н*м");
    ui->tableWidget->setItem(11, 2, item262);

    QTableWidgetItem *item263 = new QTableWidgetItem("Item263");
    item263->setCheckState(Qt::Checked);
    item263->setText("Момент Мс, Н*м");
    ui->tableWidget->setItem(12, 2, item263);

    QTableWidgetItem *item264 = new QTableWidgetItem("Item264");
    item264->setCheckState(Qt::Checked);
    item264->setText("Станина, °C");
    ui->tableWidget->setItem(13, 2, item264);

    QTableWidgetItem *item265 = new QTableWidgetItem("Item265");
    item265->setCheckState(Qt::Checked);
    item265->setText("Подшипниковый узел справа сзади, °C");
    ui->tableWidget->setItem(14, 2, item265);

    QTableWidgetItem *item266 = new QTableWidgetItem("Item266");
    item266->setCheckState(Qt::Checked);
    item266->setText("Лобовая часть слева спереди, °C");
    ui->tableWidget->setItem(15, 2, item266);

    QTableWidgetItem *item267 = new QTableWidgetItem("Item267");
    item267->setCheckState(Qt::Checked);
    item267->setText("Подшипниковый узел слева спереди, °C");
    ui->tableWidget->setItem(16, 2, item267);

    QTableWidgetItem *item268 = new QTableWidgetItem("Item268");
    item268->setCheckState(Qt::Checked);
    item268->setText("Лобовая часть слева сзади, °C");
    ui->tableWidget->setItem(17, 2, item268);

    QTableWidgetItem *item269 = new QTableWidgetItem("Item269");
    item269->setCheckState(Qt::Checked);
    item269->setText("Станина, °C");
    ui->tableWidget->setItem(18, 2, item269);

    QTableWidgetItem *item270 = new QTableWidgetItem("Item270");
    item270->setCheckState(Qt::Checked);
    item270->setText("Лобовая часть справа спереди, °C");
    ui->tableWidget->setItem(19, 2, item270);

    QTableWidgetItem *item271 = new QTableWidgetItem("Item271");
    item271->setCheckState(Qt::Checked);
    item271->setText("Лобовая часть справа сзади, °C");
    ui->tableWidget->setItem(20, 2, item271);

    QTableWidgetItem *item272 = new QTableWidgetItem("Item272");
    item272->setCheckState(Qt::Checked);
    item272->setText("Магнитопровод статора, °C");
    ui->tableWidget->setItem(21, 2, item272);

    QTableWidgetItem *item273 = new QTableWidgetItem("Item273");
    item273->setCheckState(Qt::Checked);
    item273->setText("Подшипниковый узел справа спереди, °C");
    ui->tableWidget->setItem(22, 2, item273);

    QTableWidgetItem *item274 = new QTableWidgetItem("Item274");
    item274->setCheckState(Qt::Checked);
    item274->setText("одшипниковый узел слева сзади, °C");
    ui->tableWidget->setItem(23, 2, item274);

    QTableWidgetItem *item275 = new QTableWidgetItem("Item275");
    item275->setCheckState(Qt::Checked);
    item275->setText("Ротор сверху, °C");
    ui->tableWidget->setItem(24, 2, item275);

    QTableWidgetItem *item276 = new QTableWidgetItem("Item276");
    item276->setCheckState(Qt::Checked);
    item276->setText("Ротор снизу, °C");
    ui->tableWidget->setItem(25, 2, item276);

    QTableWidgetItem *item277 = new QTableWidgetItem("Item277");
    item277->setCheckState(Qt::Checked);
    item277->setText("Станина слева, °C");
    ui->tableWidget->setItem(26, 2, item277);

    QTableWidgetItem *item278 = new QTableWidgetItem("Item278");
    item278->setCheckState(Qt::Checked);
    item278->setText("Станина справа, °C");
    ui->tableWidget->setItem(27, 2, item278);


    QTableWidgetItem *item279 = new QTableWidgetItem("Item279");
    item279->setCheckState(Qt::Checked);
    item279->setText("Вал, °C");
    ui->tableWidget->setItem(28, 2, item279);

    QTableWidgetItem *item280 = new QTableWidgetItem("Item280");
    item280->setCheckState(Qt::Checked);
    item280->setText("Клеммная коробка, °C");
    ui->tableWidget->setItem(29, 2, item280);

    for (int i=0; i<34; i++)
    {
        if (ui->tableWidget->item(i, 0) != 0)
        {
            ui->tableWidget->item(i, 0)->setText(QString("%1").arg(i+1));
            ui->tableWidget->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }


    for (int i=0; i<34; i++)
    {
        if (ui->tableWidget->item(i, 3) != 0)
        {
            ui->tableWidget->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }

        if (ui->tableWidget->item(i, 4) != 0)
        {
            ui->tableWidget->item(i, 4)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->tableWidget->setItem(0, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(0, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(1, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(1, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(2, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(2, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(3, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(3, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(4, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(4, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(5, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(5, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(6, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(6, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(7, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(7, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(8, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(8, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(9, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(9, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(10, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(10, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(11, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(11, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(12, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(12, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(13, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(13, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(14, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(14, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(15, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(15, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(16, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(16, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(17, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(17, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(18, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(18, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(19, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(19, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(20, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(20, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(21, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(21, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(22, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(22, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(23, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(23, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(24, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(24, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(25, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(25, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(26, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(26, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(27, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(27, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(28, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(28, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(29, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(29, 4, new QTableWidgetItem(QString("%1").arg(1)));

    //Заполнение таблицы результатов
    ui->tableWidget_2->setRowCount(25);
    ui->tableWidget_2->setColumnCount(4);
    QStringList name_2;
    name_2 << "Величина" << "Обозначение" << "Значение" << "Размерность";
    ui->tableWidget_2->setHorizontalHeaderLabels(name_2);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->verticalHeader()->setVisible(true);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView :: SingleSelection);

    for(int row = 0; row<ui->tableWidget_2->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_2->columnCount(); column++)
        {
            ui->tableWidget_2->setItem(row, column, new QTableWidgetItem());
        }
    }

    ui->tableWidget_2->setItem(0, 0, new QTableWidgetItem("Ток фазы А, А"));
    ui->tableWidget_2->setItem(1, 0, new QTableWidgetItem("Напряжение фазы А, В"));
    ui->tableWidget_2->setItem(2, 0, new QTableWidgetItem("Активная мошность фазы А, Вт"));
    ui->tableWidget_2->setItem(3, 0, new QTableWidgetItem("Реактивная мошность фазы А, ВА"));
    ui->tableWidget_2->setItem(4, 0, new QTableWidgetItem("Полная мошность фазы А, ВАР"));
    ui->tableWidget_2->setItem(5, 0, new QTableWidgetItem("Коэффициент мощности фазы А"));
    ui->tableWidget_2->setItem(6, 0, new QTableWidgetItem("Ток фазы В, А"));
    ui->tableWidget_2->setItem(7, 0, new QTableWidgetItem("Напряжение фазы В, В"));
    ui->tableWidget_2->setItem(8, 0, new QTableWidgetItem("Активная мошность фазы В, Вт"));
    ui->tableWidget_2->setItem(9, 0, new QTableWidgetItem("Реактивная мошность фазы В, ВА"));
    ui->tableWidget_2->setItem(10, 0, new QTableWidgetItem("Полная мошность фазы В, ВАР"));
    ui->tableWidget_2->setItem(11, 0, new QTableWidgetItem("Коэффициент мощности фазы В"));
    ui->tableWidget_2->setItem(12, 0, new QTableWidgetItem("Ток фазы С, А"));
    ui->tableWidget_2->setItem(13, 0, new QTableWidgetItem("Напряжение фазы С, В"));
    ui->tableWidget_2->setItem(14, 0, new QTableWidgetItem("Активная мошность фазы С, Вт"));
    ui->tableWidget_2->setItem(15, 0, new QTableWidgetItem("Реактивная мошность фазы С, ВА"));
    ui->tableWidget_2->setItem(16, 0, new QTableWidgetItem("Полная мошность фазы С, ВАР"));
    ui->tableWidget_2->setItem(17, 0, new QTableWidgetItem("Коэффициент мощности фазы С"));
    ui->tableWidget_2->setItem(18, 0, new QTableWidgetItem("трехфазная активная мошность, Вт"));
    ui->tableWidget_2->setItem(19, 0, new QTableWidgetItem("Трехфазная реактивная мошность, ВА"));
    ui->tableWidget_2->setItem(20, 0, new QTableWidgetItem("Трехфазная полная мошность, ВАР"));
    ui->tableWidget_2->setItem(21, 0, new QTableWidgetItem("Коэффициент мощности"));
    ui->tableWidget_2->setItem(22, 0, new QTableWidgetItem("Скорость вращения ротора, рад/с"));
    ui->tableWidget_2->setItem(23, 0, new QTableWidgetItem("Момент, Н*м"));
    ui->tableWidget_2->setItem(24, 0, new QTableWidgetItem("Момент сопротивления, Н*м"));

    ui->tableWidget_2->setItem(0, 1, new QTableWidgetItem("i_dev_a"));
    ui->tableWidget_2->setItem(1, 1, new QTableWidgetItem("u_dev_a"));
    ui->tableWidget_2->setItem(2, 1, new QTableWidgetItem("p_akt_a"));
    ui->tableWidget_2->setItem(3, 1, new QTableWidgetItem("p_reakt_a"));
    ui->tableWidget_2->setItem(4, 1, new QTableWidgetItem("p_poln_a"));
    ui->tableWidget_2->setItem(5, 1, new QTableWidgetItem("cos_f_a"));
    ui->tableWidget_2->setItem(6, 1, new QTableWidgetItem("i_dev_b"));
    ui->tableWidget_2->setItem(7, 1, new QTableWidgetItem("u_dev_b"));
    ui->tableWidget_2->setItem(8, 1, new QTableWidgetItem("p_akt_b"));
    ui->tableWidget_2->setItem(9, 1, new QTableWidgetItem("p_reakt_b"));
    ui->tableWidget_2->setItem(10, 1, new QTableWidgetItem("p_poln_b"));
    ui->tableWidget_2->setItem(11, 1, new QTableWidgetItem("cos_f_b"));
    ui->tableWidget_2->setItem(12, 1, new QTableWidgetItem("i_dev_c"));
    ui->tableWidget_2->setItem(13, 1, new QTableWidgetItem("u_dev_c"));
    ui->tableWidget_2->setItem(14, 1, new QTableWidgetItem("p_akt_c"));
    ui->tableWidget_2->setItem(15, 1, new QTableWidgetItem("p_reakt_c"));
    ui->tableWidget_2->setItem(16, 1, new QTableWidgetItem("p_poln_c"));
    ui->tableWidget_2->setItem(17, 1, new QTableWidgetItem("cos_f_c"));
    ui->tableWidget_2->setItem(18, 1, new QTableWidgetItem("p_akt"));
    ui->tableWidget_2->setItem(19, 1, new QTableWidgetItem("p_reakt"));
    ui->tableWidget_2->setItem(20, 1, new QTableWidgetItem("p_poln"));
    ui->tableWidget_2->setItem(21, 1, new QTableWidgetItem("cos_f"));
    ui->tableWidget_2->setItem(22, 1, new QTableWidgetItem("omega"));
    ui->tableWidget_2->setItem(23, 1, new QTableWidgetItem("M"));
    ui->tableWidget_2->setItem(24, 1, new QTableWidgetItem("Mc"));

    ui->tableWidget_2->setItem(0, 3, new QTableWidgetItem("А"));
    ui->tableWidget_2->setItem(1, 3, new QTableWidgetItem("В"));
    ui->tableWidget_2->setItem(2, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_2->setItem(3, 3, new QTableWidgetItem("ВА"));
    ui->tableWidget_2->setItem(4, 3, new QTableWidgetItem("ВАР"));
    ui->tableWidget_2->setItem(5, 3, new QTableWidgetItem(" - "));
    ui->tableWidget_2->setItem(6, 3, new QTableWidgetItem("А"));
    ui->tableWidget_2->setItem(7, 3, new QTableWidgetItem("В"));
    ui->tableWidget_2->setItem(8, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_2->setItem(9, 3, new QTableWidgetItem("ВА"));
    ui->tableWidget_2->setItem(10, 3, new QTableWidgetItem("ВАР"));
    ui->tableWidget_2->setItem(11, 3, new QTableWidgetItem(" - "));
    ui->tableWidget_2->setItem(12, 3, new QTableWidgetItem("А"));
    ui->tableWidget_2->setItem(13, 3, new QTableWidgetItem("В"));
    ui->tableWidget_2->setItem(14, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_2->setItem(15, 3, new QTableWidgetItem("ВА"));
    ui->tableWidget_2->setItem(16, 3, new QTableWidgetItem("ВАР"));
    ui->tableWidget_2->setItem(17, 3, new QTableWidgetItem(" - "));
    ui->tableWidget_2->setItem(18, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_2->setItem(19, 3, new QTableWidgetItem("ВА"));
    ui->tableWidget_2->setItem(20, 3, new QTableWidgetItem("ВАР"));
    ui->tableWidget_2->setItem(21, 3, new QTableWidgetItem(" - "));
    ui->tableWidget_2->setItem(22, 3, new QTableWidgetItem("рад/с"));
    ui->tableWidget_2->setItem(23, 3, new QTableWidgetItem("Н*м"));
    ui->tableWidget_2->setItem(24, 3, new QTableWidgetItem("Н*м"));

    for (int i=0; i<ui->tableWidget_2->rowCount(); i++)
    {
        if (ui->tableWidget_2->item(i, 1) != 0)
        {
            ui->tableWidget_2->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_2->item(i, 2) != 0)
        {
            ui->tableWidget_2->item(i, 2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_2->item(i, 3) != 0)
        {
            ui->tableWidget_2->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }

    QPalette p2=ui->tableWidget_2->palette();
    p2.setColor(QPalette::Base, QColor(255, 255, 191));
    p2.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget_2->setPalette(p2);


    //вставка таблицы тепловые характеристики
    ui->tableWidget_3->setRowCount(17);
    ui->tableWidget_3->setColumnCount(3);
    QStringList name;
    name << " № " << "Сигнал" << "Величина";
    ui->tableWidget_3->setHorizontalHeaderLabels(name);
    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_3->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_3->verticalHeader()->setVisible(false);
    ui->tableWidget_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_3->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_3->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_3->setColumnWidth(0, 100);

    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_3->columnCount(); column++)
        {
            ui->tableWidget_3->setItem(row, column, new QTableWidgetItem());

        }
    }

    for (int i=0; i<17; i++)
    {
        if (ui->tableWidget_3->item(i, 0) != 0)
        {
            ui->tableWidget_3->item(i, 0)->setText(QString("%1").arg(i+1));
            ui->tableWidget_3->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->tableWidget_3->setItem(0,  1, new QTableWidgetItem("Станина, °C"));
    ui->tableWidget_3->setItem(1,  1, new QTableWidgetItem("Подшипниковый узел справа сзади, °C"));
    ui->tableWidget_3->setItem(2,  1, new QTableWidgetItem("Лобовая часть слева спереди, °C"));
    ui->tableWidget_3->setItem(3,  1, new QTableWidgetItem("Подшипниковый узел слева спереди, °C"));
    ui->tableWidget_3->setItem(4,  1, new QTableWidgetItem("Лобовая часть слева сзади, °C"));
    ui->tableWidget_3->setItem(5,  1, new QTableWidgetItem("Станина, °C"));
    ui->tableWidget_3->setItem(6,  1, new QTableWidgetItem("Лобовая часть справа спереди, °C"));
    ui->tableWidget_3->setItem(7,  1, new QTableWidgetItem("Лобовая часть справа сзади, °C"));
    ui->tableWidget_3->setItem(8,  1, new QTableWidgetItem("Магнитопровод статора, °C"));
    ui->tableWidget_3->setItem(9,  1, new QTableWidgetItem("Подшипниковый узел справа спереди, °C"));
    ui->tableWidget_3->setItem(10, 1, new QTableWidgetItem("Подшипниковый узел слева сзади, °C"));
    ui->tableWidget_3->setItem(11, 1, new QTableWidgetItem("Ротор сверху, °C"));
    ui->tableWidget_3->setItem(12, 1, new QTableWidgetItem("Ротор снизу, °C"));
    ui->tableWidget_3->setItem(13, 1, new QTableWidgetItem("Станина слева, °C"));
    ui->tableWidget_3->setItem(14, 1, new QTableWidgetItem("Станина справа, °C"));
    ui->tableWidget_3->setItem(15, 1, new QTableWidgetItem("Вал, °C"));
    ui->tableWidget_3->setItem(16, 1, new QTableWidgetItem("Клеммная коробка, °C"));

    QPalette p102=ui->tableWidget_3->palette();
    p102.setColor(QPalette::Base, QColor(225, 255, 255));
    p102.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget_3->setPalette(p102);

    //вставка таблицы Энергетические характеристики таблицы tableWidget_4
    ui->tableWidget_4->setRowCount(30);
    ui->tableWidget_4->setColumnCount(4);
    QStringList name_4;
    name_4 << "Величина" << "Обозначение" << "Значение" << "Размерность";
    ui->tableWidget_4->setHorizontalHeaderLabels(name_4);
    ui->tableWidget_4->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_4->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_4->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_4->verticalHeader()->setVisible(true);
    ui->tableWidget_4->resizeColumnsToContents();

    for(int row = 0; row<ui->tableWidget_4->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_4->columnCount(); column++)
        {
            ui->tableWidget_4->setItem(row, column, new QTableWidgetItem());

        }
    }


    //Заполнение полей левой части таблицы для пояснения чекбоксов таблицы tableWidget_3
    ui->tableWidget_4->setItem(0, 0, new QTableWidgetItem("Потребляемая двигателем мощность, Вт"));
    ui->tableWidget_4->setItem(1, 0, new QTableWidgetItem("Потери в обмотке статора Вт"));
    ui->tableWidget_4->setItem(2, 0, new QTableWidgetItem("Потери в стали, Вт"));
    ui->tableWidget_4->setItem(3, 0, new QTableWidgetItem("Потери в обмотке ротора, Вт"));
    ui->tableWidget_4->setItem(4, 0, new QTableWidgetItem("Добавочные потери, Вт"));
    ui->tableWidget_4->setItem(5, 0, new QTableWidgetItem("Механические потери, Вт"));
    ui->tableWidget_4->setItem(6, 0, new QTableWidgetItem("Механическая мощность на валу двигателя, Вт"));
    ui->tableWidget_4->setItem(7, 0, new QTableWidgetItem("Коэффициент полезного действия"));
    ui->tableWidget_4->setItem(8, 0, new QTableWidgetItem("Коэффициент мощности"));

    ui->tableWidget_4->setItem(0, 1, new QTableWidgetItem("P1"));
    ui->tableWidget_4->setItem(1, 1, new QTableWidgetItem("ΔPel1"));
    ui->tableWidget_4->setItem(2, 1, new QTableWidgetItem("ΔPct"));
    ui->tableWidget_4->setItem(3, 1, new QTableWidgetItem("ΔPel2"));
    ui->tableWidget_4->setItem(4, 1, new QTableWidgetItem("ΔPdob"));
    ui->tableWidget_4->setItem(5, 1, new QTableWidgetItem("ΔPmech"));
    ui->tableWidget_4->setItem(6, 1, new QTableWidgetItem("P2"));
    ui->tableWidget_4->setItem(7, 1, new QTableWidgetItem("KPD"));
    ui->tableWidget_4->setItem(8, 1, new QTableWidgetItem("cosf"));

    ui->tableWidget_4->setItem(0, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_4->setItem(1, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_4->setItem(2, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_4->setItem(3, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_4->setItem(4, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_4->setItem(5, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_4->setItem(6, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_4->setItem(7, 3, new QTableWidgetItem("--"));
    ui->tableWidget_4->setItem(8, 3, new QTableWidgetItem("--"));

    for (int i=0; i<ui->tableWidget_4->rowCount(); i++)
    {
        if (ui->tableWidget_4->item(i, 1) != 0)
        {
            ui->tableWidget_4->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_4->item(i, 2) != 0)
        {
            ui->tableWidget_4->item(i, 2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_4->item(i, 3) != 0)
        {
            ui->tableWidget_4->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }

    QPalette p4=ui->tableWidget_4->palette();
    p4.setColor(QPalette::Base, QColor(225, 255, 255));
    p4.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget_4->setPalette(p4);

    ui->tableWidget_5->setRowCount(17);
    ui->tableWidget_5->setColumnCount(3);
    QStringList name_5;
    name_5 << " № " << "Сигнал" << "Величина";
    ui->tableWidget_5->setHorizontalHeaderLabels(name);
    ui->tableWidget_5->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_5->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_5->verticalHeader()->setVisible(false);
    ui->tableWidget_5->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_5->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_5->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_5->setColumnWidth(0, 100);

    for(int row = 0; row<ui->tableWidget_5->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_5->columnCount(); column++)
        {
            ui->tableWidget_5->setItem(row, column, new QTableWidgetItem());

        }
    }

    for (int i=0; i<17; i++)
    {
        if (ui->tableWidget_5->item(i, 0) != 0)
        {
            ui->tableWidget_5->item(i, 0)->setText(QString("%1").arg(i+1));
            ui->tableWidget_5->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->tableWidget_5->setItem(0,  1, new QTableWidgetItem("Станина, °C"));
    ui->tableWidget_5->setItem(1,  1, new QTableWidgetItem("Подшипниковый узел справа сзади, °C"));
    ui->tableWidget_5->setItem(2,  1, new QTableWidgetItem("Лобовая часть слева спереди, °C"));
    ui->tableWidget_5->setItem(3,  1, new QTableWidgetItem("Подшипниковый узел слева спереди, °C"));
    ui->tableWidget_5->setItem(4,  1, new QTableWidgetItem("Лобовая часть слева сзади, °C"));
    ui->tableWidget_5->setItem(5,  1, new QTableWidgetItem("Станина, °C"));
    ui->tableWidget_5->setItem(6,  1, new QTableWidgetItem("Лобовая часть справа спереди, °C"));
    ui->tableWidget_5->setItem(7,  1, new QTableWidgetItem("Лобовая часть справа сзади, °C"));
    ui->tableWidget_5->setItem(8,  1, new QTableWidgetItem("Магнитопровод статора, °C"));
    ui->tableWidget_5->setItem(9,  1, new QTableWidgetItem("Подшипниковый узел справа спереди, °C"));
    ui->tableWidget_5->setItem(10, 1, new QTableWidgetItem("Подшипниковый узел слева сзади, °C"));
    ui->tableWidget_5->setItem(11, 1, new QTableWidgetItem("Ротор сверху, °C"));
    ui->tableWidget_5->setItem(12, 1, new QTableWidgetItem("Ротор снизу, °C"));
    ui->tableWidget_5->setItem(13, 1, new QTableWidgetItem("Станина слева, °C"));
    ui->tableWidget_5->setItem(14, 1, new QTableWidgetItem("Станина справа, °C"));
    ui->tableWidget_5->setItem(15, 1, new QTableWidgetItem("Вал, °C"));
    ui->tableWidget_5->setItem(16, 1, new QTableWidgetItem("Клеммная коробка, °C"));

    QPalette p105=ui->tableWidget_5->palette();
    p105.setColor(QPalette::Base, QColor(225, 255, 255));
    p105.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget_5->setPalette(p105);

    ui->tableWidget_6->setRowCount(8);
    ui->tableWidget_6->setColumnCount(3);
    QStringList name_6;
    name_6 << " № " << "Сигнал" << "Величина";
    ui->tableWidget_6->setHorizontalHeaderLabels(name_6);
    ui->tableWidget_6->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_6->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_6->verticalHeader()->setVisible(false);
    ui->tableWidget_6->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_6->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_6->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_6->setColumnWidth(0, 100);
    ui->tableWidget_6->setColumnWidth(1, 400);

    for(int row = 0; row<ui->tableWidget_6->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_6->columnCount(); column++)
        {
            ui->tableWidget_6->setItem(row, column, new QTableWidgetItem());

        }
    }

    for (int i=0; i<8; i++)
    {
        if (ui->tableWidget_6->item(i, 0) != 0)
        {
            ui->tableWidget_6->item(i, 0)->setText(QString("%1").arg(i+1));
            ui->tableWidget_6->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->tableWidget_6->setItem(0, 1, new QTableWidgetItem("Ротор слева, °C"));
    ui->tableWidget_6->setItem(1, 1, new QTableWidgetItem("Ротор справа, °C"));
    ui->tableWidget_6->setItem(2, 1, new QTableWidgetItem("Станина слева, °C"));
    ui->tableWidget_6->setItem(3, 1, new QTableWidgetItem("Станина справа, °C"));
    ui->tableWidget_6->setItem(4, 1, new QTableWidgetItem("Вал, °C"));
    ui->tableWidget_6->setItem(5, 1, new QTableWidgetItem("Клеммная коробка, °C"));
    ui->tableWidget_6->setItem(6, 1, new QTableWidgetItem("Магнитопровод статора слева, °C"));
    ui->tableWidget_6->setItem(7, 1, new QTableWidgetItem("Магнитопровод статора справа, °C"));

    QPalette p106=ui->tableWidget_6->palette();
    p106.setColor(QPalette::Base, QColor(225, 255, 255));
    p106.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget_6->setPalette(p106);


    ui->tableWidget_13->setRowCount(20);
    ui->tableWidget_13->setColumnCount(4);
    QStringList name_7;
    name_7 << "Сигнал" << "Величина" << "Значение" << "Размерность";
    ui->tableWidget_13->setHorizontalHeaderLabels(name_7);
    ui->tableWidget_13->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_13->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_13->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_13->verticalHeader()->setVisible(true);
    ui->tableWidget_13->resizeColumnsToContents();

    for(int row = 0; row<ui->tableWidget_13->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_13->columnCount(); column++)
        {
            ui->tableWidget_13->setItem(row, column, new QTableWidgetItem());
        }
    }

    ui->tableWidget_13->setItem(0, 0, new QTableWidgetItem("Начальное давление вентилятора"));
    ui->tableWidget_13->setItem(1, 0, new QTableWidgetItem("Максимальный расход воздуха"));
    ui->tableWidget_13->setItem(2, 0, new QTableWidgetItem("Сопротивление входа в кожух через решетку с острыми кромками"));
    ui->tableWidget_13->setItem(3, 0, new QTableWidgetItem("Сопротивление поворота потока за входной решеткой перед входом в вентилятор"));
    ui->tableWidget_13->setItem(4, 0, new QTableWidgetItem("Сопротивление потока за входным вентилятором перед входом в межреберные каналы"));
    ui->tableWidget_13->setItem(5, 0, new QTableWidgetItem("Сопротивление косого входа в межреберные каналы"));
    ui->tableWidget_13->setItem(6, 0, new QTableWidgetItem("Сопротивление поворота потока в межреберных каналах под кожухом"));
    ui->tableWidget_13->setItem(7, 0, new QTableWidgetItem("Сопротивление выхода воздуха из межреберных каналов в воздушное пространство"));
    ui->tableWidget_13->setItem(8, 0, new QTableWidgetItem("Суммарное сопротивление вентиляционной сети"));
    ui->tableWidget_13->setItem(9, 0, new QTableWidgetItem("Рабочий расход воздуха"));
    ui->tableWidget_13->setItem(10, 0, new QTableWidgetItem("Рабочий набор вентилятора"));
    ui->tableWidget_13->setItem(11, 0, new QTableWidgetItem("Средняя скорость воздуха в межреберных каналах"));
    ui->tableWidget_13->setItem(12, 0, new QTableWidgetItem("Потребляемая вентилятором мощность"));

    ui->tableWidget_13->setItem(0, 1, new QTableWidgetItem("H0"));
    ui->tableWidget_13->setItem(1, 1, new QTableWidgetItem("Qmax"));
    ui->tableWidget_13->setItem(2, 1, new QTableWidgetItem("Z1"));
    ui->tableWidget_13->setItem(3, 1, new QTableWidgetItem("Z2"));
    ui->tableWidget_13->setItem(4, 1, new QTableWidgetItem("Z3"));
    ui->tableWidget_13->setItem(5, 1, new QTableWidgetItem("Z4"));
    ui->tableWidget_13->setItem(6, 1, new QTableWidgetItem("Z5"));
    ui->tableWidget_13->setItem(7, 1, new QTableWidgetItem("Z6"));
    ui->tableWidget_13->setItem(8, 1, new QTableWidgetItem("Z0"));
    ui->tableWidget_13->setItem(9, 1, new QTableWidgetItem("Qp"));
    ui->tableWidget_13->setItem(10, 1, new QTableWidgetItem("Hp"));
    ui->tableWidget_13->setItem(11, 1, new QTableWidgetItem("Vsr"));
    ui->tableWidget_13->setItem(12, 1, new QTableWidgetItem("Pvent"));

    ui->tableWidget_13->setItem(0, 3, new QTableWidgetItem("Па"));
    ui->tableWidget_13->setItem(1, 3, new QTableWidgetItem("м3/с"));
    ui->tableWidget_13->setItem(2, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_13->setItem(3, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_13->setItem(4, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_13->setItem(5, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_13->setItem(6, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_13->setItem(7, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_13->setItem(8, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_13->setItem(9, 3, new QTableWidgetItem("м3/с"));
    ui->tableWidget_13->setItem(10, 3, new QTableWidgetItem("Па"));
    ui->tableWidget_13->setItem(11, 3, new QTableWidgetItem("м/c"));
    ui->tableWidget_13->setItem(12, 3, new QTableWidgetItem("Вт"));

    for (int i=0; i<ui->tableWidget_13->rowCount(); i++)
    {
        if (ui->tableWidget_13->item(i, 1) != 0)
        {
            ui->tableWidget_13->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_13->item(i, 3) != 0)
        {
            ui->tableWidget_13->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }

    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
    {
        if (ui->tableWidget_13->item(row,0) != 0)
        {
            ui->tableWidget_13->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_13->item(row,1) != 0)
        {
            ui->tableWidget_13->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_13->item(row,2) != 0)
        {
            ui->tableWidget_13->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_13->item(row,3) != 0)
        {
            ui->tableWidget_13->item(row,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
    }


    QPalette p107=ui->tableWidget_13->palette();
    p107.setColor(QPalette::Base, QColor(225, 255, 255));
    p107.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget_13->setPalette(p106);

    CustomHelpDelegate* customHelpDelegate13 = new CustomHelpDelegate(this); //создание делегата для создания комбобоксов
    ui->tableWidget_13->setItemDelegateForColumn(0, customHelpDelegate13);

    ui->tableWidget_8->setRowCount(30);
    ui->tableWidget_8->setColumnCount(4);
    QStringList name_8;
    name_8 << "Величина" << "Обозначение" << "Значение" << "Размерность";
    ui->tableWidget_8->setHorizontalHeaderLabels(name_8);
    ui->tableWidget_8->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_8->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_8->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_8->verticalHeader()->setVisible(true);
    ui->tableWidget_8->resizeColumnsToContents();

    for(int row = 0; row<ui->tableWidget_8->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_8->columnCount(); column++)
        {
            ui->tableWidget_8->setItem(row, column, new QTableWidgetItem());
        }
    }

    ui->tableWidget_8->setItem(0, 0, new QTableWidgetItem("Статическое давление"));
    ui->tableWidget_8->setItem(1, 0, new QTableWidgetItem("Динамическое давление"));
    ui->tableWidget_8->setItem(2, 0, new QTableWidgetItem("Полное давление"));
    ui->tableWidget_8->setItem(3, 0, new QTableWidgetItem("Объемная производительность вентилятора"));
    ui->tableWidget_8->setItem(4, 0, new QTableWidgetItem("Мощность, потребляемая вентилятором"));
    ui->tableWidget_8->setItem(5, 0, new QTableWidgetItem("Полный КПД"));
    ui->tableWidget_8->setItem(6, 0, new QTableWidgetItem("Статический КПД"));
    ui->tableWidget_8->setItem(7, 0, new QTableWidgetItem("Момент двигателя"));
    ui->tableWidget_8->setItem(8, 0, new QTableWidgetItem("Частота вращения двигателя"));

    ui->tableWidget_8->setItem(0, 1, new QTableWidgetItem("P_ct"));
    ui->tableWidget_8->setItem(1, 1, new QTableWidgetItem("P_din"));
    ui->tableWidget_8->setItem(2, 1, new QTableWidgetItem("P_full"));
    ui->tableWidget_8->setItem(3, 1, new QTableWidgetItem("Q"));
    ui->tableWidget_8->setItem(4, 1, new QTableWidgetItem("N"));
    ui->tableWidget_8->setItem(5, 1, new QTableWidgetItem("Nu"));
    ui->tableWidget_8->setItem(6, 1, new QTableWidgetItem("Nu_ct"));
    ui->tableWidget_8->setItem(7, 1, new QTableWidgetItem("M"));
    ui->tableWidget_8->setItem(8, 1, new QTableWidgetItem("omega"));

    ui->tableWidget_8->setItem(0, 3, new QTableWidgetItem("Па"));
    ui->tableWidget_8->setItem(1, 3, new QTableWidgetItem("Па"));
    ui->tableWidget_8->setItem(2, 3, new QTableWidgetItem("Па"));
    ui->tableWidget_8->setItem(3, 3, new QTableWidgetItem("м3/с"));
    ui->tableWidget_8->setItem(4, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_8->setItem(5, 3, new QTableWidgetItem("--"));
    ui->tableWidget_8->setItem(6, 3, new QTableWidgetItem("--"));
    ui->tableWidget_8->setItem(7, 3, new QTableWidgetItem("Н*м"));
    ui->tableWidget_8->setItem(8, 3, new QTableWidgetItem("рад/с"));

    for (int i=0; i<ui->tableWidget_8->rowCount(); i++)
    {
        if (ui->tableWidget_8->item(i, 1) != 0)
        {
            ui->tableWidget_8->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_8->item(i, 2) != 0)
        {
            ui->tableWidget_8->item(i, 2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_8->item(i, 3) != 0)
        {
            ui->tableWidget_8->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }

    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget_8->rowCount(); row++)
    {
        if (ui->tableWidget_8->item(row,0) != 0)
        {
            ui->tableWidget_8->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_8->item(row,1) != 0)
        {
            ui->tableWidget_8->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_8->item(row,2) != 0)
        {
            ui->tableWidget_8->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget_8->item(row,2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_8->item(row,3) != 0)
        {
            ui->tableWidget_8->item(row,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
    }

    QPalette p108=ui->tableWidget_8->palette();
    p108.setColor(QPalette::Base, QColor(225, 255, 255));
    p108.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget_8->setPalette(p108);

    CustomHelpDelegate* customHelpDelegate8 = new CustomHelpDelegate(this); //создание делегата для создания комбобоксов
    ui->tableWidget_8->setItemDelegateForColumn(0, customHelpDelegate8);

    dataLineColors.append(Qt::red);
    dataLineColors.append(Qt::green);
    dataLineColors.append(Qt::cyan);
    dataLineColors.append(Qt::yellow);
    dataLineColors.append(Qt::red);
    dataLineColors.append(Qt::green);
    dataLineColors.append(Qt::cyan);
    dataLineColors.append(Qt::yellow);
    dataLineColors.append(Qt::red);
    dataLineColors.append(Qt::red);
    dataLineColors.append(Qt::green);
    dataLineColors.append(Qt::cyan);
    dataLineColors.append(Qt::yellow);
    dataLineColors.append(Qt::yellow);
    dataLineColors.append(Qt::red);
    dataLineColors.append(Qt::green);
    dataLineColors.append(Qt::cyan);
    dataLineColors.append(Qt::yellow);
    dataLineColors.append(Qt::red);
    dataLineColors.append(Qt::green);
    dataLineColors.append(Qt::cyan);
    dataLineColors.append(Qt::yellow);
    dataLineColors.append(Qt::yellow);
    dataLineColors.append(Qt::red);
    dataLineColors.append(Qt::green);
    dataLineColors.append(Qt::cyan);
    dataLineColors.append(Qt::yellow);
    dataLineColors.append(Qt::red);
    dataLineColors.append(Qt::green);
    dataLineColors.append(Qt::yellow);

    for (int i = 0; i < dataLineColors.size(); i++)
    {
        ui->tableWidget->item(i, 1)->setBackground(dataLineColors[i]);
    }

    connect(ui->tableWidget, &QTableWidget::cellClicked,this, &MainWindow::setcolorincell);

    //Вывод расчетных данных по теплу в таблицу
    ui->widget_5->ui->tableWidget->setRowCount(76);
    ui->widget_5->ui->tableWidget->setColumnCount(12);
    QStringList name_12;
    name_12 << "Температура" << "Значение" << "Теплоемкость" << "Значение"
            << "Мощность рассеяния" << "Значение"<< "Теплопроводность" << "Значение"
            << "Мощность рассеяния" << "Значение"<< "Падение температуры" << "Значение";
    ui->widget_5->ui->tableWidget->setHorizontalHeaderLabels(name_12);
    ui->widget_5->ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->widget_5->ui->tableWidget->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->widget_5->ui->tableWidget->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->widget_5->ui->tableWidget->verticalHeader()->setVisible(true);
    ui->widget_5->ui->tableWidget->resizeColumnsToContents();
    ui->widget_5->ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(int row = 0; row<ui->widget_5->ui->tableWidget->rowCount(); row++)
    {
        for(int column = 0; column<ui->widget_5->ui->tableWidget->columnCount(); column++)
        {
            ui->widget_5->ui->tableWidget->setItem(row, column, new QTableWidgetItem());
        }
    }

    for(int row = 0; row<ui->widget_5->ui->tableWidget->rowCount(); row++)
    {
        if (ui->widget_5->ui->tableWidget->item(row,1) != 0)
        {
            ui->widget_5->ui->tableWidget->item(row,1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->widget_5->ui->tableWidget->item(row,3) != 0)
        {
            ui->widget_5->ui->tableWidget->item(row,3)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->widget_5->ui->tableWidget->item(row,5) != 0)
        {
            ui->widget_5->ui->tableWidget->item(row,5)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->widget_5->ui->tableWidget->item(row,7) != 0)
        {
            ui->widget_5->ui->tableWidget->item(row,7)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->widget_5->ui->tableWidget->item(row,9) != 0)
        {
            ui->widget_5->ui->tableWidget->item(row,9)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->widget_5->ui->tableWidget->item(row,11) != 0)
        {
            ui->widget_5->ui->tableWidget->item(row,11)->setTextAlignment(Qt::AlignCenter);
        }
    }

    QPalette p=ui->widget_5->ui->tableWidget->palette();
    p.setColor(QPalette::Base, QColor(255, 255, 191));
    p.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->widget_5->ui->tableWidget->setPalette(p);

    CustomHelpDelegate* customHelpDelegate = new CustomHelpDelegate(this); //создание делегата для создания комбобоксов
    ui->widget_5->ui->tableWidget->setItemDelegateForColumn(0, customHelpDelegate);
    ui->widget_5->ui->tableWidget->setItemDelegateForColumn(2, customHelpDelegate);
    ui->widget_5->ui->tableWidget->setItemDelegateForColumn(4, customHelpDelegate);
    ui->widget_5->ui->tableWidget->setItemDelegateForColumn(6, customHelpDelegate);
    ui->widget_5->ui->tableWidget->setItemDelegateForColumn(8, customHelpDelegate);
    ui->widget_5->ui->tableWidget->setItemDelegateForColumn(10, customHelpDelegate);
    ui->tableWidget_2->setItemDelegateForColumn(0, customHelpDelegate);
    ui->tableWidget_4->setItemDelegateForColumn(0, customHelpDelegate);
    ui->tableWidget_7->setItemDelegateForColumn(0, customHelpDelegate);
    ui->tableWidget_10->setItemDelegateForColumn(0, customHelpDelegate);
    ui->tableWidget_11->setItemDelegateForColumn(0, customHelpDelegate);
    ui->tableWidget_12->setItemDelegateForColumn(0, customHelpDelegate);

    ui->lineEdit_8->setReadOnly(true);
    ui->lineEdit_9->setReadOnly(true);
    ui->lineEdit_10->setReadOnly(true);
    ui->lineEdit_11->setReadOnly(true);
    ui->lineEdit_12->setReadOnly(true);

    ui->lineEdit_8->setAlignment(Qt::AlignCenter);
    ui->lineEdit_9->setAlignment(Qt::AlignCenter);
    ui->lineEdit_10->setAlignment(Qt::AlignCenter);
    ui->lineEdit_11->setAlignment(Qt::AlignCenter);
    ui->lineEdit_12->setAlignment(Qt::AlignCenter);
    ui->lineEdit_13->setAlignment(Qt::AlignCenter);
    ui->lineEdit_14->setAlignment(Qt::AlignCenter);
    ui->lineEdit_15->setAlignment(Qt::AlignCenter);
    ui->lineEdit_16->setAlignment(Qt::AlignCenter);
    ui->lineEdit_17->setAlignment(Qt::AlignCenter);
    ui->lineEdit_18->setAlignment(Qt::AlignCenter);


    ui->tableWidget_9->setRowCount(40);
    ui->tableWidget_9->setColumnCount(3);
    QStringList name_9;
    name_9 << " № " << "Сигнал" << "Величина";
    ui->tableWidget_9->setHorizontalHeaderLabels(name_9);
    ui->tableWidget_9->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_9->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_9->verticalHeader()->setVisible(false);
    ui->tableWidget_9->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_9->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_9->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_9->setColumnWidth(0, 100);
    ui->tableWidget_9->setColumnWidth(1, 400);

    for(int row = 0; row<ui->tableWidget_9->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_9->columnCount(); column++)
        {
            ui->tableWidget_9->setItem(row, column, new QTableWidgetItem());

        }
    }

    for (int i=0; i<ui->tableWidget_9->rowCount(); i++)
    {
        if (ui->tableWidget_9->item(i, 0) != 0)
        {
            ui->tableWidget_9->item(i, 0)->setText(QString("%1").arg(i+1));
            ui->tableWidget_9->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->tableWidget_9->setItem(0, 1, new QTableWidgetItem("Lambda_ct"));
    ui->tableWidget_9->setItem(1, 1, new QTableWidgetItem("Lambda_adelta1"));
    ui->tableWidget_9->setItem(2, 1, new QTableWidgetItem("Lambda_a1"));
    ui->tableWidget_9->setItem(3, 1, new QTableWidgetItem("Lambda_delta1"));
    ui->tableWidget_9->setItem(4, 1, new QTableWidgetItem("Lambda_sigma"));
    ui->tableWidget_9->setItem(5, 1, new QTableWidgetItem("Lambda_1z1"));
    ui->tableWidget_9->setItem(6, 1, new QTableWidgetItem("Lambda_12"));
    ui->tableWidget_9->setItem(7, 1, new QTableWidgetItem("Lambda_1ip1"));
    ui->tableWidget_9->setItem(8, 1, new QTableWidgetItem("delta"));
    ui->tableWidget_9->setItem(9, 1, new QTableWidgetItem("Lambda_ekv"));
    ui->tableWidget_9->setItem(10, 1, new QTableWidgetItem("Lambda_epz"));
    ui->tableWidget_9->setItem(11, 1, new QTableWidgetItem("Lambda_i1z"));
    ui->tableWidget_9->setItem(12, 1, new QTableWidgetItem("Lambda_z"));
    ui->tableWidget_9->setItem(13, 1, new QTableWidgetItem("Lambda_nz"));
    ui->tableWidget_9->setItem(14, 1, new QTableWidgetItem("Lambda_i1a"));
    ui->tableWidget_9->setItem(15, 1, new QTableWidgetItem("Lambda_ekpa"));
    ui->tableWidget_9->setItem(16, 1, new QTableWidgetItem("Lambda_2ip1"));
    ui->tableWidget_9->setItem(17, 1, new QTableWidgetItem("Lambda_a"));
    ui->tableWidget_9->setItem(18, 1, new QTableWidgetItem("Lambda_na"));
    ui->tableWidget_9->setItem(19, 1, new QTableWidgetItem("Lambda_za"));
    ui->tableWidget_9->setItem(20, 1, new QTableWidgetItem("Lambda_pl"));
    ui->tableWidget_9->setItem(21, 1, new QTableWidgetItem("Lambda_il"));
    ui->tableWidget_9->setItem(22, 1, new QTableWidgetItem("Lambda_el"));
    ui->tableWidget_9->setItem(23, 1, new QTableWidgetItem("Lambda_al1"));
    ui->tableWidget_9->setItem(24, 1, new QTableWidgetItem("Lambda_l1"));
    ui->tableWidget_9->setItem(25, 1, new QTableWidgetItem("Lambda_lp2"));
    ui->tableWidget_9->setItem(26, 1, new QTableWidgetItem("Lambda_a2"));
    ui->tableWidget_9->setItem(27, 1, new QTableWidgetItem("Lambda_l2"));
    ui->tableWidget_9->setItem(28, 1, new QTableWidgetItem("Lambda_asch"));
    ui->tableWidget_9->setItem(29, 1, new QTableWidgetItem("Lambda_ast"));
    ui->tableWidget_9->setItem(30, 1, new QTableWidgetItem("Lambda_ai"));
    ui->tableWidget_9->setItem(31, 1, new QTableWidgetItem("alpha_stsumm"));
    ui->tableWidget_9->setItem(32, 1, new QTableWidgetItem("Lambda_ct1"));
    ui->tableWidget_9->setItem(33, 1, new QTableWidgetItem("Lambda_asch"));
    ui->tableWidget_9->setItem(34, 1, new QTableWidgetItem("Lambda_p"));

    QPalette p9=ui->tableWidget_9->palette();
    p9.setColor(QPalette::Base, QColor(225, 255, 255));
    p9.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget_9->setPalette(p9);

    ui->tableWidget_10->setRowCount(10);
    ui->tableWidget_10->setColumnCount(4);
    QStringList name_10;
    name_10 << "Величина" << "Обозначение" << "Значение" << "Размерность";
    ui->tableWidget_10->setHorizontalHeaderLabels(name_10);
    ui->tableWidget_10->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_10->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_10->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_10->verticalHeader()->setVisible(true);
    ui->tableWidget_10->resizeColumnsToContents();

    for(int row = 0; row<ui->tableWidget_10->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_10->columnCount(); column++)
        {
            ui->tableWidget_10->setItem(row, column, new QTableWidgetItem());

        }
    }

    ui->tableWidget_10->setItem(0, 0, new QTableWidgetItem("Внутренний расчетный диаметр вентилятора"));
    ui->tableWidget_10->setItem(1, 0, new QTableWidgetItem("Внешний расчетный диаметр вентилятора"));
    ui->tableWidget_10->setItem(2, 0, new QTableWidgetItem("Ширина лопатки вентилятора"));
    ui->tableWidget_10->setItem(3, 0, new QTableWidgetItem("Частота вращения вентилятора"));
    ui->tableWidget_10->setItem(4, 0, new QTableWidgetItem("Плотность воздуха"));
    ui->tableWidget_10->setItem(5, 0, new QTableWidgetItem("Суммарная площадь отверстий в сетке кожуха"));
    ui->tableWidget_10->setItem(6, 0, new QTableWidgetItem("Общая площадь сетки кожуха"));
    ui->tableWidget_10->setItem(7, 0, new QTableWidgetItem("Площадь сечения в месте поворота к рабочему колесу"));
    ui->tableWidget_10->setItem(8, 0, new QTableWidgetItem("Угол поворота потока к входным кромкам лопаток рабочего колеса"));
    ui->tableWidget_10->setItem(9, 0, new QTableWidgetItem("Площадь сечения в месте поворота перед входом в межреберные каналы"));
    ui->tableWidget_10->setItem(10, 0, new QTableWidgetItem("Угол поворота потока перед входом в межреберные каналы"));
    ui->tableWidget_10->setItem(11, 0, new QTableWidgetItem("Площадь сечения перед входом в межреберные каналы"));
    ui->tableWidget_10->setItem(12, 0, new QTableWidgetItem("Площадь сечения межреберных каналов от станины до кожуха вентилятора"));
    ui->tableWidget_10->setItem(13, 0, new QTableWidgetItem("Угол натекания потока на ребра станины"));
    ui->tableWidget_10->setItem(14, 0, new QTableWidgetItem("Угол поворота потока в межреберных каналах"));

    ui->tableWidget_10->setItem(0, 1, new QTableWidgetItem("D1р"));
    ui->tableWidget_10->setItem(1, 1, new QTableWidgetItem("D2р"));
    ui->tableWidget_10->setItem(2, 1, new QTableWidgetItem("b"));
    ui->tableWidget_10->setItem(3, 1, new QTableWidgetItem("n"));
    ui->tableWidget_10->setItem(4, 1, new QTableWidgetItem("ro"));
    ui->tableWidget_10->setItem(5, 1, new QTableWidgetItem("Sotv"));
    ui->tableWidget_10->setItem(6, 1, new QTableWidgetItem("S0"));
    ui->tableWidget_10->setItem(7, 1, new QTableWidgetItem("S1"));
    ui->tableWidget_10->setItem(8, 1, new QTableWidgetItem("alpha1"));
    ui->tableWidget_10->setItem(9, 1, new QTableWidgetItem("S2"));
    ui->tableWidget_10->setItem(10, 1, new QTableWidgetItem("alpha2"));
    ui->tableWidget_10->setItem(11, 1, new QTableWidgetItem("S3"));
    ui->tableWidget_10->setItem(12, 1, new QTableWidgetItem("S4"));
    ui->tableWidget_10->setItem(13, 1, new QTableWidgetItem("fi"));
    ui->tableWidget_10->setItem(14, 1, new QTableWidgetItem("fi2"));

    ui->tableWidget_10->setItem(0, 3, new QTableWidgetItem("м"));
    ui->tableWidget_10->setItem(1, 3, new QTableWidgetItem("м"));
    ui->tableWidget_10->setItem(2, 3, new QTableWidgetItem("м"));
    ui->tableWidget_10->setItem(3, 3, new QTableWidgetItem("об/мин"));
    ui->tableWidget_10->setItem(4, 3, new QTableWidgetItem("кг/м3"));
    ui->tableWidget_10->setItem(5, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_10->setItem(6, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_10->setItem(7, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_10->setItem(8, 3, new QTableWidgetItem("град."));
    ui->tableWidget_10->setItem(9, 3, new QTableWidgetItem("град."));
    ui->tableWidget_10->setItem(10, 3, new QTableWidgetItem("alpha2"));
    ui->tableWidget_10->setItem(11, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_10->setItem(12, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_10->setItem(13, 3, new QTableWidgetItem("град."));
    ui->tableWidget_10->setItem(14, 3, new QTableWidgetItem("град."));

    for (int i=0; i<ui->tableWidget_10->rowCount(); i++)
    {

        if (ui->tableWidget_10->item(i, 1) != 0)
        {
            ui->tableWidget_10->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_10->item(i, 3) != 0)
        {
            ui->tableWidget_10->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }

    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget_10->rowCount(); row++)
    {
        if (ui->tableWidget_10->item(row,0) != 0)
        {
            ui->tableWidget_10->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_10->item(row,1) != 0)
        {
            ui->tableWidget_10->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_10->item(row,2) != 0)
        {
            ui->tableWidget_10->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget_10->item(row,2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_10->item(row,3) != 0)
        {
            ui->tableWidget_10->item(row,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
    }

    QPalette p_10=ui->tableWidget_10->palette();
    p_10.setColor(QPalette::Base, QColor(255, 255, 191));
    p_10.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget_10->setPalette(p_10);

    ui->tableWidget_11->setRowCount(10);
    ui->tableWidget_11->setColumnCount(4);
    QStringList name_11;
    name_11 << "Величина" << "Обозначение" << "Значение" << "Размерность";
    ui->tableWidget_11->setHorizontalHeaderLabels(name_11);
    ui->tableWidget_11->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_11->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_11->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_11->verticalHeader()->setVisible(true);
    ui->tableWidget_11->resizeColumnsToContents();

    for(int row = 0; row<ui->tableWidget_11->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_11->columnCount(); column++)
        {
            ui->tableWidget_11->setItem(row, column, new QTableWidgetItem());

        }
    }

    ui->tableWidget_11->setItem(0, 0, new QTableWidgetItem("Потери на местных сопротивлениях и на трение"));
    ui->tableWidget_11->setItem(1, 0, new QTableWidgetItem("Потери на входе в рабочее колесо"));
    ui->tableWidget_11->setItem(2, 0, new QTableWidgetItem("Потери на вихреобразование пр протекании по тока по лопаткам колеса"));
    ui->tableWidget_11->setItem(3, 0, new QTableWidgetItem("Потери на создание и перемещение неупорядоченных потоков в вентиляторе"));
    ui->tableWidget_11->setItem(4, 0, new QTableWidgetItem("Потери при преобразовании кинетической энергии на выходе колеса в статическое давление"));
    ui->tableWidget_11->setItem(5, 0, new QTableWidgetItem("Мощность, потребляемая вентилятором"));
    ui->tableWidget_11->setItem(6, 0, new QTableWidgetItem("Полезная мощность вентилятора"));

    ui->tableWidget_11->setItem(0, 1, new QTableWidgetItem("ΔPптк"));
    ui->tableWidget_11->setItem(1, 1, new QTableWidgetItem("ΔPврк"));
    ui->tableWidget_11->setItem(2, 1, new QTableWidgetItem("ΔPвк"));
    ui->tableWidget_11->setItem(3, 1, new QTableWidgetItem("ΔPсвп"));
    ui->tableWidget_11->setItem(4, 1, new QTableWidgetItem("ΔPкд"));
    ui->tableWidget_11->setItem(5, 1, new QTableWidgetItem("Nsv"));
    ui->tableWidget_11->setItem(6, 1, new QTableWidgetItem("N"));

    ui->tableWidget_11->setItem(0, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_11->setItem(1, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_11->setItem(2, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_11->setItem(3, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_11->setItem(4, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_11->setItem(5, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_11->setItem(6, 3, new QTableWidgetItem("Вт"));

    for (int i=0; i<ui->tableWidget_11->rowCount(); i++)
    {

        if (ui->tableWidget_11->item(i, 1) != 0)
        {
            ui->tableWidget_11->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_11->item(i, 3) != 0)
        {
            ui->tableWidget_11->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }

    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget_11->rowCount(); row++)
    {
        if (ui->tableWidget_11->item(row,0) != 0)
        {
            ui->tableWidget_11->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_11->item(row,1) != 0)
        {
            ui->tableWidget_11->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_11->item(row,2) != 0)
        {
            ui->tableWidget_11->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget_11->item(row,2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_11->item(row,3) != 0)
        {
            ui->tableWidget_11->item(row,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
    }

    QPalette p11=ui->tableWidget_11->palette();
    p11.setColor(QPalette::Base, QColor(225, 255, 255));
    p11.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget_11->setPalette(p11);



    ui->tableWidget_12->setRowCount(10);
    ui->tableWidget_12->setColumnCount(4);
    QStringList name_121;
    name_121 << "Величина" << "Обозначение" << "Значение" << "Размерность";
    ui->tableWidget_12->setHorizontalHeaderLabels(name_121);
    ui->tableWidget_12->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_12->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_12->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_12->verticalHeader()->setVisible(true);
    ui->tableWidget_12->resizeColumnsToContents();

    for(int row = 0; row<ui->tableWidget_12->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_12->columnCount(); column++)
        {
            ui->tableWidget_12->setItem(row, column, new QTableWidgetItem());

        }
    }

    ui->tableWidget_12->setItem(0, 0, new QTableWidgetItem("Производительность"));
    ui->tableWidget_12->setItem(1, 0, new QTableWidgetItem("Полное давление вентилятора"));
    ui->tableWidget_12->setItem(2, 0, new QTableWidgetItem("Динамическое давление вентилятора"));
    ui->tableWidget_12->setItem(3, 0, new QTableWidgetItem("Статическое давление вентилятора"));
    ui->tableWidget_12->setItem(4, 0, new QTableWidgetItem("Полезная мощность вентилятора"));
    ui->tableWidget_12->setItem(5, 0, new QTableWidgetItem("Потребляемая мощность вентилятора"));
    ui->tableWidget_12->setItem(6, 0, new QTableWidgetItem("Полный к.п.д. вентилятора"));

    ui->tableWidget_12->setItem(0, 1, new QTableWidgetItem("Q"));
    ui->tableWidget_12->setItem(1, 1, new QTableWidgetItem("Pv"));
    ui->tableWidget_12->setItem(2, 1, new QTableWidgetItem("Pdv"));
    ui->tableWidget_12->setItem(3, 1, new QTableWidgetItem("Psv"));
    ui->tableWidget_12->setItem(4, 1, new QTableWidgetItem("Nsv"));
    ui->tableWidget_12->setItem(5, 1, new QTableWidgetItem("N"));
    ui->tableWidget_12->setItem(6, 1, new QTableWidgetItem("nu"));

    ui->tableWidget_12->setItem(0, 3, new QTableWidgetItem("м3/с"));
    ui->tableWidget_12->setItem(1, 3, new QTableWidgetItem("Па"));
    ui->tableWidget_12->setItem(2, 3, new QTableWidgetItem("Па"));
    ui->tableWidget_12->setItem(3, 3, new QTableWidgetItem("Па"));
    ui->tableWidget_12->setItem(4, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_12->setItem(5, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_12->setItem(6, 3, new QTableWidgetItem("-"));

    for (int i=0; i<ui->tableWidget_12->rowCount(); i++)
    {

        if (ui->tableWidget_12->item(i, 1) != 0)
        {
            ui->tableWidget_12->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_12->item(i, 3) != 0)
        {
            ui->tableWidget_12->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }

    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget_12->rowCount(); row++)
    {
        if (ui->tableWidget_12->item(row,0) != 0)
        {
            ui->tableWidget_12->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_12->item(row,1) != 0)
        {
            ui->tableWidget_12->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_12->item(row,2) != 0)
        {
            ui->tableWidget_12->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget_11->item(row,2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_12->item(row,3) != 0)
        {
            ui->tableWidget_12->item(row,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
    }

    QPalette p12=ui->tableWidget_12->palette();
    p12.setColor(QPalette::Base, QColor(225, 255, 255));
    p12.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget_12->setPalette(p12);


    ui->tableWidget_7->setRowCount(30);
    ui->tableWidget_7->setColumnCount(4);
    QStringList name_77;
    name_77 << "Величина" << "Обозначение" << "Значение" << "Размерность";
    ui->tableWidget_7->setHorizontalHeaderLabels(name_77);
    ui->tableWidget_7->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_7->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_7->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_7->verticalHeader()->setVisible(true);
    ui->tableWidget_7->resizeColumnsToContents();

    for(int row = 0; row<ui->tableWidget_7->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_7->columnCount(); column++)
        {
            ui->tableWidget_7->setItem(row, column, new QTableWidgetItem());

        }
    }

    ui->tableWidget_7->setItem(0, 0, new QTableWidgetItem("Внутренний расчетный диаметр вентилятора"));
    ui->tableWidget_7->setItem(1, 0, new QTableWidgetItem("Внешний расчетный диаметр вентилятора"));
    ui->tableWidget_7->setItem(2, 0, new QTableWidgetItem("Ширина лопатки вентилятора"));
    ui->tableWidget_7->setItem(3, 0, new QTableWidgetItem("Частота вращения вентилятора"));
    ui->tableWidget_7->setItem(4, 0, new QTableWidgetItem("Плотность воздуха"));
    ui->tableWidget_7->setItem(5, 0, new QTableWidgetItem("Суммарная площадь отверстий в сетке кожуха"));
    ui->tableWidget_7->setItem(6, 0, new QTableWidgetItem("Общая площадь сетки кожуха"));
    ui->tableWidget_7->setItem(7, 0, new QTableWidgetItem("Площадь сечения в месте поворота к рабочему колесу"));
    ui->tableWidget_7->setItem(8, 0, new QTableWidgetItem("Угол поворота потока к входным кромкам лопаток рабочего колеса"));
    ui->tableWidget_7->setItem(9, 0, new QTableWidgetItem("Площадь сечения в месте поворота перед входом в межреберные каналы"));
    ui->tableWidget_7->setItem(10, 0, new QTableWidgetItem("Угол поворота потока перед входом в межреберные каналы"));
    ui->tableWidget_7->setItem(11, 0, new QTableWidgetItem("Площадь сечения перед входом в межреберные каналы"));
    ui->tableWidget_7->setItem(12, 0, new QTableWidgetItem("Площадь сечения межреберных каналов от станины до кожуха вентилятора"));
    ui->tableWidget_7->setItem(13, 0, new QTableWidgetItem("Угол натекания потока на ребра станины"));
    ui->tableWidget_7->setItem(14, 0, new QTableWidgetItem("Угол поворота потока в межреберных каналах"));

    ui->tableWidget_7->setItem(0, 1, new QTableWidgetItem("D1р"));
    ui->tableWidget_7->setItem(1, 1, new QTableWidgetItem("D2р"));
    ui->tableWidget_7->setItem(2, 1, new QTableWidgetItem("b"));
    ui->tableWidget_7->setItem(3, 1, new QTableWidgetItem("n"));
    ui->tableWidget_7->setItem(4, 1, new QTableWidgetItem("ro"));
    ui->tableWidget_7->setItem(5, 1, new QTableWidgetItem("Sotv"));
    ui->tableWidget_7->setItem(6, 1, new QTableWidgetItem("S0"));
    ui->tableWidget_7->setItem(7, 1, new QTableWidgetItem("S1"));
    ui->tableWidget_7->setItem(8, 1, new QTableWidgetItem("α1"));
    ui->tableWidget_7->setItem(9, 1, new QTableWidgetItem("S2"));
    ui->tableWidget_7->setItem(10, 1, new QTableWidgetItem("α2"));
    ui->tableWidget_7->setItem(11, 1, new QTableWidgetItem("S3"));
    ui->tableWidget_7->setItem(12, 1, new QTableWidgetItem("S4"));
    ui->tableWidget_7->setItem(13, 1, new QTableWidgetItem("φ"));
    ui->tableWidget_7->setItem(14, 1, new QTableWidgetItem("φ2"));

    ui->tableWidget_7->setItem(0, 3, new QTableWidgetItem("м"));
    ui->tableWidget_7->setItem(1, 3, new QTableWidgetItem("м"));
    ui->tableWidget_7->setItem(2, 3, new QTableWidgetItem("м"));
    ui->tableWidget_7->setItem(3, 3, new QTableWidgetItem("об/мин"));
    ui->tableWidget_7->setItem(4, 3, new QTableWidgetItem("кг/м3"));
    ui->tableWidget_7->setItem(5, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_7->setItem(6, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_7->setItem(7, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_7->setItem(8, 3, new QTableWidgetItem("град."));
    ui->tableWidget_7->setItem(9, 3, new QTableWidgetItem("град."));
    ui->tableWidget_7->setItem(10, 3, new QTableWidgetItem("alpha2"));
    ui->tableWidget_7->setItem(11, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_7->setItem(12, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_7->setItem(13, 3, new QTableWidgetItem("град."));
    ui->tableWidget_7->setItem(14, 3, new QTableWidgetItem("град."));

    for (int i=0; i<ui->tableWidget_7->rowCount(); i++)
    {

        if (ui->tableWidget_7->item(i, 1) != 0)
        {
            ui->tableWidget_7->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_7->item(i, 3) != 0)
        {
            ui->tableWidget_7->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }

    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget_7->rowCount(); row++)
    {
        if (ui->tableWidget_7->item(row,0) != 0)
        {
            ui->tableWidget_7->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_7->item(row,1) != 0)
        {
            ui->tableWidget_7->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_7->item(row,2) != 0)
        {
            ui->tableWidget_7->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget_7->item(row,2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_7->item(row,3) != 0)
        {
            ui->tableWidget_7->item(row,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
    }

    QPalette p_13=ui->tableWidget_7->palette();
    p_13.setColor(QPalette::Base, QColor(255, 255, 191));
    p_13.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget_7->setPalette(p_13);

    CustomHelpDelegate* customHelpDelegate2 = new CustomHelpDelegate(this); //создание делегата для создания комбобоксов
    ui->tableWidget_7->setItemDelegateForColumn(0, customHelpDelegate2);



    ui->tableWidget_14->setRowCount(30);
    ui->tableWidget_14->setColumnCount(4);
    QStringList name_14;
    name_14 << "Величина" << "Обозначение" << "Значение" << "Размерность";
    ui->tableWidget_14->setHorizontalHeaderLabels(name_14);
    ui->tableWidget_14->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_14->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_14->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_14->verticalHeader()->setVisible(true);
    ui->tableWidget_14->resizeColumnsToContents();

    for(int row = 0; row<ui->tableWidget_14->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_14->columnCount(); column++)
        {
            ui->tableWidget_14->setItem(row, column, new QTableWidgetItem());

        }
    }
    for (int i=0; i<ui->tableWidget_14->rowCount(); i++)
    {

        if (ui->tableWidget_14->item(i, 1) != 0)
        {
            ui->tableWidget_14->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_14->item(i, 3) != 0)
        {
            ui->tableWidget_14->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }

    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget_14->rowCount(); row++)
    {
        if (ui->tableWidget_14->item(row,0) != 0)
        {
            ui->tableWidget_14->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_14->item(row,1) != 0)
        {
            ui->tableWidget_14->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_14->item(row,2) != 0)
        {
            ui->tableWidget_14->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget_14->item(row,2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_14->item(row,3) != 0)
        {
            ui->tableWidget_14->item(row,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
    }

    QPalette p_14=ui->tableWidget_14->palette();
    p_14.setColor(QPalette::Base, QColor(255, 255, 191));
    p_14.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget_14->setPalette(p_14);

    CustomHelpDelegate* customHelpDelegate4 = new CustomHelpDelegate(this); //создание делегата для создания комбобоксов
    ui->tableWidget_14->setItemDelegateForColumn(0, customHelpDelegate4);

    ui->tableWidget_15->setRowCount(30);
    ui->tableWidget_15->setColumnCount(4);
    QStringList name_15;
    name_15 << "Величина" << "Обозначение" << "Значение" << "Размерность";
    ui->tableWidget_15->setHorizontalHeaderLabels(name_15);
    ui->tableWidget_15->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_15->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_15->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_15->verticalHeader()->setVisible(true);
    ui->tableWidget_15->resizeColumnsToContents();

    for(int row = 0; row<ui->tableWidget_15->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_15->columnCount(); column++)
        {
            ui->tableWidget_15->setItem(row, column, new QTableWidgetItem());

        }
    }

    ui->tableWidget_15->setItem(0, 0, new QTableWidgetItem("Внутренний расчетный диаметр вентилятора"));
    ui->tableWidget_15->setItem(1, 0, new QTableWidgetItem("Внешний расчетный диаметр вентилятора"));
    ui->tableWidget_15->setItem(2, 0, new QTableWidgetItem("Ширина лопатки вентилятора"));
    ui->tableWidget_15->setItem(3, 0, new QTableWidgetItem("Частота вращения вентилятора"));
    ui->tableWidget_15->setItem(4, 0, new QTableWidgetItem("Плотность воздуха"));
    ui->tableWidget_15->setItem(5, 0, new QTableWidgetItem("Суммарная площадь отверстий в сетке кожуха"));
    ui->tableWidget_15->setItem(6, 0, new QTableWidgetItem("Общая площадь сетки кожуха"));
    ui->tableWidget_15->setItem(7, 0, new QTableWidgetItem("Площадь сечения в месте поворота к рабочему колесу"));
    ui->tableWidget_15->setItem(8, 0, new QTableWidgetItem("Угол поворота потока к входным кромкам лопаток рабочего колеса"));
    ui->tableWidget_15->setItem(9, 0, new QTableWidgetItem("Площадь сечения в месте поворота перед входом в межреберные каналы"));
    ui->tableWidget_15->setItem(10, 0, new QTableWidgetItem("Угол поворота потока перед входом в межреберные каналы"));
    ui->tableWidget_15->setItem(11, 0, new QTableWidgetItem("Площадь сечения перед входом в межреберные каналы"));
    ui->tableWidget_15->setItem(12, 0, new QTableWidgetItem("Площадь сечения межреберных каналов от станины до кожуха вентилятора"));
    ui->tableWidget_15->setItem(13, 0, new QTableWidgetItem("Угол натекания потока на ребра станины"));
    ui->tableWidget_15->setItem(14, 0, new QTableWidgetItem("Угол поворота потока в межреберных каналах"));

    for (int i=0; i<ui->tableWidget_15->rowCount(); i++)
    {

        if (ui->tableWidget_15->item(i, 1) != 0)
        {
            ui->tableWidget_15->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_15->item(i, 3) != 0)
        {
            ui->tableWidget_15->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }


    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget_15->rowCount(); row++)
    {
        if (ui->tableWidget_15->item(row,0) != 0)
        {
            ui->tableWidget_15->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_15->item(row,1) != 0)
        {
            ui->tableWidget_15->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_15->item(row,2) != 0)
        {
            ui->tableWidget_15->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget_15->item(row,2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_15->item(row,3) != 0)
        {
            ui->tableWidget_15->item(row,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
    }

    QPalette p_15=ui->tableWidget_15->palette();
    p_15.setColor(QPalette::Base, QColor(255, 255, 191));
    p_15.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget_15->setPalette(p_15);

    CustomHelpDelegate* customHelpDelegate15 = new CustomHelpDelegate(this); //создание делегата для создания комбобоксов
    ui->tableWidget_15->setItemDelegateForColumn(0, customHelpDelegate15);

    ui->tableWidget_16->setRowCount(30);
    ui->tableWidget_16->setColumnCount(4);
    QStringList name_16;
    name_16 << "Величина" << "Обозначение" << "Значение" << "Размерность";

    ui->tableWidget_16->setHorizontalHeaderLabels(name_16);
    ui->tableWidget_16->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_16->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_16->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_16->verticalHeader()->setVisible(true);
    ui->tableWidget_16->resizeColumnsToContents();

    for(int row = 0; row<ui->tableWidget_16->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_16->columnCount(); column++)
        {
            ui->tableWidget_16->setItem(row, column, new QTableWidgetItem());

        }
    }

    // ui->tableWidget_16->setItem(0, 0, new QTableWidgetItem("Установившаяся температура статора"));
    // ui->tableWidget_16->setItem(1, 0, new QTableWidgetItem("Установившаяся температура ротора"));
    // ui->tableWidget_16->setItem(2, 0, new QTableWidgetItem("Постоянная времени статора"));
    // ui->tableWidget_16->setItem(3, 0, new QTableWidgetItem("Постоянная времени ротора"));
    // ui->tableWidget_16->setItem(4, 0, new QTableWidgetItem("Теплоемкость статора"));
    // ui->tableWidget_16->setItem(5, 0, new QTableWidgetItem("Теплоемкость ротора"));
    // ui->tableWidget_16->setItem(6, 0, new QTableWidgetItem("Тепловая проводимость статора"));
    // ui->tableWidget_16->setItem(7, 0, new QTableWidgetItem("Тепловая проводимость между статором и ротором"));
    // ui->tableWidget_16->setItem(8, 0, new QTableWidgetItem("Тепловая проводимость ротора"));
    // ui->tableWidget_16->setItem(9, 0, new QTableWidgetItem("Суммарные потери в статоре"));
    // ui->tableWidget_16->setItem(10, 0, new QTableWidgetItem("Суммарные потери в роторе"));
    // ui->tableWidget_16->setItem(11, 0, new QTableWidgetItem("Потери в стали"));
    // ui->tableWidget_16->setItem(12, 0, new QTableWidgetItem("Скорость вращения"));
    // ui->tableWidget_16->setItem(13, 0, new QTableWidgetItem("Момент"));

    // ui->tableWidget_16->setItem(0, 1, new QTableWidgetItem("τ_1"));
    // ui->tableWidget_16->setItem(1, 1, new QTableWidgetItem("τ_2"));
    // ui->tableWidget_16->setItem(2, 1, new QTableWidgetItem("T_1"));
    // ui->tableWidget_16->setItem(3, 1, new QTableWidgetItem("T_2"));
    // ui->tableWidget_16->setItem(4, 1, new QTableWidgetItem("C_1"));
    // ui->tableWidget_16->setItem(5, 1, new QTableWidgetItem("C_2"));
    // ui->tableWidget_16->setItem(6, 1, new QTableWidgetItem("λ10"));
    // ui->tableWidget_16->setItem(7, 1, new QTableWidgetItem("λ12"));
    // ui->tableWidget_16->setItem(8, 1, new QTableWidgetItem("λ20"));
    // ui->tableWidget_16->setItem(9, 1, new QTableWidgetItem("dPel1"));
    // ui->tableWidget_16->setItem(10, 1, new QTableWidgetItem("dPel2"));
    // ui->tableWidget_16->setItem(11, 1, new QTableWidgetItem("dPct"));
    // ui->tableWidget_16->setItem(12, 1, new QTableWidgetItem("omega"));
    // ui->tableWidget_16->setItem(13, 1, new QTableWidgetItem("M"));

    // ui->tableWidget_16->setItem(0, 3, new QTableWidgetItem("˚C"));
    // ui->tableWidget_16->setItem(1, 3, new QTableWidgetItem("˚C"));
    // ui->tableWidget_16->setItem(2, 3, new QTableWidgetItem("c"));
    // ui->tableWidget_16->setItem(3, 3, new QTableWidgetItem("c"));
    // ui->tableWidget_16->setItem(4, 3, new QTableWidgetItem("Дж/˚C"));
    // ui->tableWidget_16->setItem(5, 3, new QTableWidgetItem("Дж/˚C"));
    // ui->tableWidget_16->setItem(6, 3, new QTableWidgetItem("Вт/(˚C*м)"));
    // ui->tableWidget_16->setItem(7, 3, new QTableWidgetItem("Вт/(˚C*м)"));
    // ui->tableWidget_16->setItem(8, 3, new QTableWidgetItem("Вт/(˚C*м)"));
    // ui->tableWidget_16->setItem(9, 3, new QTableWidgetItem("Вт"));
    // ui->tableWidget_16->setItem(10, 3, new QTableWidgetItem("Вт"));
    // ui->tableWidget_16->setItem(11, 3, new QTableWidgetItem("Вт"));
    // ui->tableWidget_16->setItem(12, 3, new QTableWidgetItem("рад/с"));
    // ui->tableWidget_16->setItem(13, 3, new QTableWidgetItem("Н*м"));

    for (int i=0; i<ui->tableWidget_16->rowCount(); i++)
    {

        if (ui->tableWidget_16->item(i, 1) != 0)
        {
            ui->tableWidget_16->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_16->item(i, 3) != 0)
        {
            ui->tableWidget_16->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }


    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget_16->rowCount(); row++)
    {
        if (ui->tableWidget_16->item(row,0) != 0)
        {
            ui->tableWidget_16->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_16->item(row,1) != 0)
        {
            ui->tableWidget_16->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_16->item(row,2) != 0)
        {
            ui->tableWidget_16->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget_16->item(row,2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_16->item(row,3) != 0)
        {
            ui->tableWidget_16->item(row,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
    }

    QPalette p_16=ui->tableWidget_16->palette(); 
    p_16.setColor(QPalette::Base, QColor(255, 255, 191));
    p_16.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget_16->setPalette(p_16);

    CustomHelpDelegate* customHelpDelegate16 = new CustomHelpDelegate(this); //создание делегата для создания комбобоксов
    ui->tableWidget_16->setItemDelegateForColumn(0, customHelpDelegate16);

    ui->tableWidget_17->setRowCount(30);
    ui->tableWidget_17->setColumnCount(4);
    QStringList name_17;
    name_17 << "Величина" << "Обозначение" << "Значение" << "Размерность";

    ui->tableWidget_17->setHorizontalHeaderLabels(name_16);
    ui->tableWidget_17->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_17->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_17->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_17->verticalHeader()->setVisible(true);
    ui->tableWidget_17->resizeColumnsToContents();

    for(int row = 0; row<ui->tableWidget_17->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_17->columnCount(); column++)
        {
            ui->tableWidget_17->setItem(row, column, new QTableWidgetItem());

        }
    }

    ui->tableWidget_17->setItem(0, 0, new QTableWidgetItem("Установившаяся температура статора"));
    ui->tableWidget_17->setItem(1, 0, new QTableWidgetItem("Установившаяся температура ротора"));
    ui->tableWidget_17->setItem(2, 0, new QTableWidgetItem("Постоянная времени статора"));
    ui->tableWidget_17->setItem(3, 0, new QTableWidgetItem("Постоянная времени ротора"));
    ui->tableWidget_17->setItem(4, 0, new QTableWidgetItem("Теплоемкость статора"));
    ui->tableWidget_17->setItem(5, 0, new QTableWidgetItem("Теплоемкость ротора"));
    ui->tableWidget_17->setItem(6, 0, new QTableWidgetItem("Тепловая проводимость статора"));
    ui->tableWidget_17->setItem(7, 0, new QTableWidgetItem("Тепловая проводимость между статором и ротором"));
    ui->tableWidget_17->setItem(8, 0, new QTableWidgetItem("Тепловая проводимость ротора"));
    ui->tableWidget_17->setItem(9, 0, new QTableWidgetItem("Суммарные потери в статоре"));
    ui->tableWidget_17->setItem(10, 0, new QTableWidgetItem("Суммарные потери в роторе"));
    ui->tableWidget_17->setItem(11, 0, new QTableWidgetItem("Потери в стали"));
    ui->tableWidget_17->setItem(12, 0, new QTableWidgetItem("Скорость вращения"));
    ui->tableWidget_17->setItem(13, 0, new QTableWidgetItem("Момент"));

    ui->tableWidget_17->setItem(0, 1, new QTableWidgetItem("τ_1"));
    ui->tableWidget_17->setItem(1, 1, new QTableWidgetItem("τ_2"));
    ui->tableWidget_17->setItem(2, 1, new QTableWidgetItem("T_1"));
    ui->tableWidget_17->setItem(3, 1, new QTableWidgetItem("T_2"));
    ui->tableWidget_17->setItem(4, 1, new QTableWidgetItem("C_1"));
    ui->tableWidget_17->setItem(5, 1, new QTableWidgetItem("C_2"));
    ui->tableWidget_17->setItem(6, 1, new QTableWidgetItem("λ10"));
    ui->tableWidget_17->setItem(7, 1, new QTableWidgetItem("λ12"));
    ui->tableWidget_17->setItem(8, 1, new QTableWidgetItem("λ20"));
    ui->tableWidget_17->setItem(9, 1, new QTableWidgetItem("dPel1"));
    ui->tableWidget_17->setItem(10, 1, new QTableWidgetItem("dPel2"));
    ui->tableWidget_17->setItem(11, 1, new QTableWidgetItem("dPct"));
    ui->tableWidget_17->setItem(12, 1, new QTableWidgetItem("omega"));
    ui->tableWidget_17->setItem(13, 1, new QTableWidgetItem("M"));

    ui->tableWidget_17->setItem(0, 3, new QTableWidgetItem("˚C"));
    ui->tableWidget_17->setItem(1, 3, new QTableWidgetItem("˚C"));
    ui->tableWidget_17->setItem(2, 3, new QTableWidgetItem("c"));
    ui->tableWidget_17->setItem(3, 3, new QTableWidgetItem("c"));
    ui->tableWidget_17->setItem(4, 3, new QTableWidgetItem("Дж/˚C"));
    ui->tableWidget_17->setItem(5, 3, new QTableWidgetItem("Дж/˚C"));
    ui->tableWidget_17->setItem(6, 3, new QTableWidgetItem("Вт/(˚C*м)"));
    ui->tableWidget_17->setItem(7, 3, new QTableWidgetItem("Вт/(˚C*м)"));
    ui->tableWidget_17->setItem(8, 3, new QTableWidgetItem("Вт/(˚C*м)"));
    ui->tableWidget_17->setItem(9, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_17->setItem(10, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_17->setItem(11, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_17->setItem(12, 3, new QTableWidgetItem("рад/с"));
    ui->tableWidget_17->setItem(13, 3, new QTableWidgetItem("Н*м"));

    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget_17->rowCount(); row++)
    {
        if (ui->tableWidget_17->item(row,0) != 0)
        {
            ui->tableWidget_17->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_17->item(row,1) != 0)
        {
            ui->tableWidget_17->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            ui->tableWidget_17->item(row,1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_17->item(row,2) != 0)
        {
            ui->tableWidget_17->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget_17->item(row,2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_17->item(row,3) != 0)
        {
            ui->tableWidget_17->item(row,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            ui->tableWidget_17->item(row,3)->setTextAlignment(Qt::AlignCenter);
        }
    }

    QPalette p_17=ui->tableWidget_17->palette();
    p_17.setColor(QPalette::Base, QColor(255, 255, 191));
    p_17.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget_17->setPalette(p_17);

    selectionModel3 = ui->tableWidget_17->selectionModel();
    connect(selectionModel3, &QItemSelectionModel::currentChanged,
                     this, [this]() {  int index = 0;
        QString currentTabText = ui->tabWidget->tabText(index);
        setWindowTitle(currentTabText + "@" + QString(item4->text()) + QString(" - ImView*"));
        isNablLaunched = true;
    });

    ui->tableWidget_18->setRowCount(30);
    ui->tableWidget_18->setColumnCount(4);
    QStringList name_18;
    name_18 << "Величина" << "Обозначение" << "Значение" << "Размерность";

    ui->tableWidget_18->setHorizontalHeaderLabels(name_16);
    ui->tableWidget_18->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_18->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_18->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_18->verticalHeader()->setVisible(true);
    ui->tableWidget_18->resizeColumnsToContents();

    for(int row = 0; row<ui->tableWidget_18->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_18->columnCount(); column++)
        {
            ui->tableWidget_18->setItem(row, column, new QTableWidgetItem());

        }
    }

    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget_18->rowCount(); row++)
    {
        if (ui->tableWidget_18->item(row,0) != 0)
        {
            ui->tableWidget_18->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_18->item(row,1) != 0)
        {
            ui->tableWidget_18->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            ui->tableWidget_18->item(row,1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_18->item(row,2) != 0)
        {
            ui->tableWidget_18->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget_18->item(row,2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_18->item(row,3) != 0)
        {
            ui->tableWidget_18->item(row,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            ui->tableWidget_18->item(row,3)->setTextAlignment(Qt::AlignCenter);
        }
    }

    QPalette p_18=ui->tableWidget_18->palette();
    p_18.setColor(QPalette::Base, QColor(255, 255, 191));
    p_18.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget_18->setPalette(p_18);

    ui->tableWidget_19->setRowCount(8);
    ui->tableWidget_19->setColumnCount(3);
    QStringList name_19;
    name_19 << " № " << "Сигнал" << "Величина";
    ui->tableWidget_19->setHorizontalHeaderLabels(name_19);
    ui->tableWidget_19->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_19->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_19->verticalHeader()->setVisible(false);
    ui->tableWidget_19->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_19->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_19->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_19->setColumnWidth(0, 100);
    ui->tableWidget_19->setColumnWidth(1, 400);

    for(int row = 0; row<ui->tableWidget_19->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_19->columnCount(); column++)
        {
            ui->tableWidget_19->setItem(row, column, new QTableWidgetItem());

        }
    }

    for (int i=0; i<8; i++)
    {
        if (ui->tableWidget_9->item(i, 0) != 0)
        {
            ui->tableWidget_9->item(i, 0)->setText(QString("%1").arg(i+1));
            ui->tableWidget_9->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }


    QPalette p19=ui->tableWidget_19->palette();
    p19.setColor(QPalette::Base, QColor(225, 255, 255));
    p19.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget_19->setPalette(p19);

    ui->tableWidget_20->setRowCount(30);
    ui->tableWidget_20->setColumnCount(4);
    QStringList name_20;
    name_20 << "Величина" << "Обозначение" << "Значение" << "Размерность";

    ui->tableWidget_20->setHorizontalHeaderLabels(name_20);
    ui->tableWidget_20->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_20->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_20->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_20->verticalHeader()->setVisible(true);
    ui->tableWidget_20->resizeColumnsToContents();

    for(int row = 0; row<ui->tableWidget_20->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_20->columnCount(); column++)
        {
            ui->tableWidget_20->setItem(row, column, new QTableWidgetItem());

        }
    }

    for (int i=0; i<ui->tableWidget_20->rowCount(); i++)
    {

        if (ui->tableWidget_20->item(i, 1) != 0)
        {
            ui->tableWidget_20->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_20->item(i, 3) != 0)
        {
            ui->tableWidget_20->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }


    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget_20->rowCount(); row++)
    {
        if (ui->tableWidget_20->item(row,0) != 0)
        {
            ui->tableWidget_20->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_20->item(row,1) != 0)
        {
            ui->tableWidget_20->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_20->item(row,2) != 0)
        {
            ui->tableWidget_20->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget_20->item(row,2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_20->item(row,3) != 0)
        {
            ui->tableWidget_20->item(row,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
    }

    QPalette p_20=ui->tableWidget_20->palette();
    p_20.setColor(QPalette::Base, QColor(255, 255, 191));
    p_20.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget_20->setPalette(p_20);



    ui->tabWidget->setCurrentIndex(0);
    ui->widget_5->ui->tabWidget->setCurrentIndex(0);
    ui->widget_5->ui->tabWidget_2->setCurrentIndex(0);
    ui->widget_6->ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget_3->setCurrentIndex(0);

    //Настройка статусбара
    statusbar_label = new QLabel;
    statusbar_label->setPixmap(QPixmap(":/icons/data/img/icons/archivator_red_24.svg"));
    statusbar_label->setAlignment(Qt::AlignTop);
    ui->statusbar->addWidget(statusbar_label);

    statusbar_label_2 = new QLabel("Архиватор не подключен");
    statusbar_label_2->setAlignment(Qt::AlignTop);
    ui->statusbar->addWidget(statusbar_label_2);

    statusbar_label_3 = new QLabel("");
    statusbar_label_3->setPixmap(QPixmap(":/icons/data/img/icons/osc_red_24.svg"));
    statusbar_label_3->setAlignment(Qt::AlignTop);
    ui->statusbar->addWidget(statusbar_label_3);

    statusbar_label_4 = new QLabel("Осциллограф не подключен");
    statusbar_label_4->setAlignment(Qt::AlignTop);
    ui->statusbar->addWidget(statusbar_label_4);

    statusbar_label_5 = new QLabel("");
    statusbar_label_5->setPixmap(QPixmap(":/icons/data/img/icons/plk_red_24.svg"));
    statusbar_label_5->setAlignment(Qt::AlignTop);
    ui->statusbar->addWidget(statusbar_label_5);

    statusbar_label_6 = new QLabel("ПЛК не подключен");
    statusbar_label_6->setAlignment(Qt::AlignTop);
    ui->statusbar->addWidget(statusbar_label_6);

    statusbar_label_7 = new QLabel("");
    statusbar_label_7->setPixmap(QPixmap(":/icons/data/img/icons/moment_red_24.svg"));
    statusbar_label_7->setAlignment(Qt::AlignTop);
    ui->statusbar->addWidget(statusbar_label_7);

    statusbar_label_8 = new QLabel("Управление моментом не подключено");
    statusbar_label_8->setAlignment(Qt::AlignTop);
    ui->statusbar->addWidget(statusbar_label_8);

    statusbar_label_9 = new QLabel("T=0.000000");
    statusbar_label_9->setAlignment(Qt::AlignVCenter);
    ui->statusbar->addPermanentWidget(statusbar_label_9);
    statusbar_label_9->setVisible(false);

    widget2 = new QWidget(ui->statusbar);
    widget2->setFixedWidth(50);
    widget2->setHidden(1);
    widget2->setVisible(1);
    ui->statusbar->addPermanentWidget(widget2);

    statusbar_progres = new QProgressBar(ui->statusbar);
    statusbar_progres->setMaximumSize(300,19);
    ui->statusbar->addPermanentWidget(statusbar_progres);
    setStyleSheet("QProgressBar {border: 2px solid grey;height: 5px; text-align: center;} QProgressBar::chunk {background-color: #55FF55;width: 20px}");
    statusbar_progres->setVisible(false);

    widget = new QWidget(ui->statusbar);
    widget->setFixedWidth(250);
    widget->setHidden(1);
    widget->setVisible(1);
    ui->statusbar->addPermanentWidget(widget);

    QWidget *spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacerWidget->setVisible(true);
    QAction *myAction = new QAction(tr("Exit"), this);
    QIcon icon11;
    icon11.addFile(QString::fromUtf8(":/system_icons/data/img/system_icons/file_close.svg"), QSize(), QIcon::Normal, QIcon::Off);
    myAction->setIcon(icon11);
    ui->toolBar_2->addWidget(spacerWidget);
    ui->toolBar_2->addAction(myAction);
    connect(myAction, &QAction::triggered, this, &MainWindow::close_progect);

    QObject::connect(ui->treeView, &QAbstractItemView::activated,this, &MainWindow::itemEdit);

    connect(item14->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot);
    connect(item88->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot_2);
    connect(item80->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot_3);
    connect(item68->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot_4);
    connect(item158->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot_5);
    connect(item174->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot_6);
    connect(item22->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot_7);
    connect(item178->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot_8);

    connect(buttonColumnDelegate, &ButtonColumnDelegate::projectFileSelected, this, &MainWindow::projectFileSelectedSlot);
    connect(buttonColumnDelegate, &ButtonColumnDelegate::projectFileSelected_2, this, &MainWindow::projectFileSelectedSlot_2);
    connect(buttonColumnDelegate, &ButtonColumnDelegate::projectFileSelected_3, this, &MainWindow::projectFileSelectedSlot_3);
    connect(buttonColumnDelegate, &ButtonColumnDelegate::projectFileSelected_5, this, &MainWindow::projectFileSelectedSlot_5);
    connect(buttonColumnDelegate, &ButtonColumnDelegate::projectFileSelected_6, this, &MainWindow::projectFileSelectedSlot_6);

    connect(ui->tabWidget, &QTabWidget::currentChanged, this,&MainWindow::tabClicked);
    connect(ui->widget_5->ui->tabWidget, &QTabWidget::currentChanged, this,&MainWindow::tabClicked_2);
    connect(ui->widget_5->ui->tabWidget_2, &QTabWidget::currentChanged, this,&MainWindow::tabClicked_3);
    connect(ui->widget_6->ui->tabWidget, &QTabWidget::currentChanged, this,&MainWindow::tabClicked_4);
    connect(ui->tabWidget_3, &QTabWidget::currentChanged, this,&MainWindow::tabClicked_5);
    //connect(ui->widget_7->ui->tabWidget, &QTabWidget::currentChanged, this,&MainWindow::tabClicked_6);
    connect(model2, &QStandardItemModel::itemChanged, this, &MainWindow::button_visible);
    connect(model2, &QStandardItemModel::itemChanged, this, &MainWindow::button_visible_2);

    connect(ui->lineEdit_13,&QLineEdit::textEdited, this, &MainWindow::edit);
    connect(ui->lineEdit_16,&QLineEdit::textEdited, this, &MainWindow::edit_2);
    connect(ui->lineEdit_14,&QLineEdit::textEdited, this, &MainWindow::edit_3);
    connect(ui->lineEdit_17,&QLineEdit::textEdited, this, &MainWindow::edit_4);
    connect(ui->lineEdit_15,&QLineEdit::textEdited, this, &MainWindow::edit_5);
    connect(ui->lineEdit_18,&QLineEdit::textEdited, this, &MainWindow::edit_6);
    connect(model2,&QStandardItemModel::itemChanged, this, &MainWindow::edit_treeview);

    connect(ui->widget_3, &electromagn::tick, this, &MainWindow::on_electromagn_tick);

    updateRecentFileActions();

    // if (model2) {
    //     // Получаем количество корневых узлов
    //     int rootCount = model2->rowCount();
    //     for (int i = 0; i < rootCount; ++i) {
    //         QModelIndex rootIndex = model2->index(i, 0); // Индекс корневого узла
    //         // Здесь можно выполнить действия с rootIndex (например, вывод в консоль)
    //         qDebug() << "Корневой узел индекс:" << rootIndex.row();
    //     }}
}

void MainWindow::treview_changed()
{
     //qDebug() << "Item selection changed";
    isNablLaunched = true;
}

QImage fromSvg(const QString &path, int size)
{
    QSvgRenderer renderer(path);

    QImage image(size, size, QImage::Format_ARGB32);
    image.fill(0x00ffffff);
    QPainter painter(&image);
    renderer.render(&painter);

    return image;
}

void MainWindow::itemEdit()
{
//    if(ui->treeView->isHidden())
//            return;

//        int nrFillItems = 0;
//        foreach(QStandardItem* itemm, item)){
//            if(dynamic_cast<QAbstractGraphicsShapeItem*> (item))
//                nrFillItems++;
//        }
//        if(nrFillItems == 0)
//            return;

//        int currentIndex = itemm->currentIndex();
//        QString currrenttext = colorComboBox->itemData(currentIndex).value<QColor>();
//        undoStack->push(new ChangeItemColorCommand(itemm, currrenttext));

}

void MainWindow::createUndoStackAndActions()
{
    undoStack = new QUndoStack(this);
    undoAction = ui->actionundo;
    redoAction =  ui->actionredo;
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    if(isNablLaunched == true)
    {
        QMessageBox::StandardButton resBtn = QMessageBox::warning( this, "Закрыть сеанс - IM View", "\n Данные сеанса были изменены.  \n Сохранить или отклонить изменения? \n", QMessageBox::Cancel | QMessageBox::Discard | QMessageBox::Save);
        QDir dir("/tmp/imview");
        switch (resBtn)
        {
        case QMessageBox::Save:
            ui->widget_3->stop();
            save_file();
            dir.removeRecursively();
            event->accept();
        break;
        case QMessageBox::Discard:
            ui->widget_3->stop();
            dir.removeRecursively();
            event->accept();
        break;
        default:
        case QMessageBox::Cancel:
            event->ignore();
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actionabout()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    rsc = new AboutDialog(this);
    rsc->wf = this;
    rsc->exec();
    rsc->setGeometry(
                QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    rsc->size(),
                    screen->geometry()));
}

void MainWindow::actionExit()
{
    close();
}

void MainWindow::actionhelp()
{
    view = new QWebEngineView;
    connect(view, &QWebEngineView::titleChanged, this, &MainWindow::titleChanged);
    view->setUrl(QUrl::fromLocalFile(QFileInfo("../help/index.html").absoluteFilePath()));
    view->setWindowIcon(QIcon::fromTheme("help-contents"));
    view->showMaximized();
}

void MainWindow::titleChanged(const QString &title)
{
    view->setWindowTitle(title);
}

void MainWindow::save_dannie()
{
    ui->widget->on_saveDannie_clicked();
}

void MainWindow::enter_dannie()
{
    ui->widget->on_enterDannie_clicked();
}

void MainWindow::delete_dannie()
{
    ui->widget->on_deleteDannie_clicked();
}

void MainWindow::identf_pusk()
{
    auto rowList = ui->widget->ui->tableView->selectionModel()->selectedRows();
    if(rowList.count() > 0)
    {
        rowNumber = rowList.constFirst().row();
    }
    else
    {
        QMessageBox::warning(this, "Внимание!", "Выберите в таблице строку \n с данными нужного двигателя");
        return;
    }

    ui->widget_15->setVisible(false);
    if (item88->text() == "Выбрать тип эксперимента")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        ui->tabWidget->show();
        ui->tabWidget->setCurrentIndex(1);
        QPixmap pixmap(":/system_icons/data/img/system_icons/go-previous.svg");
        QIcon ButtonIcon_1(pixmap);
        ui->switch_regim_upr->setIcon(ButtonIcon_1);
        ui->stackedWidget->setVisible(false);

        loadMotorParameters();

        ui->identf_pusk->setIcon(QIcon(":/system_icons/data/img/system_icons/media-playback-paused.svg"));
        ui->identf_stop->setEnabled(true);

        //создание папки текущего сеанса
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QTime currentTime = currentDateTime.time();
        QDate currentDate = currentDateTime.date();

        QString setpath = "../Output";
        QDir dir(setpath);

        dirName= QString ("%1""%2""%3").arg("Сеанс ",currentTime.toString("hh:mm:ss ").toUtf8().data(),
                currentDate.toString("dd.MM.yyyy").toUtf8().data());

        dir.mkdir(dirName);

        //if(item68->checkState() == Qt::Checked)
        if(item68->text() == "Сохранить")
        {
            QString filename = "result_identf.csv";
            //создание файла сохранений идентификации параметров схемы замещения
            std::ofstream fout;

            base.identfFilename = setpath+QDir::separator()+dirName+QDir::separator()+filename;

            fout.open(QString(base.identfFilename).toStdString(),std::ios::out | std::ios::app);
            fout << std::endl << "Начало измерений " << currentTime.toString("hh:mm:ss ").toUtf8().data() <<
                    currentDate.toString("dd.MM.yyyy").toUtf8().data() << std::endl;
            fout << std::endl;

            fout << "Канал №1" << " - " << "Активное сопротивление фазы ротора" << std::endl;
            fout << "Канал №2" << " - " << "Индуктивность фазы статора" << std::endl;
            fout << "Канал №3" << " - " << "Индуктивность фазы ротора" << std::endl;
            fout << "Канал №4" << " - " << "Индуктивность взаимоиндукции" << std::endl;

            fout << std::endl;

            fout << "Время;";

            for (int i=0; i<4; i++)
            {
                fout << QString("Канал №%1").arg(i+1).toUtf8().data() << ";";
                //fout << modelss.R2 << modelss.L << modelss.L << modelss.Lm;
            }

            fout << std::endl;

            fout.close();
        }
        ui->widget_2->raschet_f();
    }
}

void MainWindow::identf_stop()
{
    ui->identf_pusk->setIcon(QIcon(":/system_icons/data/img/system_icons/media-playback-start_2.svg"));
    ui->identf_stop->setEnabled(false);
    ui->widget_2->dataSource->stop();
}

void MainWindow::electromagn_start()
{
    isNablLaunched = true;
    ui->tabWidget->show();
    ui->tabWidget->setCurrentIndex(4);
    ui->stackedWidget->show();
    ui->stackedWidget->setCurrentIndex(7);
    QPixmap pixmap(":/system_icons/data/img/system_icons/go-previous.svg");
    QIcon ButtonIcon_1(pixmap);
    ui->switch_regim_upr->setIcon(ButtonIcon_1);
    //ui->stackedWidget->hide();
    base.R1 = ui->lineEdit_12->text().toDouble();
    base.R2 = ui->lineEdit_11->text().toDouble();
    base.L1 = ui->lineEdit_10->text().toDouble();
    base.L2 = ui->lineEdit_9->text().toDouble();
    base.Lm = ui->lineEdit_8->text().toDouble();

    loadMotorParameters();

    ui->electromagn_start->setIcon(QIcon(":/system_icons/data/img/system_icons/media-playback-paused.svg"));
    ui->electromagn_stop->setEnabled(true);

    statusbar_label_9->setVisible(true);
    statusbar_progres->setVisible(true);
    statusbar_progres->setMinimum(0);
    statusbar_progres->setMaximum(100);
    //statusbar_progres->setRange(0, 1000);
    statusbar_progres->reset();

    if(item70->text() == "Сохранить")
    {
        //создание файла сохранений идентификации параметров схемы замещения
        std::ofstream fout;
        QString filename = "result_electromagn.csv";
        QString setpath = "../Output";
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QTime currentTime = currentDateTime.time();
        QDate currentDate = currentDateTime.date();
        base.electromagnFilename = setpath+QDir::separator()+dirName+QDir::separator()+filename;

        fout.open(QString(base.electromagnFilename).toStdString(),std::ios::out | std::ios::app);

        fout << std::endl << "Начало измерений " << currentTime.toString("hh:mm:ss ").toUtf8().data() <<
                currentDate.toString("dd.MM.yyyy").toUtf8().data() << std::endl;
        fout << std::endl;

        fout << "Канал №1" << " - " << "Напряжение фазы А, В" << std::endl;
        fout << "Канал №2" << " - " << "Напряжение фазы В, В" << std::endl;
        fout << "Канал №3" << " - " << "Напряжение фазы С, В" << std::endl;
        fout << "Канал №4" << " - " << "Ток фазы А, В" << std::endl;
        fout << "Канал №5" << " - " << "Ток фазы В, В" << std::endl;
        fout << "Канал №6" << " - " << "Ток фазы С, В" << std::endl;
        fout << "Канал №7" << " - " << "Частота вращения, рад/с" << std::endl;
        fout << "Канал №8" << " - " << "Момент на валу, Н*м" << std::endl;
        fout << "Канал №9" << " - " << "Момент Мс, Н*м" << std::endl;

        fout << std::endl;

        fout << "Время;";

        for (int i=0; i<9; i++)
        {
            fout << QString("Канал №%1").arg(i+1).toUtf8().data() << ";";
        }

        fout << std::endl;

        fout.close();
    }

    if(item70->checkState() == Qt::Checked)
    {
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QTime currentTime = currentDateTime.time();
        QDate currentDate = currentDateTime.date();
        QString setpath = "../Output";
        //QDir dir(setpath);
        QString filename = "result_tepl.csv";

        //создание файла сохранений идентификации параметров схемы замещения
        std::ofstream fout;

        base.teplFilename = setpath+QDir::separator()+dirName+QDir::separator()+filename;

        fout.open(QString(base.teplFilename).toStdString(),std::ios::out | std::ios::app);
        fout << std::endl << "Начало измерений " << currentTime.toString("hh:mm:ss ").toUtf8().data() <<
                currentDate.toString("dd.MM.yyyy").toUtf8().data() << std::endl;
        fout << std::endl;

        fout << "Канал №1"  << " - " << "Cтанина" << std::endl;
        fout << "Канал №2"  << " - " << "Подшипниковый узел справа сзади" << std::endl;
        fout << "Канал №3"  << " - " << "Лобовая часть слева спереди" << std::endl;
        fout << "Канал №4"  << " - " << "Подшипниковый узел слева спереди" << std::endl;
        fout << "Канал №5"  << " - " << "Подшипниковый узел слева спереди" << std::endl;
        fout << "Канал №6"  << " - " << "Лобовая часть слева сзади" << std::endl;
        fout << "Канал №7"  << " - " << "Лобовая часть справа спереди" << std::endl;
        fout << "Канал №8"  << " - " << "Лобовая часть справа сзади" << std::endl;
        fout << "Канал №9"  << " - " << "Магнитопровод статора" << std::endl;
        fout << "Канал №10" << " - " << "Подшипниковый узел справа спереди" << std::endl;
        fout << "Канал №11" << " - " << "Подшипниковый узел слева сзади" << std::endl;
        fout << "Канал №12" << " - " << "Ротор сверху" << std::endl;
        fout << "Канал №13" << " - " << "Ротор снизу" << std::endl;
        fout << "Канал №14" << " - " << "Станина слева" << std::endl;
        fout << "Канал №15" << " - " << "Станина слева" << std::endl;
        fout << "Канал №16" << " - " << "Вал" << std::endl;
        fout << "Канал №17" << " - " << "Клеммная коробка" << std::endl;

        fout << std::endl;

        fout << "Время;";

        for (int i=0; i<17; i++)
        {
            fout << QString("Канал №%1").arg(i+1).toUtf8().data() << ";";
        }

        fout << std::endl;

        fout.close();
    }

    //Добавление линий графиков в виджет Plot

    ui->widget_3->ui->plot->clear();

    for (int i = 0; i < dataLineColors.size(); i++)
    {
        ui->widget_3->ui->plot->addDataLine(dataLineColors[i], 0);
    }

    //Установка нулевой точки графиков

    double b4 = ui->tableWidget->item(4,3)->text().toDouble();
    ui->widget_3->ui->plot->addPoint(0, 0, b4);//u_a
    double b5 = ui->tableWidget->item(5,3)->text().toDouble();
    ui->widget_3->ui->plot->addPoint(1, 0, b5);//u_b
    double b6 = ui->tableWidget->item(6,3)->text().toDouble();
    ui->widget_3->ui->plot->addPoint(2, 0, b6);//u_c
    double b10 = ui->tableWidget->item(7,3)->text().toDouble();
    ui->widget_3->ui->plot->addPoint(3, 0, b10);//i_a
    double b11 = ui->tableWidget->item(8,3)->text().toDouble();
    ui->widget_3->ui->plot->addPoint(4, 0, b11);//i_b
    double b12 = ui->tableWidget->item(9,3)->text().toDouble();
    ui->widget_3->ui->plot->addPoint(5, 0, b12);//i_c
    double b15 = ui->tableWidget->item(10,3)->text().toDouble();
    ui->widget_3->ui->plot->addPoint(6, 0, b15);//w
    double b16 = ui->tableWidget->item(11,3)->text().toDouble();
    ui->widget_3->ui->plot->addPoint(7, 0, b16);//moment
    double b17 = ui->tableWidget->item(12,4)->text().toDouble();
    ui->widget_3->ui->plot->addPoint(8, 0, b17);//moment_c

    ui->widget_3->raschet_el();
    ui->widget_5->ui->widget_4->startTeplo();
}

void MainWindow::electromagn_stop()
{
    isNablLaunched = false;
    ui->electromagn_start->setIcon(QIcon(":/system_icons/data/img/system_icons/media-playback-start.svg"));
    ui->electromagn_stop->setEnabled(false);
    ui->widget_5->ui->widget_4->stopTeplo();
    ui->widget_3->stop();
    statusbar_progres->setVisible(false);
    statusbar_label_9->setVisible(false);
}

void MainWindow::currentChanged(int index)
{
    QString currentTabText = ui->tabWidget->tabText(index);
    setWindowTitle(currentTabText + "@" + QString(item4->text()) + QString(" - ImView"));
}

void MainWindow::kalibr_osc()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    kalibr=new Kalibr(this);
    kalibr->showMaximized();
    kalibr->setGeometry(
    QStyle::alignedRect(
    Qt::LeftToRight,
    Qt::AlignCenter,
    kalibr->size(),
    screen->geometry()));
}

void MainWindow::nastr_graph()
{
    QPixmap pixmap(":/system_icons/data/img/system_icons/go-next.svg");
    QIcon ButtonIcon_2(pixmap);
    ui->switch_regim_upr->setIcon(ButtonIcon_2);
    ui->stackedWidget->show();
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
            ui->retranslateUi(this);
    }
}

void MainWindow::translate_en()
{
    qtLanguageTranslator = new QTranslator();
    qtLanguageTranslator->load("QtLanguage_en_US");
    qApp->removeTranslator(qtLanguageTranslator);
    qApp->installTranslator(qtLanguageTranslator);
}

void MainWindow::translate_ru()
{
    qApp->removeTranslator(qtLanguageTranslator);
    qApp->removeTranslator(qtLanguageTranslator);
}

void MainWindow::translator()
{
    QTranslator qtLanguageTranslator;
    QSettings settings( "BRU", "IM View");
    settings.beginGroup( "language interface" );
    QString lokal = settings.value( "QtLanguage_", "").toString();
    settings.endGroup();
    qtLanguageTranslator.load("QtLanguage_" + lokal);   // Загружаем перевод
    qApp->installTranslator(&qtLanguageTranslator);
}

void MainWindow::nastroiki()
{
    // QPixmap pixmap(":/system_icons//data/img/system_icons/go-next.svg");
    // QIcon ButtonIcon_2(pixmap);
    // ui->switch_regim_upr->setIcon(ButtonIcon_2);
    // ui->stackedWidget->show();
    // ui->stackedWidget->setCurrentIndex(0);

    QScreen *screen = QGuiApplication::primaryScreen();
    nastr = new Nastroiki(this);
    nastr->wf = this;
    nastr->exec();
    nastr->setGeometry(
    QStyle::alignedRect(
    Qt::LeftToRight,
    Qt::AlignCenter,
    nastr->size(),
    screen->geometry()));
}

void MainWindow::modelItemChangedSlot(QStandardItem *item)
{
    if (item == item14)
    {
        if (item->text() == "Ручной")
        {
            item93->setEnabled(true);
            item94->setEnabled(true);
            item95->setEnabled(true);
            item96->setEnabled(true);
            item97->setEnabled(true);
            item98->setEnabled(true);
            item99->setEnabled(true);
            item100->setEnabled(true);
            item101->setEnabled(true);
            item102->setEnabled(true);
            item103->setEnabled(true);
            item104->setEnabled(true);
        }
        else
        {
            item93->setEnabled(false);
            item94->setEnabled(false);
            item95->setEnabled(false);
            item96->setEnabled(false);
            item97->setEnabled(false);
            item98->setEnabled(false);
            item99->setEnabled(false);
            item100->setEnabled(false);
            item101->setEnabled(false);
            item102->setEnabled(false);
            item103->setEnabled(false);
            item104->setEnabled(false);
        }
    }
}

void MainWindow::projectFileSelectedSlot(QString projectFile)
{
    item6->setText(projectFile);
}

void MainWindow::projectFileSelectedSlot_2(QString projectFile_2)
{
    item84->setData(projectFile_2, Qt::DisplayRole);
    item84->setData(projectFile_2, Qt::UserRole);
}

void MainWindow::projectFileSelectedSlot_3(QString projectFile_3)
{
    item86->setData(projectFile_3, Qt::DisplayRole);
    item86->setData(projectFile_3, Qt::UserRole);
}

void MainWindow::projectFileSelectedSlot_4(QString projectFile_4)
{
    item86->setData(projectFile_4, Qt::DisplayRole);
    item86->setData(projectFile_4, Qt::UserRole);
}

void MainWindow::projectFileSelectedSlot_5(QString projectFile_5)
{
    item106->setData(projectFile_5, Qt::DisplayRole);
    item106->setData(projectFile_5, Qt::UserRole);
}

void MainWindow::projectFileSelectedSlot_6(QString projectFile_6)
{
    item82->setData(projectFile_6, Qt::DisplayRole);
    item82->setData(projectFile_6, Qt::UserRole);
}

void MainWindow::modelItemChangedSlot_2(QStandardItem *item)
{
    if (item == item88)
    {
        if (item->text() == "Чтение данных из файла для идентификации параметров схемы замещения")
        {
            item105->setEnabled(true);
            item106->setEnabled(true);
        }
        else
        {
            item105->setEnabled(false);
            item106->setEnabled(false);
        }
    }
}

void MainWindow::modelItemChangedSlot_3(QStandardItem *item)
{
    if (item == item80)
    {
        if (item->text() == "Чтение данных из файла для наблюдателя скорости")
        {
            item81->setEnabled(true);
            item82->setEnabled(true);
        }
        else
        {
            item81->setEnabled(false);
            item82->setEnabled(false);
        }
    }
}

void MainWindow::modelItemChangedSlot_4(QStandardItem *item)
{
    if (item == item68)
    {
        if (item->checkState() == Qt::Checked)
        {
            item68->setToolTip(tr ("Вкл"));
        }
        else
        {
            item68->setToolTip(tr ("Выкл"));
        }
    }
    else
    if (item == item70)
    {
        if (item->checkState() == Qt::Checked)
        {
            item70->setToolTip(tr ("Вкл"));
        }
        else
        {
            item70->setToolTip(tr ("Выкл"));
        }
    }
    else
    if (item == item72)
    {
        if (item->checkState() == Qt::Checked)
        {
            item72->setToolTip(tr ("Вкл"));
        }
        else
        {
            item72->setToolTip(tr ("Выкл"));
        }
    }
    else
    if (item == item74)
    {
        if (item->checkState() == Qt::Checked)
        {
            item74->setToolTip(tr ("Вкл"));
        }
        else
        {
            item74->setToolTip(tr ("Выкл"));
        }
    }
    else
    if (item == item76)
    {
        if (item->checkState() == Qt::Checked)
        {
            item76->setToolTip(tr ("Вкл"));
        }
        else
        {
            item76->setToolTip(tr ("Выкл"));
        }
    }
    else
    if (item == item78)
    {
        if (item->checkState() == Qt::Checked)
        {
            item78->setToolTip(tr ("Вкл"));
        }
        else
        {
            item78->setToolTip(tr ("Выкл"));
        }
    }
    else
    if (item == item14)
    {
        if (item->checkState() == Qt::Checked)
        {
            item14->setToolTip(tr ("Вкл"));
        }
        else
        {
            item14->setToolTip(tr ("Выкл"));
        }
    }
    else
    if (item == item94)
    {
        QString w101=item94->text();
        item94->setToolTip(w101);
    }
    else
    if (item == item96)
    {
        QString w102=item96->text();
        item96->setToolTip(w102);
    }
    else
    if (item == item98)
    {
        QString w103=item98->text();
        item98->setToolTip(w103);
    }
    else
    if (item == item100)
    {
        QString w104=item100->text();
        item100->setToolTip(w104);
    }
    else
    if (item == item102)
    {
        QString w105=item102->text();
        item102->setToolTip(w105);
    }
    else
    if (item == item104)
    {
        QString w106=item104->text();
        item104->setToolTip(w106);
    }
    else
    if (item == item20)
    {
        QString w107=item20->text();
        item20->setToolTip(w107);
    }
    else
    if (item == item22)
    {
        QString w108=item22->text();
        item22->setToolTip(w108);
    }
    else
    if (item == item24)
    {
        QString w109=item24->text();
        item24->setToolTip(w109);
    }
    else
    if (item == item90)
    {
        QString w110=item90->text();
        item90->setToolTip(w110);
    }
    else
    if (item == item92)
    {
        QString w111=item92->text();
        item92->setToolTip(w111);
    }
}

void MainWindow::modelItemChangedSlot_5(QStandardItem *item)
{
    if (item == item158)
    {
        if (item->text() == "Ручной")
        {
            item159->setEnabled(true);
            item160->setEnabled(true);
        }
        else
        {
            item159->setEnabled(false);
            item160->setEnabled(false);
        }
    }
}

void MainWindow::modelItemChangedSlot_6(QStandardItem *item)
{
    if (item == item24)
    {
        if (item->text() == "Фиксированное время")
        {
            item173->setEnabled(true);
            item174->setEnabled(true);
        }
        else
        {
            item173->setEnabled(false);
            item174->setEnabled(false);
        }
    }
}

void MainWindow::modelItemChangedSlot_7(QStandardItem *item)
{
    if (item == item20)
    {
        if (item->text() == "Режим S1")
        {
            item21->setEnabled(false);
            item22->setEnabled(false);
            item175->setEnabled(false);
            item176->setEnabled(false);
        }
        else
        {
            item21->setEnabled(true);
            item22->setEnabled(true);
            item175->setEnabled(true);
            item176->setEnabled(true);
        }
    }
}

void MainWindow::modelItemChangedSlot_8(QStandardItem *item)
{
    if (item == item20)
    {
        if (item->text() == "Режим S4")
        {
            item177->setEnabled(true);
            item178->setEnabled(true);
        }
        else
        {
            item177->setEnabled(false);
            item178->setEnabled(false);
        }
    }
}

void MainWindow::SaveProgectToFile()
{
    // QFileDialog saveDialog;
    // saveDialog.setAcceptMode(QFileDialog::AcceptSave);
    // saveDialog.setDefaultSuffix("imview");
    // saveDialog.setNameFilter(tr("Файл конфигурации проекта (*.imview);;Все файлы (*.*)"));
    // saveDialog.setViewMode(QFileDialog::Detail);
    // saveDialog.setDirectory("../Output");
    // saveDialog.exec();
    // QString str = "../" + saveDialog.selectedFiles().constFirst();

    // QFile file(QString("../save/project.xml"));
    // file.open(QIODevice::WriteOnly);


    QString filter = "Файл конфигурации проекта (*.imview);;Все файлы (*.*)";
    QString str = QFileDialog::getSaveFileName(this, "Выбрать имя, под которым сохранить данные", "../Output", filter);

   // QFile file(QString("/home/elf/ImView/data/tepl.xml"));
    QFile file(str);
    file.open(QIODevice::WriteOnly);

    //Создаем объект, с помощью которого осуществляется запись в файл
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
    xmlWriter.writeStartDocument();     // Запускаем запись в документ
    xmlWriter.writeStartElement("resources");   // Записываем первый элемент с его именем
    xmlWriter.writeStartElement("project");  // Записываем тег с именем для первого итема

    xmlWriter.writeStartElement("general_settings");

    xmlWriter.writeStartElement("project_name");
    xmlWriter.writeAttribute("value", (item4->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_1");
    xmlWriter.writeAttribute("value", (item88->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("project_path");
    xmlWriter.writeAttribute("value", (item106->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_2");
    xmlWriter.writeAttribute("value", (item80->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("project_path_2");
    xmlWriter.writeAttribute("value", (item82->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_3");
    xmlWriter.writeAttribute("value", (item68->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_4");
    xmlWriter.writeAttribute("value", (item70->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_5");
    xmlWriter.writeAttribute("value", (item72->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_6");
    xmlWriter.writeAttribute("value", (item74->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_7");
    xmlWriter.writeAttribute("value", (item76->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_8");
    xmlWriter.writeAttribute("value", (item78->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_9");
    xmlWriter.writeAttribute("value", (item14->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_1");
    xmlWriter.writeAttribute("value", (item94->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_2");
    xmlWriter.writeAttribute("value", (item96->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_3");
    xmlWriter.writeAttribute("value", (item98->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_4");
    xmlWriter.writeAttribute("value", (item100->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_5");
    xmlWriter.writeAttribute("value", (item102->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_6");
    xmlWriter.writeAttribute("value", (item104->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_10");
    xmlWriter.writeAttribute("value", (item20->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("time_cikle");
    xmlWriter.writeAttribute("value", (item22->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("time_work");
    xmlWriter.writeAttribute("value", (item176->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_11");
    xmlWriter.writeAttribute("value", (item24->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_12");
    xmlWriter.writeAttribute("value", (item92->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("napragenie");
    xmlWriter.writeAttribute("value", (item130->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("moment");
    xmlWriter.writeAttribute("value", (item132->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("start_temp");
    xmlWriter.writeAttribute("value", (item28->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_13");
    xmlWriter.writeAttribute("value", (item30->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_14");
    xmlWriter.writeAttribute("value", (item141->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_15");
    xmlWriter.writeAttribute("value", (item142->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("time_step");
    xmlWriter.writeAttribute("value", (item107->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_16");
    xmlWriter.writeAttribute("value", (item34->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_17");
    xmlWriter.writeAttribute("value", (item36->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("pressure");
    xmlWriter.writeAttribute("value", (item38->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("selected_row");
    xmlWriter.writeAttribute("value", QString("%1").arg(QString::number(rowNumber,'f',1)));
    xmlWriter.writeEndElement();

    if(item68->text() == "Сохранить")
    {
        xmlWriter.writeStartElement("sopr_R1");
        xmlWriter.writeAttribute("value", (ui->lineEdit_12->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("sopr_R2");
        xmlWriter.writeAttribute("value", (ui->lineEdit_11->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("ind_L1");
        xmlWriter.writeAttribute("value", (ui->lineEdit_10->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("ind_L2");
        xmlWriter.writeAttribute("value", (ui->lineEdit_9->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("ind_Lm");
        xmlWriter.writeAttribute("value", (ui->lineEdit_8->text()));
        xmlWriter.writeEndElement();
    }
    if(item14->text() == "Автоматический")
    {
        xmlWriter.writeStartElement("koeff_gd");
        xmlWriter.writeAttribute("value", (ui->lineEdit_13->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("koeff_ki");
        xmlWriter.writeAttribute("value", (ui->lineEdit_16->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("koeff_gb");
        xmlWriter.writeAttribute("value", (ui->lineEdit_14->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("koeff_kpsi");
        xmlWriter.writeAttribute("value", (ui->lineEdit_17->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("koeff_gp");
        xmlWriter.writeAttribute("value", (ui->lineEdit_15->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("koeff_gpsi");
        xmlWriter.writeAttribute("value", (ui->lineEdit_18->text()));
        xmlWriter.writeEndElement();
    }
    if(item24->text() == "Фиксированное время")
    {
        xmlWriter.writeStartElement("time_work");
        xmlWriter.writeAttribute("value", (item174->text()));
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();   // Закрываем файл

    if(item68->text() == "Сохранить")
    {
        QFile file2(QString("/home/elf/Видео/ImView2/save/identification.xml"));
        file2.open(QIODevice::WriteOnly);

        //Создаем объект, с помощью которого осуществляется запись в файл
        QXmlStreamWriter xmlWriter2(&file2);
        xmlWriter2.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
        xmlWriter2.writeStartDocument();     // Запускаем запись в документ
        xmlWriter2.writeStartElement("resources");   // Записываем первый элемент с его именем
        xmlWriter2.writeStartElement("identification");  // Записываем тег с именем для первого итема

        xmlWriter2.writeStartElement("stator_resistance");
        xmlWriter2.writeAttribute("value", (ui->lineEdit_12->text()));
        xmlWriter2.writeEndElement();

        xmlWriter2.writeStartElement("rotor_resistance");
        xmlWriter2.writeAttribute("value", (ui->lineEdit_11->text()));
        xmlWriter2.writeEndElement();

        xmlWriter2.writeStartElement("stator_inductance");
        xmlWriter2.writeAttribute("value", (ui->lineEdit_10->text()));
        xmlWriter2.writeEndElement();

        xmlWriter2.writeStartElement("rotor_inductance");
        xmlWriter2.writeAttribute("value", (ui->lineEdit_9->text()));
        xmlWriter2.writeEndElement();

        xmlWriter2.writeStartElement("mutual_inductance");
        xmlWriter2.writeAttribute("value", (ui->lineEdit_8->text()));
        xmlWriter2.writeEndElement();

        xmlWriter2.writeEndElement();
        xmlWriter2.writeEndElement();
        xmlWriter2.writeEndElement();
        xmlWriter2.writeEndDocument();
        file2.close();   // Закрываем файл
    }

    JlCompress::compressDir(str, "../save/");

    sessionFileName = QFileInfo(str).baseName();

    item4->setText(sessionFileName);
}

void MainWindow::LoadProject(QString str)
{
    QDir().mkdir("/tmp/imview");
    JlCompress::extractDir(str,"/tmp/imview");
    QFile file(QString("/tmp/imview/project.xml"));
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Ошибка файла", "Не удалось открыть файл", QMessageBox::Ok);
    }
    else
    {
        ui->tabWidget->show();
        ui->stackedWidget->show();
        ui->switch_regim_upr->show();
        ui->toolBar->show();
        ui->toolBar_2->show();
        ui->statusbar->show();
        ui->widget_15->hide();
        ui->menu_2->menuAction()->setVisible(true);
        ui->menu_3->menuAction()->setVisible(true);
        ui->menu_4->menuAction()->setVisible(true);
        ui->menu_5->menuAction()->setVisible(true);
        ui->save_file->setVisible(true);
        ui->save_as_file->setVisible(true);
        ui->action_save_graph_file->setVisible(true);
        ui->action_close_progect->setVisible(true);
        ui->action_close_session->setVisible(true);
        ui->print_file->setVisible(true);
        ui->print_preview->setVisible(true);

        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        xmlReader.readNext();
        while(!xmlReader.atEnd())
        {
            if(xmlReader.isStartElement())
            {
                if(xmlReader.name() == "project_name")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item4->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_1")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item88->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "project_path")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item106->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_2")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item80->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "project_path_2")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item82->setText(attribute_value);
                        }
                    }
                }                
                else if(xmlReader.name() == "combobox_3")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item68->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_4")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item70->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_5")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item72->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_6")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item74->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_7")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item76->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_8")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item78->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_9")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item14->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "coeff_1")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item94->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "coeff_2")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item96->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "coeff_3")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item98->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "coeff_4")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item100->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "coeff_5")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item102->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "coeff_6")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item104->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_10")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item20->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "time_cikle")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item22->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "time_work")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item176->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_11")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item24->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_12")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item92->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "napragenie")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item130->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "moment")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item132->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "start_temp")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item28->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_13")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item30->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_14")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item141->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_15")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item142->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "time_step")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item107->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "combobox_16")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item34->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "combobox_17")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item36->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "pressure")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item38->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "sopr_R1")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->lineEdit_12->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "sopr_R2")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->lineEdit_11->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "ind_L1")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->lineEdit_10->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "ind_L2")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->lineEdit_9->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "ind_Lm")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->lineEdit_8->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "koeff_gd")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->lineEdit_13->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "koeff_ki")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->lineEdit_16->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "koeff_gb")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->lineEdit_14->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "koeff_kpsi")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->lineEdit_17->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "koeff_gp")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->lineEdit_15->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "koeff_gpsi")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->lineEdit_18->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "time_work")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item174->setText(attribute_value);
                        }
                    }
                }


                if(xmlReader.name() == "selected_row")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            int attribute_value = attr.value().toInt();
                            ui->widget->ui->tableView->selectRow(attribute_value);
                        }
                    }
                }
            }
            xmlReader.readNext(); // Переходим к следующему элементу файла
        }
        file.close(); // Закрываем файл

        if(item68->text() == "Сохранить")
        {
            QXmlStreamReader xmlReader2;
            xmlReader2.setDevice(&file);
            xmlReader2.readNext();
            while(!xmlReader2.atEnd())
            {
                if(xmlReader2.isStartElement())
                {
                    if(xmlReader.name() == "stator_resistance")
                    {
                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                        {
                            if (attr.name().toString() == "value")
                            {
                                QString attribute_value = attr.value().toString();
                                ui->lineEdit_12->setText(attribute_value);
                            }
                        }
                    }
                    if(xmlReader2.name() == "rotor_resistance")
                    {
                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                        {
                            if (attr.name().toString() == "value")
                            {
                                QString attribute_value = attr.value().toString();
                                ui->lineEdit_11->setText(attribute_value);                        }
                        }
                    }
                    if(xmlReader2.name() == "stator_inductance")
                    {
                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                        {
                            if (attr.name().toString() == "value")
                            {
                                QString attribute_value = attr.value().toString();
                                ui->lineEdit_10->setText(attribute_value);
                            }
                        }
                    }
                    if(xmlReader2.name() == "rotor_inductance")
                    {
                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                        {
                            if (attr.name().toString() == "value")
                            {
                                QString attribute_value = attr.value().toString();
                                ui->lineEdit_9->setText(attribute_value);
                            }
                        }
                    }
                    if(xmlReader2.name() == "mutual_inductance")
                    {
                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                        {
                            if (attr.name().toString() == "value")
                            {
                                QString attribute_value = attr.value().toString();
                                ui->lineEdit_8->setText(attribute_value);
                            }
                        }
                    }
                }xmlReader.readNext(); // Переходим к следующему элементу файла

            }file.close();
        }
    }

    sessionFileName = QFileInfo(str).baseName();

    item4->setText(sessionFileName);
    //setWindowTitle(currentTabText + "@" + QString(item4->text()) + QString(" - ImView"));
    setWindowTitle(currentTabText + "@" + QString(item4->text()) + QString(" - ImView"));
    ui->save_file->setEnabled(true);
    ui->save_as_file->setEnabled(true);
    setCurrentFile(str);
    ui->widget_2->ui->plot->load();
}

void MainWindow::switch_regim_upr(bool checked)
{
    if(checked)
    {
        QPixmap pixmap(":/system_icons/data/img/system_icons/go-next.svg");
        QIcon ButtonIcon_1(pixmap);
        ui->switch_regim_upr->setIcon(ButtonIcon_1);
    }
    else
    {
        QPixmap pixmap(":/system_icons/data/img/system_icons/go-previous.svg");
        QIcon ButtonIcon_2(pixmap);
        ui->switch_regim_upr->setIcon(ButtonIcon_2);
    }
}

void MainWindow::onButtonClicked()
{
    ui->stackedWidget->setCurrentIndex( 0 );
}

void MainWindow::onButtonClicked2()
{
    ui->stackedWidget->setCurrentIndex( 6 );
}

void MainWindow::actionresult()
{
    ui->stackedWidget->show();
    ui->stackedWidget->setCurrentIndex( 3 );
}

void MainWindow::actionresultidentf()
{    
    ui->stackedWidget->show();
    ui->stackedWidget->setCurrentIndex( 2 );
}

void MainWindow::tabClicked()
{
    if(ui->tabWidget->currentIndex()==0)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(0);
    }

    if(ui->tabWidget->currentIndex()==1)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(1);
    }

    if(ui->tabWidget->currentIndex()==2)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(8);
    }

    if(ui->tabWidget->currentIndex()==3)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(22);
    }

    if(ui->tabWidget->currentIndex()==4)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(7);
    }

    if(ui->tabWidget->currentIndex()==5)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(16);
    }

    if(ui->tabWidget->currentIndex()==6)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(10);
    }

    if(ui->tabWidget->currentIndex()==7)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(2);
    }

    if(ui->tabWidget->currentIndex()==8)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(12);
    }

    if(ui->tabWidget->currentIndex()==9)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(4);
    }

    if(ui->tabWidget->currentIndex()==6)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(22);
    }
}

void MainWindow::tabClicked_2()
{
    if(ui->widget_5->ui->tabWidget->currentIndex() == 0)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(10);
    }
    if(ui->widget_5->ui->tabWidget->currentIndex() == 1)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(11);
    }
    if(ui->widget_5->ui->tabWidget->currentIndex() == 2)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(9);
    }
    if(ui->widget_5->ui->tabWidget->currentIndex() == 3)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(11);
    }
    if(ui->widget_5->ui->tabWidget->currentIndex() == 4)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(14);
    }
    if(ui->widget_5->ui->tabWidget->currentIndex() == 5)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(15);
    }
}

void MainWindow::tabClicked_3()
{
    if(ui->widget_5->ui->tabWidget_2->currentIndex() == 0)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(9);
    }
    if(ui->widget_5->ui->tabWidget_2->currentIndex() == 1)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(9);
    }
    if(ui->widget_5->ui->tabWidget_2->currentIndex() == 2)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(9);
    }
    if(ui->widget_5->ui->tabWidget_2->currentIndex() == 3)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(9);
    }
}

void MainWindow::tabClicked_4()
{
    if(ui->widget_6->ui->tabWidget->currentIndex() == 0)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(10);
    }
    if(ui->widget_6->ui->tabWidget->currentIndex() == 1)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(17);
    }
    if(ui->widget_6->ui->tabWidget->currentIndex() == 2)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(18);
    }
    if(ui->widget_6->ui->tabWidget->currentIndex() == 3)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(20);
    }
}

void MainWindow::tabClicked_5()
{
    if(ui->tabWidget_3->currentIndex() == 0)
    {
        ui->tabWidget_2->show();
        ui->tabWidget_2->setCurrentIndex(0);
    }
    if(ui->tabWidget_3->currentIndex() == 1)
    {
        ui->tabWidget_2->show();
        ui->tabWidget_2->setCurrentIndex(1);
    }
}

// void MainWindow::tabClicked_6()
// {
//     if(ui->widget_7->ui->tabWidget->currentIndex() == 0)
//     {
//         ui->stackedWidget->show();
//         ui->stackedWidget->setCurrentIndex(12);
//     }
//     if(ui->widget_7->ui->tabWidget->currentIndex() == 1)
//     {
//         ui->stackedWidget->show();
//         ui->stackedWidget->setCurrentIndex(4);
//     }
// }

void MainWindow::setcolorincell(int row, int column)
{
    if ((column == 1) && (row >= 0) && (row <= 3))
    {
        //identf
        QColor chosenColor = QColorDialog::getColor(); //return the color chosen by user
        ui->tableWidget->item(row, column)->setBackground(chosenColor);
        ui->widget_2->ui->plot->setDataLineColor(row, chosenColor);
        dataLineColors[row] = chosenColor;
        repaint();
    }
    if ((column == 1) && (row >= 4) && (row <= 12))
    {
        //electromagn
        QColor chosenColor = QColorDialog::getColor(); //return the color chosen by user
        ui->tableWidget->item(row, column)->setBackground(chosenColor);
        ui->widget_3->ui->plot->setDataLineColor(row - 4, chosenColor);
        dataLineColors[row - 4] = chosenColor;
        repaint();
    }
    if ((column == 1) && (row >= 13) && (row <= 29))
    {
        //trend
        QColor chosenColor = QColorDialog::getColor(); //return the color chosen by user
        ui->tableWidget->item(row, column)->setBackground(chosenColor);
        ui->widget_5->ui->widget_4->ui->plot->setDataLineColor(row - 13, chosenColor);
        dataLineColors[row - 13] = chosenColor;
        repaint();
    }
}

void MainWindow::radioButton_toggled(bool checked)
{
    if (item30->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item30->text() == "Статика (статор)")
        {
            if (checked)
            {
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1115').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">p</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text931').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">z</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text851').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">3</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text867').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">c</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text975').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">л1</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text943').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">п</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1011').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">л2</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1065').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">2</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1097').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">4</tspan>');"));
            }
        }
        else if (item30->text() == "Статика (упрощенный вариант)")
        {
            if (checked)
            {
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1231').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">0</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text827').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">0</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1037').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">0</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1239').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">0</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1007').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">1</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1361').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">2</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text839').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">3</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1145').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">к</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text863').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">с</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text919').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">4</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text939').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">5</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text971').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">в</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text947').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">р</tspan>');"));
           }
        }
        else if (item30->text() == "Статика (полный вариант)")
        {
            if (checked)
            {
                QMessageBox::information(this, "вариант 3!", "Статика (полный вариант)");
            }
        }

        else if (item30->text() == "Двухмассовая модель (расчет)")
        {
            if (checked)
            {
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text947-1').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">0</tspan>');"));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text863-6').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">1</tspan>');"));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text863').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">2</tspan>');"));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text947').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">0</tspan>');"));
           }
        }
    }
}

void MainWindow::radioButton_2_toggled(bool checked)
{
    if (item30->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item30->text() == "Статика (статор)")
        {
            if (checked)
            {
//                teta_p=20;
//                teta_z=50;
//                teta_3=70;
//                teta_c=76;
//                teta_l_1=120;
//                teta_pp=80;
//                teta_l_2=120;
//                teta_2=60;
//                teta_4=40;

                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1115').text('%1 °C');").arg(teta_p,0,'f',2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text931' ).text('%1 °C');").arg(teta_z, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text851').text('%1 °C');").arg(teta_3, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text867').text('%1 °C');").arg(teta_c, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text975').text('%1 °C');").arg(teta_l_1, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text943').text('%1 °C');").arg(teta_pp, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1011' ).text('%1 °C');").arg(teta_l_2, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1065').text('%1 °C');").arg(teta_2, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1097' ).text('%1 °C');").arg(teta_4, 0, 'f', 2));
             }
        }
        if (item30->text() == "Статика (упрощенный вариант)")
        {
            if (checked)
            {
                teta_0=20;
                teta_1=50;
                teta_2=80;
                teta_3=120;
                teta_k=70;
                teta_c=90;
                teta_4=90;
                teta_5=130;
                teta_v=60;
                teta_p=140;

                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1231').text('%1 °C');").arg(teta_0,0,'f',3));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text827' ).text('%1 °C');").arg(teta_0, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1037').text('%1 °C');").arg(teta_0, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1239').text('%1 °C');").arg(teta_0, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1007').text('%1 °C');").arg(teta_1, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1361').text('%1 °C');").arg(teta_2, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text839' ).text('%1 °C');").arg(teta_3, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1145').text('%1 °C');").arg(teta_k, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text863' ).text('%1 °C');").arg(teta_c, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text919' ).text('%1 °C');").arg(teta_4, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text939' ).text('%1 °C');").arg(teta_5, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text971' ).text('%1 °C');").arg(teta_v, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text947' ).text('%1 °C');").arg(teta_p, 0, 'f', 2));
            }
        }
        else if (item30->text() == "Статика (полный вариант)")
        {
            if (checked)
            {
                QMessageBox::information(this, "вариант 3!", "Статика (полный вариант)");
            }
        }
        else if (item30->text() == "Двухмассовая модель (расчет)")
        {
            if (checked)
            {


                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text947-1').text('%1 °C');").arg(teta0_0,0,'f',3));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text863-6').text('%1 °C');").arg(teta0_1,0,'f',3));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text863').text('%1 °C');").arg(teta0_2,0,'f',3));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text947').text('%1 °C');").arg(teta0_0,0,'f',3));
           }
        }
    }
}

void MainWindow::radioButton_3_toggled(bool checked)
{
    if (item30->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item30->text() == "Статика (статор)")
        {
            if (checked)
            {               
//                C_p=0.034;
//                C_z=0.35;
//                C_3=0.23;
//                C_c=0.034;
//                C_l_1=0.067;
//                C_pp=0.067;
//                C_l_2=0.67;
//                C_4=0.56;
//                C_4=0.059;

                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1115').text('%1 Дж/К');").arg(C_p, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text931').text('%1 Дж/К');").arg(C_z, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text851').text('%1 Дж/К');").arg(C_3, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text867').text('%1 Дж/К');").arg(C_c, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text975').text('%1 Дж/К');").arg(C_l_1, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text943').text('%1 Дж/К');").arg(C_pp, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1011').text('%1 Дж/К');").arg(C_l_2, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1065').text('%1 Дж/К');").arg(C_2, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1097').text('%1 Дж/К');").arg(C_4, 0, 'f', 2));
            }
        }
        if (item30->text() == "Статика (упрощенный вариант)")
        {
    if (checked)
    {
        C_0=0.034;
        C_1=0.35;
        C_2=0.23;
        C_3=0.021;
        C_4=0.034;
        C_5=0.067;
        C_k=0.067;
        C_c=0.67;
        C_p=0.56;
        C_v=0.059;

        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1231').text('%1 Дж/К');").arg(C_0, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text827').text('%1 Дж/К');").arg(C_0, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1037').text('%1 Дж/К');").arg(C_0, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1239').text('%1 Дж/К');").arg(C_0, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1007').text('%1 Дж/К');").arg(C_1, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1361').text('%1 Дж/К');").arg(C_2, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text839').text('%1 Дж/К');").arg(C_3, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1145').text('%1 Дж/К');").arg(C_4, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text863').text('%1 Дж/К');").arg(C_5, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text919').text('%1 Дж/К');").arg(C_k, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text939').text('%1 Дж/К');").arg(C_c, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text971').text('%1 Дж/К');").arg(C_p, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text947').text('%1 Дж/К');").arg(C_v, 0, 'f', 2));
    }
        }
        else if (item30->text() == "Статика (полный вариант)")
        {
            if (checked)
            {
                QMessageBox::information(this, "вариант 3!", "Статика (полный вариант)");
            }
        }
        else if (item30->text() == "Двухмассовая модель (расчет)")
        {
            if (checked)
            {

                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text863-6').text('%1 Дж/К');").arg(C0_0,0,'f',3));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text863').text('%1 Дж/К');").arg(C0_1,0,'f',3));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text947-1').hide();"));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text947').hide();"));
           }
            else
            {
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text947-1').show();"));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text947').show();"));
            }
        }
    }
}

void MainWindow::radioButton_4_toggled(bool checked)
{
    if (item30->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item30->text() == "Статика (статор)")
        {
            if (checked)
            {
//                P_p=20;
//                P_z=100;
//                P_3=120;
//                P_c=502;
//                P_l_1=67;
//                P_pp=76;
//                P_l_2=120;
//                P_2=56;
//                P_4=59;

                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1115').text('%1 Вт');").arg(P_p, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text931').text('%1 Вт');").arg(P_z, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text851').text('%1 Вт');").arg(P_3, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text867').text('%1 Вт');").arg(P_c, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text975').text('%1 Вт');").arg(P_l_1, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text943').text('%1 Вт');").arg(P_pp, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1011').text('%1 Вт');").arg(P_l_2, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1065').text('%1 Вт');").arg(P_2, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1097').text('%1 Вт');").arg(P_4, 0, 'f', 2));
            }
        }
        if (item30->text() == "Статика (упрощенный вариант)")
        {
            if (checked)
            {

                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1231').text('%1 Вт');").arg(P_0, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text827'). text('%1 Вт');").arg(P_0, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1037').text('%1 Вт');").arg(P_0, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1239').text('%1 Вт');").arg(P_0, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1007').text('%1 Вт');").arg(P_1, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1361').text('%1 Вт');").arg(P_2, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text839'). text('%1 Вт');").arg(P_3, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1145').text('%1 Вт');").arg(P_4, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text863'). text('%1 Вт');").arg(P_5, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text919'). text('%1 Вт');").arg(P_k, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text939'). text('%1 Вт');").arg(P_c, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text971'). text('%1 Вт');").arg(P_p, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text947'). text('%1 Вт');").arg(P_v, 0, 'f', 2));

            }
        }
        else if (item30->text() == "Статика (полный вариант)")
        {
            if (checked)
            {
                QMessageBox::information(this, "вариант 3!", "Статика (полный вариант)");
            }
        }
        else if (item30->text() == "Двухмассовая модель (расчет)")
        {
            if (checked)
            {
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text863-6').text('%1 Вт');").arg(P_1,0,'f',3));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text863').text('%1 Вт');").arg(P_2,0,'f',3));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text947-1').hide();"));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text947').hide();"));
           }
            else
            {
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text947-1').show();"));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text947').show();"));
            }
        }
    }
}

void MainWindow::radioButton_5_toggled(bool checked)
{
    if (item30->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item30->text() == "Статика (статор)")
        {
            if (checked)
            {
//                lambda_zp=0.034;
//                lambda_zc=0.35;
//                lambda_c3=0.23;
//                lambda_pc=0.021;
//                lambda_pz=0.034;
//                lambda_l2c=0.067;
//                lambda_l14=0.067;
//                lambda_pl1=0.67;
//                lambda_pl2=0.56;

                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1131').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">zр</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text891').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">zc</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text843').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">c3</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text915').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">пс</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text993').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">пz</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1053').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">л22</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1085').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">л14</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text967').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">пл1</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1029').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">пл2</tspan>');"));
            }
        }
        else if (item30->text() == "Статика (упрощенный вариант)")
        {
            if (checked)
            {
//                lambda_10=0.034;
//                lambda_30=0.034;
//                lambda_k0=0.34;
//                lambda_50=0.93;
//                lambda_3k=0.67;
//                lambda_21=0.35;
//                lambda_c2=0.23;
//                lambda_c3=0.067;
//                lambda_c4=0.56;
//                lambda_45=0.56;
//                lambda_pc=0.067;
//                lambda_pb=0.059;
//                lambda_b5=0.043;
//                lambda_p5=0.0045;
//                lambda_p2=0.021;

                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1223').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">10</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text883').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">30</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1195').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">к0</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1113').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">50</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1153').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">3к</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1025').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">21</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1053').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">с2</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text891').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">с3</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1101').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">с4</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1093').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">45</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1065').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">рс</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1073').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">рв</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1081').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">в5</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1253').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">р5</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1171').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">р2</tspan>');"));
            }
        }
        else if (item30->text() == "Статика (полный вариант)")
        {
            if (checked)
            {
                QMessageBox::information(this, "вариант 3!", "Статика (полный вариант)");
            }
        }
        else if (item30->text() == "Двухмассовая модель (расчет)")
        {
            if (checked)
            {
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text1065-6').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">10</tspan>');"));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text1053').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">12</tspan>');"));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text1065').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">20</tspan>');"));
            }
        }
    }
}

void MainWindow::radioButton_6_toggled(bool checked)
{
    if (item30->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item30->text() == "Статика (статор)")
        {
            if (checked)
            {
//                lambda_zp=0.034;
//                lambda_zc=0.35;
//                lambda_c3=0.23;
//                lambda_pc=0.021;
//                lambda_pz=0.034;
//                lambda_l22=0.067;
//                lambda_l14=0.067;
//                lambda_pl1=0.67;
//                lambda_pl2=0.56;

                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1131').text('%1 Вт/°C');").arg(lambda_zp, 0, 'f', 3));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text891'). text('%1 Вт/°C');").arg(lambda_zc, 0, 'f', 3));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text843'). text('%1 Вт/°C');").arg(lambda_c3, 0, 'f', 3));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text915'). text('%1 Вт/°C');").arg(lambda_pс, 0, 'f', 3));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text993'). text('%1 Вт/°C');").arg(lambda_pz, 0, 'f', 3));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1053').text('%1 Вт/°C');").arg(lambda_l22, 0, 'f', 3));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1085').text('%1 Вт/°C');").arg(lambda_l14, 0, 'f', 3));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text967'). text('%1 Вт/°C');").arg(lambda_pl1, 0, 'f', 3));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1029').text('%1 Вт/°C');").arg(lambda_pl2, 0, 'f', 3));
            }
        }
        else if (item30->text() == "Статика (упрощенный вариант)")
        {
            if (checked)
            {
                //                lambda_10=0.034;
                //                lambda_30=0.034;
                //                lambda_k0=0.34;
                //                lambda_50=0.93;
                //                lambda_3k=0.67;
                //                lambda_21=0.35;
                //                lambda_c2=0.23;
                //                lambda_c3=0.067;
                //                lambda_c4=0.56;
                //                lambda_45=0.56;
                //                lambda_pc=0.067;
                //                lambda_pb=0.059;
                //                lambda_b5=0.043;
                //                lambda_p5=0.0045;
                //                lambda_p2=0.021;
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1223').text('%1 Вт/°C');").arg(lambda_10, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text883' ).text('%1 Вт/°C');").arg(lambda_30, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1195').text('%1 Вт/°C');").arg(lambda_k0, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1113').text('%1 Вт/°C');").arg(lambda_50, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1153').text('%1 Вт/°C');").arg(lambda_3k, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1025').text('%1 Вт/°C');").arg(lambda_21, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1053').text('%1 Вт/°C');").arg(lambda_c2, 0, 'f', 2));

                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text891' ).text('%1 Вт/°C');").arg(lambda_c3, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1101').text('%1 Вт/°C');").arg(lambda_c4, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1093').text('%1 Вт/°C');").arg(lambda_45, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1065').text('%1 Вт/°C');").arg(lambda_pc, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1073').text('%1 Вт/°C');").arg(lambda_pb, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1253').text('%1 Вт/°C');").arg(lambda_b5, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1171').text('%1 Вт/°C');").arg(lambda_p5, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1081').text('%1 Вт/°C');").arg(lambda_p2, 0, 'f', 2));
            }
        }
        else if (item30->text() == "Статика (полный вариант)")
        {
            if (checked)
            {
                QMessageBox::information(this, "вариант 3!", "Статика (полный вариант)");
            }
        }
        else if (item30->text() == "Двухмассовая модель (расчет)")
        {
            if (checked)
            {
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text1065-6').text('%1 Вт/°C');").arg(lambda0_10, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text1053').text('%1 Вт/°C');").arg(lambda0_12, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text1065').text('%1 Вт/°C');").arg(lambda0_20, 0, 'f', 2));
            }
        }
    }
}

void MainWindow::radioButton_7_toggled(bool checked)
{
    if (item30->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item30->text() == "Статика (статор)")
        {
            if (checked)
            {
//                dP_zp=100;
//                dP_zc=220;
//                dP_c3=230;
//                dP_pс=450;
//                dP_pz=120;
//                dP_l22=340;
//                dP_l14=560;
//                dP_pl1=506;
//                dP_pl2=760;

                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1131').text('%1 Вт');").arg(dP_zp, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text891').text('%1 Вт);").arg(dP_zc, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text843').text('%1 Вт');").arg(dP_c3, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text915').text('%1 Вт');").arg(dP_pс, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text993').text('%1 Вт');").arg(dP_pz, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1053').text('%1 Вт');").arg(dP_l22, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1085').text('%1 Вт');").arg(dP_l14, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text967').text('%1 Вт');").arg(dP_pl1, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1029').text('%1 Вт');").arg(dP_pl2, 0, 'f', 2));
            }
        }
        else if (item30->text() == "Статика (упрощенный вариант)")
        {
            if (checked)
            {
//                P_10=100;
//                P_30=220;
//                P_k0=230;
//                P_50=450;
//                P_3k=120;
//                P_21=340;
//                P_c2=560;
//                P_c3=506;
//                P_c4=760;
//                P_45=100;
//                P_pc=220;
//                P_pb=230;
//                P_b5=450;
//                P_p5=120;
//                P_p2=340;

                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1223').text('%1 °C');").arg(P_10, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text883').text('%1 °C');").arg(P_30, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1195').text('%1 °C');").arg(P_k0, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1113').text('%1 °C');").arg(P_50, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1153').text('%1 °C');").arg(P_3k, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1025').text('%1 °C');").arg(P_21, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1053').text('%1 °C');").arg(P_c2, 0, 'f', 2));

                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text891').text('%1 °C');").arg(P_c3, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1101').text('%1 °C');").arg(P_c4, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1093').text('%1 °C');").arg(P_45, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1065').text('%1 °C');").arg(P_pc, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1073').text('%1 °C');").arg(P_pb, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1081').text('%1 °C');").arg(P_b5, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1253').text('%1 °C');").arg(P_p5, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1171').text('%1 °C');").arg(P_p2, 0, 'f', 2));
            }
        }
        else if (item30->text() == "Статика (полный вариант)")
        {
            if (checked)
            {
                QMessageBox::information(this, "вариант 3!", "Статика (полный вариант)");
            }
        }
        else if (item30->text() == "Двухмассовая модель (расчет)")
        {
            if (checked)
            {
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text1065-6').text('%1 Вт');").arg(lambda0_10, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text1053').text('%1 Вт');").arg(lambda0_12, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text1065').text('%1 Вт');").arg(lambda0_20, 0, 'f', 2));
            }
        }
    }
}

void MainWindow::radioButton_8_toggled(bool checked)
{
    if (item30->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item30->text() == "Статика (статор)")
        {
            if (checked)
            {
//                d_teta_zp=10;
//                d_teta_zc=5;
//                d_teta_c3=20;
//                d_teta_pc=30;
//                d_teta_pz=15;
//                d_teta_l22=10;
//                d_teta_l14=5;
//                d_teta_pl1=35;
//                d_teta_pl2=35;

                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1131').text('%1 °C');").arg(d_teta_zp, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text891').text('%1 °C');").arg(d_teta_zc, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text843').text('%1 °C');").arg(d_teta_c3, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text915').text('%1 °C');").arg(d_teta_pc, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text993').text('%1 °C');").arg(d_teta_pz, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1053').text('%1 °C');").arg(d_teta_l22, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1085').text('%1 °C');").arg(d_teta_l14, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text967').text('%1 °C');").arg(d_teta_pl1, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1029').text('%1 °C');").arg(d_teta_pl2, 0, 'f', 2));
            }
        }
        if (item30->text() == "Статика (упрощенный вариант)")
        {
            if (checked)
            {
                //                d_teta_10=100;
                //                d_teta_30=220;
                //                d_teta_k0=230;
                //                d_teta_50=450;
                //                d_teta_3k=120;
                //                d_teta_21=340;
                //                d_teta_c2=560;
                //                d_teta_c3=506;
                //                d_teta_c4=760;
                //                d_teta_45=100;
                //                d_teta_pc=220;
                //                d_teta_pb=230;
                //                d_teta_b5=450;
                //                d_teta_p5=120;
                //                d_teta_p2=340;

                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1223').text('%1 Вт');").arg(d_teta_10, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text883').text('%1 Вт');").arg(d_teta_30, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1195').text('%1 Вт');").arg(d_teta_k0, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1113').text('%1 Вт');").arg(d_teta_50, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1153').text('%1 Вт');").arg(d_teta_3k,0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1025').text('%1 Вт');").arg(d_teta_21, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1053').text('%1 Вт');").arg(d_teta_c2, 0, 'f', 2));

                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text891').text('%1 Вт');").arg(d_teta_c3, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1101').text('%1 Вт');").arg(d_teta_c4, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1093').text('%1 Вт');").arg(d_teta_45, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1065').text('%1 Вт');").arg(d_teta_pc, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1073').text('%1 Вт');").arg(d_teta_pb, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1081').text('%1 Вт');").arg(d_teta_b5, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1253').text('%1 Вт');").arg(d_teta_p5, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1171').text('%1 Вт');").arg(d_teta_p2, 0, 'f', 2));
            }
        }
        else if (item30->text() == "Статика (полный вариант)")
        {
            if (checked)
            {
                QMessageBox::information(this, "вариант 3!", "Статика (полный вариант)");
            }
        }
        else if (item30->text() == "Двухмассовая модель (расчет)")
        {
            if (checked)
            {
                d_teta0_10=100;
                d_teta0_12=220;
                d_teta0_20=230;
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text1065-6').text('%1 Вт');").arg(d_teta0_10, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text1053').text('%1 Вт');").arg(d_teta0_12, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text1065').text('%1 Вт');").arg(d_teta0_20, 0, 'f', 2));
            }
        }
    }
}

void MainWindow::radioButton_9_toggled(bool checked)
{
    if (item30->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item30->text() == "Статика (статор)")
        {
            if (checked)
            {
                //ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1131').hide();"));

                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1115').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text931').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text851').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text867').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text975').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text943').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1011').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1065').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1097').hide();"));
            }
            else
            {
                //ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1131').show();"));

                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1115').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text931').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text851').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text867').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text975').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text943').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1011').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1065').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1097').show();"));

            }
        }
        else if (item30->text() == "Статика (упрощенный вариант)")
        {
            if (checked)
            {
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1231').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text827').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1037').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1239').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1007').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1361').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text839').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1145').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text863').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text919').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text939').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text971').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text947').hide();"));
            }
            else
            {
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1231').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text827').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1037').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1239').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1007').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1361').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text839').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1145').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text863').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text919').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text939').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text971').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text947').show();"));
            }
        }
        else if (item30->text() == "Статика (полный вариант)")
        {
            if (checked)
            {
                QMessageBox::information(this, "вариант 3!", "Статика (полный вариант)");
            }
        }
        else if (item30->text() == "Двухмассовая модель (расчет)")
        {
            if (checked)
            {
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text947-1').hide();"));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text863-6').hide();"));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text863').hide();"));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text947').hide();"));
           }
            else
            {
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text947-1').show();"));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text863-6').show();"));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text863').show();"));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text947').show();"));
            }
        }
    }
}

void MainWindow::radioButton_10_toggled(bool checked)
{
    if (item30->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item30->text() == "Статика (статор)")
        {
            if (checked)
            {
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1131').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text891').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text843').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text915').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text993').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1053').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1085').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text967').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1029').hide();"));
            }
            else
            {
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1131').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text891').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text843').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text915').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text993').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1053').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1085').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text967').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1029').show();"));
            }
        }
        else if (item30->text() == "Статика (упрощенный вариант)")
        {
            if (checked)
            {
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1223').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text883').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1195').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1113').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1153').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1025').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1053').hide();"));

                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text891').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1101').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1093').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1065').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1073').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1081').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1253').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1171').hide();"));
            }
            else
            {
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1223').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text883').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1195').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1113').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1153').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1025').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1053').show();"));

                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text891').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1101').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1093').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1065').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1073').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1081').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1253').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1171').show();"));
            }
        }
        else if (item30->text() == "Статика (полный вариант)")
        {
            if (checked)
            {
                QMessageBox::information(this, "вариант 3!", "Статика (полный вариант)");
            }
        }
        else if (item30->text() == "Двухмассовая модель (расчет)")
        {
            if (checked)
            {
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text1065-6').hide();"));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text1053').hide();"));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text1065').hide();"));
            }
            else
            {
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text1065-6').show();"));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text1053').show();"));
                ui->widget_5->ui->webEngineView_3->page()->runJavaScript(QString("$('#text1065').show();"));
            }
        }
    }
}

void MainWindow::on_save_tepl_dannie_clicked()
{
    QString filter = "Файл конфигурации тепловых данных (*.xml);;Все файлы (*.*)";
    QString str = QFileDialog::getSaveFileName(this, "Выбрать имя, под которым сохранить данные", "../save", filter);

   // QFile file(QString("/home/elf/ImView/data/tepl.xml"));
    QFile file(str);
    file.open(QIODevice::WriteOnly);

    //Создаем объект, с помощью которого осуществляется запись в файл
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
    xmlWriter.writeStartDocument();     // Запускаем запись в документ
    xmlWriter.writeStartElement("resources");   // Записываем первый элемент с его именем
    xmlWriter.writeStartElement("tepl_dannie");  // Записываем тег с именем для первого итема

    xmlWriter.writeStartElement("general_settings");

    xmlWriter.writeStartElement("sinxr_scorost");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(0,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("kol-vo_par_polusov");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(1,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("visota_osi_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(2,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("diametr_staniny_v_osnovanii_reber");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(3,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("dlina_staniny_so_storony_privoda");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(4,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("dlina_staniny_so_storony_ventilatora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(5,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("zazor_megdu_diffuzorom_i_schitom");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(6,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("kolichestvo_reber_staniny");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(7,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("visota_rebra_staniny");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(8,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("tolschina_rebra_staniny");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(9,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("vneshny_diametr_ventilatora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(10,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("vneshny_diametr_serdechnika_statora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(11,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("vnutrenny_diametr_serdechnika_statora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(12,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("dlina_paza");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(13,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("chislo_pazov_statora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(14,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koef-t_shtrichovki");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(15,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("bolshaya_shirina_paza");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(16,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("menshaya_shirina_paza");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(17,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("visota_paza");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(18,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("shirina_slica");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(19,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("visota_zubca");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(20,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("shirina_zubca");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(21,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("kol-vo_vitkov_v_obmotke_statore");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(22,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("chislo_parallelnych_vetvey");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(23,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("srednaja_dlina_obmotki");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(24,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("dlina_vileta_lobovoi_chasti_obmotki");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(25,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koef-t_propitki_obmotki");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(26,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("tolshina_okraski_obmotki_v_lobovoi_chasty");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(27,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("tolschina_pazovoi_izolacii");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(28,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("vneshniy_diametr_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(29,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("chislo_pazov_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(30,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("shirina_korotkozamakauchego_kolca");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(31,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("visota_korotkozamakauchego_kolca");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(32,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("shirina_lopatki_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(33,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("visota_lopatki_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(34,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("kol-vo_lopatok_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(35,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koef-t_kachestva_lopatki");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(36,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("tolschina_zazora_megdu_statorom_i_rotorom");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(37,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("kinematicheskaja_vaskost_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(38,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("chtlyaja_temperatura_obmotki");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(39,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koeff-t_teploprovodnosty_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(40,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koeff-t_teploprovodnosty_medi");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(41,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koeff-t_teploprovodnosty_alumimia");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(42,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koeff-t_teploprovodnosty_stali_statora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(43,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("diametr_provoda_bez_izolacii");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(44,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("diametr_izolirovannogo_provoda");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(45,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koefficient_propitki_obmotki");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(46,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koef-t_teploprovodnosty_propitochnogo_sostava");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(47,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koef-t_teploprovodnosty_izolacii_provodnikov");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(48,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("vneshnid_diametr_lobovoi_chasti");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(49,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koefft_teploprovodnosti_okraski_obmotki_v_lobovoi_chasti");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(50,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koefft_teploprovodnosty_izolacii_provodnikov_2");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(51,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("tolshina_vozdushnych_prosloek");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(52,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("visota_zubca_3");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(53,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("srednaja_shirina_zubca");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(54,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("diametr_okrugnosti_kasatelnoi_k_dnu_pazov");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(55,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("bolshaja_shirina_paza");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(56,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("menshaja_shirina_paza");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(57,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("visota_paza_2");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(58,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koef-t_kachestva_lopatki_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(59,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("shag_reber_staniny");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(60,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("chislo_faz_statora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(61,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("kol-vo_elementarnych_provodnikov");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(62,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("plotnost_medi");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(63,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("udelnaja_teploemkost_medi_obmotki_statora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(64,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("plotnost_stali");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(65,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("udelnaja_teploemkost_medi_stali");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(66,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("udelnaje_soprotivlenie_medi");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(67,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("poleznaja_mochnost");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(68,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("napragenie_pitanija");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(69,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koefficient_poleznogo_deistvia");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(70,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koefficient_mochnosti");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(71,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("udelnaje_soprotivlenie_aluminia");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(72,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("srednij_diametr_korotkozamykauchego_kolca");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(73,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("obmotochny_koefficient_obmotki_statora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(74,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koefficient_ckosa_pazov");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(75,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();   // Закрываем файл

    //JlCompress::compressDir(str, "/home/elf/ImView/data/");
}

void MainWindow::on_save_Vent_dannie_clicked()
{
    QString filter2 = "Файл конфигурации вентиляционных данных (*.xml);;Все файлы (*.*)";
    QString str2 = QFileDialog::getSaveFileName(this, "Выбрать имя, под которым сохранить данные", "../save", filter2);

   // QFile file(QString("/home/elf/ImView/data/vent.xml"));
    QFile file(str2);
    file.open(QIODevice::WriteOnly);

    //Создаем объект, с помощью которого осуществляется запись в файл
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
    xmlWriter.writeStartDocument();     // Запускаем запись в документ
    xmlWriter.writeStartElement("resources");   // Записываем первый элемент с его именем
    xmlWriter.writeStartElement("vent_dannie");  // Записываем тег с именем для первого итема

    xmlWriter.writeStartElement("general_settings");

    xmlWriter.writeStartElement("intenal_diameter_ventilator");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(0,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("extenal_diameter_ventilator");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(1,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("shirina_lopatki_ventilatora");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(2,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("chastota_vrasachenia_ventilatora");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(3,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("plotnost_vozducha");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(4,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("summarnaja_ploschad_otverstiy_v_setke_kogucha");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(5,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Obchaja_ploschad_setki_kogucha");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(6,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Ploschad_sechenia_v_meste_povorota_k_rabochemu_kolesu");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(7,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Ugol_povorota_potoka_k_vchodnim_kromkam_lopatok_rabochego_kolesa");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(8,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Ploschad_sechenia_v_meste_povorota_pered_vchodom_v_megrebernye_kanaly");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(9,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Ugol_povorota_potoka_pered_vhodom_v_megrebernye_kanaly");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(10,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Ploschad_sechenia_pered_vhodom_v_megrebernye_kanaly");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(11,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Ploschad_sechenia_megrebernyh_kanalov_ot_staniny_do_koguha_ventilatora");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(12,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Ugol_natekania_potoka_na_rebra_staniny");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(13,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Ugol_povorota_potoka_v_megrebernych_kanalah");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(14,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();   // Закрываем файл

    //JlCompress::compressDir(str, "/home/elf/ImView/data/");
}


void MainWindow::on_load_tepl_dannie_clicked()
{
    QString filter = "Файл конфигурации тепловых данных (*.xml);;Все файлы (*.*)";
    QString str = QFileDialog::getOpenFileName(this, "Выбрать имя, под которым сохранить данные", "/tmp/imview", filter);
    LoadTeplDannie(str);
}

void MainWindow::LoadTeplDannie(QString str)
{
//    QDir().mkdir("/tmp/imview");
//    JlCompress::extractDir(str,"/tmp/imview");


    QFile file(str);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Ошибка файла", "Не удалось открыть файл", QMessageBox::Ok);
    }
    else
    {
        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        xmlReader.readNext();
        while(!xmlReader.atEnd())
        {
            if(xmlReader.isStartElement())
            {
                if(xmlReader.name() == "sinxr_scorost")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(0,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "kol-vo_par_polusov")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(1,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "visota_osi_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(2,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "diametr_staniny_v_osnovanii_reber")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(3,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "dlina_staniny_so_storony_privoda")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(4,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "dlina_staniny_so_storony_ventilatora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(5,1)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "zazor_megdu_diffuzorom_i_schitom")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(6,1)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "kolichestvo_reber_staniny")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(7,1)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "visota_rebra_staniny")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(8,1)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "tolschina_rebra_staniny")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(9,1)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "vneshny_diametr_ventilatora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(10,1)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "vneshny_diametr_serdechnika_statora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(11,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "vnutrenny_diametr_serdechnika_statora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(12,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "dlina_paza")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(13,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "chislo_pazov_statora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(14,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koef-t_shtrichovki")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(15,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "bolshaya_shirina_paza")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(16,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "menshaya_shirina_paza")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(17,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "visota_paza")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(18,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "shirina_slica")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(19,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "visota_zubca")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(20,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "shirina_zubca")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(21,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "kol-vo_vitkov_v_obmotke_statore")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(22,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "chislo_parallelnych_vetvey")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(23,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "srednaja_dlina_obmotki")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(24,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "dlina_vileta_lobovoi_chasti_obmotki")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(25,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koef-t_propitki_obmotki")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(26,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "tolshina_okraski_obmotki_v_lobovoi_chasty")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(27,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "tolschina_pazovoi_izolacii")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(28,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "vneshniy_diametr_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(29,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "chislo_pazov_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(30,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "shirina_korotkozamakauchego_kolca")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(31,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "visota_korotkozamakauchego_kolca")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(32,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "shirina_lopatki_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(33,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "visota_lopatki_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(34,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "kol-vo_lopatok_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(35,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koef-t_kachestva_lopatki")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(36,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "tolschina_zazora_megdu_statorom_i_rotorom")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(37,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "kinematicheskaja_vaskost_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(38,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "chtlyaja_temperatura_obmotki")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(39,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koeff-t_teploprovodnosty_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(40,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koeff-t_teploprovodnosty_medi")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(41,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koeff-t_teploprovodnosty_alumimia")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(42,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koeff-t_teploprovodnosty_stali_statora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(43,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "diametr_provoda_bez_izolacii")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(44,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "diametr_izolirovannogo_provoda")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(45,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koefficient_propitki_obmotki")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(46,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koef-t_teploprovodnosty_propitochnogo_sostava")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(47,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koef-t_teploprovodnosty_izolacii_provodnikov")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(48,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "vneshnid_diametr_lobovoi_chasti")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(49,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koefft_teploprovodnosti_okraski_obmotki_v_lobovoi_chasti")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(50,1)->setText(attribute_value);
                            //qDebug() << attribute_value;
                        }
                    }
                }
                else if(xmlReader.name() == "koefft_teploprovodnosty_izolacii_provodnikov_2")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(51,1)->setText(attribute_value);
                            //qDebug() << attribute_value;
                        }
                    }
                }
                else if(xmlReader.name() == "tolshina_vozdushnych_prosloek")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(52,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "visota_zubca_3")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(53,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "srednaja_shirina_zubca")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(54,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "diametr_okrugnosti_kasatelnoi_k_dnu_pazov")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(55,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "bolshaja_shirina_paza")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(56,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "menshaja_shirina_paza")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(57,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "visota_paza_2")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(58,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koef-t_kachestva_lopatki_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(59,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "shag_reber_staniny")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(60,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "chislo_faz_statora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(61,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "kol-vo_elementarnych_provodnikov")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(62,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "plotnost_medi")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(63,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "udelnaja_teploemkost_medi_obmotki_statora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(64,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "plotnost_stali")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(65,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "udelnaja_teploemkost_medi_stali")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(66,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "udelnaje_soprotivlenie_medi")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(67,1)->setText(attribute_value);
                        }
                    }
                }
            else if(xmlReader.name() == "poleznaja_mochnost")
            {
                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                {
                    if (attr.name().toString() == "value")
                    {
                        QString attribute_value = attr.value().toString();
                        ui->widget_5->ui->widget_2->ui->tableWidget->item(68,1)->setText(attribute_value);
                    }
                }
            }
            else if(xmlReader.name() == "napragenie_pitanija")
            {
                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                {
                    if (attr.name().toString() == "value")
                    {
                        QString attribute_value = attr.value().toString();
                        ui->widget_5->ui->widget_2->ui->tableWidget->item(69,1)->setText(attribute_value);
                    }
                }
            }
            else if(xmlReader.name() == "koefficient_poleznogo_deistvia")
            {
                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                {
                    if (attr.name().toString() == "value")
                    {
                        QString attribute_value = attr.value().toString();
                        ui->widget_5->ui->widget_2->ui->tableWidget->item(70,1)->setText(attribute_value);
                    }
                }
            }
            else if(xmlReader.name() == "koefficient_mochnosti")
            {
                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                {
                    if (attr.name().toString() == "value")
                    {
                        QString attribute_value = attr.value().toString();
                        ui->widget_5->ui->widget_2->ui->tableWidget->item(71,1)->setText(attribute_value);
                    }
                }
            }
            else if(xmlReader.name() == "udelnaje_soprotivlenie_aluminia")
            {
                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                {
                    if (attr.name().toString() == "value")
                    {
                        QString attribute_value = attr.value().toString();
                        ui->widget_5->ui->widget_2->ui->tableWidget->item(72,1)->setText(attribute_value);
                    }
                }
            }
            else if(xmlReader.name() == "srednij_diametr_korotkozamykauchego_kolca")
            {
                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                {
                    if (attr.name().toString() == "value")
                    {
                        QString attribute_value = attr.value().toString();
                        ui->widget_5->ui->widget_2->ui->tableWidget->item(73,1)->setText(attribute_value);
                    }
                }
            }
            else if(xmlReader.name() == "obmotochny_koefficient_obmotki_statora")
            {
                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                {
                    if (attr.name().toString() == "value")
                    {
                        QString attribute_value = attr.value().toString();
                        ui->widget_5->ui->widget_2->ui->tableWidget->item(74,1)->setText(attribute_value);
                    }
                }
            }
            else if(xmlReader.name() == "koefficient_ckosa_pazov")
            {
                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                {
                    if (attr.name().toString() == "value")
                    {
                        QString attribute_value = attr.value().toString();
                        ui->widget_5->ui->widget_2->ui->tableWidget->item(75,1)->setText(attribute_value);
                    }
                }
            }
        }
        xmlReader.readNext(); // Переходим к следующему элементу файла
     }
        file.close(); // Закрываем файл
  }
}

void MainWindow::on_load_Vent_dannie_clicked()
{
    QString filter = "Файл конфигурации тепловых данных (*.xml);;Все файлы (*.*)";
    QString str = QFileDialog::getOpenFileName(this, "Выбрать имя, под которым сохранить данные", "/tmp/imview", filter);
    LoadVentDannie(str);
}

void MainWindow::LoadVentDannie(QString str)
{
    //    QDir().mkdir("/tmp/imview");
    //    JlCompress::extractDir(str,"/tmp/imview");

    QFile file(str);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Ошибка файла", "Не удалось открыть файл", QMessageBox::Ok);
    }
    else
    {
        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        xmlReader.readNext();
        while(!xmlReader.atEnd())
        {
            if(xmlReader.isStartElement())
            {
                if(xmlReader.name() == "intenal_diameter_ventilator")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(0,2)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "extenal_diameter_ventilator")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(1,2)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "shirina_lopatki_ventilatora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(2,2)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "chastota_vrasachenia_ventilatora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(3,2)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "plotnost_vozducha")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(4,2)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "summarnaja_ploschad_otverstiy_v_setke_kogucha")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(5,2)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "Obchaja_ploschad_setki_kogucha")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(6,2)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "Ploschad_sechenia_v_meste_povorota_k_rabochemu_kolesu")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(7,2)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "Ugol_povorota_potoka_k_vchodnim_kromkam_lopatok_rabochego_kolesa")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(8,2)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "Ploschad_sechenia_v_meste_povorota_pered_vchodom_v_megrebernye_kanaly")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(9,2)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "Ugol_povorota_potoka_pered_vhodom_v_megrebernye_kanaly")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(10,2)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "Ploschad_sechenia_pered_vhodom_v_megrebernye_kanaly")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(11,2)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "Ploschad_sechenia_megrebernyh_kanalov_ot_staniny_do_koguha_ventilatora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(12,2)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "Ugol_natekania_potoka_na_rebra_staniny")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(13,2)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "Ugol_povorota_potoka_v_megrebernych_kanalah")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(14,2)->setText(attribute_value);
                        }
                    }
                }
            }
            xmlReader.readNext(); // Переходим к следующему элементу файла
        }
        file.close(); // Закрываем файл
    }
}


void MainWindow::on_tepl_result_clicked()
{
    if (item30->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item30->text() == "Статика (статор)")
        {
            ui->widget_5->ui->tabWidget->show();
            ui->widget_5->ui->tabWidget->setCurrentIndex(11);

            //СЧИТЫВАНИЕ ИСХОДНЫХ ДАННЫХ

            base_tepl.Da1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(0,1)->text().toDouble();
            base_tepl.Ha1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(1,1)->text().toDouble();
            base_tepl.lambda_c1       = ui->widget_5->ui->widget_2->ui->tableWidget->item(2,1)->text().toDouble();
            base_tepl.L1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(3,1)->text().toDouble();
            base_tepl.delta_ct = ui->widget_5->ui->widget_2->ui->tableWidget->item(4,1)->text().toDouble();
            base_tepl.lambda_ct   = ui->widget_5->ui->widget_2->ui->tableWidget->item(5,1)->text().toDouble();
            base_tepl.lambda_i  = ui->widget_5->ui->widget_2->ui->tableWidget->item(6,1)->text().toDouble();
            base_tepl.delta_ai     = ui->widget_5->ui->widget_2->ui->tableWidget->item(7,1)->text().toDouble();
            base_tepl.Kc1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(8,1)->text().toDouble();
            base_tepl.Di1   = ui->widget_5->ui->widget_2->ui->tableWidget->item(9,1)->text().toDouble();

            base_tepl.Z1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(10,1)->text().toDouble();
            base_tepl.Bz1       = ui->widget_5->ui->widget_2->ui->tableWidget->item(11,1)->text().toDouble();
            base_tepl.lambda_с     = ui->widget_5->ui->widget_2->ui->tableWidget->item(12,1)->text().toDouble();
            base_tepl.Hz1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(13,1)->text().toDouble();
            base_tepl.lambda_ip1    = ui->widget_5->ui->widget_2->ui->tableWidget->item(14,1)->text().toDouble();
            base_tepl.delta_ip1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(15,1)->text().toDouble();
            base_tepl.d1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(16,1)->text().toDouble();
            base_tepl.Kz     = ui->widget_5->ui->widget_2->ui->tableWidget->item(17,1)->text().toDouble();
            //base_tepl.delta     = ui->widget_5->ui->widget_2->ui->tableWidget->item(18,1)->text().toDouble();
            //base_tepl.lambda_ekv   = ui->widget_5->ui->widget_2->ui->tableWidget->item(19,1)->text().toDouble();

            base_tepl.Bp   = ui->widget_5->ui->widget_2->ui->tableWidget->item(20,1)->text().toDouble();
            base_tepl.sigma_ipr    = ui->widget_5->ui->widget_2->ui->tableWidget->item(21,1)->text().toDouble();
            base_tepl.teta_m     = ui->widget_5->ui->widget_2->ui->tableWidget->item(22,1)->text().toDouble();
            base_tepl.Kp     = ui->widget_5->ui->widget_2->ui->tableWidget->item(23,1)->text().toDouble();
            //base_tepl.Kp2       = ui->widget_5->ui->widget_2->ui->tableWidget->item(24,1)->text().toDouble();
            //base_tepl.d12    = ui->widget_5->ui->widget_2->ui->tableWidget->item(25,1)->text().toDouble();
            base_tepl.lambda_l    = ui->widget_5->ui->widget_2->ui->tableWidget->item(26,1)->text().toDouble();
            base_tepl.lambda_em     = ui->widget_5->ui->widget_2->ui->tableWidget->item(27,1)->text().toDouble();
            base_tepl.sigma_i = ui->widget_5->ui->widget_2->ui->tableWidget->item(28,1)->text().toDouble();
            base_tepl.lambda_ek  = ui->widget_5->ui->widget_2->ui->tableWidget->item(29,1)->text().toDouble();

            //base_tepl.lambda_c   = ui->widget_5->ui->widget_2->ui->tableWidget->item(30,1)->text().toDouble();
            base_tepl.lambda_mi     = ui->widget_5->ui->widget_2->ui->tableWidget->item(31,1)->text().toDouble();
            base_tepl.q_mi     = ui->widget_5->ui->widget_2->ui->tableWidget->item(32,1)->text().toDouble();
           // base_tepl.z_i     = ui->widget_5->ui->widget_2->ui->tableWidget->item(33,1)->text().toDouble();
            base_tepl.Lp1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(34,1)->text().toDouble();
            base_tepl.lambda_il     = ui->widget_5->ui->widget_2->ui->tableWidget->item(35,1)->text().toDouble();
            base_tepl.K_l1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(36,1)->text().toDouble();
            base_tepl.delta_il1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(37,1)->text().toDouble();
            base_tepl.lambda_ekuz     = ui->widget_5->ui->widget_2->ui->tableWidget->item(38,1)->text().toDouble();
            base_tepl.lambda_ekpa      = ui->widget_5->ui->widget_2->ui->tableWidget->item(39,1)->text().toDouble();

            //base_tepl.L_li    = ui->widget_5->ui->widget_2->ui->tableWidget->item(40,1)->text().toDouble();
           // base_tepl.alpha_l1    = ui->widget_5->ui->widget_2->ui->tableWidget->item(41,1)->text().toDouble();
            base_tepl.lambda_m2    = ui->widget_5->ui->widget_2->ui->tableWidget->item(42,1)->text().toDouble();
            base_tepl.qc    = ui->widget_5->ui->widget_2->ui->tableWidget->item(43,1)->text().toDouble();
            base_tepl.Z2    = ui->widget_5->ui->widget_2->ui->tableWidget->item(44,1)->text().toDouble();
            base_tepl.L2  = ui->widget_5->ui->widget_2->ui->tableWidget->item(45,1)->text().toDouble();
            base_tepl.Bk    = ui->widget_5->ui->widget_2->ui->tableWidget->item(46,1)->text().toDouble();
            //base_tepl.alpha_а2    = ui->widget_5->ui->widget_2->ui->tableWidget->item(47,1)->text().toDouble();
            base_tepl.S_l2    = ui->widget_5->ui->widget_2->ui->tableWidget->item(48,1)->text().toDouble();
           // base_tepl.alpha_asch      = ui->widget_5->ui->widget_2->ui->tableWidget->item(49,1)->text().toDouble();

            base_tepl.S_isch    = ui->widget_5->ui->widget_2->ui->tableWidget->item(50,1)->text().toDouble();
           // base_tepl.alpha_ast    = ui->widget_5->ui->widget_2->ui->tableWidget->item(51,1)->text().toDouble();
            base_tepl.S_ist    = ui->widget_5->ui->widget_2->ui->tableWidget->item(52,1)->text().toDouble();
            base_tepl.alpha_st    = ui->widget_5->ui->widget_2->ui->tableWidget->item(53,1)->text().toDouble();
            base_tepl.alpha_r    = ui->widget_5->ui->widget_2->ui->tableWidget->item(54,1)->text().toDouble();
            base_tepl.D_ct  = ui->widget_5->ui->widget_2->ui->tableWidget->item(55,1)->text().toDouble();
            //base_tepl.Krp    = ui->widget_5->ui->widget_2->ui->tableWidget->item(56,1)->text().toDouble();
            base_tepl.Hp    = ui->widget_5->ui->widget_2->ui->tableWidget->item(57,1)->text().toDouble();
            base_tepl.tp    = ui->widget_5->ui->widget_2->ui->tableWidget->item(58,1)->text().toDouble();
            base_tepl.alpha_c   = ui->widget_5->ui->widget_2->ui->tableWidget->item(59,1)->text().toDouble();

            base_tepl.delta_Kp  = ui->widget_5->ui->widget_2->ui->tableWidget->item(60,1)->text().toDouble();
            base_tepl.Dp1  = ui->widget_5->ui->widget_2->ui->tableWidget->item(61,1)->text().toDouble();

            //Решение СЛАУ

            double a_data[] = { 0.18, 0.60, 0.57, 0.96,
                                0.41, 0.24, 0.99, 0.58,
                                0.14, 0.30, 0.97, 0.66,
                                0.51, 0.13, 0.19, 0.85 };

            double b_data[] = { 1.0, 2.0, 3.0, 4.0 };

            gsl_matrix_view m = gsl_matrix_view_array (a_data, 4, 4);
            gsl_vector_view b = gsl_vector_view_array (b_data, 4);
            gsl_vector *x = gsl_vector_alloc (4);
            int s;
            gsl_permutation * p = gsl_permutation_alloc (4);
            gsl_linalg_LU_decomp (&m.matrix, p, &s);
            gsl_linalg_LU_solve (&m.matrix, p, &b.vector, x);



            //ВЫВОД ДАННЫХ В ТАБЛИЦЫ

            //вывод температур в таблицу
            teta_2=gsl_vector_get(x, 0);
            teta_3=gsl_vector_get(x, 1);
            teta_4=gsl_vector_get(x, 2);
            teta_c=gsl_vector_get(x, 3);
            teta_p=gsl_vector_get(x, 0);
            teta_z=gsl_vector_get(x, 1);
            teta_pp=gsl_vector_get(x, 2);
            teta_l_1=gsl_vector_get(x, 3);
            teta_l_2=gsl_vector_get(x, 0);

            gsl_permutation_free (p);
            gsl_vector_free (x);

            //Расчет температур
            teta_p=20;
            teta_z=50;
            teta_3=70;
            teta_c=76;
            teta_l_1=120;
            teta_pp=80;
            teta_l_2=120;
            teta_2=60;
            teta_4=40;

            //Вывод температур в таблицу
            ui->widget_5->ui->tableWidget->item(0,0)->setText("Температура_1, °C");
            ui->widget_5->ui->tableWidget->item(1,0)->setText("Температура_2, °C");
            ui->widget_5->ui->tableWidget->item(2,0)->setText("Температура_3, °C");
            ui->widget_5->ui->tableWidget->item(3,0)->setText("Температура_4, °C");
            ui->widget_5->ui->tableWidget->item(4,0)->setText("Температура_5, °C");
            ui->widget_5->ui->tableWidget->item(5,0)->setText("Температура_6, °C");
            ui->widget_5->ui->tableWidget->item(6,0)->setText("Температура_7, °C");
            ui->widget_5->ui->tableWidget->item(7,0)->setText("Температура_8, °C");
            ui->widget_5->ui->tableWidget->item(8,0)->setText("Температура_9, °C");

            ui->widget_5->ui->tableWidget->item(0,1)->setText(QString::number(teta_p,'f',3));
            ui->widget_5->ui->tableWidget->item(1,1)->setText(QString::number(teta_z,'f',3));
            ui->widget_5->ui->tableWidget->item(2,1)->setText(QString::number(teta_3,'f',3));
            ui->widget_5->ui->tableWidget->item(3,1)->setText(QString::number(teta_c,'f',3));
            ui->widget_5->ui->tableWidget->item(4,1)->setText(QString::number(teta_l_1,'f',3));
            ui->widget_5->ui->tableWidget->item(5,1)->setText(QString::number(teta_pp,'f',3));
            ui->widget_5->ui->tableWidget->item(6,1)->setText(QString::number(teta_l_2,'f',3));
            ui->widget_5->ui->tableWidget->item(7,1)->setText(QString::number(teta_2,'f',3));
            ui->widget_5->ui->tableWidget->item(8,1)->setText(QString::number(teta_4,'f',3));

            //Расчет тепловых проводимостей
            lambda_zp=0.034;
            lambda_zc=0.35;
            lambda_c3=0.23;
            lambda_pc=0.021;
            lambda_pz=0.034;
            lambda_l22=0.067;
            lambda_l14=0.067;
            lambda_pl1=0.67;
            lambda_pl2=0.56;

            //Вывод тепловых проводимостей в таблицу
            ui->widget_5->ui->tableWidget->item(0,2)->setText("Теплопроводность_1, Вт/°C");
            ui->widget_5->ui->tableWidget->item(1,2)->setText("Теплопроводность_2, Вт/°C");
            ui->widget_5->ui->tableWidget->item(2,2)->setText("Теплопроводность_3, Вт/°C");
            ui->widget_5->ui->tableWidget->item(3,2)->setText("Теплопроводность_4, Вт/°C");
            ui->widget_5->ui->tableWidget->item(4,2)->setText("Теплопроводность_5, Вт/°C");
            ui->widget_5->ui->tableWidget->item(5,2)->setText("Теплопроводность_6, Вт/°C");
            ui->widget_5->ui->tableWidget->item(6,2)->setText("Теплопроводность_7, Вт/°C");
            ui->widget_5->ui->tableWidget->item(7,2)->setText("Теплопроводность_8, Вт/°C");
            ui->widget_5->ui->tableWidget->item(8,2)->setText("Теплопроводность_9, Вт/°C");

            ui->widget_5->ui->tableWidget->item(0,3)->setText(QString::number(lambda_zp,'f',3));
            ui->widget_5->ui->tableWidget->item(1,3)->setText(QString::number(lambda_zc,'f',3));
            ui->widget_5->ui->tableWidget->item(2,3)->setText(QString::number(lambda_c3,'f',3));
            ui->widget_5->ui->tableWidget->item(3,3)->setText(QString::number(lambda_pc,'f',3));
            ui->widget_5->ui->tableWidget->item(4,3)->setText(QString::number(lambda_pz,'f',3));
            ui->widget_5->ui->tableWidget->item(5,3)->setText(QString::number(lambda_l22,'f',3));
            ui->widget_5->ui->tableWidget->item(6,3)->setText(QString::number(lambda_l14,'f',3));
            ui->widget_5->ui->tableWidget->item(7,3)->setText(QString::number(lambda_pl1,'f',3));
            ui->widget_5->ui->tableWidget->item(8,3)->setText(QString::number(lambda_pl2,'f',3));

            //Расчет мощности рассеяния
            P_p=20;
            P_z=100;
            P_3=120;
            P_c=502;
            P_l_1=67;
            P_pp=76;
            P_l_2=120;
            P_2=56;
            P_4=59;

            //Вывод мощностей рассеяния в таблицу
            ui->widget_5->ui->tableWidget->item(0,4)->setText("Мощность_рассеяния_1, Вт");
            ui->widget_5->ui->tableWidget->item(1,4)->setText("Мощность_рассеяния_2, Вт");
            ui->widget_5->ui->tableWidget->item(2,4)->setText("Мощность_рассеяния_3, Вт");
            ui->widget_5->ui->tableWidget->item(3,4)->setText("Мощность_рассеяния_4, Вт");
            ui->widget_5->ui->tableWidget->item(4,4)->setText("Мощность_рассеяния_5, Вт");
            ui->widget_5->ui->tableWidget->item(5,4)->setText("Мощность_рассеяния_6, Вт");
            ui->widget_5->ui->tableWidget->item(6,4)->setText("Мощность_рассеяния_7, Вт");
            ui->widget_5->ui->tableWidget->item(7,4)->setText("Мощность_рассеяния_8, Вт");
            ui->widget_5->ui->tableWidget->item(8,4)->setText("Мощность_рассеяния_9, Вт");

            ui->widget_5->ui->tableWidget->item(0,5)->setText(QString::number(P_p,'f',3));
            ui->widget_5->ui->tableWidget->item(1,5)->setText(QString::number(P_z,'f',3));
            ui->widget_5->ui->tableWidget->item(2,5)->setText(QString::number(P_3,'f',3));
            ui->widget_5->ui->tableWidget->item(3,5)->setText(QString::number(P_c,'f',3));
            ui->widget_5->ui->tableWidget->item(4,5)->setText(QString::number(P_l_1,'f',3));
            ui->widget_5->ui->tableWidget->item(5,5)->setText(QString::number(P_pp,'f',3));
            ui->widget_5->ui->tableWidget->item(6,5)->setText(QString::number(P_l_2,'f',3));
            ui->widget_5->ui->tableWidget->item(7,5)->setText(QString::number(P_2,'f',3));
            ui->widget_5->ui->tableWidget->item(8,5)->setText(QString::number(P_4,'f',3));

            //Расчет теплоемкостей
            C_p=0.034;
            C_z=0.35;
            C_3=0.23;
            C_c=0.034;
            C_l_1=0.067;
            C_pp=0.067;
            C_l_2=0.67;
            C_2=0.56;
            C_4=0.059;

            //Вывод теплоемкостей в таблицу
            ui->widget_5->ui->tableWidget->item(0,6)->setText("Теплоемкость_1, Дж/К");
            ui->widget_5->ui->tableWidget->item(1,6)->setText("Теплоемкость_2, Дж/К");
            ui->widget_5->ui->tableWidget->item(2,6)->setText("Теплоемкость_3, Дж/К");
            ui->widget_5->ui->tableWidget->item(3,6)->setText("Теплоемкость_4, Дж/К");
            ui->widget_5->ui->tableWidget->item(4,6)->setText("Теплоемкость_5, Дж/К");
            ui->widget_5->ui->tableWidget->item(5,6)->setText("Теплоемкость_6, Дж/К");
            ui->widget_5->ui->tableWidget->item(6,6)->setText("Теплоемкость_7, Дж/К");
            ui->widget_5->ui->tableWidget->item(7,6)->setText("Теплоемкость_8, Дж/К");
            ui->widget_5->ui->tableWidget->item(8,6)->setText("Теплоемкость_9, Дж/К");

            ui->widget_5->ui->tableWidget->item(0,7)->setText(QString::number(C_p,'f',3));
            ui->widget_5->ui->tableWidget->item(1,7)->setText(QString::number(C_z,'f',3));
            ui->widget_5->ui->tableWidget->item(2,7)->setText(QString::number(C_3,'f',3));
            ui->widget_5->ui->tableWidget->item(3,7)->setText(QString::number(C_c,'f',3));
            ui->widget_5->ui->tableWidget->item(4,7)->setText(QString::number(C_l_1,'f',3));
            ui->widget_5->ui->tableWidget->item(5,7)->setText(QString::number(C_pp,'f',3));
            ui->widget_5->ui->tableWidget->item(6,7)->setText(QString::number(C_l_2,'f',3));
            ui->widget_5->ui->tableWidget->item(7,7)->setText(QString::number(C_2,'f',3));
            ui->widget_5->ui->tableWidget->item(8,7)->setText(QString::number(C_4,'f',3));

            //Расчет мощностей рассеяния
            dP_zp=100;
            dP_zc=220;
            dP_c3=230;
            dP_pс=450;
            dP_pz=120;
            dP_l22=340;
            dP_l14=560;
            dP_pl1=506;
            dP_pl2=760;

            //Вывод мощностей рассеяния в таблицу
            ui->widget_5->ui->tableWidget->item(0,8)->setText("Мощность_рассеяния_1, Вт");
            ui->widget_5->ui->tableWidget->item(1,8)->setText("Мощность_рассеяния_2, Вт");
            ui->widget_5->ui->tableWidget->item(2,8)->setText("Мощность_рассеяния_3, Вт");
            ui->widget_5->ui->tableWidget->item(3,8)->setText("Мощность_рассеяния_4, Вт");
            ui->widget_5->ui->tableWidget->item(4,8)->setText("Мощность_рассеяния_5, Вт");
            ui->widget_5->ui->tableWidget->item(5,8)->setText("Мощность_рассеяния_6, Вт");
            ui->widget_5->ui->tableWidget->item(6,8)->setText("Мощность_рассеяния_7, Вт");
            ui->widget_5->ui->tableWidget->item(7,8)->setText("Мощность_рассеяния_8, Вт");
            ui->widget_5->ui->tableWidget->item(8,8)->setText("Мощность_рассеяния_9, Вт");

            ui->widget_5->ui->tableWidget->item(0,9)->setText(QString::number(dP_zp,'f',3));
            ui->widget_5->ui->tableWidget->item(1,9)->setText(QString::number(dP_zc,'f',3));
            ui->widget_5->ui->tableWidget->item(2,9)->setText(QString::number(dP_c3,'f',3));
            ui->widget_5->ui->tableWidget->item(3,9)->setText(QString::number(dP_pс,'f',3));
            ui->widget_5->ui->tableWidget->item(4,9)->setText(QString::number(dP_pz,'f',3));
            ui->widget_5->ui->tableWidget->item(5,9)->setText(QString::number(dP_l22,'f',3));
            ui->widget_5->ui->tableWidget->item(6,9)->setText(QString::number(dP_l14,'f',3));
            ui->widget_5->ui->tableWidget->item(7,9)->setText(QString::number(dP_pl1,'f',3));
            ui->widget_5->ui->tableWidget->item(8,9)->setText(QString::number(dP_pl2,'f',3));

            //Расчет превышений температуры
            d_teta_zp=10;
            d_teta_zc=5;
            d_teta_c3=20;
            d_teta_pc=30;
            d_teta_pz=15;
            d_teta_l22=10;
            d_teta_l14=5;
            d_teta_pl1=35;
            d_teta_pl2=35;

            //Вывод превышений температуры в таблицу
            ui->widget_5->ui->tableWidget->item(0,10)->setText("Температура_1, °C");
            ui->widget_5->ui->tableWidget->item(1,10)->setText("Температура_2, °C");
            ui->widget_5->ui->tableWidget->item(2,10)->setText("Температура_3, °C");
            ui->widget_5->ui->tableWidget->item(3,10)->setText("Температура_4, °C");
            ui->widget_5->ui->tableWidget->item(4,10)->setText("Температура_5, °C");
            ui->widget_5->ui->tableWidget->item(5,10)->setText("Температура_6, °C");
            ui->widget_5->ui->tableWidget->item(6,10)->setText("Температура_7, °C");
            ui->widget_5->ui->tableWidget->item(7,10)->setText("Температура_8, °C");
            ui->widget_5->ui->tableWidget->item(8,10)->setText("Температура_9, °C");

            ui->widget_5->ui->tableWidget->item(0,11)->setText(QString::number(d_teta_zp,'f',3));
            ui->widget_5->ui->tableWidget->item(1,11)->setText(QString::number(d_teta_zc,'f',3));
            ui->widget_5->ui->tableWidget->item(2,11)->setText(QString::number(d_teta_c3,'f',3));
            ui->widget_5->ui->tableWidget->item(3,11)->setText(QString::number(d_teta_pc,'f',3));
            ui->widget_5->ui->tableWidget->item(4,11)->setText(QString::number(d_teta_pz,'f',3));
            ui->widget_5->ui->tableWidget->item(5,11)->setText(QString::number(d_teta_l22,'f',3));
            ui->widget_5->ui->tableWidget->item(6,11)->setText(QString::number(d_teta_l14,'f',3));
            ui->widget_5->ui->tableWidget->item(7,11)->setText(QString::number(d_teta_pl1,'f',3));
            ui->widget_5->ui->tableWidget->item(8,11)->setText(QString::number(d_teta_pl2,'f',3));
        }
        if (item30->text() == "Статика (упрощенный вариант)")
        {
            ui->widget_5->ui->tabWidget->show();
            ui->widget_5->ui->tabWidget->setCurrentIndex(11);
            //ввод данных
            base_tepl.Da1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(0,1)->text().toDouble();
            base_tepl.Ha1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(1,1)->text().toDouble();
            base_tepl.lambda_c1       = ui->widget_5->ui->widget_2->ui->tableWidget->item(2,1)->text().toDouble();
            base_tepl.L1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(3,1)->text().toDouble();
            base_tepl.delta_ct = ui->widget_5->ui->widget_2->ui->tableWidget->item(4,1)->text().toDouble();
            base_tepl.lambda_ct   = ui->widget_5->ui->widget_2->ui->tableWidget->item(5,1)->text().toDouble();
            base_tepl.lambda_i  = ui->widget_5->ui->widget_2->ui->tableWidget->item(6,1)->text().toDouble();
            base_tepl.delta_ai     = ui->widget_5->ui->widget_2->ui->tableWidget->item(7,1)->text().toDouble();
            base_tepl.Kc1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(8,1)->text().toDouble();
            base_tepl.Di1   = ui->widget_5->ui->widget_2->ui->tableWidget->item(9,1)->text().toDouble();

            base_tepl.Z1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(10,1)->text().toDouble();
            base_tepl.Bz1       = ui->widget_5->ui->widget_2->ui->tableWidget->item(11,1)->text().toDouble();
            base_tepl.lambda_с     = ui->widget_5->ui->widget_2->ui->tableWidget->item(12,1)->text().toDouble();
            base_tepl.Hz1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(13,1)->text().toDouble();
            base_tepl.lambda_ip1    = ui->widget_5->ui->widget_2->ui->tableWidget->item(14,1)->text().toDouble();
            base_tepl.delta_ip1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(15,1)->text().toDouble();
            base_tepl.Kz      = ui->widget_5->ui->widget_2->ui->tableWidget->item(16,1)->text().toDouble();
            base_tepl.d1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(17,1)->text().toDouble();
            base_tepl.teta_m     = ui->widget_5->ui->widget_2->ui->tableWidget->item(18,1)->text().toDouble();
            base_tepl.Kp   = ui->widget_5->ui->widget_2->ui->tableWidget->item(19,1)->text().toDouble();

            base_tepl.lambda_l   = ui->widget_5->ui->widget_2->ui->tableWidget->item(20,1)->text().toDouble();
            base_tepl.lambda_em    = ui->widget_5->ui->widget_2->ui->tableWidget->item(21,1)->text().toDouble();
            base_tepl.Bp     = ui->widget_5->ui->widget_2->ui->tableWidget->item(22,1)->text().toDouble();
            base_tepl.sigma_ipr     = ui->widget_5->ui->widget_2->ui->tableWidget->item(23,1)->text().toDouble();
            base_tepl.sigma_i       = ui->widget_5->ui->widget_2->ui->tableWidget->item(24,1)->text().toDouble();
            base_tepl.lambda_ek    = ui->widget_5->ui->widget_2->ui->tableWidget->item(25,1)->text().toDouble();
            base_tepl.lambda_mi    = ui->widget_5->ui->widget_2->ui->tableWidget->item(26,1)->text().toDouble();
            base_tepl.q_mi     = ui->widget_5->ui->widget_2->ui->tableWidget->item(27,1)->text().toDouble();
            base_tepl.Lp1 = ui->widget_5->ui->widget_2->ui->tableWidget->item(28,1)->text().toDouble();
            base_tepl.Lambda_el  = ui->widget_5->ui->widget_2->ui->tableWidget->item(29,1)->text().toDouble();

            base_tepl.lambda_ekuz   = ui->widget_5->ui->widget_2->ui->tableWidget->item(30,1)->text().toDouble();
            base_tepl.lambda_ekpa     = ui->widget_5->ui->widget_2->ui->tableWidget->item(31,1)->text().toDouble();
            base_tepl.n     = ui->widget_5->ui->widget_2->ui->tableWidget->item(32,1)->text().toDouble();
            base_tepl.Dv1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(33,1)->text().toDouble();
            base_tepl.nu     = ui->widget_5->ui->widget_2->ui->tableWidget->item(34,1)->text().toDouble();
            base_tepl.K_l1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(35,1)->text().toDouble();
            base_tepl.lambda_il     = ui->widget_5->ui->widget_2->ui->tableWidget->item(36,1)->text().toDouble();
            base_tepl.delta_il1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(37,1)->text().toDouble();
            base_tepl.lambda_m2     = ui->widget_5->ui->widget_2->ui->tableWidget->item(38,1)->text().toDouble();
            base_tepl.qc      = ui->widget_5->ui->widget_2->ui->tableWidget->item(39,1)->text().toDouble();

            base_tepl.L2    = ui->widget_5->ui->widget_2->ui->tableWidget->item(40,1)->text().toDouble();
            base_tepl.Bk    = ui->widget_5->ui->widget_2->ui->tableWidget->item(41,1)->text().toDouble();
            base_tepl.Z2    = ui->widget_5->ui->widget_2->ui->tableWidget->item(42,1)->text().toDouble();
            base_tepl.u_rot    = ui->widget_5->ui->widget_2->ui->tableWidget->item(43,1)->text().toDouble();
            base_tepl.Dl    = ui->widget_5->ui->widget_2->ui->tableWidget->item(44,1)->text().toDouble();
            base_tepl.S_l2  = ui->widget_5->ui->widget_2->ui->tableWidget->item(45,1)->text().toDouble();
            base_tepl.S_isch    = ui->widget_5->ui->widget_2->ui->tableWidget->item(46,1)->text().toDouble();
            base_tepl.S_ist    = ui->widget_5->ui->widget_2->ui->tableWidget->item(47,1)->text().toDouble();
            base_tepl.alpha_r    = ui->widget_5->ui->widget_2->ui->tableWidget->item(48,1)->text().toDouble();

            base_tepl.alpha_st      = ui->widget_5->ui->widget_2->ui->tableWidget->item(49,1)->text().toDouble();
            base_tepl.h_p    = ui->widget_5->ui->widget_2->ui->tableWidget->item(50,1)->text().toDouble();
            base_tepl.t_p    = ui->widget_5->ui->widget_2->ui->tableWidget->item(51,1)->text().toDouble();
            base_tepl.n_p    = ui->widget_5->ui->widget_2->ui->tableWidget->item(52,1)->text().toDouble();
            base_tepl.a_p    = ui->widget_5->ui->widget_2->ui->tableWidget->item(53,1)->text().toDouble();
            base_tepl.D_ct    = ui->widget_5->ui->widget_2->ui->tableWidget->item(54,1)->text().toDouble();
            base_tepl.u2  = ui->widget_5->ui->widget_2->ui->tableWidget->item(55,1)->text().toDouble();
            base_tepl.alpha_c   = ui->widget_5->ui->widget_2->ui->tableWidget->item(59,1)->text().toDouble();
            base_tepl.delta_Kp  = ui->widget_5->ui->widget_2->ui->tableWidget->item(60,1)->text().toDouble();
            base_tepl.Dp1  = ui->widget_5->ui->widget_2->ui->tableWidget->item(61,1)->text().toDouble();
            base_tepl.lambda_v   = ui->widget_5->ui->widget_2->ui->tableWidget->item(62,1)->text().toDouble();


            double Lambda_ct,Lambda_adelta1,Lambda_a1,Lambda_delta1,Lambda_sigma,Lambda_1z1,Lambda_12,Lambda_1ip1,
                    delta,Lambda_epz,Lambda_ekv,Lambda_i1z,Lambda_z,Lambda_nz,Lambda_i1a,Lambda_ekpa,
                    Lambda_2ip1,Lambda_a,Lambda_na,Lambda_za,Lambda_pl,Lambda_il,Lambda_el,Lambda_al1,Lambda_l1,
                    Lambda_lp2,Lambda_a2,Lambda_l2,Lambda_asch,Lambda_ast,Lambda_ai,alpha_stsumm,Lambda_ct1,ro_t,Krp1,Lambda_p,
                    alpha_sigma,Lambda_sch;
            double Re1,wl,dek,Nu1,alpha_l1,Re2,Nu2,alpha_а2,wr,alpha_asch,alpha_ast,k_p,delta_Kp,alpha_1sch,alpha_2sch;



            //+Тепловая проводимость станины
            Lambda_ct = (M_PI*(base_tepl.Da1 + base_tepl.delta_ct) * base_tepl.L1 * base_tepl.lambda_ct) / (base_tepl.delta_ct);

            //+Тепловая проводимость зазора между сердечником статора и станиной
            Lambda_adelta1 = (M_PI * base_tepl.Da1 * base_tepl.L1 * base_tepl.lambda_i)/base_tepl.delta_ai;

            //+Тепловая проводимость спинки статора
            Lambda_a1 = M_PI * base_tepl.L1 * base_tepl.lambda_c1 * base_tepl.Kc1 * (2 * base_tepl.Da1 - base_tepl.Ha1) / base_tepl.Ha1;

            //+Общая тепловая проводимость между сердечником статора и станиной
            Lambda_delta1 = 1/((1/ Lambda_a1)+(1/ Lambda_adelta1)+(1/ Lambda_ct));

            //+Коэффициент теплоотдачи от ротора к внутреннему воздуху
            alpha_sigma = (((2*base_tepl.delta_ai)/(base_tepl.Dp1/2))*(base_tepl.lambda_v/(2*base_tepl.delta_ai)))/
            log(1+(base_tepl.delta_ai/(base_tepl.Dp1/2)));

            //+Тепловая проводимость воздушного зазора:
            Lambda_sigma = (M_PI / 2) * (base_tepl.Di1 * base_tepl.L1 * alpha_sigma);

            //+Тепловая проводимость зубцов статора:
            Lambda_1z1 = (2 * base_tepl.Z1 * base_tepl.Bz1 * base_tepl.L1 * base_tepl.Kc1 * base_tepl.lambda_c1) / base_tepl.Hz1;

            //+Общая тепловая проводимость между статором и ротором
            Lambda_12 = (Lambda_sigma * Lambda_1z1)/( Lambda_sigma + Lambda_1z1);

            //+Тепловая проводимость пазовой изоляции
            Lambda_1ip1 = (2 * base_tepl.Hz1 * base_tepl.Z1 * base_tepl.L1 * base_tepl.lambda_ip1)/base_tepl.delta_ip1;

            //+Воздушный зазор между проводами в пазе статора
            delta = base_tepl.d1 * (0.022 + 0.5 * (1 / sqrt(base_tepl.Kz) - 1));

            //+Эквивалентный коэффициент теплопроводности обмотки
            Lambda_ekv = 0.00165*(1 + 0.0007 * base_tepl.teta_m)*(1 - 3.2 * base_tepl.d1 * (1 - 9.2 * base_tepl.Kp + 5.2 *
            pow(base_tepl.Kp,2)) + 81 * pow(base_tepl.d1,2))*( 2.11 * pow(base_tepl.Kz,1.5) * 1.15 - 0.32)*pow((base_tepl.lambda_l / 0.00162 ),0.33) *
            pow((base_tepl.lambda_em/ 0.00143),0.25);

            //+Эквивалентная тепловая проводимость обмотки к зубцам
            Lambda_epz = ((base_tepl.d1 + delta) * Lambda_ekv * 2 * base_tepl.Hz1 * base_tepl.Z1 * base_tepl.L1)/
            ((base_tepl.Bp - 2 * base_tepl.delta_ip1) * (base_tepl.sigma_ipr + delta));

            //+Тепловая проводимость воздушного зазора между пазовой изоляцией и зубцами статора
            Lambda_i1z = (2 * base_tepl.Hz1 * base_tepl.L1 * base_tepl.Z1 * base_tepl.lambda_i)/base_tepl.sigma_i;

            //+Проводимость зубца статора в направлении теплового потока от пазовой части проводки
            Lambda_z = base_tepl.Bz1 / (base_tepl.Z1 * base_tepl.Hz1 * base_tepl.L1 * base_tepl.Kc1 * base_tepl.lambda_с);

            //+Общая тепловая проводимость между пазовой частью обмотки статора и зубцами
            Lambda_nz = 1/((1/Lambda_1ip1)+(1/Lambda_epz)+(1/Lambda_i1z)+(1/Lambda_z));

            //+Тепловая проводимость воздушного зазора между пазовой изоляцией и спинкой статора
            Lambda_i1a = (base_tepl.Bp * base_tepl.L1 * base_tepl.Z1 * base_tepl.lambda_i)/base_tepl.sigma_i;

            //+Эквивалентная тепловая проводимость обмотки к спинке
            Lambda_ekpa = ((base_tepl.d1 + delta) * base_tepl.lambda_ek * base_tepl.Bp * base_tepl.L1 * base_tepl.Z1) /
            ((base_tepl.Hz1 - 2 * base_tepl.delta_ip1) * (base_tepl.sigma_ipr + delta));

            //+Тепловая проводимость пазовой изоляции
            Lambda_2ip1 = (base_tepl.Z1 * base_tepl.Bp * base_tepl.L1 * base_tepl.lambda_ip1)/base_tepl.delta_ip1;

            //+Проводимость спинки статора в направлении теплового потока от пазовой части обмотки
            Lambda_a = base_tepl.Ha1/((0.5 * 3.14 * (base_tepl.Da1 - base_tepl.Ha1) + base_tepl.Z1 * base_tepl.Bp) *
            base_tepl.L1 * base_tepl.Kc1 * base_tepl.lambda_c1);

            //+Общая тепловая проводимость между пазовой частью обмотки и спинкой статора
            Lambda_na = 1/((1/Lambda_2ip1) + (1/Lambda_ekpa)+(1/Lambda_i1a)+(1/Lambda_a));

            //+Проводимость между зубцом и спинкой статора
            Lambda_za = base_tepl.L1 * base_tepl.Kc1 * base_tepl.lambda_c1/(base_tepl.Hz1/( 2 * base_tepl.Z1 * base_tepl.Bz1) +
            base_tepl.Ha1 / (2 * 3.14 * (base_tepl.Da1 - base_tepl.Ha1)));

            //+hТепловая проводимость между пазовой и лобовой частями обмотки статора
            Lambda_pl = 12 * base_tepl.lambda_mi * base_tepl.q_mi * base_tepl.Z1 / (base_tepl.L1 + base_tepl.Lp1);

            //+Тепловая проводимость изоляции
            Lambda_il= (base_tepl.lambda_il * 2 * (base_tepl.Hz1 + base_tepl.Bp) * base_tepl.L1 * base_tepl.Z1 *
            base_tepl.K_l1) / base_tepl.delta_il1;

            //+Эквивалентная тепловая проводимость лобовой части
            Lambda_el = (base_tepl.lambda_ekuz + base_tepl.lambda_ekpa) * base_tepl.Lp1 / base_tepl.L1;

            //+Тепловая проводимость лобовых частей
            wl = 0.022 *base_tepl.n * base_tepl.Dv1;
            dek = 4 * base_tepl.Bp * base_tepl.Hz1 /(2 * base_tepl.Bp + base_tepl.Hz1);
            Re1 = (wl * dek) / base_tepl.nu;
            Nu1 = 0.103 * pow(Re1,0.66);
            alpha_l1 = (Nu1 * base_tepl.lambda_v)/ base_tepl.Da1;
            Lambda_al1 = alpha_l1 * 2 * (base_tepl.Hz1 + base_tepl.Bp) * base_tepl.Lp1 * base_tepl.Z1 * base_tepl.K_l1;

            //+Полная тепловая проводимость лобовой части обмотки статора к окружающей среде
            Lambda_l1 = 1 / ((1 / Lambda_il) + (1 / Lambda_al1) + (1 / Lambda_el));

            //+Общая тепловая проводимость между лобовой и пазовой частями клетки статора
            Lambda_lp2 = (12 * base_tepl.lambda_m2 * base_tepl.qc * base_tepl.Z2)/(base_tepl.L2 + base_tepl.Bk);

            //+тепловая проводимость лобовых частей обмоток статора, обращенных к ротору
            Re2=(base_tepl.u_rot * base_tepl.Dl) / (2*base_tepl.nu);
            Nu2 = 0.456 * pow(Re2,0.6);
            alpha_а2 = (Nu2 * base_tepl.lambda_v)/ base_tepl.Dl;
            Lambda_a2 = alpha_а2 * base_tepl.S_l2;

            //+Общая тепловая проводимость лобовой части обмотки ротора к внутреннему воздуху
            Lambda_l2 = (Lambda_lp2 * Lambda_a2) / (Lambda_lp2 + Lambda_a2);

            //+Тепловая проводимость внутреннего воздуха к подшипниковым щитам
            wr = (3.14 * base_tepl.Dl * base_tepl.u_rot ) / 60;
            alpha_asch = 15 + 6.5 * pow(wr,0.7);
            Lambda_asch = alpha_asch * base_tepl.S_isch;

            //+Тепловая проводимость внутреннего воздуха к станине
            wr = (3.14 * base_tepl.Dl * base_tepl.u_rot ) / 60;
            alpha_ast = 4.58 * pow(wr,0.74);
            Lambda_ast = alpha_ast * base_tepl.S_ist;

            //+Общая тепловая проводимость внутреннего воздуха к оболочке двигателя
            Lambda_ai = Lambda_asch + Lambda_ast;

            //+суммарный коэффициент теплоотдачи станины
            alpha_stsumm = base_tepl.alpha_st + base_tepl.alpha_r;

            //Тепловая проводимость станины к окружающей среде
            k_p = base_tepl.h_p * (base_tepl.t_p / 3.14) * base_tepl.D_ct;
            delta_Kp = base_tepl.n_p * base_tepl.a_p / 3.14 * base_tepl.D_ct * k_p;
            ro_t  = sqrt((2 * base_tepl.alpha_st)/(base_tepl.lambda_ct * base_tepl.Bp));
            Krp1 = (1 / (ro_t * base_tepl.h_p)) * (tanh(ro_t * base_tepl.h_p) * (2 * base_tepl.h_p/ base_tepl.t_p) *
            (1-(base_tepl.alpha_r / alpha_stsumm)) + ro_t * base_tepl.h_p *delta_Kp);
            Lambda_ct1 = alpha_stsumm * 3.14 * base_tepl.D_ct * k_p * Krp1;

            //Параметр теплоотдачи
            alpha_1sch = 20 + 14.3 * pow((0.5 * base_tepl.u2),0.6);
            alpha_2sch = 20 + 2.6 * pow((0.5 * base_tepl.u2),0.9);
            Lambda_sch = 0.5 * ( alpha_1sch + alpha_2sch) * 3.14 * pow(base_tepl.D_ct,2);

            //Тепловая проводимость оболочки двигателя к окружающей среде
            Lambda_p = Lambda_ct1 + Lambda_sch;

            if (ui->tableWidget_9->item(0, 2) != 0)
            {
                ui->tableWidget_9->item(0, 2)->setText(QString::number(Lambda_ct,'f',3));
            }

            if (ui->tableWidget_9->item(1, 2) != 0)
            {
                ui->tableWidget_9->item(1, 2)->setText(QString::number(Lambda_adelta1,'f',3));
            }

            if (ui->tableWidget_9->item(2, 2) != 0)
            {
                ui->tableWidget_9->item(2, 2)->setText(QString::number(Lambda_a1,'f',3));
            }

            if (ui->tableWidget_9->item(3, 2) != 0)
            {
                ui->tableWidget_9->item(3, 2)->setText(QString::number(Lambda_delta1,'f',3));
            }

            if (ui->tableWidget_9->item(4, 2) != 0)
            {
                ui->tableWidget_9->item(4, 2)->setText(QString::number(Lambda_sigma,'f',3));
            }

            if (ui->tableWidget_9->item(5, 2) != 0)
            {
                ui->tableWidget_9->item(5, 2)->setText(QString::number(Lambda_1z1,'f',3));
            }

            if (ui->tableWidget_9->item(6, 2) != 0)
            {
                ui->tableWidget_9->item(6, 2)->setText(QString::number(Lambda_12,'f',3));
            }

            if (ui->tableWidget_9->item(7, 2) != 0)
            {
                ui->tableWidget_9->item(7, 2)->setText(QString::number(Lambda_1ip1,'f',3));
            }

            if (ui->tableWidget_9->item(8, 2) != 0)
            {
                ui->tableWidget_9->item(8, 2)->setText(QString::number(delta,'f',6));
            }

            if (ui->tableWidget_9->item(9, 2) != 0)
            {
                ui->tableWidget_9->item(9, 2)->setText(QString::number(Lambda_ekv,'f',6));
            }

            if (ui->tableWidget_9->item(10, 2) != 0)
            {
                ui->tableWidget_9->item(10, 2)->setText(QString::number(Lambda_epz,'f',6));
            }

            if (ui->tableWidget_9->item(11, 2) != 0)
            {
                ui->tableWidget_9->item(11, 2)->setText(QString::number(Lambda_i1z,'f',6));
            }

            if (ui->tableWidget_9->item(12, 2) != 0)
            {
                ui->tableWidget_9->item(12, 2)->setText(QString::number(Lambda_z,'f',6));
            }

            if (ui->tableWidget_9->item(13, 2) != 0)
            {
                ui->tableWidget_9->item(13, 2)->setText(QString::number(Lambda_nz,'f',6));
            }

            if (ui->tableWidget_9->item(14, 2) != 0)
            {
                ui->tableWidget_9->item(14, 2)->setText(QString::number(Lambda_i1a,'f',6));
            }

            if (ui->tableWidget_9->item(15, 2) != 0)
            {
                ui->tableWidget_9->item(15, 2)->setText(QString::number(Lambda_ekpa,'f',6));
            }

            if (ui->tableWidget_9->item(16, 2) != 0)
            {
                ui->tableWidget_9->item(16, 2)->setText(QString::number(Lambda_2ip1,'f',6));
            }

            if (ui->tableWidget_9->item(17, 2) != 0)
            {
                ui->tableWidget_9->item(17, 2)->setText(QString::number(Lambda_a,'f',6));
            }

            if (ui->tableWidget_9->item(18, 2) != 0)
            {
                ui->tableWidget_9->item(18, 2)->setText(QString::number(Lambda_na,'f',6));
            }

            if (ui->tableWidget_9->item(19, 2) != 0)
            {
                ui->tableWidget_9->item(19, 2)->setText(QString::number(Lambda_za,'f',6));
            }

            if (ui->tableWidget_9->item(20, 2) != 0)
            {
                ui->tableWidget_9->item(20, 2)->setText(QString::number(Lambda_pl,'f',6));
            }

            if (ui->tableWidget_9->item(21, 2) != 0)
            {
                ui->tableWidget_9->item(21, 2)->setText(QString::number(Lambda_il,'f',6));
            }

            if (ui->tableWidget_9->item(22, 2) != 0)
            {
                ui->tableWidget_9->item(22, 2)->setText(QString::number(Lambda_el,'f',6));
            }
            if (ui->tableWidget_9->item(23, 2) != 0)
            {
                ui->tableWidget_9->item(23, 2)->setText(QString::number(Lambda_al1,'f',6));
            }

            if (ui->tableWidget_9->item(24, 2) != 0)
            {
                ui->tableWidget_9->item(24, 2)->setText(QString::number(Lambda_l1,'f',6));
            }

            if (ui->tableWidget_9->item(25, 2) != 0)
            {
                ui->tableWidget_9->item(25, 2)->setText(QString::number(Lambda_lp2,'f',6));
            }

            if (ui->tableWidget_9->item(26, 2) != 0)
            {
                ui->tableWidget_9->item(26, 2)->setText(QString::number(Lambda_a2,'f',6));
            }

            if (ui->tableWidget_9->item(27, 2) != 0)
            {
                ui->tableWidget_9->item(27, 2)->setText(QString::number(Lambda_l2,'f',6));
            }

            if (ui->tableWidget_9->item(28, 2) != 0)
            {
                ui->tableWidget_9->item(28, 2)->setText(QString::number(Lambda_asch,'f',6));
            }

            if (ui->tableWidget_9->item(29, 2) != 0)
            {
                ui->tableWidget_9->item(29, 2)->setText(QString::number(Lambda_ast,'f',6));
            }

            if (ui->tableWidget_9->item(30, 2) != 0)
            {
                ui->tableWidget_9->item(30, 2)->setText(QString::number(Lambda_ai,'f',6));
            }

            if (ui->tableWidget_9->item(31, 2) != 0)
            {
                ui->tableWidget_9->item(31, 2)->setText(QString::number(alpha_stsumm,'f',6));
            }

            if (ui->tableWidget_9->item(32, 2) != 0)
            {
                ui->tableWidget_9->item(32, 2)->setText(QString::number(Lambda_ct1,'f',6));
            }

            if (ui->tableWidget_9->item(33, 2) != 0)
            {
                ui->tableWidget_9->item(33, 2)->setText(QString::number(Lambda_sch,'f',6));
            }

            if (ui->tableWidget_9->item(34, 2) != 0)
            {
                ui->tableWidget_9->item(34, 2)->setText(QString::number(Lambda_p,'f',6));
            }


            //Решение СЛАУ

            double a_data[] = { 0.18, 0.60, 0.57, 0.96,
                                0.41, 0.24, 0.99, 0.58,
                                0.14, 0.30, 0.97, 0.66,
                                0.51, 0.13, 0.19, 0.85 };

            double b_data[] = { 1.0, 2.0, 3.0, 4.0 };

            gsl_matrix_view m = gsl_matrix_view_array (a_data, 4, 4);

            gsl_vector_view b = gsl_vector_view_array (b_data, 4);

            gsl_vector *x = gsl_vector_alloc (4);

            int s;

            gsl_permutation * p = gsl_permutation_alloc (4);

            gsl_linalg_LU_decomp (&m.matrix, p, &s);

            gsl_linalg_LU_solve (&m.matrix, p, &b.vector, x);

            //ВЫВОД ДАННЫХ В ТАБЛИЦЫ

            //вывод температур в таблицу
            teta_0=gsl_vector_get(x, 0);
            teta_1=gsl_vector_get(x, 1);
            teta_2=gsl_vector_get(x, 2);
            teta_3=gsl_vector_get(x, 3);
            teta_4=gsl_vector_get(x, 0);
            teta_5=gsl_vector_get(x, 1);
            teta_k=gsl_vector_get(x, 2);
            teta_c=gsl_vector_get(x, 3);
            teta_p=gsl_vector_get(x, 0);
            teta_v=gsl_vector_get(x, 1);

            gsl_permutation_free (p);
            gsl_vector_free (x);

            //Расчет температур
            teta_p=20;
            teta_z=50;
            teta_3=70;
            teta_c=76;
            teta_l_1=120;
            teta_pp=80;
            teta_l_2=120;
            teta_2=60;
            teta_4=40;

            //Вывод температур в таблицу
            ui->widget_5->ui->tableWidget->item(0,0)->setText("Температура_1, °C");
            ui->widget_5->ui->tableWidget->item(1,0)->setText("Температура_2, °C");
            ui->widget_5->ui->tableWidget->item(2,0)->setText("Температура_3, °C");
            ui->widget_5->ui->tableWidget->item(3,0)->setText("Температура_4, °C");
            ui->widget_5->ui->tableWidget->item(4,0)->setText("Температура_5, °C");
            ui->widget_5->ui->tableWidget->item(5,0)->setText("Температура_6, °C");
            ui->widget_5->ui->tableWidget->item(6,0)->setText("Температура_7, °C");
            ui->widget_5->ui->tableWidget->item(7,0)->setText("Температура_8, °C");
            ui->widget_5->ui->tableWidget->item(8,0)->setText("Температура_9, °C");
            ui->widget_5->ui->tableWidget->item(9,0)->setText("Температура_10, °C");

            ui->widget_5->ui->tableWidget->item(0,1)->setText(QString::number(teta_0,'f',3));
            ui->widget_5->ui->tableWidget->item(1,1)->setText(QString::number(teta_1,'f',3));
            ui->widget_5->ui->tableWidget->item(2,1)->setText(QString::number(teta_2,'f',3));
            ui->widget_5->ui->tableWidget->item(3,1)->setText(QString::number(teta_3,'f',3));
            ui->widget_5->ui->tableWidget->item(4,1)->setText(QString::number(teta_4,'f',3));
            ui->widget_5->ui->tableWidget->item(5,1)->setText(QString::number(teta_5,'f',3));
            ui->widget_5->ui->tableWidget->item(6,1)->setText(QString::number(teta_k,'f',3));
            ui->widget_5->ui->tableWidget->item(7,1)->setText(QString::number(teta_c,'f',3));
            ui->widget_5->ui->tableWidget->item(8,1)->setText(QString::number(teta_p,'f',3));
            ui->widget_5->ui->tableWidget->item(9,1)->setText(QString::number(teta_v,'f',3));

            //Расчет тоеплоемкостей в таблицу
            C_0=0.034;
            C_1=0.35;
            C_2=0.23;
            C_3=0.021;
            C_4=0.034;
            C_5=0.067;
            C_k=0.067;
            C_c=0.67;
            C_p=0.56;
            C_v=0.059;

            //вывод тоеплоемкостей в таблицу
            ui->widget_5->ui->tableWidget->item(0,2)->setText("Теплоемкость_1, Дж/К");
            ui->widget_5->ui->tableWidget->item(1,2)->setText("Теплоемкость_2, Дж/К");
            ui->widget_5->ui->tableWidget->item(2,2)->setText("Теплоемкость_3, Дж/К");
            ui->widget_5->ui->tableWidget->item(3,2)->setText("Теплоемкость_4, Дж/К");
            ui->widget_5->ui->tableWidget->item(4,2)->setText("Теплоемкость_5, Дж/К");
            ui->widget_5->ui->tableWidget->item(5,2)->setText("Теплоемкость_6, Дж/К");
            ui->widget_5->ui->tableWidget->item(6,2)->setText("Теплоемкость_7, Дж/К");
            ui->widget_5->ui->tableWidget->item(7,2)->setText("Теплоемкость_8, Дж/К");
            ui->widget_5->ui->tableWidget->item(8,2)->setText("Теплоемкость_9, Дж/К");
            ui->widget_5->ui->tableWidget->item(9,2)->setText("Теплоемкость_10, Дж/К");

            ui->widget_5->ui->tableWidget->item(0,3)->setText(QString::number(C_0,'f',3));
            ui->widget_5->ui->tableWidget->item(1,3)->setText(QString::number(C_1,'f',3));
            ui->widget_5->ui->tableWidget->item(2,3)->setText(QString::number(C_2,'f',3));
            ui->widget_5->ui->tableWidget->item(3,3)->setText(QString::number(C_3,'f',3));
            ui->widget_5->ui->tableWidget->item(4,3)->setText(QString::number(C_4,'f',3));
            ui->widget_5->ui->tableWidget->item(5,3)->setText(QString::number(C_5,'f',3));
            ui->widget_5->ui->tableWidget->item(6,3)->setText(QString::number(C_k,'f',3));
            ui->widget_5->ui->tableWidget->item(7,3)->setText(QString::number(C_c,'f',3));
            ui->widget_5->ui->tableWidget->item(8,3)->setText(QString::number(C_p,'f',3));
            ui->widget_5->ui->tableWidget->item(9,3)->setText(QString::number(C_v,'f',3));

            //Расчет мощностей рассеяния в таблицу
            P_0=0.034;
            P_1=0.35;
            P_2=0.23;
            P_3=0.021;
            P_4=0.034;
            P_5=0.067;
            P_k=0.067;
            P_c=0.67;
            P_p=0.56;
            P_v=0.059;

            //Вывод мощностей рассеяния в таблицу
            ui->widget_5->ui->tableWidget->item(0,4)->setText("Мощность_рассеяния_1, Вт");
            ui->widget_5->ui->tableWidget->item(1,4)->setText("Мощность_рассеяния_2, Вт");
            ui->widget_5->ui->tableWidget->item(2,4)->setText("Мощность_рассеяния_3, Вт");
            ui->widget_5->ui->tableWidget->item(3,4)->setText("Мощность_рассеяния_4, Вт");
            ui->widget_5->ui->tableWidget->item(4,4)->setText("Мощность_рассеяния_5, Вт");
            ui->widget_5->ui->tableWidget->item(5,4)->setText("Мощность_рассеяния_6, Вт");
            ui->widget_5->ui->tableWidget->item(6,4)->setText("Мощность_рассеяния_7, Вт");
            ui->widget_5->ui->tableWidget->item(7,4)->setText("Мощность_рассеяния_8, Вт");
            ui->widget_5->ui->tableWidget->item(8,4)->setText("Мощность_рассеяния_9, Вт");
            ui->widget_5->ui->tableWidget->item(9,4)->setText("Мощность_рассеяния_10, Вт");

            ui->widget_5->ui->tableWidget->item(0,5)->setText(QString::number(P_0,'f',3));
            ui->widget_5->ui->tableWidget->item(1,5)->setText(QString::number(P_1,'f',3));
            ui->widget_5->ui->tableWidget->item(2,5)->setText(QString::number(P_2,'f',3));
            ui->widget_5->ui->tableWidget->item(3,5)->setText(QString::number(P_3,'f',3));
            ui->widget_5->ui->tableWidget->item(4,5)->setText(QString::number(P_4,'f',3));
            ui->widget_5->ui->tableWidget->item(5,5)->setText(QString::number(P_5,'f',3));
            ui->widget_5->ui->tableWidget->item(6,5)->setText(QString::number(P_k,'f',3));
            ui->widget_5->ui->tableWidget->item(7,5)->setText(QString::number(P_c,'f',3));
            ui->widget_5->ui->tableWidget->item(8,5)->setText(QString::number(P_p,'f',3));
            ui->widget_5->ui->tableWidget->item(9,5)->setText(QString::number(P_v,'f',3));

            //вывод тепловых проводимостей в таблицу
            //lambda_10=0.034;
            lambda_10=Lambda_1z1;
            //lambda_30=0.034;
            lambda_30=Lambda_sigma;
            lambda_k0=0.34;
            lambda_50=0.93;
            lambda_3k=0.67;
            lambda_21=0.35;
            lambda_c2=0.23;
            lambda_c3=0.067;
            lambda_c4=0.56;
            lambda_45=0.56;
            lambda_pc=0.067;
            lambda_pb=0.059;
            lambda_b5=0.043;
            lambda_p5=0.0045;
            lambda_p2=0.021;

            ui->widget_5->ui->tableWidget->item(0,6)->setText("Теплопроводность_1, Вт/°C");
            ui->widget_5->ui->tableWidget->item(1,6)->setText("Теплопроводность_2, Вт/°C");
            ui->widget_5->ui->tableWidget->item(2,6)->setText("Теплопроводность_3, Вт/°C");
            ui->widget_5->ui->tableWidget->item(3,6)->setText("Теплопроводность_4, Вт/°C");
            ui->widget_5->ui->tableWidget->item(4,6)->setText("Теплопроводность_5, Вт/°C");
            ui->widget_5->ui->tableWidget->item(5,6)->setText("Теплопроводность_6, Вт/°C");
            ui->widget_5->ui->tableWidget->item(6,6)->setText("Теплопроводность_7, Вт/°C");
            ui->widget_5->ui->tableWidget->item(7,6)->setText("Теплопроводность_8, Вт/°C");
            ui->widget_5->ui->tableWidget->item(8,6)->setText("Теплопроводность_9, Вт/°C");
            ui->widget_5->ui->tableWidget->item(9,6)->setText("Теплопроводность_10, Вт/°C");
            ui->widget_5->ui->tableWidget->item(10,6)->setText("Теплопроводность_11, Вт/°C");
            ui->widget_5->ui->tableWidget->item(11,6)->setText("Теплопроводность_12, Вт/°C");
            ui->widget_5->ui->tableWidget->item(12,6)->setText("Теплопроводность_13, Вт/°C");
            ui->widget_5->ui->tableWidget->item(13,6)->setText("Теплопроводность_14, Вт/°C");
            ui->widget_5->ui->tableWidget->item(14,6)->setText("Теплопроводность_15, Вт/°C");

            ui->widget_5->ui->tableWidget->item(0,7)->setText(QString::number(lambda_10,'f',3));
            ui->widget_5->ui->tableWidget->item(1,7)->setText(QString::number(lambda_30,'f',3));
            ui->widget_5->ui->tableWidget->item(2,7)->setText(QString::number(lambda_k0,'f',3));
            ui->widget_5->ui->tableWidget->item(3,7)->setText(QString::number(lambda_50,'f',3));
            ui->widget_5->ui->tableWidget->item(4,7)->setText(QString::number(lambda_3k,'f',3));
            ui->widget_5->ui->tableWidget->item(5,7)->setText(QString::number(lambda_21,'f',3));
            ui->widget_5->ui->tableWidget->item(6,7)->setText(QString::number(lambda_c2,'f',3));
            ui->widget_5->ui->tableWidget->item(7,7)->setText(QString::number(lambda_c3,'f',3));
            ui->widget_5->ui->tableWidget->item(8,7)->setText(QString::number(lambda_c4,'f',3));
            ui->widget_5->ui->tableWidget->item(9,7)->setText(QString::number(lambda_45,'f',3));
            ui->widget_5->ui->tableWidget->item(10,7)->setText(QString::number(lambda_pc,'f',3));
            ui->widget_5->ui->tableWidget->item(11,7)->setText(QString::number(lambda_pb,'f',3));
            ui->widget_5->ui->tableWidget->item(12,7)->setText(QString::number(lambda_b5,'f',3));
            ui->widget_5->ui->tableWidget->item(13,7)->setText(QString::number(lambda_p5,'f',3));
            ui->widget_5->ui->tableWidget->item(14,7)->setText(QString::number(lambda_p2,'f',3));

            //Расчет мощностей рассеяния
            P_10=100;
            P_30=220;
            P_k0=230;
            P_50=450;
            P_3k=120;
            P_21=340;
            P_c2=560;
            P_c3=506;
            P_c4=760;
            P_45=100;
            P_pc=220;
            P_pb=230;
            P_b5=450;
            P_p5=120;
            P_p2=340;

            //Вывод тепловых проводимостей в таблицу
            ui->widget_5->ui->tableWidget->item(0,8)->setText("Мощность_рассеяния_1, Вт");
            ui->widget_5->ui->tableWidget->item(1,8)->setText("Мощность_рассеяния_2, Вт");
            ui->widget_5->ui->tableWidget->item(2,8)->setText("Мощность_рассеяния_3, Вт");
            ui->widget_5->ui->tableWidget->item(3,8)->setText("Мощность_рассеяния_4, Вт");
            ui->widget_5->ui->tableWidget->item(4,8)->setText("Мощность_рассеяния_5, Вт");
            ui->widget_5->ui->tableWidget->item(5,8)->setText("Мощность_рассеяния_6, Вт");
            ui->widget_5->ui->tableWidget->item(6,8)->setText("Мощность_рассеяния_7, Вт");
            ui->widget_5->ui->tableWidget->item(7,8)->setText("Мощность_рассеяния_8, Вт");
            ui->widget_5->ui->tableWidget->item(8,8)->setText("Мощность_рассеяния_9, Вт");
            ui->widget_5->ui->tableWidget->item(9,8)->setText("Мощность_рассеяния_10, Вт");
            ui->widget_5->ui->tableWidget->item(10,8)->setText("Мощность_рассеяния_11, Вт");
            ui->widget_5->ui->tableWidget->item(11,8)->setText("Мощность_рассеяния_12, Вт");
            ui->widget_5->ui->tableWidget->item(12,8)->setText("Мощность_рассеяния_13, Вт");
            ui->widget_5->ui->tableWidget->item(13,8)->setText("Мощность_рассеяния_14, Вт");
            ui->widget_5->ui->tableWidget->item(14,8)->setText("Мощность_рассеяния_15, Вт");

            ui->widget_5->ui->tableWidget->item(0,9)->setText(QString::number(P_10,'f',3));
            ui->widget_5->ui->tableWidget->item(1,9)->setText(QString::number(P_30,'f',3));
            ui->widget_5->ui->tableWidget->item(2,9)->setText(QString::number(P_k0,'f',3));
            ui->widget_5->ui->tableWidget->item(3,9)->setText(QString::number(P_50,'f',3));
            ui->widget_5->ui->tableWidget->item(4,9)->setText(QString::number(P_3k,'f',3));
            ui->widget_5->ui->tableWidget->item(5,9)->setText(QString::number(P_21,'f',3));
            ui->widget_5->ui->tableWidget->item(6,9)->setText(QString::number(P_c2,'f',3));
            ui->widget_5->ui->tableWidget->item(7,9)->setText(QString::number(P_c3,'f',3));
            ui->widget_5->ui->tableWidget->item(8,9)->setText(QString::number(P_c4,'f',3));
            ui->widget_5->ui->tableWidget->item(9,9)->setText(QString::number(P_45,'f',3));
            ui->widget_5->ui->tableWidget->item(10,9)->setText(QString::number(P_pc,'f',3));
            ui->widget_5->ui->tableWidget->item(11,9)->setText(QString::number(P_pb,'f',3));
            ui->widget_5->ui->tableWidget->item(12,9)->setText(QString::number(P_b5,'f',3));
            ui->widget_5->ui->tableWidget->item(13,9)->setText(QString::number(P_p5,'f',3));
            ui->widget_5->ui->tableWidget->item(14,9)->setText(QString::number(P_p2,'f',3));

            //Расчет падений температур
            d_teta_10=10;
            d_teta_30=22;
            d_teta_k0=23;
            d_teta_50=45;
            d_teta_3k=12;
            d_teta_21=34;
            d_teta_c2=56;
            d_teta_c3=50;
            d_teta_c4=76;
            d_teta_45=10;
            d_teta_pc=22;
            d_teta_pb=23;
            d_teta_b5=45;
            d_teta_p5=12;
            d_teta_p2=34;

            //Вывод падений температур в таблицу
            ui->widget_5->ui->tableWidget->item(0,10)->setText("Падение_температуры_1, °C");
            ui->widget_5->ui->tableWidget->item(1,10)->setText("Падение_температуры_2, °C");
            ui->widget_5->ui->tableWidget->item(2,10)->setText("Падение_температуры_3, °C");
            ui->widget_5->ui->tableWidget->item(3,10)->setText("Падение_температуры_4, °C");
            ui->widget_5->ui->tableWidget->item(4,10)->setText("Падение_температуры_5, °C");
            ui->widget_5->ui->tableWidget->item(5,10)->setText("Падение_температуры_6, °C");
            ui->widget_5->ui->tableWidget->item(6,10)->setText("Падение_температуры_7, °C");
            ui->widget_5->ui->tableWidget->item(7,10)->setText("Падение_температуры_8, °C");
            ui->widget_5->ui->tableWidget->item(8,10)->setText("Падение_температуры_9, °C");
            ui->widget_5->ui->tableWidget->item(9,10)->setText("Падение_температуры_10, °C");
            ui->widget_5->ui->tableWidget->item(10,10)->setText("Падение_температуры_11, °C");
            ui->widget_5->ui->tableWidget->item(11,10)->setText("Падение_температуры_12, °C");
            ui->widget_5->ui->tableWidget->item(12,10)->setText("Падение_температуры_13, °C");
            ui->widget_5->ui->tableWidget->item(13,10)->setText("Падение_температуры_14, °C");
            ui->widget_5->ui->tableWidget->item(14,10)->setText("Падение_температуры_15, °C");

            ui->widget_5->ui->tableWidget->item(0,11)->setText(QString::number(d_teta_10,'f',3));
            ui->widget_5->ui->tableWidget->item(1,11)->setText(QString::number(d_teta_30,'f',3));
            ui->widget_5->ui->tableWidget->item(2,11)->setText(QString::number(d_teta_k0,'f',3));
            ui->widget_5->ui->tableWidget->item(3,11)->setText(QString::number(d_teta_50,'f',3));
            ui->widget_5->ui->tableWidget->item(4,11)->setText(QString::number(d_teta_3k,'f',3));
            ui->widget_5->ui->tableWidget->item(5,11)->setText(QString::number(d_teta_21,'f',3));
            ui->widget_5->ui->tableWidget->item(6,11)->setText(QString::number(d_teta_c2,'f',3));
            ui->widget_5->ui->tableWidget->item(7,11)->setText(QString::number(d_teta_c3,'f',3));
            ui->widget_5->ui->tableWidget->item(8,11)->setText(QString::number(d_teta_c4,'f',3));
            ui->widget_5->ui->tableWidget->item(9,11)->setText(QString::number(d_teta_45,'f',3));
            ui->widget_5->ui->tableWidget->item(10,11)->setText(QString::number(d_teta_pc,'f',3));
            ui->widget_5->ui->tableWidget->item(11,11)->setText(QString::number(d_teta_pb,'f',3));
            ui->widget_5->ui->tableWidget->item(12,11)->setText(QString::number(d_teta_b5,'f',3));
            ui->widget_5->ui->tableWidget->item(13,11)->setText(QString::number(d_teta_p5,'f',3));
            ui->widget_5->ui->tableWidget->item(14,11)->setText(QString::number(d_teta_p2,'f',3));
        }
        if (item30->text() == "Статика (полный вариант)")
        {
            QMessageBox::information(this, "вариант 3!", "Статика (полный вариант)");
        }
        if (item30->text() == "Динамика (расчет)")
        {
            ui->tepl_result->setCheckable(true);
            if(ui->tepl_result->isChecked())
            {
                progress->setVisible(true);
                progress->setRange(0, 64 - 1);
                progress->reset();
                ui->widget_5->ui->widget_4->startTeplo();
            }
            else
            {
                ui->widget_5->ui->widget_4->stopTeplo();
            }
        }
        if (item30->text() == "Динамика (эксперимент)")
        {
            QMessageBox::information(this, "вариант 3!", "Статика (полный вариант)");
        }
        if (item30->text() == "Двухмассовая модель (расчет)")
        {
            ui->widget_5->ui->tabWidget->show();
            ui->widget_5->ui->tabWidget->setCurrentIndex(11);
            //ввод данных
            base_tepl.Da1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(0,1)->text().toDouble();
            base_tepl.Ha1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(1,1)->text().toDouble();
            base_tepl.lambda_c1       = ui->widget_5->ui->widget_2->ui->tableWidget->item(2,1)->text().toDouble();
            base_tepl.L1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(3,1)->text().toDouble();
            base_tepl.delta_ct = ui->widget_5->ui->widget_2->ui->tableWidget->item(4,1)->text().toDouble();
            base_tepl.lambda_ct   = ui->widget_5->ui->widget_2->ui->tableWidget->item(5,1)->text().toDouble();
            base_tepl.lambda_i  = ui->widget_5->ui->widget_2->ui->tableWidget->item(6,1)->text().toDouble();
            base_tepl.delta_ai     = ui->widget_5->ui->widget_2->ui->tableWidget->item(7,1)->text().toDouble();
            base_tepl.Kc1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(8,1)->text().toDouble();
            base_tepl.Di1   = ui->widget_5->ui->widget_2->ui->tableWidget->item(9,1)->text().toDouble();

            base_tepl.Z1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(10,1)->text().toDouble();
            base_tepl.Bz1       = ui->widget_5->ui->widget_2->ui->tableWidget->item(11,1)->text().toDouble();
            base_tepl.lambda_с     = ui->widget_5->ui->widget_2->ui->tableWidget->item(12,1)->text().toDouble();
            base_tepl.Hz1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(13,1)->text().toDouble();
            base_tepl.lambda_ip1    = ui->widget_5->ui->widget_2->ui->tableWidget->item(14,1)->text().toDouble();
            base_tepl.delta_ip1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(15,1)->text().toDouble();
            base_tepl.Kz      = ui->widget_5->ui->widget_2->ui->tableWidget->item(16,1)->text().toDouble();
            base_tepl.d1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(17,1)->text().toDouble();
            base_tepl.teta_m     = ui->widget_5->ui->widget_2->ui->tableWidget->item(18,1)->text().toDouble();
            base_tepl.Kp   = ui->widget_5->ui->widget_2->ui->tableWidget->item(19,1)->text().toDouble();

            base_tepl.lambda_l   = ui->widget_5->ui->widget_2->ui->tableWidget->item(20,1)->text().toDouble();
            base_tepl.lambda_em    = ui->widget_5->ui->widget_2->ui->tableWidget->item(21,1)->text().toDouble();
            base_tepl.Bp     = ui->widget_5->ui->widget_2->ui->tableWidget->item(22,1)->text().toDouble();
            base_tepl.sigma_ipr     = ui->widget_5->ui->widget_2->ui->tableWidget->item(23,1)->text().toDouble();
            base_tepl.sigma_i       = ui->widget_5->ui->widget_2->ui->tableWidget->item(24,1)->text().toDouble();
            base_tepl.lambda_ek    = ui->widget_5->ui->widget_2->ui->tableWidget->item(25,1)->text().toDouble();
            base_tepl.lambda_mi    = ui->widget_5->ui->widget_2->ui->tableWidget->item(26,1)->text().toDouble();
            base_tepl.q_mi     = ui->widget_5->ui->widget_2->ui->tableWidget->item(27,1)->text().toDouble();
            base_tepl.Lp1 = ui->widget_5->ui->widget_2->ui->tableWidget->item(28,1)->text().toDouble();
            base_tepl.Lambda_el  = ui->widget_5->ui->widget_2->ui->tableWidget->item(29,1)->text().toDouble();

            base_tepl.lambda_ekuz   = ui->widget_5->ui->widget_2->ui->tableWidget->item(30,1)->text().toDouble();
            base_tepl.lambda_ekpa     = ui->widget_5->ui->widget_2->ui->tableWidget->item(31,1)->text().toDouble();
            base_tepl.n     = ui->widget_5->ui->widget_2->ui->tableWidget->item(32,1)->text().toDouble();
            base_tepl.Dv1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(33,1)->text().toDouble();
            base_tepl.nu     = ui->widget_5->ui->widget_2->ui->tableWidget->item(34,1)->text().toDouble();
            base_tepl.K_l1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(35,1)->text().toDouble();
            base_tepl.lambda_il     = ui->widget_5->ui->widget_2->ui->tableWidget->item(36,1)->text().toDouble();
            base_tepl.delta_il1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(37,1)->text().toDouble();
            base_tepl.lambda_m2     = ui->widget_5->ui->widget_2->ui->tableWidget->item(38,1)->text().toDouble();
            base_tepl.qc      = ui->widget_5->ui->widget_2->ui->tableWidget->item(39,1)->text().toDouble();

            base_tepl.L2    = ui->widget_5->ui->widget_2->ui->tableWidget->item(40,1)->text().toDouble();
            base_tepl.Bk    = ui->widget_5->ui->widget_2->ui->tableWidget->item(41,1)->text().toDouble();
            base_tepl.Z2    = ui->widget_5->ui->widget_2->ui->tableWidget->item(42,1)->text().toDouble();
            base_tepl.u_rot    = ui->widget_5->ui->widget_2->ui->tableWidget->item(43,1)->text().toDouble();
            base_tepl.Dl    = ui->widget_5->ui->widget_2->ui->tableWidget->item(44,1)->text().toDouble();
            base_tepl.S_l2  = ui->widget_5->ui->widget_2->ui->tableWidget->item(45,1)->text().toDouble();
            base_tepl.S_isch    = ui->widget_5->ui->widget_2->ui->tableWidget->item(46,1)->text().toDouble();
            base_tepl.S_ist    = ui->widget_5->ui->widget_2->ui->tableWidget->item(47,1)->text().toDouble();
            base_tepl.alpha_r    = ui->widget_5->ui->widget_2->ui->tableWidget->item(48,1)->text().toDouble();

            base_tepl.alpha_st      = ui->widget_5->ui->widget_2->ui->tableWidget->item(49,1)->text().toDouble();
            base_tepl.h_p    = ui->widget_5->ui->widget_2->ui->tableWidget->item(50,1)->text().toDouble();
            base_tepl.t_p    = ui->widget_5->ui->widget_2->ui->tableWidget->item(51,1)->text().toDouble();
            base_tepl.n_p    = ui->widget_5->ui->widget_2->ui->tableWidget->item(52,1)->text().toDouble();
            base_tepl.a_p    = ui->widget_5->ui->widget_2->ui->tableWidget->item(53,1)->text().toDouble();
            base_tepl.D_ct    = ui->widget_5->ui->widget_2->ui->tableWidget->item(54,1)->text().toDouble();
            base_tepl.u2  = ui->widget_5->ui->widget_2->ui->tableWidget->item(55,1)->text().toDouble();
            base_tepl.alpha_c   = ui->widget_5->ui->widget_2->ui->tableWidget->item(59,1)->text().toDouble();
            base_tepl.delta_Kp  = ui->widget_5->ui->widget_2->ui->tableWidget->item(60,1)->text().toDouble();
            base_tepl.Dp1  = ui->widget_5->ui->widget_2->ui->tableWidget->item(61,1)->text().toDouble();
            base_tepl.lambda_v   = ui->widget_5->ui->widget_2->ui->tableWidget->item(62,1)->text().toDouble();

            //Расчет переменных состояния


            teta0_0=item28->text().toDouble();

            teta0_1n=80;
            teta0_2n=70;

            C_0=0;
            C_1=0;

            d_teta_10=10;
            d_teta_30=22;

            if(ui->tableWidget_4->item(1,2)!=0)
            {
                tepl_struct.dPel1=ui->tableWidget_4->item(1,2)->text().toDouble();
            }

            if(ui->tableWidget_4->item(2,2)!=0)
            {
                tepl_struct.dPct=ui->tableWidget_4->item(2,2)->text().toDouble();
            }

            if(ui->tableWidget_4->item(3,2)!=0)
            {
                tepl_struct.dPel2=ui->tableWidget_4->item(3,2)->text().toDouble();
            }

           lambda0_10 = (tepl_struct.dPel1+tepl_struct.dPct)/teta0_1n;
           lambda0_20 = (tepl_struct.dPel1+tepl_struct.dPct)/teta0_2n;
           lambda0_12 = (tepl_struct.dPel1+tepl_struct.dPel2+tepl_struct.dPct)/(teta0_2n-teta0_2n);

            //Решение СЛАУ

            double n = 0;
            double n_k = 10000;
            while(n<n_k)
            {
                n+=0.1;
            double a_data[] = { lambda0_10+lambda0_12, -lambda0_12,
                                -lambda0_12, lambda0_10+lambda0_12 };

            //double b_data[] = { dPel1+dPct+lambda0_10*teta0_0, dPel2+lambda0_10*teta0_0 };

            double b_data[] = { tepl_struct.dPel1+tepl_struct.dPct+lambda0_10*teta0_0, tepl_struct.dPel2+lambda0_10*teta0_0 };

            gsl_matrix_view m = gsl_matrix_view_array (a_data, 2, 2);

            gsl_vector_view b = gsl_vector_view_array (b_data, 2);

            gsl_vector *x = gsl_vector_alloc (2);

            int s;

            gsl_permutation * p = gsl_permutation_alloc (2);

            gsl_linalg_LU_decomp (&m.matrix, p, &s);

            gsl_linalg_LU_solve (&m.matrix, p, &b.vector, x);

            //ВЫВОД ДАННЫХ В ТАБЛИЦЫ

            //вывод температур в таблицу
            teta0_1=gsl_vector_get(x, 0);
            teta0_2=gsl_vector_get(x, 1);

            gsl_permutation_free (p);
            gsl_vector_free (x);

            //Вывод температур в таблицу
            ui->widget_5->ui->tableWidget->item(0,0)->setText("Температура_1, °C");
            ui->widget_5->ui->tableWidget->item(1,0)->setText("Температура_2, °C");

            ui->widget_5->ui->tableWidget->item(0,1)->setText(QString::number(teta0_1,'f',3));
            ui->widget_5->ui->tableWidget->item(1,1)->setText(QString::number(teta0_2,'f',3));

            ui->widget_5->ui->tableWidget->item(0,2)->setText("Теплоемкость_1, Дж/К");
            ui->widget_5->ui->tableWidget->item(1,2)->setText("Теплоемкость_2, Дж/К");

            ui->widget_5->ui->tableWidget->item(0,3)->setText(QString::number(C_0,'f',3));
            ui->widget_5->ui->tableWidget->item(1,3)->setText(QString::number(C_1,'f',3));

            ui->widget_5->ui->tableWidget->item(0,4)->setText("Мощность_рассеяния_1, Вт");
            ui->widget_5->ui->tableWidget->item(1,4)->setText("Мощность_рассеяния_2, Вт");

            ui->widget_5->ui->tableWidget->item(0,5)->setText(QString::number(tepl_struct.dPel1+tepl_struct.dPct+lambda0_10*teta0_0,'f',3));
            ui->widget_5->ui->tableWidget->item(1,5)->setText(QString::number(tepl_struct.dPel2+lambda0_10*teta0_0,'f',3));

            //ui->widget_5->ui->tableWidget->item(0,5)->setText(QString::number(dPel1+dPct+lambda0_10*teta0_0,'f',3));
            //ui->widget_5->ui->tableWidget->item(1,5)->setText(QString::number(dPel2+lambda0_10*teta0_0,'f',3));


            ui->widget_5->ui->tableWidget->item(0,6)->setText("Теплопроводность_1, Вт/°C");
            ui->widget_5->ui->tableWidget->item(1,6)->setText("Теплопроводность_2, Вт/°C");

            ui->widget_5->ui->tableWidget->item(0,7)->setText(QString::number(lambda_10,'f',3));
            ui->widget_5->ui->tableWidget->item(1,7)->setText(QString::number(lambda_30,'f',3));

            ui->widget_5->ui->tableWidget->item(0,8)->setText("Падение_температуры_1, °C");
            ui->widget_5->ui->tableWidget->item(1,8)->setText("Падение_температуры_2, °C");

            ui->widget_5->ui->tableWidget->item(0,9)->setText(QString::number(d_teta_10,'f',3));
            ui->widget_5->ui->tableWidget->item(1,9)->setText(QString::number(d_teta_30,'f',3));
        }}
        if (item30->text() == "Двухмассовая модель (эксперимент)")
        {
            ui->widget_5->ui->tabWidget->show();
            ui->widget_5->ui->tabWidget->setCurrentIndex(11);
            //ввод данных
            base_tepl.Da1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(0,1)->text().toDouble();
            base_tepl.Ha1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(1,1)->text().toDouble();
            base_tepl.lambda_c1       = ui->widget_5->ui->widget_2->ui->tableWidget->item(2,1)->text().toDouble();
            base_tepl.L1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(3,1)->text().toDouble();
            base_tepl.delta_ct = ui->widget_5->ui->widget_2->ui->tableWidget->item(4,1)->text().toDouble();
            base_tepl.lambda_ct   = ui->widget_5->ui->widget_2->ui->tableWidget->item(5,1)->text().toDouble();
            base_tepl.lambda_i  = ui->widget_5->ui->widget_2->ui->tableWidget->item(6,1)->text().toDouble();
            base_tepl.delta_ai     = ui->widget_5->ui->widget_2->ui->tableWidget->item(7,1)->text().toDouble();
            base_tepl.Kc1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(8,1)->text().toDouble();
            base_tepl.Di1   = ui->widget_5->ui->widget_2->ui->tableWidget->item(9,1)->text().toDouble();

            base_tepl.Z1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(10,1)->text().toDouble();
            base_tepl.Bz1       = ui->widget_5->ui->widget_2->ui->tableWidget->item(11,1)->text().toDouble();
            base_tepl.lambda_с     = ui->widget_5->ui->widget_2->ui->tableWidget->item(12,1)->text().toDouble();
            base_tepl.Hz1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(13,1)->text().toDouble();
            base_tepl.lambda_ip1    = ui->widget_5->ui->widget_2->ui->tableWidget->item(14,1)->text().toDouble();
            base_tepl.delta_ip1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(15,1)->text().toDouble();
            base_tepl.Kz      = ui->widget_5->ui->widget_2->ui->tableWidget->item(16,1)->text().toDouble();
            base_tepl.d1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(17,1)->text().toDouble();
            base_tepl.teta_m     = ui->widget_5->ui->widget_2->ui->tableWidget->item(18,1)->text().toDouble();
            base_tepl.Kp   = ui->widget_5->ui->widget_2->ui->tableWidget->item(19,1)->text().toDouble();

            base_tepl.lambda_l   = ui->widget_5->ui->widget_2->ui->tableWidget->item(20,1)->text().toDouble();
            base_tepl.lambda_em    = ui->widget_5->ui->widget_2->ui->tableWidget->item(21,1)->text().toDouble();
            base_tepl.Bp     = ui->widget_5->ui->widget_2->ui->tableWidget->item(22,1)->text().toDouble();
            base_tepl.sigma_ipr     = ui->widget_5->ui->widget_2->ui->tableWidget->item(23,1)->text().toDouble();
            base_tepl.sigma_i       = ui->widget_5->ui->widget_2->ui->tableWidget->item(24,1)->text().toDouble();
            base_tepl.lambda_ek    = ui->widget_5->ui->widget_2->ui->tableWidget->item(25,1)->text().toDouble();
            base_tepl.lambda_mi    = ui->widget_5->ui->widget_2->ui->tableWidget->item(26,1)->text().toDouble();
            base_tepl.q_mi     = ui->widget_5->ui->widget_2->ui->tableWidget->item(27,1)->text().toDouble();
            base_tepl.Lp1 = ui->widget_5->ui->widget_2->ui->tableWidget->item(28,1)->text().toDouble();
            base_tepl.Lambda_el  = ui->widget_5->ui->widget_2->ui->tableWidget->item(29,1)->text().toDouble();

            base_tepl.lambda_ekuz   = ui->widget_5->ui->widget_2->ui->tableWidget->item(30,1)->text().toDouble();
            base_tepl.lambda_ekpa     = ui->widget_5->ui->widget_2->ui->tableWidget->item(31,1)->text().toDouble();
            base_tepl.n     = ui->widget_5->ui->widget_2->ui->tableWidget->item(32,1)->text().toDouble();
            base_tepl.Dv1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(33,1)->text().toDouble();
            base_tepl.nu     = ui->widget_5->ui->widget_2->ui->tableWidget->item(34,1)->text().toDouble();
            base_tepl.K_l1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(35,1)->text().toDouble();
            base_tepl.lambda_il     = ui->widget_5->ui->widget_2->ui->tableWidget->item(36,1)->text().toDouble();
            base_tepl.delta_il1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(37,1)->text().toDouble();
            base_tepl.lambda_m2     = ui->widget_5->ui->widget_2->ui->tableWidget->item(38,1)->text().toDouble();
            base_tepl.qc      = ui->widget_5->ui->widget_2->ui->tableWidget->item(39,1)->text().toDouble();

            base_tepl.L2    = ui->widget_5->ui->widget_2->ui->tableWidget->item(40,1)->text().toDouble();
            base_tepl.Bk    = ui->widget_5->ui->widget_2->ui->tableWidget->item(41,1)->text().toDouble();
            base_tepl.Z2    = ui->widget_5->ui->widget_2->ui->tableWidget->item(42,1)->text().toDouble();
            base_tepl.u_rot    = ui->widget_5->ui->widget_2->ui->tableWidget->item(43,1)->text().toDouble();
            base_tepl.Dl    = ui->widget_5->ui->widget_2->ui->tableWidget->item(44,1)->text().toDouble();
            base_tepl.S_l2  = ui->widget_5->ui->widget_2->ui->tableWidget->item(45,1)->text().toDouble();
            base_tepl.S_isch    = ui->widget_5->ui->widget_2->ui->tableWidget->item(46,1)->text().toDouble();
            base_tepl.S_ist    = ui->widget_5->ui->widget_2->ui->tableWidget->item(47,1)->text().toDouble();
            base_tepl.alpha_r    = ui->widget_5->ui->widget_2->ui->tableWidget->item(48,1)->text().toDouble();

            base_tepl.alpha_st      = ui->widget_5->ui->widget_2->ui->tableWidget->item(49,1)->text().toDouble();
            base_tepl.h_p    = ui->widget_5->ui->widget_2->ui->tableWidget->item(50,1)->text().toDouble();
            base_tepl.t_p    = ui->widget_5->ui->widget_2->ui->tableWidget->item(51,1)->text().toDouble();
            base_tepl.n_p    = ui->widget_5->ui->widget_2->ui->tableWidget->item(52,1)->text().toDouble();
            base_tepl.a_p    = ui->widget_5->ui->widget_2->ui->tableWidget->item(53,1)->text().toDouble();
            base_tepl.D_ct    = ui->widget_5->ui->widget_2->ui->tableWidget->item(54,1)->text().toDouble();
            base_tepl.u2  = ui->widget_5->ui->widget_2->ui->tableWidget->item(55,1)->text().toDouble();
            base_tepl.alpha_c   = ui->widget_5->ui->widget_2->ui->tableWidget->item(59,1)->text().toDouble();
            base_tepl.delta_Kp  = ui->widget_5->ui->widget_2->ui->tableWidget->item(60,1)->text().toDouble();
            base_tepl.Dp1  = ui->widget_5->ui->widget_2->ui->tableWidget->item(61,1)->text().toDouble();
            base_tepl.lambda_v   = ui->widget_5->ui->widget_2->ui->tableWidget->item(62,1)->text().toDouble();



        }
    }
}

void MainWindow::on_vent_result_clicked()
{
    ui->tabWidget->show();
    ui->tabWidget->setCurrentIndex(5);
    ui->widget_6->ui->tabWidget->show();
    ui->widget_6->ui->tabWidget->setCurrentIndex(1);
    ui->stackedWidget->show();
    ui->stackedWidget->setCurrentIndex(17);

    if (item34->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if ((item34->text() == "Статика")&&(item36->text() == "Один вентилятор"))
        {
            ui->widget_6->ui->tabWidget_3->show();
            ui->widget_6->ui->tabWidget_3->setCurrentIndex(0);
            ui->stackedWidget->show();
            ui->stackedWidget->setCurrentIndex(17);

            base_tepl.D1p      = ui->tableWidget_7->item(0,2)->text().toDouble();
            base_tepl.D2p      = ui->tableWidget_7->item(1,2)->text().toDouble();
            base_tepl.b       = ui->tableWidget_7->item(2,2)->text().toDouble();
            base_tepl.n2     = ui->tableWidget_7->item(3,2)->text().toDouble();
            base_tepl.ro = ui->tableWidget_7->item(4,2)->text().toDouble();
            base_tepl.Sotv   = ui->tableWidget_7->item(5,2)->text().toDouble();
            base_tepl.S0  = ui->tableWidget_7->item(6,2)->text().toDouble();
            base_tepl.S1     = ui->tableWidget_7->item(7,2)->text().toDouble();
            base_tepl.alpha1     = ui->tableWidget_7->item(8,2)->text().toDouble();
            base_tepl.S2   = ui->tableWidget_7->item(9,2)->text().toDouble();
            base_tepl.alpha2     = ui->tableWidget_7->item(10,2)->text().toDouble();
            base_tepl.S3   = ui->tableWidget_7->item(11,2)->text().toDouble();
            base_tepl.S4   = ui->tableWidget_7->item(12,2)->text().toDouble();
            base_tepl.fi     = ui->tableWidget_7->item(13,2)->text().toDouble();
            base_tepl.fi2   = ui->tableWidget_7->item(14,2)->text().toDouble();

            //Начальное давление вентилятора:
            H0=0.00695 * pow(base_tepl.n2,2) * (pow(base_tepl.D2p,2) - pow(base_tepl.D1p,2));

            //Максимальный расход воздуха:
            Qmax = 0.006 * pow(base_tepl.D2p,2) * base_tepl.b * base_tepl.n2;

            //Сопротивление входа в кожух через решетку с острыми кромками
            base_tepl.epsilon1 = 0.5;
            Z1 = base_tepl.epsilon1 * (base_tepl.ro / (2 * pow(base_tepl.Sotv,2)));

            //Сопротивление поворота потока за входной решеткой перед входом в вентилятор
            base_tepl.epsilon2 = 0.5;
            Z2 = base_tepl.epsilon2 * (base_tepl.ro / (2 * pow(base_tepl.S1,2)));

            //Сопротивление потока за входным вентилятором перед входом в межреберные каналы
            base_tepl.epsilon3 = 0.5;
            Z3 = base_tepl.epsilon3 * (base_tepl.ro / (2 * pow(base_tepl.S2,2)));

            //Сопротивление косого входа в межреберные каналы
            base_tepl.epsilon4 = 0.5;
            base_tepl.cosf = 0.7;
            Z4 = base_tepl.epsilon4 * (base_tepl.ro / (2 * pow( base_tepl.S4,2) * pow(base_tepl.cosf,2)));

            //Сопротивление поворота потока в межреберных каналах под кожухом
            base_tepl.epsilon5 = 0.5;
            Z5 = base_tepl.epsilon5 * (base_tepl.ro / (2 * pow(base_tepl.S4,2)));

            //Сопротивление выхода воздуха из межреберных каналов в воздушное пространство
            base_tepl.epsilon6 = 0.5;
            Z6 = base_tepl.epsilon6 * (base_tepl.ro / (2 * pow(base_tepl.S4,2)));

            //Суммарное сопротивление вентиляционной сети
            Z0=1.2 *(Z1 + Z2 + Z3 + Z4 + Z5 + Z6);

            //Рабочий расход воздуха
            Qp = Qmax * sqrt(H0 /(H0 + Z0 * pow(Qmax,2)));

            //Рабочий набор вентилятора
            Hp = Z0 * pow(Qp,2);

            //Средняя скорость воздуха в межреберных каналах
            base_tepl.K = 1;
            Vcp = base_tepl.K *Qp /base_tepl.S4;

            //Потребляемая вентилятором мощность
            base_tepl.nu2 = 0.7;
            Pvent = 9.81 * (Qp * Hp / base_tepl.nu2);



            if (ui->tableWidget_13->item(0, 2) != 0)
            {
                ui->tableWidget_13->item(0, 2)->setText(QString::number(H0,'f',3));
            }

            if (ui->tableWidget_13->item(1, 2) != 0)
            {
                ui->tableWidget_13->item(1, 2)->setText(QString::number(Qmax,'f',3));
            }

            if (ui->tableWidget_13->item(2, 2) != 0)
            {
                ui->tableWidget_13->item(2, 2)->setText(QString::number(Z1,'f',3));
            }

            if (ui->tableWidget_13->item(3, 2) != 0)
            {
                ui->tableWidget_13->item(3, 2)->setText(QString::number(Z2,'f',3));
            }
            if (ui->tableWidget_13->item(4, 2) != 0)
            {
                ui->tableWidget_13->item(4, 2)->setText(QString::number(Z3,'f',3));
            }

            if (ui->tableWidget_13->item(5, 2) != 0)
            {
                ui->tableWidget_13->item(5, 2)->setText(QString::number(Z4,'f',3));
            }

            if (ui->tableWidget_13->item(6, 2) != 0)
            {
                ui->tableWidget_13->item(6, 2)->setText(QString::number(Z5,'f',3));
            }

            if (ui->tableWidget_13->item(7, 2) != 0)
            {
                ui->tableWidget_13->item(7, 2)->setText(QString::number(Z6,'f',3));
            }

            if (ui->tableWidget_13->item(8, 2) != 0)
            {
                ui->tableWidget_13->item(8, 2)->setText(QString::number(Z0,'f',6));
            }

            if (ui->tableWidget_13->item(9, 2) != 0)
            {
                ui->tableWidget_13->item(9, 2)->setText(QString::number(Qp,'f',6));
            }

            if (ui->tableWidget_13->item(10, 2) != 0)
            {
                ui->tableWidget_13->item(10, 2)->setText(QString::number(Hp,'f',6));
            }

            if (ui->tableWidget_13->item(11, 2) != 0)
            {
                ui->tableWidget_13->item(11, 2)->setText(QString::number(Vcp,'f',6));
            }

            if (ui->tableWidget_13->item(12, 2) != 0)
            {
                ui->tableWidget_13->item(12, 2)->setText(QString::number(Pvent,'f',6));
            }


            double Q =0;
            double H1 = 0;
            double H2 = 0;
            //double ne = 0;
            double Pv = 0;
            double P_ct = 0;
            double P_din = 0;
            double v = 1.5;
            double N = 0;
            double Nu = 0;
            double Nu_ct = 0;
            double M = 0;
            double omega = 0;
            ui->widget_6->ui->plot->clear();
            ui->widget_6->ui->plot->addDataLine(QColor(Qt::red), 0);
            ui->widget_6->ui->plot->addDataLine(QColor(Qt::green), 0);
            ui->widget_6->ui->plot->addDataLine(QColor(Qt::blue), 0);
            ui->widget_6->ui->plot->addDataLine(QColor(Qt::green), 0);
            ui->widget_6->ui->plot->addDataLine(QColor(Qt::blue), 0);

            while (Q < Qp)
            {
                Q+=0.00001;
                H1 = Z0/100 * pow(Q,2);
                H2 = H0/100 *(1 - pow((Q/Qmax),2));
                Pv=Q*H1;
                P_din=1.2*pow(v,2);
                P_ct=Pv-P_din;
                ui->widget_6->ui->plot->addPoint(0, Q, H1);
                ui->widget_6->ui->plot->addPoint(1, Q, H2);
                ui->widget_6->ui->plot->addPoint(2, Q, Pv);
                ui->widget_6->ui->plot->addPoint(3, Q, P_din);
                ui->widget_6->ui->plot->addPoint(4, Q, P_ct);
            }

            if (ui->tableWidget_8->item(0, 2) != 0)
            {
                ui->tableWidget_8->item(0, 2)->setText(QString::number(P_ct,'f',3));
            }
            if (ui->tableWidget_8->item(1, 2) != 0)
            {
                ui->tableWidget_8->item(1, 2)->setText(QString::number(P_din,'f',3));
            }
            if (ui->tableWidget_8->item(2, 2) != 0)
            {
                ui->tableWidget_8->item(2, 2)->setText(QString::number(Pv,'f',3));
            }
            if (ui->tableWidget_8->item(3, 2) != 0)
            {
                ui->tableWidget_8->item(3, 2)->setText(QString::number(Q,'f',3));
            }
            if (ui->tableWidget_8->item(4, 2) != 0)
            {
                ui->tableWidget_8->item(4, 2)->setText(QString::number(N,'f',3));
            }
            if (ui->tableWidget_8->item(5, 2) != 0)
            {
                ui->tableWidget_8->item(5, 2)->setText(QString::number(Nu,'f',3));
            }
            if (ui->tableWidget_8->item(6, 2) != 0)
            {
                ui->tableWidget_8->item(6, 2)->setText(QString::number(Nu_ct,'f',3));
            }
            if (ui->tableWidget_8->item(7, 2) != 0)
            {
                ui->tableWidget_8->item(7, 2)->setText(QString::number(M,'f',3));
            }
            if (ui->tableWidget_8->item(8, 2) != 0)
            {
                ui->tableWidget_8->item(8, 2)->setText(QString::number(omega,'f',3));
            }

           // ne=0.19*sin(M_PI)*(Qp/Qmax);
            Pv=(Qp*Hp);
            double dPvk=0.01;
            double dPsvp=0.001;
            double dPkd=0.6;
            double eps = 0.07;
            double dPptk = eps * base_tepl.ro * pow((Qp/base_tepl.S1),2);
            double dPvpk = eps * base_tepl.ro * pow((Qp/base_tepl.S1),2);


            //Расчет составляющих энергетической диаграммы вентилятора

            if (ui->tableWidget_11->item(5, 2) != 0)
            {
                ui->tableWidget_11->item(5, 2)->setText(QString::number(Pvent,'f',3));
            }
            if (ui->tableWidget_11->item(6, 2) != 0)
            {
                ui->tableWidget_11->item(6, 2)->setText(QString::number(Pv,'f',3));
            }
            if (ui->tableWidget_11->item(0, 2) != 0)
            {
                ui->tableWidget_11->item(0, 2)->setText(QString::number(dPptk,'f',3));
            }
            if (ui->tableWidget_11->item(1, 2) != 0)
            {
                ui->tableWidget_11->item(1, 2)->setText(QString::number(dPvpk,'f',3));
            }
            if (ui->tableWidget_11->item(2, 2) != 0)
            {
                ui->tableWidget_11->item(2, 2)->setText(QString::number(dPvk,'f',3));
            }
            if (ui->tableWidget_11->item(3, 2) != 0)
            {
                ui->tableWidget_11->item(3, 2)->setText(QString::number(dPsvp,'f',3));
            }
            if (ui->tableWidget_11->item(4, 2) != 0)
            {
                ui->tableWidget_11->item(4, 2)->setText(QString::number(dPkd,'f',3));
            }

            ui->widget_6->ui->webEngineView_4->page()->runJavaScript(QString("$(\"#text139\").text('Nsv = %1 Вт');").arg(Pvent, 0, 'f', 3));
            ui->widget_6->ui->webEngineView_4->page()->runJavaScript(QString("$(\"#text75\").text('N = %1 Вт');").arg(Pv, 0, 'f', 3));
            ui->widget_6->ui->webEngineView_4->page()->runJavaScript(QString("$(\"#text113\").text('ΔNptk = %1 Вт');").arg(dPptk, 0, 'f', 3));
            ui->widget_6->ui->webEngineView_4->page()->runJavaScript(QString("$(\"#text91\").text('ΔNvpk = %1 Вт');").arg(dPvpk, 0, 'f', 3));
            ui->widget_6->ui->webEngineView_4->page()->runJavaScript(QString("$(\"#text33\").text('ΔNvk = %1 Вт');").arg(dPvk, 0, 'f', 3));
            ui->widget_6->ui->webEngineView_4->page()->runJavaScript(QString("$(\"#text53\").text('ΔNsvp = %1 Вт');").arg(dPsvp, 0, 'f', 3));
            ui->widget_6->ui->webEngineView_4->page()->runJavaScript(QString("$(\"#text185\").text('ΔNkd = %1 Вт');").arg(dPkd, 0, 'f', 3));
        }
        if ((item34->text() == "Статика")&&(item36->text() == "Независимая вентиляция"))
        {
            ui->widget_6->ui->tabWidget_3->show();
            ui->widget_6->ui->tabWidget_3->setCurrentIndex(1);
            ui->stackedWidget->show();
            ui->stackedWidget->setCurrentIndex(17);

            base_tepl.D1p      = ui->tableWidget_7->item(0,2)->text().toDouble();
            base_tepl.D2p      = ui->tableWidget_7->item(1,2)->text().toDouble();
            base_tepl.b       = ui->tableWidget_7->item(2,2)->text().toDouble();
            base_tepl.n2     = ui->tableWidget_7->item(3,2)->text().toDouble();
            base_tepl.ro = ui->tableWidget_7->item(4,2)->text().toDouble();
            base_tepl.Sotv   = ui->tableWidget_7->item(5,2)->text().toDouble();
            base_tepl.S0  = ui->tableWidget_7->item(6,2)->text().toDouble();
            base_tepl.S1     = ui->tableWidget_7->item(7,2)->text().toDouble();
            base_tepl.alpha1     = ui->tableWidget_7->item(8,2)->text().toDouble();
            base_tepl.S2   = ui->tableWidget_7->item(9,2)->text().toDouble();
            base_tepl.alpha2     = ui->tableWidget_7->item(10,2)->text().toDouble();
            base_tepl.S3   = ui->tableWidget_7->item(11,2)->text().toDouble();
            base_tepl.S4   = ui->tableWidget_7->item(12,2)->text().toDouble();
            base_tepl.fi     = ui->tableWidget_7->item(13,2)->text().toDouble();
            base_tepl.fi2   = ui->tableWidget_7->item(14,2)->text().toDouble();

            //Начальное давление вентилятора:
            H0=0.00695 * pow(base_tepl.n2,2) * (pow(base_tepl.D2p,2) - pow(base_tepl.D1p,2));

            //Максимальный расход воздуха:
            Qmax = 0.006 * pow(base_tepl.D2p,2) * base_tepl.b * base_tepl.n2;

            //Сопротивление входа в кожух через решетку с острыми кромками
            base_tepl.epsilon1 = 0.5;
            Z1 = base_tepl.epsilon1 * (base_tepl.ro / (2 * pow(base_tepl.Sotv,2)));

            //Сопротивление поворота потока за входной решеткой перед входом в вентилятор
            base_tepl.epsilon2 = 0.5;
            Z2 = base_tepl.epsilon2 * (base_tepl.ro / (2 * pow(base_tepl.S1,2)));

            //Сопротивление потока за входным вентилятором перед входом в межреберные каналы
            base_tepl.epsilon3 = 0.5;
            Z3 = base_tepl.epsilon3 * (base_tepl.ro / (2 * pow(base_tepl.S2,2)));

            //Сопротивление косого входа в межреберные каналы
            base_tepl.epsilon4 = 0.5;
            base_tepl.cosf = 0.7;
            Z4 = base_tepl.epsilon4 * (base_tepl.ro / (2 * pow( base_tepl.S4,2) * pow(base_tepl.cosf,2)));

            //Сопротивление поворота потока в межреберных каналах под кожухом
            base_tepl.epsilon5 = 0.5;
            Z5 = base_tepl.epsilon5 * (base_tepl.ro / (2 * pow(base_tepl.S4,2)));

            //Сопротивление выхода воздуха из межреберных каналов в воздушное пространство
            base_tepl.epsilon6 = 0.5;
            Z6 = base_tepl.epsilon6 * (base_tepl.ro / (2 * pow(base_tepl.S4,2)));

            //Суммарное сопротивление вентиляционной сети
            Z0=1.2 *(Z1 + Z2 + Z3 + Z4 + Z5 + Z6);

            //Рабочий расход воздуха
            Qp = Qmax * sqrt(H0 /(H0 + Z0 * pow(Qmax,2)));

            //Рабочий набор вентилятора
            Hp = Z0 * pow(Qp,2);

            //Средняя скорость воздуха в межреберных каналах
            base_tepl.K = 1;
            Vcp = base_tepl.K *Qp /base_tepl.S4;

            //Потребляемая вентилятором мощность
            base_tepl.nu2 = 0.7;
            Pvent = 9.81 * (Qp * Hp / base_tepl.nu2);



            if (ui->tableWidget_13->item(0, 2) != 0)
            {
                ui->tableWidget_13->item(0, 2)->setText(QString::number(H0,'f',3));
            }

            if (ui->tableWidget_13->item(1, 2) != 0)
            {
                ui->tableWidget_13->item(1, 2)->setText(QString::number(Qmax,'f',3));
            }

            if (ui->tableWidget_13->item(2, 2) != 0)
            {
                ui->tableWidget_13->item(2, 2)->setText(QString::number(Z1,'f',3));
            }

            if (ui->tableWidget_13->item(3, 2) != 0)
            {
                ui->tableWidget_13->item(3, 2)->setText(QString::number(Z2,'f',3));
            }
            if (ui->tableWidget_13->item(4, 2) != 0)
            {
                ui->tableWidget_13->item(4, 2)->setText(QString::number(Z3,'f',3));
            }

            if (ui->tableWidget_13->item(5, 2) != 0)
            {
                ui->tableWidget_13->item(5, 2)->setText(QString::number(Z4,'f',3));
            }

            if (ui->tableWidget_13->item(6, 2) != 0)
            {
                ui->tableWidget_13->item(6, 2)->setText(QString::number(Z5,'f',3));
            }

            if (ui->tableWidget_13->item(7, 2) != 0)
            {
                ui->tableWidget_13->item(7, 2)->setText(QString::number(Z6,'f',3));
            }

            if (ui->tableWidget_13->item(8, 2) != 0)
            {
                ui->tableWidget_13->item(8, 2)->setText(QString::number(Z0,'f',6));
            }

            if (ui->tableWidget_13->item(9, 2) != 0)
            {
                ui->tableWidget_13->item(9, 2)->setText(QString::number(Qp,'f',6));
            }

            if (ui->tableWidget_13->item(10, 2) != 0)
            {
                ui->tableWidget_13->item(10, 2)->setText(QString::number(Hp,'f',6));
            }

            if (ui->tableWidget_13->item(11, 2) != 0)
            {
                ui->tableWidget_13->item(11, 2)->setText(QString::number(Vcp,'f',6));
            }

            if (ui->tableWidget_13->item(12, 2) != 0)
            {
                ui->tableWidget_13->item(12, 2)->setText(QString::number(Pvent,'f',6));
            }


            double Q =0;
            double H1 = 0;
            double H2 = 0;
            //double ne = 0;
            double Pv;
            ui->widget_6->ui->plot->clear();
            ui->widget_6->ui->plot->addDataLine(QColor(Qt::red), 0);
            ui->widget_6->ui->plot->addDataLine(QColor(Qt::green), 0);

            while (Q < Qp)
            {
                Q+=0.00001;
                H1 = Z0 * pow(Q,2);
                H2 = H0 *(1 - pow((Q/Qmax),2));
                ui->widget_6->ui->plot->addPoint(0, Q, H1);
                ui->widget_6->ui->plot->addPoint(1, Q, H2);
            }

            //ne=0.19*sin(M_PI)*(Qp/Qmax);
            Pv=(Qp*Hp);
            double dPvk=0.01;
            double dPsvp=0.001;
            double dPkd=0.6;

            double eps = 0.07;
            double dPptk = eps * base_tepl.ro * pow((Qp/base_tepl.S1),2);
            double dPvpk = eps * base_tepl.ro * pow((Qp/base_tepl.S1),2);

            //Расчет составляющих энергетической диаграммы вентилятора

            if (ui->tableWidget_11->item(5, 2) != 0)
            {
                ui->tableWidget_11->item(5, 2)->setText(QString::number(Pvent,'f',3));
            }
            if (ui->tableWidget_11->item(6, 2) != 0)
            {
                ui->tableWidget_11->item(6, 2)->setText(QString::number(Pv,'f',3));
            }
            if (ui->tableWidget_11->item(0, 2) != 0)
            {
                ui->tableWidget_11->item(0, 2)->setText(QString::number(dPptk,'f',3));
            }
            if (ui->tableWidget_11->item(1, 2) != 0)
            {
                ui->tableWidget_11->item(1, 2)->setText(QString::number(dPvpk,'f',3));
            }
            if (ui->tableWidget_11->item(2, 2) != 0)
            {
                ui->tableWidget_11->item(2, 2)->setText(QString::number(dPvk,'f',3));
            }
            if (ui->tableWidget_11->item(3, 2) != 0)
            {
                ui->tableWidget_11->item(3, 2)->setText(QString::number(dPsvp,'f',3));
            }
            if (ui->tableWidget_11->item(4, 2) != 0)
            {
                ui->tableWidget_11->item(4, 2)->setText(QString::number(dPkd,'f',3));
            }

            ui->widget_6->ui->webEngineView_4->page()->runJavaScript(QString("$(\"#text139\").text('Nsv = %1 Вт');").arg(Pvent, 0, 'f', 3));
            ui->widget_6->ui->webEngineView_4->page()->runJavaScript(QString("$(\"#text75\").text('N = %1 Вт');").arg(Pv, 0, 'f', 3));
            ui->widget_6->ui->webEngineView_4->page()->runJavaScript(QString("$(\"#text113\").text('ΔNptk = %1 Вт');").arg(dPptk, 0, 'f', 3));
            ui->widget_6->ui->webEngineView_4->page()->runJavaScript(QString("$(\"#text91\").text('ΔNvpk = %1 Вт');").arg(dPvpk, 0, 'f', 3));
            ui->widget_6->ui->webEngineView_4->page()->runJavaScript(QString("$(\"#text33\").text('ΔNvk = %1 Вт');").arg(dPvk, 0, 'f', 3));
            ui->widget_6->ui->webEngineView_4->page()->runJavaScript(QString("$(\"#text53\").text('ΔNsvp = %1 Вт');").arg(dPsvp, 0, 'f', 3));
            ui->widget_6->ui->webEngineView_4->page()->runJavaScript(QString("$(\"#text185\").text('ΔNkd = %1 Вт');").arg(dPkd, 0, 'f', 3));
        }
        if ((item34->text() == "Динамика")&&(item36->text() == "Динамика (расчет)"))
        {
            QMessageBox::information(this, "Динамика", "Динамика (расчет)");
        }
        if ((item34->text() == "Динамика")&&(item36->text() == "Динамика (эксперимент)"))
        {
            QMessageBox::information(this, "Динамика", "Динамика (эксперимент)");
        }
    }
}

void MainWindow::save_electromagn_graph_file()
{
    QString filters;
    foreach(QByteArray byte, QImageWriter::supportedImageFormats())
    {
        QString format = byte;
        filters += QString("%1 (%2)\n").arg(format.toUpper(),"*." + format);
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as..."), "img.png", filters);
    if (fileName.isEmpty() || fileName.isNull())
        return;

    ui->widget_2->ui->plot->grab().save(fileName);
}


void MainWindow::on_save_electromagn2_file_clicked()
{
    QString filters;
    foreach(QByteArray byte, QImageWriter::supportedImageFormats())
    {
        QString format = byte;
        filters += QString("%1 (%2)\n").arg(format.toUpper(),"*." + format);
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as..."), "img.png", filters);
    if (fileName.isEmpty() || fileName.isNull())
        return;

    ui->widget_3->ui->plot->grab().save(fileName);
}


void MainWindow::on_save_tepl_graph_file_clicked()
{
    QString filters;
    foreach(QByteArray byte, QImageWriter::supportedImageFormats())
    {
        QString format = byte;
        filters += QString("%1 (%2)\n").arg(format.toUpper(),"*." + format);
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as..."), "img.png", filters);
    if (fileName.isEmpty() || fileName.isNull())
        return;

    ui->widget_5->ui->widget_4->ui->plot->grab().save(fileName);
}



void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    //ui->lineEdit->setText(QString("%1").arg(value / 99.0 * 30));
    ui->lineEdit->setText(QString("%1").arg(value));
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    //ui->lineEdit_2->setText(QString("%1").arg(value / 99.0 * 311.0));
    ui->lineEdit_2->setText(QString("%1").arg(value));
}



void MainWindow::on_radioButton_11_toggled(bool checked)
{
    if (item34->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item34->text() == "Статика")
        {
            if (checked)
            {
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text909').html('Z<tspan style=\"font-size: 15px;\" dy=\"3\">1</tspan>');"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text913').html('Z<tspan style=\"font-size: 15px;\" dy=\"3\">2</tspan>');"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text917').html('Z<tspan style=\"font-size: 15px;\" dy=\"3\">3</tspan>');"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text921').html('Z<tspan style=\"font-size: 15px;\" dy=\"3\">4</tspan>');"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text925').html('Z<tspan style=\"font-size: 15px;\" dy=\"3\">5</tspan>');"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text929').html('Z<tspan style=\"font-size: 15px;\" dy=\"3\">6</tspan>');"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text953').html('Q<tspan style=\"font-size: 15px;\" dy=\"3\">p</tspan>');"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text941').html('H<tspan style=\"font-size: 15px;\" dy=\"3\">p</tspan>');"));

            }
        }
    }
}


void MainWindow::on_radioButton_12_toggled(bool checked)
{
    if (item34->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item34->text() == "Статика")
        {
            if (checked)
            {
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text909').text('%1 кг·с²/м⁸');").arg(Z1,0,'f',3));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text913' ).text('%1 кг·с²/м⁸');").arg(Z2, 0, 'f', 2));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text917').text('%1 кг·с²/м⁸');").arg(Z3, 0, 'f', 2));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text921').text('%1 кг·с²/м⁸');").arg(Z4, 0, 'f', 2));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text925').text('%1 кг·с²/м⁸');").arg(Z5, 0, 'f', 2));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text929').text('%1 кг·с²/м⁸');").arg(Z6, 0, 'f', 2));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text953' ).text('%1 м³/с');").arg(Qp, 0, 'f', 2));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text941').text('%1 Па');").arg(Hp, 0, 'f', 2));                           }
        }
    }
}


void MainWindow::on_radioButton_13_toggled(bool checked)
{
    if (item34->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item34->text() == "Статика")
        {
            if (checked)
            {
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text909').hide();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text913').hide();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text917').hide();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text921').hide();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text925').hide();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text929').hide();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text953').hide();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text941').hide();"));
            }
            else
            {
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text909').show();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text913').show();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text917').show();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text921').show();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text925').show();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text929').show();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text1011').show();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text953').show();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text941').show();"));
            }
        }
    }
}

SettinsKanals::SettinsKanals(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settinsKanals)
{
    ui->setupUi(this);
}

void MainWindow::actionteplident_start()
{
    isNablLaunched = true;

    QPixmap pixmap(":/system_icons/data/img/system_icons/go-previous.svg");
    QIcon ButtonIcon_1(pixmap);
    ui->switch_regim_upr->setIcon(ButtonIcon_1);

    ui->tableWidget_16->setItem(0, 0, new QTableWidgetItem("Суммарные потери"));
    ui->tableWidget_16->setItem(1, 0, new QTableWidgetItem("Теплоемкость"));
    ui->tableWidget_16->setItem(2, 0, new QTableWidgetItem("Коэффициент теплоотдачи"));

    ui->tableWidget_16->setItem(0, 1, new QTableWidgetItem("dPsumm"));
    ui->tableWidget_16->setItem(1, 1, new QTableWidgetItem("C_1"));
    ui->tableWidget_16->setItem(2, 1, new QTableWidgetItem("А"));

    ui->tableWidget_16->setItem(0, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_16->setItem(1, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_16->setItem(2, 3, new QTableWidgetItem("Вт"));


    if (item141->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
        ui->actionteplident_start->setIcon(QIcon(":/system_icons/data/img/system_icons/media-playback-start_3.svg"));
        ui->actionteplident_stop->setEnabled(false);

    }
    else
    {
        if (item141->text() == "Одномассовая модель")
        {
            ui->tabWidget->show();
            ui->tabWidget->setCurrentIndex(2);
            ui->stackedWidget->hide();
            ui->actionteplident_start->setIcon(QIcon(":/system_icons/data/img/system_icons/media-playback-paused.svg"));
            ui->actionteplident_stop->setEnabled(true);
            base.R1 = ui->lineEdit_12->text().toDouble();
            base.R2 = ui->lineEdit_11->text().toDouble();
            base.L1 = ui->lineEdit_10->text().toDouble();
            base.L2 = ui->lineEdit_9->text().toDouble();
            base.Lm = ui->lineEdit_8->text().toDouble();
            teta0_0=item28->text().toDouble();

            ui->widget_10->ui->plot->clear();
            ui->widget_10->ui->plot->addDataLine(QColor(Qt::red), 0);
            ui->widget_10->ui->plot->addDataLine(QColor(Qt::green), 0);

            tepl_ident_P1.clear();
            tepl_ident_P2.clear();
            tepl_ident_t.clear();
            tepl_ident_StatorTemp.clear();
            tepl_start = false;

            statusbar_label_9->setVisible(true);
            statusbar_progres->setVisible(true);
            statusbar_progres->setMinimum(0);
            statusbar_progres->setMaximum(100);
            //statusbar_progres->setRange(0, 1000);
            statusbar_progres->reset();
            ui->widget_3->raschet_el();

        }
    }

    // double teta_1=0, teta_2=0, T_1=0, T_2=0, C_1=0, C_2=0, lambda10=0, lambda12=0,
    //         lambda20=0, dPel1=0, dPel2=0, omega=0, M=0, dPct=0, dPsumm=1100;
    // ui->tableWidget_16->item(0,2)->setText(QString::number(teta_1,'f',3));
    // ui->tableWidget_16->item(1,2)->setText(QString::number(teta_2,'f',3));
    // ui->tableWidget_16->item(2,2)->setText(QString::number(T_1,'f',3));
    // ui->tableWidget_16->item(3,2)->setText(QString::number(T_2,'f',3));
    // ui->tableWidget_16->item(4,2)->setText(QString::number(C_1,'f',3));
    // ui->tableWidget_16->item(5,2)->setText(QString::number(C_2,'f',3));
    // ui->tableWidget_16->item(6,2)->setText(QString::number(lambda10,'f',3));
    // ui->tableWidget_16->item(7,2)->setText(QString::number(lambda12,'f',3));
    // ui->tableWidget_16->item(8,2)->setText(QString::number(lambda20,'f',3));
    // ui->tableWidget_16->item(9,2)->setText(QString::number(dPel1,'f',3));
    // ui->tableWidget_16->item(10,2)->setText(QString::number(dPel2,'f',3));
    // ui->tableWidget_16->item(11,2)->setText(QString::number(dPct,'f',3));
    // ui->tableWidget_16->item(12,2)->setText(QString::number(omega,'f',3));
    // ui->tableWidget_16->item(13,2)->setText(QString::number(M,'f',3));
}

void MainWindow::actionteplident_stop()
{
    isNablLaunched = false;
    ui->actionteplident_start->setIcon(QIcon(":/system_icons/data/img/system_icons/media-playback-start_3.svg"));
    ui->actionteplident_stop->setEnabled(false);

    ui->widget_3->stop();
    ui->stackedWidget->show();

}

void MainWindow::open_file()
{
    QString filter = "Файл конфигурации проекта (*.imview);;Все файлы (*.*)";
    QString str = QFileDialog::getOpenFileName(this, "Выбрать имя, под которым сохранить данные", "../Output", filter);
    LoadProject(str);
}

void MainWindow::save_file()
{
    sessionFileName = QFileInfo(item4->text()).fileName();

    if (sessionFileName.isEmpty())
    {
        return;
    }

    QFile file(QString("../save/project.xml"));
    file.open(QIODevice::WriteOnly);

    //Создаем объект, с помощью которого осуществляется запись в файл
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
    xmlWriter.writeStartDocument();     // Запускаем запись в документ
    xmlWriter.writeStartElement("resources");   // Записываем первый элемент с его именем
    xmlWriter.writeStartElement("project");  // Записываем тег с именем для первого итема

    xmlWriter.writeStartElement("general_settings");

    xmlWriter.writeStartElement("general_settings");

    xmlWriter.writeStartElement("project_name");
    xmlWriter.writeAttribute("value", (item4->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_1");
    xmlWriter.writeAttribute("value", (item88->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("project_path");
    xmlWriter.writeAttribute("value", (item106->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_2");
    xmlWriter.writeAttribute("value", (item80->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("project_path_2");
    xmlWriter.writeAttribute("value", (item82->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_3");
    xmlWriter.writeAttribute("value", (item68->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_4");
    xmlWriter.writeAttribute("value", (item70->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_5");
    xmlWriter.writeAttribute("value", (item72->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_6");
    xmlWriter.writeAttribute("value", (item74->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_7");
    xmlWriter.writeAttribute("value", (item76->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_8");
    xmlWriter.writeAttribute("value", (item78->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_9");
    xmlWriter.writeAttribute("value", (item14->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_1");
    xmlWriter.writeAttribute("value", (item94->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_2");
    xmlWriter.writeAttribute("value", (item96->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_3");
    xmlWriter.writeAttribute("value", (item98->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_4");
    xmlWriter.writeAttribute("value", (item100->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_5");
    xmlWriter.writeAttribute("value", (item102->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_6");
    xmlWriter.writeAttribute("value", (item104->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_10");
    xmlWriter.writeAttribute("value", (item20->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("time_cikle");
    xmlWriter.writeAttribute("value", (item22->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("time_work");
    xmlWriter.writeAttribute("value", (item176->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_11");
    xmlWriter.writeAttribute("value", (item24->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_12");
    xmlWriter.writeAttribute("value", (item92->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("napragenie");
    xmlWriter.writeAttribute("value", (item130->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("moment");
    xmlWriter.writeAttribute("value", (item132->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("start_temp");
    xmlWriter.writeAttribute("value", (item28->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_13");
    xmlWriter.writeAttribute("value", (item30->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_14");
    xmlWriter.writeAttribute("value", (item141->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_15");
    xmlWriter.writeAttribute("value", (item142->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("time_step");
    xmlWriter.writeAttribute("value", (item107->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_16");
    xmlWriter.writeAttribute("value", (item34->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_17");
    xmlWriter.writeAttribute("value", (item36->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("pressure");
    xmlWriter.writeAttribute("value", (item38->text()));
    xmlWriter.writeEndElement();    

    xmlWriter.writeStartElement("selected_row");
    xmlWriter.writeAttribute("value", QString::number(rowNumber));
    xmlWriter.writeEndElement();

    if(item68->text() == "Сохранить")
    {
        xmlWriter.writeStartElement("sopr_R1");
        xmlWriter.writeAttribute("value", (ui->lineEdit_12->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("sopr_R2");
        xmlWriter.writeAttribute("value", (ui->lineEdit_11->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("ind_L1");
        xmlWriter.writeAttribute("value", (ui->lineEdit_10->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("ind_L2");
        xmlWriter.writeAttribute("value", (ui->lineEdit_9->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("ind_Lm");
        xmlWriter.writeAttribute("value", (ui->lineEdit_8->text()));
        xmlWriter.writeEndElement();
    }
    if(item14->text() == "Автоматический")
    {
        xmlWriter.writeStartElement("koeff_gd");
        xmlWriter.writeAttribute("value", (ui->lineEdit_13->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("koeff_ki");
        xmlWriter.writeAttribute("value", (ui->lineEdit_16->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("koeff_gb");
        xmlWriter.writeAttribute("value", (ui->lineEdit_14->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("koeff_kpsi");
        xmlWriter.writeAttribute("value", (ui->lineEdit_17->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("koeff_gp");
        xmlWriter.writeAttribute("value", (ui->lineEdit_15->text()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("koeff_gpsi");
        xmlWriter.writeAttribute("value", (ui->lineEdit_18->text()));
        xmlWriter.writeEndElement();
    }
    if(item24->text() == "Фиксированное время")
    {
        xmlWriter.writeStartElement("time_work");
        xmlWriter.writeAttribute("value", (item174->text()));
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();   // Закрываем файл

    if(item68->text() == "Сохранить")
    {
        QFile file2(QString("/home/elf/Видео/ImView2/save/identification.xml"));
        file2.open(QIODevice::WriteOnly);

        //Создаем объект, с помощью которого осуществляется запись в файл
        QXmlStreamWriter xmlWriter2(&file2);
        xmlWriter2.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
        xmlWriter2.writeStartDocument();     // Запускаем запись в документ
        xmlWriter2.writeStartElement("resources");   // Записываем первый элемент с его именем
        xmlWriter2.writeStartElement("identification");  // Записываем тег с именем для первого итема

        xmlWriter2.writeStartElement("stator_resistance");
        xmlWriter2.writeAttribute("value", (ui->lineEdit_12->text()));
        xmlWriter2.writeEndElement();

        xmlWriter2.writeStartElement("rotor_resistance");
        xmlWriter2.writeAttribute("value", (ui->lineEdit_11->text()));
        xmlWriter2.writeEndElement();

        xmlWriter2.writeStartElement("stator_inductance");
        xmlWriter2.writeAttribute("value", (ui->lineEdit_10->text()));
        xmlWriter2.writeEndElement();

        xmlWriter2.writeStartElement("rotor_inductance");
        xmlWriter2.writeAttribute("value", (ui->lineEdit_9->text()));
        xmlWriter2.writeEndElement();

        xmlWriter2.writeStartElement("mutual_inductance");
        xmlWriter2.writeAttribute("value", (ui->lineEdit_8->text()));
        xmlWriter2.writeEndElement();

        xmlWriter2.writeEndElement();
        xmlWriter2.writeEndElement();
        xmlWriter2.writeEndElement();
        xmlWriter2.writeEndDocument();
        file2.close();   // Закрываем файл
    }

    ui->widget_2->ui->plot->save();

    JlCompress::compressDir(QString("../Output/") + sessionFileName + ".imview", "../save/");
    ui->save_file->setEnabled(false);
}

void MainWindow::save_as_file()
{
    SaveProgectToFile();
}

void MainWindow::print_preview_file()
{
    QPrinter *printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageSize(QPageSize(QPageSize::A4));
    printer->setPageOrientation(QPageLayout::Landscape);
    printer->setFullPage(true);

    QPrintPreviewDialog *printPreview = new QPrintPreviewDialog(printer);
    connect(printPreview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(printPreview(QPrinter*)));
    printPreview->setWindowTitle("Preview Dialog");
    Qt::WindowFlags flags(Qt::WindowTitleHint);
    printPreview->setWindowFlags(flags);
    printPreview->showMaximized();
    printPreview->exec();
}

void MainWindow::printPreview(QPrinter *printer)
{
    printTable(printer, true);
}

void MainWindow::printTable(QPrinter *printer, bool isPreview)
{
    printer->setPageSize(QPageSize(QPageSize::A4));
    printer->setPageOrientation(QPageLayout::Landscape);
    printer->setFullPage(true);

    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->treeView->model()->rowCount();
    const int columnCount = ui->treeView->model()->columnCount();

    out <<  "<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
            <<  QString("<title>%1</title>\n").arg(dirName)
            <<  "</head>\n"
            "<body bgcolor=#ffffff link=#5000A0>\n"
            "<table border=1 cellspacing=0 cellpadding=2>\n";

        // headers
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->treeView->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->treeView->model()->headerData(column, Qt::Horizontal).toString());

    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++)
    {
        out << "<tr>";
            for (int column = 0; column < columnCount; column++)
            {
                if (!ui->treeView->isColumnHidden(column))
                {
                    QString data = ui->treeView->model()->data(ui->treeView->model()->index(row, column)).toString().simplified();
                    out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                }
            }
            out << "</tr>\n";
        }
    out <<  "</table>\n"
            "</body>\n"
            "</html>\n";

    QTextDocument document;
    document.setHtml(strStream);

    if (isPreview)
    {
        document.print(printer);
    }
    else
    {
        QPrintDialog dialog(printer, NULL);
        if (dialog.exec() == QDialog::Accepted) {
            document.print(printer);
        }
    }
}

void MainWindow::pagePrint()
{
    QPrinter printer;
    printTable(&printer, false);
}

void MainWindow::button_visible()
{
    ui->save_file->setEnabled(true);
}

void MainWindow::button_visible_2()
{
    ui->save_as_file->setEnabled(true);
}

void MainWindow::createUndoView()
{
    undoView = new QUndoView(undoStack);
    undoView->setWindowTitle(tr("Command List"));
    undoView->show();
    undoView->setAttribute(Qt::WA_QuitOnClose, false);
}

void MainWindow::edit()
{
    cleanState = false;
    if (undoOperation)
        return;
    QUndoCommand *cutCommand = new QUndoCommand();
    cutCommand->setText("lineEdit_13");
    undoStack->push(cutCommand);

    ui->actionundo->setEnabled(true);
    ui->actionredo->setEnabled(true);
}

void MainWindow::edit_2()
{
    cleanState = false;
    if (undoOperation)
        return;
    QUndoCommand *cutCommand = new QUndoCommand();
    cutCommand->setText("lineEdit_16");
    undoStack->push(cutCommand);

    ui->actionundo->setEnabled(true);
    ui->actionredo->setEnabled(true);
}
void MainWindow::edit_3()
{
    cleanState = false;
    if (undoOperation)
        return;
    QUndoCommand *cutCommand = new QUndoCommand();
    cutCommand->setText("lineEdit_14");
    undoStack->push(cutCommand);

    ui->actionundo->setEnabled(true);
    ui->actionredo->setEnabled(true);
}
void MainWindow::edit_4()
{
    cleanState = false;
    if (undoOperation)
        return;
    QUndoCommand *cutCommand = new QUndoCommand();
    cutCommand->setText("lineEdit_17");
    undoStack->push(cutCommand);

    ui->actionundo->setEnabled(true);
    ui->actionredo->setEnabled(true);
}

void MainWindow::edit_5()
{
    cleanState = false;
    if (undoOperation)
        return;
    QUndoCommand *cutCommand = new QUndoCommand();
    cutCommand->setText("lineEdit_15");
    undoStack->push(cutCommand);

    ui->actionundo->setEnabled(true);
    ui->actionredo->setEnabled(true);
}

void MainWindow::edit_6()
{
    cleanState = false;
    if (undoOperation)
        return;
    QUndoCommand *cutCommand = new QUndoCommand();
    cutCommand->setText("lineEdit_18");
    undoStack->push(cutCommand);

    ui->actionundo->setEnabled(true);
    ui->actionredo->setEnabled(true);
}

void MainWindow::actioncopy()
{
    if(ui->lineEdit_13->text().isEmpty())
    {
        return;
    }
    else
    {
        if(ui->lineEdit_13->hasFocus())
        {
            QUndoCommand *copyCommand = new QUndoCommand();
            QClipboard *clipboard = QApplication::clipboard();
            QString s1 = ui->lineEdit_13->text();
            clipboard->setText(s1);
            copyCommand->setText("lineEdit");
            ui->lineEdit_13->paste();
            undoStack->push(copyCommand);
        }
    }
    if(ui->lineEdit_16->text().isEmpty())
    {
    return;
    }
    else
    {
        if(ui->lineEdit_16->hasFocus())
        {
            QUndoCommand *copyCommand = new QUndoCommand();
            QClipboard *clipboard = QApplication::clipboard();
            QString s1 = ui->lineEdit_16->text();
            clipboard->setText(s1);
            copyCommand->setText("lineEdit_16");
            ui->lineEdit_16->paste();
            undoStack->push(copyCommand);
        }
    }
    if(ui->lineEdit_14->text().isEmpty())
    {
    return;
    }
    else
    {
        if(ui->lineEdit_14->hasFocus())
        {
            QUndoCommand *copyCommand = new QUndoCommand();
            QClipboard *clipboard = QApplication::clipboard();
            QString s1 = ui->lineEdit_14->text();
            clipboard->setText(s1);
            copyCommand->setText("lineEdit_14");
            ui->lineEdit_14->paste();
            undoStack->push(copyCommand);
        }
    }
    if(ui->lineEdit_17->text().isEmpty())
    {
    return;
    }
    else
    {
        if(ui->lineEdit_17->hasFocus())
        {
            QUndoCommand *copyCommand = new QUndoCommand();
            QClipboard *clipboard = QApplication::clipboard();
            QString s1 = ui->lineEdit_17->text();
            clipboard->setText(s1);
            copyCommand->setText("lineEdit_17");
            ui->lineEdit_17->paste();
            undoStack->push(copyCommand);
        }
    }
    if(ui->lineEdit_15->text().isEmpty())
    {
    return;
    }
    else
    {
        if(ui->lineEdit_15->hasFocus())
        {
            QUndoCommand *copyCommand = new QUndoCommand();
            QClipboard *clipboard = QApplication::clipboard();
            QString s1 = ui->lineEdit_15->text();
            clipboard->setText(s1);
            copyCommand->setText("lineEdit_15");
            ui->lineEdit_15->paste();
            undoStack->push(copyCommand);
        }
    }
    if(ui->lineEdit_18->text().isEmpty())
    {
    return;
    }
    else
    {
        if(ui->lineEdit_18->hasFocus())
        {
            QUndoCommand *copyCommand = new QUndoCommand();
            QClipboard *clipboard = QApplication::clipboard();
            QString s1 = ui->lineEdit_18->text();
            clipboard->setText(s1);
            copyCommand->setText("lineEdit_18");
            ui->lineEdit_18->paste();
            undoStack->push(copyCommand);
        }
    }
    if(item4->text().isEmpty())
    {
    return;
    }
    else
    {
        if(item4->isSelectable())
        {
            QUndoCommand *copyCommand = new QUndoCommand();
            QClipboard *clipboard = QApplication::clipboard();
            QString s1 = item4->text();
            clipboard->setText(s1);
            copyCommand->setText("lineEdit_18");
            //item4->paste();
            undoStack->push(copyCommand);
        }
    }
}


void MainWindow::actionpaste()
{
    if(ui->lineEdit_13->hasFocus())
    {
        QUndoCommand *addCommand = new QUndoCommand();
        addCommand->setText("lineEdit_13");
        ui->lineEdit_13->paste();
        undoStack->push(addCommand);
    }
    if(ui->lineEdit_13->text().isEmpty())
    {
    return;
    }
    else
    {
        if(ui->lineEdit_16->hasFocus())
        {
            QUndoCommand *addCommand = new QUndoCommand();
            addCommand->setText("lineEdit_16");
            ui->lineEdit_16->paste();
            undoStack->push(addCommand);
        }
    }
    if(ui->lineEdit_16->text().isEmpty())
    {
    return;
    }
    else
    {
        if(ui->lineEdit_14->hasFocus())
        {
            QUndoCommand *addCommand = new QUndoCommand();
            addCommand->setText("lineEdit_14");
            ui->lineEdit_14->paste();
            undoStack->push(addCommand);
        }
    }
    if(ui->lineEdit_14->text().isEmpty())
    {
    return;
    }
    else
    {
        if(ui->lineEdit_17->hasFocus())
        {
            QUndoCommand *addCommand = new QUndoCommand();
            addCommand->setText("lineEdit_17");
            ui->lineEdit_17->paste();
            undoStack->push(addCommand);
        }
    }
    if(ui->lineEdit_17->text().isEmpty())
    {
    return;
    }
    else
    {
        if(ui->lineEdit_15->hasFocus())
        {
            QUndoCommand *addCommand = new QUndoCommand();
            addCommand->setText("lineEdit_15");
            ui->lineEdit_15->paste();
            undoStack->push(addCommand);
        }
    }
    if(ui->lineEdit_15->text().isEmpty())
    {
    return;
    }
    else
    {
        if(ui->lineEdit_18->hasFocus())
        {
            QUndoCommand *addCommand = new QUndoCommand();
            addCommand->setText("lineEdit_18");
            ui->lineEdit_18->paste();
            undoStack->push(addCommand);
        }
    }
    if(ui->lineEdit_18->text().isEmpty())
    {
    return;
    }
    else
    {
        if(item4->isSelectable())
        {
            QUndoCommand *addCommand = new QUndoCommand();
            addCommand->setText("item4");
            //item4->paste();
            undoStack->push(addCommand);
        }
    }
    if(item4->text().isEmpty())
    {
    return;
    }
}

void MainWindow::actionundo()
{
    QString undoText = undoStack->undoText();
    ui->actionredo->setEnabled(true);

    if(undoText == "lineEdit_13")
    {
        undoOperation = true;
        ui->lineEdit_13->undo();
        undoOperation = false;
    }
    if(undoText == "lineEdit_16")
    {
        undoOperation = true;
        ui->lineEdit_16->undo();
        undoOperation = false;
    }
    if(undoText == "lineEdit_14")
    {
        undoOperation = true;
        ui->lineEdit_14->undo();
        undoOperation = false;
    }
    if(undoText == "lineEdit_14")
    {
        undoOperation = true;
        ui->lineEdit_14->undo();
        undoOperation = false;
    }
    if(undoText == "lineEdit_15")
    {
        undoOperation = true;
        ui->lineEdit_15->undo();
        undoOperation = false;
    }
    if(undoText == "lineEdit_18")
    {
        undoOperation = true;
        ui->lineEdit_18->undo();
        undoOperation = false;
    }
    if(undoText == "item4")
    {
        undoOperation = true;
        //item4->undo();
        undoOperation = false;
    }

    undoStack->undo();
    if (undoStack->index() == 0)
    {
        ui->actionundo->setEnabled(false);
    }
}

void MainWindow::actionredo()
{
    QString redoText = undoStack->redoText();
    ui->actionundo->setEnabled(true);

    if(redoText == "lineEdit_13")
    {
        undoOperation = true;
        ui->lineEdit_13->redo();
        undoOperation = false;
    }
    if(redoText == "lineEdit_16")
    {
        undoOperation = true;
        ui->lineEdit_16->redo();
        undoOperation = false;
    }
    if(redoText == "lineEdit_14")
    {
        undoOperation = true;
        ui->lineEdit_14->redo();
        undoOperation = false;
    }
    if(redoText == "lineEdit_17")
    {
        undoOperation = true;
        ui->lineEdit_17->redo();
        undoOperation = false;
    }
    if(redoText == "lineEdit_15")
    {
        undoOperation = true;
        ui->lineEdit_15->redo();
        undoOperation = false;
    }
    if(redoText == "lineEdit_18")
    {
        undoOperation = true;
        ui->lineEdit_18->redo();
        undoOperation = false;
    }
   /* if(redoText == "tablewidget")
    {
        undoOperation = true;
        ui->tableWidget->redo();
        undoOperation = false;
    }*/
    undoStack->redo();
    if (undoStack->index() == undoStack->count())
    {
        ui->actionredo->setEnabled(false);
    }
}

void MainWindow::actioncut()
{
    if(ui->lineEdit_13->text().isEmpty())
    {
        return;
    }
    else
    {
        if(ui->lineEdit_13->hasFocus())
        {
            QUndoCommand *cutCommand = new QUndoCommand();
            cutCommand->setText("lineEdit_13");
            ui->lineEdit_13->cut();
            undoStack->push(cutCommand);
        }
    }
    if(ui->lineEdit_16->text().isEmpty())
    {
        return;
    }
    else
    {
        if(ui->lineEdit_16->hasFocus())
        {
            QUndoCommand *cutCommand = new QUndoCommand();
            cutCommand->setText("lineEdit_16");
            ui->lineEdit_16->cut();
            undoStack->push(cutCommand);
        }
    }
    if(ui->lineEdit_14->text().isEmpty())
    {
        return;
    }
    else
    {
        if(ui->lineEdit_14->hasFocus())
        {
            QUndoCommand *cutCommand = new QUndoCommand();
            cutCommand->setText("lineEdit_14");
            ui->lineEdit_14->cut();
            undoStack->push(cutCommand);
        }
    }
    if(ui->lineEdit_17->text().isEmpty())
    {
        return;
    }
    else
    {
        if(ui->lineEdit_17->hasFocus())
        {
            QUndoCommand *cutCommand = new QUndoCommand();
            cutCommand->setText("lineEdit_17");
            ui->lineEdit_17->cut();
            undoStack->push(cutCommand);
        }
    }
    if(ui->lineEdit_15->text().isEmpty())
    {
        return;
    }
    else
    {
        if(ui->lineEdit_15->hasFocus())
        {
            QUndoCommand *cutCommand = new QUndoCommand();
            cutCommand->setText("lineEdit_15");
            ui->lineEdit_15->cut();
            undoStack->push(cutCommand);
        }
    }
    if(ui->lineEdit_18->text().isEmpty())
    {
        return;
    }
    else
    {
        if(ui->lineEdit_18->hasFocus())
        {
            QUndoCommand *cutCommand = new QUndoCommand();
            cutCommand->setText("lineEdit_18");
            ui->lineEdit_18->cut();
            undoStack->push(cutCommand);
        }
    }
    /*if(ui->tableWidget->hasFocus())
    {
        ui->tableWidget->cut();
    }*/
}

void MainWindow::edit_treeview()
{
    cleanState = false;
    if (undoOperation)
        return;
    QUndoCommand *cutCommand = new QUndoCommand();
    cutCommand->setText("treeview");
    undoStack->push(cutCommand);

    ui->actionundo->setEnabled(true);
    ui->actionredo->setEnabled(true);
}

void MainWindow::openRecentFile()
{
    ui->tabWidget->show();
    ui->stackedWidget->show();
    ui->switch_regim_upr->show();
    QAction *action = qobject_cast<QAction *>(sender());
    if (action)
    {
        QString fileName = action->data().toString();
        loadFile(fileName);
        int index = ui->tabWidget->currentIndex();
        QString currentTabText = ui->tabWidget->tabText(index);
        QFileInfo fi(fileName);
        QString base = fi.baseName();
        setWindowTitle(currentTabText + "@" + QString(base) + QString(" - IM View"));
    }
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowFilePath(curFile);

    QSettings settings("BRU", "IM View");
    QStringList files = settings.value("recentFileList").toStringList();
    files.removeAll(fileName);
    files.prepend(fileName);

    while (files.size() > MaxRecentFiles)
    {
        files.removeLast();
    }

    settings.setValue("recentFileList", files);

    foreach (QWidget *widget, QApplication::topLevelWidgets())
    {
        MainWindow *mainWin = qobject_cast<MainWindow *>(widget);
        if (mainWin)
            mainWin->updateRecentFileActions();
    }
}

void MainWindow::updateRecentFileActions()
{
    QSettings settings("BRU", "IM View");
    QStringList files = settings.value("recentFileList").toStringList();

    for (int i = 0; i < files.size(); i++)
    {
        QFileInfo fi(files[i]);
        if (!fi.exists())
        {
            files.removeAt(i);
            i--;
        }
    }

    settings.setValue("recentFileList", files);

    int numRecentFiles = qMin(files.size(), (int)MaxRecentFiles);

    for (int i = 0; i < numRecentFiles; ++i) {
        QString text = tr("&%1 %2").arg(i + 1).arg(strippedName(files[i]));
        recentFileActs[i]->setText(text);
        recentFileActs[i]->setData(files[i]);
        recentFileActs[i]->setVisible(true);
    }
    for (int j = numRecentFiles; j < MaxRecentFiles; ++j)
        recentFileActs[j]->setVisible(false);

    recentFileActs[MaxRecentFiles-1]->setVisible(numRecentFiles > 0);
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::loadFile(const QString &fileName)
{
    // setWindowTitle(fileName + QString(" - IM View"));
    // dat->table();
     //on_LoadProgect_clicked();
     LoadProject(fileName);
     setCurrentFile(fileName);

     QFileInfo fi(fileName);
     QString base = fi.baseName();
     ui->label_9->setText(base);
     int index = ui->tabWidget->currentIndex();
     QString currentTabText = ui->tabWidget->tabText(index);
     setWindowTitle(currentTabText + "@" + QString(base) + QString(" - IM View"));
}

void::MainWindow::close_progect()
{
    item4->setText(tr("Имя сеанса"));
    item88->setText(tr("Выбрать тип эксперимента"));
    item106->setText(tr("Указать каталог"));
    item80->setText(tr("Выбрать тип эксперимента"));
    item82->setText(tr("Указать каталог"));
    item117->setText(tr("Выбрать каналы"));
    item14->setText(tr("Выберите режим"));
    item20->setText(tr("Выбрать режим"));
    item22->setText(tr("0"));
    item24->setText(tr("0"));
    item28->setText(tr("0"));
    item130->setText(tr("0"));
    item132->setText(tr("0"));
    item92->setText(tr("Выбрать режим"));
    item28->setText(tr("0"));
    item30->setText(tr("Выберите режим"));
    item107->setText(tr("0"));
    item34->setText(tr("Выберите режим"));
    item36->setText(tr("Выберите конструкцию"));
    item38->setText(tr("0"));
    item68->setText(tr("Выбрать режим"));
    item70->setText(tr("Выбрать режим"));
    item72->setText(tr("Выбрать режим"));
    item74->setText(tr("Выбрать режим"));
    item76->setText(tr("Выбрать режим"));
    item78->setText(tr("Выбрать режим"));

    ui->lineEdit_12->clear();
    ui->lineEdit_11->clear();
    ui->lineEdit_10->clear();
    ui->lineEdit_9->clear();
    ui->lineEdit_8->clear();

    ui->lineEdit_13->clear();
    ui->lineEdit_16->clear();
    ui->lineEdit_14->clear();
    ui->lineEdit_17->clear();
    ui->lineEdit_8->clear();
    ui->lineEdit_15->clear();
    ui->lineEdit_18->clear();

    //ui->widget_2->ui->plot->save();
    ui->widget_2->ui->plot->clear();
    ui->tabWidget->hide();
    ui->stackedWidget->hide();
    ui->switch_regim_upr->hide();
    ui->toolBar->hide();
    ui->toolBar_2->hide();
    ui->menu_2->menuAction()->setVisible(false);
    ui->menu_3->menuAction()->setVisible(false);
    ui->menu_4->menuAction()->setVisible(false);
    ui->menu_5->menuAction()->setVisible(false);
    ui->widget_15->show();
    ui->widget->ui->tableView->clearSelection();

}

void MainWindow::open_panel()
{
    ui->widget_12->setVisible(true);
    ui->widget_12->ui->lineEdit->clear();

}

void MainWindow::poisk()
{
    select_all();
    int i,x, j, xz,iz, jz, number;
    QString str,moc_2;
    str = ui->widget_12->ui->lineEdit->text();

    QSettings settings( "BRU", "IM View");
    xz = settings.value( "xz", "").toInt();
    iz = settings.value( "iz", "").toInt();
    jz = settings.value( "jz", "").toInt();
    number=settings.value( "number", "").toInt();

    if (number < 1)
    {
        ui->tabWidget->setCurrentIndex(0);
        ui->widget->ui->tableView->setFocus();

        if(ui->widget->ui->tableView->isEnabled()==true)
        {
            //int i,x,xx, ii, number;
            str = ui->widget_12->ui->lineEdit->text();

            QSettings settings( "BRU", "IM View");
            xz = settings.value( "xz", "").toInt();
            iz = settings.value( "iz", "").toInt();
            number = settings.value( "number", "").toInt();
            int currentRow = ui->widget->modd->rowCount();
            int currentCol = ui->widget->modd->columnCount();

            for(x=xz;x<currentRow;x++)
            {
                for(i=iz;i<currentCol;i++)
                {
                    QString moc_2 = ui->widget->modd->item(x,i)->text();

                    int pos = moc_2.indexOf(str, 0,Qt::CaseInsensitive);
                    if (pos != -1)
                    {
                        ui->widget->modd->item(x,i)->setBackground(Qt::green);
                        QSettings settings( "BRU", "IM View");
                        settings.setValue( "iz", i+1);
                        settings.setValue( "xz", x);
                        if(x == currentRow-1)
                        {
                            settings.setValue( "iz", i+1);
                        }
                        return;
                    }
                }
                iz = 0;
            }
            settings.setValue( "number", 1);
            QMessageBox::information(this, tr("IM View"), tr("Анализ таблицы закончен"));
            ui->tabWidget->setCurrentIndex(0);
            ui->treeView->setFocus();
        }
    }

    if ((number == 1) && (number < 2))
    {
        ui->tabWidget->setCurrentIndex(0);
        ui->treeView->setFocus();

        if(ui->treeView->isEnabled()==true)
        {
            //int i,x,xx, ii, number;
            str = ui->widget_12->ui->lineEdit->text();

            QSettings settings( "BRU", "IM View");
            xz = settings.value( "xz", "").toInt();
            iz = settings.value( "iz", "").toInt();
            number = settings.value( "number", "").toInt();
            iterate(model2->index(15,0), model2, str);

            settings.setValue( "number", 2);
            QMessageBox::information(this, tr("IM View"), tr("Анализ таблицы закончен"));
            ui->tabWidget->setCurrentIndex(2);
            ui->tableWidget_16->setFocus();
        }
    }


if ((number == 2) && (number < 3))    {


        if(ui->tableWidget_16->isEnabled() == true)
        {
            for(x = xz; x <ui->tableWidget_16->rowCount(); x++)
            {
                for(i = iz; i <ui->tableWidget_16->columnCount(); i++)
                {
                    moc_2 = ui->tableWidget_16->item(x,i)->text();

                    j = jz;
                    while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
                    {
                        ui->tableWidget_16->item(x,i)->setBackground(Qt::green);

                        QSettings settings( "BRU", "IM View");
                        settings.setValue( "iz", i+1);
                        settings.setValue( "jz", j+1);
                        settings.setValue( "xz", x);

                        if(x == ui->tableWidget_16->rowCount()-1)
                        {
                            settings.setValue( "iz", i+1);
                        }
                        return;
                    }
                    jz = 0;
                }
                iz = 0;
            }

            QSettings settings( "BRU", "IM View");
            settings.setValue( "iz", 0);
            settings.setValue( "xz", 0);
            settings.setValue( "jz", 0);
            settings.setValue( "number", 3);
            QMessageBox::information(this, tr("IM View"), tr("Анализ таблицы закончен"));
            ui->tabWidget->setCurrentIndex(3);
            ui->tabWidget_2->setCurrentIndex(0);
            ui->tableWidget_2->setFocus();
        }
    }

    if ((number == 3) && (number < 4))
    {

        QSettings settings( "BRU", "IM View");
        xz = settings.value( "xz", "").toInt();
        iz = settings.value( "iz", "").toInt();
        jz = settings.value( "jz", "").toInt();

        if(ui->tableWidget_2->isEnabled() == true)
        {
            for(x = xz; x < ui->tableWidget_2->rowCount(); x++)
            {
                for(i = iz; i < ui->tableWidget_2->columnCount(); i++)
                {
                    moc_2 = ui->tableWidget_2->item(x,i)->text();

                    j = jz;
                    while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
                    {
                        ui->tableWidget_2->item(x,i)->setBackground(Qt::green);

                        QSettings settings( "BRU", "IM View");
                        settings.setValue( "iz", i+1);
                        settings.setValue( "jz", j+1);
                        settings.setValue( "xz", x);

                        if(x == ui->tableWidget_2->rowCount()-1)
                        {
                            settings.setValue( "iz", i+1);
                        }
                        return;
                    }
                    jz = 0;
                }
                iz = 0;
            }

            QSettings settings( "BRU", "IM View");
            settings.setValue( "iz", 0);
            settings.setValue( "xz", 0);
            settings.setValue( "jz", 0);
            settings.setValue( "number", 4);
            QMessageBox::information(this, tr("IM View"), tr("Анализ таблицы закончен"));
            ui->tabWidget->setCurrentIndex(3);
            ui->tabWidget_2->setCurrentIndex(1);
            ui->tableWidget_4->setFocus();
        }
    }

    if ((number == 3) && (number < 4))
    {
        //i=0,x=0,j=0;
        QSettings settings( "BRU", "IM View");
        xz = settings.value( "xz", "").toInt();
        iz = settings.value( "iz", "").toInt();
        jz = settings.value( "jz", "").toInt();

        if(ui->tableWidget_4->isEnabled() == true)
        {
            for(x = xz; x < ui->tableWidget_4->rowCount(); x++)
            {
                for(i = iz; i < ui->tableWidget_4->columnCount(); i++)
                {
                    moc_2 = ui->tableWidget_4->item(x,i)->text();

                    j = jz;
                    while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
                    {
                        ui->tableWidget_4->item(x,i)->setBackground(Qt::green);

                        QSettings settings( "BRU", "IM View");
                        settings.setValue( "iz", i+1);
                        settings.setValue( "jz", j+1);
                        settings.setValue( "xz", x);

                        if(x == ui->tableWidget_4->rowCount()-1)
                        {
                            settings.setValue( "iz", i+1);
                        }
                        return;
                    }
                    jz = 0;
                }
                iz = 0;
            }

            QSettings settings( "BRU", "IM View");
            settings.setValue( "iz", 0);
            settings.setValue( "xz", 0);
            settings.setValue( "jz", 0);
            settings.setValue( "number", 4);
            QMessageBox::information(this, tr("IM View"), tr("Анализ таблицы закончен"));
            ui->tabWidget->setCurrentIndex(4);
            ui->widget_5->ui->tabWidget->setCurrentIndex(0);
            ui->tableWidget_9->setFocus();
        }
    }

    if ((number == 4) && (number < 5))
    {
        //i=0,x=0,j=0;
        QSettings settings( "BRU", "IM View");
        xz = settings.value( "xz", "").toInt();
        iz = settings.value( "iz", "").toInt();
        jz = settings.value( "jz", "").toInt();

        if(ui->widget_5->ui->widget_2->ui->tableWidget->isEnabled() == true)
        {


            for(x = xz; x <ui->widget_5->ui->widget_2->ui->tableWidget->rowCount(); x++)
            {
                for(i = iz; i<ui->widget_5->ui->widget_2->ui->tableWidget->columnCount(); i++)
                {
                    moc_2 = ui->widget_5->ui->widget_2->ui->tableWidget->item(x,i)->text();

                    j = jz;
                    while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
                    {
                        ui->widget_5->ui->widget_2->ui->tableWidget->item(x,i)->setBackground(Qt::green);

                        QSettings settings( "BRU", "IM View");
                        settings.setValue( "iz", i+1);
                        settings.setValue( "jz", j+1);
                        settings.setValue( "xz", x);

                        if(x == ui->widget_5->ui->widget_2->ui->tableWidget->rowCount()-1)
                        {
                            settings.setValue( "iz", i+1);
                        }
                        return;
                    }
                    jz = 0;
                }
                iz = 0;
            }



            QSettings settings( "BRU", "IM View");
            settings.setValue( "iz", 0);
            settings.setValue( "xz", 0);
            settings.setValue( "jz", 0);
            settings.setValue( "number", 5);
            QMessageBox::information(this, tr("IM View"), tr("Анализ таблицы закончен"));
            ui->tabWidget->setCurrentIndex(4);
            ui->widget_5->ui->tabWidget->setCurrentIndex(0);
            ui->tableWidget_9->setFocus();
        }
    }

    if ((number == 5) && (number < 6))
    {
        //i=0,x=0,j=0;
        QSettings settings( "BRU", "IM View");
        xz = settings.value( "xz", "").toInt();
        iz = settings.value( "iz", "").toInt();
        jz = settings.value( "jz", "").toInt();

        if(ui->tableWidget_9->isEnabled()==true)
        {
            for(x=xz; x<ui->tableWidget_9->rowCount(); x++)
            {
                for(i=iz; i<ui->tableWidget_9->columnCount(); i++)
                {
                    moc_2 = ui->tableWidget_9->item(x,i)->text();

                    j = jz;
                    while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
                    {
                        ui->tableWidget_9->item(x,i)->setBackground(Qt::green);

                        QSettings settings( "BRU", "IM View");
                        settings.setValue( "iz", i+1);
                        settings.setValue( "jz", j+1);
                        settings.setValue( "xz", x);

                        if(x==ui->tableWidget_9->rowCount()-1)
                        {
                            settings.setValue( "iz", i+1);
                        }
                        return;
                    }
                    jz=0;
                }
                iz = 0;
            }

            QSettings settings( "BRU", "IM View");
            settings.setValue( "iz", 0);
            settings.setValue( "xz", 0);
            settings.setValue( "jz", 0);
            settings.setValue( "number", 6);
            QMessageBox::information(this, tr("IM View"), tr("Анализ таблицы закончен"));
            ui->tabWidget->setCurrentIndex(4);
            ui->widget_5->ui->tabWidget->setCurrentIndex(1);
            ui->widget_5->ui->tableWidget->setFocus();
        }
    }

    if ((number == 6) && (number < 7))
    {
        //i=0,x=0,j=0;
        QSettings settings( "BRU", "IM View");
        xz = settings.value( "xz", "").toInt();
        iz = settings.value( "iz", "").toInt();
        jz = settings.value( "jz", "").toInt();

        if(ui->widget_5->ui->tableWidget->isEnabled()==true)
        {
            for(x=xz;x<ui->widget_5->ui->tableWidget->rowCount();x++)
            {
                for(i=iz;i<ui->widget_5->ui->tableWidget->columnCount();i++)
                {
                    moc_2 = ui->widget_5->ui->tableWidget->item(x,i)->text();

                    j = jz;
                    while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
                    {
                        ui->widget_5->ui->tableWidget->item(x,i)->setBackground(Qt::green);

                        QSettings settings( "BRU", "IM View");
                        settings.setValue( "iz", i+1);
                        settings.setValue( "jz", j+1);
                        settings.setValue( "xz", x);

                        if(x==ui->widget_5->ui->tableWidget->rowCount()-1)
                        {
                            settings.setValue( "iz", i+1);
                        }
                        return;
                    }
                    jz=0;
                }
                iz = 0;
            }

            QSettings settings( "BRU", "IM View");
            settings.setValue( "iz", 0);
            settings.setValue( "xz", 0);
            settings.setValue( "jz", 0);
            settings.setValue( "number", 7);
            QMessageBox::information(this, tr("IM View"), tr("Анализ таблицы закончен"));
            ui->tabWidget->setCurrentIndex(4);
            ui->widget_5->ui->tabWidget->setCurrentIndex(3);
            ui->tableWidget_3->setFocus();
        }
    }

    if ((number == 7) && (number < 8))
    {
        //i=0,x=0,j=0;
        QSettings settings( "BRU", "IM View");
        xz = settings.value( "xz", "").toInt();
        iz = settings.value( "iz", "").toInt();
        jz = settings.value( "jz", "").toInt();

        if(ui->tableWidget_3->isEnabled()==true)
        {
            for(x=xz;x<ui->tableWidget_3->rowCount();x++)
            {
                for(i=iz;i<ui->tableWidget_3->columnCount();i++)
                {
                    moc_2 = ui->tableWidget_3->item(x,i)->text();

                    j = jz;
                    while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
                    {
                        ui->tableWidget_3->item(x,i)->setBackground(Qt::green);

                        QSettings settings( "BRU", "IM View");
                        settings.setValue( "iz", i+1);
                        settings.setValue( "jz", j+1);
                        settings.setValue( "xz", x);

                        if(x == ui->tableWidget_3->rowCount()-1)
                        {
                            settings.setValue( "iz", i+1);
                        }
                        return;
                    }
                    jz=0;
                }
                iz = 0;
            }

            QSettings settings( "BRU", "IM View");
            settings.setValue( "iz", 0);
            settings.setValue( "xz", 0);
            settings.setValue( "jz", 0);
            settings.setValue( "number", 7);
            QMessageBox::information(this, tr("IM View"), tr("Анализ таблицы закончен"));
            ui->tabWidget->setCurrentIndex(4);
            ui->widget_5->ui->tabWidget->setCurrentIndex(4);
            ui->tableWidget_5->setFocus();
        }
    }

    if ((number == 8) && (number < 9))
    {
        //i=0,x=0,j=0;
        QSettings settings( "BRU", "IM View");
        xz = settings.value( "xz", "").toInt();
        iz = settings.value( "iz", "").toInt();
        jz = settings.value( "jz", "").toInt();

        if(ui->tableWidget_5->isEnabled()==true)
        {
            for(x=xz;x<ui->tableWidget_5->rowCount();x++)
            {
                for(i=iz;i<ui->tableWidget_5->columnCount();i++)
                {
                    moc_2 = ui->tableWidget_5->item(x,i)->text();

                    j = jz;
                    while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
                    {
                        ui->tableWidget_5->item(x,i)->setBackground(Qt::green);

                        QSettings settings( "BRU", "IM View");
                        settings.setValue( "iz", i+1);
                        settings.setValue( "jz", j+1);
                        settings.setValue( "xz", x);

                        if(x == ui->tableWidget_5->rowCount()-1)
                        {
                            settings.setValue( "iz", i+1);
                        }
                        return;
                    }
                    jz=0;
                }
                iz = 0;
            }

            QSettings settings( "BRU", "IM View");
            settings.setValue( "iz", 0);
            settings.setValue( "xz", 0);
            settings.setValue( "jz", 0);
            settings.setValue( "number", 9);
            QMessageBox::information(this, tr("IM View"), tr("Анализ таблицы закончен"));
            ui->tabWidget->setCurrentIndex(4);
            ui->widget_5->ui->tabWidget->setCurrentIndex(5);
            ui->tableWidget_6->setFocus();

        }
    }

    if ((number == 9) && (number < 10))
    {
        //i=0,x=0,j=0;
        QSettings settings( "BRU", "IM View");
        xz = settings.value( "xz", "").toInt();
        iz = settings.value( "iz", "").toInt();
        jz = settings.value( "jz", "").toInt();

        if(ui->tableWidget_6->isEnabled()==true)
        {
            for(x=xz;x<ui->tableWidget_6->rowCount();x++)
            {
                for(i=iz;i<ui->tableWidget_6->columnCount();i++)
                {
                    moc_2 = ui->tableWidget_6->item(x,i)->text();

                    j = jz;
                    while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
                    {
                        ui->tableWidget_6->item(x,i)->setBackground(Qt::green);


                        QSettings settings( "BRU", "IM View");
                        settings.setValue( "iz", i+1);
                        settings.setValue( "jz", j+1);
                        settings.setValue( "xz", x);

                        if(x == ui->tableWidget_6->rowCount()-1)
                        {
                            settings.setValue( "iz", i+1);
                        }
                        return;
                    }
                    jz=0;
                }
                iz = 0;
            }

            QSettings settings( "BRU", "IM View");
            settings.setValue( "iz", 0);
            settings.setValue( "xz", 0);
            settings.setValue( "jz", 0);
            settings.setValue( "number", 10);
            QMessageBox::information(this, tr("IM View"), tr("Анализ таблицы закончен"));
            ui->tabWidget->setCurrentIndex(5);
            ui->widget_6->ui->tabWidget->setCurrentIndex(0);
            ui->widget_6->ui->tabWidget_2->setCurrentIndex(0);
            ui->tableWidget_7->setFocus();
        }
    }

    if ((number == 10) && (number < 11))
    {
        //i=0,x=0,j=0;
        QSettings settings( "BRU", "IM View");
        xz = settings.value( "xz", "").toInt();
        iz = settings.value( "iz", "").toInt();
        jz = settings.value( "jz", "").toInt();

        if(ui->tableWidget_7->isEnabled()==true)
        {
            for(x=xz;x<ui->tableWidget_7->rowCount();x++)
            {
                for(i=iz;i<ui->tableWidget_7->columnCount();i++)
                {
                    moc_2 = ui->tableWidget_7->item(x,i)->text();

                    j = jz;
                    while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
                    {
                        ui->tableWidget_7->item(x,i)->setBackground(Qt::green);

                        QSettings settings( "BRU", "IM View");
                        settings.setValue( "iz", i+1);
                        settings.setValue( "jz", j+1);
                        settings.setValue( "xz", x);

                        if(x == ui->tableWidget_7->rowCount()-1)
                        {
                            settings.setValue( "iz", i+1);
                        }
                        return;
                    }
                    jz=0;
                }
                iz = 0;
            }

            QSettings settings( "BRU", "IM View");
            settings.setValue( "iz", 0);
            settings.setValue( "xz", 0);
            settings.setValue( "jz", 0);
            settings.setValue( "number", 11);
            QMessageBox::information(this, tr("IM View"), tr("Анализ таблицы закончен"));
            ui->tabWidget->setCurrentIndex(5);
            ui->widget_6->ui->tabWidget->setCurrentIndex(1);
            ui->widget_6->ui->tabWidget_2->setCurrentIndex(0);
            ui->tableWidget_13->setFocus();
        }
    }

    if ((number == 11) && (number < 12))
    {
        //i=0,x=0,j=0;
        QSettings settings( "BRU", "IM View");
        xz = settings.value( "xz", "").toInt();
        iz = settings.value( "iz", "").toInt();
        jz = settings.value( "jz", "").toInt();

        if(ui->tableWidget_13->isEnabled()==true)
        {
            for(x=xz;x<ui->tableWidget_13->rowCount();x++)
            {
                for(i=iz;i<ui->tableWidget_13->columnCount();i++)
                {
                    moc_2 = ui->tableWidget_13->item(x,i)->text();

                    j = jz;
                    while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
                    {
                        ui->tableWidget_13->item(x,i)->setBackground(Qt::green);

                        QSettings settings( "BRU", "IM View");
                        settings.setValue( "iz", i+1);
                        settings.setValue( "jz", j+1);
                        settings.setValue( "xz", x);

                        if(x == ui->tableWidget_13->rowCount()-1)
                        {
                            settings.setValue( "iz", i+1);
                        }
                        return;
                    }
                    jz=0;
                }
                iz = 0;
            }

            QSettings settings( "BRU", "IM View");
            settings.setValue( "iz", 0);
            settings.setValue( "xz", 0);
            settings.setValue( "jz", 0);
            settings.setValue( "number", 12);
            QMessageBox::information(this, tr("IM View"), tr("Анализ таблицы закончен"));
            ui->tabWidget->setCurrentIndex(5);
            ui->widget_6->ui->tabWidget->setCurrentIndex(2);
            ui->tableWidget_8->setFocus();
        }
    }

    if ((number == 12) && (number < 13))
    {
        //i=0,x=0,j=0;
        QSettings settings( "BRU", "IM View");
        xz = settings.value( "xz", "").toInt();
        iz = settings.value( "iz", "").toInt();
        jz = settings.value( "jz", "").toInt();

        if(ui->tableWidget_8->isEnabled()==true)
        {
            for(x=xz;x<ui->tableWidget_8->rowCount();x++)
            {
                for(i=iz;i<ui->tableWidget_8->columnCount();i++)
                {
                    moc_2 = ui->tableWidget_8->item(x,i)->text();

                    j = jz;
                    while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
                    {
                        ui->tableWidget_8->item(x,i)->setBackground(Qt::green);

                        QSettings settings( "BRU", "IM View");
                        settings.setValue( "iz", i+1);
                        settings.setValue( "jz", j+1);
                        settings.setValue( "xz", x);

                        if(x == ui->tableWidget_8->rowCount()-1)
                        {
                            settings.setValue( "iz", i+1);
                        }
                        return;
                    }
                    jz=0;
                }
                iz = 0;
            }

            QSettings settings( "BRU", "IM View");
            settings.setValue( "iz", 0);
            settings.setValue( "xz", 0);
            settings.setValue( "jz", 0);
            settings.setValue( "number", 13);
            QMessageBox::information(this, tr("IM View"), tr("Анализ таблицы закончен"));
            ui->tabWidget->setCurrentIndex(5);
            ui->widget_6->ui->tabWidget->setCurrentIndex(3);
            ui->tableWidget_10->setFocus();
        }
    }

    if ((number == 13) && (number < 14))
    {
        //i=0,x=0,j=0;
        QSettings settings( "BRU", "IM View");
        xz = settings.value( "xz", "").toInt();
        iz = settings.value( "iz", "").toInt();
        jz = settings.value( "jz", "").toInt();

        if(ui->tableWidget_10->isEnabled()==true)
        {
            for(x=xz;x<ui->tableWidget_10->rowCount();x++)
            {
                for(i=iz;i<ui->tableWidget_10->columnCount();i++)
                {
                    moc_2 = ui->tableWidget_10->item(x,i)->text();

                    j = jz;
                    while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
                    {
                        ui->tableWidget_10->item(x,i)->setBackground(Qt::green);

                        QSettings settings( "BRU", "IM View");
                        settings.setValue( "iz", i+1);
                        settings.setValue( "jz", j+1);
                        settings.setValue( "xz", x);

                        if(x == ui->tableWidget_10->rowCount()-1)
                        {
                            settings.setValue( "iz", i+1);
                        }
                        return;
                    }
                    jz=0;
                }
                iz = 0;
            }

            QSettings settings( "BRU", "IM View");
            settings.setValue( "iz", 0);
            settings.setValue( "xz", 0);
            settings.setValue( "jz", 0);
            settings.setValue( "number", 14);
            QMessageBox::information(this, tr("IM View"), tr("Анализ таблицы закончен"));
            ui->tabWidget->setCurrentIndex(0);
            ui->treeView->setFocus();
        }
    }



    if ((number == 14) && (number < 15))
    {
        QSettings settings( "BRU", "IM View");
        xz = settings.value( "xz", "").toInt();
        iz = settings.value( "iz", "").toInt();
        jz = settings.value( "jz", "").toInt();
        if(ui->treeView->isEnabled()==true)
        {
            iterate(model2->index(0,0), model2, str);

            QSettings settings( "BRU", "IM View");
            settings.setValue( "iz", 0);
            settings.setValue( "xz", 0);
            settings.setValue( "jz", 0);
            settings.setValue( "number", 15);
        }
    }

    if(number == 15)
    {
        QMessageBox::information(this, tr("IM View"), tr("Поиск закончен"));

    }
}

void MainWindow::zakr()
{
    ui->widget_12->setVisible(false);

    int currentRow = ui->widget->ui->tableView->model()->rowCount();
    int currentCol = ui->widget->ui->tableView->model()->columnCount();

    for(int i = 0; i < currentCol; i ++)
    {
        for(int x = 0; x < currentRow; x ++)
        {
            QString color=ui->widget->modd->item(x,i)->background().color().name();
            if(color == "#ffff00")
            {
                ui->widget->modd->item(x,i)->setBackground(QColor(255, 255, 255));
            }
        }
    }

    for(int i = 0; i < ui->tableWidget_16->columnCount(); i++)
    {
        for(int x = 0; x < ui->tableWidget_16->rowCount(); x++)
        {
            if (x % 2 == 0)
            {
                ui->tableWidget_16->item(x,i)->setBackground(QColor(255, 255, 191));
            }
            else
            {
                ui->tableWidget_16->item(x,i)->setBackground( QColor(255, 255, 222));
            }
        }
    }

    for(int i = 0; i < ui->tableWidget_2->columnCount(); i++)
    {
        for(int x = 0; x < ui->tableWidget_2->rowCount(); x++)
        {
            if (x % 2 == 0)
            {
                ui->tableWidget_2->item(x,i)->setBackground(QColor(255, 255, 191));
            }
            else
            {
                ui->tableWidget_2->item(x,i)->setBackground( QColor(255, 255, 222));
            }
        }
    }

    for(int i = 0; i < ui->tableWidget_4->columnCount(); i++)
    {
        for(int x = 0; x < ui->tableWidget_4->rowCount(); x++)
        {
            if (x % 2 == 0)
            {
                ui->tableWidget_4->item(x,i)->setBackground(QColor(255, 255, 191));
            }
            else
            {
                ui->tableWidget_4->item(x,i)->setBackground( QColor(255, 255, 222));
            }
        }
    }

    for(int i=0; i<ui->widget_5->ui->widget_2->ui->tableWidget->columnCount();i++)
    {
        for(int x=0; x<ui->widget_5->ui->widget_2->ui->tableWidget->rowCount();x++)
        {
            if (x % 2 == 0)
            {
                ui->widget_5->ui->widget_2->ui->tableWidget->item(x,i)->setBackground(QColor(255, 255, 191));
            }
            else
            {
                ui->widget_5->ui->widget_2->ui->tableWidget->item(x,i)->setBackground( QColor(255, 255, 222));
            }
        }
    }

    for(int i=0; i<ui->tableWidget_9->columnCount();i++)
    {
        for(int x=0; x<ui->tableWidget_9->rowCount();x++)
        {
            if (x % 2 == 0)
            {
                ui->tableWidget_9->item(x,i)->setBackground(QColor(225, 255, 255));
            }
            else
            {
                ui->tableWidget_9->item(x,i)->setBackground( QColor(200, 255, 255));
            }
        }
    }

    for(int i=0; i<ui->widget_5->ui->tableWidget->columnCount();i++)
    {
        for(int x=0; x<ui->widget_5->ui->tableWidget->rowCount();x++)
        {
            if (x % 2 == 0)
            {
                ui->widget_5->ui->tableWidget->item(x,i)->setBackground(QColor(255, 255, 191));
            }
            else
            {
                ui->widget_5->ui->tableWidget->item(x,i)->setBackground( QColor(255, 255, 222));
            }
        }
    }

    for(int i=0; i<ui->tableWidget_3->columnCount();i++)
    {
        for(int x=0; x<ui->tableWidget_3->rowCount();x++)
        {
            if (x % 2 == 0)
            {
                ui->tableWidget_3->item(x,i)->setBackground(QColor(225, 255, 255));
            }
            else
            {
                ui->tableWidget_3->item(x,i)->setBackground( QColor(200, 255, 255));
            }
        }
    }

    for(int i=0;i<ui->tableWidget_5->columnCount();i++)
    {
        for(int x=0;x<ui->tableWidget_5->rowCount();x++)
        {
            if (x % 2 == 0)
            {
                ui->tableWidget_5->item(x,i)->setBackground(QColor(225, 255, 255));
            }
            else
            {
                ui->tableWidget_5->item(x,i)->setBackground( QColor(200, 255, 255));
            }
        }
    }

    for(int i=0;i<ui->tableWidget_6->columnCount();i++)
    {
        for(int x=0;x<ui->tableWidget_6->rowCount();x++)
        {
            if (x % 2 == 0)
            {
                ui->tableWidget_6->item(x,i)->setBackground(QColor(225, 255, 255));
            }
            else
            {
                ui->tableWidget_6->item(x,i)->setBackground( QColor(200, 255, 255));
            }
        }
    }

    for(int i=0;i<ui->tableWidget_7->columnCount();i++)
    {
        for(int x=0;x<ui->tableWidget_7->rowCount();x++)
        {
            if (x % 2 == 0)
            {
                ui->tableWidget_7->item(x,i)->setBackground(QColor(255, 255, 191));
            }
            else
            {
                ui->tableWidget_7->item(x,i)->setBackground( QColor(255, 255, 222));
            }
        }
    }

    for(int i=0;i<ui->tableWidget_13->columnCount();i++)
    {
        for(int x=0;x<ui->tableWidget_13->rowCount();x++)
        {
            if (x % 2 == 0)
            {
                ui->tableWidget_13->item(x,i)->setBackground(QColor(225, 255, 255));
            }
            else
            {
                ui->tableWidget_13->item(x,i)->setBackground( QColor(200, 255, 255));
            }
        }
    }

    for(int i=0;i<ui->tableWidget_8->columnCount();i++)
    {
        for(int x=0;x<ui->tableWidget_8->rowCount();x++)
        {
            if (x % 2 == 0)
            {
                ui->tableWidget_8->item(x,i)->setBackground(QColor(225, 255, 255));
            }
            else
            {
                ui->tableWidget_8->item(x,i)->setBackground( QColor(200, 255, 255));
            }
        }
    }

    for(int i=0;i<ui->tableWidget_10->columnCount();i++)
    {
        for(int x=0;x<ui->tableWidget_10->rowCount();x++)
        {
            if (x % 2 == 0)
            {
                ui->tableWidget_10->item(x,i)->setBackground(QColor(225, 255, 255));
            }
            else
            {
                ui->tableWidget_10->item(x,i)->setBackground( QColor(200, 255, 255));
            }
        }
    }    

    QSettings settings( "BRU", "IM View");
    settings.setValue( "ii", 0);
    settings.setValue( "xx", 0);
    settings.setValue( "iz", 0);
    settings.setValue( "xz", 0);
    settings.setValue( "iu", 0);
    settings.setValue( "jz", 0);
    settings.setValue( "number", 0);
}

void MainWindow::select_all()
{
    int index = 0;
    QString str = ui->widget_12->ui->lineEdit->text();
    int currentRow = ui->widget->modd->rowCount();
    int currentCol = ui->widget->modd->columnCount();
    if(str!=nullptr)
    {
        for(int i=0;i<currentCol;i++)
        {
            for(int x=0;x<currentRow;x++)
            {
                //QModelIndex index = ui->widget->ui->tableView->model()->index(x, i, QModelIndex());
                //QString s = ui->widget->ui->tableView->model()->data(index).toString();

                QString moc_2 = ui->widget->modd->item(x,i)->text();

                int pos = moc_2.indexOf(str, 0,Qt::CaseInsensitive);
                if (pos != -1)
                {
                    ui->widget->modd->item(x,i)->setBackground(Qt::yellow);
                    //return true;
                }

                //index = moc_2.indexOf(str, index);
                //int j = 0;
                //while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive)) != -1)
                //{
                    // QColor color(Qt::yellow);
                    // QBrush br(color);
                    // br.setColor(color);
                   // ui->widget->modd->item(x,i)->setBackground(Qt::yellow);
                    //ui->widget->ui->tableView->model()->setData(index,br, Qt::BackgroundRole);
                   // ++j;
              //  }

                // if(s==str)
                // {
                //     QColor color(Qt::yellow);
                //     QBrush br(color);
                //     br.setColor(color);
                //     ui->widget->ui->tableView->model()->setData(index,br, Qt::BackgroundRole);
                // }
            }
        }
    }

    //select all tableWidget



    for(int i = 0; i < ui->tableWidget_16->columnCount(); i++)
    {
        for(int x = 0; x < ui->tableWidget_16->rowCount(); x++)
        {
            QString moc_2 = ui->tableWidget_16->item(x,i)->text();
            index = moc_2.indexOf(str, index);
            int j = 0;
            while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
            {
                ui->tableWidget_16->item(x,i)->setBackground(Qt::yellow);
                ++j;
            }
        }
    }

    for(int i = 0; i < ui->tableWidget_2->columnCount(); i++)
    {
        for(int x = 0; x < ui->tableWidget_2->rowCount(); x++)
        {
            QString moc_2 = ui->tableWidget_2->item(x,i)->text();
            index = moc_2.indexOf(str, index);
            int j = 0;
            while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
            {
                ui->tableWidget_2->item(x,i)->setBackground(Qt::yellow);
                ++j;
            }
        }
    }

    for(int i = 0; i <  ui->tableWidget_4->columnCount(); i++)
    {
        for(int x = 0; x <  ui->tableWidget_4->rowCount(); x++)
        {
            QString moc_2 =  ui->tableWidget_4->item(x,i)->text();
            index = moc_2.indexOf(str, index);
            int j = 0;
            while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
            {
                ui->tableWidget_4->item(x,i)->setBackground(Qt::yellow);
                ++j;
            }
        }
    }

    for(int i=0;i<ui->widget_5->ui->widget_2->ui->tableWidget->columnCount();i++)
    {
        for(int x=0;x<ui->widget_5->ui->widget_2->ui->tableWidget->rowCount();x++)
        {
            QString moc_2 = ui->widget_5->ui->widget_2->ui->tableWidget->item(x,i)->text();
            index = moc_2.indexOf(str, index);
            int j = 0;
            while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
            {
                ui->widget_5->ui->widget_2->ui->tableWidget->item(x,i)->setBackground(Qt::yellow);
                ++j;
            }
        }
    }

    for(int i=0;i<ui->tableWidget_9->columnCount();i++)
    {
        for(int x=0;x<ui->tableWidget_9->rowCount();x++)
        {
            QString moc_2 = ui->tableWidget_9->item(x,i)->text();
            index = moc_2.indexOf(str, index);
            int j = 0;
            while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
            {
                ui->tableWidget_9->item(x,i)->setBackground(Qt::yellow);
                ++j;
            }
        }
    }

    for(int i=0;i<ui->widget_5->ui->tableWidget->columnCount();i++)
    {
        for(int x=0;x<ui->widget_5->ui->tableWidget->rowCount();x++)
        {
            QString moc_2 = ui->widget_5->ui->tableWidget->item(x,i)->text();
            index = moc_2.indexOf(str, index);
            int j = 0;
            while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
            {
                ui->widget_5->ui->tableWidget->item(x,i)->setBackground(Qt::yellow);
                ++j;
            }
        }
    }

    for(int i=0;i<ui->tableWidget_3->columnCount();i++)
    {
        for(int x=0;x<ui->tableWidget_3->rowCount();x++)
        {
            QString moc_2 = ui->tableWidget_3->item(x,i)->text();
            index = moc_2.indexOf(str, index);
            int j = 0;
            while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
            {
                ui->tableWidget_3->item(x,i)->setBackground(Qt::yellow);
                ++j;
            }
        }
    }

    for(int i=0;i<ui->tableWidget_5->columnCount();i++)
    {
        for(int x=0;x<ui->tableWidget_5->rowCount();x++)
        {
            QString moc_2 = ui->tableWidget_5->item(x,i)->text();
            index = moc_2.indexOf(str, index);
            int j = 0;
            while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
            {
                ui->tableWidget_5->item(x,i)->setBackground(Qt::yellow);
                ++j;
            }
        }
    }

    for(int i=0;i<ui->tableWidget_6->columnCount();i++)
    {
        for(int x=0;x<ui->tableWidget_6->rowCount();x++)
        {
            QString moc_2 = ui->tableWidget_6->item(x,i)->text();
            index = moc_2.indexOf(str, index);
            int j = 0;
            while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
            {
                ui->tableWidget_6->item(x,i)->setBackground(Qt::yellow);
                ++j;
            }
        }
    }

    for(int i=0;i<ui->tableWidget_7->columnCount();i++)
    {
        for(int x=0;x<ui->tableWidget_7->rowCount();x++)
        {
            QString moc_2 = ui->tableWidget_7->item(x,i)->text();
            index = moc_2.indexOf(str, index);
            int j = 0;
            while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
            {
                ui->tableWidget_7->item(x,i)->setBackground(Qt::yellow);
                ++j;
            }
        }
    }

    for(int i=0;i<ui->tableWidget_13->columnCount();i++)
    {
        for(int x=0;x<ui->tableWidget_13->rowCount();x++)
        {
            QString moc_2 = ui->tableWidget_13->item(x,i)->text();
            index = moc_2.indexOf(str, index);
            int j = 0;
            while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
            {
                ui->tableWidget_13->item(x,i)->setBackground(Qt::yellow);
                ++j;
            }
        }
    }

    for(int i=0;i<ui->tableWidget_8->columnCount();i++)
    {
        for(int x=0;x<ui->tableWidget_8->rowCount();x++)
        {
            QString moc_2 = ui->tableWidget_8->item(x,i)->text();
            index = moc_2.indexOf(str, index);
            int j = 0;
            while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
            {
                ui->tableWidget_8->item(x,i)->setBackground(Qt::yellow);
                ++j;
            }
        }
    }

    for(int i=0;i<ui->tableWidget_10->columnCount();i++)
    {
        for(int x=0;x<ui->tableWidget_10->rowCount();x++)
        {
            QString moc_2 = ui->tableWidget_10->item(x,i)->text();
            index = moc_2.indexOf(str, index);
            int j = 0;
            while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
            {
                ui->tableWidget_10->item(x,i)->setBackground(Qt::yellow);
                ++j;
            }
        }
    }

    for(int i=0;i<ui->tableWidget_11->columnCount();i++)
    {
        for(int x=0;x<ui->tableWidget_11->rowCount();x++)
        {
            QString moc_2 = ui->tableWidget_11->item(x,i)->text();
            index = moc_2.indexOf(str, index);
            int j = 0;
            while ((j = moc_2.indexOf(str, j, Qt::CaseSensitive )) != -1)
            {
                ui->tableWidget_11->item(x,i)->setBackground(Qt::yellow);
                ++j;
            }
        }
    }

    //iterate(model2->index(0,0), model2, str);
    iterate(model2->index(15,0), model2, str);
}

void MainWindow::rename()
{
    //rename in tableview

    QString str = ui->widget_12->ui->lineEdit->text();
    QString str_2 = ui->widget_12->ui->lineEdit_2->text();
    QString moc;
    int i,x,ii,xx;

    for(i=0;i<=model->columnCount();i++)
    {
        for(x=0;x<=model->rowCount();x++)
        {
            QModelIndex ind = model->index(x,i);
            if(ind.data().toString()==str)
            {
                modd->item( x, i )->setBackground( Qt::yellow );
            }
        }
    }


    QSettings settings( "BRU", "IM View");
    xx = settings.value( "xx", "").toInt();
    ii = settings.value( "ii", "").toInt();

    for(i=ii;i<=modd->columnCount();i++)
    {
        for(x=xx;x<=modd->rowCount();x++)
        {
            moc = ui->widget->ui->tableView->model()->data(ui->widget->ui->tableView->model()->index(x,i)).toString();

            if(moc==str)
            {
                QFont font("DroidSans", 10, QFont::Bold,false);

                modd->item(x,i)->setFont(font);
                modd->item(x,i)->setText(str_2);
                modd->item(x,i)->setBackground(Qt::yellow);
                QSettings settings( "BRU", "IM View");
                settings.setValue( "ii", i);
                settings.setValue( "xx", x+1);
                return;
            }
        }
    }
    //rename in tablewidget

    for(i=ii;i<ui->tableWidget->columnCount();i++)
    {
        for(x=xx;x<ui->tableWidget->rowCount();x++)
        {
           QString moc_2 = ui->tableWidget->item(x,i)->text();

            if(moc_2==str)
            {
                ui->tableWidget->item(x,i)->setText(str_2);
                ui->tableWidget->item(x,i)->setText(str_2);
                ui->tableWidget->item(x,i)->setBackground(Qt::yellow);
                QSettings settings( "BRU", "IM View");
                settings.setValue( "ii", i);
                settings.setValue( "xx", x+1);
                return;
            }
        }
    }
}

void MainWindow::rename_all()
{
    //rename in tableview

    QString str = ui->widget_12->ui->lineEdit->text();
    QString str_2 = ui->widget_12->ui->lineEdit_2->text();
    QString moc;
    int i,x,ii,xx;

    QSettings settings( "BRU", "IM View");
    xx = settings.value( "xx", "").toInt();
    ii = settings.value( "ii", "").toInt();

    for(i=ii;i<=model->columnCount();i++)
    {
        for(x=xx;x<=model->rowCount();x++)
        {
            moc = ui->widget->ui->tableView->model()->data(ui->widget->ui->tableView->model()->index(x,i)).toString();

            if(moc==str)
            {
                modd->item(x,i)->setText(str_2);
                modd->item(x,i)->setBackground(Qt::yellow);
                QSettings settings( "BRU", "IM View");
                settings.setValue( "ii", i);
                settings.setValue( "xx", x+1);
               // return;
            }
        }
    }
    //rename in tablewidget

    for(i=ii;i<ui->tableWidget->columnCount();i++)
    {
        for(x=xx;x<ui->tableWidget->rowCount();x++)
        {
            QString moc_2 = ui->tableWidget->item(x,i)->text();

            if(moc_2==str)
            {
                ui->tableWidget->item(x,i)->setText(str_2);
                ui->tableWidget->item(x,i)->setText(str_2);
                ui->tableWidget->item(x,i)->setBackground(Qt::yellow);
                QSettings settings( "BRU", "IM View");
                settings.setValue( "ii", i);
                settings.setValue( "xx", x+1);
                //return;
            }
        }
    }
}

bool MainWindow::iterate(const QModelIndex index, const QStandardItemModel * model, QString str)
{

    str = ui->widget_12->ui->lineEdit->text();
    if (index.isValid())
    {
        // Do action here
    }

    QString itemText = model->itemData(index)[0].toString();

    int pos = itemText.indexOf(str, 0);
    if (pos != -1)
    {
        model2->itemFromIndex(index)->setBackground(Qt::yellow);
        //return true;
    }

    if (!model->hasChildren(index) || (index.flags() &
                                       Qt::ItemNeverHasChildren))
    {
        return true;
    }

    auto rows = model2->rowCount(index);
    auto cols = model2->columnCount(index);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; j++)
            if (iterate(model2->index(i, j, index), model2, str) == false)
                return false;
    }

    return true;
}

void MainWindow::changeTreeViewRowColor()
{
    item1->setData(QColor(5, 50, 255));
    item2->setBackground(QColor(5, 50, 255));
}

void::MainWindow::tab_open()
{
    int i, iu;
    QSettings settings( "BRU", "IM View");
    iu = settings.value( "iu", "").toInt();
    i=iu;
    i=i+1;
    ui->stackedWidget->setCurrentIndex(i);
    ui->label_34->setText("page_number:"+QString::number(i));
    settings.setValue( "iu", i);
    if(i==ui->stackedWidget->count()-1)
    {
        settings.setValue( "iu", -1);
    }
    return;
}

void::MainWindow::save_graphs()
{
    ui->widget_2->ui->plot->save();
}

void::MainWindow::load_graphs()
{
    ui->widget_2->ui->plot->load();
}

void MainWindow::read_klass_izol()
{

    if(klass == "A")
    {
        klass_izol.klass_A.G_A = 15.3;
        klass_izol.klass_A.B_A = 0.000095;
        G = klass_izol.klass_A.G_A;
        B = klass_izol.klass_A.B_A;
    }
    else if(klass == "B")
    {
        klass_izol.klass_B.G_B = 15.5;
        klass_izol.klass_B.B_B = 0.000102;
        G = klass_izol.klass_B.G_B;
        B = klass_izol.klass_B.B_B;
            }
    else if(klass == "C")
    {
        klass_izol.klass_C.G_C = 21.8;
        klass_izol.klass_C.B_C = 0.000155;
        G = klass_izol.klass_C.G_C;
        B = klass_izol.klass_C.B_C;
    }
    else if(klass == "E")
    {
        klass_izol.klass_E.G_E = 15.1;
        klass_izol.klass_E.B_E = 0.0000985;
        G = klass_izol.klass_E.G_E;
        B = klass_izol.klass_E.B_E;
    }
    else if(klass == "F")
    {
        klass_izol.klass_F.G_F = 19.7;
        klass_izol.klass_F.B_F = 0.000127;
        G = klass_izol.klass_F.G_F;
        B = klass_izol.klass_F.B_F;
    }
    else if(klass == "H")
    {
        klass_izol.klass_H.G_H = 24.2;
        klass_izol.klass_H.B_H = 0.000155;
        G = klass_izol.klass_H.G_H;
        B = klass_izol.klass_H.B_H;
    }

    double Q = 20;
    ui->widget_13->ui->plots->clear();
    ui->widget_13->ui->plots->addDataLine(QColor(Qt::green), 0);

    while (Q < 30)
    {
        Q = Q + 1;
        double T = 0;
        int k = 1;
        T = k*exp(((Q+273)/B)-G);
        ui->widget_13->ui->plots->addPoint(0, Q, T);

    }
}

void MainWindow::color_treview(const QModelIndex & index, const QStandardItemModel * model2)
{
   // int rows = model2->rowCount(index);
    int cols = model2->columnCount(index);

    for (int i = 0; i < cols; ++i)
            for (int j = 0; j < 8; ++j){
                QPalette p109=ui->treeView->palette();
                p109.setColor(QPalette::Base, QColor(255, 255, 222));
                p109.setColor(QPalette::AlternateBase, QColor(255, 255, 191));
                ui->treeView->setPalette(p109);

            }
}

void MainWindow::save_identf_in_file()
{
    QString filename = "result_identf_final.csv";
    QString setpath = "../Output";
    std::ofstream fout;

    QModelIndex myIndex;
    myIndex = ui->widget->ui->tableView->model()->index(ui->widget->ui->tableView->currentIndex().row(), 1, QModelIndex());
    //QString str = ui->widget->ui->tableView->model()->data(myIndex).toString();
    //char* ch = str.toLocal8Bit().data();

    double R1 = ui->lineEdit_12->text().toDouble();
    double R2 = ui->lineEdit_11->text().toDouble();
    double L = ui->lineEdit_10->text().toDouble();
    double Lm = ui->lineEdit_8->text().toDouble();

    base.identfFilename = setpath+QDir::separator()+filename;

    fout.open(QString(base.identfFilename).toStdString(),std::ios::out | std::ios_base::app);

    fout << "Марка двигателя:&" << ui->widget->ui->tableView->model()->data(myIndex).toString().toLocal8Bit().data() << std::endl;
    fout << "Активное сопротивление фазы статора:&" << R1 << std::endl;
    fout << "Активное сопротивление фазы ротора:&" << R2 << std::endl;
    fout << "Индуктивность фазы статора:&" << L << std::endl;
    fout << "Индуктивность фазы ротора:&" << L << std::endl;
    fout << "Индуктивность взаимоиндукции:&" << Lm << std::endl;

    fout << std::endl;

    fout.close();
}

void MainWindow::saveDataSQL()
{
    ui->widget->zapis_from_cell_tableview();
}

double dPprev = 0.0;
double temp_prev = 0.0;

void MainWindow::on_electromagn_tick()
{
    double t = ui->widget_3->key;
    int maxTime = item174->text().toInt();

    statusbar_label_9->setText("T = " + QString::number(t,'f',5) + " " + "c");
    statusbar_label_9->setAlignment(Qt::AlignTop);
    statusbar_progres->setAlignment(Qt::AlignTop);
    statusbar_progres->setValue(t / maxTime * 100);
   // qDebug() << t / maxTime * 100;

    if (tepl_start)
    {
        tepl_ident_P1.append(tepl_struct.P1);
        tepl_ident_P2.append(tepl_struct.P2);
    }

    //double y =  80.0 *( 1.0 - exp(-t / 1800.0)) + item28->text().toDouble();

    //ui->widget_10->ui->plot->addPoint(0, t, y);

    double Temp = 80.0 *( 1.0 - exp(-t / 1800.0)) + item28->text().toDouble();
    tepl_ident_t.append(t);
    tepl_ident_StatorTemp.append(Temp);

    double k = 1;
    double Ts = 0.01;
    double A = 200;
    double C = 6000;

    double dP = tepl_struct.P1 - tepl_struct.P2;

    if (fabs(dP - dPprev) < 20.0)
        tepl_start = true;

    double temp = temp_prev*((2*C-A*k*Ts)/(2*C+A*k*Ts))+(k*Ts*dP+k*Ts*dPprev)/(2*C+A*k*Ts);
    ui->widget_10->ui->plot->addPoint(0, t, temp);

    temp_prev = temp;
    dPprev = dP;

    if (ui->widget_3->key > maxTime)
    {
        electromagn_stop();

        double P1sum = 0.0;
        double P2sum = 0.0;
        for (int i = 0; i < tepl_ident_P1.size(); i++)
        {
            P1sum += tepl_ident_P1[i];
            P2sum += tepl_ident_P2[i];
        }
        P1sum /= tepl_ident_P1.size();
        P2sum /= tepl_ident_P2.size();

        ui->tableWidget_16->item(0,2)->setText(QString::number(P1sum - P2sum,'f',3));

        //double A = tepl_ident_StatorTemp[tepl_ident_StatorTemp.size() - 1] / (P1sum - P2sum);
        //double t1 = tepl_ident_StatorTemp

        statusbar_label_9->setVisible(false);
        statusbar_progres->setVisible(false);
        QMessageBox::information(this, "Ахтунг", "Электромагнитный расчет закончен");
    }
}

void MainWindow::loadMotorParameters()
{
    QModelIndex myIndex, myIndex2, myIndex3,myIndex4,myIndex5,myIndex6,myIndex7,myIndex8,myIndex9,myIndex10;
    myIndex = ui->widget->ui->tableView->model()->index(ui->widget->ui->tableView->currentIndex().row(), 2, QModelIndex());
    base.P_nom=ui->widget->ui->tableView->model()->data(myIndex).toDouble();
    myIndex2 = ui->widget->ui->tableView->model()->index(ui->widget->ui->tableView->currentIndex().row(), 3, QModelIndex());
    base.n_nom=ui->widget->ui->tableView->model()->data(myIndex2).toDouble();
    myIndex3 = ui->widget->ui->tableView->model()->index(ui->widget->ui->tableView->currentIndex().row(), 4, QModelIndex());
    base.U_fnom=ui->widget->ui->tableView->model()->data(myIndex3).toDouble();
    myIndex4 = ui->widget->ui->tableView->model()->index(ui->widget->ui->tableView->currentIndex().row(), 5, QModelIndex());
    base.cosf_nom=ui->widget->ui->tableView->model()->data(myIndex4).toDouble();
    myIndex5 = ui->widget->ui->tableView->model()->index(ui->widget->ui->tableView->currentIndex().row(), 6, QModelIndex());
    base.kpd_nom=ui->widget->ui->tableView->model()->data(myIndex5).toDouble();
    myIndex6 = ui->widget->ui->tableView->model()->index(ui->widget->ui->tableView->currentIndex().row(), 7, QModelIndex());
    base.muk=ui->widget->ui->tableView->model()->data(myIndex6).toDouble();
    myIndex7 = ui->widget->ui->tableView->model()->index(ui->widget->ui->tableView->currentIndex().row(), 8, QModelIndex());
    base.n_0=ui->widget->ui->tableView->model()->data(myIndex7).toDouble();
    myIndex8 = ui->widget->ui->tableView->model()->index(ui->widget->ui->tableView->currentIndex().row(), 9, QModelIndex());
    klass=ui->widget->ui->tableView->model()->data(myIndex8).toString();
    myIndex9 = ui->widget->ui->tableView->model()->index(ui->widget->ui->tableView->currentIndex().row(), 9, QModelIndex());
    base.J_dv=ui->widget->ui->tableView->model()->data(myIndex9).toDouble();
    myIndex10 = ui->widget->ui->tableView->model()->index(ui->widget->ui->tableView->currentIndex().row(), 9, QModelIndex());
    klass=ui->widget->ui->tableView->model()->data(myIndex10).toString();
}

void MainWindow::actionaction_graph()
{
    if(ui->actionaction_graph->isChecked())
    {
        if(ui->tabWidget->currentIndex() == 1)
        {
            ui->stackedWidget->hide();
            ui->widget_2->ui->widget->show();
        }
        else if(ui->tabWidget->currentIndex() == 4)
        {
            ui->stackedWidget->hide();
            ui->widget_3->ui->widget->show();
            ui->widget_3->ui->tableWidget->item(0,5)->setText(QString::number(model_el.u_dev_a,'f',3));
            ui->widget_3->ui->tableWidget->item(1,5)->setText(QString::number(model_el.u_dev_b,'f',3));
            ui->widget_3->ui->tableWidget->item(2,5)->setText(QString::number(model_el.u_dev_b,'f',3));
            ui->widget_3->ui->tableWidget->item(3,5)->setText(QString::number(model_el.i_dev_a,'f',3));
            ui->widget_3->ui->tableWidget->item(4,5)->setText(QString::number(model_el.i_dev_b,'f',3));
            ui->widget_3->ui->tableWidget->item(5,5)->setText(QString::number(model_el.i_dev_c,'f',3));
            ui->widget_3->ui->tableWidget->item(6,5)->setText(QString::number(model_el.omega,'f',3));
            ui->widget_3->ui->tableWidget->item(7,5)->setText(QString::number(model_el.M,'f',3));
            ui->widget_3->ui->tableWidget->item(8,5)->setText(QString::number(model_el.Mc,'f',3));
        }
        else if(ui->tabWidget->currentIndex() == 5)
        {
            //ui->stackedWidget->hide();
            ui->widget_5->ui->widget_4->ui->widget->show();
        }
    }
    else
    {
        ui->widget_2->ui->widget->hide();
        ui->widget_3->ui->widget->hide();
        ui->widget_5->ui->widget_4->ui->widget->hide();
        ui->stackedWidget->show();
    }
}

void MainWindow::action_gruph()
{
    if(ui->action_gruph->isChecked())
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(6);
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void MainWindow::updateWindowSize()
{
    // Получение размеров экрана
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen)
    {
        QSize screenSize = screen->size();
        int width = static_cast<int>(screenSize.width() * 0.8);
        int height = static_cast<int>(screenSize.height() * 0.8);
        this->resize(width, height);
        this->move((screenSize.width() - width) / 2, (screenSize.height() - height) / 2);
    }

}
