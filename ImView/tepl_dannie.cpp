#include "tepl_dannie.h"
#include "customhelpdelegate.h"
#include "ui_tepl_dannie.h"

Tepl_dannie::Tepl_dannie(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tepl_dannie)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(76);
    ui->tableWidget->setColumnCount(6);
    QStringList name;
    name << "Свойство" << "Значение" << "Свойство" << "Значение"<< "Свойство" << "Значение";
    ui->tableWidget->setHorizontalHeaderLabels(name);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget->verticalHeader()->setVisible(true);
    ui->tableWidget->resizeColumnsToContents();
    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget->columnCount(); column++)
        {
            ui->tableWidget->setItem(row, column, new QTableWidgetItem());
        }
    }
    ui->tableWidget->item(0,0)->setText("Da1 – внешний диаметр сердечника статора, м");
    ui->tableWidget->item(1,0)->setText("ha1 – высота оси вращения, м");
    ui->tableWidget->item(2,0)->setText("lambda_c1 – коэффициент теплопроводности стали сердечника");
    ui->tableWidget->item(3,0)->setText("L1 – длина сердечника статора, м");
    ui->tableWidget->item(4,0)->setText("delta(ст) – толщина станины, м");
    ui->tableWidget->item(5,0)->setText("lambda(ст) – коэффициент проводимости материала станины");
    ui->tableWidget->item(6,0)->setText("lambda(i) – коэффициент теплопроводности воздуха");
    ui->tableWidget->item(7,0)->setText("delta(ai) – контактный зазор между сердечником статора и станиной, м");
    ui->tableWidget->item(8,0)->setText("k(c1) – коэффициент заполнения сердечника сталью");
    ui->tableWidget->item(9,0)->setText("Di1 - внутренний диаметр сердечника статора, м");

    ui->tableWidget->item(10,0)->setText("z1 – число зубцов статора");
    ui->tableWidget->item(11,0)->setText("bz1 – ширина паза статора, м");
    ui->tableWidget->item(12,0)->setText("lambda_с – высота зубца статора, м");
    ui->tableWidget->item(13,0)->setText("Hz1 – высота зубца статора, м");
    ui->tableWidget->item(14,0)->setText("lambda_ip1 – коэффициент теплопроводности пазовой изоляции");
    ui->tableWidget->item(15,0)->setText("delta_ip1 – толщина пазовой изоляции");
    ui->tableWidget->item(16,0)->setText("Кз – коэффициент заполнения паза");
    ui->tableWidget->item(17,0)->setText("d1 - толщина пазовой изоляции");
    ui->tableWidget->item(18,0)->setText("teta_m – допускаемая температура обмотки статора для данного класса нагревостойкости пазовой изоляции");
    ui->tableWidget->item(19,0)->setText("Kp - оэффициент пропитки");

    ui->tableWidget->item(20,0)->setText("lambda_l – коэффициент теплопроводности пропиточного лака , м");
    ui->tableWidget->item(21,0)->setText("lambda(эм) – коэффициент теплопроводности изоляции обмоточного провода");
    ui->tableWidget->item(22,0)->setText("Bp -Ширина паза статора");
    ui->tableWidget->item(23,0)->setText("sigma_ipr - Толщина изоляции провода");
    ui->tableWidget->item(24,0)->setText("sigma_i - fff");
    ui->tableWidget->item(25,0)->setText("lambda_ek – коэффициент теплопроводности пропиточного лака");
    ui->tableWidget->item(26,0)->setText("lambda_mi - коэффициент теплопроводности материала обмотки статора");
    ui->tableWidget->item(27,0)->setText("q_mi - суммарное сечение проводников в пазу статора");
    ui->tableWidget->item(28,0)->setText("Lp1 - длина вылета лобовой части");
    ui->tableWidget->item(29,0)->setText("lambda(mi) - dd;");

    ui->tableWidget->item(30,0)->setText("lambda_ekuz – fff");
    ui->tableWidget->item(31,0)->setText("lambda_ekpa – fff");
    ui->tableWidget->item(32,0)->setText("n - ddd;");
    ui->tableWidget->item(33,0)->setText("Dv1 - fff;");
    ui->tableWidget->item(34,0)->setText("nu – коэффициент теплопроводности лобовых частей");
    ui->tableWidget->item(35,0)->setText("Kл1 – коэффициент обдува лобовых частей");
    ui->tableWidget->item(36,0)->setText("lambda_il – коэффициент теплопроводности изоляции лобовых частей");
    ui->tableWidget->item(37,0)->setText("delta_il1 - толщина изоляции лобовых частей");
    ui->tableWidget->item(38,0)->setText("lambda_m2 - коэффициент теплопроводности материала обмотки ротора");
    ui->tableWidget->item(39,0)->setText("qc - сечение стержня клетки ротора");

    ui->tableWidget->item(40,0)->setText("L2 – Длина сердечника ротора");
    ui->tableWidget->item(41,0)->setText("Bk – Ширина короткозамыкающего кольца");
    ui->tableWidget->item(42,0)->setText("Z2 – число зубцов ротора");
    ui->tableWidget->item(43,0)->setText("u_rot - dcdd");
    ui->tableWidget->item(44,0)->setText("Dl - fff");
    ui->tableWidget->item(45,0)->setText("S_l2 – поверхность двух лобовых частей обмотки ротора");
    ui->tableWidget->item(46,0)->setText("S_isch – площадь подшипниковых щитов");
    ui->tableWidget->item(47,0)->setText("S_ist – площадь станины");
    ui->tableWidget->item(48,0)->setText("alpha_r – средний коэффициент теплоотдачи с внутренней поверхности подшипникового щита");
    ui->tableWidget->item(49,0)->setText("alpha_st – площадь внутренней поверхности двух подшипниковых щитов");

    ui->tableWidget->item(50,0)->setText("h_p – средний коэффициент теплоотдачи с внутренней поверхности станины");
    ui->tableWidget->item(51,0)->setText("t_p – коэффициент конвективной теплоотдачи станины");
    ui->tableWidget->item(52,0)->setText("n_p – коэффициент теплоотдачи излучением");
    ui->tableWidget->item(53,0)->setText("a_p – наружный диаметр станины");
    ui->tableWidget->item(54,0)->setText("D_ct – коэффициент оребрения станины с учетом внутреннего теплового сопротивления ребер");
    ui->tableWidget->item(55,0)->setText("u2 - радиус ротора, м");
    ui->tableWidget->item(56,0)->setText("lambda_v - коэффициент теплопроводности воздуха");
    ui->tableWidget->item(57,0)->setText("lambda_v – наружный диаметр станины");
    ui->tableWidget->item(58,0)->setText("Шаг ребер станины, м");
    ui->tableWidget->item(59,0)->setText("Число фаз обмотки статора");

    ui->tableWidget->item(60,0)->setText("Количество элементарных проводников");
    ui->tableWidget->item(61,0)->setText("Dp1 - радиус ротора");
    ui->tableWidget->item(62,0)->setText("lambda_v - коэффициент теплопроводности воздуха");
    ui->tableWidget->item(63,0)->setText("lambda_v – наружный диаметр станины");
    ui->tableWidget->item(64,0)->setText("Удельная теплоемкость стали");
    ui->tableWidget->item(65,0)->setText("Удельное сопротивление меди");
    ui->tableWidget->item(66,0)->setText("Полезная мощность, Вт");
    ui->tableWidget->item(67,0)->setText("Напряжение питания, В");
    ui->tableWidget->item(68,0)->setText("Коэффициент полезного действия");
    ui->tableWidget->item(69,0)->setText("Коэффициент мощности");

    ui->tableWidget->item(70,0)->setText("Удельное сопротивление алюминия");
    ui->tableWidget->item(71,0)->setText("Средний диаметр короткозамыкающего кольца");
    ui->tableWidget->item(72,0)->setText("Обмоточный коэффициент обмотки статора");
    ui->tableWidget->item(73,0)->setText("Коэффициент скоса пазов");

    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
    {
        if (ui->tableWidget->item(row,0) != 0)
        {
            ui->tableWidget->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget->item(row,1) != 0)
        {
            ui->tableWidget->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget->item(row,1)->setTextAlignment(Qt::AlignCenter);            
        }
        if (ui->tableWidget->item(row,2) != 0)
        {
            ui->tableWidget->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget->item(row,3) != 0)
        {
            ui->tableWidget->item(row,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget->item(row,3)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget->item(row,4) != 0)
        {
            ui->tableWidget->item(row,4)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget->item(row,5) != 0)
        {
            ui->tableWidget->item(row,5)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget->item(row,5)->setTextAlignment(Qt::AlignCenter);
        }
    }

    QPalette p=ui->tableWidget->palette();
    p.setColor(QPalette::Base, QColor(255, 255, 191));
    p.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget->setPalette(p);

    CustomHelpDelegate* customHelpDelegate = new CustomHelpDelegate(this); //создание делегата для создания комбобоксов
    ui->tableWidget->setItemDelegateForColumn(0, customHelpDelegate);
}

Tepl_dannie::~Tepl_dannie()
{
    delete ui;
}

