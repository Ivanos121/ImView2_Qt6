#include <QDesktopServices>
#include <QFileDialog>
#include <QScreen>
#include <QSettings>
#include <QSvgWidget>
#include <QUrl>

#include "start_app.h"
#include "mainwindow.h"
#include "save_progect.h"
#include "ui_start_app.h"
#include "ui_mainwindow.h"

Save_progect save_progect;

Start_app::Start_app(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Start_app)
{
    ui->setupUi(this);

    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->verticalHeader()->hide();

    connect(ui->tableWidget, &QTableWidget::cellClicked, this, &Start_app::selectImage);
    connect(ui->tableWidget, &QTableWidget::cellClicked, this, &Start_app::openRecentFile);
    connect(ui->label_4, &MyLabel::clicked, this, &Start_app::click_open_metod_one);
    connect(ui->label_5, &MyLabel::clicked, this, &Start_app::click_open_metod_two);
    connect(ui->label_6, &MyLabel::clicked, this, &Start_app::click_open_metod_three);
    connect(ui->label_7, &MyLabel::clicked, this, &Start_app::click_open_metod_four);
    connect(ui->label_8, &MyLabel::clicked, this, &Start_app::click_open_metod_five);
    connect(ui->label_9, &MyLabel::clicked, this, &Start_app::click_open_metod_six);
    connect(ui->label_10, &MyLabel::clicked, this, &Start_app::click_open_metod_seven);
    connect(ui->label_11, &MyLabel::clicked, this, &Start_app::click_open_metod_eight);
    connect(ui->label_12, &MyLabel::clicked, this, &Start_app::click_open_metod_nine);
    connect(ui->label_13, &MyLabel::clicked, this, &Start_app::click_open_metod_ten);
    connect(ui->label_14, &MyLabel::clicked, this, &Start_app::click_open_metod_eleven);
    connect(ui->label_15, &MyLabel::clicked, this, &Start_app::click_open_metod_twelv);

    for(int row = 0; row<ui->tableWidget->rowCount()-2; row++)
    {
        for(int column = 0; column<ui->tableWidget->columnCount(); column++)
        {
            ui->tableWidget->setItem(row, column, new QTableWidgetItem());
        }
    }

    for (int i=0; i<ui->tableWidget->rowCount()-2; i++)
    {
        if (ui->tableWidget->item(i, 1) != 0)
        {
            ui->tableWidget->item(i, 1)->setTextAlignment(Qt::AlignLeft);
            ui->tableWidget->item(i, 1)->setTextAlignment(Qt::AlignVCenter);
        }
    }

    for(int row = 0; row<ui->tableWidget->rowCount()-2; row++)
    {
        if (ui->tableWidget->item(row,0) != 0)
        {
            ui->tableWidget->item(row,0)->setFlags(Qt::NoItemFlags);
        }
        if (ui->tableWidget->item(row,1) != 0)
        {
            ui->tableWidget->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
    }

    ui->label_2->setText("<a href=\"whatever\" style=\"color: black;QFont::Normal\">Открыть файл сохранения</a>");
    ui->label_2->setTextInteractionFlags(Qt::TextBrowserInteraction);
    QFont newFont("DroidSans", 14, QFont::Normal,false);
    ui->label_2->setFont(newFont);

    ui->label->setText("<a href=\"whatever\" style=\"color: black;\">Справка</a>");
    ui->label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    QFont newFont2("DroidSans", 14, QFont::Normal,false);
    ui->label->setFont(newFont2);

    ui->label_16->setText("Создать");
    ui->label_16->setTextInteractionFlags(Qt::TextBrowserInteraction);
    QFont newFont3("DroidSans", 14, QFont::Normal,false);
    ui->label_16->setFont(newFont3);

    ui->label_4->setText("Основы работы");
    ui->label_4->setStyleSheet("font-weight: normal; color: black; text-decoration: underline;");

    ui->label_5->setText("Настройка сессии");
    ui->label_5->setStyleSheet("font-weight: normal; color: black; text-decoration: underline;");

    ui->label_6->setText("Ввод исходных данных");
    ui->label_6->setStyleSheet("font-weight: normal; color: black; text-decoration: underline;");

    ui->label_7->setText("Идентификация параметров схемы замещения асинхронного электродвигателя");
    ui->label_7->setStyleSheet("font-weight: normal; color: black; text-decoration: underline;");

    ui->label_8->setText("Энергетическая модель асинхронного электродвигателя");
    ui->label_8->setStyleSheet("font-weight: normal; color: black; text-decoration: underline;");

    ui->label_9->setText("Тепловая модель асинхронного электродвигателя");
    ui->label_9->setStyleSheet("font-weight: normal; color: black; text-decoration: underline;");

    ui->label_10->setText("Вентиляционная модель асинхронного электродвигателя");
    ui->label_10->setStyleSheet("font-weight: normal; color: black; text-decoration: underline;");

    ui->label_11->setText("Тепловентиляционная модель асинхронного электродвигателя");
    ui->label_11->setStyleSheet("font-weight: normal; color: black; text-decoration: underline;");

    ui->label_12->setText("Прогноз температур асинхронного электродвигателя");
    ui->label_12->setStyleSheet("font-weight: normal; color: black; text-decoration: underline;");

    ui->label_13->setText("Тепловой наблюдатель");
    ui->label_13->setStyleSheet("font-weight: normal; color: black; text-decoration: underline;");

    ui->label_14->setText("Остаточный тепаловой ресурс обмотки статора асинхронного электродвигателя");
    ui->label_14->setStyleSheet("font-weight: normal; color: black; text-decoration: underline;");

    ui->label_15->setText("Оформление протокола исследований");
    ui->label_15->setStyleSheet("font-weight: normal; color: black; text-decoration: underline;");

    connect(ui->label_2,&QLabel::linkActivated, this, &Start_app::click_open_file);
    connect(ui->label,&QLabel::linkActivated, this, &Start_app::click_open_help);
    connect(ui->tableWidget,&QTableWidget::itemActivated,this,&Start_app::click_open_progect);
    connect(ui->tableWidget_2,&QAbstractItemView::clicked,this,&Start_app::click_open_progect_2);

    ui->tableWidget_2->setRowCount(6);
    ui->tableWidget_2->setColumnCount(5);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView :: NoSelection);
    ui->tableWidget_2->horizontalHeader()->hide();
    ui->tableWidget_2->verticalHeader()->hide();
    ui->tableWidget_2->verticalHeader()->hide();
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for(int row = 0; row<ui->tableWidget_2->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_2->columnCount(); column++)
        {
            ui->tableWidget_2->setItem(row, column, new QTableWidgetItem());
        }
    }

    for (int i=0; i<ui->tableWidget_2->columnCount(); i++)
    {
        if (ui->tableWidget_2->item(1, i) != 0)
        {
            ui->tableWidget_2->item(1, i)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_2->item(1, i)->setTextAlignment(Qt::AlignVCenter);
        }
        if (ui->tableWidget_2->item(3, i) != 0)
        {
            ui->tableWidget_2->item(3, i)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_2->item(3, i)->setTextAlignment(Qt::AlignVCenter);
        }
    }

    ui->tableWidget_2->setItem(1, 0, new QTableWidgetItem("Создание нового сеанса"));
    ui->tableWidget_2->setItem(1, 2, new QTableWidgetItem("Идентификация \n данных"));
    ui->tableWidget_2->setItem(1, 4, new QTableWidgetItem("Электромагнитная \n модель"));
    ui->tableWidget_2->setItem(3, 0, new QTableWidgetItem("Тепловая модель"));
    ui->tableWidget_2->setItem(3, 2, new QTableWidgetItem("Вентиляционная модель"));
    ui->tableWidget_2->setItem(3, 4, new QTableWidgetItem("Прогноз температур"));
    ui->tableWidget_2->setItem(5, 0, new QTableWidgetItem("Остаточный \n тепловой \n ресурс"));

    svgwidget2 = new MySvgWidget();
    QWidget *widget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->addWidget(svgwidget2);
    svgwidget2->svgFileName = "/home/elf/ImView2/data/img/system_icons/IM_96x96_ns.svg";
    svgwidget2->svgSelectedFileName = "/home/elf/ImView2/data/img/system_icons/IM_96x96_ns_select.svg";
    svgwidget2->loadFile();
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(0,0,0,0);
    ui->tableWidget_2->setCellWidget(0, 0, widget);
    ui->tableWidget_2->item(1, 0)->setTextAlignment(Qt::AlignCenter);

    svgwidget3 = new MySvgWidget();
    QWidget *widget2 = new QWidget();
    svgwidget3->svgFileName = "/home/elf/ImView2/data/img/system_icons/IM_96x96_id.svg";
    svgwidget3->svgSelectedFileName = "/home/elf/ImView2/data/img/system_icons/IM_96x96_id_select.svg";
    svgwidget3->loadFile();
    QHBoxLayout *layout2 = new QHBoxLayout(widget2);
    layout2->addWidget(svgwidget3);
    layout2->setAlignment(Qt::AlignCenter);
    layout2->setContentsMargins(0,0,0,0);
    ui->tableWidget_2->setCellWidget(0, 2, widget2);
    ui->tableWidget_2->item(1, 2)->setTextAlignment(Qt::AlignCenter);

    svgwidget4 = new MySvgWidget();
    QWidget *widget3 = new QWidget();
    svgwidget4->svgFileName = "/home/elf/ImView2/data/img/system_icons/IM_96x96_elm.svg";
    svgwidget4->svgSelectedFileName = "/home/elf/ImView2/data/img/system_icons/IM_96x96_elm_select.svg";
    svgwidget4->loadFile();
    QHBoxLayout *layout3 = new QHBoxLayout(widget3);
    layout3->addWidget(svgwidget4);
    layout3->setAlignment(Qt::AlignCenter);
    layout3->setContentsMargins(0,0,0,0);
    ui->tableWidget_2->setCellWidget(0, 4, widget3);
    ui->tableWidget_2->item(1, 4)->setTextAlignment(Qt::AlignCenter);

    svgwidget5 = new MySvgWidget();
    QWidget *widget4 = new QWidget();
    svgwidget5->svgFileName = "/home/elf/ImView2/data/img/system_icons/IM_96x96_tm.svg";
    svgwidget5->svgSelectedFileName = "/home/elf/ImView2/data/img/system_icons/IM_96x96_tm_select.svg";
    svgwidget5->loadFile();
    QHBoxLayout *layout4 = new QHBoxLayout(widget4);
    layout4->addWidget(svgwidget5);
    layout4->setAlignment(Qt::AlignCenter);
    layout4->setContentsMargins(0,0,0,0);
    ui->tableWidget_2->setCellWidget(2, 0, widget4);
    ui->tableWidget_2->item(3, 0)->setTextAlignment(Qt::AlignCenter);

    svgwidget6 = new MySvgWidget();
    QWidget *widget5 = new QWidget();
    svgwidget6->svgFileName = "/home/elf/ImView2/data/img/system_icons/IM_96x96_vm.svg";
    svgwidget6->svgSelectedFileName = "/home/elf/ImView2/data/img/system_icons/IM_96x96_vm_select.svg";
    svgwidget6->loadFile();
    QHBoxLayout *layout5 = new QHBoxLayout(widget5);
    layout5->addWidget(svgwidget6);
    layout5->setAlignment(Qt::AlignCenter);
    layout5->setContentsMargins(0,0,0,0);
    ui->tableWidget_2->setCellWidget(2, 2, widget5);
    ui->tableWidget_2->item(3, 2)->setTextAlignment(Qt::AlignCenter);

    svgwidget7 = new MySvgWidget();
    QWidget *widget6 = new QWidget();
    svgwidget7->svgFileName = "/home/elf/ImView2/data/img/system_icons/IM_96x96_pt.svg";
    svgwidget7->svgSelectedFileName = "/home/elf/ImView2/data/img/system_icons/IM_96x96_pt_select.svg";
    svgwidget7->loadFile();
    QHBoxLayout *layout6 = new QHBoxLayout(widget6);
    layout6->addWidget(svgwidget7);
    layout6->setAlignment(Qt::AlignCenter);
    layout6->setContentsMargins(0,0,0,0);
    ui->tableWidget_2->setCellWidget(2, 4, widget6);
    ui->tableWidget_2->item(3, 4)->setTextAlignment(Qt::AlignCenter);

    svgwidget8 = new MySvgWidget();
    QWidget *widget7 = new QWidget();
    svgwidget8->svgFileName = "/home/elf/ImView2/data/img/system_icons/IM_96x96_otr.svg";
    svgwidget8->svgSelectedFileName = "/home/elf/ImView2/data/img/system_icons/IM_96x96_otr_select.svg";
    svgwidget8->loadFile();
    QHBoxLayout *layout7 = new QHBoxLayout(widget7);
    layout7->addWidget(svgwidget8);
    layout7->setAlignment(Qt::AlignCenter);
    layout7->setContentsMargins(0,0,0,0);
    ui->tableWidget_2->setCellWidget(4, 0, widget7);
    ui->tableWidget_2->item(5, 0)->setTextAlignment(Qt::AlignCenter);

    QPalette palette = ui->tableWidget_2->palette();
    palette.setBrush(QPalette::Highlight,QBrush(QColor(239, 240, 241)));
    palette.setBrush(QPalette::HighlightedText,QBrush(Qt::black));
    ui->tableWidget_2->setPalette(palette);

    updateRecentFileActions();
}

