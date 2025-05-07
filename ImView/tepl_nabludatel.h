#ifndef TEPL_NABLUDATEL_H
#define TEPL_NABLUDATEL_H

#include <QWidget>

namespace Ui {
class tepl_nabludatel;
}

class tepl_nabludatel : public QWidget
{
    Q_OBJECT

public:
    explicit tepl_nabludatel(QWidget *parent = nullptr);
    ~tepl_nabludatel();

public:
    Ui::tepl_nabludatel *ui;
};

#endif // TEPL_NABLUDATEL_H
