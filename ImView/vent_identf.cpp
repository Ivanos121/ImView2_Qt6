#include "vent_identf.h"
#include "ui_vent_identf.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "base.h"
#include "Base_tepl_vent.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <QVector>

#include <stdio.h>
#include <gsl/gsl_multifit.h>
#include <gsl/gsl_blas.h>

#include <QFileInfo>
#include <QMessageBox>
#include <QSettings>
#include <algorithm>

double keys = 0.0;
QTimer *times;
static bool isFinished;
int stepen;
const int N = 100.0;
QVector<double> w[N];
QVector<double> Q[N];

Vent_identf::Vent_identf(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Vent_identf)
{
    ui->setupUi(this);
    ui->plot->t_max = 10.0;
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

    // for (int i = 0; i < dataLineColors_vent_identf.size(); i++)
    // {
    //     ui->tableWidget->item(i, 1)->setBackground(dataLineColors_vent_identf[i]);
    // }

    times = new QTimer(this);

    ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/vent_schem_zam/vent_schem_zam.html")
                                                      .absoluteFilePath()));
}

Vent_identf::~Vent_identf()
{
    delete ui;
}

void Vent_identf::raschet_vent_identf()
{
    wf->ui->stackedWidget->hide();
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

    qDebug() << s_kr << " " << q;


    const int N = 100; // количество точек
    QVector<double> w(N);
    QVector<double> M(N);

    double s_min = 0.0;
    double s_max = 1.0;
    double step = (s_max - s_min) / (N - 1);

    ui->plot->clear();

    for (int i = 0; i < 8; i++)
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

    // ventparam.Q =0;
    // ventparam.H1 = 0;
    // ventparam.H2 = 0;
    // ventparam.Pv = 0;
    // ventparam.P_ct = 0;
    // double P_din = 0;
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
    for (int s_idx1 = 0; s_idx1 < N; ++s_idx1)
    {
        ventparam.Q = Q_min + s_idx1 * steps;
        double anser = ventparam.Q;
        Q[s_idx1] = anser;
        H1[s_idx1] = ventparam.Z0/100 * pow(ventparam.Q,2);
        H2[s_idx1] = ventparam.H0/100 *(1 - pow((ventparam.Q/ventparam.Qmax),2));
        Pv[s_idx1] = ventparam.Q*ventparam.H1;
        P_din[s_idx1] = 1.2*pow(ventparam.v,2);
        P_ct[s_idx1] = ventparam.Pv-ventparam.P_din;
        ui->plot->addPoint(0, ventparam.Q, H1[s_idx1]);
        ui->plot->addPoint(1, ventparam.Q, H2[s_idx1]);
        ui->plot->addPoint(2, ventparam.Q, Pv[s_idx1]);
        ui->plot->addPoint(3, ventparam.Q, P_din[s_idx1]);
        ui->plot->addPoint(4, ventparam.Q, P_ct[s_idx1]);
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



    double x[N];

    for (int i = 0; i < N; ++i)
    {
        x[i] = w[i];
    }

    double y[N];

    for (int i = 0; i < N; ++i)
    {
        y[i] = Q_inv[i];
    }

    for (int i = 0; i < N; ++i) {
        std::cout << x[i] << " " << y[i] << std::endl;
    }
    std::cout << std::endl;

    size_t n = sizeof(x) / sizeof(x[0]);

    /* выбор степени полинома аппроксимации данных */

    int optimalDegree = -1;

    if(wf->data_approximation_mode_value->text() == "Ручной")
    {
        optimalDegree = wf->degree_approximating_polynomial_value->text().toInt();
    }
    else if(wf->data_approximation_mode_value->text() == "Автоматический")
    {
        optimalDegree = bestDegree(Q_inv, w);
    }

   // bestDegree(Q,w);

    //size_t p = stepen; // степень полинома + 1 (для квадратичной: степень 2 => p=3)

    size_t p = optimalDegree;

    // Создаем gsl матрицы и векторы
    gsl_matrix *X = gsl_matrix_alloc(n, p);
    gsl_vector *Y = gsl_vector_alloc(n);
    gsl_vector *c = gsl_vector_alloc(p); // параметры модели
    gsl_matrix *cov = gsl_matrix_alloc(p, p);

    // Заполняем X матрицу значениями
    for (size_t i = 0; i < n; i++)
    {
        double xi = x[i];
        for (size_t j = 0; j < p; j++)
        {
            gsl_matrix_set(X, i, j, pow(xi, j));
        }
        gsl_vector_set(Y, i, y[i]);
    }

    // Выполняем аппроксимацию методом наименьших квадратов
    gsl_multifit_linear_workspace *work = gsl_multifit_linear_alloc(n, p);
    double chisq;

    int status = gsl_multifit_linear(X, Y, c, cov, &chisq, work);
    if (status != GSL_SUCCESS)
    {
        printf("Ошибка при вычислении аппроксимации\n");
        return;
    }

    // Вывод полученных коэффициентов
    printf("Коэффициенты полинома:\n");
    for (size_t j=0; j<p; j++) {
        printf("a_%zu = %g\n", j, gsl_vector_get(c,j));
    }
    printf("Отклонение (chisq): %g\n", chisq);

    // Используем модель для оценки новых значений
    double x_eval = 2.5;
    double y_eval = 0;
    for (size_t j=0; j<p; j++) {
        y_eval += gsl_vector_get(c,j) * pow(x_eval,j);
    }
    printf("Оценка в точке x=%.2f: y=%.2f\n", x_eval,y_eval);

    // Освобождение ресурсов
    gsl_multifit_linear_free(work);
    gsl_matrix_free(X);
    gsl_vector_free(Y);
    gsl_vector_free(c);
    gsl_matrix_free(cov);

    isFinished = false;
    wf->statusbar_label_9->setVisible(true);
    wf->statusbar_progres->setVisible(true);
    wf->statusbar_progres->setRange(0, 100);
    wf->statusbar_progres->reset();
    isFinished = false;
    if (times->isActive())
    {
        times->stop();
    }
    keys = 0.0;

    connect(times, &QTimer::timeout, this, &Vent_identf::realtimeDataSlot);
    double Ts=0.000032;
    times->start(Ts);
}

void Vent_identf::realtimeDataSlot()
{

    // calculate two new data points:

    keys = keys+0.000032; // time elapsed since start of demo, in seconds

    double t = keys;
    double maxTime = 0.1;
    wf->statusbar_progres->setValue(t / maxTime * 100);

    wf->statusbar_label_9->setText("T = " + QString::number(keys,'f',5) + " " + "c");
    wf->statusbar_label_9->setAlignment(Qt::AlignTop);
    wf->statusbar_progres->setAlignment(Qt::AlignTop);

    if (keys>=0.1&& !isFinished)
    {
        isFinished = true;
        if (times->isActive())
        {
            times->stop();
        }
        wf->ui->vent_identf_stop->setEnabled(false);
        wf->ui->ventidentf_start->setIcon(QIcon(":/system_icons/data/img/system_icons/media-playback-start_4.svg"));

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

        // wf->ui->lineEdit_7->setText(QString::number(0.5,'f',3));
        // wf->ui->lineEdit_7->setAlignment(Qt::AlignCenter);
        // wf->ui->lineEdit_19->setText(QString::number(0.4,'f',3));
        // wf->ui->lineEdit_19->setAlignment(Qt::AlignCenter);
        // wf->ui->lineEdit_20->setText(QString::number(0.07,'f',3));
        // wf->ui->lineEdit_20->setAlignment(Qt::AlignCenter);

        wf->ui->stackedWidget->show();
        wf->ui->stackedWidget->setCurrentIndex(22);

        wf->statusbar_label_9->setVisible(false);
        wf->statusbar_progres->setVisible(false);
    }
}

std::vector<double> Vent_identf::polyfit(const std::vector<double>& x,
                            const std::vector<double>& y,
                            int degree)
{
    int N = x.size();
    int M = degree + 1;

    // Создаем матрицу A и вектор b
    std::vector<std::vector<double>> A(M, std::vector<double>(M, 0));
    std::vector<double> b(M, 0);

    // Заполняем A и b
    for (int row = 0; row < M; ++row)
    {
        for (int col = 0; col < M; ++col)
        {
            double sum = 0;
            for (int i = 0; i < N; ++i)
                sum += std::pow(x[i], row + col);
            A[row][col] = sum;
        }
        double sum_b = 0;
        for (int i = 0; i < N; ++i)
            sum_b += y[i] * std::pow(x[i], row);
        b[row] = sum_b;
    }

    // Решение системы методом Гаусса
    for (int i = 0; i < M; ++i)
    {
        // Поворотный элемент
        for (int k = i + 1; k < M; ++k)
        {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j < M; ++j)
                A[k][j] -= factor * A[i][j];
            b[k] -= factor * b[i];
        }
    }

    // Обратный ход
    std::vector<double> coeffs(M);
    for (int i = M - 1; i >= 0; --i)
    {
        double sum = b[i];
        for (int j = i + 1; j < M; ++j)
            sum -= A[i][j] * coeffs[j];
        coeffs[i] = sum / A[i][i];
    }

    return coeffs;
}

