#include "qdebug.h"
#include <QPoint>

double linearInterpolation(const QVector<QPointF>& data, double t) {
    // Проверка на наличие данных
    if (data.isEmpty()) {
        qDebug() << "Ошибка: массив данных пуст.";
        return 0.0; // Возвращаем 0.0 в случае ошибки
    }

    if (data.last().x() < t)
    {
        return data.last().y();
    }

    // Ищем две ближайшие точки
    QPointF point1, point2;
    bool found = false;

    for (int i = 0; i < data.size() - 1; ++i) {
        if (t >= data[i].x() && t <= data[i + 1].x()) {
            point1 = data[i];
            point2 = data[i + 1];
            found = true;
            break;
        }
    }

    // Если t вне диапазона данных
    if (!found) {
        qDebug() << "Ошибка: значение времени вне диапазона.";
        return 0.0; // Возвращаем 0.0 в случае ошибки
    }

    // Линейная интерполяция
    double t1 = point1.x();
    double V1 = point1.y();
    double t2 = point2.x();
    double V2 = point2.y();

    double V = V1 + (V2 - V1) / (t2 - t1) * (t - t1);
    return V;
}
