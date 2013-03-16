/**
 * GLCD Tools
 *
 * A toolset for code creation for graphic LCDs usable
 * in microcontroller projects (such as Microchip)
 *
 * Author: Florian Born
 *
 * File glcdpreview.cpp
 * Version: 0.2
 * last modified: 2009-05-15
 *
 * License: GPL
 */

#include <QtGui>
#include <QtWidgets/QMessageBox>
#include "glcdpreview.h"

GLCDPreview::GLCDPreview(QWidget* parent) : QWidget(parent)
{
    setGLCDColor(QColor(0, 0, 255));
    setGLCDSize(1, 1);

    setBackgroundRole(QPalette::Dark);
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFocusPolicy(Qt::StrongFocus);
    setPixelSize(2);
//    refreshPixmap();
}

void GLCDPreview::setGLCDColor(QColor color)
{
    colorLight = color;
    colorDark = colorLight.darker(400);
    colorFrame = colorDark.darker(150);
}

void GLCDPreview::drawPoint(int x, int y)
{
    QPoint p;

    p.setX(x);
    p.setY(y);

    drawPoint(p);
}

void GLCDPreview::drawPoint(QPoint point)
{
    points.append(point);

    //refreshPixmap();
}

void GLCDPreview::clear(void)
{
    points.clear();
}

void GLCDPreview::paintEvent(QPaintEvent * /* event */)
{
//    QStylePainter painter(this);
    QPainter painter(this);
    QTransform transform;

    transform.scale(zoomFactor, zoomFactor);
    painter.setTransform(transform);

    painter.setPen(QPen(colorDark));
    painter.fillRect(0, 0, pixmapWidth, pixmapHeight, Qt::SolidPattern);
//    transform.translate(currentPan.x(), currentPan.y());
//    painter.setTransform(transform);
//    painter.save();
//    painter.setRenderHint(QPainter::Antialiasing);

    drawGrid(&painter);
    drawPoints(&painter);
//    painter.setRenderHint(QPainter::Antialiasing);
//    painter.drawPixmap(0, 0, pixmap);
}

void GLCDPreview::resizeEvent(QResizeEvent * /* event */)
{
//    repaint();
}

void GLCDPreview::setGLCDSize(int width, int height)
{
    this->width  = width;
    this->height = height;
    //this->parent()->resize(size());
    clear();
    resize(size());
}

QSize GLCDPreview::size(void)
{
    QSize s;

    pixmapHeight = (this->height * 3) + 1;
    pixmapWidth = (this->width * 3);

    s.setHeight(pixmapHeight);
    s.setWidth(pixmapWidth);

    return s;
}

void GLCDPreview::drawGrid(QPainter* p)
{
    QBrush brush;
    //brush.setColor(colorLight);
    brush.setColor(colorDark);
    brush.setStyle(Qt::SolidPattern);

    p->setPen(QPen(brush, 0.2));

    // Horizontale Striche
    for (int i=0; i<pixmapHeight; i = i+3)
    {
        p->drawLine(0, i, pixmapWidth, i);
    }

    // Vertikale Striche
    for (int i=0; i<pixmapWidth; i = i+3)
    {
        p->drawLine(i, 0, i, pixmapHeight);
    }
}

void GLCDPreview::drawPoints(QPainter* p)
{
    QBrush brush;
    brush.setColor(colorLight);
    brush.setStyle(Qt::SolidPattern);

    p->setPen(QPen(brush, 1));

    for (int i=0; i<points.size(); i++)
    {
        p->drawPoint((points.at(i).x() * 3)+1, (points.at(i).y()*3)+1);
        p->drawPoint((points.at(i).x() * 3)+1, (points.at(i).y()*3)+2);
        p->drawPoint((points.at(i).x() * 3)+2, (points.at(i).y()*3)+1);
        p->drawPoint((points.at(i).x() * 3)+2, (points.at(i).y()*3)+2);

//        p->drawRect((points.at(i).x() * (pixelSize+1))+1, (points.at(i).y() * (pixelSize+1))+1, 1, 1);
    }
}

void GLCDPreview::setData(QByteArray* ba)
{
    char byte;
    int x,y;

    points.clear();         // Clear current data

    for(int i=0; i < ba->size(); i++)
    {
        byte = ba->at(i);

        for (int bit=0; bit < 8; bit++)
        {
            if ((byte & (0x01<<bit)) == (0x01<<bit))
            {
                x = i%(this->width);
                y = ((i-x)/(this->width))*8;
                y += bit;
                points.append(QPoint(x,y));
            }
        }
    }

    repaint();
}

QByteArray GLCDPreview::data()
{
    QByteArray ba, replacement;
    int index=0;
    int x,y;
    char byte;
    int byteCount;

    byteCount = (int)ceil((double)this->height/8.0);
    byteCount *= this->width;

    ba.fill(0x00, byteCount);

    for (int i=0; i<points.size(); i++)
    {
        index = 0;

        x = points.at(i).x();
        y = points.at(i).y();

        index += ((y-(y%8))/8)*this->width;
        index += points.at(i).x();

        if (index >= byteCount)
        {
            QMessageBox::warning(this, "Fatal Error", "index out of bounds");
        }
        else
        {
            byte = ba.at(index);

            byte |= (0x01 << (y%8));
            replacement.clear();
            replacement.append(byte);

            ba.replace(index, 1, replacement);
        }
    }

    return ba;
}

void GLCDPreview::setPixelSize(int i)
{
    pixelSize = i;
    zoomFactor = i/2;
    update();
}

void GLCDPreview::setZoomFactor(double z)
{
    zoomFactor = z;
    update();
}

QRect GLCDPreview::boundingRect(void)
{
    int minX, minY, maxX, maxY;

    minX = minY = maxX = maxY = -1;

    minX = maxX = points.at(0).x();
    minY = maxY = points.at(0).y();

    if (points.size() > 1)
    {
        for (int i=1; i<points.size(); i++)
        {
            if (points.at(i).x() < minX)    minX = points.at(i).x();
            if (points.at(i).y() < minY)    minY = points.at(i).y();
            if (points.at(i).x() > maxX)    maxX = points.at(i).x();
            if (points.at(i).y() > maxY)    maxY = points.at(i).y();
        }
    }

    return QRect(QPoint(minX,minY), QPoint(maxX,maxY));
}
