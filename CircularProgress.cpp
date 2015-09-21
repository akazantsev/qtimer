#include <QPainter>

#include "CircularProgress.h"

CircularProgress::CircularProgress(QQuickItem *parent) :
    QQuickPaintedItem(parent), m_penWidth(10), m_value(0), m_color(0, 0, 0)
{

}

int CircularProgress::penWidth() const
{
    return m_penWidth;
}

void CircularProgress::setPenWidth(int newPenWidth)
{
    if (newPenWidth != m_penWidth)
    {
        m_penWidth = newPenWidth;
        emit penWidthChanged(newPenWidth);
    }
}

int CircularProgress::value() const
{
    return m_value;
}

void CircularProgress::setValue(int newValue)
{
    if (newValue != m_value)
    {
        m_value = newValue;
        update();
        emit valueChanged(newValue);
    }
}

QColor CircularProgress::color() const
{
    return m_color;
}

void CircularProgress::setColor(QColor newColor)
{
    if (newColor != m_color)
    {
        m_color = newColor;
        emit colorChanged(newColor);
    }
}

void CircularProgress::paint(QPainter *painter)
{
    int startAngle = 90 * 16;
    const int halfPenWidth = penWidth() / 2;
    const QRectF rect = boundingRect().adjusted(halfPenWidth, halfPenWidth,
                                                -halfPenWidth, -halfPenWidth);

    painter->setRenderHint(QPainter::Antialiasing, true);

    QPen progressBarPen(QColor(140, 140, 140), penWidth());
    painter->setPen(progressBarPen);
    painter->drawArc(rect, startAngle, 360 * 16 - value());

    QPen progressPen(m_color, penWidth());
    painter->setPen(progressPen);
    painter->drawArc(rect, startAngle, -value());
}
