#ifndef TEPL_DANNIE_H
#define TEPL_DANNIE_H

#include <QWidget>
//#include "base_tepl.h"

namespace Ui {
class Tepl_dannie;
}

class Tepl_dannie : public QWidget
{
    Q_OBJECT

public:
    explicit Tepl_dannie(QWidget *parent = nullptr);
    ~Tepl_dannie();

    Ui::Tepl_dannie *ui;
};

#endif // TEPL_DANNIE_H
