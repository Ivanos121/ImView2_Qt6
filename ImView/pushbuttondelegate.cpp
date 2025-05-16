#include "pushbuttondelegate.h"

#include <QPainter>
#include <QPushButton>
#include <QStylePainter>
#include <QDebug>
#include <QTableView>
#include <QSpinBox>
#include <QFileDialog>
#include <QDoubleSpinBox>
#include <QHelpEvent>
#include <QToolTip>
#include "qabstractitemview.h"
#include "qcombobox.h"
#include "settingscanals.h"
#include "vent_settings.h"

ButtonColumnDelegate::ButtonColumnDelegate(QObject *parent) :QStyledItemDelegate(parent)
{
}

QWidget * ButtonColumnDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 0))
    {
        //выбор режима работы программы
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Осциллограф ");
        editor->insertItem(1, "Внутренний источник данных");
        editor->insertItem(2, "Чтение данных из файла для идентификации параметров схемы замещения");
        return editor;
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 1))
    {
        //загрузка или сохранение и отображение пути файла
        QPushButton * btn = new QPushButton(parent);
        const QSize BUTTON_SIZE = QSize(22, 22);
        btn->setMinimumSize(BUTTON_SIZE);
        btn->setFixedSize(BUTTON_SIZE);
        btn->setText("...");
        connect(btn,SIGNAL(clicked()), this, SLOT(btn_clicked_5()));
        return btn;
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 2))
    {
        //выбор режима работы программы
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "БВАСv1  + наблюдатель скорости (без датчика скорости)");
        editor->insertItem(1, "БВАСv1 + наблюдатель скорости (с датчиком скорости)");
        editor->insertItem(2, "БВАСv2 + наблюдатель скорости (без датчика скорости)");
        editor->insertItem(3, "БВАСv2 + наблюдатель скорости (с датчиком скорости)");
        editor->insertItem(4, "Внутренний источник данных");
        editor->insertItem(5, "Чтение данных из файла для наблюдателя скорости");
        return editor;
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 3))
    {
        //загрузка или сохранение и отображение пути файла
        QPushButton * btn = new QPushButton(parent);
        const QSize BUTTON_SIZE = QSize(22, 22);
        btn->setMinimumSize(BUTTON_SIZE);
        btn->setFixedSize(BUTTON_SIZE);
        btn->setText("...");
        connect(btn,SIGNAL(clicked()), this, SLOT(btn_clicked_6()));
        return btn;
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 4))
    {
        //загрузка или сохранение и отображение пути файла
        QPushButton * btn = new QPushButton(parent);
        const QSize BUTTON_SIZE = QSize(22, 22);
        btn->setMinimumSize(BUTTON_SIZE);
        btn->setFixedSize(BUTTON_SIZE);
        btn->setText("...");
        connect(btn,SIGNAL(clicked()), this, SLOT(btn_clicked_7()));
        return btn;
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 0))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Сохранить");
        editor->insertItem(1, "Не сохранять");
        return editor;
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 1))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Сохранить");
        editor->insertItem(1, "Не сохранять");
        return editor;
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 2))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Сохранить");
        editor->insertItem(1, "Не сохранять");
        return editor;
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 3))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Сохранить");
        editor->insertItem(1, "Не сохранять");
        return editor;
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 4))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Сохранить");
        editor->insertItem(1, "Не сохранять");
        return editor;
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 5))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Сохранить");
        editor->insertItem(1, "Не сохранять");
        return editor;
    }

    else if ((index.parent().row() == 1) && (index.row() == 0))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Автоматический");
        editor->insertItem(1, "Ручной");
        return editor;
    }
    else if ((index.parent().row() == 1) && (index.row() == 1))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    else if ((index.parent().row() == 1) && (index.row() == 2))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    else if ((index.parent().row() == 1) && (index.row() == 3))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    else if ((index.parent().row() == 1) && (index.row() == 4))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    else if ((index.parent().row() == 1) && (index.row() == 5))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    else if ((index.parent().row() == 1) && (index.row() == 6))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    else if ((index.parent().row() == 1) && (index.row() == 7))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    else if ((index.parent().row() == 2) && (index.row() == 0))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Одномассовая модель");
        editor->insertItem(1, "Двухмассовая модель");
        editor->insertItem(2, "Трехмассовая модель");
        editor->insertItem(3, "Четырехмассовая модель");
        editor->insertItem(4, "Многомассовая модель");
        return editor;
    }
    else if ((index.parent().row() == 2) && (index.row() == 1))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Одномассовая модель");
        editor->insertItem(1, "Двухмассовая модель");
        editor->insertItem(2, "Трехмассовая модель");
        editor->insertItem(3, "Четырехмассовая модель");
        editor->insertItem(4, "Многомассовая модель");
        return editor;
    }
    else if ((index.parent().row() == 2) && (index.row() == 2))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Одномассовая модель");
        editor->insertItem(1, "Двухмассовая модель");
        editor->insertItem(2, "Трехмассовая модель");
        editor->insertItem(3, "Четырехмассовая модель");
        editor->insertItem(4, "Многомассовая модель");
        return editor;
    }
    else if ((index.parent().row() == 3) && (index.row() == 0))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Принудительная вентиляция");
        editor->insertItem(1, "Независимая вентиляция");
        return editor;
    }
    else if ((index.parent().row() == 3) && (index.row() == 1))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Автоматический");
        editor->insertItem(1, "Ручной");
        return editor;
    }
    else if ((index.parent().row() == 3) && (index.row() == 2))
    {
        QPushButton * btn = new QPushButton(parent);
        const QSize BUTTON_SIZE = QSize(22, 22);
        btn->setMinimumSize(BUTTON_SIZE);
        btn->setFixedSize(BUTTON_SIZE);
        btn->setText("...");
        connect(btn,SIGNAL(clicked()), this, SLOT(btn_clicked_8()));
        return btn;
    }
    else if ((index.parent().row() == 3) && (index.row() == 3))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Учитывать");
        editor->insertItem(1, "Не учитывать");
        return editor;
    }

    else if ((index.parent().row() == 4) && (index.row() == 0))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Режим S1");
        editor->insertItem(1, "Режим S2");
        editor->insertItem(2, "Режим S3");
        editor->insertItem(3, "Режим S4");
        editor->insertItem(4, "Режим S6");
        return editor;
    }
    else if ((index.parent().row() == 4) && (index.row() == 1))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    else if ((index.parent().row() == 4) && (index.row() == 2))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    else if ((index.parent().row() == 4) && (index.row() == 3))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    else if ((index.parent().row() == 4) && (index.row() == 4))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Текущее время");
        editor->insertItem(1, "Фиксированное время");
        return editor;
    }
    else if ((index.parent().row() == 4) && (index.row() == 5))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(0);
        editor->setMaximum(6000);
        return editor;
    }

    else if ((index.parent().row() == 4) && (index.row() == 6))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Прямой пуск");
        editor->insertItem(1, "Система ТРН-АД");
        editor->insertItem(2, "Система ПЧ-АД");
        return editor;
    }
    else if ((index.parent().row() == 4) && (index.row() == 7))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(0);
        editor->setMaximum(600);
        return editor;
    }
    else if ((index.parent().row() == 4) && (index.row() == 8))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    else if ((index.parent().row() == 5) && (index.row() == 0))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    else if ((index.parent().row() == 5) && (index.row() == 1))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Статика (статор)");
        editor->insertItem(1, "Статика (упрощенный вариант)");
        editor->insertItem(2, "Статика (полный вариант)");
        editor->insertItem(3, "Динамика (расчет)");
        editor->insertItem(4, "Динамика (эксперимент)");
        editor->insertItem(5, "Двухмассовая модель (расчет)");
        editor->insertItem(6, "Двухмассовая модель (эксперимент)");
        editor->insertItem(7, "Нет");

        return editor;
    }
    else if ((index.parent().row() == 5) && (index.row() == 2))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Одномассовая модель");
        editor->insertItem(1, "Двухмассовая модель");
        editor->insertItem(2, "Трехмассовая модель");
        editor->insertItem(3, "Четырехмассовая модель");
        editor->insertItem(4, "Пятимассовая модель");
        editor->insertItem(5, "Нет");

        return editor;
    }
    else if ((index.parent().row() == 5) && (index.row() == 3))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Одномассовая модель");
        editor->insertItem(1, "Двухмассовая модель");
        editor->insertItem(2, "Трехмассовая модель");
        editor->insertItem(3, "Четырехмассовая модель");
        editor->insertItem(4, "Пятимассовая модель");
        editor->insertItem(5, "Нет");

        return editor;
    }
    else if ((index.parent().row() == 5) && (index.row() == 4))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    else if ((index.parent().row() == 6) && (index.row() == 0))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Статика");
        editor->insertItem(1, "Динамика (расчет)");
        editor->insertItem(2, "Динамика (эксперимент)");
        return editor;
    }
    else if ((index.parent().row() == 6) && (index.row() == 1))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Один вентилятор");
        editor->insertItem(1, "Независимая вентиляция");
        return editor;
    }
    else if ((index.parent().row() == 8) && (index.row() == 0))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Одномассовая модель");
        editor->insertItem(1, "Двухмассовая модель");
        return editor;
    }
    else if ((index.parent().row() == 9) && (index.row() == 0))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Одномассовая модель");
        editor->insertItem(1, "Двухмассовая модель");
        editor->insertItem(2, "Трехмассовая модель");
        editor->insertItem(3, "Четырехмассовая модель");
        editor->insertItem(4, "Пятимассовая модель");
        return editor;
    }
    else
    {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
}

