#include "moment_signal_builder.h"
#include "ui_moment_signal_builder.h"
#include "base.h"

#include <QFile>
#include <QLineSeries>
#include <QValueAxis>
#include <QXmlStreamWriter>
#include <QFileDialog>
#include <QMessageBox>


Moment_signal_builder::Moment_signal_builder(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Moment_signal_builder)
{
    ui->setupUi(this);
    connect(ui->pushButtonPlot, &QPushButton::clicked, this, &Moment_signal_builder::plotGraph);
    connect(ui->clearButton, &QPushButton::clicked, this, &Moment_signal_builder::clearGraph);
    connect(ui->saveButton, &QPushButton::clicked, this, &Moment_signal_builder::saveGraph);
    connect(ui->loadButton, &QPushButton::clicked, this, &Moment_signal_builder::loadGraph);
    connect(ui->apply_pushButton, &QPushButton::clicked, this, &Moment_signal_builder::apply_pushButton);
    connect(ui->close_pushButton, &QPushButton::clicked, this, &Moment_signal_builder::close_pushButton);

    chart = new QChart();
    chart->setTitle("График изменения сигнала");

    // Создаем серию данных
    series = new QLineSeries();
    chart->addSeries(series);

    // Создаем оси
    axisX = new QValueAxis();
    axisX->setTitleText("Ось X (Время)");
    axisX->setRange(0, 3); // Устанавливаем диапазон оси X

    axisY = new QValueAxis();
    axisY->setTitleText("Ось Y (Уровень)");
    axisY->setRange(0, 10); // Устанавливаем диапазон оси Y

    // Добавляем оси к графику
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    // Устанавливаем график в QChartView
    ui->chartView->setChart(chart);
}

Moment_signal_builder::~Moment_signal_builder()
{
    delete ui;
}

void Moment_signal_builder::plotGraph()
{
    // Считываем значения из QLineEdit
    QString timeText = ui->lineEditX->text();
    QString levelText = ui->lineEditY->text();

    // Отладочные сообщения
    qDebug() << "Введенные значения для времени:" << timeText;
    qDebug() << "Введенные значения для уровня:" << levelText;

    // Разделяем строки на массивы чисел
    QStringList timeValues = timeText.split(' ', Qt::SkipEmptyParts);
    QStringList levelValues = levelText.split(' ', Qt::SkipEmptyParts);

    QVector<double> timeArray, levelArray;

    // Преобразуем строки в числа для времени
    for (const QString &value : std::as_const(timeValues))
    {
        QString cleanedValue = value;
        cleanedValue.remove('[').remove(']'); // Удаляем квадратные скобки
        cleanedValue = cleanedValue.trimmed(); // Удаляем пробелы

        bool ok;
        double timeValue = cleanedValue.toDouble(&ok);
        if (ok)
        {
            timeArray.append(timeValue);
        }
        else
        {
            qDebug() << "Ошибка преобразования строки:" << cleanedValue;
        }
    }

    // Преобразуем строки в числа для уровня
    for (const QString &value : std::as_const(levelValues))
    {
        QString cleanedValue = value; // Создаем копию строки
        cleanedValue.remove('[').remove(']'); // Удаляем квадратные скобки
        cleanedValue = cleanedValue.trimmed(); // Удаляем пробелы

        bool ok;
        double levelValue = cleanedValue.toDouble(&ok);
        if (ok)
        {
            levelArray.append(levelValue);
        }
        else
        {
            qDebug() << "Ошибка преобразования строки уровня:" << cleanedValue;
        }
    }

    // Отладочные сообщения
    qDebug() << "Time Array:" << timeArray;
    qDebug() << "Level Array:" << levelArray;

    // Проверяем, что массивы имеют одинаковый размер
    if (timeArray.size() != levelArray.size()) {
        // Проверяем, есть ли возможность исправить размерности
        if (timeArray.size() == 0 || levelArray.size() == 0)
        {
            QMessageBox::warning(this, "Внимание!", "Ошибка: Один из массивов пуст.");
        } else
        {
            QMessageBox::warning(this, "Внимание!", "Ошибка: Массивы не совпадают по размеру.");
        }
        return; // Обработка ошибки: массивы не совпадают по размеру
    }

    // Удаляем предыдущую серию, если она существует
    if (ui->chartView->chart()->series().size() > 0)
    {
        ui->chartView->chart()->removeAllSeries();
    }

    // Создаем серию для графика
    series = new QLineSeries();

    // Интерполяция
    const int pointsPerSegment = 200; // Количество точек между узловыми
    for (int i = 0; i < timeArray.size() - 1; ++i)
    {
        double x0 = timeArray[i];
        double y0 = levelArray[i];
        double x1 = timeArray[i + 1];
        double y1 = levelArray[i + 1];

        // Линейная интерполяция
        for (int j = 0; j <= pointsPerSegment; ++j)
        {
            double t = static_cast<double>(j) / pointsPerSegment; // Нормализованный параметр
            double interpolatedX = x0 + t * (x1 - x0);
            double interpolatedY = y0 + t * (y1 - y0);
            series->append(interpolatedX, interpolatedY);
        }
    }

    // for (int i = 0; i < timeArray.size(); ++i)
    // {
    //     series->append(timeArray[i], levelArray[i]);
    // }


    // Добавляем серию к графику
    ui->chartView->chart()->addSeries(series);
    ui->chartView->chart()->createDefaultAxes();

    // Проверяем, что массивы не пустые перед установкой диапазонов осей
    if (timeArray.isEmpty() || levelArray.isEmpty())
    {
        QMessageBox::warning(this, "Внимание!", "Ошибка: Один из массивов пуст. Диапазоны осей не будут установлены.");
    }
    else
    {
        ui->chartView->chart()->axes(Qt::Horizontal).first()->setRange(*std::min_element(timeArray.begin(), timeArray.end()),
                                                                       *std::max_element(timeArray.begin(), timeArray.end()));
        ui->chartView->chart()->axes(Qt::Vertical).first()->setRange(*std::min_element(levelArray.begin(), levelArray.end()),
                                                                     *std::max_element(levelArray.begin(), levelArray.end()));
    }

    // Подписываем оси
    auto xAxis = qobject_cast<QValueAxis *>(ui->chartView->chart()->axes(Qt::Horizontal).first());
    if (xAxis)
    {
        xAxis->setTitleText("Ось X (Время)"); // Подпись для оси X
    }

    auto yAxis = qobject_cast<QValueAxis *>(ui->chartView->chart()->axes(Qt::Vertical).first());
    if (yAxis)
    {
        yAxis->setTitleText("Ось Y (Уровень)"); // Подпись для оси Y
    }

    // Отладочное сообщение о завершении
    qDebug() << "График обновлен.";
}

