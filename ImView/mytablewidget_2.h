#ifndef MYTABLEWIDGET_2_H
#define MYTABLEWIDGET_2_H

#include <QEvent>
#include <QTableWidget>


class MyTableWidget_2: public QTableWidget {
    Q_OBJECT
public:
    explicit MyTableWidget_2(QWidget *parent = nullptr);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
};

#endif // MYTABLEWIDGET_2_H