//setEditorData
void ButtonColumnDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 0))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        //comboBox->addItem(value);
        if(value == "Осциллограф")
            comboBox->setCurrentIndex(0);
        else if(value == "Внутренний источник данных")
            comboBox->setCurrentIndex(1);
        else if(value == "Чтение данных из файла для идентификации параметров схемы замещения")
            comboBox->setCurrentIndex(2);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 1))
    {
        QPushButton * btn = qobject_cast<QPushButton *>(editor);
        btn->setProperty("data_value", index.data());
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 2))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        //comboBox->addItem(value);
        if(value == "БВАСv1 + наблюдатель скорости (без датчика скорости)")
            comboBox->setCurrentIndex(0);
        else if(value == "БВАСv1 + наблюдатель скорости (с датчиком скорости)")
            comboBox->setCurrentIndex(1);
        if(value == "БВАСv2 + наблюдатель скорости (без датчика скорости)")
            comboBox->setCurrentIndex(0);
        else if(value == "БВАСv2 + наблюдатель скорости (с датчиком скорости)")
            comboBox->setCurrentIndex(1);
        else if(value == "Внутренний источник данных")
            comboBox->setCurrentIndex(2);
        else if(value == "Чтение данных из файла для наблюдателя скорости")
            comboBox->setCurrentIndex(3);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 3))
    {
        QPushButton * btn = qobject_cast<QPushButton *>(editor);
        btn->setProperty("data_value", index.data());
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 4))
    {
        QPushButton * btn = qobject_cast<QPushButton *>(editor);
        btn->setProperty("data_value", index.data());
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 0))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Сохранить")
            comboBox->setCurrentIndex(0);
        else if(value == "Не сохранять")
            comboBox->setCurrentIndex(1);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 1))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Сохранить")
            comboBox->setCurrentIndex(0);
        else if(value == "Не сохранять")
            comboBox->setCurrentIndex(1);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 2))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Сохранить")
            comboBox->setCurrentIndex(0);
        else if(value == "Не сохранять")
            comboBox->setCurrentIndex(1);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 3))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Сохранить")
            comboBox->setCurrentIndex(0);
        else if(value == "Не сохранять")
            comboBox->setCurrentIndex(1);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 4))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Сохранить")
            comboBox->setCurrentIndex(0);
        else if(value == "Не сохранять")
            comboBox->setCurrentIndex(1);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 5))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Сохранить")
            comboBox->setCurrentIndex(0);
        else if(value == "Не сохранять")
            comboBox->setCurrentIndex(1);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().row() == 1) && (index.row() == 0))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Автоматический")
            comboBox->setCurrentIndex(0);
        else if(value == "Ручной")
            comboBox->setCurrentIndex(1);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().row() == 1) && (index.row() == 1))
    {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(value);
    }
    else if ((index.parent().row() == 1) && (index.row() == 2))
    {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(value);
    }
    else if ((index.parent().row() == 1) && (index.row() == 3))
    {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(value);
    }
    else if ((index.parent().row() == 1) && (index.row() == 5))
    {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(value);
    }
    else if ((index.parent().row() == 1) && (index.row() == 6))
    {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(value);
    }    
    else if ((index.parent().row() == 2) && (index.row() == 0))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Одномассовая модель")
            comboBox->setCurrentIndex(0);
        else if(value == "Двухмассовая модель")
            comboBox->setCurrentIndex(1);
        else if(value == "Трехмассовая модель")
            comboBox->setCurrentIndex(2);
        else if(value == "Четырехмассовая модель")
            comboBox->setCurrentIndex(3);
        else if(value == "Многомассовая модель")
            comboBox->setCurrentIndex(4);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().row() == 2) && (index.row() == 1))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Одномассовая модель")
            comboBox->setCurrentIndex(0);
        else if(value == "Двухмассовая модель")
            comboBox->setCurrentIndex(1);
        else if(value == "Трехмассовая модель")
            comboBox->setCurrentIndex(2);
        else if(value == "Четырехмассовая модель")
            comboBox->setCurrentIndex(3);
        else if(value == "Многомассовая модель")
            comboBox->setCurrentIndex(4);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().row() == 2) && (index.row() == 2))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Одномассовая модель")
            comboBox->setCurrentIndex(0);
        else if(value == "Двухмассовая модель")
            comboBox->setCurrentIndex(1);
        else if(value == "Трехмассовая модель")
            comboBox->setCurrentIndex(2);
        else if(value == "Четырехмассовая модель")
            comboBox->setCurrentIndex(3);
        else if(value == "Многомассовая модель")
            comboBox->setCurrentIndex(4);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().row() == 3) && (index.row() == 0))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Принудительная вентиляция")
            comboBox->setCurrentIndex(0);
        else if(value == "Независимая вентиляция")
            comboBox->setCurrentIndex(1);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().row() == 3) && (index.row() == 1))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Автоматический")
            comboBox->setCurrentIndex(0);
        else if(value == "Ручной")
            comboBox->setCurrentIndex(1);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().row() == 3) && (index.row() == 2))
    {
        QPushButton * btn = qobject_cast<QPushButton *>(editor);
        btn->setProperty("data_value", index.data());
    }
    else if ((index.parent().row() == 3) && (index.row() == 2))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Учитывать")
            comboBox->setCurrentIndex(0);
        else if(value == "Не учитывать")
            comboBox->setCurrentIndex(1);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().row() == 4) && (index.row() == 0))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Режим S1")
            comboBox->setCurrentIndex(0);
        else if(value == "Режим S2")
            comboBox->setCurrentIndex(1);
        else if(value == "Режим S3")
            comboBox->setCurrentIndex(2);
        else if(value == "Режим S4")
            comboBox->setCurrentIndex(3);
        else if(value == "Режим S6")
            comboBox->setCurrentIndex(4);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().row() == 4) && (index.row() == 1))
    {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(value);
    }
    else if ((index.parent().row() == 4) && (index.row() == 2))
    {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(value);
    }
    else if ((index.parent().row() == 4) && (index.row() == 3))
    {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(value);
    }
    else if ((index.parent().row() == 4) && (index.row() == 4))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Текущее время")
            comboBox->setCurrentIndex(0);
        else if(value == "Фиксированное время")
            comboBox->setCurrentIndex(1);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().row() == 4) && (index.row() == 5))
    {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(value);
    }

    else if ((index.parent().row() == 4) && (index.row() == 6))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        //comboBox->addItem(value);
        if(value == "Прямой пуск")
            comboBox->setCurrentIndex(0);        
        else if(value == "Система ТРН-АД")
            comboBox->setCurrentIndex(1);
        else if(value == "Система ПЧ-АД")
            comboBox->setCurrentIndex(2);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().row() == 4) && (index.row() == 7))
    {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(value);
    }
    else if ((index.parent().row() == 4) && (index.row() == 8))
    {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(value);
    }
    else if ((index.parent().row() == 5) && (index.row() == 0))
    {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(value);
    }
    else if ((index.parent().row() == 5) && (index.row() == 1))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Статика (статор)")
            comboBox->setCurrentIndex(0);
        if(value == "Статика (упрощенный вариант)")
            comboBox->setCurrentIndex(1);
        else if(value == "Статика (полный вариант)")
            comboBox->setCurrentIndex(2);
        else if(value == "Динамика (расчет)")
            comboBox->setCurrentIndex(3);
        else if(value == "Динамика (эксперимент)")
            comboBox->setCurrentIndex(4);
        else if(value == "Двухмассовая модель (расчет)")
            comboBox->setCurrentIndex(5);
        else if(value == "Двухмассовая модель (эксперимент)")
            comboBox->setCurrentIndex(6);
        else if(value == "Нет")
            comboBox->setCurrentIndex(7);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().row() == 5) && (index.row() == 2))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Одномассовая модель")
            comboBox->setCurrentIndex(0);
        if(value == "Двухмассовая модель")
            comboBox->setCurrentIndex(1);
        else if(value == "Трехмассовая модель")
            comboBox->setCurrentIndex(2);
        else if(value == "Четырехмассовая модель")
            comboBox->setCurrentIndex(3);
        else if(value == "Пятимассовая модель")
            comboBox->setCurrentIndex(4);
        else if(value == "Нет")
            comboBox->setCurrentIndex(5);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().row() == 5) && (index.row() == 3))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Одномассовая модель")
            comboBox->setCurrentIndex(0);
        if(value == "Двухмассовая модель")
            comboBox->setCurrentIndex(1);
        else if(value == "Трехмассовая модель")
            comboBox->setCurrentIndex(2);
        else if(value == "Четырехмассовая модель")
            comboBox->setCurrentIndex(3);
        else if(value == "Пятимассовая модель")
            comboBox->setCurrentIndex(4);
        else if(value == "Нет")
            comboBox->setCurrentIndex(5);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().row() == 5) && (index.row() == 4))
    {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(value);
    }
    else if ((index.parent().row() == 6) && (index.row() == 0))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Статика (статор)")
            comboBox->setCurrentIndex(0);
        else if(value == "Динамика (расчет)")
            comboBox->setCurrentIndex(1);
        else if(value == "Динамика (эксперимент)")
            comboBox->setCurrentIndex(2);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().row() == 6) && (index.row() == 1))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Один вентилятор")
            comboBox->setCurrentIndex(0);
        else if(value == "Независимая вентиляция")
            comboBox->setCurrentIndex(1);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().row() == 8) && (index.row() == 0))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Одномассовая модель")
            comboBox->setCurrentIndex(0);
        else if(value == "Двухмассовая модель")
            comboBox->setCurrentIndex(1);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().row() == 9) && (index.row() == 0))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Одномассовая модель")
            comboBox->setCurrentIndex(0);
        else if(value == "Двухмассовая модель")
            comboBox->setCurrentIndex(1);
        else if(value == "Трехмассовая модель")
            comboBox->setCurrentIndex(2);
        else if(value == "Четырехмассовая модель")
            comboBox->setCurrentIndex(3);
        else if(value == "Пятимассовая модель")
            comboBox->setCurrentIndex(4);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
        else
    {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void ButtonColumnDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 0))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 1))
    {
        QPushButton *btn = qobject_cast<QPushButton *>(editor);
        model->setData(index, btn->property("data_value"));
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 2))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 3))
    {
        QPushButton *btn = qobject_cast<QPushButton *>(editor);
        model->setData(index, btn->property("data_value"));
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 4))
    {
        QPushButton *btn = qobject_cast<QPushButton *>(editor);
        model->setData(index, btn->property("data_value"));
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 0))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 1))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 2))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 3))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 4))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 5))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().row() == 1) && (index.row() == 0))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().row() == 2) && (index.row() == 0))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().row() == 2) && (index.row() == 1))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().row() == 2) && (index.row() == 2))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().row() == 3) && (index.row() == 0))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().row() == 3) && (index.row() == 1))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().row() == 3) && (index.row() == 2))
    {
        QPushButton *btn = qobject_cast<QPushButton *>(editor);
        model->setData(index, btn->property("data_value"));
    }
    else if ((index.parent().row() == 3) && (index.row() == 3))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().row() == 4) && (index.row() == 0))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().row() == 4) && (index.row() == 1))
    {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->interpretText();
        double value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    }
    else if ((index.parent().row() == 4) && (index.row() == 2))
    {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->interpretText();
        double value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    }
    else if ((index.parent().row() == 4) && (index.row() == 3))
    {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->interpretText();
        double value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    }
    else if ((index.parent().row() == 4) && (index.row() == 4))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().row() == 4) && (index.row() == 5))
    {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->interpretText();
        double value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    }
    else if ((index.parent().row() == 4) && (index.row() == 6))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().row() == 4) && (index.row() == 7))
    {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->interpretText();
        double value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    }
    else if ((index.parent().row() == 4) && (index.row() == 8))
    {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->interpretText();
        double value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    }

    // else if ((index.parent().row() == 4) && (index.row() == 0))
    // {
    //     QComboBox *comboBox = static_cast<QComboBox*>(editor);
    //     QString value = comboBox->currentText();
    //     model->setData(index, value);
    // }
    // else if ((index.parent().row() == 4) && (index.row() == 1))
    // {
    //     QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
    //     spinBox->interpretText();
    //     double value = spinBox->value();
    //     model->setData(index, value, Qt::EditRole);
    // }
    // else if ((index.parent().row() == 4) && (index.row() == 2))
    // {
    //     QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
    //     spinBox->interpretText();
    //     double value = spinBox->value();
    //     model->setData(index, value, Qt::EditRole);
    // }
    // else if ((index.parent().row() == 4) && (index.row() == 3))
    // {
    //     QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
    //     spinBox->interpretText();
    //     double value = spinBox->value();
    //     model->setData(index, value, Qt::EditRole);
    // }
    // else if ((index.parent().row() == 4) && (index.row() == 4))
    // {
    //     QComboBox *comboBox = static_cast<QComboBox*>(editor);
    //     QString value = comboBox->currentText();
    //     model->setData(index, value);
    // }
    // else if ((index.parent().row() == 4) && (index.row() == 5))
    // {
    //     QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
    //     spinBox->interpretText();
    //     double value = spinBox->value();
    //     model->setData(index, value, Qt::EditRole);
    // }
    // else if ((index.parent().row() == 4) && (index.row() == 6))
    // {
    //     QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
    //     spinBox->interpretText();
    //     double value = spinBox->value();
    //     model->setData(index, value, Qt::EditRole);
    // }
    else if ((index.parent().row() == 5) && (index.row() == 0))
    {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->interpretText();
        double value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    }
    else if ((index.parent().row() == 5) && (index.row() == 1))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().row() == 5) && (index.row() == 2))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().row() == 5) && (index.row() == 3))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().row() == 5) && (index.row() == 4))
    {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->interpretText();
        double value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    }
    else if ((index.parent().row() == 6) && (index.row() == 0))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().row() == 6) && (index.row() == 1))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().row() == 8) && (index.row() == 0))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().row() == 9) && (index.row() == 0))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
        else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void ButtonColumnDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}

