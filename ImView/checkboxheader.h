#ifndef CHECKBOXHEADER_H
#define CHECKBOXHEADER_H

#include <QHeaderView>
#include <QSplitter>
#include <QMessageBox>


class CheckBoxHeader : public QHeaderView
{
    Q_OBJECT

public:
    explicit CheckBoxHeader(Qt::Orientation orientation, QWidget* parent = nullptr);
    ~CheckBoxHeader() override;

    bool isChecked1() const { return isChecked_1; }
    bool isChecked2() const { return isChecked_2; }
    void setIsChecked1(bool val);
    void setIsChecked2(bool val);
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void checkBoxClicked1(bool state);
    void checkBoxClicked2(bool state);

protected:
    void paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const override;

private:
    bool isChecked_1;
    bool isChecked_2;
    void redrawCheckBox();
};

#endif // CHECKBOXHEADER_H
