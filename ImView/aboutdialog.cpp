#include "aboutdialog.h"
#include "ui_aboutdialog.h"

#include <QSettings>

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    connect(ui->actionclose,&QPushButton::clicked, this, &AboutDialog::actionclose);
    QSettings settings("BRU", "IM View");
    QString version = settings.value("version").toString();
    ui->label_2->setText("Version: " + version);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::actionclose()
{
    close();
}
