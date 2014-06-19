#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QtMath>
#include <QWheelEvent>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(QWidget *parent = 0);

protected:
    virtual void wheelEvent(QWheelEvent *event);
signals:

public slots:

};

#endif // GRAPHICSVIEW_H
