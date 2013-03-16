/**
 * GLCD Tools
 *
 * A toolset for code creation for graphic LCDs usable
 * in microcontroller projects (such as Microchip)
 *
 * Author: Florian Born
 *
 * File glcdcolors.h
 * Version: 0.1
 * last modified: 2009-05-10
 *
 * License: GPL
 */

#ifndef GLCDFONT_H
#define GLCDFONT_H

#include <QtWidgets/QWidget>
#include <QByteArray>
#include <QSize>
#include <QChar>
#include <QImage>
#include <QPainter>
#include <QFont>
#include <QtWidgets/QErrorMessage>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QGridLayout>
#include <QColor>

#include "glcdpreview.h"

class GLCDFont : public QWidget
{
    Q_OBJECT

public:
    GLCDFont(QWidget* parent=0);

    void setCharacter(QChar c);
    QByteArray data();
    void setPixelSize(QSize s) {setPixelSize(s.width(), s.height());}
    void setPixelSize(int width, int height);
    void setFont(QFont f);
    GLCDPreview* glcdWidget() {return glcd;}
    void updateGLCD(void);
    void updateChar(void);

    void incOffsetX(void) {offsetX++; updateChar();}
    void incOffsetY(void) {offsetY++; updateChar();}
    void decOffsetX(void) {offsetX--; updateChar();}
    void decOffsetY(void) {offsetY--; updateChar();}
    void setOffsetX(int x) {offsetX = x; updateChar();}
    void setOffsetY(int y) {offsetY = y; updateChar();}

    void rotateCCW(void);
    void rotateCW(void);
    void resetPosition(void);

    void setGLCDColor(QColor c);

    int getRotation(void) { return rotation; }

    QRect boundingRect(void);
    // test
    void showCode(void);
private:
    QByteArray ba;
    GLCDPreview* glcd;
    QImage image;
    QFont font;
    QChar currentChar;
    int width;
    int height;
    int offsetX, offsetY;
    int rotationOffsetX, rotationOffsetY;
    int rotation;

    void showError(QString s);
signals:
    void error(QString s);
};

#endif // GLCDFONT_H