Start_app::~Start_app()
{
    delete ui;    
}

void Start_app::click_open_file()
{
    wf->open_file();
}

void Start_app::click_open_progect()
{
    QSettings settings( "BRU", "IM View");

    QList<QString> name = { "name_1", "name_2", "name_3", "name_4", "name_5", "name_6", "name_7", "name_8", "name_9", "name_10" };
    QList<QString> path = { "path_1", "path_2", "path_3", "path_4", "path_5", "path_6", "path_7", "path_8", "path_9", "path_10" };
    QList<QString> id = { "id_1", "id_2", "id_3", "id_4", "id_5", "id_6", "id_7", "id_8", "id_9", "id_10" };

    for (int i = 0; i < name.size(); ++i)
    {
        if (name.at(i) == "name_1")
            save_progect.progect_1.name_1 = settings.value( "name_1", "").toString();
    }

    for (int i = 0; i < path.size(); ++i)
    {
        if (path.at(i) == "path_1")
            save_progect.progect_1.path_1 = settings.value( "path_1", "").toString();
    }
    for (int i = 0; i < id.size(); ++i)
    {
        if (id.at(i) == "id_1")
            save_progect.progect_1.id_1 = settings.value( "id_1", "").toInt();
    }

    QString str = save_progect.progect_1.path_1 + "/" + save_progect.progect_1.name_1;
    wf->LoadProject(str);
    wf->updateWindowSize();
}

