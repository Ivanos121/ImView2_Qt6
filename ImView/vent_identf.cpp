#include "vent_identf.h"
#include "qxmlstream.h"
#include "ui_vent_identf.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "base.h"
#include "Base_tepl_vent.h"
#include "polynomial.h"

#include <iostream>
#include <fstream>
#include <QVector>

#include <stdio.h>
#include <gsl/gsl_multifit.h>
#include <gsl/gsl_blas.h>

#include <QFileInfo>
#include <QMessageBox>
#include <QSettings>
#include <algorithm>

#define N 100

Vent_identf::Vent_identf(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Vent_identf)
{
    ui->setupUi(this);
    ui->plot->t_max = 0.01;
    ui->plot->U_max = 3.0;
    ui->plot->margin_bottom = 40;
    ui->plot->margin_left = 100;
    ui->plot->reset();

    dataLineColors_vent_identf.append(Qt::red);
    dataLineColors_vent_identf.append(Qt::green);
    dataLineColors_vent_identf.append(Qt::blue);
    dataLineColors_vent_identf.append(Qt::yellow);
    dataLineColors_vent_identf.append(Qt::red);
    dataLineColors_vent_identf.append(Qt::green);
    dataLineColors_vent_identf.append(Qt::blue);
    dataLineColors_vent_identf.append(Qt::yellow);
    dataLineColors_vent_identf.append(Qt::green);

    ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/vent_schem_zam/vent_schem_zam.html")
                                                      .absoluteFilePath()));
    ui->tabWidget->setCurrentIndex(0);
    connect(ui->tabWidget, &QTabWidget::currentChanged,
            this, &Vent_identf::on_tabWidget_currentChanged);
}

Vent_identf::~Vent_identf()
{
    delete ui;
}

void Vent_identf::on_tabWidget_currentChanged()
{
    wf->ui->stackedWidget->show();
    wf->ui->stackedWidget->setCurrentIndex(22);    
}

