#include "nastroiki.h"
#include "ui_nastroiki.h"
#include "QSettings"
#include "mainwindow.h"


Nastroiki::Nastroiki(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Nastroiki)
{
    wf = (MainWindow*)parent;
    ui->setupUi(this);
    QListWidgetItem *item_1=new QListWidgetItem(QIcon(":/system_icons/data/img/system_icons/folder.svg"), "Интерфейс");
    ui->listWidget->addItem(item_1);
    QListWidgetItem *item_2=new QListWidgetItem(QIcon(":/system_icons/data/img/system_icons/labplot-axis-vertical.svg"), "Исходные данные");
    ui->listWidget->addItem(item_2);
    QListWidgetItem *item_3=new QListWidgetItem(QIcon(":/system_icons/data/img/system_icons/labplot-matrix-new.svg"), "Идентификация параметров");
    ui->listWidget->addItem(item_3);
    QListWidgetItem *item_4=new QListWidgetItem(QIcon(":/system_icons/data/img/system_icons/labplot-xy-interpolation-curve.svg"), "Энергетические показатели");
    ui->listWidget->addItem(item_4);
    QListWidgetItem *item_5=new QListWidgetItem(QIcon(":/system_icons/data/img/system_icons/labplot-zoom-out-y.svg"), "Тепловентиляция");
    ui->listWidget->addItem(item_5);
    QListWidgetItem *item_6=new QListWidgetItem(QIcon(":/system_icons/data/img/system_icons/map-flat.svg"), "Выходные данные");
    ui->listWidget->addItem(item_6);

    QModelIndex firstRow = ui->listWidget->model()->index(0, 0);
    ui->listWidget->selectionModel()->select(firstRow,
                                             QItemSelectionModel::ClearAndSelect |
                                                 QItemSelectionModel::Rows);

    ui->listWidget->setFocus();

    connect(ui->listWidget, &QListWidget::itemSelectionChanged, this, &Nastroiki::on_listWidget_itemSelectionChanged);


    ui->stackedWidget->setCurrentIndex(0);
    ui->comboBox->addItem(tr("Русский язык"));
    ui->comboBox->addItem(tr("English language"));

    ui->comboBox_2->addItem(tr("Фиксированные сообщения"));
    ui->comboBox_2->addItem(tr("Всплывающие сообщения"));

  /*  connect(ui->comboBox, QOverload<const QString &>::of(&QComboBox::currentIndexChanged),
            [=](const QString &text){ wf->translator(); });*/

    connect(ui->comboBox,&QComboBox::currentIndexChanged,this, &Nastroiki::translator);

        connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [=](int index){ ui->pushButton_2->setEnabled(true); });

    QSettings settings( "BRU", "IM View");
    settings.beginGroup( "language interface" );
    QString lokal = settings.value( "QtLanguage_", "").toString();
    settings.endGroup();

    if(lokal == "ru_RU")
    {
        ui->comboBox->setCurrentIndex(0);
    }
    else if(lokal == "en_US")
    {
        ui->comboBox->setCurrentIndex(1);
    }

   // QSettings settings( "BRU", "IM View");
    settings.beginGroup( "System_messages" );
    QString message = settings.value( "Messages", "").toString();
    settings.endGroup();

    if(message == "fix")
    {
        ui->comboBox_2->setCurrentIndex(0);
    }
    else if(message == "nonfix")
    {
        ui->comboBox_2->setCurrentIndex(1);
    }
}

Nastroiki::~Nastroiki()
{
    delete ui;
}

void Nastroiki::on_pushButton_clicked()
{

    if(ui->comboBox->currentText() == "Русский язык")
    {
        ui->comboBox->setCurrentIndex(0);
        wf->translate_ru();
        QSettings settings( "BRU", "IM View");
        settings.beginGroup( "language interface" );
        settings.setValue( "QtLanguage_", "ru_RU");
        settings.endGroup();
    }
    else if(ui->comboBox->currentText()  == "English language")
    {
        ui->comboBox->setCurrentIndex(1);
        wf->translate_en();
        QSettings settings( "BRU", "IM View");
        settings.beginGroup( "language interface" );
        settings.setValue( "QtLanguage_", "en_US");
        settings.endGroup();
    }

    if(ui->comboBox_2->currentText() == "Фиксированные сообщения")
    {
        ui->comboBox_2->setCurrentIndex(0);
        QSettings settings( "BRU", "IM View");
        settings.beginGroup( "System_messages" );
        settings.setValue( "Messages", "fix");
        settings.endGroup();
    }
    else if(ui->comboBox_2->currentText()  == "Всплывающие сообщения")
    {
        ui->comboBox_2->setCurrentIndex(1);
        wf->translate_en();
        QSettings settings( "BRU", "IM View");
        settings.beginGroup( "System_messages" );
        settings.setValue( "Messages", "nonfix");
        settings.endGroup();
    }
    close();
}

void Nastroiki::on_pushButton_2_clicked()
{
    if(ui->comboBox->currentText() == "Русский язык")
    {
        ui->comboBox->setCurrentIndex(0);
        wf->translate_ru();
        QSettings settings( "BRU", "IM View");
        settings.beginGroup( "language interface" );
        settings.setValue( "QtLanguage_", "ru_RU");
        settings.endGroup();
    }
    else if(ui->comboBox->currentText()  == "English language")
    {
        ui->comboBox->setCurrentIndex(1);
        wf->translate_en();
        QSettings settings( "BRU", "IM View");
        settings.beginGroup( "language interface" );
        settings.setValue( "QtLanguage_", "en_US");
        settings.endGroup();
    }

    if(ui->comboBox_2->currentText() == "Фиксированные сообщения")
    {
        ui->comboBox_2->setCurrentIndex(0);
        QSettings settings( "BRU", "IM View");
        settings.beginGroup( "System_messages" );
        settings.setValue( "Messages", "fix");
        settings.endGroup();
    }
    else if(ui->comboBox_2->currentText()  == "Всплывающие сообщения")
    {
        ui->comboBox_2->setCurrentIndex(1);
        wf->translate_en();
        QSettings settings( "BRU", "IM View");
        settings.beginGroup( "System_messages" );
        settings.setValue( "Messages", "nonfix");
        settings.endGroup();
    }
    ui->pushButton_2->setEnabled(false);
}

void Nastroiki::on_pushButton_3_clicked()
{
    close();
}

void Nastroiki::on_listWidget_itemSelectionChanged()
{
    ui->stackedWidget->setCurrentIndex(ui->listWidget->currentRow());
}

void Nastroiki::translator()
{
    wf->translator();
}