void Start_app::click_open_progect_2(const QModelIndex& idx)
{
    int x = idx.row();
    int y = idx.column();

    if((x == 0) && (y == 0))
    {
        wf->ui->widget_15->hide();
        wf->ui->tabWidget->show();
        wf->ui->stackedWidget->show();
        wf->ui->switch_regim_upr->show();
        wf->ui->toolBar->show();
        wf->ui->toolBar_2->show();
        wf->ui->menu_2->menuAction()->setVisible(true);
        wf->ui->menu_3->menuAction()->setVisible(true);
        wf->ui->menu_4->menuAction()->setVisible(true);
        wf->ui->menu_5->menuAction()->setVisible(true);
        wf->ui->save_file->setVisible(true);
        wf->ui->save_as_file->setVisible(true);
        wf->ui->action_save_graph_file->setVisible(true);
        wf->ui->action_close_progect->setVisible(true);
        wf->ui->action_close_session->setVisible(true);
        wf->ui->print_file->setVisible(true);
        wf->ui->print_preview->setVisible(true);
        wf->ui->statusbar->show();        
    }

    if((x == 0) && (y == 2))
    {
        wf->ui->widget_15->hide();
        wf->ui->tabWidget->show();
        wf->ui->stackedWidget->show();
        wf->ui->switch_regim_upr->show();
        wf->ui->toolBar->show();
        wf->ui->toolBar_2->show();
        wf->ui->menu_2->menuAction()->setVisible(true);
        wf->ui->menu_3->menuAction()->setVisible(true);
        wf->ui->menu_4->menuAction()->setVisible(true);
        wf->ui->menu_5->menuAction()->setVisible(true);
        wf->ui->save_file->setVisible(true);
        wf->ui->save_as_file->setVisible(true);
        wf->ui->action_save_graph_file->setVisible(true);
        wf->ui->action_close_progect->setVisible(true);
        wf->ui->action_close_session->setVisible(true);
        wf->ui->print_file->setVisible(true);
        wf->ui->print_preview->setVisible(true);
        wf->ui->statusbar->show();
        wf->ui->tabWidget->setTabVisible(4, false);
        wf->ui->tabWidget->setTabVisible(5, false);
        wf->ui->tabWidget->setTabVisible(6, false);
        wf->ui->tabWidget->setTabVisible(7, false);
        wf->ui->tabWidget->setTabVisible(8, false);

        if (wf->model_treeView) {
            // Получаем количество корневых узлов
            int rootCount = wf->model_treeView->rowCount();
            for (int i = rootCount - 1; i >= 0; --i)
            {
                QModelIndex rootIndex = wf->model_treeView->index(i, 0);
                QStandardItem *rootItem = wf->model_treeView->itemFromIndex(rootIndex);
                // Проверьте ваши условия для промежуточного узла (например, по типу, названиям и т.д.)
                if ((rootItem->text() == "Электромагнитная модель")
                    ||(rootItem->text() == "Тепловая модель")
                    ||(rootItem->text() == "Вентиляционная модель")
                    ||(rootItem->text() == "Прогнозирование температур")
                    ||(rootItem->text() == "Оценка остаточного теплового ресурса"))
                {
                    wf->model_treeView->removeRow(i); // Удаляем узел
                }
            }
        }
    }

    if((x == 0) && (y == 4))
    {
        wf->ui->widget_15->hide();
        wf->ui->tabWidget->show();
        wf->ui->stackedWidget->show();
        wf->ui->switch_regim_upr->show();
        wf->ui->toolBar->show();
        wf->ui->toolBar_2->show();
        wf->ui->menu_2->menuAction()->setVisible(true);
        wf->ui->menu_3->menuAction()->setVisible(true);
        wf->ui->menu_4->menuAction()->setVisible(true);
        wf->ui->menu_5->menuAction()->setVisible(true);
        wf->ui->save_file->setVisible(true);
        wf->ui->save_as_file->setVisible(true);
        wf->ui->action_save_graph_file->setVisible(true);
        wf->ui->action_close_progect->setVisible(true);
        wf->ui->action_close_session->setVisible(true);
        wf->ui->print_file->setVisible(true);
        wf->ui->print_preview->setVisible(true);
        wf->ui->statusbar->show();
        wf->ui->tabWidget->setTabVisible(1, false);
        wf->ui->tabWidget->setTabVisible(2, false);
        wf->ui->tabWidget->setTabVisible(3, false);
        wf->ui->tabWidget->setTabVisible(5, false);
        wf->ui->tabWidget->setTabVisible(6, false);
        wf->ui->tabWidget->setTabVisible(7, false);
        wf->ui->tabWidget->setTabVisible(8, false);

        if (wf->model_treeView) {
            // Получаем количество корневых узлов
            int rootCount = wf->model_treeView->rowCount();
            for (int i = rootCount - 1; i >= 0; --i)
            {
                QModelIndex rootIndex = wf->model_treeView->index(i, 0);
                QStandardItem *rootItem = wf->model_treeView->itemFromIndex(rootIndex);
                // Проверьте ваши условия для промежуточного узла (например, по типу, названиям и т.д.)
                if ((rootItem->text() == "Идентификация параметров схемы замещения")
                    ||(rootItem->text() == "Тепловая идентификация")
                    ||(rootItem->text() == "Вентиляционная идентификация")
                    ||(rootItem->text() == "Тепловая модель")
                    ||(rootItem->text() == "Вентиляционная модель")
                    ||(rootItem->text() == "Прогнозирование температур")
                    ||(rootItem->text() == "Оценка остаточного теплового ресурса"))
                {
                    wf->model_treeView->removeRow(i); // Удаляем узел
                }
            }
        }
    }

    if((x == 2) && (y == 0))
    {
        wf->ui->widget_15->hide();
        wf->ui->tabWidget->show();
        wf->ui->stackedWidget->show();
        wf->ui->switch_regim_upr->show();
        wf->ui->toolBar->show();
        wf->ui->toolBar_2->show();
        wf->ui->menu_2->menuAction()->setVisible(true);
        wf->ui->menu_3->menuAction()->setVisible(true);
        wf->ui->menu_4->menuAction()->setVisible(true);
        wf->ui->menu_5->menuAction()->setVisible(true);
        wf->ui->save_file->setVisible(true);
        wf->ui->save_as_file->setVisible(true);
        wf->ui->action_save_graph_file->setVisible(true);
        wf->ui->action_close_progect->setVisible(true);
        wf->ui->action_close_session->setVisible(true);
        wf->ui->print_file->setVisible(true);
        wf->ui->print_preview->setVisible(true);
        wf->ui->tabWidget->setTabVisible(1, false);
        wf->ui->tabWidget->setTabVisible(2, false);
        wf->ui->tabWidget->setTabVisible(3, false);
        wf->ui->tabWidget->setTabVisible(4, false);
        wf->ui->tabWidget->setTabVisible(6, false);
        wf->ui->tabWidget->setTabVisible(7, false);
        wf->ui->tabWidget->setTabVisible(8, false);

        if (wf->model_treeView) {
            // Получаем количество корневых узлов
            int rootCount = wf->model_treeView->rowCount();
            for (int i = rootCount - 1; i >= 0; --i)
            {
                QModelIndex rootIndex = wf->model_treeView->index(i, 0);
                QStandardItem *rootItem = wf->model_treeView->itemFromIndex(rootIndex);
                // Проверьте ваши условия для промежуточного узла (например, по типу, названиям и т.д.)
                if ((rootItem->text() == "Идентификация параметров схемы замещения")
                    ||(rootItem->text() == "Тепловая идентификация")
                    ||(rootItem->text() == "Вентиляционная идентификация")
                    ||(rootItem->text() == "Электромагнитная модель")
                    ||(rootItem->text() == "Вентиляционная модель")
                    ||(rootItem->text() == "Прогнозирование температур")
                    ||(rootItem->text() == "Оценка остаточного теплового ресурса"))
                {
                    wf->model_treeView->removeRow(i); // Удаляем узел
                }
            }
        }
    }

    if((x == 2) && (y == 2))
    {
        wf->ui->widget_15->hide();
        wf->ui->tabWidget->show();
        wf->ui->stackedWidget->show();
        wf->ui->switch_regim_upr->show();
        wf->ui->toolBar->show();
        wf->ui->toolBar_2->show();
        wf->ui->menu_2->menuAction()->setVisible(true);
        wf->ui->menu_3->menuAction()->setVisible(true);
        wf->ui->menu_4->menuAction()->setVisible(true);
        wf->ui->menu_5->menuAction()->setVisible(true);
        wf->ui->save_file->setVisible(true);
        wf->ui->save_as_file->setVisible(true);
        wf->ui->action_save_graph_file->setVisible(true);
        wf->ui->action_close_progect->setVisible(true);
        wf->ui->action_close_session->setVisible(true);
        wf->ui->print_file->setVisible(true);
        wf->ui->print_preview->setVisible(true);
        wf->ui->statusbar->show();
        wf->ui->tabWidget->setTabVisible(1, false);
        wf->ui->tabWidget->setTabVisible(2, false);
        wf->ui->tabWidget->setTabVisible(3, false);
        wf->ui->tabWidget->setTabVisible(4, false);
        wf->ui->tabWidget->setTabVisible(5, false);
        wf->ui->tabWidget->setTabVisible(7, false);
        wf->ui->tabWidget->setTabVisible(8, false);

        if (wf->model_treeView) {
            // Получаем количество корневых узлов
            int rootCount = wf->model_treeView->rowCount();
            for (int i = rootCount - 1; i >= 0; --i)
            {
                QModelIndex rootIndex = wf->model_treeView->index(i, 0);
                QStandardItem *rootItem = wf->model_treeView->itemFromIndex(rootIndex);
                // Проверьте ваши условия для промежуточного узла (например, по типу, названиям и т.д.)
                if ((rootItem->text() == "Идентификация параметров схемы замещения")
                    ||(rootItem->text() == "Тепловая идентификация")
                    ||(rootItem->text() == "Вентиляционная идентификация")
                    ||(rootItem->text() == "Электромагнитная модель")
                    ||(rootItem->text() == "Тепловая модель")
                    ||(rootItem->text() == "Прогнозирование температур")
                    ||(rootItem->text() == "Оценка остаточного теплового ресурса"))
                {
                    wf->model_treeView->removeRow(i); // Удаляем узел
                }
            }
        }
    }

    if((x == 2) && (y == 4))
    {
        wf->ui->widget_15->hide();
        wf->ui->tabWidget->show();
        wf->ui->stackedWidget->show();
        wf->ui->switch_regim_upr->show();
        wf->ui->toolBar->show();
        wf->ui->toolBar_2->show();
        wf->ui->menu_2->menuAction()->setVisible(true);
        wf->ui->menu_3->menuAction()->setVisible(true);
        wf->ui->menu_4->menuAction()->setVisible(true);
        wf->ui->menu_5->menuAction()->setVisible(true);
        wf->ui->save_file->setVisible(true);
        wf->ui->save_as_file->setVisible(true);
        wf->ui->action_save_graph_file->setVisible(true);
        wf->ui->action_close_progect->setVisible(true);
        wf->ui->action_close_session->setVisible(true);
        wf->ui->print_file->setVisible(true);
        wf->ui->print_preview->setVisible(true);
        wf->ui->statusbar->show();
        wf->ui->tabWidget->setTabVisible(1, false);
        wf->ui->tabWidget->setTabVisible(2, false);
        wf->ui->tabWidget->setTabVisible(3, false);
        wf->ui->tabWidget->setTabVisible(4, false);
        wf->ui->tabWidget->setTabVisible(5, false);
        wf->ui->tabWidget->setTabVisible(6, false);
        wf->ui->tabWidget->setTabVisible(8, false);

        if (wf->model_treeView) {
            // Получаем количество корневых узлов
            int rootCount = wf->model_treeView->rowCount();
            for (int i = rootCount - 1; i >= 0; --i)
            {
                QModelIndex rootIndex = wf->model_treeView->index(i, 0);
                QStandardItem *rootItem = wf->model_treeView->itemFromIndex(rootIndex);
                // Проверьте ваши условия для промежуточного узла (например, по типу, названиям и т.д.)
                if ((rootItem->text() == "Идентификация параметров схемы замещения")
                    ||(rootItem->text() == "Тепловая идентификация")
                    ||(rootItem->text() == "Вентиляционная идентификация")
                    ||(rootItem->text() == "Электромагнитная модель")
                    ||(rootItem->text() == "Тепловая модель")
                    ||(rootItem->text() == "Вентиляционная модель")
                    ||(rootItem->text() == "Оценка остаточного теплового ресурса"))
                {
                    wf->model_treeView->removeRow(i); // Удаляем узел
                }
            }
        }
    }

    if((x == 4) && (y == 0))
    {
        wf->ui->widget_15->hide();
        wf->ui->tabWidget->show();
        wf->ui->stackedWidget->show();
        wf->ui->switch_regim_upr->show();
        wf->ui->toolBar->show();
        wf->ui->toolBar_2->show();
        wf->ui->menu_2->menuAction()->setVisible(true);
        wf->ui->menu_3->menuAction()->setVisible(true);
        wf->ui->menu_4->menuAction()->setVisible(true);
        wf->ui->menu_5->menuAction()->setVisible(true);
        wf->ui->save_file->setVisible(true);
        wf->ui->save_as_file->setVisible(true);
        wf->ui->action_save_graph_file->setVisible(true);
        wf->ui->action_close_progect->setVisible(true);
        wf->ui->action_close_session->setVisible(true);
        wf->ui->print_file->setVisible(true);
        wf->ui->print_preview->setVisible(true);
        wf->ui->statusbar->show();
        wf->ui->tabWidget->setTabVisible(1, false);
        wf->ui->tabWidget->setTabVisible(2, false);
        wf->ui->tabWidget->setTabVisible(3, false);
        wf->ui->tabWidget->setTabVisible(4, false);
        wf->ui->tabWidget->setTabVisible(5, false);
        wf->ui->tabWidget->setTabVisible(6, false);
        wf->ui->tabWidget->setTabVisible(7, false);

        if (wf->model_treeView) {
            // Получаем количество корневых узлов
            int rootCount = wf->model_treeView->rowCount();
            for (int i = rootCount - 1; i >= 0; --i)
            {
                QModelIndex rootIndex = wf->model_treeView->index(i, 0);
                QStandardItem *rootItem = wf->model_treeView->itemFromIndex(rootIndex);
                // Проверьте ваши условия для промежуточного узла (например, по типу, названиям и т.д.)
                if ((rootItem->text() == "Идентификация параметров схемы замещения")
                    ||(rootItem->text() == "Тепловая идентификация")
                    ||(rootItem->text() == "Вентиляционная идентификация")
                    ||(rootItem->text() == "Электромагнитная модель")
                    ||(rootItem->text() == "Тепловая модель")
                    ||(rootItem->text() == "Вентиляционная модель")
                    ||(rootItem->text() == "Прогнозирование температур"))
                {
                    wf->model_treeView->removeRow(i); // Удаляем узел
                }
            }
        }
    }
}

