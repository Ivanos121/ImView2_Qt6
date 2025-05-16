#include "teplovent.h"
#include "ui_teplovent.h"

teplovent::teplovent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::teplovent)
{
    ui->setupUi(this);

}

teplovent::~teplovent()
{
    delete ui;
}