void ButtonColumnDelegate::btn_clicked_4()
{
    QString projectFile_4 = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.cpp *.h");
    if(projectFile_4 != "")
    {
        emit projectFileSelected_4(projectFile_4);
    }
}

void ButtonColumnDelegate::btn_clicked_5()
{
    QString projectFile_5 = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.cpp *.h");
    if(projectFile_5 != "")
    {
        emit projectFileSelected_5(projectFile_5);
    }
}

void ButtonColumnDelegate::btn_clicked_6()
{
    QString projectFile_6 = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.cpp *.h");
    if(projectFile_6 != "")
    {
        emit projectFileSelected_6(projectFile_6);
    }
}

void ButtonColumnDelegate::btn_clicked_7()
{
    SettingsCanals *settinпsСanals = new SettingsCanals();
    settinпsСanals->show();
}

void ButtonColumnDelegate::btn_clicked_8()
{
    Vent_settings *vent_settings = new Vent_settings();
    vent_settings->show();
}

bool ButtonColumnDelegate::helpEvent( QHelpEvent* e, QAbstractItemView* view,
                                      const QStyleOptionViewItem& option, const QModelIndex& index )
{
    if (!e || !view)
        return false;
    if (e->type() == QEvent::ToolTip)
    {
        QVariant tooltip = index.data(Qt::DisplayRole);
        if (tooltip.canConvert<QString>()) {
            QString src=tooltip.toString();
            QToolTip::showText( e->globalPos(), QString("<div>%1</div>").arg(src.toHtmlEscaped()), view);
            return true;
        }
        if (!QStyledItemDelegate::helpEvent( e, view, option, index))
            QToolTip::hideText();
        return true;
    }

    return QStyledItemDelegate::helpEvent( e, view, option, index);
}
