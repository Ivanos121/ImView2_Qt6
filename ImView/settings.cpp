#include "settings.h"
//#include "qtranslator.h"
#include "ui_settings.h"

Ksettings::Ksettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ksettings)
{
    ui->setupUi(this);

    ui->stackedWidget->addWidget(ui->comboBox);
    ui->stackedWidget->setCurrentIndex(0);
    ui->comboBox->addItem(tr("Русский язык"));
    ui->comboBox->addItem(tr("English language"));
    ui->comboBox->setCurrentIndex(1);

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

    connect(ui->listWidget, &QListWidget::itemSelectionChanged, this, &Ksettings::onlistWidget_itemSelectionChanged);

    //QTranslator *qtLanguageTranslator = nullptr ;
    ui->stackedWidget->setCurrentIndex(0);
    ui->comboBox->addItem(tr("Русский язык"));
    ui->comboBox->addItem(tr("English language"));
    ui->comboBox_2->addItem(tr("Фиксированные сообщения"));
    ui->comboBox_2->addItem(tr("Всплывающие сообщения"));
    // ui->comboBox->setCurrentIndex(0);

    /*connect(ui->comboBox, QOverload<const QString &>::of(&QComboBox::currentIndexChanged),
            [=](const QString &text){
                qtLanguageTranslator->load("QtLanguage_" + text, ".");   // Загружаем перевод
                qApp->installTranslator(qtLanguageTranslator);        // Устанавливаем перевод в приложение
            });*/

    // connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
    //         [=](int index){ ui->pushButton_2->setEnabled(true); });

}

Ksettings::~Ksettings()
{
    delete ui;
}

void Ksettings::on_pushButton_clicked()
{

}

void Ksettings::onlistWidget_itemSelectionChanged()
{
    ui->stackedWidget->setCurrentIndex(ui->listWidget->currentRow());
}
