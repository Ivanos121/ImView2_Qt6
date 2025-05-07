#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    connect(ui->actionclose,&QPushButton::clicked, this, &AboutDialog::actionclose);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::actionclose()
{
    close();
}
