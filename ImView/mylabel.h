#ifndef MYLABEL_H
#define MYLABEL_H

#include <QEvent>
#include <QLabel>
#include <QCursor>

class MyLabel : public QLabel {
    Q_OBJECT
public:
    MyLabel(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

signals:
    void clicked();
};

#endif // MYLABEL_H
