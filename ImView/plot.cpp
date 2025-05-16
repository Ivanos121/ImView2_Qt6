#include <QPainter>
#include <QPoint>
#include <QtMath>
#include <QWheelEvent>
#include <QDebug>
#include <QMessageBox>
#include <QRegularExpression>
#include <QFile>

#include "plot.h"

Plot::Plot(QWidget *parent) :
    QWidget(parent),
    t_offset(0),
    U_offset(0),
    gridStep(20)
{

}

Plot::~Plot()
{

}

void Plot::drawBorder()
{
    QPainter painter(this);
    QColor coordLineColor(255,255,255);

    QPen apen = QPen(coordLineColor);
    apen.setWidth(4);
    painter.setPen(apen);

    painter.drawLine(QLine(margin_left + 1,20,width() - 20 - 1,20));
    painter.drawLine(QLine(margin_left,20,margin_left,height() - margin_bottom));
    painter.drawLine(QLine(margin_left + 1,height() - margin_bottom,width() - 20 - 1,height() - margin_bottom));
    painter.drawLine(QLine(width() - 20,20,width() - 20,height() - margin_bottom));
}

void Plot::drawGrid()
{
    QPainter painter(this);
    QColor coordLineColor2(255, 255, 255);

    QPen apen2 = QPen(coordLineColor2);
    apen2.setWidthF(0.5);
    apen2.setStyle(Qt::DotLine);
    painter.setPen(apen2);

    for (double i=margin_left - gridStep * 5.0; i <= width() - 20 + gridStep * 5.0; i += gridStep)
    {
        double offset = t_offset / t_max_v * (width() -20 - margin_left);
        while (offset >= gridStep * 5.0)
        {
            offset -= gridStep * 5.0;
        }
        while (offset <= -gridStep * 5.0)
        {
            offset += gridStep * 5.0;
        }
        if (!(((i - offset) <= margin_left) || ((i - offset) >= (width() -20))))
        {
           painter.drawLine(i - offset,20,i - offset,height() - margin_bottom);
        }
    }

    for (double j=height() - margin_bottom + gridStep * 5.0; j >= 20 - gridStep * 5.0; j -= gridStep)
    {
        double offset = U_offset / U_max_v * (height() -20 - margin_bottom);
        while (offset >= gridStep * 5.0)
        {
            offset -= gridStep * 5.0;
        }
        while (offset <= -gridStep * 5.0)
        {
            offset += gridStep * 5.0;
        }
        if (!(((j - offset) <= 20) || ((j - offset) >= (height() - margin_bottom))))
        {
            painter.drawLine(QLine(margin_left,j-offset,width() - 20,j-offset));
        }
    }
}

void Plot::drawMainGrid()
{
    QPainter painter(this);
    QColor coordLineColor3(255, 255, 255);

    QPen apen3 = QPen(coordLineColor3);
    apen3.setWidthF(0.5);
    painter.setPen(apen3);

    for (double i=margin_left; i <= width() - 20 + gridStep * 5.0; i += gridStep * 5.0)
    {
        double offset = t_offset / t_max_v * (width() -20 - margin_left);
        while (offset >= gridStep * 5.0)
        {
            offset -= gridStep * 5.0;
        }
        while (offset <= -gridStep * 5.0)
        {
            offset += gridStep * 5.0;
        }
        if (!(((i - offset) <= margin_left) || ((i - offset) >= (width() -20))))
        {
           painter.drawLine(i - offset,20,i - offset,height() - margin_bottom);
        }
    }

    for (double j=height() - margin_bottom; j >= 20 - gridStep * 5.0; j -= gridStep * 5.0)
    {
        double offset = U_offset / U_max_v * (height() -20 - margin_bottom);
        while (offset >= gridStep * 5.0)
        {
            offset -= gridStep * 5.0;
        }
        while (offset <= -gridStep * 5.0)
        {
            offset += gridStep * 5.0;
        }
        if (!(((j - offset) <= 20) || ((j - offset) >= (height() - margin_bottom))))
        {
            painter.drawLine(QLine(margin_left,j-offset,width() - 20,j-offset));
        }
    }

    if ((U_offset >= 0) && (U_offset <= U_max_v))
    {
        double zero_level = height() - margin_bottom - U_offset/(U_max_v)*(height() - 20 - margin_bottom);
        QPen zeroPen(coordLineColor3);
        zeroPen.setWidthF(2.0);
        painter.setPen(zeroPen);
        painter.drawLine(QLine(margin_left,zero_level,width() - 20,zero_level));
    }

    if ((-t_offset >= 0) && (-t_offset <= t_max_v))
    {
        double zero_level = margin_left - t_offset/t_max_v*(width() - 20 - margin_left);
        QPen zeroPen(coordLineColor3);
        zeroPen.setWidthF(2.0);
        painter.setPen(zeroPen);
        painter.drawLine(zero_level,20,zero_level,height() - margin_bottom);
    }
}