void Vent_identf::raschet_vent_identf()
{
    if(wf->kind_ventilation_value->text() == "Независимая вентиляция")
    {
        QMessageBox::critical(this, "cc","cc");
    }
    else if(wf->kind_ventilation_value->text() == "Принудительная вентиляция")
    {
        wf->ui->stackedWidget->hide();

        /*Ввод исходных данных */

        wf->loadMotorParameters();

        double w_0 = (2.0*M_PI)*base.n_0/60;
        int w_nom = 2.0*M_PI*base.n_nom/60;
        int M_nom = base.P_nom/w_nom;
        double M_kr = M_nom*base.muk;
        double s_nom = (w_0-w_nom)/w_0;
        double s_kr = (sqrt(s_nom)+sqrt(((base.muk)-1)/((base.muk/2)-1)))
                      /((1/sqrt(s_nom))+sqrt(((base.muk)-1)/((base.muk/2)-1)));
        double qq=((1/sqrt(s_kr))-sqrt(s_kr));
        double q = ((pow(qq,2)/((base.muk/2)-1)))-2;

        /*Расчет параметров */

        QVector<double> w(N);
        QVector<double> M(N);

        double s_min = 0.0;
        double s_max = 1.0;
        double step = (s_max - s_min) / (N - 1);

        ui->plot->clear();

        for (int i = 0; i < 9; i++)
        {
            ui->plot->addDataLine(dataLineColors_vent_identf[i], 0);
        }

        for (int s_idx = 0; s_idx < N; ++s_idx)
        {
            double s = s_min + s_idx * step;
            w[s_idx] = w_0 * (1 - s);
            M[s_idx] = (M_kr * (2 + q)) / ((s / s_kr) + (s_kr / s) + q);
            // ui->plot->addPoint(0, s, w[s_idx]);
            // ui->plot->addPoint(1, M[s_idx], w[s_idx]);
        }

        //Начальное давление вентилятора:
        ventparam.H0=0.00695 * pow(ventparam.n,2) * (pow(ventparam.d2p,2) - pow(ventparam.d1p,2));

        //Максимальный расход воздуха:
        ventparam.Qmax = 0.006 * pow(ventparam.d2p,2) * ventparam.b * ventparam.n;

        //Сопротивление входа в кожух через решетку с острыми кромками
        ventparam.epsilon1 = 0.5;
        ventparam.Z1 = ventparam.epsilon1 * (ventparam.ro / (2 * pow(ventparam.sotv,2)));

        //Сопротивление поворота потока за входной решеткой перед входом в вентилятор
        ventparam.epsilon2 = 0.5;
        ventparam.Z2 = ventparam.epsilon2 * (ventparam.ro / (2 * pow(ventparam.s1,2)));

        //Сопротивление потока за входным вентилятором перед входом в межреберные каналы
        ventparam.epsilon3 = 0.5;
        ventparam.Z3 = ventparam.epsilon3 * (ventparam.ro / (2 * pow(ventparam.s2,2)));

        //Сопротивление косого входа в межреберные каналы
        ventparam.epsilon4 = 0.5;
        ventparam.cosf = 0.7;
        ventparam.Z4 = ventparam.epsilon4 * (ventparam.ro / (2 * pow(ventparam.s4,2) * pow(ventparam.cosf,2)));

        //Сопротивление поворота потока в межреберных каналах под кожухом
        ventparam.epsilon5 = 0.5;
        ventparam.Z5 = ventparam.epsilon5 * (ventparam.ro / (2 * pow(ventparam.s4,2)));

        //Сопротивление выхода воздуха из межреберных каналов в воздушное пространство
        ventparam.epsilon6 = 0.5;
        ventparam.Z6 = ventparam.epsilon6 * (ventparam.ro / (2 * pow(ventparam.s4,2)));

        //Суммарное сопротивление вентиляционной сети
        ventparam.Z0=1.2 *(ventparam.Z1 + ventparam.Z2 + ventparam.Z3 + ventparam.Z4 + ventparam.Z5 + ventparam.Z6);

        //Рабочий расход воздуха
        ventparam.Qp = ventparam.Qmax * sqrt(ventparam.H0 /(ventparam.H0 + ventparam.Z0 * pow(ventparam.Qmax,2)));

        //Рабочий набор вентилятора
        ventparam.Hp = ventparam.Z0 * pow(ventparam.Qp,2);

        //Средняя скорость воздуха в межреберных каналах
        ventparam.K = 1;
        ventparam.Vcp = ventparam.K *ventparam.Qp /ventparam.s4;

        //Потребляемая вентилятором мощность
        ventparam.nu2 = 0.7;
        ventparam.Pvent = 9.81 * (ventparam.Qp * ventparam.Hp / ventparam.nu2);

        qDebug() << "Qp = " << ventparam.Qp << " " << "Qmax =" << ventparam.Qmax;

        ventparam.v = 1.5;

        QVector<double> Q(N);
        QVector<double> H1(N);
        QVector<double> H2(N);
        QVector<double> Pv(N);
        QVector<double> P_din(N);
        QVector<double> P_ct(N);

        double Q_min = 0.0;
        double Q_max = ventparam.Qmax;
        double steps = (Q_max - Q_min) / (N - 1);

        ui->plot->clear();

        for (int i = 0; i < 9; i++)
        {
            ui->plot->addDataLine(dataLineColors_vent_identf[i], 0);
        }

        ui->plot->U_offset = 0.1;

        for (int s_idx1 = 0; s_idx1 < N; ++s_idx1)
        {
            Q[s_idx1] = Q_min + s_idx1 * steps;
            H1[s_idx1] = ventparam.Z0/100 * pow(Q[s_idx1],2);
            H2[s_idx1] = ventparam.H0/100 *(1 - pow((Q[s_idx1]/ventparam.Qmax),2));
            Pv[s_idx1] = Q[s_idx1]*H1[s_idx1];
            P_din[s_idx1] = 1.2*pow(ventparam.v,2);
            P_ct[s_idx1] = Pv[s_idx1]-P_din[s_idx1];
            ui->plot->addPoint(0, Q[s_idx1], H1[s_idx1]);
            ui->plot->addPoint(1, Q[s_idx1], H2[s_idx1]);
            ui->plot->addPoint(2, Q[s_idx1], Pv[s_idx1]);
            ui->plot->addPoint(3, Q[s_idx1], P_din[s_idx1]);
            ui->plot->addPoint(4, Q[s_idx1], P_ct[s_idx1]);
        }

        QVector<double> Q_inv;
        Q_inv.reserve(Q.size());

        // добавляем элементы в обратном порядке
        for (int i = Q.size() - 1; i >= 0; --i) {
            Q_inv.append(Q[i]);
        }

        // Открываем файл для записи
        std::ofstream outFile("output.txt");

        // Проверяем успешность открытия файла
        if (!outFile.is_open()) {
            std::cerr << "Не удалось открыть файл для записи." << std::endl;
            return; // или обработка ошибки
        }

        // Записываем данные
        // Например, по одной точке на строку: w[i] и Q[i]
        size_t size = std::min(w.size(), Q_inv.size());
        for (size_t i = 0; i < size; ++i)
        {
            outFile << w[i] << " " << Q_inv[i] << "\n";
        }

        // Закрываем файл
        outFile.close();

        /* выбор степени полинома аппроксимации данных */

        int optimalDegree = -1;

        if(wf->data_approximation_mode_value->text() == "Ручной")
        {
            optimalDegree = wf->degree_approximating_polynomial_value->text().toInt();
        }
        else if(wf->data_approximation_mode_value->text() == "Автоматический")
        {
            optimalDegree = bestDegree(w, Q_inv);
        }

        ventparam.w_Q_inv_koeffss = approximate(w, Q_inv, optimalDegree);
        ventparam.Q_H1_koeffss = approximate(Q, H1, optimalDegree);
        ventparam.Q_H2_koeffss = approximate(Q, H2, optimalDegree);
        ventparam.Q_Pv_koeffss = approximate(Q, Pv, optimalDegree);

        Polynomial w_Q_inv_poly(ventparam.w_Q_inv_koeffss);
        Polynomial Q_H1_poly(ventparam.Q_H1_koeffss);
        Polynomial Q_H2_poly(ventparam.Q_H2_koeffss);
        Polynomial Q_Pv_poly(ventparam.Q_Pv_koeffss);

        QVector<double> Q_appr(N);
        QVector<double> H1_appr(N);
        QVector<double> H2_appr(N);
        QVector<double> Pv_appr(N);

        for(int i=0;i<N; ++i)
        {
            Q_appr[i] = w_Q_inv_poly.evaluate(w[i]);
            H1_appr[i] = Q_H1_poly.evaluate(Q_appr[i]);
            H2_appr[i] = Q_H2_poly.evaluate(Q_appr[i]);
            Pv_appr[i] = Q_Pv_poly.evaluate(Q_appr[i]);
            ui->plot->addPoint(5, Q_appr[i], w[i]);
            ui->plot->addPoint(6, Q_appr[i], H1_appr[i]);
            ui->plot->addPoint(7, Q_appr[i], H2_appr[i]);
            ui->plot->addPoint(8, Q_appr[i], Pv_appr[i]);
        }

        std::ofstream outFile2("output2.txt");

        // Проверяем успешность открытия файла
        if (!outFile2.is_open()) {
            std::cerr << "Не удалось открыть файл для записи." << std::endl;
            return; // или обработка ошибки
        }

        // Записываем данные


        for (int i = 0; i < N; ++i)
        {
            // Записываем одну строку с данными из всех массивов
            outFile2 << w[i] << "\t"
                     << Q[i] << "\t"
                     << Q_appr[i] << "\t"
                     << H1_appr[i] << "\t"
                     << H2_appr[i] << "\t"
                     << Pv_appr[i] << "\n";
        }

        // Закрываем файл
        outFile2.close();

        if(wf->data_identification_value->text() == "Сохранить")
        {
            save_vent_identf();
        }

        isFinished = false;
        wf->statusbar_label_9->setVisible(true);
        wf->statusbar_progres->setVisible(true);
        wf->statusbar_progres->setRange(0, 100);
        wf->statusbar_progres->reset();
        isFinished = false;

        QSettings settings( "BRU", "IM View");
        settings.beginGroup( "System_messages" );
        QString lokal = settings.value( "Messages", "").toString();
        settings.endGroup();

        if(lokal == "fix")
        {
            QMessageBox::information(this, tr("Сообщение"), tr("Расчет параметров тепловой схемы замещения закончен"));
        }
        else if(lokal == "nonfix")
        {
            QString summary_s = "Сообщение";
            QString body_s = "Расчет параметров тепловой схемы замещения закончен";
            wf->message_action(summary_s, body_s);
        }

        wf->ui->stackedWidget->show();
        wf->ui->stackedWidget->setCurrentIndex(22);

        wf->statusbar_label_9->setVisible(false);
        wf->statusbar_progres->setVisible(false);
    }
}

