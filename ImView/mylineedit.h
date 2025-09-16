#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>
#include <QKeyEvent>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MyLineEdit(QWidget *parent = nullptr) : QLineEdit(parent)
    {
        // Инициализация с квадратными скобками
        setText("[");
        setCursorPosition(1); // Устанавливаем курсор между скобками
        setAlignment(Qt::AlignLeft); // Выравнивание текста влево
    }
protected:
    void keyPressEvent(QKeyEvent *event) override
    {
        // Запрещаем удаление первой позиции
        if (cursorPosition() == 0 && event->key() == Qt::Key_Backspace)
        {
            return; // Игнорируем нажатие клавиши
        }
        QLineEdit::keyPressEvent(event); // Обрабатываем остальные нажатия
    }

    void focusOutEvent(QFocusEvent *event) override
    {
        // Убедитесь, что текст всегда начинается с '[' и заканчивается на ']'
        QString currentText = text();
        if (!currentText.startsWith('['))
        {
            currentText.prepend('[');
        }
        if (!currentText.endsWith(']'))
        {
            currentText.append(']');
        }
        setText(currentText);
        setCursorPosition(1); // Устанавливаем курсор между скобками
        QLineEdit::focusOutEvent(event);
    }

    void resizeEvent(QResizeEvent *event) override
    {
        QLineEdit::resizeEvent(event);
        // Устанавливаем правую скобку в конце текста
        QString currentText = text();
        if (!currentText.endsWith(']'))
        {
            setText(currentText + ']');
            setCursorPosition(1); // Устанавливаем курсор между скобками
        }
    }
};

#endif // MYLINEEDIT_H