void Start_app::resizeEvent(QResizeEvent *)
{
    for(int row = 0; row<ui->tableWidget_2->rowCount(); row++)
    {
        if ((row == 1) || (row == 3))
        {
            ui->tableWidget_2->setRowHeight(row, 30);
        }
        else
        {
            int max_height = (height() - 60 - ui->label_3->height() - ui->label_16->height() - 60) / 2;
            int height = ui->tableWidget_2->columnWidth(0);
            if (height > max_height)
            {
                height = max_height;
            }
            ui->tableWidget_2->setRowHeight(row, height);
        }
    }
}

void Start_app::openRecentFile(int row, int column)
{
    QString fileName = ui->tableWidget->item(row, column)->data(Qt::UserRole).toString();
    wf->loadFile(fileName);
    ui->tableWidget->clearSelection();
}

void Start_app::updateRecentFileActions()
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

    ui->tableWidget->setRowCount(numRecentFiles);

    for (int i = 0; i < numRecentFiles; ++i) {
        QString text = files[i];
        //recentFileActs[i]->setText(text);
        //recentFileActs[i]->setData(Qt::UserRole, files[i]);

        QString w1, w2;

        w1 = text;

        QDateTime currentDateTime = QDateTime::currentDateTime();
        QTime currentTime = currentDateTime.time();
        QDate currentDate = currentDateTime.date();

        w2 = QString("%1""%2""%3").arg("Сеанс ",currentTime.toString("hh:mm:ss ").toUtf8().data(),
                      currentDate.toString("dd.MM.yyyy").toUtf8().data());

        // svgwidget13 = new MySvgWidget();
        // svgwidget13->load(QString(":/system_icons/data/img/system_icons/IM_96x96.svg"));
        // svgwidget13->setMaximumSize(100,100);
        // ui->tableWidget->setCellWidget(i, 0, svgwidget13);
        // ui->tableWidget->resizeRowToContents(i);
        // ui->tableWidget->resizeColumnToContents(i);
        // ui->tableWidget->item(i, 1)->setText(QString("%1 \n %2").arg(w1, w2));
        // ui->tableWidget->item(i, 1)->setData(Qt::UserRole, text);

        svgwidget13 = new MySvgWidget();
        QWidget *widget13 = new QWidget();
        svgwidget13->svgFileName = ":/system_icons/data/img/system_icons/IM_96x96.svg";
        svgwidget13->svgSelectedFileName = ":/system_icons/data/img/system_icons/IM_96x96.svg";
        svgwidget13->loadFile();
        QHBoxLayout *layout = new QHBoxLayout(widget13);

        layout->addWidget(svgwidget13);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(0,0,0,0);

        ui->tableWidget->setRowHeight(i,100);
        ui->tableWidget->setCellWidget(i, 0, svgwidget13);
        ui->tableWidget->item(i, 1)->setText(QString("%1 \n %2").arg(w1, w2));
        ui->tableWidget->item(i, 1)->setData(Qt::UserRole, text);

        // svgwidget4 = new MySvgWidget();
        // QWidget *widget3 = new QWidget();
        // svgwidget4->svgFileName = "/home/elf/ImView2/data/img/system_icons/IM_96x96_elm.svg";
        // svgwidget4->svgSelectedFileName = "/home/elf/ImView2/data/img/system_icons/IM_96x96_elm_select.svg";
        // svgwidget4->loadFile();
        // QHBoxLayout *layout3 = new QHBoxLayout(widget3);
        // layout3->addWidget(svgwidget4);
        // layout3->setAlignment(Qt::AlignCenter);
        // layout3->setContentsMargins(0,0,0,0);
        // ui->tableWidget_2->setCellWidget(0, 4, widget3);
        // ui->tableWidget_2->item(1, 4)->setTextAlignment(Qt::AlignCenter);
    }
}

