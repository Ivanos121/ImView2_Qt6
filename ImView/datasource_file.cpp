#include "ui_mainwindow.h"
#include "datasource_file.h"
#include "ui_datas.h"
#include "mainwindow.h"
#include "base.h"
#include <fstream>
#include <QMessageBox>
#include <stdio.h>

std::ifstream fin;

DataSource_file::DataSource_file()
{
    dataTimer = new QTimer(this);
    connect(dataTimer, &QTimer::timeout, this, &DataSource_file::read);
}

void DataSource_file::init()
{
    fin.open(base.dataSourceFilename.toUtf8(),std::ios::in);
    if(!fin.is_open())
    {
        QMessageBox::critical(nullptr, "Ошибка!", "Не удалось открыть файл!");
        return;
    }
    dataTimer->start(300);
}

void DataSource_file::read()
{
    for (int i = 0; i < BUF_SIZE; i++)
    {
        fin >> time[i] >> ua[i] >> ub[i] >> uc[i] >>ia[i] >> ib[i] >> ic[i] >> w[i];
    }

    emit ready();

    if (fin.eof()) // Достигнут конец файла
    {
        QMessageBox msg;
        msg.setText("чтение файла закончено");
        msg.exec();
        stop();
    }
}

void DataSource_file::stop()
{
    dataTimer->stop();
    fin.close();
}

