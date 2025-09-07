#ifndef SIGNAL_BUILDER_H
#define SIGNAL_BUILDER_H

#include <QWidget>

namespace Ui {
class Signal_builder;
}

class Signal_builder : public QWidget
{
    Q_OBJECT

public:
    explicit Signal_builder(QWidget *parent = nullptr);
    ~Signal_builder();

protected slots:
    void apply_signal_builder();
    void close_signal_builder();
private:
    Ui::Signal_builder *ui;
};

#endif // SIGNAL_BUILDER_H