QString Start_app::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void Start_app::showEvent(QShowEvent *)
{
    updateRecentFileActions();
}

void Start_app::click_open_help()
{
    wf->actionhelp();
}

void Start_app::click_open_metod_one()
{
    view = new QWebEngineView;
    connect(view, &QWebEngineView::titleChanged, this, &Start_app::titleChanged);
    view->setUrl(QUrl::fromLocalFile(QFileInfo("../Study_matireals/osnovi_raboty.html").absoluteFilePath()));
    view->setWindowIcon(QIcon("/home/elf/ImView2/data/img/icons/IM_16x16.png"));
    view->showMaximized();
}

void Start_app::click_open_metod_two()
{
    view = new QWebEngineView;
    connect(view, &QWebEngineView::titleChanged, this, &Start_app::titleChanged);
    view->setUrl(QUrl::fromLocalFile(QFileInfo("../Study_matireals/nastroika_sessii.html").absoluteFilePath()));
    view->setWindowIcon(QIcon("/home/elf/ImView2/data/img/icons/IM_16x16.png"));
    view->showMaximized();
}

void Start_app::click_open_metod_three()
{
    view = new QWebEngineView;
    connect(view, &QWebEngineView::titleChanged, this, &Start_app::titleChanged);
    view->setUrl(QUrl::fromLocalFile(QFileInfo("../Study_matireals/vvod_ischdnich_dannich.html").absoluteFilePath()));
    view->setWindowIcon(QIcon("/home/elf/ImView2/data/img/icons/IM_16x16.png"));
    view->showMaximized();
}

