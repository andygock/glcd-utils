/**
 * GLCD Tools
 *
 * A toolset for code creation for graphic LCDs usable
 * in microcontroller projects (such as Microchip)
 *
 * Author: Florian Born
 *
 * File glcdfont.cpp
 * Version: 0.1
 * last modified: 2009-05-10
 *
 * License: GPL
 */


#include "glcdfont.h"
#include <QtDebug>

//GLCDFont::GLCDFont()
//{
//    GLCDFont(0);
//}

GLCDFont::GLCDFont(QWidget* parent) : QWidget(parent)
{
    this->width  = 6;
    this->height = 8;

    font = QFont("System", 8, QFont::Normal, false);
    glcd = new GLCDPreview(this);
    glcd->setPixelSize(4);
    currentChar = 0x20;

    offsetX = 0;
    offsetY = 0;

    rotation = 0;
    rotationOffsetX = 0;
    rotationOffsetY = 0;
 }

void GLCDFont::setCharacter(QChar c)
{
    QImage i(128, 64, QImage::Format_Mono);
    QPainter p(&i);
    uchar* data;
    QByteArray scanLines;
    QRect requiredRect, minimumRect;
    QTransform transform;

    currentChar = c;

    switch(rotation)
    {
        case 0:
            rotationOffsetX = 0;
            rotationOffsetY = 0;
        break;

        case 90:
            rotationOffsetX = this->width;
            rotationOffsetY = 0;
        break;

        case 180:
            rotationOffsetX = this->width;
            rotationOffsetY = this->height;
        break;

        case 270:
            rotationOffsetX = 0;
            rotationOffsetY = this->height;
        break;

        default: break;
    }
//qDebug() << "Rot: " << rotation << ";rX: " << rotationOffsetX << ";rY: " << rotationOffsetY;
    transform.translate(offsetX+rotationOffsetX, offsetY+rotationOffsetY);
    transform.rotate(rotation);
    p.setTransform(transform);
//    p.fillRect(QRectF(0,0, 128, 64), QColor(Qt::white));
    i.fill(0xFFFFFFFF);
    p.setFont(this->font);

//    qDebug() << this->font.family();
//    p.drawText(QPoint(0,this->font.pointSize()), QString(c));

//    if (rotation != 0)  p.rotate(rotation);

//    p.drawText(QRect(offsetX,offsetY,128, 64), Qt::AlignLeft | Qt::AlignTop, QString(c), &requiredRect);
    p.drawText(QRect(0,0,128, 64), Qt::AlignLeft | Qt::AlignTop, QString(c), &requiredRect);
//    minimumRect = QRect(0,0,1,1);
//    requiredRect = p.boundingRect(minimumRect, Qt::AlignLeft | Qt::AlignTop, QString(c));

    if (requiredRect.width() > this->width || requiredRect.height() > this->height)
        showError(QString("Character does not fit specified size.\nNeeding %1x%2 pixels.").arg(requiredRect.width()).arg(requiredRect.height()));

    data = i.bits();

    ba.clear();
    scanLines.fill(0x00, i.numBytes());
    ba.fill(0x00, i.numBytes());

//    qDebug() << "bytes per line: " << i.bytesPerLine();
//    qDebug() << "num bytes: " << i.numBytes();
//    qDebug() << "num colors: " << i.numColors();

    // Sehr dreckig
    glcd->clear();

    for (int x=0; x < this->width; x++)
    {
        for (int y=0; y < this->height; y++)
        {
            QRgb rgb = i.pixel(x,y);
            if (rgb == qRgb(00,00,00))
            {
                glcd->drawPoint(x,y);
//                int index = 0;
//                index = ((y-(y%8))/8)*this->width + x;
//                ba[index] = ba[index] | (0x01 << (y%8));
            }
        }
    }
}

QByteArray GLCDFont::data()
{
    ba = glcd->data();
    return ba;
}

void GLCDFont::setPixelSize(int width, int height)
{
    this->width = width;
    this->height = height;

    glcd->setGLCDSize(width, height);
    updateChar();
}

void GLCDFont::setFont(QFont f)
{
    this->font = f;
    updateChar();
}

void GLCDFont::showError(QString s)
{
//    QErrorMessage em(this);
//    em.showMessage(s);
//    QMessageBox::warning(this, "Warning", s);
//    QWidget * parent, const QString & title, const QString & text, StandardButtons buttons = Ok, StandardButton defaultButton = NoButton
    emit error(s);
}

void GLCDFont::updateGLCD(void)
{
//    glcd->setData(&ba);
    glcd->repaint();
}

void GLCDFont::updateChar(void)
{
    setCharacter(currentChar);
    updateGLCD();
}

void GLCDFont::showCode()
{
    QString c;
    QByteArray ba;

    c = "Code: ";
    ba = glcd->data();

    for (int i=0; i<ba.size(); i++)
        c.append(QString("0x%1,").arg((uchar)ba.at(i),2,16,QChar('0')));

    QMessageBox::warning(this, "Code", c);
}

void GLCDFont::rotateCW(void)
{
    rotation += 90;
    if (rotation >= 360)  rotation -= 360;

    updateChar();
}

void GLCDFont::rotateCCW(void)
{
    rotation -= 90;
    if (rotation < 0)    rotation += 360;

    updateChar();
}

void GLCDFont::resetPosition(void)
{
    rotation = 0;
    offsetX = 0;
    offsetY = 0;

    updateChar();
}

void GLCDFont::setGLCDColor(QColor c)
{
    glcd->setGLCDColor(c);

    updateChar();
}

/**
 * Return bounding rectangle for current char
 */
QRect GLCDFont::boundingRect(void)
{
    return glcd->boundingRect();
}