void Plot::drawAxisText()
{
    QPainter painter(this);
    QColor coordLineColor(255, 255, 255);

    QPen apen = QPen(coordLineColor);
    apen.setWidth(2);
    painter.setPen(apen);
    double offset = t_offset / t_max_v * (width() -20 - margin_left);
    while (offset >= gridStep * 5.0)
    {
        offset -= gridStep * 5.0;
    }
    while (offset <= -gridStep * 5.0)
    {
        offset += gridStep * 5.0;
    }
    for (double i=margin_left; i <= width() - 20 + gridStep * 5.0; i += gridStep * 5.0)
    {
        if (!(((i - offset) <= margin_left) || ((i - offset) >= (width() -20))))
        {
           double t = (double)(i - offset - margin_left) / (double)(width() - margin_left - 20) * t_max_v + t_offset;
           if (fabs(t) < 0.0005)
           {
               t = 0.0;
           }
           painter.drawText(QPoint(i -20 -offset,height()-15), QString("%1").arg(t, 0, 'f', 3));
        }
    }

    for (double j=height() - margin_bottom; j >= 20 - gridStep * 5.0; j -= gridStep * 5.0)
    {
        double offset = U_offset / U_max_v * (height() -20 - margin_bottom);
        while (offset >= gridStep * 5.0)
        {
            offset -= gridStep * 5.0;
        }
        while (offset <= -gridStep * 5.0)
        {
            offset += gridStep * 5.0;
        }
        if (!(((j - offset) <= 20) || ((j - offset) >= (height() - margin_bottom))))
        {
            double U = (double)(-j + offset + height() - margin_bottom) / (double)(height() - margin_bottom - 20) * U_max_v - U_offset;
            if (fabs(U) < 0.0005)
            {
                U = 0.0;
            }
            painter.drawText(QPoint(20,j+5-offset), QString("%1").arg(U, 0, 'f', 3));
        }
    }

    painter.setFont(QFont("helvetica", 10));
}

void Plot::drawBackground()
{
    QPainter painter(this);

    QLinearGradient linearGrad;
    linearGrad.setColorAt( 0 , QColor(80, 80, 80));
    linearGrad.setColorAt( 1 , QColor(50, 50, 50));
    painter.fillRect(0, 0, width(), height(), linearGrad);
}