void Start_app::click_open_metod_four()
{
    view = new QWebEngineView;
    connect(view, &QWebEngineView::titleChanged, this, &Start_app::titleChanged);
    view->setUrl(QUrl::fromLocalFile(QFileInfo("../Study_matireals/identf_param_scheme_zam_ad.html").absoluteFilePath()));
    view->setWindowIcon(QIcon("/home/elf/ImView2/data/img/icons/IM_16x16.png"));
    view->showMaximized();
}

void Start_app::click_open_metod_five()
{
    view = new QWebEngineView;
    connect(view, &QWebEngineView::titleChanged, this, &Start_app::titleChanged);
    view->setUrl(QUrl::fromLocalFile(QFileInfo("../Study_matireals/energetik_model_ad.html").absoluteFilePath()));
    view->setWindowIcon(QIcon("/home/elf/ImView2/data/img/icons/IM_16x16.png"));
    view->showMaximized();
}

void Start_app::click_open_metod_six()
{
    view = new QWebEngineView;
    connect(view, &QWebEngineView::titleChanged, this, &Start_app::titleChanged);
    view->setUrl(QUrl::fromLocalFile(QFileInfo("../Study_matireals/tepl_model_ad.html").absoluteFilePath()));
    view->setWindowIcon(QIcon("/home/elf/ImView2/data/img/icons/IM_16x16.png"));
    view->showMaximized();
}

