#include "graph_nastr.h"
#include "ui_graph_nastr.h"

graph_nastr::graph_nastr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::graph_nastr)
{
    ui->setupUi(this);
}

graph_nastr::~graph_nastr()
{
    delete ui;
}
