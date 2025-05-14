#ifndef MYSVGWIDGET_H
#define MYSVGWIDGET_H

#include <QSvgWidget>

class MySvgWidget:public QSvgWidget
{
    Q_OBJECT

public:
    MySvgWidget(QWidget *parent = nullptr);
    void loadFile();
    void loadSelectedFile();    
    QString svgFileName;
    QString svgSelectedFileName;

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;    
};

#endif // MYSVGWIDGET_H