void Start_app::click_open_metod_seven()
{
    view = new QWebEngineView;
    connect(view, &QWebEngineView::titleChanged, this, &Start_app::titleChanged);
    view->setUrl(QUrl::fromLocalFile(QFileInfo("../Study_matireals/vent_model_ad.html").absoluteFilePath()));
    view->setWindowIcon(QIcon("/home/elf/ImView2/data/img/icons/IM_16x16.png"));
    view->showMaximized();
}

void Start_app::click_open_metod_eight()
{
    view = new QWebEngineView;
    connect(view, &QWebEngineView::titleChanged, this, &Start_app::titleChanged);
    view->setUrl(QUrl::fromLocalFile(QFileInfo("../Study_matireals/teplovent_model_ad.html").absoluteFilePath()));
    view->setWindowIcon(QIcon("/home/elf/ImView2/data/img/icons/IM_16x16.png"));
    view->showMaximized();
}

void Start_app::click_open_metod_nine()
{
    view = new QWebEngineView;
    connect(view, &QWebEngineView::titleChanged, this, &Start_app::titleChanged);
    view->setUrl(QUrl::fromLocalFile(QFileInfo("../Study_matireals/temp_prognoz_ad.html").absoluteFilePath()));
    view->setWindowIcon(QIcon("/home/elf/ImView2/data/img/icons/IM_16x16.png"));
    view->showMaximized();
}