void Plot::paintEvent(QPaintEvent *)
{
    drawBackground();
    drawGrid();
    drawMainGrid();
    drawAxisText();

    QPainter painter(this);

    for (DataLine& line : dataLines)
    {
        if (!line.enabled)
        {
            continue;
        }
        //painter.setPen(QPen(QColor(line.color), 2));
        QPen pen(QBrush(), 2, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin);
        pen.setColor(QColor(line.color));
        painter.setPen(pen);

        for (int i=0 , n=line.data.size(); i < n - 1 - 1; i++)
        {
            double t1 = line.data[i].t;
            double t2 = line.data[i + 1].t;

            int x1 = (t1 - t_offset) / t_max_v * (width() -20 - margin_left) + margin_left;
            int x2 = (t2 - t_offset) / t_max_v * (width() -20 - margin_left) + margin_left;

            if ((x1 < margin_left) && (x2 < margin_left)) continue;
            if ((x1 > (width() - 20)) && (x2 > (width() - 20))) continue;

            double U1 = line.data[i].U * line.lineScale + U_offset + line.lineOffset;
            double U2 = line.data[i + 1].U * line.lineScale + U_offset + line.lineOffset;

            int y1 = (double)(-U1 / U_max_v * (double)(height() - margin_bottom - 20) + height() - margin_bottom );
            int y2 = (double)(-U2 / U_max_v * (double)(height() - margin_bottom - 20) + height() - margin_bottom );

            if ((y1 < 20) && (y2 < 20)) continue;
            if ((y1 > height() -margin_bottom) && (y2 > height() -margin_bottom)) continue;

            if (x1 < margin_left)
            {
                double k = (double)(y2 - y1) / (double)(x2 - x1);
                double b = y1 - k * x1;
                x1 = margin_left;
                y1 = k * x1 + b;
            }

            if (x2 > width() -20)
            {
                double k = (double)(y2 - y1) / (double)(x2 - x1);
                double b = y1 - k * x1;
                x2 = width() - 20;
                y2 = k * x2 + b;
            }

            if (y1 < 20)
            {
                double k = (double)(y2 - y1) / (double)(x2 - x1);
                double b = y1 - k * x1;
                x1 = (20.0 - b) / k;
                y1 = 20;
            }
            if (y1 > height() - margin_bottom)
            {
                double k = (double)(y2 - y1) / (double)(x2 - x1);
                double b = y1 - k * x1;
                x1 = (height() - margin_bottom - b) / k;
                y1 = height() - margin_bottom;
            }
            if (y2 < 20)
            {
                double k = (double)(y2 - y1) / (double)(x2 - x1);
                double b = y2 - k * x2;
                x2 = (20.0 - b) / k;
                y2 = 20;
            }
            if (y2 > height() - margin_bottom)
            {
                double k = (double)(y2 - y1) / (double)(x2 - x1);
                double b = y2 - k * x2;
                x2 = (height() - margin_bottom - b) / k;
                y2 = height() - margin_bottom;
            }

            if (x1 < margin_left) continue;
            if (x2 > width() -20) continue;

            painter.drawLine(x1,y1,x2,y2);
        }
    }

    if (leftButtonPressed)
    {
        QPen pen(Qt::white, 1, Qt::DotLine);
        painter.setPen(pen);
        painter.drawRect(p1.x(),p1.y(),p2.x() - p1.x(),p2.y() - p1.y());
    }

    drawBorder();
}

void Plot::wheelEvent(QWheelEvent *event)
{
    double t_max_new = t_max_v * (-event->angleDelta().y() / 2000.0 + 1.0);
    double delta_t = (double)(event->position().x() - margin_left)/(double)(width() - margin_left - 20) * t_max_new -
            (double)(event->position().x() - margin_left)/(double)(width() - margin_left - 20) * t_max_v;
    t_offset -= delta_t;
    t_max_v = t_max_new;

    double U_max_new = U_max_v * (-event->angleDelta().y() / 2000.0 + 1.0);
    double delta_U = (double)(-event->position().y() + height() - margin_bottom) / (double)(height() - margin_bottom - 20) *
            (U_max_new - U_max_v);

    U_max_v = U_max_new;
    U_offset += delta_U;

    gridStep /= (-event->angleDelta().y() / 2000.0 + 1.0);
    if (gridStep > 40.0)
    {
        gridStep /= 2.0;
    }
    if (gridStep < 10.0)
    {
        gridStep *= 2.0;
    }

    repaint();
}

void Plot::mouseDoubleClickEvent(QMouseEvent *)
{
    setCursor(Qt::ArrowCursor);
    reset();
    repaint();
}

void Plot::reset()
{
    t_offset = 0.0;
    U_offset = 0.0;
    gridStep = 20.0;
    t_max_v = t_max;
    U_max_v = U_max;
}

void Plot::mousePressEvent(QMouseEvent *e)
{
    p1=e->pos();
    if (e->buttons() & Qt::LeftButton)
    {
        setCursor(Qt::CrossCursor);
        p2 = p1;
        leftButtonPressed = true;
    }
    else
    {
        leftButtonPressed = false;
    }

    if (e->buttons() & Qt::MiddleButton)
    {
        t_offset_move = t_offset;
        U_offset_move = U_offset;
    }
}

void Plot::mouseReleaseEvent(QMouseEvent *)
{
    if (leftButtonPressed)
    {
        if ((p1.x() == p2.x() || (p1.y() == p2.y())))
        {
            return;
        }

        if (p1.x() > p2.x())
        {
            int temp = p1.x();
            p1.setX(p2.x());
            p2.setX(temp);
        }

        if (p1.y() > p2.y())
        {
            int temp = p1.y();
            p1.setY(p2.y());
            p2.setY(temp);
        }

        double t1 = (double)(p1.x() - margin_left)/(double)(width() - margin_left - 20) * t_max_v;
        t_offset += t1;
        t_max_v *= (p2.x() - p1.x()) / (double)(width() - margin_left - 20);

        double U1 = (double)(-p2.y() + height() - margin_bottom) / (double)(height() - margin_bottom - 20) * U_max_v;
        U_offset -= U1;
        U_max_v *= (p2.y() - p1.y()) / (double)(height() - margin_bottom - 20);
    }
    setCursor(Qt::ArrowCursor);
    leftButtonPressed = false;
    repaint();
}

