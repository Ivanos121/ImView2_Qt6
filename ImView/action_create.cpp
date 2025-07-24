#include "action_create.h"
#include "ui_action_create.h"
#include "ui_mainwindow.h"

Action_create::Action_create(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Action_create)
{
    ui->setupUi(this);

    connect(ui->action_close, &QPushButton::clicked, this, &Action_create::Action_closes);
    ui->tableWidget->setRowCount(6);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView :: NoSelection);
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setShowGrid(false);
    ui->tableWidget->clearFocus();

    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget->columnCount(); column++)
        {
            ui->tableWidget->setItem(row, column, new QTableWidgetItem());
        }
    }

    for (int i=0; i<ui->tableWidget->columnCount(); i++)
    {
        if (ui->tableWidget->item(1, i) != 0)
        {
            ui->tableWidget->item(1, i)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->item(1, i)->setTextAlignment(Qt::AlignVCenter);
        }
        if (ui->tableWidget->item(3, i) != 0)
        {
            ui->tableWidget->item(3, i)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->item(3, i)->setTextAlignment(Qt::AlignVCenter);
        }
    }

    ui->tableWidget->setItem(1, 0, new QTableWidgetItem("Создание нового сеанса"));
    ui->tableWidget->setItem(1, 2, new QTableWidgetItem("Идентификация \n данных"));
    ui->tableWidget->setItem(1, 4, new QTableWidgetItem("Электромагнитная \n модель"));
    ui->tableWidget->setItem(3, 0, new QTableWidgetItem("Тепловая модель"));
    ui->tableWidget->setItem(3, 2, new QTableWidgetItem("Вентиляционная модель"));
    ui->tableWidget->setItem(3, 4, new QTableWidgetItem("Прогноз температур"));
    ui->tableWidget->setItem(5, 0, new QTableWidgetItem("Остаточный \n тепловой \n ресурс"));
    ui->tableWidget->clearSelection();

    svgwidget = new MySvgWidget();
    QWidget *widget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->addWidget(svgwidget);
    svgwidget->svgFileName = ":/system_icons/data/img/system_icons/IM_96x96_ns.svg";
    svgwidget->svgSelectedFileName = ":/system_icons/data/img/system_icons/IM_96x96_ns_select.svg";
    svgwidget->loadFile();
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(0,0,0,0);
    ui->tableWidget->setCellWidget(0, 0, widget);
    ui->tableWidget->item(1, 0)->setTextAlignment(Qt::AlignCenter);

    svgwidget2 = new MySvgWidget();
    QWidget *widget2 = new QWidget();
    svgwidget2->svgFileName = ":/system_icons/data/img/system_icons/IM_96x96_id.svg";
    svgwidget2->svgSelectedFileName = ":/system_icons/data/img/system_icons/IM_96x96_id_select.svg";
    svgwidget2->loadFile();
    QHBoxLayout *layout2 = new QHBoxLayout(widget2);
    layout2->addWidget(svgwidget2);
    layout2->setAlignment(Qt::AlignCenter);
    layout2->setContentsMargins(0,0,0,0);
    ui->tableWidget->setCellWidget(0, 2, widget2);
    ui->tableWidget->item(1, 2)->setTextAlignment(Qt::AlignCenter);

    svgwidget3 = new MySvgWidget();
    QWidget *widget3 = new QWidget();
    svgwidget3->svgFileName = ":/system_icons/data/img/system_icons/IM_96x96_elm.svg";
    svgwidget3->svgSelectedFileName = ":/system_icons/data/img/system_icons/IM_96x96_elm_select.svg";
    svgwidget3->loadFile();
    QHBoxLayout *layout3 = new QHBoxLayout(widget3);
    layout3->addWidget(svgwidget3);
    layout3->setAlignment(Qt::AlignCenter);
    layout3->setContentsMargins(0,0,0,0);
    ui->tableWidget->setCellWidget(0, 4, widget3);
    ui->tableWidget->item(1, 4)->setTextAlignment(Qt::AlignCenter);

    svgwidget4 = new MySvgWidget();
    QWidget *widget4 = new QWidget();
    svgwidget4->svgFileName = ":/system_icons/data/img/system_icons/IM_96x96_tm.svg";
    svgwidget4->svgSelectedFileName = ":/system_icons/data/img/system_icons/IM_96x96_tm_select.svg";
    svgwidget4->loadFile();
    QHBoxLayout *layout4 = new QHBoxLayout(widget4);
    layout4->addWidget(svgwidget4);
    layout4->setAlignment(Qt::AlignCenter);
    layout4->setContentsMargins(0,0,0,0);
    ui->tableWidget->setCellWidget(2, 0, widget4);
    ui->tableWidget->item(3, 0)->setTextAlignment(Qt::AlignCenter);

    svgwidget5 = new MySvgWidget();
    QWidget *widget5 = new QWidget();
    svgwidget5->svgFileName = ":/system_icons/data/img/system_icons/IM_96x96_vm.svg";
    svgwidget5->svgSelectedFileName = ":/system_icons/data/img/system_icons/IM_96x96_vm_select.svg";
    svgwidget5->loadFile();
    QHBoxLayout *layout5 = new QHBoxLayout(widget5);
    layout5->addWidget(svgwidget5);
    layout5->setAlignment(Qt::AlignCenter);
    layout5->setContentsMargins(0,0,0,0);
    ui->tableWidget->setCellWidget(2, 2, widget5);
    ui->tableWidget->item(3, 2)->setTextAlignment(Qt::AlignCenter);

    svgwidget6 = new MySvgWidget();
    QWidget *widget6 = new QWidget();
    svgwidget6->svgFileName = ":/system_icons/data/img/system_icons/IM_96x96_pt.svg";
    svgwidget6->svgSelectedFileName = ":/system_icons/data/img/system_icons/IM_96x96_pt_select.svg";
    svgwidget6->loadFile();
    QHBoxLayout *layout6 = new QHBoxLayout(widget6);
    layout6->addWidget(svgwidget6);
    layout6->setAlignment(Qt::AlignCenter);
    layout6->setContentsMargins(0,0,0,0);
    ui->tableWidget->setCellWidget(2, 4, widget6);
    ui->tableWidget->item(3, 4)->setTextAlignment(Qt::AlignCenter);

    svgwidget7 = new MySvgWidget();
    QWidget *widget7 = new QWidget();
    svgwidget7->svgFileName = ":/system_icons/data/img/system_icons/IM_96x96_otr.svg";
    svgwidget7->svgSelectedFileName = ":/system_icons/data/img/system_icons/IM_96x96_otr_select.svg";
    svgwidget7->loadFile();
    QHBoxLayout *layout7 = new QHBoxLayout(widget7);
    layout7->addWidget(svgwidget7);
    layout7->setAlignment(Qt::AlignCenter);
    layout7->setContentsMargins(0,0,0,0);
    ui->tableWidget->setCellWidget(4, 0, widget7);
    ui->tableWidget->item(5, 0)->setTextAlignment(Qt::AlignCenter);

    QPalette palette = ui->tableWidget->palette();
    palette.setBrush(QPalette::Highlight,QBrush(QColor(239, 240, 241)));
    palette.setBrush(QPalette::HighlightedText,QBrush(Qt::black));
    ui->tableWidget->setPalette(palette);

    connect(ui->tableWidget,&QAbstractItemView::clicked,this,&Action_create::click_open_progect);
}

Action_create::~Action_create()
{
    delete ui;
}

void Action_create::Action_closes()
{
    close();
}

void Action_create::click_open_progect(const QModelIndex& idx)
{
    done(QDialog::Accepted);
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
