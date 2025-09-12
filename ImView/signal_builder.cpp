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

    series = new QLineSeries(this);
    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();

    // Получаем оси
    QValueAxis *axisX = qobject_cast<QValueAxis*>(chart->axisX());
    QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axisY());

    if (axisX && axisY) {
        // Включаем сетку на осях
        axisX->setGridLineVisible(true);
        axisY->setGridLineVisible(true);
        // Можно настроить параметры сетки и осей, например шаг
        axisX->setTickCount(6);  // количество делений по X
        axisY->setTickCount(6);  // количество делений по Y
    }

    chartView = new QChartView(chart);

    // Устанавливаем график в QChartView
    ui->chartView->setChart(chart);

    // Включаем анимацию (опционально)
    chart->setAnimationOptions(QChart::AllAnimations);
    chartView->setRenderHint(QPainter::Antialiasing);

    updateChart();

    connect(ui->saveButton, &QPushButton::clicked, this, [this]()
            {
                savePointsToXml(this->fileName);
            });

    connect(ui->loadButton, &QPushButton::clicked, this, [this]()
            {
                loadPointsFromXml(this->fileName);
            });


    connect(ui->apply_pushButton, &QPushButton::clicked, this, &Signal_builder::apply_signal_builder);
    connect(ui->close_pushButton, &QPushButton::clicked, this, &Signal_builder::close_signal_builder);

    connect(ui->add_time_value_pushButton, &QPushButton::clicked, this, &Signal_builder::add_time_value_pushButton);
    connect(ui->clear_pushButton, &QPushButton::clicked, this, &Signal_builder::clear_pushButton);
}

Signal_builder::~Signal_builder()
{
    delete ui;
}

void Signal_builder::apply_signal_builder()
{
    base.voltageData = series->points();  // Получить массив точек
    close();
}

void Signal_builder::add_time_value_pushButton()
{
    bool okTime, okValue;
    double time = ui->lineEditTime->text().toDouble(&okTime);
    double value = ui->lineEditValue->text().toDouble(&okValue);

    if (!okTime || !okValue)
    {
        QMessageBox::warning(this, "Ошибка", "Введите корректные числа для времени и уровня");
        return;
    }

    signalBuilder.addPoint(time, value);
    series->append(time, value);

    updateAxes();

    updateChart();


}

void Signal_builder::clear_pushButton()
{
    signalBuilder.clear();
    series->clear();
    updateAxes();
    updateChart();

    qDebug() << "Точек после clear:" << series->count();  // Должно быть 0

    //ui->plot->clear();

    ui->chartView->chart()->removeSeries(series);
    ui->chartView->chart()->addSeries(series);
    qDebug() << "Точек после append:" << series->count();  // Должно быть 1 или больше

    ui->chartView->chart()->createDefaultAxes(); // если нужно обновить оси
    ui->chartView->chart()->update();

}

void Signal_builder::updateChart()
{
    chart = ui->chartView->chart();

    // Не удаляем серии полностью, просто очищаем данные
    if (!series)
        return;

    series->clear();

    const auto& points = signalBuilder.getPoints();
    if (points.empty())
    {
        chart->createDefaultAxes();
        return;
    }

    // Добавляем интерполированные точки
    const int samples = 200;
    double t_min = points.front().time;
    double t_max = points.back().time;

    for (int i = 0; i <= samples; ++i)
    {
        double t = t_min + (t_max - t_min) * i / samples;
        double v = signalBuilder.getValue(t);
        series->append(t, v);
    }

    // Если series ещё не добавлена в график, добавляем
    if (!chart->series().contains(series))
        chart->addSeries(series);

    chart->createDefaultAxes();

    auto axisX = qobject_cast<QValueAxis*>(chart->axes(Qt::Horizontal).constFirst());
    auto axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).constFirst());
    if (axisX) axisX->setTitleText("Время");
    if (axisY) axisY->setTitleText("Уровень");
}

void Signal_builder::saveDataXml()
{
    QString filter = "Файл конфигурации проекта (*.xml);;Все файлы (*.*)";
    QString str = QFileDialog::getSaveFileName(this, "Выбрать имя, под которым сохранить данные", filter);
    bool saved = savePointsToXml(str);
    if (saved)
    {
        qDebug() << "Данные успешно сохранены в XML";
    }
    else
    {
        qDebug() << "Ошибка сохранения XML";
    }
}

void Signal_builder::loadDataXml()
{
    QVector<QPointF> loadedData;
    bool loaded = loadPointsFromXml("points.xml");
    if (loaded)
    {
        qDebug() << "Данные успешно загружены из XML, точек:" << loadedData.size();
        // Можно обновить график: series->replace(loadedData); или аналогично
    }
    else
    {
        qDebug() << "Ошибка загрузки XML";
    }
}