void Start_app::click_open_metod_ten()
{
    view = new QWebEngineView;
    connect(view, &QWebEngineView::titleChanged, this, &Start_app::titleChanged);
    view->setUrl(QUrl::fromLocalFile(QFileInfo("../Study_matireals/tepl_observer.html").absoluteFilePath()));
    view->setWindowIcon(QIcon("/home/elf/ImView2/data/img/icons/IM_16x16.png"));
    view->showMaximized();
}

void Start_app::click_open_metod_eleven()
{
    view = new QWebEngineView;
    connect(view, &QWebEngineView::titleChanged, this, &Start_app::titleChanged);
    view->setUrl(QUrl::fromLocalFile(QFileInfo("../Study_matireals/ostat_tepl_resurs.html").absoluteFilePath()));
    view->setWindowIcon(QIcon("/home/elf/ImView2/data/img/icons/IM_16x16.png"));
    view->showMaximized();
}

void Start_app::click_open_metod_twelv()
{
    view = new QWebEngineView;
    connect(view, &QWebEngineView::titleChanged, this, &Start_app::titleChanged);
    view->setUrl(QUrl::fromLocalFile(QFileInfo("../Study_matireals/otchet.html").absoluteFilePath()));
    view->setWindowIcon(QIcon("/home/elf/ImView2/data/img/icons/IM_16x16.png"));
    view->showMaximized();
}

void Start_app::titleChanged(const QString &title)
{
    view->setWindowTitle(title);
}

void Start_app::selectImage()
{

}
