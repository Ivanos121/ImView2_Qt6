#ifndef NASTROIKI_H
#define NASTROIKI_H

#include <QDialog>
#include "QTranslator"

class MainWindow;

namespace Ui {
class Nastroiki;
}

class Nastroiki : public QDialog
{
    Q_OBJECT

public:
    explicit Nastroiki(QWidget *parent = nullptr);
    ~Nastroiki();
    MainWindow *wf;

public slots:
    void switch_language();

private slots:
    void enter_action();
    void apply_action();
    void close_action();
    void onlistWidget_itemSelectionChanged();
    void enabled_button();
    void enabled_button_2();

private:
    Ui::Nastroiki *ui;
    QTranslator qtLanguageTranslator;
};

#endif // NASTROIKI_H