bool Signal_builder::savePointsToXml(const QString &fileName)
{
    QString str = fileName;

    QString filter = "Данные сигнала скорости (*.xml);;Все файлы (*.*)";
    QString selectedFilter;  // Переменная для хранения выбранного фильтра

    str = QFileDialog::getSaveFileName(this, "Выбрать имя, под которым сохранить данные", QDir::homePath()
                                       , filter, &selectedFilter);
    if (!str.isEmpty())
    {
        if (selectedFilter == "Данные сигнала скорости (*.xml)" && !str.endsWith(".xml"))
        {
            str += ".xml";
        }
    }

    QFile file(str);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeStartElement("Points");  // Корневой элемент

    // Получаем точки из серии
    const auto points = series->points();

    for (const QPointF &pt : points) {
        xml.writeStartElement("Point");
        xml.writeAttribute("x", QString::number(pt.x()));
        xml.writeAttribute("y", QString::number(pt.y()));
        xml.writeEndElement(); // Point
    }

    xml.writeEndElement(); // Points
    xml.writeEndDocument();

    file.close();
    qDebug() << "Сохранено точек:" << points.size();
    return true;
}

bool Signal_builder::loadPointsFromXml(const QString &fileName)
{
    QVector<QPointF> points;

    QString str = fileName;

    QString filter = "Данные сигнала скорости (*.xml);;Все файлы (*.*)";

    str = QFileDialog::getOpenFileName(this, "Выбрать имя, под которым загрузить данные", QDir::homePath()
                                       , filter);

    // Открываем файл
    QFile file(str);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Не удалось открыть файл" << fileName;
        return false;
    }

    // Создаём XML-ридер
    QXmlStreamReader xml(&file);

    // Читаем XML
    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::StartElement && xml.name() == QStringLiteral("Point"))
        {
            // Извлекаем атрибуты x и y
            QString xStr = xml.attributes().value("x").toString();
            QString yStr = xml.attributes().value("y").toString();

            bool okX, okY;
            double x = xStr.toDouble(&okX);
            double y = yStr.toDouble(&okY);

            if (okX && okY)
            {
                points.append(QPointF(x, y));
            } else
            {
                qWarning() << "Неверный формат точки в XML:" << xStr << yStr;
            }
        }
    }

    // Проверяем на ошибки чтения
    if (xml.hasError())
    {
        qWarning() << "Ошибка чтения XML:" << xml.errorString();
        file.close();
        return false;
    }

    file.close();

    // Если точек нет, ничего не делаем
    if (points.isEmpty())
    {
        qWarning() << "В файле нет точек";
        return false;
    }

    // Обновляем серию
    //series->clear();  // Очищаем старую серию
    series->replace(points);  // Добавляем новые точки

    // Принудительно обновляем график
    if (chart->series().contains(series))
    {
        chart->removeSeries(series);  // Удаляем, чтобы пересоздать
    }

    // Удаляем старые оси
    const auto axes = chart->axes();
    for (QAbstractAxis *axis : axes)
    {
        chart->removeAxis(axis);
    }

    chart->addSeries(series);

    // Создаём и настраиваем оси
    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;

    double minX = points.first().x(), maxX = points.first().x();
    double minY = points.first().y(), maxY = points.first().y();

    for (const QPointF &p : std::as_const(points))
    {
        if (p.x() < minX) minX = p.x();
        if (p.x() > maxX) maxX = p.x();
        if (p.y() < minY) minY = p.y();
        if (p.y() > maxY) maxY = p.y();
    }

    axisX->setRange(minX, maxX);
    axisY->setRange(minY, maxY);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->legend()->hide();

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    ui->chartView->setChart(chart);
    ui->chartView->repaint();

    return true;
}

void Signal_builder::resieve_dannie()
{
    if (!series || series->points().isEmpty())
    {
        qDebug() << "Нет данных для передачи в plot";
        return;
    }

    emit dataReady(series->points());
}

void Signal_builder::updateAxes()
{
    if (!series)
        return;

    // Получаем все точки серии
    auto points = series->points();
    if (points.isEmpty())
        return;

    double minX = points[0].x();
    double maxX = points[0].x();
    double minY = points[0].y();
    double maxY = points[0].y();

    for (const QPointF& p : points)
    {
        if (p.x() < minX) minX = p.x();
        if (p.x() > maxX) maxX = p.x();
        if (p.y() < minY) minY = p.y();
        if (p.y() > maxY) maxY = p.y();
    }

    // Немного расширим диапазон для красоты
    double marginX = (maxX - minX) * 0.1;
    double marginY = (maxY - minY) * 0.1;

    auto axisX = qobject_cast<QValueAxis*>(chart->axes(Qt::Horizontal).first());
    auto axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());

    if (axisX)
        axisX->setRange(minX - marginX, maxX + marginX);
    if (axisY)
        axisY->setRange(minY - marginY, maxY + marginY);
}


void Signal_builder::close_signal_builder()
{
    close();
}