void Plot::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
    {
        p2 = e->pos();
        repaint();
    }

    if (e->buttons() & Qt::MiddleButton)
    {
        double delta_t = (double)(e->pos().x() - p1.x())/(double)(width() - margin_left - 20) * t_max_v;
        double delta_U = (double)(e->pos().y() - p1.y())/(double)(height() - margin_bottom - 20) * U_max_v;
        t_offset = t_offset_move;
        U_offset = U_offset_move;
        t_offset -= delta_t;
        U_offset -= delta_U;
        repaint();
    }
}

void Plot::addPoint(size_t lineNumber, double t, double U)
{
    if (lineNumber >= dataLines.size())
    {
        return;
    }

    dataLines[lineNumber].data.push_back(DataPoint(t, U));

    double t_m = t_max_v + t_offset;
    if (t > t_m)
    {
        t_offset = t - t_max_v;
    }

    if ((U + dataLines[lineNumber].lineOffset) > (U_max_v - U_offset))
    {
        U_max_v = U + dataLines[lineNumber].lineOffset + U_offset;
    }

    if ((U + dataLines[lineNumber].lineOffset) < (-U_offset))
    {
        double newOffset = -(U + dataLines[lineNumber].lineOffset);
        U_max_v = U_max_v - U_offset + newOffset;
        U_offset = newOffset;
    }

    repaint();
}

void Plot::addDataLine(QColor color, double lineOffset)
{
    DataLine newLine(color, lineOffset, 1.0);
    dataLines.push_back(newLine);
}

void Plot::addDataLine(QColor color, double lineOffset, double lineScale)
{
    DataLine newLine(color, lineOffset, lineScale);
    dataLines.push_back(newLine);
}


void Plot::setDataLineColor(size_t lineNumber, QColor _color)
{
    if (lineNumber >= dataLines.size())
    {
        return;
    }
    dataLines[lineNumber].color = _color;
    repaint();
}

void Plot::clear()
{
    reset();
    dataLines.clear();
    repaint();
}

void Plot::save()
{
    if (dataLines.size() == 0)
    {
        return;
    }

    if (dataLines[0].data.size() == 0)
    {
        return;
    }

    QFile f("result.csv");
    f.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream fout(&f);

    for (auto& line : dataLines)
    {
        fout << line.color.name() << " ";
    }
    fout << "\n";

    for (size_t i=0; i < dataLines[0].data.size(); i++)
    {
        double t = dataLines[0].data[i].t;
        fout << t;

        for (auto& line : dataLines)
        {
            double U = line.data[i].U;
            fout << " " << U;
        }
        fout << "\n";
    }

    f.close();
}

void Plot::load()
{
    clear();
    QFile f("result.csv");
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream fin(&f);
    QString line = fin.readLine();
    QStringList list = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    int plotLinesSize = list.size();

    for (int i = 0; i < plotLinesSize; i++)
    {
        bool bStatus;
        addDataLine(list[i].remove(0,1).toUInt(&bStatus, 16), 0.0);
    }

    line = fin.readLine();
    list = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

    while (!line.isNull())
    {
        double t = list[0].toDouble();

        for (int i = 0; i < plotLinesSize; i++)
        {
            double U = list[i + 1].toDouble();
            addPoint(i, t, U);
        }

        line = fin.readLine();
        list = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    }

    f.close();
    repaint();
}

void Plot::setDataLineOffset(size_t lineNumber, double offset)
{
    if ((size_t)lineNumber < dataLines.size())
    {
        dataLines[lineNumber].lineOffset = offset;
    }
}

void Plot::setDataLineScale(size_t lineNumber, double scale)
{
    if ((size_t)lineNumber < dataLines.size())
    {
        dataLines[lineNumber].lineScale = scale;
    }
}

void Plot::enableDataLine(int lineNum, bool en)
{
    if ((size_t)lineNum < dataLines.size())
    {
        dataLines[lineNum].enabled = en;
    }
}
