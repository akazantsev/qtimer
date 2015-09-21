#ifndef CIRCULARPROGRESS_H
#define CIRCULARPROGRESS_H

#include <QtQuick/QQuickPaintedItem>
#include <QColor>

class CircularProgress : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(int penWidth READ penWidth WRITE setPenWidth
               NOTIFY penWidthChanged)

public:
    CircularProgress(QQuickItem *parent = nullptr);

    int penWidth() const;
    void setPenWidth(int newPenWidth);
    int value() const;
    void setValue(int newValue);
    QColor color() const;
    void setColor(QColor newColor);

    void paint(QPainter *painter) override;

signals:
    void penWidthChanged(int newPenWidth);
    void valueChanged(int newValue);
    void colorChanged(QColor newColor);

private:
    int m_penWidth;
    int m_value;
    QColor m_color;
};

#endif // CIRCULARPROGRESS_H