double Vent_identf::computeError(const std::vector<double>& x,
                    const std::vector<double>& y,
                    const std::vector<double>& coeffs)
{
    double error_sum=0;
    int N=x.size();
    int degree=coeffs.size()-1;

    for(int i=0;i<N;++i)
    {
        double y_pred=0;
        for(int j=0;j<=degree;++j)
            y_pred+=coeffs[j]*std::pow(x[i],j);
        double diff=y[i]-y_pred;
        error_sum+=diff*diff;
    }
    return std::sqrt(error_sum/N); // среднеквадратичная ошибка
}

int Vent_identf::bestDegree(const QVector<double>& Q_inv, const QVector<double>& w)
{
    int maxDegree=5;
    double bestError=std::numeric_limits<double>::max();
    int bestDegree=1;

    for(int degree=1;degree<=maxDegree;++degree)
    {
        std::vector<double> w_std(w.begin(), w.end());

        // for (size_t i = 0; i < w_std.size(); ++i)
        // {
        //     std::cout << w_std[i] << " ";
        // }
        // std::cout << std::endl;

        std::vector<double> Q_std(Q_inv.begin(), Q_inv.end());

        // for (size_t i = 0; i < Q_std.size(); ++i) {
        //     std::cout << Q_std[i] << " ";
        // }
        // std::cout << std::endl;

        auto coeffs = polyfit(w_std, Q_std, degree);
        double err=computeError(w_std,Q_std,coeffs);
        std::cout<<"Степень "<<degree<<" ошибка "<<err<<std::endl;
        if(err<bestError)
        {
            bestError=err;
            bestDegree=degree;
        }
    }

    std::cout<<"Оптимальная степень: "<<bestDegree<<", ошибка: "<<bestError<<std::endl;
    return bestDegree;
}
