#ifndef VENT_SETTINGS_H
#define VENT_SETTINGS_H

#include <QWidget>

namespace Ui {
class Vent_settings;
}

class Vent_settings : public QWidget
{
    Q_OBJECT

public:
    explicit Vent_settings(QWidget *parent = nullptr);
    ~Vent_settings();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::Vent_settings *ui;
};

#endif // VENT_SETTINGS_H