void Moment_signal_builder::clearGraph()
{
    // Удаляем все серии из графика
    if (ui->chartView->chart())
    {
        ui->chartView->chart()->removeAllSeries();
    }

    // Удаляем оси (если необходимо)
    auto axes = ui->chartView->chart()->axes();

    for (auto axis : std::as_const(axes))
    {
        ui->chartView->chart()->removeAxis(axis);// Удаляем все серии из графика
    }

    // Очистка QLineEdit (если необходимо)
    ui->lineEditX->clear();
    ui->lineEditY->clear();

    // Восстанавливаем квадратные скобки в QLineEdit
    ui->lineEditX->setText("[]"); // Восстанавливаем квадратные скобки для времени
    ui->lineEditY->setText("[]"); // Восстанавливаем квадратные скобки для уровня

    // Создаем новую серию
    series = new QLineSeries();

    // Создаем новые оси
    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;

    // Устанавливаем диапазоны для осей (можно настроить по вашему усмотрению)
    axisX->setRange(0, 10); // Пример диапазона для оси X
    axisY->setRange(0, 10); // Пример диапазона для оси Y

    // Добавляем оси в график
    ui->chartView->chart()->addAxis(axisX, Qt::AlignBottom);
    ui->chartView->chart()->addAxis(axisY, Qt::AlignLeft);

    // Настройка сетки
    axisX->setGridLineVisible(true);
    axisY->setGridLineVisible(true);

    // Привязываем оси к серии (если серия уже существует)
    if (series)
    {
        series->attachAxis(axisX);
        series->attachAxis(axisY);
    }

    // Отладочное сообщение
    qDebug() << "График очищен и поля ввода восстановлены.";
}

void Moment_signal_builder::saveGraph()
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

bool Moment_signal_builder::savePointsToXml(const QString &fileName)
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

    for (const QPointF &pt : points)
    {
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

void Moment_signal_builder::loadGraph()
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

bool Moment_signal_builder::loadPointsFromXml(const QString &fileName)
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

    // Убедитесь, что series инициализирован
    if (series) {
        series = new QLineSeries(); // Создаем новый экземпляр серии
        qDebug() << "Серия обновлена новыми точками.";
    } else {
        qWarning() << "Серия не инициализирована, не удалось обновить.";
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

    // Подписываем оси
    auto xAxis = qobject_cast<QValueAxis *>(ui->chartView->chart()->axes(Qt::Horizontal).first());
    if (xAxis) {
        xAxis->setTitleText("Ось X (Время)"); // Подпись для оси X
    }

    auto yAxis = qobject_cast<QValueAxis *>(ui->chartView->chart()->axes(Qt::Vertical).first());
    if (yAxis) {
        yAxis->setTitleText("Ось Y (Уровень)"); // Подпись для оси Y
    }

    return true;
}

void Moment_signal_builder::apply_pushButton()
{
    base.momentData = series->points();

    if (series->count() == 0)
    {
        QMessageBox::warning(this, "Внимание!", "Ошибка: Нет данных для отображения в графике.");
        return; // Выход из слота, если данных нет
    }

    if (!base.momentData.isEmpty())
    {
        // Получаем последний элемент типа QPointF
        QPointF lastPoint = base.momentData.last();

        // Извлекаем координаты
        base.lastPointX = lastPoint.x();
        //double lastY = lastPoint.y();

        // Выводим значения (или используем их по вашему усмотрению)
        //qDebug() << "Последняя точка: (" << base.lastPointX << ", " << lastY << ")";
    }
    close();
}

void Moment_signal_builder::close_pushButton()
{
    close();
}
