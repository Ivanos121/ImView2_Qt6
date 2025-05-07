#ifndef DRAW_LINE_NEW_H
#define DRAW_LINE_NEW_H

#include <QWidget>
#include <QWebEngineView>

namespace Ui {
class draw_line_new;
}

class draw_line_new : public QWidget
{
    Q_OBJECT

public:
    explicit draw_line_new(QWidget *parent = nullptr);
    ~draw_line_new();

public:
    Ui::draw_line_new *ui;
    QWebEngineView *view;
};

#endif // DRAW_LINE_NEW_H
