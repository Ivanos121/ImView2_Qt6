#include <QMessageBox>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QFile>
#include <QDomDocument>
#include <QVector>
#include <QPointF>
#include <QXmlStreamReader>
#include <QFileDialog>

#include "signal_builder.h"
#include "ui_signal_builder.h"

Signal_builder::Signal_builder(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Signal_builder)
{
    ui->setupUi(this);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &Signal_builder::apply_signal_builder);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &Signal_builder::close_signal_builder);
}

Signal_builder::~Signal_builder()
{
    delete ui;
}

void Signal_builder::apply_signal_builder()
{
    close();
}

void Signal_builder::close_signal_builder()
{
    close();
}
