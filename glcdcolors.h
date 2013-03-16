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

#ifndef GLCDCOLORS_H
#define GLCDCOLORS_H

#include <QStringList>
#include <QColor>

class GLCDColors
{
public:
    GLCDColors();

    QStringList colors(void) { return sl; }
    QColor      color(QString name);
private:
    QStringList sl;
};

#endif // GLCDCOLORS_H
