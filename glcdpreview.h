/**
 * GLCD Tools
 *
 * A toolset for code creation for graphic LCDs usable
 * in microcontroller projects (such as Microchip)
 *
 * Author: Florian Born
 *
 * File glcdpreview.h
 * Version: 0.2
 * last modified: 2009-05-15
 *
 * License: GPL
 */

#ifndef GLCDPREVIEW_H
#define GLCDPREVIEW_H

#include <QWidget>
#include <QColor>

class GLCDPreview : public QWidget
{
    Q_OBJECT

public:
    GLCDPreview(QWidget* parent = 0);
//    ~GLCDPreview() {}
    void setGLCDColor(QColor color);
    void drawPoint(int x, int y);
    void drawPoint(QPoint point);
    void setGLCDSize(int width, int height);
    void setData(QByteArray* ba);
    QByteArray data();
    void setPixelSize(int i);
    void setZoomFactor(double z);
    QRect boundingRect(void);
    void clear(void);
private:
    int width, height, pixelSize;
    int pixmapHeight, pixmapWidth;
    double zoomFactor;
    QList<QPoint> points;
    QPixmap pixmap;
    void drawGrid(QPainter* p);
    void drawPoints(QPainter* p);
    QSize size(void);
    QColor colorDark;
    QColor colorLight;
    QColor colorFrame;
    //static QPointer<GLCDPreview> _self;

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
//    void closeEvent( QCloseEvent* );

};

#endif // GLCDPREVIEW_H
