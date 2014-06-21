#include "graphicsview.h"

GraphicsView::GraphicsView(QWidget *parent) :
    QGraphicsView(parent) {
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}


/**
 * Переопределение функции масштабирования изображения
 * @brief GraphicsView::wheelEvent
 * @param event
 */
void GraphicsView::wheelEvent(QWheelEvent *event) {
    qreal scale_factor = qPow(2.0, event -> delta() / 240.0);
    qreal factor = transform().scale(scale_factor, scale_factor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (0.05 < factor && factor < 10)
        scale(scale_factor, scale_factor);
}
