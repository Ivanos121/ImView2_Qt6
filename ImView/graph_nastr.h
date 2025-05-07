#ifndef GRAPH_NASTR_H
#define GRAPH_NASTR_H

#include <QWidget>

namespace Ui {
class graph_nastr;
}

class graph_nastr : public QWidget
{
    Q_OBJECT

public:
    explicit graph_nastr(QWidget *parent = nullptr);
    ~graph_nastr();

private:
    Ui::graph_nastr *ui;
};

#endif // GRAPH_NASTR_H
