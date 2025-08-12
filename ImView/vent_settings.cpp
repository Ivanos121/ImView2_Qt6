#include <QFileInfo>
#include <QMessageBox>
#include <QUrl>

#include "vent_settings.h"
#include "ui_vent_settings.h"
#include "vent_datas.h"
#include "Base_tepl_vent.h"

Vent_settings::Vent_settings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Vent_settings)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked, this, &Vent_settings::apply_vent_dannie);
    connect(ui->pushButton_2,&QPushButton::clicked, this, &Vent_settings::close_vent_dannie);

    ui->tableWidget->setRowCount(16);
    ui->tableWidget->setColumnCount(4);
    QStringList name;
    name << "Величина" << "Обозначение" << "Значение" << "Размерность";
    ui->tableWidget->setHorizontalHeaderLabels(name);
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget->verticalHeader()->setVisible(true);
    //ui->tableWidget->resizeColumnToContents(0);

    // Для первого столбца — подгонка по содержимому
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    // Для остальных — растягивание
    for (int i = 1; i < ui->tableWidget->columnCount(); ++i) {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }


    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget->columnCount(); column++)
        {
            ui->tableWidget->setItem(row, column, new QTableWidgetItem());

        }
    }

    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("Марка двигателя"));
    ui->tableWidget->setItem(1, 0, new QTableWidgetItem("Внутренний расчетный диаметр вентилятора"));
    ui->tableWidget->setItem(2, 0, new QTableWidgetItem("Внешний расчетный диаметр вентилятора"));
    ui->tableWidget->setItem(3, 0, new QTableWidgetItem("Ширина лопатки вентилятора"));
    ui->tableWidget->setItem(4, 0, new QTableWidgetItem("Частота вращения вентилятора"));
    ui->tableWidget->setItem(5, 0, new QTableWidgetItem("Плотность воздуха"));
    ui->tableWidget->setItem(6, 0, new QTableWidgetItem("Суммарная площадь отверстий в сетке кожуха"));
    ui->tableWidget->setItem(7, 0, new QTableWidgetItem("Общая площадь сетки кожуха"));
    ui->tableWidget->setItem(8, 0, new QTableWidgetItem("Площадь сечения в месте поворота к рабочему колесу"));
    ui->tableWidget->setItem(9, 0, new QTableWidgetItem("Угол поворота потока к входным кромкам лопаток рабочего колеса"));
    ui->tableWidget->setItem(10, 0, new QTableWidgetItem("Площадь сечения в месте поворота перед входом в межреберные каналы"));
    ui->tableWidget->setItem(11, 0, new QTableWidgetItem("Угол поворота потока перед входом в межреберные каналы"));
    ui->tableWidget->setItem(12, 0, new QTableWidgetItem("Площадь сечения перед входом в межреберные каналы"));
    ui->tableWidget->setItem(13, 0, new QTableWidgetItem("Площадь сечения межреберных каналов от станины до кожуха вентилятора"));
    ui->tableWidget->setItem(14, 0, new QTableWidgetItem("Угол натекания потока на ребра станины"));
    ui->tableWidget->setItem(15, 0, new QTableWidgetItem("Угол поворота потока в межреберных каналах"));

    ui->tableWidget->setItem(0, 1, new QTableWidgetItem("name"));
    ui->tableWidget->setItem(1, 1, new QTableWidgetItem("D1р"));
    ui->tableWidget->setItem(2, 1, new QTableWidgetItem("D2р"));
    ui->tableWidget->setItem(3, 1, new QTableWidgetItem("b"));
    ui->tableWidget->setItem(4, 1, new QTableWidgetItem("n"));
    ui->tableWidget->setItem(5, 1, new QTableWidgetItem("ro"));
    ui->tableWidget->setItem(6, 1, new QTableWidgetItem("Sotv"));
    ui->tableWidget->setItem(7, 1, new QTableWidgetItem("S0"));
    ui->tableWidget->setItem(8, 1, new QTableWidgetItem("S1"));
    ui->tableWidget->setItem(9, 1, new QTableWidgetItem("α1"));
    ui->tableWidget->setItem(10, 1, new QTableWidgetItem("S2"));
    ui->tableWidget->setItem(11, 1, new QTableWidgetItem("α2"));
    ui->tableWidget->setItem(12, 1, new QTableWidgetItem("S3"));
    ui->tableWidget->setItem(13, 1, new QTableWidgetItem("S4"));
    ui->tableWidget->setItem(14, 1, new QTableWidgetItem("φ"));
    ui->tableWidget->setItem(15, 1, new QTableWidgetItem("φ2"));

    ui->tableWidget->setItem(0, 3, new QTableWidgetItem("м"));
    ui->tableWidget->setItem(1, 3, new QTableWidgetItem("м"));
    ui->tableWidget->setItem(2, 3, new QTableWidgetItem("м"));
    ui->tableWidget->setItem(3, 3, new QTableWidgetItem("м"));
    ui->tableWidget->setItem(4, 3, new QTableWidgetItem("об/мин"));
    ui->tableWidget->setItem(5, 3, new QTableWidgetItem("кг/м³"));
    ui->tableWidget->setItem(6, 3, new QTableWidgetItem("м²"));
    ui->tableWidget->setItem(7, 3, new QTableWidgetItem("м²"));
    ui->tableWidget->setItem(8, 3, new QTableWidgetItem("м²"));
    ui->tableWidget->setItem(9, 3, new QTableWidgetItem("град."));
    ui->tableWidget->setItem(10, 3, new QTableWidgetItem("град."));
    ui->tableWidget->setItem(11, 3, new QTableWidgetItem("alpha2"));
    ui->tableWidget->setItem(12, 3, new QTableWidgetItem("м²"));
    ui->tableWidget->setItem(13, 3, new QTableWidgetItem("м²"));
    ui->tableWidget->setItem(14, 3, new QTableWidgetItem("град."));
    ui->tableWidget->setItem(15, 3, new QTableWidgetItem("град."));

    for (int i=0; i<ui->tableWidget->rowCount(); i++)
    {

        if (ui->tableWidget->item(i, 1) != 0)
        {
            ui->tableWidget->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget->item(i, 3) != 0)
        {
            ui->tableWidget->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }

    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
    {
        if (ui->tableWidget->item(row,0) != 0)
        {
            ui->tableWidget->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget->item(row,1) != 0)
        {
            ui->tableWidget->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget->item(row,2) != 0)
        {
            ui->tableWidget->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget->item(row,2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget->item(row,3) != 0)
        {
            ui->tableWidget->item(row,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
    }

    // Расчет общей высоты строк
    int totalHeight = ui->tableWidget->horizontalHeader()->height(); // высота заголовка
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        totalHeight += ui->tableWidget->rowHeight(row);
    }

    // Установка фиксированной высоты таблицы
    ui->tableWidget->setFixedHeight(totalHeight+20);

    QPalette p_13=ui->tableWidget->palette();
    p_13.setColor(QPalette::Base, QColor(255, 255, 191));
    p_13.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget->setPalette(p_13);
    ui->label->setStyleSheet("background-color: white;");




    connect(ui->tableWidget, &QTableWidget::cellClicked, this, &Vent_settings::onCellClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Vent_settings::button_close);
    connect(ui->pushButton, &QPushButton::clicked, this, &Vent_settings::button_apply);
}

Vent_settings::~Vent_settings()
{
    delete ui;
}

void Vent_settings::apply_vent_dannie()
{
    ventparam.name = ui->tableWidget->item(0,2)->text();
    ventparam.d1p = ui->tableWidget->item(1,2)->text().toDouble();
    ventparam.d2p = ui->tableWidget->item(2,2)->text().toDouble();
    ventparam.b = ui->tableWidget->item(3,2)->text().toDouble();
    ventparam.n = ui->tableWidget->item(4,2)->text().toDouble();
    ventparam.ro = ui->tableWidget->item(5,2)->text().toDouble();
    ventparam.sotv = ui->tableWidget->item(6,2)->text().toDouble();
    ventparam.s0 = ui->tableWidget->item(7,2)->text().toDouble();
    ventparam.s1 = ui->tableWidget->item(8,2)->text().toDouble();
    ventparam.a1 = ui->tableWidget->item(9,2)->text().toDouble();
    ventparam.s2 = ui->tableWidget->item(10,2)->text().toDouble();
    ventparam.a2 = ui->tableWidget->item(11,2)->text().toDouble();
    ventparam.s3 = ui->tableWidget->item(12,2)->text().toDouble();
    ventparam.s4 = ui->tableWidget->item(13,2)->text().toDouble();
    ventparam.fi = ui->tableWidget->item(14,2)->text().toDouble();
    ventparam.fi2 = ui->tableWidget->item(15,2)->text().toDouble();


    if(ui->tableWidget->item(0,2)->text().isEmpty()||
        ui->tableWidget->item(1,2)->text().isEmpty()||
        ui->tableWidget->item(2,2)->text().isEmpty()||
        ui->tableWidget->item(3,2)->text().isEmpty()||
        ui->tableWidget->item(4,2)->text().isEmpty()||
        ui->tableWidget->item(5,2)->text().isEmpty()||
        ui->tableWidget->item(6,2)->text().isEmpty()||
        ui->tableWidget->item(7,2)->text().isEmpty()||
        ui->tableWidget->item(8,2)->text().isEmpty()||
        ui->tableWidget->item(9,2)->text().isEmpty()||
        ui->tableWidget->item(10,2)->text().isEmpty()||
        ui->tableWidget->item(11,2)->text().isEmpty()||
        ui->tableWidget->item(12,2)->text().isEmpty()||
        ui->tableWidget->item(13,2)->text().isEmpty()||
        ui->tableWidget->item(14,2)->text().isEmpty()||
        ui->tableWidget->item(15,2)->text().isEmpty())
    {
        QMessageBox::critical(this, "Ошибка!", "Заполните пустые поля");
    }
    else
    {
        wf->zapis();
        wf->table();
        close();
    }
}

void Vent_settings::close_vent_dannie()
{
    close();
}

void Vent_settings::onCellClicked(int row, int column)
{
    if (column != 2)
        return;

    QString imagePath;

    if (row == 0)        {
        //imagePath = ":/image/data/img/images/vent_settings_1.svg";
        imagePath = "/home/elf/ImView2_Qt6/data/img/images/vent_settings_1.svg";
    } else if (row == 1) {
        //imagePath = basePath + "/ввв.jpg"; // замените на свой путь
        imagePath = "/home/elf/ImView2_Qt6/data/img/images/vent_settings_2.svg";
    } else if (row == 2) {
        //imagePath = basePath + "/дддд.jpg"; // замените на свой путь
        imagePath = "/home/elf/ImView2_Qt6/data/img/images/vent_settings_3.svg";
    } else if (row == 3) {
        //imagePath = basePath + "/tery3b.jpg"; // замените на свой путь
        imagePath = "/home/elf/ImView2_Qt6/data/img/images/vent_settings_4.svg";
    } else if (row == 4) {
        //imagePath = ":/image/data/img/images/vent_settings_1.svg";
        imagePath = "/home/elf/ImView2_Qt6/data/img/images/vent_settings_5.svg";
    } else if (row == 5) {
        //imagePath = basePath + "/ввв.jpg"; // замените на свой путь
        imagePath = "/home/elf/ImView2_Qt6/data/img/images/vent_settings_6.svg";
    } else if (row == 6) {
        //imagePath = basePath + "/дддд.jpg"; // замените на свой путь
        imagePath = "/home/elf/ImView2_Qt6/data/img/images/vent_settings_7.svg";
    } else if (row == 7) {
        //imagePath = basePath + "/tery3b.jpg"; // замените на свой путь
        imagePath = "/home/elf/ImView2_Qt6/data/img/images/vent_settings_8.svg";
    } else if (row == 8) {
        //imagePath = basePath + "/ввв.jpg"; // замените на свой путь
        imagePath = "/home/elf/ImView2_Qt6/data/img/images/vent_settings_9.svg";
    } else if (row == 9) {
        //imagePath = basePath + "/дддд.jpg"; // замените на свой путь
        imagePath = "/home/elf/ImView2_Qt6/data/img/images/vent_settings_10.svg";
    } else if (row == 10) {
        //imagePath = basePath + "/tery3b.jpg"; // замените на свой путь
        imagePath = "/home/elf/ImView2_Qt6/data/img/images/vent_settings_11.svg";
    } else if (row == 11) {
        //imagePath = ":/image/data/img/images/vent_settings_1.svg";
        imagePath = "/home/elf/ImView2_Qt6/data/img/images/vent_settings_12.svg";
    } else if (row == 12) {
        //imagePath = basePath + "/ввв.jpg"; // замените на свой путь
        imagePath = "/home/elf/ImView2_Qt6/data/img/images/vent_settings_13.svg";
    } else if (row == 13) {
        //imagePath = basePath + "/дддд.jpg"; // замените на свой путь
        imagePath = "/home/elf/ImView2_Qt6/data/img/images/vent_settings_14.svg";
    } else if (row == 14) {
        //imagePath = basePath + "/tery3b.jpg"; // замените на свой путь
        imagePath = "/home/elf/ImView2_Qt6/data/img/images/vent_settings_15.svg";
    } /*else if (row == 15) {
        //imagePath = basePath + "/дддд.jpg"; // замените на свой путь
        imagePath = "/home/elf/ImView2_Qt6/data/img/images/vent_settings_16.svg";
    }*/ else {
        return; // если строка не ожидается
    }

    // Проверьте существование файла перед отображением
    QFileInfo checkFile(imagePath);
    if (!checkFile.exists() || !checkFile.isFile()) {
        qDebug() << "Файл не найден:" << imagePath;
        return;
    }

    QPixmap pixmap(imagePath);
    if (!pixmap.isNull())
    {
        ui->label->setPixmap(pixmap);
        ui->label->setScaledContents(true); // чтобы картинка подгонялась под размер QLabel
    } else
    {
        // Обработка ошибки: изображение не найдено или не загружено
        ui->label->clear();
    }
}

void Vent_settings::button_close()
{
    close();
}

void Vent_settings::button_apply()
{

}
