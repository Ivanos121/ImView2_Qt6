#include "poisk.h"
#include "ui_poisk.h"

poisk::poisk(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::poisk)
{
    ui->setupUi(this);
    QPixmap pixmap("/home/elf/ImView2/data/img/system_icons/window-close1.svg");
    QIcon ButtonIcon(pixmap);
    ui->pushButton_7->setIcon(ButtonIcon);
    ui->pushButton_7->setIconSize(pixmap.rect().size());
}

poisk::~poisk()
{
    delete ui;
}
