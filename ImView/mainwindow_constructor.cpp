#include <QPropertyAnimation>
#include <QStyle>
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
#include <QUndoCommand>
#include <QPixmap>
#include <QSvgRenderer>
#include <QString>
#include <QEvent>
#include <QSettings>
#include <QSqlRecord>
#include <QFileDialog>
#include <QSvgRenderer>
#include <QPainter>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusVariant>
#include <QDBusReply>
#include <QDBusInterface>
#include <QImageWriter>
#include <cxxabi.h>

#include "base.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "datas.h"
#include "ui_datas.h"
#include "identf.h"
#include "ui_identf.h"
#include "electromagn.h"
#include "kalibr.h"
#include "teplovent.h"
//#include "ui_nastroiki.h"
#include "ui_poisk.h"
#include "ui_teplovent.h"
#include "ui_electromagn.h"
#include "ui_draw_line.h"
#include "ui_draw_poper.h"
#include "ui_teplschem.h"
#include "ui_vent_datas.h"
#include "ui_vent_identf.h"
#include "ui_vent_model.h"
#include "ui_trend.h"
#include "ui_datas.h"
#include "vent_model.h"
#include "ui_vent_model.h"
#include "customhelpdelegate.h"
#include "plot.h"
#include "tepl_identf.h"
#include "settings.h"
#include "poisk.h"
#include "pushbuttondelegate.h"
#include "start_app.h"
//#include "spandelegate.h"
//#include "branchdrawingdelegate.h"
#include "linedelegate.h"
#include "fillicondelegate.h"
#include "version.h"
#include "version_hash.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , cleanState(true)
    , undoOperation(false)
{
    ui->setupUi(this);

#ifdef GIT_HASH
    QString vers2 = QString("%1.%2.%3").arg(APP_VERSION_MAJOR).arg(APP_VERSION_MINOR).arg(GIT_HASH);
    qDebug() << "Git hash:" << vers2;
#endif

    ui->actionaction_graph->setCheckable(true);
    ui->action_gruph->setCheckable(true);
    ui->widget_2->ui->widget->hide();

    ui->actionsdtart_app->setEnabled(false);

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

    connect(ui->treeView, &QTreeView::expanded, this, &MainWindow::onNodeExpandeds);
    connect(ui->treeView, &QTreeView::collapsed, this, &MainWindow::onNodeCollapseds);

    //Управление меню для sql-баз
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);
    onTabChanged(0);

    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged_2);
    onTabChanged_2(1);

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

    connect(ui->action_create, &QAction::triggered, this, &MainWindow::action_create);
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

    connect(ui->enter_dannie_vent, &QAction::triggered, this, &MainWindow::enter_dannie_vent);
    connect(ui->save_dannie_vent, &QAction::triggered, this, &MainWindow::save_dannie_vent);
    connect(ui->delete_dannie_vent, &QAction::triggered, this, &MainWindow::delete_dannie_vent);

    connect(ui->identf_pusk, &QAction::triggered, this, &MainWindow::identf_pusk);
    ui->identf_stop->setEnabled(false);
    connect(ui->identf_pusk_panel, &QAction::triggered, this, &MainWindow::identf_pusk);
    connect(ui->identf_stop, &QAction::triggered, this, &MainWindow::identf_stop);
    connect(ui->identf_stop_panel, &QAction::triggered, this, &MainWindow::identf_stop);
    connect(ui->actionteplident_start, &QAction::triggered, this, &MainWindow::actionteplident_start);
    connect(ui->actionteplident_start_panel, &QAction::triggered, this, &MainWindow::actionteplident_start);
    connect(ui->actionteplident_stop, &QAction::triggered, this, &MainWindow::actionteplident_stop);
    connect(ui->actionteplident_stop_panel, &QAction::triggered, this, &MainWindow::actionteplident_stop);
    connect(ui->ventidentf_start, &QAction::triggered, this, &MainWindow::ventidentf_start);
    connect(ui->ventidentf_start_panel, &QAction::triggered, this, &MainWindow::ventidentf_start);
    connect(ui->vent_identf_stop_panel, &QAction::triggered, this, &MainWindow::ventidentf_stop);
    connect(ui->electromagn_start, &QAction::triggered, this, &MainWindow::electromagn_start);
    connect(ui->electromagn_start_panel, &QAction::triggered, this, &MainWindow::electromagn_start);
    connect(ui->electromagn_stop, &QAction::triggered, this, &MainWindow::electromagn_stop);
    connect(ui->electromagn_stop_panel, &QAction::triggered, this, &MainWindow::electromagn_stop);
    connect(ui->kalibr_osc, &QAction::triggered, this, &MainWindow::kalibr_osc);
    connect(ui->actionresult, &QAction::triggered, this, &MainWindow::actionresult);
    connect(ui->actionresultidentf, &QAction::triggered, this, &MainWindow::actionresultidentf);
    connect(ui->identf_nastr, &QAction::triggered, this,&MainWindow::open_identf_nastr);
    connect(ui->identf_nastr_2, &QAction::triggered, this,&MainWindow::open_identf_nastr_2);
    connect(ui->identf_nastr_3, &QAction::triggered, this,&MainWindow::open_identf_nastr_3);

    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::actionExit);
    connect(ui->actionabout, &QAction::triggered, this, &MainWindow::actionabout);
    connect(ui->actionhelp, &QAction::triggered, this, &MainWindow::actionhelp);
    connect(ui->switch_regim_upr,&QPushButton::clicked, this, &MainWindow::switch_regim_upr);
    connect(ui->actionaction_graph, &QAction::triggered, this, &MainWindow::actionaction_graph);
    connect(ui->action_gruph, &QAction::triggered, this, &MainWindow::action_gruph);
    connect(ui->actionsdtart_app, &QAction::triggered, this, &MainWindow::open_start_screen);
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::enable_disable_actionsdtart_app);
    connect(ui->stackedWidget, &QStackedWidget::currentChanged, this, &MainWindow::enable_disable_actionsdtart_app);

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
    connect(ui->radioButton_22,&QRadioButton::toggled, this, &MainWindow::radioButton_22_toggled);
    connect(ui->radioButton_17,&QRadioButton::toggled, this, &MainWindow::radioButton_17_toggled);
    connect(ui->radioButton_14,&QRadioButton::toggled, this, &MainWindow::radioButton_14_toggled);
    connect(ui->radioButton_15,&QRadioButton::toggled, this, &MainWindow::loadTable1);
    connect(ui->radioButton_16,&QRadioButton::toggled, this, &MainWindow::loadTable2);

    connect(ui->pushButton_5, &QPushButton::clicked,this, &MainWindow::electrostart);
    connect(ui->pushButton_8, &QPushButton::clicked,this, &MainWindow::electrostop);

    ui->pushButton_8->setEnabled(false);

    connect(ui->horizontalSlider,&QSlider::valueChanged, this, &MainWindow::horizontalSlider_valueChanged);
    connect(ui->horizontalSlider_2,&QSlider::valueChanged, this, &MainWindow::horizontalSlider_2_valueChanged);
    connect(ui->horizontalSlider_3,&QSlider::valueChanged, this, &MainWindow::horizontalSlider_3_valueChanged);
    connect(ui->horizontalSlider_4,&QSlider::valueChanged, this, &MainWindow::horizontalSlider_4_valueChanged);
    connect(ui->save_identf_in_file, &QPushButton::clicked, this, &MainWindow::save_identf_in_file);
    //connect(ui->save_identf_in_file, &QPushButton::clicked, this, &MainWindow::save_vent_in_file);

    //connect(ui->widget->ui->tableView, &QAbstractItemView::clicked, this, &MainWindow::saveDataSQL);
    connect(ui->widget->ui->tableView->itemDelegate(), &QAbstractItemDelegate::closeEditor, this, &MainWindow::saveDataSQL);

    //connect(ui->widget->ui->tableView, &QHeaderView::sectionClicked, this, &MainWindow::sort);

    //connect(ui->widget->ui->tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));

    //Настройка связи форм
    ui->widget_2->wf=this;
    ui->widget_3->wf=this;
    ui->widget_5->wf=this;
    ui->widget_6->wf=this;
    ui->widget_7->wf=this;
    ui->widget_7->setDefaultVentModel();
    ui->widget_5->ui->widget_4->wf=this;
    ui->widget->wf=this;
    ui->widget_15->wf=this;
    ui->widget_10->wf=this;
    ui->widget_7->ui->widget->wf = this;

    //формирование поведения файловых операций
    ui->LoadProgect->setVisible(false);
    ui->SaveProgectToFile->setVisible(false);
    ui->save_file->setEnabled(false);
    ui->save_as_file->setEnabled(false);

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

    // if(kind_ventilation_value->text() == "Принудительная вентиляция")
    // {
    //     ui->widget_7->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/vent_schem_zam/vent_schem_zam.html")
    //                                                   .absoluteFilePath()));
    // }
    // else if(kind_ventilation_value->text() == "Независимая вентиляция")
    // {
    //     ui->widget_7->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/two_vent_schem_zam/two_vent_energo_scheme.html")
    //                                                       .absoluteFilePath()));
    // }

    showMaximized();

    ui->identf_stop->setEnabled(false);
    ui->electromagn_stop->setEnabled(false);
    ui->actionteplident_stop->setEnabled(false);

    ui->switch_regim_upr->setCheckable(true);
    ui->switch_regim_upr->setChecked(true);
    QObject::connect(ui->switch_regim_upr, &QPushButton::clicked, ui->stackedWidget, &MainWindow::setVisible);

    ui->stackedWidget->setCurrentIndex(0);

    /* НАСТРОЙКИ QTREEVIEW  */

    //Настройка свойств QTreeView
    ui->treeView->setSelectionBehavior(QTreeView :: SelectRows); // Выбираем всю строку за раз
    ui->treeView->setSelectionMode(QTreeView :: SingleSelection); // Одиночный выбор, при этом вся строка над ним является одной строкой меню
    ui->treeView->setFocusPolicy(Qt :: NoFocus);
    ui->treeView->setExpandsOnDoubleClick(true);

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

    connect(ui->treeView, &QTreeView::expanded, this, [this]()
            {
                ui->treeView->viewport()->update();
            });
    connect(ui->treeView, &QTreeView::collapsed, this, [this]()
            {
                ui->treeView->viewport()->update();
            });

    //Создание модели QTreeView
    model_treeView=new QStandardItemModel(ui->treeView);
    model_treeView->setHorizontalHeaderLabels (QStringList () << tr("Наименование") << tr("Свойство")); // Установить заголовок столбца
    ui->treeView->header()->setDefaultAlignment(Qt::AlignCenter);
    ui->treeView->setAlternatingRowColors(true);

    //настройка итемов QTreeView

    /* секция "Общие настройки сессии" */

    QList<QStandardItem*> all_sesion_name;
    all_sesion_name_parametr = new QStandardItem();
    QString all_sesion_name_tooltip=all_sesion_name_parametr->text();
    all_sesion_name_parametr->setToolTip(all_sesion_name_tooltip);
    all_sesion_name_value = new QStandardItem();
    all_sesion_name.append(all_sesion_name_parametr);
    all_sesion_name.append(all_sesion_name_value);
    model_treeView->appendRow(all_sesion_name);
    all_sesion_name_parametr->setSelectable(false);
    all_sesion_name_parametr->setEditable(false);
    all_sesion_name_value->setSelectable(false);
    all_sesion_name_value->setEditable(false);

    QList<QStandardItem*> sesion_name;
    sesion_name_parametr1 = new QStandardItem(tr("Название сессии"));
    sesion_name_parametr1->setEditable(false);
    QString wsesion_name_parametr1_tooltip1 = sesion_name_parametr1->text();
    sesion_name_parametr1->setToolTip(wsesion_name_parametr1_tooltip1);
    sesion_name_value1 = new QStandardItem(tr("Имя сеанса"));
    QString sesion_name_value1_tooltip = sesion_name_value1->text();
    sesion_name_value1->setToolTip(sesion_name_value1_tooltip);
    sesion_name.append(sesion_name_parametr1);
    sesion_name.append(sesion_name_value1);
    all_sesion_name_parametr->appendRow(sesion_name);
    sesion_name.clear();

    /* секция "Тип эксперимента" */

    kind_experiment_parametr = new QStandardItem();
    kind_experiment_parametr->setEditable(false);
    QString kind_experiment_parametr_tooltip = kind_experiment_parametr->text();
    kind_experiment_parametr->setToolTip(kind_experiment_parametr_tooltip);
    kind_experiment_value = new QStandardItem();
    kind_experiment_value->setEditable(false);
    QString kind_experiment_value_tooltip = kind_experiment_value->text();
    kind_experiment_value->setToolTip(kind_experiment_value_tooltip);
    sesion_name.append(kind_experiment_parametr);
    sesion_name.append(kind_experiment_value);
    all_sesion_name_parametr->appendRow(sesion_name);
    sesion_name.clear();

    identification_switch_parametr = new QStandardItem(tr("Идентификация данных схемы замещения"));
    identification_switch_parametr->setEditable(false);
    QString identification_switch_parametr_tooltip = identification_switch_parametr->text();
    identification_switch_parametr->setToolTip(identification_switch_parametr_tooltip);
    identification_switch_value = new QStandardItem(tr("Выбрать тип эксперимента"));
    QString identification_switch_value_tooltip = identification_switch_value->text();
    identification_switch_value->setToolTip(identification_switch_value_tooltip);
    sesion_name.append(identification_switch_parametr);
    sesion_name.append(identification_switch_value);
    kind_experiment_parametr->appendRow(sesion_name);
    sesion_name.clear();

    load_data_ruchn_identf_parametr = new QStandardItem(tr("Загрузка данных ручной идентификации"));
    load_data_ruchn_identf_parametr->setEditable(false);
    load_data_ruchn_identf_parametr->setEnabled(false);
    QString load_data_ruchn_identf_parametr_tooltip = load_data_ruchn_identf_parametr->text();
    load_data_ruchn_identf_parametr->setToolTip(load_data_ruchn_identf_parametr_tooltip);
    load_data_ruchn_identf_value = new QStandardItem(tr("Указать каталог"));
    load_data_ruchn_identf_value->setEnabled(false);
    QString load_data_ruchn_identf_value_tooltip = load_data_ruchn_identf_value->text();
    load_data_ruchn_identf_value->setToolTip(load_data_ruchn_identf_value_tooltip);
    sesion_name.append(load_data_ruchn_identf_parametr);
    sesion_name.append(load_data_ruchn_identf_value);
    kind_experiment_parametr->appendRow(sesion_name);
    sesion_name.clear();

    identufication_observer_parametr = new QStandardItem(tr("Наблюдатель состояния"));
    identufication_observer_parametr->setEditable(false);
    QString identufication_observer_parametr_tooltip = identufication_observer_parametr->text();
    identufication_observer_parametr->setToolTip(identufication_observer_parametr_tooltip);
    enter_type_experiment_value = new QStandardItem(tr("Выбрать тип эксперимента"));
    QString enter_type_experiment_value_tooltip = enter_type_experiment_value->text();
    enter_type_experiment_value->setToolTip(enter_type_experiment_value_tooltip);
    sesion_name.append(identufication_observer_parametr);
    sesion_name.append(enter_type_experiment_value);
    kind_experiment_parametr->appendRow(sesion_name);
    sesion_name.clear();

    read_data_identf_observer_parametr = new QStandardItem(tr("Чтение данных для наблюдателя скорости"));
    read_data_identf_observer_parametr->setEditable(false);
    read_data_identf_observer_parametr->setEnabled(false);
    QString read_data_identf_observer_parametr_tooltip = read_data_identf_observer_parametr->text();
    read_data_identf_observer_parametr->setToolTip(read_data_identf_observer_parametr_tooltip);
    read_data_identf_observer_value = new QStandardItem(tr("Указать каталог"));
    read_data_identf_observer_value->setEnabled(false);
    QString read_data_identf_observer_value_tooltip = read_data_identf_observer_value->text();
    read_data_identf_observer_value->setToolTip(read_data_identf_observer_value_tooltip);
    sesion_name.append(read_data_identf_observer_parametr);
    sesion_name.append(read_data_identf_observer_value);
    kind_experiment_parametr->appendRow(sesion_name);
    sesion_name.clear();

    search_kanals_parametr = new QStandardItem(tr("Настройка каналов"));
    search_kanals_parametr->setEditable(false);
    QString search_kanals_parametr_tooltip = search_kanals_parametr->text();
    search_kanals_parametr->setToolTip(search_kanals_parametr_tooltip);
    search_kanals_value = new QStandardItem(tr("Выбрать каналы"));
    QString search_kanals_value_tooltip = search_kanals_value->text();
    search_kanals_value->setToolTip(search_kanals_value_tooltip);
    sesion_name.append(search_kanals_parametr);
    sesion_name.append(search_kanals_value);
    kind_experiment_parametr->appendRow(sesion_name);
    sesion_name.clear();

    /* секция "Сохранение данных" */

    save_data_parametr = new QStandardItem();
    save_data_parametr->setEditable(false);
    QString save_data_parametr_tooltip = save_data_parametr->text();
    save_data_parametr->setToolTip(save_data_parametr_tooltip);
    save_data_value = new QStandardItem();
    save_data_value->setEditable(false);
    sesion_name.append(save_data_parametr);
    sesion_name.append(save_data_value);
    all_sesion_name_parametr->appendRow(sesion_name);
    sesion_name.clear();

    data_identification_parametr = new QStandardItem(tr("Данные идентификации параметров схемы замещения"));
    data_identification_parametr->setEditable(false);
    QString data_identification_parametr_tooltip = data_identification_parametr->text();
    data_identification_parametr->setToolTip(data_identification_parametr_tooltip);
    data_identification_value = new QStandardItem(tr("Выбрать режим"));
    QString data_identification_value_tooltip = data_identification_value->text();
    data_identification_value->setToolTip(data_identification_value_tooltip);
    sesion_name.append(data_identification_parametr);
    sesion_name.append(data_identification_value);
    save_data_parametr->appendRow(sesion_name);
    sesion_name.clear();

    data_tepl_identification_parametr = new QStandardItem(tr("Данные тепловой идентификации"));
    data_tepl_identification_parametr->setEditable(false);
    QString data_tepl_identification_parametr_tooltip = data_tepl_identification_parametr->text();
    data_tepl_identification_parametr->setToolTip(data_tepl_identification_parametr_tooltip);
    data_tepl_identification_value = new QStandardItem(tr("Выбрать режим"));
    QString data_tepl_identification_value_tooltip = data_tepl_identification_value->text();
    data_tepl_identification_value->setToolTip(data_tepl_identification_value_tooltip);
    sesion_name.append(data_tepl_identification_parametr);
    sesion_name.append(data_tepl_identification_value);
    save_data_parametr->appendRow(sesion_name);
    sesion_name.clear();

    data_vent_identification_parametr = new QStandardItem(tr("Данные вентиляционной идентификации"));
    data_vent_identification_parametr->setEditable(false);
    QString data_vent_identification_parametr_tooltip = data_vent_identification_parametr->text();
    data_vent_identification_parametr->setToolTip(data_vent_identification_parametr_tooltip);
    data_vent_identification_value = new QStandardItem(tr("Выбрать режим"));
    QString data_vent_identification_value_tooltip = data_vent_identification_value->text();
    data_vent_identification_value->setToolTip(data_vent_identification_value_tooltip);
    sesion_name.append(data_vent_identification_parametr);
    sesion_name.append(data_vent_identification_value);
    save_data_parametr->appendRow(sesion_name);
    sesion_name.clear();

    data_electomagn_process_parametr = new QStandardItem(tr("Данные электромагнитных процессов"));
    data_electomagn_process_parametr->setEditable(false);
    QString data_electomagn_process_parametr_tooltip = data_electomagn_process_parametr->text();
    data_electomagn_process_parametr->setToolTip(data_electomagn_process_parametr_tooltip);
    data_electomagn_process_value = new QStandardItem(tr("Выбрать режим"));
    QString data_electomagn_process_value_tooltip = data_electomagn_process_value->text();
    data_electomagn_process_value->setToolTip(data_electomagn_process_value_tooltip);
    sesion_name.append(data_electomagn_process_parametr);
    sesion_name.append(data_electomagn_process_value);
    save_data_parametr->appendRow(sesion_name);
    sesion_name.clear();

    data_tepl_process_parametr = new QStandardItem(tr("Данные тепловых процессов"));
    data_tepl_process_parametr->setEditable(false);
    QString data_tepl_process_parametr_tooltip = data_tepl_process_parametr->text();
    data_tepl_process_parametr->setToolTip(data_tepl_process_parametr_tooltip);
    data_tepl_process_value = new QStandardItem(tr("Выбрать режим"));
    QString data_tepl_process_value_tooltip = data_tepl_process_value->text();
    data_tepl_process_value->setToolTip(data_tepl_process_value_tooltip);
    sesion_name.append(data_tepl_process_parametr);
    sesion_name.append(data_tepl_process_value);
    save_data_parametr->appendRow(sesion_name);
    sesion_name.clear();

    data_vent_process_parametr = new QStandardItem(tr("Данные вентиляционных процессов"));
    data_vent_process_parametr->setEditable(false);
    QString data_vent_process_parametr_tooltip = data_vent_process_parametr->text();
    data_vent_process_parametr->setToolTip(data_vent_process_parametr_tooltip );
    data_vent_process_value = new QStandardItem(tr("Выбрать режим"));
    QString data_vent_process_value_tooltip = data_vent_process_value->text();
    data_vent_process_value->setToolTip(data_vent_process_value_tooltip );
    sesion_name.append(data_vent_process_parametr);
    sesion_name.append(data_vent_process_value);
    save_data_parametr->appendRow(sesion_name);
    sesion_name.clear();

    data_tepl_prognose_parametr = new QStandardItem(tr("Данные прогноза температур"));
    data_tepl_prognose_parametr->setEditable(false);
    QString data_tepl_prognose_parametr_tooltip = data_tepl_prognose_parametr->text();
    data_tepl_prognose_parametr->setToolTip(data_tepl_prognose_parametr_tooltip );
    data_tepl_prognose_value = new QStandardItem(tr("Выбрать режим"));
    QString data_tepl_prognose_value_tooltip = data_tepl_prognose_value->text();
    data_tepl_prognose_value->setToolTip(data_tepl_prognose_value_tooltip );
    sesion_name.append(data_tepl_prognose_parametr);
    sesion_name.append(data_tepl_prognose_value);
    save_data_parametr->appendRow(sesion_name);
    sesion_name.clear();

    data_ostat_tepl_resurs_parametr = new QStandardItem(tr("Данные остаточного теплового ресурса"));
    data_ostat_tepl_resurs_parametr->setEditable(false);
    QString data_ostat_tepl_resurs_parametr_tooltip = data_ostat_tepl_resurs_parametr->text();
    data_ostat_tepl_resurs_parametr->setToolTip(data_ostat_tepl_resurs_parametr_tooltip );
    data_ostat_tepl_resurs_value = new QStandardItem(tr("Выбрать режим"));
    QString data_ostat_tepl_resurs_value_tooltip = data_ostat_tepl_resurs_value->text();
    data_ostat_tepl_resurs_value->setToolTip(data_ostat_tepl_resurs_value_tooltip );
    sesion_name.append(data_ostat_tepl_resurs_parametr);
    sesion_name.append(data_ostat_tepl_resurs_value);
    save_data_parametr->appendRow(sesion_name);
    sesion_name.clear();

    /* секция "Идентификация параметров схемы замещения" */

    QList<QStandardItem*> identf_scheme_zam;
    identf_scheme_zam_parametr = new QStandardItem();
    identf_scheme_zam_parametr->setSelectable(false);
    identf_scheme_zam_parametr->setEditable(false);
    QString identf_scheme_zam_parametr_tooltip=identf_scheme_zam_parametr->text();
    identf_scheme_zam_parametr->setToolTip(identf_scheme_zam_parametr_tooltip);
    identf_scheme_zam_value = new QStandardItem();
    identf_scheme_zam_value->setSelectable(false);
    identf_scheme_zam_value->setEditable(false);
    QString identf_scheme_zam_value_tooltip=identf_scheme_zam_value->text();
    identf_scheme_zam_value->setToolTip(identf_scheme_zam_value_tooltip);
    identf_scheme_zam.append(identf_scheme_zam_parametr);
    identf_scheme_zam.append(identf_scheme_zam_value);
    model_treeView->appendRow(identf_scheme_zam);
    identf_scheme_zam.clear();

    QList<QStandardItem*> iteidentf_scheme_zamms4;
    calculation_mode_parametr = new QStandardItem(tr("Режим расчета"));
    calculation_mode_parametr->setEditable(false);
    QString calculation_mode_parametr_tooltip = calculation_mode_parametr->text();
    calculation_mode_parametr->setToolTip(calculation_mode_parametr_tooltip );
    calculation_mode_value = new QStandardItem(tr("Выберите режим"));
    QString calculation_mode_value_tooltip = calculation_mode_value->text();
    calculation_mode_value->setToolTip(calculation_mode_value_tooltip);
    iteidentf_scheme_zamms4.append(calculation_mode_parametr);
    iteidentf_scheme_zamms4.append(calculation_mode_value);
    identf_scheme_zam_parametr->appendRow(iteidentf_scheme_zamms4);
    iteidentf_scheme_zamms4.clear();

    tuning_coefficient_gd_parametr = new QStandardItem(tr("Настроечный коэффициент gd="));
    tuning_coefficient_gd_parametr->setEditable(false);
    tuning_coefficient_gd_parametr->setEnabled(false);
    QString tuning_coefficient_gd_parametr_tooltip = tuning_coefficient_gd_parametr->text();
    tuning_coefficient_gd_parametr->setToolTip(tuning_coefficient_gd_parametr_tooltip);
    tuning_coefficient_gd_value = new QStandardItem(tr("0"));
    tuning_coefficient_gd_value->setEnabled(false);
    tuning_coefficient_gd_value->setCheckable(false);
    QString tuning_coefficient_gd_value_tooltip = tuning_coefficient_gd_value->text();
    tuning_coefficient_gd_value->setToolTip(tuning_coefficient_gd_value_tooltip);
    iteidentf_scheme_zamms4.append(tuning_coefficient_gd_parametr);
    iteidentf_scheme_zamms4.append(tuning_coefficient_gd_value);
    identf_scheme_zam_parametr->appendRow(iteidentf_scheme_zamms4);
    iteidentf_scheme_zamms4.clear();

    tuning_coefficient_ki_parametr = new QStandardItem(tr("Настроечный коэффициент ki="));
    tuning_coefficient_ki_parametr->setEditable(false);
    tuning_coefficient_ki_parametr->setEnabled(false);
    QString tuning_coefficient_ki_parametr_tooltip = tuning_coefficient_ki_parametr->text();
    tuning_coefficient_ki_parametr->setToolTip(tuning_coefficient_ki_parametr_tooltip);
    tuning_coefficient_ki_value = new QStandardItem(tr("0"));
    tuning_coefficient_ki_value->setEnabled(false);
    tuning_coefficient_ki_value->setCheckable(false);
    QString uning_coefficient_ki_value_tooltip = tuning_coefficient_ki_value->text();
    tuning_coefficient_ki_value->setToolTip(uning_coefficient_ki_value_tooltip);
    iteidentf_scheme_zamms4.append(tuning_coefficient_ki_parametr);
    iteidentf_scheme_zamms4.append(tuning_coefficient_ki_value);
    identf_scheme_zam_parametr->appendRow(iteidentf_scheme_zamms4);
    iteidentf_scheme_zamms4.clear();

    tuning_coefficient_gb_parametr = new QStandardItem(tr("Настроечный коэффициент gb="));
    tuning_coefficient_gb_parametr->setEditable(false);
    tuning_coefficient_gb_parametr->setEnabled(false);
    QString tuning_coefficient_gb_parametr_tooltip = tuning_coefficient_gb_parametr->text();
    tuning_coefficient_gb_parametr->setToolTip(tuning_coefficient_gb_parametr_tooltip);
    tuning_coefficient_gb_value = new QStandardItem(tr("0"));
    tuning_coefficient_gb_value->setEnabled(false);
    tuning_coefficient_gb_value->setCheckable(false);
    QString tuning_coefficient_gb_value_tooltip = tuning_coefficient_gb_value->text();
    tuning_coefficient_gb_value->setToolTip(tuning_coefficient_gb_value_tooltip);
    iteidentf_scheme_zamms4.append(tuning_coefficient_gb_parametr);
    iteidentf_scheme_zamms4.append(tuning_coefficient_gb_value);
    identf_scheme_zam_parametr->appendRow(iteidentf_scheme_zamms4);
    iteidentf_scheme_zamms4.clear();

    tuning_coefficient_kpsi_parametr = new QStandardItem(tr("Настроечный коэффициент kpsi="));
    tuning_coefficient_kpsi_parametr->setEditable(false);
    tuning_coefficient_kpsi_parametr->setEnabled(false);
    QString tuning_coefficient_kpsi_parametr_tooltip = tuning_coefficient_kpsi_parametr->text();
    tuning_coefficient_kpsi_parametr->setToolTip(tuning_coefficient_kpsi_parametr_tooltip);
    tuning_coefficient_kpsi_value = new QStandardItem(tr("0"));
    tuning_coefficient_kpsi_value->setEnabled(false);
    tuning_coefficient_kpsi_value->setCheckable(false);
    QString tuning_coefficient_kpsi_value_tooltip = tuning_coefficient_kpsi_value->text();
    tuning_coefficient_kpsi_value->setToolTip(tuning_coefficient_kpsi_value_tooltip);
    iteidentf_scheme_zamms4.append(tuning_coefficient_kpsi_parametr);
    iteidentf_scheme_zamms4.append(tuning_coefficient_kpsi_value);
    identf_scheme_zam_parametr->appendRow(iteidentf_scheme_zamms4);
    iteidentf_scheme_zamms4.clear();

    tuning_coefficient_gp_parametr = new QStandardItem(tr("Настроечный коэффициент gp="));
    tuning_coefficient_gp_parametr->setEditable(false);
    tuning_coefficient_gp_parametr->setEnabled(false);
    QString tuning_coefficient_gp_parametr_tooltip = tuning_coefficient_gp_parametr->text();
    tuning_coefficient_gp_parametr->setToolTip(tuning_coefficient_gp_parametr_tooltip );
    tuning_coefficient_gp_value = new QStandardItem(tr("0"));
    tuning_coefficient_gp_value->setEnabled(false);
    tuning_coefficient_gp_value->setCheckable(false);
    QString tuning_coefficient_gp_value_tooltip = tuning_coefficient_gp_value->text();
    tuning_coefficient_gp_value->setToolTip(tuning_coefficient_gp_value_tooltip);
    iteidentf_scheme_zamms4.append(tuning_coefficient_gp_parametr);
    iteidentf_scheme_zamms4.append(tuning_coefficient_gp_value);
    identf_scheme_zam_parametr->appendRow(iteidentf_scheme_zamms4);
    iteidentf_scheme_zamms4.clear();

    tuning_coefficient_gpsi_parametr = new QStandardItem(tr("Настроечный коэффициент gpsi="));
    tuning_coefficient_gpsi_parametr->setEditable(false);
    tuning_coefficient_gpsi_parametr->setEnabled(false);
    QString tuning_coefficient_gpsi_parametr_tooltip = tuning_coefficient_gpsi_parametr->text();
    tuning_coefficient_gpsi_parametr->setToolTip(tuning_coefficient_gpsi_parametr_tooltip);
    tuning_coefficient_gpsi_value = new QStandardItem(tr("0"));
    tuning_coefficient_gpsi_value->setEnabled(false);
    tuning_coefficient_gpsi_value->setCheckable(false);
    QString tuning_coefficient_gpsi_value_tooltip = tuning_coefficient_gpsi_value->text();
    tuning_coefficient_gpsi_value->setToolTip(tuning_coefficient_gpsi_value_tooltip);
    iteidentf_scheme_zamms4.append(tuning_coefficient_gpsi_parametr);
    iteidentf_scheme_zamms4.append(tuning_coefficient_gpsi_value);
    identf_scheme_zam_parametr->appendRow(iteidentf_scheme_zamms4);
    iteidentf_scheme_zamms4.clear();

    /* секция "Тепловая идентификация" */

    QList<QStandardItem*> thermal_identification;
    thermal_identification_parametr = new QStandardItem();
    thermal_identification_parametr->setSelectable(false);
    thermal_identification_parametr->setEditable(false);
    QString  thermal_identification_parametr_tooltip = thermal_identification_parametr->text();
    thermal_identification_parametr->setToolTip( thermal_identification_parametr_tooltip);
    thermal_identification_value = new QStandardItem();
    thermal_identification_value->setSelectable(false);
    thermal_identification_value->setEditable(false);
    thermal_identification.append(thermal_identification_parametr);
    thermal_identification.append(thermal_identification_value);
    model_treeView->appendRow(thermal_identification);
    thermal_identification.clear();

    kind_thermal_model_parametr = new QStandardItem(tr("Тип тепловой модели"));
    kind_thermal_model_parametr->setEditable(false);
    QString kind_thermal_model_parametr_tooltip = kind_thermal_model_parametr->text();
    kind_thermal_model_parametr->setToolTip(kind_thermal_model_parametr_tooltip);
    kind_thermal_model_value = new QStandardItem(tr("Выберите тип"));
    QString kind_thermal_model_value_tooltip = kind_thermal_model_value->text();
    kind_thermal_model_value->setToolTip(kind_thermal_model_value_tooltip);
    thermal_identification.append(kind_thermal_model_parametr);
    thermal_identification.append(kind_thermal_model_value);
    thermal_identification_parametr->appendRow(thermal_identification);
    thermal_identification.clear();

    kind_thermal_model_2_parametr = new QStandardItem(tr("Вид тепловой идентификации"));
    kind_thermal_model_2_parametr->setEditable(false);
    QString kind_thermal_model_2_parametr_tooltip = kind_thermal_model_2_parametr->text();
    kind_thermal_model_2_parametr->setToolTip(kind_thermal_model_2_parametr_tooltip);
    kind_thermal_model_2_value = new QStandardItem(tr("Выберите вид"));
    QString kind_thermal_model_2_value_tooltip = kind_thermal_model_2_value->text();
    kind_thermal_model_2_value->setToolTip(kind_thermal_model_2_value_tooltip);
    thermal_identification.append(kind_thermal_model_2_parametr);
    thermal_identification.append(kind_thermal_model_2_value);
    thermal_identification_parametr->appendRow(thermal_identification);
    thermal_identification.clear();

    kind_thermal_model_4_parametr = new QStandardItem(tr("Необходимость учета вентиляции"));
    kind_thermal_model_4_parametr->setEditable(false);
    QString kind_thermal_model_4_parametr_tooltip = kind_thermal_model_4_parametr->text();
    kind_thermal_model_4_parametr->setToolTip(kind_thermal_model_4_parametr_tooltip);
    kind_thermal_model_4_value = new QStandardItem(tr("Выберите параметр"));
    QString kind_thermal_model_4_value_tooltip = kind_thermal_model_4_value->text();
    kind_thermal_model_4_value->setToolTip(kind_thermal_model_4_value_tooltip);
    thermal_identification.append(kind_thermal_model_4_parametr);
    thermal_identification.append(kind_thermal_model_4_value);
    thermal_identification_parametr->appendRow(thermal_identification);
    thermal_identification.clear();

    /* секция "Вентиляционная идентификация" */

    QList<QStandardItem*> iteventilation_identificationms18;
    ventilation_identification_parametr = new QStandardItem();
    ventilation_identification_parametr->setSelectable(false);
    ventilation_identification_parametr->setEditable(false);
    QString ventilation_identification_parametr_tooltip = ventilation_identification_parametr->text();
    ventilation_identification_parametr->setToolTip(ventilation_identification_parametr_tooltip);
    ventilation_identification_value = new QStandardItem();
    ventilation_identification_value->setSelectable(false);
    ventilation_identification_value->setEditable(false);
    iteventilation_identificationms18.append(ventilation_identification_parametr);
    iteventilation_identificationms18.append(ventilation_identification_value);
    model_treeView->appendRow(iteventilation_identificationms18);
    iteventilation_identificationms18.clear();

    kind_ventilation_parametr = new QStandardItem(tr("Вид вентиляции"));
    kind_ventilation_parametr->setEditable(false);
    QString kind_ventilation_parametr_tooltip = kind_ventilation_parametr->text();
    kind_ventilation_parametr->setToolTip(kind_ventilation_parametr_tooltip);
    kind_ventilation_value = new QStandardItem(tr("Выберите вид"));
    QString kind_ventilation_value_tooltip = kind_ventilation_value->text();
    kind_ventilation_value->setToolTip(kind_ventilation_value_tooltip);
    iteventilation_identificationms18.append(kind_ventilation_parametr);
    iteventilation_identificationms18.append(kind_ventilation_value);
    ventilation_identification_parametr->appendRow(iteventilation_identificationms18);
    iteventilation_identificationms18.clear();

    calculation_modes_parametr = new QStandardItem(tr("Режим расчета"));
    calculation_modes_parametr->setEditable(false);
    QString calculation_modes_parametr_tooltip = kind_ventilation_parametr->text();
    calculation_modes_parametr->setToolTip(calculation_modes_parametr_tooltip);
    calculation_modes_value = new QStandardItem(tr("Выберите вид"));
    QString calculation_modes_value_tooltip = kind_ventilation_value->text();
    calculation_modes_value->setToolTip(calculation_modes_value_tooltip);
    iteventilation_identificationms18.append(calculation_modes_parametr);
    iteventilation_identificationms18.append(calculation_modes_value);
    ventilation_identification_parametr->appendRow(iteventilation_identificationms18);
    iteventilation_identificationms18.clear();

    geometry_parameters_parametr = new QStandardItem(tr("Геометрические параметры"));
    geometry_parameters_parametr->setEditable(false);
    geometry_parameters_parametr->setEnabled(false);
    QString geometry_parameters_parametr_tooltip = geometry_parameters_parametr->text();
    geometry_parameters_parametr->setToolTip(geometry_parameters_parametr_tooltip);
    geometry_parameters_value = new QStandardItem(tr("Введите данные"));
    geometry_parameters_value->setEnabled(false);
    QString geometry_parameters_value_tooltip = geometry_parameters_value->text();
    geometry_parameters_value->setToolTip(geometry_parameters_value_tooltip);
    iteventilation_identificationms18.append(geometry_parameters_parametr);
    iteventilation_identificationms18.append(geometry_parameters_value);
    ventilation_identification_parametr->appendRow(iteventilation_identificationms18);
    iteventilation_identificationms18.clear();

    Heat_processes_accounting_parameter = new QStandardItem(tr("Учет тепловых процессов"));
    Heat_processes_accounting_parameter->setEditable(false);
    QString Heat_processes_accounting_parameter_tooltip = Heat_processes_accounting_parameter->text();
    Heat_processes_accounting_parameter->setToolTip(Heat_processes_accounting_parameter_tooltip );
    Heat_processes_accounting_value = new QStandardItem(tr("Введите данные"));
    QString Heat_processes_accounting_value_tooltip = Heat_processes_accounting_value->text();
    Heat_processes_accounting_value->setToolTip(Heat_processes_accounting_value_tooltip);
    iteventilation_identificationms18.append(Heat_processes_accounting_parameter);
    iteventilation_identificationms18.append(Heat_processes_accounting_value);
    ventilation_identification_parametr->appendRow(iteventilation_identificationms18);
    iteventilation_identificationms18.clear();

    data_approximation_mode_parameter = new QStandardItem(tr("Режим аппроксимации данных"));
    data_approximation_mode_parameter->setEditable(false);
    QString data_approximation_mode_parameter_tooltip = data_approximation_mode_parameter->text();
    data_approximation_mode_parameter->setToolTip(data_approximation_mode_parameter_tooltip);
    data_approximation_mode_value = new QStandardItem(tr("Автоматический"));
    QString data_approximation_mode_value_tooltip = data_approximation_mode_value->text();
    data_approximation_mode_value->setToolTip(data_approximation_mode_value_tooltip);
    iteventilation_identificationms18.append(data_approximation_mode_parameter);
    iteventilation_identificationms18.append(data_approximation_mode_value);
    ventilation_identification_parametr->appendRow(iteventilation_identificationms18);
    iteventilation_identificationms18.clear();

    degree_approximating_polynomial_parameter = new QStandardItem(tr("Степень полинома аппроксимации"));
    degree_approximating_polynomial_parameter->setEditable(false);
    degree_approximating_polynomial_parameter->setEnabled(false);
    QString degree_approximating_polynomial_parameter_tooltip = degree_approximating_polynomial_parameter->text();
    degree_approximating_polynomial_parameter->setToolTip(degree_approximating_polynomial_parameter_tooltip);
    degree_approximating_polynomial_value = new QStandardItem(tr("Введите данные"));
    degree_approximating_polynomial_value->setEnabled(false);
    QString degree_approximating_polynomial_value_tooltip = degree_approximating_polynomial_value->text();
    degree_approximating_polynomial_value->setToolTip(degree_approximating_polynomial_value_tooltip);
    iteventilation_identificationms18.append(degree_approximating_polynomial_parameter);
    iteventilation_identificationms18.append(degree_approximating_polynomial_value);
    ventilation_identification_parametr->appendRow(iteventilation_identificationms18);
    iteventilation_identificationms18.clear();

    /* секция "Электромагнитная модель" */

    QList<QStandardItem*> electromagnetic_model;
    electromagnetic_model_parametr = new QStandardItem();
    electromagnetic_model_parametr->setSelectable(false);
    electromagnetic_model_parametr->setEditable(false);
    QString electromagnetic_model_parametr_tooltip=electromagnetic_model_parametr->text();
    electromagnetic_model_parametr->setToolTip(electromagnetic_model_parametr_tooltip);
    electromagnetic_model_value = new QStandardItem();
    electromagnetic_model_value->setSelectable(false);
    electromagnetic_model_value->setEditable(false);
    electromagnetic_model.append(electromagnetic_model_parametr);
    electromagnetic_model.append(electromagnetic_model_value);
    model_treeView->appendRow(electromagnetic_model);
    electromagnetic_model.clear();

    QList<QStandardItem*> engine_duty_cycle;
    engine_duty_cycle_parametr = new QStandardItem(tr("Pежим работы двигателя"));
    engine_duty_cycle_parametr->setEditable(false);
    QString engine_duty_cycle_parametr_tooltip = engine_duty_cycle_parametr->text();
    engine_duty_cycle_parametr->setToolTip(engine_duty_cycle_parametr_tooltip );
    engine_duty_cycle_value = new QStandardItem(tr("Выбрать режим"));
    QString engine_duty_cycle_value_tooltip = engine_duty_cycle_value->text();
    engine_duty_cycle_value->setToolTip(engine_duty_cycle_value_tooltip);
    engine_duty_cycle.append(engine_duty_cycle_parametr);
    engine_duty_cycle.append(engine_duty_cycle_value);
    electromagnetic_model_parametr->appendRow(engine_duty_cycle);
    engine_duty_cycle.clear();

    time_cycle_parametr = new QStandardItem(tr("Время цикла, с:"));
    time_cycle_parametr->setEditable(false);
    time_cycle_parametr->setEnabled(false);
    QString time_cycle_parametr_tooltip = time_cycle_parametr->text();
    time_cycle_parametr->setToolTip(time_cycle_parametr_tooltip);
    time_cycle_value = new QStandardItem(tr("0"));
    time_cycle_value->setEnabled(false);
    QString time_cycle_value_tooltip = time_cycle_value->text();
    time_cycle_value->setToolTip(time_cycle_value_tooltip);
    engine_duty_cycle.append(time_cycle_parametr);
    engine_duty_cycle.append(time_cycle_value);
    electromagnetic_model_parametr->appendRow(engine_duty_cycle);
    engine_duty_cycle.clear();

    time_work_in_cycle_parametr = new QStandardItem(tr("Время работы в цикле, с:"));
    time_work_in_cycle_parametr->setEditable(false);
    time_work_in_cycle_parametr->setEnabled(false);
    QString time_work_in_cycle_parametr_tooltip = time_work_in_cycle_parametr->text();
    time_work_in_cycle_parametr->setToolTip(time_work_in_cycle_parametr_tooltip );
    time_work_in_cycle_value = new QStandardItem(tr("0"));
    time_work_in_cycle_value->setEnabled(false);
    QString time_work_in_cycle_value_tooltip = time_work_in_cycle_value->text();
    time_work_in_cycle_value->setToolTip(time_work_in_cycle_value_tooltip);
    engine_duty_cycle.append(time_work_in_cycle_parametr);
    engine_duty_cycle.append(time_work_in_cycle_value);
    electromagnetic_model_parametr->appendRow(engine_duty_cycle);
    engine_duty_cycle.clear();

    time_start_in_cycle_parametr = new QStandardItem(tr("Время пуска в цикле, с:"));
    time_start_in_cycle_parametr->setEditable(false);
    time_start_in_cycle_parametr->setEnabled(false);
    QString time_start_in_cycle_parametr_tooltip = time_start_in_cycle_parametr->text();
    time_start_in_cycle_parametr->setToolTip(time_start_in_cycle_parametr_tooltip);
    time_start_in_cycle_value = new QStandardItem(tr("0"));
    time_start_in_cycle_value->setEnabled(false);
    QString time_start_in_cycle_value_tooltip = time_start_in_cycle_value->text();
    time_start_in_cycle_value->setToolTip(time_start_in_cycle_value_tooltip);
    engine_duty_cycle.append(time_start_in_cycle_parametr);
    engine_duty_cycle.append(time_start_in_cycle_value);
    electromagnetic_model_parametr->appendRow(engine_duty_cycle);
    engine_duty_cycle.clear();

    time_base_selection_parametr = new QStandardItem(tr("Выбор системы отсчета времени"));
    time_base_selection_parametr->setEditable(false);
    QString time_base_selection_parametr_tooltip = time_base_selection_parametr->text();
    time_base_selection_parametr->setToolTip(time_base_selection_parametr_tooltip );
    time_base_selection_value = new QStandardItem(tr("Выберите тип отсчета"));
    QString time_base_selection_value_tooltip = time_base_selection_value->text();
    time_base_selection_value->setToolTip(time_base_selection_value_tooltip);
    engine_duty_cycle.append(time_base_selection_parametr);
    engine_duty_cycle.append(time_base_selection_value);
    electromagnetic_model_parametr->appendRow(engine_duty_cycle);
    engine_duty_cycle.clear();

    time_work_parametr = new QStandardItem(tr("Время работы, с:"));
    time_work_parametr->setEditable(false);
    time_work_parametr->setEnabled(false);
    QString time_work_parametr_tooltip = time_work_parametr->text();
    time_work_parametr->setToolTip(time_work_parametr_tooltip);
    time_work_value = new QStandardItem(tr("0"));
    time_work_value->setEnabled(false);
    QString time_work_value_tooltip = time_work_value->text();
    time_work_value->setToolTip(time_work_value_tooltip);
    engine_duty_cycle.append(time_work_parametr);
    engine_duty_cycle.append(time_work_value);
    electromagnetic_model_parametr->appendRow(engine_duty_cycle);
    engine_duty_cycle.clear();

    switch_system_electrodrive_parametr = new QStandardItem(tr("Выбор системы электропривода"));
    switch_system_electrodrive_parametr->setEditable(false);
    QString switch_system_electrodrive_parametr_tooltip=switch_system_electrodrive_parametr->text();
    switch_system_electrodrive_parametr->setToolTip(switch_system_electrodrive_parametr_tooltip);
    switch_system_electrodrive_value = new QStandardItem(tr("Выбрать режим"));
    QString switch_system_electrodrive_value_tooltip=switch_system_electrodrive_value->text();
    switch_system_electrodrive_value->setToolTip(switch_system_electrodrive_value_tooltip);
    engine_duty_cycle.append(switch_system_electrodrive_parametr);
    engine_duty_cycle.append(switch_system_electrodrive_value);
    electromagnetic_model_parametr->appendRow(engine_duty_cycle);
    engine_duty_cycle.clear();

    creating_motor_voltage_change_chart_parametr = new QStandardItem(tr("Уровень напряжения питания"));
    creating_motor_voltage_change_chart_parametr->setEditable(false);
    QString creating_motor_voltage_change_chart_parametr_tooltip = creating_motor_voltage_change_chart_parametr->text();
    creating_motor_voltage_change_chart_parametr->setToolTip(creating_motor_voltage_change_chart_parametr_tooltip );
    creating_motor_voltage_change_chart_value = new QStandardItem(tr("Выберите режим"));
    QString creating_motor_voltage_change_chart_tooltip = creating_motor_voltage_change_chart_value->text();
    creating_motor_voltage_change_chart_value->setToolTip(creating_motor_voltage_change_chart_tooltip);
    engine_duty_cycle.append(creating_motor_voltage_change_chart_parametr);
    engine_duty_cycle.append(creating_motor_voltage_change_chart_value);
    electromagnetic_model_parametr->appendRow(engine_duty_cycle);
    engine_duty_cycle.clear();

    enter_voltage_im_mashine_parametr = new QStandardItem(tr("Ввод напряжения питания двигателя"));
    enter_voltage_im_mashine_parametr->setEditable(false);
    enter_voltage_im_mashine_parametr->setEnabled(false);
    QString enter_voltage_im_mashine_parametr_tooltip = enter_voltage_im_mashine_parametr->text();
    enter_voltage_im_mashine_parametr->setToolTip(enter_voltage_im_mashine_parametr_tooltip );
    enter_voltage_im_mashine_value = new QStandardItem(tr("0"));
    //enter_voltage_im_mashine_value->setEditable(false);
    enter_voltage_im_mashine_value->setEnabled(false);
    QString enter_voltage_im_mashine_value_tooltip = enter_voltage_im_mashine_value->text();
    enter_voltage_im_mashine_value->setToolTip(enter_voltage_im_mashine_value_tooltip);
    engine_duty_cycle.append(enter_voltage_im_mashine_parametr);
    engine_duty_cycle.append(enter_voltage_im_mashine_value);
    electromagnetic_model_parametr->appendRow(engine_duty_cycle);
    engine_duty_cycle.clear();

    creating_motor_speed_change_chart_parametr = new QStandardItem(tr("Создание диаграммы изменения скорости вращения двигателя"));
    creating_motor_speed_change_chart_parametr->setEditable(false);
    creating_motor_speed_change_chart_parametr->setEnabled(false);
    QString creating_motor_speed_change_chart_parametr_tooltip = creating_motor_speed_change_chart_parametr->text();
    creating_motor_speed_change_chart_parametr->setToolTip(creating_motor_speed_change_chart_parametr_tooltip );
    creating_motor_speed_change_chart_value = new QStandardItem(tr("Нажмите на кнопку"));
    //creating_motor_speed_change_chart_value->setEditable(false);
    creating_motor_speed_change_chart_value->setEnabled(false);
    QString creating_motor_speed_change_chart_value_tooltip = creating_motor_speed_change_chart_value->text();
    creating_motor_speed_change_chart_value->setToolTip(creating_motor_speed_change_chart_value_tooltip);
    engine_duty_cycle.append(creating_motor_speed_change_chart_parametr);
    engine_duty_cycle.append(creating_motor_speed_change_chart_value);
    electromagnetic_model_parametr->appendRow(engine_duty_cycle);
    engine_duty_cycle.clear();

    enter_moment_parametr = new QStandardItem(tr("Ввод значение момента нагрузки"));
    enter_moment_parametr->setEditable(false);
    QString enter_moment_parametr_tooltip = enter_moment_parametr->text();
    enter_moment_parametr->setToolTip(enter_moment_parametr_tooltip );
    enter_moment_value = new QStandardItem(tr("0"));
    QString enter_moment_value_tooltip = enter_moment_value->text();
    enter_moment_value->setToolTip(enter_moment_value_tooltip);
    engine_duty_cycle.append(enter_moment_parametr);
    engine_duty_cycle.append( enter_moment_value);
    electromagnetic_model_parametr->appendRow(engine_duty_cycle);
    engine_duty_cycle.clear();

    /* секция "Тепловая модель" */

    QList<QStandardItem*> tepl_model;
    tepl_model_parametr = new QStandardItem();
    tepl_model_parametr->setSelectable(false);
    tepl_model_parametr->setEditable(false);
    QString tepl_model_parametr_tooltip = tepl_model_parametr->text();
    tepl_model_parametr->setToolTip(tepl_model_parametr_tooltip);
    tepl_model_value = new QStandardItem();
    tepl_model_value->setSelectable(false);
    tepl_model_value->setEditable(false);
    tepl_model.append(tepl_model_parametr);
    tepl_model.append(tepl_model_value);
    model_treeView->appendRow(tepl_model);
    tepl_model.clear();

    QList<QStandardItem*> start_tepl_temperature;
    start_tepl_temperature_parametr = new QStandardItem(tr("Начальное значение температуры, °C"));
    start_tepl_temperature_parametr->setEditable(false);
    QString start_tepl_temperature_parametr_tooltip = start_tepl_temperature_parametr->text();
    start_tepl_temperature_parametr->setToolTip(start_tepl_temperature_parametr_tooltip);
    start_tepl_temperature_value = new QStandardItem(tr("0"));
    QString start_tepl_temperature_value_tooltip = start_tepl_temperature_value->text();
    start_tepl_temperature_value->setToolTip(start_tepl_temperature_value_tooltip);
    start_tepl_temperature.append(start_tepl_temperature_parametr);
    start_tepl_temperature.append(start_tepl_temperature_value);
    tepl_model_parametr->appendRow(start_tepl_temperature);
    start_tepl_temperature.clear();

    temperature_regime_parametr = new QStandardItem(tr("Температурный режим"));
    temperature_regime_parametr->setEditable(false);
    QString temperature_regime_parametr_tooltip = temperature_regime_parametr->text();
    temperature_regime_parametr->setToolTip(temperature_regime_parametr_tooltip);
    temperature_regime_value = new QStandardItem(tr("Выберите режим"));
    QString temperature_regime_value_tooltip = temperature_regime_value->text();
    temperature_regime_value->setToolTip(temperature_regime_value_tooltip);
    start_tepl_temperature.append(temperature_regime_parametr);
    start_tepl_temperature.append(temperature_regime_value);
    tepl_model_parametr->appendRow(start_tepl_temperature);
    start_tepl_temperature.clear();

    temperature_regime_static_parametr = new QStandardItem(tr("Температурный режим Статика"));
    temperature_regime_static_parametr->setEditable(false);
    QString temperature_regime_static_parametr_tooltip = temperature_regime_static_parametr->text();
    temperature_regime_static_parametr->setToolTip(temperature_regime_static_parametr_tooltip);
    temperature_regime_static_value = new QStandardItem(tr("Выберите режим"));
    QString temperature_regime_static_value_tooltip = temperature_regime_static_value->text();
    temperature_regime_static_value->setToolTip(temperature_regime_static_value_tooltip);
    start_tepl_temperature.append(temperature_regime_static_parametr);
    start_tepl_temperature.append(temperature_regime_static_value);
    tepl_model_parametr->appendRow(start_tepl_temperature);
    start_tepl_temperature.clear();

    temperature_regime_dinamic_parametr = new QStandardItem(tr("Температурный режим Динамика"));
    temperature_regime_dinamic_parametr->setEditable(false);
    QString temperature_regime_dinamic_parametr_tooltip = temperature_regime_dinamic_parametr->text();
    temperature_regime_dinamic_parametr->setToolTip(temperature_regime_dinamic_parametr_tooltip);
    temperature_regime_dinamic_value = new QStandardItem(tr("Выберите режим"));
    QString temperature_regime_dinamic_value_tooltip = temperature_regime_dinamic_value->text();
    temperature_regime_dinamic_parametr->setToolTip(temperature_regime_dinamic_value_tooltip);
    start_tepl_temperature.append(temperature_regime_dinamic_parametr);
    start_tepl_temperature.append(temperature_regime_dinamic_value);
    tepl_model_parametr->appendRow(start_tepl_temperature);
    start_tepl_temperature.clear();

    point_selection_step_parametr = new QStandardItem(tr("Шаг выбора точек"));
    point_selection_step_parametr->setEditable(false);
    QString time_base_selection_parameter_tooltip = time_base_selection_parametr->text();
    point_selection_step_parametr->setToolTip(time_base_selection_parameter_tooltip);
    point_selection_step_value = new QStandardItem(tr("0"));
    QString time_base_selection_valuex_tooltip = point_selection_step_value->text();
    point_selection_step_value->setToolTip(time_base_selection_valuex_tooltip);
    start_tepl_temperature.append(point_selection_step_parametr);
    start_tepl_temperature.append(point_selection_step_value);
    tepl_model_parametr->appendRow(start_tepl_temperature);
    start_tepl_temperature.clear();

    /* секция "Вентиляционная модель" */

    QList<QStandardItem*> ventilation_model;
    ventilation_model_parametr = new QStandardItem();
    ventilation_model_parametr->setSelectable(false);
    ventilation_model_parametr->setEditable(false);
    ventilation_model_value = new QStandardItem();
    ventilation_model_value->setSelectable(false);
    ventilation_model_value->setEditable(false);
    ventilation_model.append(ventilation_model_parametr);
    ventilation_model.append(ventilation_model_value);
    model_treeView->appendRow(ventilation_model);
    ventilation_model.clear();

    QList<QStandardItem*> ventilation_regime;
    ventilation_regime_parametr = new QStandardItem(tr("Вентиляционный режим"));
    ventilation_regime_parametr->setEditable(false);
    QString ventilation_regime_parameter_tooltip = ventilation_regime_parametr->text();
    ventilation_regime_parametr->setToolTip(ventilation_regime_parameter_tooltip);
    ventilation_regime_value = new QStandardItem(tr("Выберите режим"));
    QString ventilation_regime_value_tooltip = ventilation_regime_value->text();
    ventilation_regime_value->setToolTip(ventilation_regime_value_tooltip);
    ventilation_regime.append(ventilation_regime_parametr);
    ventilation_regime.append(ventilation_regime_value);
    ventilation_model_parametr->appendRow(ventilation_regime);
    ventilation_regime.clear();

    design_ventilation_system_parametr = new QStandardItem(tr("Конструкция вентиляционной системы электродвигателя"));
    design_ventilation_system_parametr->setEditable(false);
    QString design_ventilation_system_parametr_tooltip = design_ventilation_system_parametr->text();
    design_ventilation_system_parametr->setToolTip(design_ventilation_system_parametr_tooltip);
    design_ventilation_system_value = new QStandardItem(QString ("Выберите конструкцию"));
    QString design_ventilation_system_value_tooltip = design_ventilation_system_value->text();
    design_ventilation_system_value->setToolTip(design_ventilation_system_value_tooltip);
    ventilation_regime.append(design_ventilation_system_parametr);
    ventilation_regime.append(design_ventilation_system_value);
    ventilation_model_parametr->appendRow(ventilation_regime);
    ventilation_regime.clear();

    barometric_pressure_parametr = new QStandardItem(tr("Барометрическое давление, Па"));
    barometric_pressure_parametr->setEditable(false);
    QString barometric_pressure_parametr_tooltip = barometric_pressure_parametr->text();
    barometric_pressure_parametr->setToolTip(barometric_pressure_parametr_tooltip);
    barometric_pressure_value = new QStandardItem(tr("0"));
    QString barometric_pressure_value_tooltip = barometric_pressure_value->text();
    barometric_pressure_value->setToolTip(barometric_pressure_value_tooltip);
    ventilation_regime.append(barometric_pressure_parametr);
    ventilation_regime.append(barometric_pressure_value);
    ventilation_model_parametr->appendRow(ventilation_regime);
    ventilation_regime.clear();

    /* секция "Прогнозирование температур" */

    QList<QStandardItem*> predicting_temperature;
    predicting_temperature_parametr = new QStandardItem();
    predicting_temperature_parametr->setSelectable(false);
    predicting_temperature_parametr->setEditable(false);
    predicting_temperature_value = new QStandardItem();
    predicting_temperature_value->setSelectable(false);
    predicting_temperature_value->setEditable(false);
    predicting_temperature.append(predicting_temperature_parametr);
    predicting_temperature.append(predicting_temperature_value);
    model_treeView->appendRow(predicting_temperature);
    predicting_temperature.clear();

    QList<QStandardItem*> value_one;
    value_one_parametr = new QStandardItem(tr("Условие 13"));
    value_one_parametr->setEditable(false);
    QString value_one_parametr_tooltip = value_one_parametr->text();
    value_one_parametr->setToolTip(value_one_parametr_tooltip);
    value_one_value = new QStandardItem(tr("Значение 13"));
    QString  value_one_value_tooltip =  value_one_value->text();
    value_one_value->setToolTip( value_one_value_tooltip);
    value_one.append(value_one_parametr);
    value_one.append(value_one_value);
    predicting_temperature_parametr->appendRow(value_one);
    value_one.clear();

    value_two_parametr = new QStandardItem(tr("Условие 14"));
    value_two_parametr->setEditable(false);
    QString value_two_parametr_tooltip = value_two_parametr->text();
    value_two_parametr->setToolTip(value_two_parametr_tooltip);
    value_two_value = new QStandardItem(tr("Значение 14"));
    QString  value_two_value_tooltip =  value_two_value->text();
    value_two_value->setToolTip( value_two_value_tooltip);
    value_one.append(value_two_parametr);
    value_one.append(value_two_value);
    predicting_temperature_parametr->appendRow(value_one);
    value_one.clear();

    value_three_parametr = new QStandardItem(tr("Условие 15"));
    QString value_three_parametr_tooltip = value_three_parametr->text();
    value_three_parametr->setToolTip(value_three_parametr_tooltip);
    value_three_parametr->setEditable(false);
    value_three_value = new QStandardItem(tr("Значение 15"));
    QString value_three_value_tooltip = value_three_value->text();
    value_three_value->setToolTip(value_three_value_tooltip);
    value_one.append(value_three_parametr);
    value_one.append(value_three_value);
    predicting_temperature_parametr->appendRow(value_one);
    value_one.clear();

    /* секция "Оценка остаточного теплового ресурса" */

    QList<QStandardItem*> estimation_residual_thermal_life;
    estimation_residual_thermal_life_parametr = new QStandardItem();
    estimation_residual_thermal_life_parametr->setSelectable(false);
    estimation_residual_thermal_life_parametr->setEditable(false);
    estimation_residual_thermal_life_value = new QStandardItem();
    estimation_residual_thermal_life_value->setSelectable(false);
    estimation_residual_thermal_life_value->setEditable(false);
    estimation_residual_thermal_life.append(estimation_residual_thermal_life_parametr);
    estimation_residual_thermal_life.append(estimation_residual_thermal_life_value);
    model_treeView->appendRow(estimation_residual_thermal_life);
    estimation_residual_thermal_life.clear();

    QList<QStandardItem*> value_four;
    value_four_parametr = new QStandardItem(tr("Условие 16"));
    value_four_parametr->setEditable(false);

    value_four_value = new QStandardItem(tr("Значение 16"));

    value_four.append(value_four_parametr);
    value_four.append(value_four_value);
    estimation_residual_thermal_life_parametr->appendRow(value_four);
    value_four.clear();

    value_five_parametr = new QStandardItem(tr("Условие 17"));
    value_five_parametr->setEditable(false);

    value_five_value = new QStandardItem(tr("Значение 17"));

    value_four.append(value_five_parametr);
    value_four.append(value_five_value);
    estimation_residual_thermal_life_parametr->appendRow(value_four);
    value_four.clear();

    value_six_parametr = new QStandardItem(tr ("Условие 18"));
    value_six_parametr->setEditable(false);

    value_six_value = new QStandardItem(tr ("Значение 18"));

    value_four.append(value_six_parametr);
    value_four.append(value_six_value);
    estimation_residual_thermal_life_parametr->appendRow(value_four);
    value_four.clear();

    /* секция "Выходные данные" */

    QList<QStandardItem*> output_data;
    output_data_parametr = new QStandardItem();
    output_data_parametr->setSelectable(false);
    output_data_parametr->setEditable(false);
    output_data_value = new QStandardItem();
    output_data_value->setSelectable(false);
    output_data_value->setEditable(false);
    output_data.append(output_data_parametr);
    output_data.append(output_data_value);
    model_treeView->appendRow(output_data);
    output_data.clear();

    QList<QStandardItem*> value_seven;
    value_seven_parametr = new QStandardItem(tr ("Условие 19"));
    value_seven_parametr->setEditable(false);

    value_seven_value = new QStandardItem(tr ("Значение 19"));

    value_seven.append(value_seven_parametr);
    value_seven.append(value_seven_value);
    output_data_parametr->appendRow(value_seven);
    value_seven.clear();

    value_eight_parametr = new QStandardItem(tr ("Условие 20"));
    value_eight_parametr->setEditable(false);

    value_eight_value = new QStandardItem(QString ("Значение 20"));

    value_seven.append(value_eight_parametr);
    value_seven.append(value_eight_value);
    output_data_parametr->appendRow(value_seven);
    value_seven.clear();

    value_nine_parametr = new QStandardItem(tr ("Условие 21"));
    value_nine_parametr->setEditable(false);

    value_nine_value = new QStandardItem(tr ("Значение 21"));

    value_seven.append(value_nine_parametr);
    value_seven.append(value_nine_value);
    output_data_parametr->appendRow(value_seven);
    value_seven.clear();

    //Настройка представления модели QTreeView
    ui->treeView->setModel(model_treeView);
    ui->treeView->header()->resizeSection(0,270);
    ui->treeView->header()->setSectionResizeMode(0,QHeaderView::Interactive);
    ui->treeView->header()->setSectionResizeMode(1,QHeaderView::Fixed);
    ui->treeView->expandAll();

    buttonColumnDelegate = new ButtonColumnDelegate(ui->treeView, this); //создание делегата для создания комбобоксов
    //buttonColumnDelegate->setRootIcon(QIcon("/home/elf/ImView2_Qt6/data/img/icons/branch-open.png"));
    ui->treeView->setItemDelegateForColumn(1, buttonColumnDelegate);

    LineDelegate *delegate = new LineDelegate(ui->treeView);
    ui->treeView->setItemDelegateForColumn(0, delegate);

    FillIconDelegate *fillIconDelegate = new FillIconDelegate(ui->treeView);
    ui->treeView->setItemDelegate(fillIconDelegate);

    //     ui->treeView->setStyleSheet(
    //                     "QScrollBar:vertical {border-width: 0px;border-style: solid;"
    //                     "background-color: #FFFFFF; width: 18px;}"
    //                     "QScrollBar::handle:vertical {background-color:#d0d2d2;min-height: 25px;"
    //                     "margin-left:5px;margin-right:5px;border-radius:4px;margin-top:5px;margin-bottom:5px;}"
    //                     "QScrollBar::handle:vertical:hover {background-color:#97d5f0;}"
    //                     "QScrollBar::add-line:vertical {border: 0px solid black;"
    //                     "height: 0px;subcontrol-position: bottom;subcontrol-origin: margin;}"
    //                     "QScrollBar::sub-line:vertical {border: 0px solid black;"
    //                     "height: 0px;subcontrol-position: top;subcontrol-origin: margin;}"
    //                             "*{"
    //                             "background: rgb(255, 255, 222);"
    //                             "}"
    //                            "*{"
    //                             "alternate-background-color: rgb(255, 255, 191);"
    //                            "}"
    //                             // "*::item{"
    //                             // "    border-top-width: 0px;"
    //                             // "    border-right-width: 1px;"
    //                             // "    border-bottom-width: 1px;"
    //                             // "    border-left-width: 0px;"
    //                             // "    border-style: solid;"
    //                             // "    border-color: silver;"
    //                             // "}"
    //                             "*::item:selected{"
    //                             "    background: palette(Highlight);"
    //                             "}"
    // //                            "*::item:has-children{"
    // //                            "    background: rgb(128,128,128);"
    // //                            "}"
    //                             // "::branch"
    //                             // "{"
    //                             // "border-bottom: 1px solid silver;"
    //                             // "border-image: none 0;"
    //                             // "image: none 0;"
    //                             // "}"
    //                                     "::branch:has-children:!has-siblings:closed,"
    //                                     "::branch:closed:has-children:has-siblings {"
    //                                     "        border-image: none;"
    //                                     //"        image: url(:/image/data/img/icons/branch-closed.png);"
    //                                     "}"
    //                                     "::branch:open:has-children:!has-siblings,"
    //                                     "::branch:open:has-children:has-siblings  {"
    //                                    "        border-image: none;"
    //                                    // "        image: url(:/image/data/img/icons/branch-open.png);"
    //                                     "}"
    //                 "::branch:has-siblings:!adjoins-item {"
    //                 "    border-image: url(:/data/img/icons/vline.png) 0;"
    //                 "}"

    //                 "::branch:has-siblings:adjoins-item {"
    //                 "    border-image: url(:/data/img/icons/branch-more.png) 0;"
    //                 "}"

    //                 "::branch:!has-children:!has-siblings:adjoins-item {"
    //                 "    border-image: url(:/data/img/icons/branch-end.png) 0;"
    //                 "}"

    //                 "::branch:has-children:!has-siblings:closed,"
    //                 "::branch:closed:has-children:has-siblings {"
    //                 "        border-image: none;"
    //                 "        image: url(:/image/data/img/icons/branch-closed.png);"
    //                 "}"

    //                 "::branch:open:has-children:!has-siblings,"
    //                 "::branch:open:has-children:has-siblings  {"
    //                 "        border-image: none;"
    //                 "        image: url(:/image/data/img/icons/branch-open.png);"
    //                 "}"

    //                                     );

    ui->treeView->setRootIsDecorated(true);

    selectionModel = ui->treeView->selectionModel();
    connect(selectionModel, &QItemSelectionModel::currentChanged,
            this, [this]() {   int index = 0;
                QString currentTabText = ui->tabWidget->tabText(index);
                setWindowTitle(currentTabText + "@" + QString(sesion_name_value1->text()) + QString(" - ImView*"));
                isNablLaunched = true;
            });

    selectionModel2 = ui->widget->ui->tableView->selectionModel();
    //connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &MainWindow::treview_changed);
    connect(selectionModel2, &QItemSelectionModel::currentChanged,
            this, &MainWindow::on_textChanged);


    connect(ui->lineEdit_13, &QLineEdit::textChanged, this, &MainWindow::on_textChanged);
    connect(ui->lineEdit_14, &QLineEdit::textChanged, this, &MainWindow::on_textChanged);
    connect(ui->lineEdit_15, &QLineEdit::textChanged, this, &MainWindow::on_textChanged);
    connect(ui->lineEdit_16, &QLineEdit::textChanged, this, &MainWindow::on_textChanged);
    connect(ui->lineEdit_17, &QLineEdit::textChanged, this, &MainWindow::on_textChanged);
    connect(ui->lineEdit_18, &QLineEdit::textChanged, this, &MainWindow::on_textChanged);
    connect(ui->lineEdit_8, &QLineEdit::textChanged, this, &MainWindow::on_textChanged);
    connect(ui->lineEdit_9, &QLineEdit::textChanged, this, &MainWindow::on_textChanged);
    connect(ui->lineEdit_10, &QLineEdit::textChanged, this, &MainWindow::on_textChanged);
    connect(ui->lineEdit_11, &QLineEdit::textChanged, this, &MainWindow::on_textChanged);
    connect(ui->lineEdit_12, &QLineEdit::textChanged, this, &MainWindow::on_textChanged);

    ui->tabWidget->setCurrentIndex(0);
    currentTabText = ui->tabWidget->tabText(0);

    setWindowTitle(currentTabText + "@" + QString(sesion_name_value1->text()) + QString(" - ImView"));
    if(ui->LoadProgect->isChecked() && ui->SaveProgectToFile->isChecked())
    {
        setWindowTitle(currentTabText + "@" + QString(sesion_name_value1->text()) + QString(" - ImView"));
    }

    //Настройка таблицы "Настройки графиков"
    ui->graph_settings->setRowCount(30); //задание количества строк таблицы
    ui->graph_settings->setColumnCount(5); //задание количества столбцов
    QStringList name2; //объявление указателя на тип QStringList
    name2 << "№" << "Цвет" << "Свойство" << "Смещение" << "Масштаб"; //перечисление заголовков
    ui->graph_settings->setHorizontalHeaderLabels(name2); //установка заголовков в таблицу
    ui->graph_settings->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); //Устанавливает ограничения на то, как размер заголовка может быть изменен до тех, которые описаны в данном режиме
    ui->graph_settings->horizontalHeader()->setStretchLastSection(true);
    ui->graph_settings->setSelectionMode(QAbstractItemView :: NoSelection);
    ui->graph_settings->verticalHeader()->setVisible(false);
    ui->graph_settings->resizeColumnsToContents();
    ui->graph_settings->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->graph_settings->setColumnWidth(0, 100);

    for(int row = 0; row<ui->graph_settings->rowCount(); row++)
    {
        for(int column = 0; column<ui->graph_settings->columnCount(); column++)
        {
            ui->graph_settings->setItem(row, column, new QTableWidgetItem());
        }
    }

    QTableWidgetItem *item251 = new QTableWidgetItem("Item251");
    item251->setCheckState(Qt::Checked);
    item251->setText("Сопротивление ротора R2, Ом");
    ui->graph_settings->setItem(0, 2, item251);

    QTableWidgetItem *item252 = new QTableWidgetItem("Item252");
    item252->setCheckState(Qt::Checked);
    item252->setText("Индуктивность обмотки статора L1, Гн");
    ui->graph_settings->setItem(1, 2, item252);

    QTableWidgetItem *item253 = new QTableWidgetItem("Item253");
    item253->setCheckState(Qt::Checked);
    item253->setText("Индуктивность обмотки ротора L2, Гн");
    ui->graph_settings->setItem(2, 2, item253);

    QTableWidgetItem *item254 = new QTableWidgetItem("Item254");
    item254->setCheckState(Qt::Checked);
    item254->setText("Индуктивность взаимоиндукции Lm, Гн");
    ui->graph_settings->setItem(3, 2, item254);

    QTableWidgetItem *item255 = new QTableWidgetItem("Item255");
    item255->setCheckState(Qt::Checked);
    item255->setText("Напряжение фазы А, В");
    ui->graph_settings->setItem(4, 2, item255);

    QTableWidgetItem *item256 = new QTableWidgetItem("Item256");
    item256->setCheckState(Qt::Checked);
    item256->setText("Напряжение фазы B, В");
    ui->graph_settings->setItem(5, 2, item256);

    QTableWidgetItem *item257 = new QTableWidgetItem("Item257");
    item257->setCheckState(Qt::Checked);
    item257->setText("Напряжение фазы C, В");
    ui->graph_settings->setItem(6, 2, item257);

    QTableWidgetItem *item258 = new QTableWidgetItem("Item258");
    item258->setCheckState(Qt::Checked);
    item258->setText("Ток фазы А, А");
    ui->graph_settings->setItem(7, 2, item258);

    QTableWidgetItem *item259 = new QTableWidgetItem("Item259");
    item259->setCheckState(Qt::Checked);
    item259->setText("Ток фазы B, А");
    ui->graph_settings->setItem(8, 2, item259);

    QTableWidgetItem *item260 = new QTableWidgetItem("Item260");
    item260->setCheckState(Qt::Checked);
    item260->setText("Ток фазы C, А");
    ui->graph_settings->setItem(9, 2, item260);

    QTableWidgetItem *item261 = new QTableWidgetItem("Item261");
    item261->setCheckState(Qt::Checked);
    item261->setText("Частота вращения, рад/с");
    ui->graph_settings->setItem(10, 2, item261);

    QTableWidgetItem *item262 = new QTableWidgetItem("Item262");
    item262->setCheckState(Qt::Checked);
    item262->setText("Момент на валу, Н*м");
    ui->graph_settings->setItem(11, 2, item262);

    QTableWidgetItem *item263 = new QTableWidgetItem("Item263");
    item263->setCheckState(Qt::Checked);
    item263->setText("Момент Мс, Н*м");
    ui->graph_settings->setItem(12, 2, item263);

    QTableWidgetItem *item264 = new QTableWidgetItem("Item264");
    item264->setCheckState(Qt::Checked);
    item264->setText("Станина, °C");
    ui->graph_settings->setItem(13, 2, item264);

    QTableWidgetItem *item265 = new QTableWidgetItem("Item265");
    item265->setCheckState(Qt::Checked);
    item265->setText("Подшипниковый узел справа сзади, °C");
    ui->graph_settings->setItem(14, 2, item265);

    QTableWidgetItem *item266 = new QTableWidgetItem("Item266");
    item266->setCheckState(Qt::Checked);
    item266->setText("Лобовая часть слева спереди, °C");
    ui->graph_settings->setItem(15, 2, item266);

    QTableWidgetItem *item267 = new QTableWidgetItem("Item267");
    item267->setCheckState(Qt::Checked);
    item267->setText("Подшипниковый узел слева спереди, °C");
    ui->graph_settings->setItem(16, 2, item267);

    QTableWidgetItem *item268 = new QTableWidgetItem("Item268");
    item268->setCheckState(Qt::Checked);
    item268->setText("Лобовая часть слева сзади, °C");
    ui->graph_settings->setItem(17, 2, item268);

    QTableWidgetItem *item269 = new QTableWidgetItem("Item269");
    item269->setCheckState(Qt::Checked);
    item269->setText("Станина, °C");
    ui->graph_settings->setItem(18, 2, item269);

    QTableWidgetItem *item270 = new QTableWidgetItem("Item270");
    item270->setCheckState(Qt::Checked);
    item270->setText("Лобовая часть справа спереди, °C");
    ui->graph_settings->setItem(19, 2, item270);

    QTableWidgetItem *item271 = new QTableWidgetItem("Item271");
    item271->setCheckState(Qt::Checked);
    item271->setText("Лобовая часть справа сзади, °C");
    ui->graph_settings->setItem(20, 2, item271);

    QTableWidgetItem *item272 = new QTableWidgetItem("Item272");
    item272->setCheckState(Qt::Checked);
    item272->setText("Магнитопровод статора, °C");
    ui->graph_settings->setItem(21, 2, item272);

    QTableWidgetItem *item273 = new QTableWidgetItem("Item273");
    item273->setCheckState(Qt::Checked);
    item273->setText("Подшипниковый узел справа спереди, °C");
    ui->graph_settings->setItem(22, 2, item273);

    QTableWidgetItem *item274 = new QTableWidgetItem("Item274");
    item274->setCheckState(Qt::Checked);
    item274->setText("одшипниковый узел слева сзади, °C");
    ui->graph_settings->setItem(23, 2, item274);

    QTableWidgetItem *item275 = new QTableWidgetItem("Item275");
    item275->setCheckState(Qt::Checked);
    item275->setText("Ротор сверху, °C");
    ui->graph_settings->setItem(24, 2, item275);

    QTableWidgetItem *item276 = new QTableWidgetItem("Item276");
    item276->setCheckState(Qt::Checked);
    item276->setText("Ротор снизу, °C");
    ui->graph_settings->setItem(25, 2, item276);

    QTableWidgetItem *item277 = new QTableWidgetItem("Item277");
    item277->setCheckState(Qt::Checked);
    item277->setText("Станина слева, °C");
    ui->graph_settings->setItem(26, 2, item277);

    QTableWidgetItem *item278 = new QTableWidgetItem("Item278");
    item278->setCheckState(Qt::Checked);
    item278->setText("Станина справа, °C");
    ui->graph_settings->setItem(27, 2, item278);


    QTableWidgetItem *item279 = new QTableWidgetItem("Item279");
    item279->setCheckState(Qt::Checked);
    item279->setText("Вал, °C");
    ui->graph_settings->setItem(28, 2, item279);

    QTableWidgetItem *item280 = new QTableWidgetItem("Item280");
    item280->setCheckState(Qt::Checked);
    item280->setText("Клеммная коробка, °C");
    ui->graph_settings->setItem(29, 2, item280);

    for (int i=0; i<34; i++)
    {
        if (ui->graph_settings->item(i, 0) != 0)
        {
            ui->graph_settings->item(i, 0)->setText(QString("%1").arg(i+1));
            ui->graph_settings->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }

    for (int i=0; i<34; i++)
    {
        if (ui->graph_settings->item(i, 3) != 0)
        {
            ui->graph_settings->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }

        if (ui->graph_settings->item(i, 4) != 0)
        {
            ui->graph_settings->item(i, 4)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->graph_settings->setItem(0, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(0, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(1, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(1, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(2, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(2, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(3, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(3, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(4, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(4, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(5, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(5, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(6, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(6, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(7, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(7, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(8, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(8, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(9, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(9, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(10, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(10, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(11, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(11, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(12, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(12, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(13, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(13, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(14, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(14, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(15, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(15, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(16, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(16, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(17, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(17, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(18, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(18, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(19, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(19, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(20, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(20, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(21, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(21, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(22, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(22, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(23, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(23, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(24, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(24, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(25, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(25, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(26, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(26, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(27, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(27, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(28, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(28, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->graph_settings->setItem(29, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->graph_settings->setItem(29, 4, new QTableWidgetItem(QString("%1").arg(1)));

    //Заполнение таблицы результатов
    ui->electromagn_result->setRowCount(25);
    ui->electromagn_result->setColumnCount(4);
    QStringList name_2;
    name_2 << "Величина" << "Обозначение" << "Значение" << "Размерность";
    ui->electromagn_result->setHorizontalHeaderLabels(name_2);
    ui->electromagn_result->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->electromagn_result->verticalHeader()->setVisible(true);
    ui->electromagn_result->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->electromagn_result->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->electromagn_result->setSelectionMode(QAbstractItemView :: SingleSelection);

    for(int row = 0; row<ui->electromagn_result->rowCount(); row++)
    {
        for(int column = 0; column<ui->electromagn_result->columnCount(); column++)
        {
            ui->electromagn_result->setItem(row, column, new QTableWidgetItem());
        }
    }

    ui->electromagn_result->setItem(0, 0, new QTableWidgetItem("Ток фазы А, А"));
    ui->electromagn_result->setItem(1, 0, new QTableWidgetItem("Напряжение фазы А, В"));
    ui->electromagn_result->setItem(2, 0, new QTableWidgetItem("Активная мошность фазы А, Вт"));
    ui->electromagn_result->setItem(3, 0, new QTableWidgetItem("Реактивная мошность фазы А, ВА"));
    ui->electromagn_result->setItem(4, 0, new QTableWidgetItem("Полная мошность фазы А, ВАР"));
    ui->electromagn_result->setItem(5, 0, new QTableWidgetItem("Коэффициент мощности фазы А"));
    ui->electromagn_result->setItem(6, 0, new QTableWidgetItem("Ток фазы В, А"));
    ui->electromagn_result->setItem(7, 0, new QTableWidgetItem("Напряжение фазы В, В"));
    ui->electromagn_result->setItem(8, 0, new QTableWidgetItem("Активная мошность фазы В, Вт"));
    ui->electromagn_result->setItem(9, 0, new QTableWidgetItem("Реактивная мошность фазы В, ВА"));
    ui->electromagn_result->setItem(10, 0, new QTableWidgetItem("Полная мошность фазы В, ВАР"));
    ui->electromagn_result->setItem(11, 0, new QTableWidgetItem("Коэффициент мощности фазы В"));
    ui->electromagn_result->setItem(12, 0, new QTableWidgetItem("Ток фазы С, А"));
    ui->electromagn_result->setItem(13, 0, new QTableWidgetItem("Напряжение фазы С, В"));
    ui->electromagn_result->setItem(14, 0, new QTableWidgetItem("Активная мошность фазы С, Вт"));
    ui->electromagn_result->setItem(15, 0, new QTableWidgetItem("Реактивная мошность фазы С, ВА"));
    ui->electromagn_result->setItem(16, 0, new QTableWidgetItem("Полная мошность фазы С, ВАР"));
    ui->electromagn_result->setItem(17, 0, new QTableWidgetItem("Коэффициент мощности фазы С"));
    ui->electromagn_result->setItem(18, 0, new QTableWidgetItem("трехфазная активная мошность, Вт"));
    ui->electromagn_result->setItem(19, 0, new QTableWidgetItem("Трехфазная реактивная мошность, ВА"));
    ui->electromagn_result->setItem(20, 0, new QTableWidgetItem("Трехфазная полная мошность, ВАР"));
    ui->electromagn_result->setItem(21, 0, new QTableWidgetItem("Коэффициент мощности"));
    ui->electromagn_result->setItem(22, 0, new QTableWidgetItem("Скорость вращения ротора, рад/с"));
    ui->electromagn_result->setItem(23, 0, new QTableWidgetItem("Момент, Н*м"));
    ui->electromagn_result->setItem(24, 0, new QTableWidgetItem("Момент сопротивления, Н*м"));

    ui->electromagn_result->setItem(0, 1, new QTableWidgetItem("i_dev_a"));
    ui->electromagn_result->setItem(1, 1, new QTableWidgetItem("u_dev_a"));
    ui->electromagn_result->setItem(2, 1, new QTableWidgetItem("p_akt_a"));
    ui->electromagn_result->setItem(3, 1, new QTableWidgetItem("p_reakt_a"));
    ui->electromagn_result->setItem(4, 1, new QTableWidgetItem("p_poln_a"));
    ui->electromagn_result->setItem(5, 1, new QTableWidgetItem("cos_f_a"));
    ui->electromagn_result->setItem(6, 1, new QTableWidgetItem("i_dev_b"));
    ui->electromagn_result->setItem(7, 1, new QTableWidgetItem("u_dev_b"));
    ui->electromagn_result->setItem(8, 1, new QTableWidgetItem("p_akt_b"));
    ui->electromagn_result->setItem(9, 1, new QTableWidgetItem("p_reakt_b"));
    ui->electromagn_result->setItem(10, 1, new QTableWidgetItem("p_poln_b"));
    ui->electromagn_result->setItem(11, 1, new QTableWidgetItem("cos_f_b"));
    ui->electromagn_result->setItem(12, 1, new QTableWidgetItem("i_dev_c"));
    ui->electromagn_result->setItem(13, 1, new QTableWidgetItem("u_dev_c"));
    ui->electromagn_result->setItem(14, 1, new QTableWidgetItem("p_akt_c"));
    ui->electromagn_result->setItem(15, 1, new QTableWidgetItem("p_reakt_c"));
    ui->electromagn_result->setItem(16, 1, new QTableWidgetItem("p_poln_c"));
    ui->electromagn_result->setItem(17, 1, new QTableWidgetItem("cos_f_c"));
    ui->electromagn_result->setItem(18, 1, new QTableWidgetItem("p_akt"));
    ui->electromagn_result->setItem(19, 1, new QTableWidgetItem("p_reakt"));
    ui->electromagn_result->setItem(20, 1, new QTableWidgetItem("p_poln"));
    ui->electromagn_result->setItem(21, 1, new QTableWidgetItem("cos_f"));
    ui->electromagn_result->setItem(22, 1, new QTableWidgetItem("omega"));
    ui->electromagn_result->setItem(23, 1, new QTableWidgetItem("M"));
    ui->electromagn_result->setItem(24, 1, new QTableWidgetItem("Mc"));

    ui->electromagn_result->setItem(0, 3, new QTableWidgetItem("А"));
    ui->electromagn_result->setItem(1, 3, new QTableWidgetItem("В"));
    ui->electromagn_result->setItem(2, 3, new QTableWidgetItem("Вт"));
    ui->electromagn_result->setItem(3, 3, new QTableWidgetItem("ВА"));
    ui->electromagn_result->setItem(4, 3, new QTableWidgetItem("ВАР"));
    ui->electromagn_result->setItem(5, 3, new QTableWidgetItem(" - "));
    ui->electromagn_result->setItem(6, 3, new QTableWidgetItem("А"));
    ui->electromagn_result->setItem(7, 3, new QTableWidgetItem("В"));
    ui->electromagn_result->setItem(8, 3, new QTableWidgetItem("Вт"));
    ui->electromagn_result->setItem(9, 3, new QTableWidgetItem("ВА"));
    ui->electromagn_result->setItem(10, 3, new QTableWidgetItem("ВАР"));
    ui->electromagn_result->setItem(11, 3, new QTableWidgetItem(" - "));
    ui->electromagn_result->setItem(12, 3, new QTableWidgetItem("А"));
    ui->electromagn_result->setItem(13, 3, new QTableWidgetItem("В"));
    ui->electromagn_result->setItem(14, 3, new QTableWidgetItem("Вт"));
    ui->electromagn_result->setItem(15, 3, new QTableWidgetItem("ВА"));
    ui->electromagn_result->setItem(16, 3, new QTableWidgetItem("ВАР"));
    ui->electromagn_result->setItem(17, 3, new QTableWidgetItem(" - "));
    ui->electromagn_result->setItem(18, 3, new QTableWidgetItem("Вт"));
    ui->electromagn_result->setItem(19, 3, new QTableWidgetItem("ВА"));
    ui->electromagn_result->setItem(20, 3, new QTableWidgetItem("ВАР"));
    ui->electromagn_result->setItem(21, 3, new QTableWidgetItem(" - "));
    ui->electromagn_result->setItem(22, 3, new QTableWidgetItem("рад/с"));
    ui->electromagn_result->setItem(23, 3, new QTableWidgetItem("Н*м"));
    ui->electromagn_result->setItem(24, 3, new QTableWidgetItem("Н*м"));

    for (int i=0; i<ui->electromagn_result->rowCount(); i++)
    {
        if (ui->electromagn_result->item(i, 1) != 0)
        {
            ui->electromagn_result->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->electromagn_result->item(i, 2) != 0)
        {
            ui->electromagn_result->item(i, 2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->electromagn_result->item(i, 3) != 0)
        {
            ui->electromagn_result->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }

    QPalette electromagn_result_palette=ui->electromagn_result->palette();
    electromagn_result_palette.setColor(QPalette::Base, QColor(255, 255, 191));
    electromagn_result_palette.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->electromagn_result->setPalette(electromagn_result_palette);


    //вставка таблицы тепловые характеристики
    ui->tepl_results->setRowCount(17);
    ui->tepl_results->setColumnCount(3);
    QStringList name;
    name << " № " << "Сигнал" << "Величина";
    ui->tepl_results->setHorizontalHeaderLabels(name);
    ui->tepl_results->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tepl_results->horizontalHeader()->setStretchLastSection(true);
    ui->tepl_results->verticalHeader()->setVisible(false);
    ui->tepl_results->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tepl_results->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tepl_results->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tepl_results->setColumnWidth(0, 100);

    for(int row = 0; row<ui->graph_settings->rowCount(); row++)
    {
        for(int column = 0; column<ui->tepl_results->columnCount(); column++)
        {
            ui->tepl_results->setItem(row, column, new QTableWidgetItem());

        }
    }

    for (int i=0; i<17; i++)
    {
        if (ui->tepl_results->item(i, 0) != 0)
        {
            ui->tepl_results->item(i, 0)->setText(QString("%1").arg(i+1));
            ui->tepl_results->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->tepl_results->setItem(0,  1, new QTableWidgetItem("Станина, °C"));
    ui->tepl_results->setItem(1,  1, new QTableWidgetItem("Подшипниковый узел справа сзади, °C"));
    ui->tepl_results->setItem(2,  1, new QTableWidgetItem("Лобовая часть слева спереди, °C"));
    ui->tepl_results->setItem(3,  1, new QTableWidgetItem("Подшипниковый узел слева спереди, °C"));
    ui->tepl_results->setItem(4,  1, new QTableWidgetItem("Лобовая часть слева сзади, °C"));
    ui->tepl_results->setItem(5,  1, new QTableWidgetItem("Станина, °C"));
    ui->tepl_results->setItem(6,  1, new QTableWidgetItem("Лобовая часть справа спереди, °C"));
    ui->tepl_results->setItem(7,  1, new QTableWidgetItem("Лобовая часть справа сзади, °C"));
    ui->tepl_results->setItem(8,  1, new QTableWidgetItem("Магнитопровод статора, °C"));
    ui->tepl_results->setItem(9,  1, new QTableWidgetItem("Подшипниковый узел справа спереди, °C"));
    ui->tepl_results->setItem(10, 1, new QTableWidgetItem("Подшипниковый узел слева сзади, °C"));
    ui->tepl_results->setItem(11, 1, new QTableWidgetItem("Ротор сверху, °C"));
    ui->tepl_results->setItem(12, 1, new QTableWidgetItem("Ротор снизу, °C"));
    ui->tepl_results->setItem(13, 1, new QTableWidgetItem("Станина слева, °C"));
    ui->tepl_results->setItem(14, 1, new QTableWidgetItem("Станина справа, °C"));
    ui->tepl_results->setItem(15, 1, new QTableWidgetItem("Вал, °C"));
    ui->tepl_results->setItem(16, 1, new QTableWidgetItem("Клеммная коробка, °C"));

    QPalette p102=ui->tepl_results->palette();
    p102.setColor(QPalette::Base, QColor(225, 255, 255));
    p102.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tepl_results->setPalette(p102);

    //вставка таблицы Энергетические характеристики таблицы tableWidget_4
    ui->energy_results->setRowCount(30);
    ui->energy_results->setColumnCount(4);
    QStringList name_4;
    name_4 << "Величина" << "Обозначение" << "Значение" << "Размерность";
    ui->energy_results->setHorizontalHeaderLabels(name_4);
    ui->energy_results->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->energy_results->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->energy_results->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->energy_results->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->energy_results->verticalHeader()->setVisible(true);
    ui->energy_results->resizeColumnsToContents();

    for(int row = 0; row<ui->energy_results->rowCount(); row++)
    {
        for(int column = 0; column<ui->energy_results->columnCount(); column++)
        {
            ui->energy_results->setItem(row, column, new QTableWidgetItem());

        }
    }


    //Заполнение полей левой части таблицы для пояснения чекбоксов таблицы tableWidget_3
    ui->energy_results->setItem(0, 0, new QTableWidgetItem("Потребляемая двигателем мощность, Вт"));
    ui->energy_results->setItem(1, 0, new QTableWidgetItem("Потери в обмотке статора Вт"));
    ui->energy_results->setItem(2, 0, new QTableWidgetItem("Потери в стали, Вт"));
    ui->energy_results->setItem(3, 0, new QTableWidgetItem("Потери в обмотке ротора, Вт"));
    ui->energy_results->setItem(4, 0, new QTableWidgetItem("Добавочные потери, Вт"));
    ui->energy_results->setItem(5, 0, new QTableWidgetItem("Механические потери, Вт"));
    ui->energy_results->setItem(6, 0, new QTableWidgetItem("Механическая мощность на валу двигателя, Вт"));
    ui->energy_results->setItem(7, 0, new QTableWidgetItem("Коэффициент полезного действия"));
    ui->energy_results->setItem(8, 0, new QTableWidgetItem("Коэффициент мощности"));

    ui->energy_results->setItem(0, 1, new QTableWidgetItem("P1"));
    ui->energy_results->setItem(1, 1, new QTableWidgetItem("ΔPel1"));
    ui->energy_results->setItem(2, 1, new QTableWidgetItem("ΔPct"));
    ui->energy_results->setItem(3, 1, new QTableWidgetItem("ΔPel2"));
    ui->energy_results->setItem(4, 1, new QTableWidgetItem("ΔPdob"));
    ui->energy_results->setItem(5, 1, new QTableWidgetItem("ΔPmech"));
    ui->energy_results->setItem(6, 1, new QTableWidgetItem("P2"));
    ui->energy_results->setItem(7, 1, new QTableWidgetItem("KPD"));
    ui->energy_results->setItem(8, 1, new QTableWidgetItem("cosf"));

    ui->energy_results->setItem(0, 3, new QTableWidgetItem("Вт"));
    ui->energy_results->setItem(1, 3, new QTableWidgetItem("Вт"));
    ui->energy_results->setItem(2, 3, new QTableWidgetItem("Вт"));
    ui->energy_results->setItem(3, 3, new QTableWidgetItem("Вт"));
    ui->energy_results->setItem(4, 3, new QTableWidgetItem("Вт"));
    ui->energy_results->setItem(5, 3, new QTableWidgetItem("Вт"));
    ui->energy_results->setItem(6, 3, new QTableWidgetItem("Вт"));
    ui->energy_results->setItem(7, 3, new QTableWidgetItem("--"));
    ui->energy_results->setItem(8, 3, new QTableWidgetItem("--"));

    for (int i=0; i<ui->energy_results->rowCount(); i++)
    {
        if (ui->energy_results->item(i, 1) != 0)
        {
            ui->energy_results->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->energy_results->item(i, 2) != 0)
        {
            ui->energy_results->item(i, 2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->energy_results->item(i, 3) != 0)
        {
            ui->energy_results->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }

    QPalette p4=ui->energy_results->palette();
    p4.setColor(QPalette::Base, QColor(225, 255, 255));
    p4.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->energy_results->setPalette(p4);

    ui->temp_draw_line->setRowCount(17);
    ui->temp_draw_line->setColumnCount(3);
    QStringList name_5;
    name_5 << " № " << "Сигнал" << "Величина";
    ui->temp_draw_line->setHorizontalHeaderLabels(name);
    ui->temp_draw_line->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->temp_draw_line->horizontalHeader()->setStretchLastSection(true);
    ui->temp_draw_line->verticalHeader()->setVisible(false);
    ui->temp_draw_line->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->temp_draw_line->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->temp_draw_line->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->temp_draw_line->setColumnWidth(0, 100);

    for(int row = 0; row<ui->temp_draw_line->rowCount(); row++)
    {
        for(int column = 0; column<ui->temp_draw_line->columnCount(); column++)
        {
            ui->temp_draw_line->setItem(row, column, new QTableWidgetItem());

        }
    }

    for (int i=0; i<17; i++)
    {
        if (ui->temp_draw_line->item(i, 0) != 0)
        {
            ui->temp_draw_line->item(i, 0)->setText(QString("%1").arg(i+1));
            ui->temp_draw_line->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->temp_draw_line->setItem(0,  1, new QTableWidgetItem("Станина, °C"));
    ui->temp_draw_line->setItem(1,  1, new QTableWidgetItem("Подшипниковый узел справа сзади, °C"));
    ui->temp_draw_line->setItem(2,  1, new QTableWidgetItem("Лобовая часть слева спереди, °C"));
    ui->temp_draw_line->setItem(3,  1, new QTableWidgetItem("Подшипниковый узел слева спереди, °C"));
    ui->temp_draw_line->setItem(4,  1, new QTableWidgetItem("Лобовая часть слева сзади, °C"));
    ui->temp_draw_line->setItem(5,  1, new QTableWidgetItem("Станина, °C"));
    ui->temp_draw_line->setItem(6,  1, new QTableWidgetItem("Лобовая часть справа спереди, °C"));
    ui->temp_draw_line->setItem(7,  1, new QTableWidgetItem("Лобовая часть справа сзади, °C"));
    ui->temp_draw_line->setItem(8,  1, new QTableWidgetItem("Магнитопровод статора, °C"));
    ui->temp_draw_line->setItem(9,  1, new QTableWidgetItem("Подшипниковый узел справа спереди, °C"));
    ui->temp_draw_line->setItem(10, 1, new QTableWidgetItem("Подшипниковый узел слева сзади, °C"));
    ui->temp_draw_line->setItem(11, 1, new QTableWidgetItem("Ротор сверху, °C"));
    ui->temp_draw_line->setItem(12, 1, new QTableWidgetItem("Ротор снизу, °C"));
    ui->temp_draw_line->setItem(13, 1, new QTableWidgetItem("Станина слева, °C"));
    ui->temp_draw_line->setItem(14, 1, new QTableWidgetItem("Станина справа, °C"));
    ui->temp_draw_line->setItem(15, 1, new QTableWidgetItem("Вал, °C"));
    ui->temp_draw_line->setItem(16, 1, new QTableWidgetItem("Клеммная коробка, °C"));

    QPalette p105=ui->temp_draw_line->palette();
    p105.setColor(QPalette::Base, QColor(225, 255, 255));
    p105.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->temp_draw_line->setPalette(p105);

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
    for(int row = 0; row<ui->graph_settings->rowCount(); row++)
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
        ui->graph_settings->item(i, 1)->setBackground(dataLineColors[i]);
    }

    connect(ui->graph_settings, &QTableWidget::cellClicked,this, &MainWindow::setcolorincell);

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
    ui->electromagn_result->setItemDelegateForColumn(0, customHelpDelegate);
    ui->energy_results->setItemDelegateForColumn(0, customHelpDelegate);
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
    ui->tableWidget_7->setItem(11, 3, new QTableWidgetItem("м²"));
    ui->tableWidget_7->setItem(12, 3, new QTableWidgetItem("м²"));
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

    ui->tableWidget_17->setRowCount(30);
    ui->tableWidget_17->setColumnCount(4);
    QStringList name_17;
    name_17 << "Величина" << "Обозначение" << "Значение" << "Размерность";

    ui->tableWidget_17->setHorizontalHeaderLabels(name_17);
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
                setWindowTitle(currentTabText + "@" + QString(sesion_name_value1->text()) + QString(" - ImView*"));
                isNablLaunched = true;
            });

    ui->tableWidget_18->setRowCount(30);
    ui->tableWidget_18->setColumnCount(4);
    QStringList name_18;
    name_18 << "Величина" << "Обозначение" << "Значение" << "Размерность";

    ui->tableWidget_18->setHorizontalHeaderLabels(name_18);
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

    ui->tableWidget_20->setRowCount(6);
    ui->tableWidget_20->setColumnCount(4);
    QStringList name_20;
    name_20 << "Величина" << "Обозначение" << "Значение" << "Размерность";

    ui->tableWidget_20->setHorizontalHeaderLabels(name_20);
    ui->tableWidget_20->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_20->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_20->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_20->verticalHeader()->setVisible(true);
    ui->tableWidget_20->resizeColumnsToContents();

    // for(int row = 0; row<ui->tableWidget_20->rowCount(); row++)
    // {
    //     for(int column = 0; column<ui->tableWidget_20->columnCount(); column++)
    //     {
    //         ui->tableWidget_20->setItem(row, column, new QTableWidgetItem());

    //     }
    // }

    ui->tableWidget_20->setItem(0, 0, new QTableWidgetItem("Рабочий расход воздуха"));
    ui->tableWidget_20->setItem(1, 0, new QTableWidgetItem("Максимальный расход воздуха"));
    ui->tableWidget_20->setItem(2, 0, new QTableWidgetItem("Начальное давление вентилятора"));
    ui->tableWidget_20->setItem(3, 0, new QTableWidgetItem("Рабочий набор вентилятора"));
    ui->tableWidget_20->setItem(4, 0, new QTableWidgetItem("Суммарное сопротивление вентиляционной сети"));
    ui->tableWidget_20->setItem(5, 0, new QTableWidgetItem("Потребляемая вентилятором мощность"));

    ui->tableWidget_20->setItem(0, 1, new QTableWidgetItem("Qp"));
    ui->tableWidget_20->setItem(1, 1, new QTableWidgetItem("Qmax"));
    ui->tableWidget_20->setItem(2, 1, new QTableWidgetItem("H0"));
    ui->tableWidget_20->setItem(3, 1, new QTableWidgetItem("Hp"));
    ui->tableWidget_20->setItem(4, 1, new QTableWidgetItem("Z0"));
    ui->tableWidget_20->setItem(5, 1, new QTableWidgetItem("Pvent"));

    ui->tableWidget_20->setItem(0, 2, new QTableWidgetItem(" "));
    ui->tableWidget_20->setItem(1, 2, new QTableWidgetItem(" "));
    ui->tableWidget_20->setItem(2, 2, new QTableWidgetItem(" "));
    ui->tableWidget_20->setItem(3, 2, new QTableWidgetItem(" "));
    ui->tableWidget_20->setItem(4, 2, new QTableWidgetItem(" "));
    ui->tableWidget_20->setItem(5, 2, new QTableWidgetItem(" "));

    ui->tableWidget_20->setItem(0, 3, new QTableWidgetItem("м³/c"));
    ui->tableWidget_20->setItem(1, 3, new QTableWidgetItem("м³/c"));
    ui->tableWidget_20->setItem(2, 3, new QTableWidgetItem("Па"));
    ui->tableWidget_20->setItem(3, 3, new QTableWidgetItem("Па"));
    ui->tableWidget_20->setItem(4, 3, new QTableWidgetItem("--"));
    ui->tableWidget_20->setItem(5, 3, new QTableWidgetItem("Вт"));

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
    p_20.setColor(QPalette::Base, QColor(225, 255, 255));
    p_20.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
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
    widget2->setFixedWidth(0);
    widget2->setHidden(1);
    widget2->setVisible(1);
    ui->statusbar->addPermanentWidget(widget2);

    statusbar_progres = new QProgressBar(ui->statusbar);
    statusbar_progres->setMaximumSize(200,19);
    statusbar_progres->setMinimumSize(200,19);
    ui->statusbar->addPermanentWidget(statusbar_progres);
    setStyleSheet("QProgressBar {border: 2px solid grey;height: 5px; text-align: center;} QProgressBar::chunk {background-color: #55FF55;}");
    statusbar_progres->setVisible(false);

    widget = new QWidget(ui->statusbar);
    widget->setFixedWidth(250);
    widget->setHidden(1);
    widget->setVisible(1);
    ui->statusbar->addPermanentWidget(widget);

    QLabel *rightLabel = new QLabel(QString("Версия: ") + vers2);
    //QLabel *rightLabel = new QLabel("Версия: " + vers2);
    rightLabel->setContentsMargins(0, 0, 20, 0);
    ui->statusbar->addPermanentWidget(rightLabel);

    widget = new QWidget(ui->statusbar);
    widget->setFixedWidth(50);
    widget->setHidden(1);
    widget->setVisible(1);
    ui->statusbar->addWidget(widget);

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

    connect(calculation_mode_value->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot);
    connect(identification_switch_value->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot_2);
    connect(enter_type_experiment_value->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot_3);
    connect(data_identification_value->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot_4);
    connect(calculation_modes_value->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot_5);
    connect(time_base_selection_value->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot_6);
    connect(time_cycle_value->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot_7);
    connect(time_start_in_cycle_value->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot_8);
    connect(data_approximation_mode_value->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot_9);

    connect(creating_motor_voltage_change_chart_value->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot_10);

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
    connect(ui->widget_7->ui->tabWidget, &QTabWidget::currentChanged, this,&MainWindow::tabClicked_6);
    connect(model_treeView, &QStandardItemModel::itemChanged, this, &MainWindow::button_visible);
    connect(model_treeView, &QStandardItemModel::itemChanged, this, &MainWindow::button_visible_2);

    connect(ui->lineEdit_13,&QLineEdit::textEdited, this, &MainWindow::edit);
    connect(ui->lineEdit_16,&QLineEdit::textEdited, this, &MainWindow::edit_2);
    connect(ui->lineEdit_14,&QLineEdit::textEdited, this, &MainWindow::edit_3);
    connect(ui->lineEdit_17,&QLineEdit::textEdited, this, &MainWindow::edit_4);
    connect(ui->lineEdit_15,&QLineEdit::textEdited, this, &MainWindow::edit_5);
    connect(ui->lineEdit_18,&QLineEdit::textEdited, this, &MainWindow::edit_6);
    connect(model_treeView,&QStandardItemModel::itemChanged, this, &MainWindow::edit_treeview);

    connect(ui->widget_3, &electromagn::tick, this, &MainWindow::electromagn_tick);

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

void MainWindow::on_textChanged()
{
  isNablLaunched = true;
}

void MainWindow::loadTable1()
{
    loadTable("ventilators"); // Замените на имя вашей первой таблицы
    ui->widget_7->ui->widget->table();
}

void MainWindow::loadTable2()
{
    loadTable("vent__lopast"); // Замените на имя вашей второй таблицы
    ui->widget_7->ui->widget->table_2();
}

void MainWindow::loadTable(const QString &tableName)
{
    if (ui->widget_7->ui->widget->model2)
    {
        delete ui->widget_7->ui->widget->model2;
    }

    ui->widget_7->ui->widget->model2 = new QSqlTableModel(this, QSqlDatabase::database("connection2"));
    ui->widget_7->ui->widget->model2->setTable(tableName);
    if (!ui->widget_7->ui->widget->model2->select())
    {
        QMessageBox::critical(this, "Ошибка", ui->widget_7->ui->widget->model2->lastError().text());
        return;
    }
    ui->widget_7->ui->widget->model2->select();
    ui->widget_7->ui->widget->ui->tableView->setModel(ui->widget_7->ui->widget->model2);
}

void MainWindow::electrostart()
{
    ui->pushButton_8->setEnabled(true);
    base.Mc_n = enter_moment_value->text().toDouble();
    base.Um = enter_voltage_im_mashine_value->text().toDouble();
    ui->horizontalSlider_4->setValue(base.Mc_n);
    ui->horizontalSlider_3->setValue(base.Um);
    ui->lineEdit_26->setText(QString("%1").arg(base.Mc_n));
    ui->lineEdit_25->setText(QString("%1").arg(base.Um));
    ui->widget_6->vent_model_start();
}

void MainWindow::electrostop()
{
    ui->horizontalSlider_4->setValue(0);
    ui->horizontalSlider_3->setValue(0);
    ui->lineEdit_26->setText(QString("%1").arg(0));
    ui->lineEdit_25->setText(QString("%1").arg(0));
    ui->widget_6->vent_model_stop();
    ui->pushButton_8->setEnabled(false);
}
