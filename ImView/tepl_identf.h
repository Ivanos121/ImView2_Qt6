#ifndef TEPL_IDENTF_H
#define TEPL_IDENTF_H

#include <QWidget>
#include <QElapsedTimer>

namespace Ui {
class Tepl_identf;
}

class Tepl_identf : public QWidget
{
    Q_OBJECT

public:
    explicit Tepl_identf(QWidget *parent = nullptr);
    ~Tepl_identf();
    Ui::Tepl_identf *ui;

private:

    QElapsedTimer *time;
};

#endif // TEPL_IDENTF_H