QVector<double> Vent_identf::approximate(const QVector<double>& x,
                                         const QVector<double>& y,
                                         size_t degree)
{
    degree++;
    QVector<double> koeffs(degree);

    for (int i = 0; i < N; ++i) {
        std::cout << x[i] << " " << y[i] << std::endl;
    }
    std::cout << std::endl;

    size_t n = x.size();

    // Создаем gsl матрицы и векторы
    gsl_matrix *X = gsl_matrix_alloc(n, degree);
    gsl_vector *Y = gsl_vector_alloc(n);
    gsl_vector *c = gsl_vector_alloc(degree); // параметры модели
    gsl_matrix *cov = gsl_matrix_alloc(degree, degree);

    // Заполняем X матрицу значениями
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < degree; j++)
        {
            gsl_matrix_set(X, i, j, pow(x[i], j));
        }
        gsl_vector_set(Y, i, y[i]);
    }

    // Выполняем аппроксимацию методом наименьших квадратов
    gsl_multifit_linear_workspace *work = gsl_multifit_linear_alloc(n, degree);
    double chisq;

    int status = gsl_multifit_linear(X, Y, c, cov, &chisq, work);
    if (status != GSL_SUCCESS)
    {
        printf("Ошибка при вычислении аппроксимации\n");
        return koeffs;
    }

    // Вывод полученных коэффициентов
    printf("Коэффициенты полинома:\n");
    for (size_t j=0; j<degree; j++) {
        koeffs[j] = gsl_vector_get(c,j);
        printf("a_%zu = %g\n", j, gsl_vector_get(c,j));
    }
    printf("Отклонение (chisq): %g\n", chisq);

    // Используем модель для оценки новых значений
    double x_eval = x[0];
    double y_eval = 0;
    for (size_t j=0; j<degree; j++) {
        y_eval += gsl_vector_get(c,j) * pow(x_eval,j);
    }
    printf("Оценка в точке x=%.2f: y=%.2f\n", x_eval,y_eval);

    // Освобождение ресурсов
    gsl_multifit_linear_free(work);
    gsl_matrix_free(X);
    gsl_vector_free(Y);
    gsl_vector_free(c);
    gsl_matrix_free(cov);

    return koeffs;
}

