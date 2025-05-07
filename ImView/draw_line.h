#ifndef DRAW_LINE_H
#define DRAW_LINE_H

#include <QWidget>
#include <QWebEngineView>

namespace Ui {
class draw_line;
}

class draw_line : public QWidget
{
    Q_OBJECT

public:
    explicit draw_line(QWidget *parent = nullptr);
    ~draw_line();

public:
    Ui::draw_line *ui;
    QWebEngineView *view;
};

#endif // DRAW_LINE_NEW_H