double Vent_identf::computeError(const QVector<double>& x,
                                 const QVector<double>& y,
                                 const QVector<double>& coeffs)
{
    double error_sum=0;
    int degree=coeffs.size()-1;

    for(int i=0;i<x.size();++i)
    {
        double y_pred=0;
        for(int j=0;j<=degree;++j)
            y_pred+=coeffs[j]*std::pow(x[i],j);
        double diff=y[i]-y_pred;
        error_sum+=diff*diff;
    }
    return std::sqrt(error_sum/x.size()); // среднеквадратичная ошибка
}

int Vent_identf::bestDegree(const QVector<double>& x, const QVector<double>& y)
{
    int maxDegree=5;
    double bestError=std::numeric_limits<double>::max();
    int bestDegree=1;

    for(int degree=1;degree<=maxDegree;++degree)
    {
        auto coeffs = approximate(x, y, degree);
        double err=computeError(x, y, coeffs);
        std::cout<<"Степень "<<degree<<" ошибка "<<err<<std::endl;

        if (err < 1e-10)
        {
            bestError=err;
            bestDegree=degree;
            break;
        }

        if(err<bestError)
        {
            bestError=err;
            bestDegree=degree;
        }
    }

    std::cout<<"Оптимальная степень: "<<bestDegree<<", ошибка: "<<bestError<<std::endl;
    return bestDegree;
}

void Vent_identf::save_vent_identf()
{
    QFile file(QString("/home/elf/ImView2_Qt6/save/vent_identf.xml"));
    file.open(QIODevice::WriteOnly);

    //Создаем объект, с помощью которого осуществляется запись в файл
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
    xmlWriter.writeStartDocument();     // Запускаем запись в документ
    xmlWriter.writeStartElement("resources");   // Записываем первый элемент с его именем
    xmlWriter.writeStartElement("vent_identf");  // Записываем тег с именем для первого итема

    xmlWriter.writeStartElement("general_settings");

    xmlWriter.writeStartElement("Fan_working_set_Qp");
    //xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(0,2)->text()));
    xmlWriter.writeAttribute("value", (QString::number(ventparam.Qp)));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Maximum_air_flow_Qmax");
    //xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(1,2)->text()));
    xmlWriter.writeAttribute("value", (QString::number(ventparam.Qmax)));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Initial_fan_pressure_H0");
    //xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(2,2)->text()));
    xmlWriter.writeAttribute("value", (QString::number(ventparam.H0)));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Fan_working_set_Hp");
    //xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(3,2)->text()));
    xmlWriter.writeAttribute("value", (QString::number(ventparam.Hp)));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Total_resistance_of_ventilation_network_Z0");
    //xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(4,2)->text()));
    xmlWriter.writeAttribute("value", (QString::number(ventparam.Hp)));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Fan_power_consumption_Pvent");
    //xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(5,2)->text()));
    xmlWriter.writeAttribute("value", (QString::number(ventparam.Pvent)));
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();

}
